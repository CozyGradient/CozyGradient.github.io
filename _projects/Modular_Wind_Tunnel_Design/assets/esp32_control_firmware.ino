/* ============================================================
   ESP32 CYD — Fan & LED Controller (standalone, no Arduino)
   ============================================================
   All control runs directly from the CYD expansion header.
   No external microcontroller needed.

   ┌─────────────────────────────────────────────────────────┐
   │  LED Strip (12 V)                                       │
   │    12 V PSU + ─────────────────── LED strip + (red)    │
   │    LED strip – (black) ── IRFZ44N Drain                │
   │    IRFZ44N Source ──────────────── PSU GND / CYD GND   │
   │    IRFZ44N Gate  ── 100 Ω ──────── GPIO27              │
   │    Gate also needs 10 kΩ to GND (keeps FET off at boot)│
   │                                                         │
   │  PWM Fan (12 V 4-wire)                                  │
   │    Fan red    ── 12 V PSU +                             │
   │    Fan black  ── PSU GND / CYD GND                     │
   │    Fan blue   (PWM in)  ── 1 kΩ ── GPIO22             │
   │    Fan yellow (Tach out) ────────── GPIO35              │
   │      GPIO35 is input-only; fan tach is open-collector  │
   │      so add 10 kΩ from GPIO35 to 3.3 V                 │
   │                                                         │
   │  Common GND between CYD and 12 V PSU required          │
   └─────────────────────────────────────────────────────────┘

   Pin summary (expansion header only):
     GPIO27 — LED strip PWM via IRFZ44N MOSFET
     GPIO22 — Fan PWM control (25 kHz, ledc channel 0)
     GPIO35 — Fan tach input (input-only pin, interrupt)

   LVGL / display pins are unchanged from stock CYD config.
============================================================ */

#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

/* ── Touchscreen SPI ── */
#define XPT2046_IRQ  36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK  25
#define XPT2046_CS   33

SPIClass touchscreenSPI = SPIClass(HSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

/* ── Display ── */
#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 320

/* ── Output pins ── */
#define PIN_LED_PWM   27    /* MOSFET gate for LED strip   */
#define PIN_FAN_PWM   22    /* Fan PWM control signal      */
#define PIN_FAN_TACH  35    /* Fan tach — input only       */

/* ── ledc settings ── */
#define LEDC_FAN_FREQ 25000   /* 25 kHz — Intel 4-wire fan spec */
#define LEDC_LED_FREQ 1000    /* 1 kHz for LED strip MOSFET     */
#define LEDC_RES      8       /* 8-bit: 0-255                   */

/* ── Tachometer ── */
static volatile uint32_t tachPulses = 0;
static uint32_t          lastRpmMs  = 0;
#define RPM_INTERVAL 500   /* ms between RPM updates */

void IRAM_ATTR tach_isr() {
  tachPulses++;
}

/* ── LVGL objects ── */
lv_obj_t *tabview, *tab_fan, *tab_led, *tab_info;
lv_obj_t *slider_fan, *sw_fan, *slider_led, *sw_led;
lv_obj_t *lbl_rpm, *lbl_fan_pct, *lbl_led_pct;
#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

/* ── Screensaver ──────────────────────────────────────────────────
   Poppins Bold requires a pre-generated LVGL font file:
     1. Download Poppins-Bold.ttf from Google Fonts
     2. Go to https://lvgl.io/tools/fontconverter
     3. Upload the .ttf, set size=72, bpp=4, name=poppins_bold_72
     4. Add the generated .c file to your sketch folder
     5. Declare and swap it in here:
          LV_FONT_DECLARE(poppins_bold_72);
          #define SAVER_FONT (&poppins_bold_72)
   Until then, Montserrat 48 is used as a stand-in.
   Ensure LV_FONT_MONTSERRAT_48 1 is set in lv_conf.h.
─────────────────────────────────────────────────────────────────── */

#define SAVER_FONT       (&lv_font_montserrat_48)
#define SAVER_TIMEOUT_MS  15000

static lv_obj_t *scr_saver    = NULL;
static lv_obj_t *scr_main_ref = NULL;
static bool      saver_active  = false;
static uint32_t  lastTouchMs   = 0;   /* millis() of last confirmed touch */

/* ── Touch read with affine calibration ──
   To recalibrate: run cyd_touch_calibrate.ino and replace the
   six values below with the ones printed in Serial Monitor.
*/
void touchscreen_read(lv_indev_t * indev, lv_indev_data_t * data) {
  if (touchscreen.tirqTouched() && touchscreen.touched()) {
    TS_Point p = touchscreen.getPoint();
    /* Reject noise — ghost reads have very low x/y */
    if (p.x < 200 || p.y < 200 || p.z < 400) {
      data->state = LV_INDEV_STATE_RELEASED;
      return;
    }
    /* Record touch time for our own inactivity timer */
    lastTouchMs = millis();
    if (saver_active) {
      data->state = LV_INDEV_STATE_RELEASED;
      return;
    }
    /* Calibration coefficients from cyd_touch_calibrate.ino */
    const float alpha_x =  0.124f;
    const float beta_x  = -0.032f;
    const float delta_x = -20.114f;
    const float alpha_y = -0.028f;
    const float beta_y  =  0.093f;
    const float delta_y = -15.823f;
    /* Affine transform — display rotated 90 degrees, axes swapped */
    int x = (int)(alpha_y * p.x + beta_y * p.y + delta_y);
    int y = (int)(alpha_x * p.x + beta_x * p.y + delta_x);
    x = max(0, min(x, (int)SCREEN_WIDTH  - 1));
    y = max(0, min(y, (int)SCREEN_HEIGHT - 1));
    /* Calibration + 270° rotation already handled by affine coefficients above */
    data->point.x = x;
    data->point.y = y;
    data->state   = LV_INDEV_STATE_PRESSED;
  } else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

/* ── Apply fan duty cycle ── */
static void apply_fan(int pct) {
  int duty = lv_obj_has_state(sw_fan, LV_STATE_CHECKED) ?
    map(pct, 0, 100, 0, 255) : 0;

  /* Updated for v3.0+: Use pin directly */
  ledcWrite(PIN_FAN_PWM, duty);

  char buf[8];
  snprintf(buf, sizeof(buf), "%d%%",
    lv_obj_has_state(sw_fan, LV_STATE_CHECKED) ? pct : 0);
  lv_label_set_text(lbl_fan_pct, buf);
  Serial.printf("[FAN] duty=%d (%d%%)\n", duty, pct);
}

/* ── Apply LED duty cycle ── */
static void apply_led(int pct) {
  int duty = lv_obj_has_state(sw_led, LV_STATE_CHECKED) ?
    map(pct, 0, 100, 0, 255) : 0;

  /* Updated for v3.0+: Use pin directly */
  ledcWrite(PIN_LED_PWM, duty);

  char buf[8];
  snprintf(buf, sizeof(buf), "%d%%",
    lv_obj_has_state(sw_led, LV_STATE_CHECKED) ? pct : 0);
  lv_label_set_text(lbl_led_pct, buf);
  Serial.printf("[LED] duty=%d (%d%%)\n", duty, pct);
}

/* ── Callbacks ── */
static void fan_event_cb(lv_event_t * e) {
  apply_fan(lv_slider_get_value(slider_fan));
}

static void led_event_cb(lv_event_t * e) {
  apply_led(lv_slider_get_value(slider_led));
}

/* ── GUI ── */
void lv_create_main_gui(void) {
  lv_obj_t *scr = lv_screen_active();
  tabview = lv_tabview_create(scr);
  lv_tabview_set_tab_bar_size(tabview, 40);
  /* ── Fan tab ── */
  tab_fan = lv_tabview_add_tab(tabview, "Fan");
  lv_obj_clear_flag(tab_fan, LV_OBJ_FLAG_SCROLLABLE);

  slider_fan = lv_slider_create(tab_fan);
  lv_obj_set_size(slider_fan, 200, 30);
  lv_obj_align(slider_fan, LV_ALIGN_CENTER, 0, -30);
  lv_obj_set_ext_click_area(slider_fan, 20);
  lv_obj_add_event_cb(slider_fan, fan_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

  lbl_fan_pct = lv_label_create(tab_fan);
  lv_label_set_text(lbl_fan_pct, "0%");
  lv_obj_align_to(lbl_fan_pct, slider_fan, LV_ALIGN_OUT_BOTTOM_MID, 0, 6);
  sw_fan = lv_switch_create(tab_fan);
  lv_obj_align(sw_fan, LV_ALIGN_CENTER, 0, 40);
  lv_obj_add_event_cb(sw_fan, fan_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  /* ── LED tab ── */
  tab_led = lv_tabview_add_tab(tabview, "LED");
  lv_obj_clear_flag(tab_led, LV_OBJ_FLAG_SCROLLABLE);

  slider_led = lv_slider_create(tab_led);
  lv_obj_set_size(slider_led, 200, 30);
  lv_obj_align(slider_led, LV_ALIGN_CENTER, 0, -30);
  lv_obj_set_ext_click_area(slider_led, 20);
  lv_obj_add_event_cb(slider_led, led_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

  lbl_led_pct = lv_label_create(tab_led);
  lv_label_set_text(lbl_led_pct, "0%");
  lv_obj_align_to(lbl_led_pct, slider_led, LV_ALIGN_OUT_BOTTOM_MID, 0, 6);
  sw_led = lv_switch_create(tab_led);
  lv_obj_align(sw_led, LV_ALIGN_CENTER, 0, 40);
  lv_obj_add_event_cb(sw_led, led_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  /* ── Info tab ── */
  tab_info = lv_tabview_add_tab(tabview, "Info");
  lv_obj_clear_flag(tab_info, LV_OBJ_FLAG_SCROLLABLE);

  lbl_rpm = lv_label_create(tab_info);
  lv_label_set_text(lbl_rpm, "RPM: ---");
  lv_obj_center(lbl_rpm);
}

/* ── Screensaver screen ── */
void create_screensaver(void) {
  scr_saver = lv_obj_create(NULL);   /* NULL parent = standalone screen */
  lv_obj_set_style_bg_color(scr_saver, lv_color_black(), 0);
  lv_obj_set_style_bg_opa(scr_saver, LV_OPA_COVER, 0);

  /* "Wind" label — upper half */
  lv_obj_t *lbl_wind = lv_label_create(scr_saver);
  lv_label_set_text(lbl_wind, "Wind");
  lv_obj_set_style_text_font(lbl_wind, SAVER_FONT, 0);
  lv_obj_set_style_text_color(lbl_wind, lv_color_white(), 0);
  lv_obj_set_style_text_letter_space(lbl_wind, 6, 0);
  lv_obj_align(lbl_wind, LV_ALIGN_CENTER, 0, -38);

  /* "Maker" label — lower half */
  lv_obj_t *lbl_maker = lv_label_create(scr_saver);
  lv_label_set_text(lbl_maker, "Maker");
  lv_obj_set_style_text_font(lbl_maker, SAVER_FONT, 0);
  lv_obj_set_style_text_color(lbl_maker, lv_color_white(), 0);
  lv_obj_set_style_text_letter_space(lbl_maker, 6, 0);
  lv_obj_align(lbl_maker, LV_ALIGN_CENTER, 0, 38);
}

/* ── RPM update — called every RPM_INTERVAL ms ── */
void update_rpm() {
  uint32_t now = millis();
  if (now - lastRpmMs < RPM_INTERVAL) return;
  lastRpmMs = now;

  portDISABLE_INTERRUPTS();
  uint32_t pulses = tachPulses;
  tachPulses = 0;
  portENABLE_INTERRUPTS();
  /* Most 4-wire fans: 2 pulses per revolution */
  uint32_t rpm = (pulses * 60000UL) / (2UL * RPM_INTERVAL);
  char buf[16];
  snprintf(buf, sizeof(buf), "RPM: %lu", rpm);
  lv_label_set_text(lbl_rpm, buf);
  Serial.printf("[TACH] %lu RPM (%lu pulses)\n", rpm, pulses);
}

/* ── setup ── */
void setup() {
  Serial.begin(115200);
  Serial.println("[BOOT] CYD fan controller starting");

  /* Updated Fan PWM — 25 kHz */
  ledcAttach(PIN_FAN_PWM, LEDC_FAN_FREQ, LEDC_RES);
  ledcWrite(PIN_FAN_PWM, 0);
  Serial.println("[BOOT] Fan PWM ready on GPIO22");

  /* Updated LED PWM — 1 kHz */
  ledcAttach(PIN_LED_PWM, LEDC_LED_FREQ, LEDC_RES);
  ledcWrite(PIN_LED_PWM, 0);
  Serial.println("[BOOT] LED PWM ready on GPIO27");

  /* Tach interrupt */
  pinMode(PIN_FAN_TACH, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_FAN_TACH), tach_isr, FALLING);
  Serial.println("[BOOT] Tach interrupt ready on GPIO35");

  /* LVGL + display */
  lv_init();
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  touchscreen.setRotation(0);
  lv_display_t *disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_270);
  lv_indev_t *indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, touchscreen_read);
  lv_create_main_gui();
  scr_main_ref = lv_screen_active();   /* save main screen for screensaver dismiss */
  create_screensaver();
  lastRpmMs  = millis();
  lastTouchMs = millis();   /* start inactivity timer from boot */
  Serial.println("[BOOT] Ready");
}

/* ── loop ── */
void loop() {
  lv_tick_inc(5);
  lv_task_handler();

  uint32_t now = millis();

  if (saver_active) {
    /* Dismiss on touch — touchscreen_read sets lastTouchMs */
    if (lastTouchMs > 0 && now - lastTouchMs < 200) {
      saver_active = false;
      lastTouchMs  = now;   /* prevent immediate re-trigger */
      lv_screen_load(scr_main_ref);
    }
  } else {
    /* Activate after timeout with no touch */
    if (now - lastTouchMs > SAVER_TIMEOUT_MS) {
      saver_active = true;
      lv_screen_load(scr_saver);
    }
  }

  update_rpm();
  delay(5);
}
