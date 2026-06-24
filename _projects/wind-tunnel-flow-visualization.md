---
layout: single
title: "Wind Tunnel Flow Visualization Setup"
excerpt: "Designing a modular testing environment for aerodynamic flow observation using custom 3D-printed mechanics."
header:
  teaser: "/assets/images/projects/wind-tunnel-teaser.jpg"
gallery:
  - url: /assets/images/projects/wind-tunnel-1.jpg
    image_path: /assets/images/projects/wind-tunnel-1.jpg
    alt: "Lensgo Smoke Go integration"
  - url: /assets/images/projects/wind-tunnel-2.jpg
    image_path: /assets/images/projects/wind-tunnel-2.jpg
    alt: "Airflow over model airplane"
toc: true
toc_sticky: true
---

This project focuses on building a reliable, small-scale wind tunnel setup capable of clear aerodynamic flow visualization. The primary goal was to observe air currents and vortex generation over various physical models.

## Hardware & Fabrication
To ensure a tight, controlled airflow environment, several key mechanical components were custom-designed and rapidly prototyped using Creality 3D printers. 

Key modifications included:
* Printing modular mounts to securely hold model airplanes and test shapes within the test chamber.
* Upgrading the printer hardware, specifically the hotend fan, to handle continuous, long-duration prints of the structural supports.
* Ensuring filament consistency with a dedicated drying setup to prevent stringing on precise aerodynamic testing parts.

## Flow Visualization Integration
For the actual visualization, I integrated a Lensgo Smoke Go fog machine directly into the air intake. By piping the fog through a custom-printed flow straightener, the setup produces clean, distinct streamlines. 

Here is a look at the hardware integration and initial test runs:

{% include gallery caption="Testing the smoke stream integration and model airflow." %}

## Results and Next Steps
The streamlined fog effectively highlighted the vortex paths coming off the model edges. Future iterations will involve transitioning some of these tests into a water tank environment to compare fluid dynamic behaviors across different mediums.
