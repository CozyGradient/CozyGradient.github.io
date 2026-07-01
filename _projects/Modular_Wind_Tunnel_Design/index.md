---
title: "Modular Desktop Wind Tunnel"
excerpt: "An affordable, educational tool for studying fluid dynamics right on your desk."
layout: single
permalink: /projects/modular-wind-tunnel/
author_profile: true
header:
  overlay_image: /_projects/Modular_Wind_Tunnel_Design/images/1080x500_Banner.png
  overlay_filter: 0.4
  teaser: /_projects/Modular_Wind_Tunnel_Design/images/1080x600_Teaser.png # ADD THIS LINE
  actions:
    - label: "Jump straight to Technical Deep Dive"
      url: "/projects/modular-wind-tunnel/deep-dive/"
      btn_class: "btn--primary"

feature_row_overview:
  - image_path: /_projects/Modular_Wind_Tunnel_Design/images/1200x900_Sketch_to_Real_Life.png
    alt: "From concept to real life"
    title: "The Vision"
    excerpt: "Traditional wind tunnels are massive and cost thousands of dollars. This project breaks down a professional fluid dynamics lab into safe, modular, 3D-printable blocks that fit on a standard desk."
    feature_row_overview:
  - image_path: /_projects/Modular_Wind_Tunnel_Design/images/1200x900_Sketch_to_Real_Life.png
    alt: "From concept to real life"
    title: "The Vision"
    excerpt: "Traditional wind tunnels are massive and cost thousands of dollars. This project breaks down a professional fluid dynamics lab into safe, modular, 3D-printable blocks that fit on a standard desk."
    feature_row_overview:
  - image_path: /_projects/Modular_Wind_Tunnel_Design/images/1200x900_Sketch_to_Real_Life.png
    alt: "From concept to real life"
    title: "The Vision"
    excerpt: "Traditional wind tunnels are massive and cost thousands of dollars. This project breaks down a professional fluid dynamics lab into safe, modular, 3D-printable blocks that fit on a standard desk."
---

## The Basic Idea

This machine is a wind tunnel, meaning it produces a torrent of wind inside a closed off volume for a variety of observations. Some wind tunnels are designed to let you measure objects undergoing flow scenarios, and others are designed just to visualize smoke. The machine I designed falls into the latter category, for a number of reasons I'll leave out here _(psst, check out the deep dive)_.

{% include video id="kYgQ7hUqkZo" provider="youtube" %}

This machine lets you see wake behaviors and stagnation points in flow regions, meaning the downwind parts of the flow that don't seem to be going anywhere. In real life this causes issues like drag, which reduces fuel efficiency in cars and aircraft, or slows down someone jumping out of a plane with (or without) a parachute.

<figure>
    <img src="/_projects/Modular_Wind_Tunnel_Design/images/1920x1080_Informative_Diagram.png" alt="Informative Diagram Wind Tunnel During Operation"/>
    <figcaption>What are we looking for when the machine is running?</figcaption>
</figure>
It has interchangeable smoke rakes, which let you change how smoke gets distributed in the volume. This means you can either have chaotic turbulent streamlines from the get go, or put in rakes shaped like the objects you actually want to study, like the von Karman rakes I designed, which trace flow going over circular cross sections and produce periodic vortex shedding events.

The machine isn't perfect, and I think it could be improved with a couple tweaks. Sadly deadlines are a thing, since this served as my graduation project, so I never got to fully clean up the streamlines. That said, it still produces some really cool visuals.

{% include feature_row id="feature_row_overview" %}

## Ready for the Engineering Details?

If you're looking for calculations, raw CFD validation models, honeycomb flow straightener geometry, or electrical circuit schematics, check out the full engineering documentation.
