---
layout: single
title: "Three Ghosts: What Are RGB Channels Actually?"
date: 2026-09-15
categories:
  - Photography
  - Engineering
tags:
  - photography
  - color theory
  - trichromatic
excerpt: "Turning three separate photos into a lesson on how color photography works."
header:
  teaser: "/assets/images/posts/rgb-ghosts/teaser.jpg"
  overlay_image: "/assets/images/posts/rgb-ghosts/banner.jpg"
  overlay_filter: 0.4
toc: false
toc_sticky: false
---
# Three Ghosts: What Are RGB Channels Actually?

I was watching a video on colorful photography a couple days back, and it explained how early colored photography worked: it showed a graphic of a person taking multiple pictures with a colored filter on B/W film and then recombining them into a colored picture with post processing. It got me so curious. Why not do it in reverse, to pay homage to this ancient method?

<div style="position:relative;width:100%;padding-bottom:56.25%;height:0;overflow:hidden;border-radius:8px;margin-bottom:1em;">
  <iframe src="https://www.youtube.com/embed/TpY2XGA9KkU?si=CuIdDlS7Ha8RBPxx" title="YouTube video player" style="position:absolute;top:0;left:0;width:100%;height:100%;border:0;" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
</div>
(the video I was watching.)

So, I took three separate pictures with the camera stable and a moving subject, converted the pics into red, green, and blue, and then stitched the pics back together into a final completed image.The result was this amazing ghosting effect.

<img src="/assets/images/posts/rgb-ghosts/ghostlyboat.jpg" alt="Long-exposure-style ghost photo of a moving toy boat, with red, green, and blue channel separation visible at the edges" style="display:block;width:100%;height:auto;border-radius:8px;margin:1em 0;" />

This got me thinking a little more devious.

## The Visualization

My next picture had to one-up that, and I also wanted to show off how the effect works; so I created the visualization tool below. In my instance, I added the single channel color information together to create a really cool result. Toggle the red, green, and blue channels on and off to see how they combine, two channels together give you a secondary color, and how all three give you the full image back.

<div style="display:flex;gap:16px;margin-bottom:12px;flex-wrap:wrap;align-items:center;">
  <label style="display:flex;align-items:center;gap:6px;cursor:pointer;">
    <input type="checkbox" id="chk-red" checked /> Red
  </label>
  <label style="display:flex;align-items:center;gap:6px;cursor:pointer;">
    <input type="checkbox" id="chk-green" /> Green
  </label>
  <label style="display:flex;align-items:center;gap:6px;cursor:pointer;">
    <input type="checkbox" id="chk-blue" /> Blue
  </label>
</div>
<div style="position:relative;width:100%;max-width:100%;border-radius:8px;overflow:hidden;">
  <img id="ghost-img" src="/assets/images/posts/rgb-ghosts/red.jpg" alt="RGB channel combination preview" style="display:block;width:100%;height:auto;transition:opacity 0.15s;" />
</div>
<p style="font-size:0.9em;color:#666;margin-top:8px;" id="ghost-caption">Red channel only.</p>
<script>
(function() {
  var basePath = "/assets/images/posts/rgb-ghosts/";
  // Every combination of R/G/B maps to one image. "000" (nothing checked)
  // falls back to black.jpg instead of leaving a blank box.
  var combos = {
    "000": { file: "black.jpg", label: "Nothing selected: black." },
    "100": { file: "red.jpg", label: "Red channel only." },
    "010": { file: "green.jpg", label: "Green channel only." },
    "001": { file: "blue.jpg", label: "Blue channel only." },
    "110": { file: "yellow.jpg", label: "Red + green: yellow." },
    "101": { file: "magenta.jpg", label: "Red + blue: magenta." },
    "011": { file: "cyan.jpg", label: "Green + blue: cyan." },
    "111": { file: "white.jpg", label: "All three channels: the full-color image." }
  };

  var chkRed = document.getElementById("chk-red");
  var chkGreen = document.getElementById("chk-green");
  var chkBlue = document.getElementById("chk-blue");
  var img = document.getElementById("ghost-img");
  var caption = document.getElementById("ghost-caption");

  function update() {
    var key = (chkRed.checked ? "1" : "0") +
              (chkGreen.checked ? "1" : "0") +
              (chkBlue.checked ? "1" : "0");
    var entry = combos[key];
    img.style.opacity = 0;
    setTimeout(function() {
      img.src = basePath + entry.file;
      img.style.opacity = 1;
    }, 100);
    caption.textContent = entry.label;
  }

  [chkRed, chkGreen, chkBlue].forEach(function(chk) {
    chk.addEventListener("change", update);
  });

  update();
})();
</script>

This also produces some interesting side effects like chromatic aberrations on edges and weirdly colored shadows. What is a shadow if not the absence of light? In this unique instance that's the absence of color information from a single channel (you subtract the color channel of the thing that has a shadow from the blended color of the background).

## Some Interesting Background

<img src="/assets/images/posts/rgb-ghosts/SergeiPhotography.jpg" alt="Portrait of Sergei Prokudin-Gorskii" style="display:block;width:100%;height:auto;border-radius:8px;margin:1em 0;" />

This technique has a real creator as well: it was invented by Sergei Prokudin-Gorskii, a Russian photographer that worked in the 20th century. He shot three black and white images with red, green and blue filters respectively, and then he projected all of them together to create a full-color image before the invention of colored film. He also happened to experiment with subjects that changed their positions, which interestingly enough led to the same effect I came up with while playing around in Affinity Suite.

<img src="/assets/images/posts/rgb-ghosts/Bayer_pattern_on_sensor.svg" alt="Diagram of a Bayer filter pattern on a camera sensor" style="display:block;width:100%;max-width:500px;height:auto;margin:1em auto;" />

This is also very similar to how modern camera sensors work. Basically every digital sensor uses a Bayer filter array: a grid of sensors, referred to as photosites, each measuring a specific color of light. The camera's software then stitches the information together to make a full color image by using interpolation, a technique called demosaicing in this example. I've also discovered an absolutely wild video of a guy scraping off the Bayer filter of his camera, and it's genuinely so difficult to watch.

<div style="position:relative;width:100%;padding-bottom:56.25%;height:0;overflow:hidden;border-radius:8px;margin-bottom:1em;">
  <iframe src="https://www.youtube.com/embed/rUui5PZuKnU?si=spImMEV8PTUV-aQ9&amp;start=562" title="YouTube video player" style="position:absolute;top:0;left:0;width:100%;height:100%;border:0;" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
</div>

## Another Fun Application

<div style="position:relative;width:100%;padding-bottom:56.25%;height:0;overflow:hidden;border-radius:8px;margin-bottom:1em;">
  <iframe src="https://www.youtube.com/embed/p0cAmwtsSmU?si=oV6A8BvupfVFWHez" title="YouTube video player" style="position:absolute;top:0;left:0;width:100%;height:100%;border:0;" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
</div>

I shot a video trying to do the same effect in DaVinci Resolve, and I realized that my phone camera automatically adjusts the brightness each time I start the video; so, in this example I had to film myself out of frame and then quickly jump into frame and dance. I made the background cyan and the layer where I'm dancing red to make the process a little easier for me since I'm not that knowledgeable in video editing.

In conclusion, I had a real blast exploring color, and I'm confident that I have a better understanding of digital color than I started with. I found this deep dive very enlightening.
