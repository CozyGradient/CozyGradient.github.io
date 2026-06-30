---
layout: single
title: "Modular Wind Tunnel Design"
excerpt: "Designing an open-source modular testing environment for aerodynamic flow scenarios using custom 3D-printed parts."
date: 2026-06-30
permalink: /projects/modular-wind-tunnel/  # Fixes the ugly /index/ URL
toc: true
toc_sticky: true
mathjax: true                              # Activates LaTeX for your fluid dynamics equations
header:
  teaser: "/_projects/Modular_Wind_Tunnel_Design/images/1080x600_Teaser.png"
  overlay_image: "/_projects/Modular_Wind_Tunnel_Design/images/1080x500_Banner.png"  # Creates the top banner
gallery:
  - url: /_projects/Modular_Wind_Tunnel_Design/images/1200x900_Wind_Tunnel_Overview.png
    image_path: /_projects/Modular_Wind_Tunnel_Design/images/1200x900_Wind_Tunnel_Overview.png
    alt: "Wind tunnel overview"
  - url: /_projects/Modular_Wind_Tunnel_Design/images/1200x900_WebUI.png
    image_path: /_projects/Modular_Wind_Tunnel_Design/images/1200x900_WebUI.png
    alt: "Web UI control interface"
    # {% include gallery caption="Initial design and interface overview." %}
--- 

## Prologue

<iframe width="560" height="315" src="https://www.youtube.com/embed/kYgQ7hUqkZo?si=ltBCUeqKCMHEl6qI" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
*Figure P.a: Wind Tunnel Project Demonstration YouTube Video*

> ***Document Purpose:** This file serves as the authoritative technical master record, system documentation, and handover repository for this open-loop wind tunnel. It is designed to preserve institutional knowledge, guide future student iterations, and provide open-source access to all engineering design files.*

## 0. Executive Summary & Project Scope

### 0.1 Abstract
This project details the design, manufacturing, and evaluation of an open-loop, small-scale, subsonic, open-source wind tunnel optimized for educational environments. Developed to address the absence of aerodynamic testing equipment at my university, the system was engineered from scratch within strict budgetary constraints. The final apparatus features a clear test section fabricated from four acrylic panels chemically welded with chloroform. It is driven by a pull-configuration array of 4x 140mm desktop fans that draw air through the inlet and custom flow straighteners. A modular smoke rake injects tracer streams into the column, generating clean streamlines that visualize fluid behavior and flow separation over test profiles.

### 0.2 Project Governance & Ownership

While this project was an academic collaboration, the technical execution was heavily divided. My explicit responsibilities and core ownership areas included:
- **Lead Mechanical Designer:** Established the fan-first geometric constraints, CAD assembly, and modular routing.
- **Fluid Dynamics & Simulation Engineer:** Set up, ran, and interpreted the critical CFD validation passes.
- **Systems Integrator & Primary Fabricator:** Executed the electronics assembly and custom touchscreen firmware layout.

### 0.3 Project Scope

To ensure project delivery and keep the development focused, strict engineering boundaries were established for Version 1 of the tunnel:

**In Scope:**
- **Aerodynamic chassis manufacturing:** Designing and assembling the physical tunnel segments to establish a sealed, clear test section for fluid flow.
- **Flow-straightening optimization:** Developing and refining the intake straightener geometry to smooth out incoming air and create stable fluid streams.
- **Modular smoke rake iteration:** Designing, testing, and rebuilding the smoke distribution rakes and the custom top-mounting plugs around a portable smoke machine.
- **Physical touchscreen UI:** Building a standalone control deck that utilizes PWM to regulate fan speeds and adjust internal LED brightness through interactive sliders.

**Out of Scope:**
- **High-accuracy quantitative fluid metrology:** Extracting precise numerical measurement data from the test section, since fluid simulations confirmed the open-loop setup is optimized strictly for visual tracking.
- **Closed-loop automated sensor data logging:** Writing the firmware routines required to pull live data from sensor nodes and print active telemetry directly onto the display screen.
- **Custom manufactured PCB generation:** Consolidating the loose breadboard wiring and independent voltage regulators into a unified Gerber circuit board design, which is officially delegated to the V2 roadmap.

## 1. Genesis, Academic Research, & Simulation
### 1.1 The Educational Equipment Vacuum

For most mechanical engineering students, exposure to high-quality visuals of fluid mechanics phenomena is typically limited to Yusuf Çengel's _Fluid Mechanics_ textbook, lecture slides, or online videos. This was exactly the case at Başkent University. While the university possessed a small wind tunnel, it was completely non-functional. This lack of operational equipment was highly unfortunate, because developing my own wind tunnel later revealed a vast world of fluid flow interactions that are completely invisible to the naked eye, yet incredibly valuable for physical observation and deep engineering understanding.
### 1.2 Insights from the Field: The Lab Tour

![](/_projects/Modular_Wind_Tunnel_Design/images/1200x900_THK_University.png)
*Figure 1.2.1: THK University Visit*

Under the guidance of our project advisor, Asst. Prof. Dr. Erhan Solakoğlu, we visited the wind tunnel and fluids laboratory of Asst. Prof. Dr. Ali Ruhşen Çete. During this visit, we observed several intriguing wind tunnel configurations. One particular 2D wind tunnel design stood out, featuring clear acrylic panels bolted directly to aluminum extrusions. Its airflow was driven by standard desktop PC fans arranged in a 1x4 rectangular array. This specific configuration, with a few minor modifications, became our chosen baseline design moving forward.

![](/_projects/Modular_Wind_Tunnel_Design/images/1200x900_THK_WindTunnelDesign.png)
*Figure 1.2.2: THK University Wind Tunnel Design Inspirational Components*
### 1.3 Academic Literature Benchmarks & Design Trade-Offs

![](/_projects/Modular_Wind_Tunnel_Design/images/1200x900_Main_Sources.png)
*Figure 1.3.1: Main Sources that have been reviewed, (a) Eckert, Mort, & Jope, 1976, (b) Barlow, Rae, & Pope, 3rd ed.*

When diving into established aerodynamic literature to evaluate how small-scale or open-source wind tunnels are traditionally designed, several geometric parameters emerge:

- **The Contraction Ratio Constraint:** The literature explicitly recommends an incredibly large contraction ratio (often up to 24:1 for high-performance low-speed testing) to drastically smooth out incoming airflow and minimize spatial velocity variations *(Barlow, Rae, & Pope, 3rd ed., p. 35, sec. 2.5).*
- **The Desktop Reality & Space-Saving Pivot:** Incorporating a 24:1 contraction cone into a compact desktop footprint is entirely impractical, as the required intake nozzle would demand a massive physical volume. To maintain our core project constraint of portability and a small workspace footprint, we deliberately bypassed the contraction section entirely, opting for a 1:1 straight-duct architecture.
- **The Honeycomb Compensation:** Because a 1:1 duct inherently loses the automatic flow-straightening and air-acceleration benefits of a narrowing funnel, the burden of eliminating swirl falls entirely on the intake grid. To compensate for the lack of contraction, we relied heavily on a 3D-printed honeycomb style straightener. According to subsonic design guidelines, maintaining a cell length-to-diameter ratio between 5 and 10 allows the honeycomb to strip out lateral turbulence and align the air paths effectively without choking the low-power consumer fan array *(Eckert, Mort, & Jope, 1976).*
### 1.5 The CFD Reality Pass & The Simulation Pivot

#### 1.5.1 Computational Framework and Setup

![](/_projects/Modular_Wind_Tunnel_Design/images/1200x900_CFD_Preparation.png)
*Figure 1.5.1.a: CFD Boundary Conditions, Mesh, Control Volume*

To validate the aerodynamic behavior within the straight-duct configuration, a steady-state Computational Fluid Dynamics (CFD) simulation was conducted. The computational domain utilized a Reynolds-Averaged Navier-Stokes (RANS) $k-\omega$ SST turbulence model. This specific model choice was justified because the operational velocity of 1 m/s yields a turbulent Reynolds number of approximately 18,500.

To account for the 3D-printed honeycomb flow straightener at the intake without modeling every individual cell, the inlet section was defined as a porous media zone. This zone applied the Darcy-Forchheimer law with a porosity value ($\gamma$) of 0.95. The ambient environment of the still testing room at 20 degrees Celsius was initialized with a baseline turbulence intensity of 1.5% derived from fluid dynamics literature.

#### 1.5.2 Simulation Takeaways and Scope Validation

![](/_projects/Modular_Wind_Tunnel_Design/images/1200x900_CFD_Result.gif)
*Figure 1.5.2.a: High Turbulence Regions visualized through Nu_T (GIF)*

The numerical analysis provided clear data regarding the boundary layer development and the internal turbulence behavior, which directly guided the final scope of the project:

- **Boundary Layer Behavior:** The simulation indicated that the boundary layer thickness reaches a maximum length of 20.9 mm near the exit. Because this layer remains thin relative to the overall cross-section, it does not disrupt or choke the core flow in the center of the tunnel. The central testing volume remains completely clear of wall-bounded fluid disturbances.
- **Turbulence Management:** The results showed that passing the air through the properly managed honeycomb straightener allows the internal chamber to maintain a turbulence intensity close to the ambient room baseline of 1.5%.

These insights defined the simulation pivot. A turbulence intensity around 1.5% is too high for high-precision quantitative aerodynamic testing or numerical sensor logging. However, it is entirely stable and effective for flow visualization and qualitative wake studies.

Rather than chasing complex, space-consuming geometric additions to force the turbulence intensity below 1%, these results validated the choice to maintain a compact 1:1 straight layout. The simulation proved that the 3D-printed honeycomb straightener alone is sufficient to deliver the stable, parallel flow required to capture clean smoke trails.
### 1.5 Project Milestone Timeline

<style>
  .custom-timeline {
    max-width: 800px;
    margin: 40px auto;
    counter-reset: timeline-counter;
  }
  .timeline-node {
    display: flex;
    gap: 20px;
    counter-increment: timeline-counter;
  }
  .timeline-marker {
    display: flex;
    flex-direction: column;
    align-items: center;
    flex-shrink: 0;
  }
  .timeline-dot {
    width: 26px;
    height: 26px;
    border-radius: 50%;
    background: #007acc;
    border: 2px solid currentColor;
    box-shadow: 0 0 0 4px rgba(0, 122, 204, 0.15);
    display: flex;
    align-items: center;
    justify-content: center;
    font-size: 0.75em;
    font-weight: bold;
    color: #ffffff;
    flex-shrink: 0;
  }
  .timeline-dot::before {
    content: counter(timeline-counter);
  }
  .timeline-line {
    flex: 1;
    width: 2px;
    background: currentColor;
    opacity: 0.25;
    margin-top: 4px;
  }
  .timeline-node:last-child .timeline-line {
    display: none;
  }
  .timeline-card {
    flex: 1;
    padding: 15px 20px;
    background: rgba(128, 128, 128, 0.05);
    border: 1px solid rgba(128, 128, 128, 0.15);
    border-radius: 6px;
    margin-bottom: 35px;
    transition: transform 0.2s ease, border-color 0.2s ease;
  }
  .timeline-node:last-child .timeline-card {
    margin-bottom: 0;
  }
  .timeline-card:hover {
    border-color: #007acc;
    transform: translateX(4px);
  }
  .timeline-card h3 {
    margin: 0 0 6px;
  }
  .timeline-card p {
    margin: 0;
  }
</style>
<div class="custom-timeline">
  <div class="timeline-node">
    <div class="timeline-marker">
      <div class="timeline-dot"></div>
      <div class="timeline-line"></div>
    </div>
    <div class="timeline-card">
      <h3>Genesis & Research</h3>
      <p>Literature review, university aerodynamics lab tour, and initial number crunching.</p>
    </div>
  </div>
  <div class="timeline-node">
    <div class="timeline-marker">
      <div class="timeline-dot"></div>
      <div class="timeline-line"></div>
    </div>
    <div class="timeline-card">
      <h3>Scale Prototyping</h3>
      <p>Construction of a miniature 1x 40mm fan proof-of-concept using burning incense.</p>
    </div>
  </div>
  <div class="timeline-node">
    <div class="timeline-marker">
      <div class="timeline-dot"></div>
      <div class="timeline-line"></div>
    </div>
    <div class="timeline-card">
      <h3>Structural Fabrication</h3>
      <p>Sourcing and chemically welding full-scale acrylic body panels using chloroform.</p>
    </div>
  </div>
  <div class="timeline-node">
    <div class="timeline-marker">
      <div class="timeline-dot"></div>
      <div class="timeline-line"></div>
    </div>
    <div class="timeline-card">
      <h3>The CFD Reality Check</h3>
      <p>Running fluid simulations and formally executing the pivot from quantitative measurement to qualitative flow visualization.</p>
    </div>
  </div>
  <div class="timeline-node">
    <div class="timeline-marker">
      <div class="timeline-dot"></div>
      <div class="timeline-line"></div>
    </div>
    <div class="timeline-card">
      <h3>Aerodynamic Component Iteration</h3>
      <p>Tweaking the PLA infill straighteners, designing top-mounted plugs, and refining smoke rake geometries.</p>
    </div>
  </div>
  <div class="timeline-node">
    <div class="timeline-marker">
      <div class="timeline-dot"></div>
      <div class="timeline-line"></div>
    </div>
    <div class="timeline-card">
      <h3>Control Electronics Evolution</h3>
      <p>Transitioning from direct 12V LED PSU power to an ESP32 microcontroller running local web server PWM controls.</p>
    </div>
  </div>
  <div class="timeline-node">
    <div class="timeline-marker">
      <div class="timeline-dot"></div>
      <div class="timeline-line"></div>
    </div>
    <div class="timeline-card">
      <h3>UX & Visualization Tuning</h3>
      <p>Creating a custom LED strip, adding a high-contrast black backdrop, and overhauling the controls to a standalone touchscreen interface.</p>
    </div>
  </div>
  <div class="timeline-node">
    <div class="timeline-marker">
      <div class="timeline-dot"></div>
      <div class="timeline-line"></div>
    </div>
    <div class="timeline-card">
      <h3>Repository Sunsetting</h3>
      <p>Compiling STEP models, circuit diagrams, and source code into this open-source package.</p>
    </div>
  </div>
</div>

## **2. Geometric Constraints & Scale Modeling**

### 2.1 Fan-First Architectural Design

The initial architecture of the wind tunnel was dictated by the square cross section of the selected fans. However, unlike the 1x4 linear fan array observed at the THK lab, we opted for a 2x2 configuration to introduce a true 3D test section. This aspect ratio allowed for the simultaneous observation of fluid phenomena from both the top and side profiles. Furthermore, this symmetrical geometry established a critical constraint that standardized the design of all downstream modular components, such as the honeycomb air straightener.
### 2.2 The Micro-Scale Proof of Concept

![](/_projects/Modular_Wind_Tunnel_Design/images/1200x900_MicroScale_Prototype.png)
*Figure 2.2.a: Microscale Prototype with Test Geometries and 40mm Fan*

To validate the core system architecture prior to full-scale fabrication, a compact prototype was produced using 3D printing. This  model scaled the cross-sectional testing domain down from the final 280 mm × 280 mm dimensions to a localized 40 mm × 40 mm framework. The deployment of this small-scale iteration served two primary objectives:

- **Control Scheme Development:** It provided a low-risk hardware sandbox to implement, troubleshoot, and refine the fan motor control loops and logic.
- **Flow Visualization Mechanics:** It allowed for the empirical evaluation of various smoke generation methods and a clear physical assessment of how the medium interacts with the intake flow straightener.

Because of the drastically reduced geometric scale and the physical limitations of the 40 mm exhaust fan, the prototype naturally operated at a highly restricted flow velocity. This combination of a small characteristic length and low-speed flow established an ultra-low Reynolds number regime. Consequently, the fluid dynamics within the test section remained strictly laminar, yielding exceptionally fine, stable streamlines that provided an ideal qualitative benchmark for the project.

## 3. Materials & Fabrication Hacks

### 3.1 Solvent Acrylic Welding via Chloroform

#### 3.1.1 Preparation and Laser Cutting

Fabrication of the primary tunnel housing was completed in collaboration with a technical workshop using acrylic sheets. Prior to the assembly and welding phases, a 20 mm diameter hole was machined into the top panel of the tunnel via precision laser cutting. Preparing this feature before joining the sheets was much easier to do beforehand than it would have been afterwards.

#### 3.1.2 Fixturing and Solvent Application

The individual panels were arranged to form a precise 280 mm × 280 mm square cross-section. To maintain geometric alignment and rigidity during the bonding process, the panels were mechanically secured using heavy-duty tape and tension ties.

The structural seams were joined using chloroform as a solvent-welding agent, applied directly to the intersecting joints via a precision syringe. Immediately following the injection, the entire tunnel assembly was inclined. This tilt utilized gravity to pull the low-viscosity solvent deeper into the joint junctions through capillary action, ensuring complete surface wetting and eliminating internal micro-voids.

#### 3.1.3 Curing and Structural Integrity

![](/_projects/Modular_Wind_Tunnel_Design/images/1200x900_Solvent_Welded_Seam.png)
*Figure 3.1.3.a: Cured Solvent Welded Seam*

Once the solvent was successfully distributed along the seams, the fixtured assembly remained at the workshop overnight. This uninterrupted layout allowed for complete solvent evaporation and bonding across the joint interfaces. This curing period yielded a highly rigid, transparent, and sealed weld capable of maintaining the internal flow pressures.

### 3.2 Integrated 3D-Printed Infill as a Flow Straightener

#### 3.2.1 Manufacturing Choice

![](/_projects/Modular_Wind_Tunnel_Design/images/1200x900_Honeycomb_Straightener.png)
*Figure 3.2.1.a: Honeycomb Pattern Straightener*

To meet tight project deadlines, the slicing software's native infill was used as a direct substitute for a separately modeled honeycomb component. This approach eliminated the design overhead of modeling thousands of individual cells manually.

#### 3.2.2 Aerodynamic Performance

The component was printed at a fine layer resolution to minimize surface roughness. This choice provided two critical aerodynamic benefits:

- **Reduced Friction:** Smoother internal cell walls promoted stable boundary layer attachment and minimized skin friction.
- **Turbulence Suppression:** Eliminating physical defects within the lattice prevented disorganized air movements, keeping the internal turbulence intensity low enough to protect the downstream visualization field.


## 4. Modular Subsystems & Visual Optimization

![](/_projects/Modular_Wind_Tunnel_Design/images/1200x900_Wind_Tunnel_Overview.png)
*Figure 4.a: Wind Tunnel Design Overview*

### 4.1 The Lensgo Smoke Injection System

#### 4.1.1 Integration Mechanics

A commercial Lensgo photography fog machine serves as the primary visualization source. The machine connects to the tunnel using its native rubber tubing. To route this tubing into the 20 mm laser-cut aperture at the top of the tunnel, a custom adapter plug was designed and 3D printed. This custom plug securely bridges the external rubber tube to the internal smoke rake.

#### 4.1.2 Composition and Operational Constraints

The system generates dense smoke trails by vaporizing a liquid fluid mixture consisting of glycerin and propylene glycol. Because the machine is a compact handheld device, it features a distinct thermal duty cycle limit. The unit can produce smoke continuously for approximately 10 minutes before its internal temperature threshold requires a cooldown period.
### 4.2 Smoke Rake Iterations and Pressure Screen Optimization

#### 4.2.1 Smoke Rake Design Evolution

![](/_projects/Modular_Wind_Tunnel_Design/images/1200x900_Smoke_Rake_Design_Iteration.png)
*Figure 4.2.1.a: Smoke Rake Design Iterations*

The smoke injection rake underwent an iterative design process to correct internal pressure imbalances and minimize aerodynamic interference within the test section:

- **Initial Design Imperfections:** The first prototype utilized a single inlet feeding a simple tube with five linear outlets. This configuration created an uneven internal pressure gradient. The first outlet discharged a high-velocity, disorganized jet of smoke, while subsequent outlets suffered from a major pressure drop, leaving only the final outlet to produce a fine, laminar streamline.
- **Plenum and Aerodynamic Integration:** To equalize pressure across all five exit points, a distribution plenum was integrated into the design. To minimize wake disruption upstream of the test area, the outer geometry of the rake was modeled as a aerodynamic NACA-0018 airfoil profile.
- **Structural Stabilization:** The first aerodynamic prototype suffered from physical imbalance and sagging because the entry tube was placed too close to the leading edge of the airfoil. To correct this, the mounting aperture was relocated to align with the component's center of mass from above. The vertical length of the rake was also extended so its base rested flush against the floor of the wind tunnel, replacing the unstable cantilevered mount.
- **Alternative Cross-Sections:** Additional cylindrical rakes were fabricated to serve as alternative testing assets. These allowed for the qualitative visualization of potential flow characteristics and stagnation points over a standard circular cross-section.
#### 4.2.2 Pressure Screen Implementation and Relocation

![](/_projects/Modular_Wind_Tunnel_Design/images/1200x900_Pressure_Screen.png)
*Figure 4.2.2.a: 3D Printed Pressure Screen (note: finer mesh compared to honeycomb straighteners)*

A fine-mesh pressure screen was introduced to manage tunnel velocity and optimize flow alignment:

- **Velocity Suppression:** The baseline speed of the exhaust fan array at its lowest operational threshold (5% PWM duty cycle) was too high to maintain completely stable laminar streamlines. The pressure screen was introduced to create a targeted static pressure drop, effectively slowing the core flow down to an ideal velocity for flow visualization.
- **Optimal Placement:** The screen was originally positioned immediately upstream of the exhaust fan array. However, empirical testing showed that relocating the screen to the tunnel entrance, directly ahead of the 3D-printed flow straighteners, provided superior flow conditioning. The small cell diameter of the mesh acted as an effective primary stage for removing large-scale fluid disturbances before the air entered the honeycomb lattice.
### 4.3 Improved Presentation

![](/_projects/Modular_Wind_Tunnel_Design/images/1200x900_Improved_Visuals.png)
*Figure 4.3.a: Improved Presentation due to Black Backdrop and LED Lighting*
#### 4.3.1 Contrast Enhancement

To address feedback regarding the low visibility of the internal smoke volume, a high-contrast background was integrated into the test section. A matte black backing was installed along the rear panel of the channel, providing a dark baseline that isolates the light-colored aerosol streamlines.

#### 4.3.2 Illumination and Glare Mitigation

A high-intensity LED strip was mounted within the tunnel housing to provide targeted illumination across the active fluid domain. This configuration yielded two critical practical advantages:

- **Streamline Definition:** The directional light paths maximize scattering across the smoke particles, significantly enhancing the visibility of fine flow structures.
- **Optical Clarity for Documentation:** The specialized lighting angle eliminates internal secondary reflections and surface glare along the transparent acrylic walls, facilitating better photographic and video capture of the qualitative wake behavior.


## 5. Electronics, UI, & UX Evolution

### 5.1 Direct Power to ESP32 Web Server

#### 5.1.1 Phase 1: Baseline Hardware Validation

Initial hardware testing bypassed the control electronics by wiring the exhaust fans directly to a dedicated 12V power supply unit (PSU). Running the fans at maximum duty cycle validated the basic electrical assembly, verified that the system could achieve adequate suction, and ensured the integrity of the mounting layout.

However, this unthrottled operational baseline proved unviable for testing. The maximum flow velocity generated excessive turbulence inside the channel, which rapidly disrupted and tore apart the injected smoke streamlines.

#### 5.1.2 Phase 2: ESP32 Microcontroller Integration and Web UI

![](/_projects/Modular_Wind_Tunnel_Design/images/1200x900_Initial_Circuit_Diagram.png)
*Figure 5.1.2.a: Initial Circuit Diagram*

To lower the flow velocity to an acceptable level for qualitative flow visualization, an ESP32 microcontroller was integrated into the system architecture. This setup allowed for the following software and control implementations:

- **Pulse-Width Modulation (PWM) Control:** The ESP32 was programmed to generate a low-duty-cycle PWM signal, throttling the fan motor speeds to suppress internal turbulence and stabilize the fluid stream.
- **Asynchronous Web Interface:** The microcontroller hosted a localized web server, serving a basic, functional user interface accessible via any browser on the local network.
- **Control Inputs:** The interface consisted of a simple slider to dynamically adjust the fan speed percentage and a toggle button to initialize or cut power to the array.

This digital control loop provided the stable, low-speed environment necessary to conduct the subsequent developmental iterations on the NACA-0018 smoke rakes and the 3D-printed flow straighteners.

![](/_projects/Modular_Wind_Tunnel_Design/images/1200x900_WebUI.png)
*Figure 5.1.2.b: Asynchronous Web Interface*

### 5.2 Phase 3: The Standalone Touchscreen Interface

![](/_projects/Modular_Wind_Tunnel_Design/images/1200x900_Sketch_to_Real_Life.png)
*Figure 5.2.a: (a) Initial Sketches of the Touch Screen Interface, (b) Final Design*

#### 5.2.1 UI Redesign Rationalization

Following a design review, a faculty professor noted that requiring users to connect a secondary device to an IP address served by the microcontroller was an inefficient and bulky workflow for a localized laboratory instrument. While the professor suggested a simpler potentiometer to manually adjust the fan speeds, a more comprehensive digital solution was pursued to preserve the system's modularity and expandability. The interface hardware was upgraded to a Cheap Yellow Display (CYD) ESP32-2432S028 touchscreen module, consolidating the control inputs into a standalone physical dashboard mounted on the PSU case.

#### 5.2.2 Touchscreen UI and Sensor Integration

The software architecture was rebuilt to take advantage of the color touchscreen interface, enabling direct, local interaction with the wind tunnel's electronic components:

- **Integrated Component Control:** The new user interface layout featured dedicated digital sliders and toggles to dynamically regulate the fan speed duty cycles and manage power to the high-intensity internal LED strip.
- **Telemetry Data Logging:** The control loop was designed to utilize the fourth pin (tachometer signal) of the exhaust fan array. This allowed the ESP32 to capture real-time RPM feedback from the motors, displaying active hardware telemetry alongside the control sliders.
### 5.3 Disclosures on Current Work-in-Progress

![](/_projects/Modular_Wind_Tunnel_Design/images/1200x900_New_Case_TopView.png)
*Figure 5.3.a: Top View of New Case (note: LED pins not yet connected to the CYD due to issues with code)*

#### 5.3.1 Technical Limitations and Current System State

While the transition to the standalone touchscreen interface successfully consolidated the primary controls, several hardware-software interactions remain in an intermediate development phase:

- **Lighting Control Issues:** The internal high-intensity LED strip control loop is currently non-functional via the touchscreen interface. To ensure adequate visibility during active flow visualization trials, the lighting circuit has been bridged to an "always-on" state when the system is powered.
- **Tachometer Feedback Faults:** The telemetry data captured by the microcontroller from the fourth pin (tachometer signal) exhibits severe signal noise resulting in faulty and inconsistent RPM readings on the display dashboard.
#### 5.3.2 Future Software Roadmap

These unresolved features will be addressed in a subsequent iteration of the software bundle. Future debugging efforts will focus on implementing proper hardware interrupts for accurate pulse counting on the tachometer line and debugging the pulse-width modulation (PWM) or relay logic for the lighting subsystem. Resolving these issues will deliver a robust, fully integrated electronic package ready for seamless deployment and hand-off to future students.

## 6. Future Maintainers, Handover, & V2 Roadmap

### 6.1 Safety & Operation Standard Operating Procedures (SOP)

#### 6.1.1 Thermal and Mechanical Management of the Injection System

To prevent equipment damage and ensure user safety, operation of the Lensgo portable fog machine must adhere to strict runtime and handling constraints:

> ***WARNING: THERMAL BURN HAZARD***
> *Residual fluid discharging from the device between operational cycles reaches extreme temperatures. Operators must exercise strict caution, as direct contact with this high-temperature effluent can cause severe thermal burns. Furthermore, the metal nozzle assembly retains intense heat long after the machine is deactivated. Do not touch or handle the metal nozzle or drainage paths until the system has completely cooled to ambient temperature.*

- **Duty Cycle Limits:** Although the manufacturer specifies a baseline threshold, practical operation reveals that the device accumulates heat rapidly. It should not be operated continuously for more than 5 minutes at a time to avoid internal thermal overload.
- **Post-Operation Maintenance:** Immediately after shutting off the device, the internal vaporization chamber and heating coil remain dangerously hot. Users must never handle these internal components directly post-use.
- **Fluid Stagnation Clearing:** To prevent clogging, the device should be turned upside down after operation. This orientation utilizes gravity to drain stagnant fluid away from the heating coil, ensuring reliable startup in subsequent trials.
- **Pneumatic Coupling Care:** The rubber delivery tube frequently binds to the metal nozzle of the fog machine during thermal expansion. Users must never attempt to pull the tube off with force, as this can damage the fitting. The connection naturally loosens on its own once the system cools down to ambient temperature.

#### 6.1.2 Chemical Hazards and Ventilation Protocols

The smoke generation mechanism relies on the thermal vaporization of a glycerin and propylene glycol mixture. This process introduces specific biochemical considerations:

- **Acrolein Exposure Mitigation:** Under prolonged heating or restricted flow conditions, the thermal decomposition of glycerin produces acrolein, a volatile compound that acts as a severe respiratory and throat irritant.
- **Clogging Indicators and Maintenance:**  Acrolein concentration increases significantly if the machine is operated while clogged. Users must monitor the fluid state visually, as a distinct yellow discoloration of the fluid correlates directly with increased clogging and higher irritant production. If respiratory irritation becomes severe, the system must be shut down immediately. To clear the system, the contaminated fluid reservoir must be washed and allowed to dry completely, removing the degraded, yellowed mixture and replacing it with fresh, clear fluid.
#### 6.1.3 System Startup and Experimental Integration

To initialize the wind tunnel and begin qualitative flow visualization, follow these steps:

1. **Electrical Power-Up:** Connect the main power supply unit to the system. Assuming all internal wiring harnesses are securely attached, the microcontroller interface will initialize immediately, granting the operator immediate control over the exhaust fan speed profiles and telemetry.
2. **Mechanical Assembly:** Ensure the wind tunnel housing is fully assembled. The 3D-printed flow straighteners must be seated flush at the intake, the exhaust fan array secured at the outlet, and the selected aerodynamic smoke rake properly aligned and plugged into its mounting aperture.
3. **Fluidic Coupling:** After making sure the reservoir of the Lensgo fog machine is full up to at least midway with clear fluid. Connect the black delivery tube from the machine to the external-facing port of the 3D-printed adapter plug. Once coupled, initiate the smoke machine to feed the plenum, allowing the rake to produce stable, parallel streamlines within the test section.
### 6.2 Open-Source Sustainability and Obsolescence Defense

![](/_projects/Modular_Wind_Tunnel_Design/images/1200x900_Various_Modular_Components.png)
*Figure 6.2.a: Various Modular Components*

#### 6.2.1 Modular Architecture and Component Substitution

This project is engineered with a strict emphasis on adaptability and long-term modularity. Complete technical drawings, geometric dimensions, source code, and wiring schematics for every custom component are appended to this document. This open design framework ensures that if a specific hardware component becomes unavailable, undergoes manufacturer discontinuation, or suffers mechanical failure, future developers can easily adapt new hardware to interface with the existing system.

For example, if the commercial Lensgo portable fog machine fails or is phased out of production, the 3D-printed intake adapter plug can be easily remodeled or swapped out to accommodate the pneumatic tubing of a completely different aerosol generation device without requiring alterations to the primary tunnel housing.
#### 6.2.2 Version Control and Document Evolution

Continuous iterative development is highly encouraged. The architecture of this wind tunnel is intended to serve as an evolving platform rather than a static finalized product. If modifications are made to the mechanical components, electrical control loops, or software repositories, subsequent developers are strongly urged to amend this documentation. Keeping the master file up to date, or documenting experimental insights within their respective repository forks, preserves institutional knowledge and ensures the system remains highly functional for future engineering students.
### 6.3 Future Development Roadmap

Future student engineering teams looking to advance this platform should prioritize the following critical system upgrades:

- **Task A: Unified PCB Integration:** The current electrical infrastructure utilizes a breadboard configuration with discrete, loose voltage regulators. This layout should be converted into a single, custom printed circuit board (PCB). Designing and manufacturing a dedicated Gerber circuit board layout will significantly minimize signal noise, reduce the system's physical footprint, and eliminate intermittent wiring failures.
- **Task B: Telemetry Firmware Overhaul:** The software architecture requires a comprehensive rewrite to establish a reliable data pipeline between the physical sensor nodes and the graphical user interface. Future development must focus on stabilizing the hardware interrupt routines for the tachometer line and mapping those verified data streams directly to the touchscreen readout fields.
- **Task C: Dynamic Air Viscosity Estimation:** To transition the wind tunnel into a more quantitative testing instrument, an active software readout for real-time fluid properties should be developed. By integrating ambient temperature, barometric pressure, and localized altitude sensor inputs, the microcontroller can programmatically compute and display the active dynamic and kinematic air viscosity within the testing chamber.
- **Task D: Integrated Flow Anemometer:** A dedicated thermal or mechanical anemometer probe should be permanently fixed within the tunnel chassis. Routing this sensor's output directly to the primary control board will provide operators with constant, real-time core airspeed readouts, enabling accurate validation of the flow velocity alongside qualitative visualization trials.

## 7. File Repository

| Asset Description                 | Target Deployment Component   | File Reference                                           | Status     |
| :-------------------------------- | :---------------------------- | :------------------------------------------------------- | :--------- |
| **Complete Wind Tunnel Assembly** | Full Mechanical CAD Chassis   | `[Download STEP](./assets/machine_assembly.step)`        | **Active** |
| **Iterated Smoke Rakes & Plugs**  | Modular Flow Accessories      | `[Download STEP](./assets/smoke_rake_components.step)`   | **Active** |
| **Touchscreen Display Console**   | Control Electronics Housing   | `[Download STEP](./assets/ui_chassis_box.step)`          | **Active** |
| **ESP32 Touch Deck Firmware**     | System Source Control Code    | `[Download Source](./assets/esp32_control_firmware.ino)` | **Active** |
| **Integrated System Schematics**  | Point-to-Point Circuit Layout | `[Download PDF](./assets/circuit_schematics.pdf)`        | **Active** |
| **Custom Voltage/Sensor PCB**     | Unified Control Electronics   | `[Future Release]`                                       | *Planned*  |
