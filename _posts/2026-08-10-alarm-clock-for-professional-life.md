---
layout: single
title: "An Alarm Clock for Professional Life"
date: 2026-08-10
categories:
  - Engineering
  - Coding
  - Industrial Design
  - Arduino
tags:
  - arduino
  - Industrial Design
  - alarm clock
excerpt: "A new professional needs a way of waking up on time, so it's time to build an alarm clock."
header:
  teaser: "/assets/images/posts/alarm-clock/teaser.jpg"
  overlay_image: "/assets/images/posts/alarm-clock/banner.jpg"
  overlay_filter: 0.4
toc: false
toc_sticky: false
---

# An Alarm Clock for Professional Life

So I've been waking up later than usual, as I normalize to life outside of academia and I've also been applying for work recently. I've realized that a good way to put my engineering degree to use and add something practical to my life is to build an alarm clock, but not just any alarm clock oh no, an alarm clock that can brief me on current world events. This might snowball into a larger project but I'm currently undecided on how hard I should pursue this.

## Drafting the Ideas

I've been getting into industrial design lately mainly through the works of legendary designer Dieter Rams, I've been studying some of his work with Braun. Theres just something so mesmerizing about the sleek utilitarian minimalism of his work. So early ideas started off considering exactly which features the alarm clock needed and how the interface should be set up in such a way to interact with those features. I sketched out some early designs and decided to work on the hardware and initial software implementation.

## The Hardware & Software

Due to the nature of the project being a device that needs up to date information on world events, IoT was a non negotiable framework to go by. I decided to choose a simple ESP32 dev board for it's ubiquity and heavy support (and since I already had one on hand). I wrote up a simple script to display a clock on screen and this is by no means even an initial draft of the software going forward but it's a good starting point. The device will eventually make API calls to various services like my calendar provider to give me a briefing of what I have on my plate for the day, I'm also gonna add a weather forecast and maybe some extra spice like whether or not the Hormuz Strait is open (not that I have a stake in brent crude!).

Here I've Set up a basic breadboard layout with the buttons I'm considering adding to the finished design. I decided it would be safe to add 3 buttons for the controls and 1 button for the alarm. Powered by 5v to reduce complexity with step down converters.

## Future Ideas and   Improvements

<!--
OPTIONAL: closing thoughts / future improvements
-->
