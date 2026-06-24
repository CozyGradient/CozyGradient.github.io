---
layout: single
title: "Extracting Vortex Core Data Using Python"
date: 2026-06-24
categories:
  - Engineering
  - Coding
tags:
  - fluid-dynamics
  - python
  - data-analysis
excerpt: "Using OpenCV and NumPy to track vortex core displacement from laboratory fluid tank video footage."
header:
  teaser: "/assets/images/posts/vortex-analysis/teaser.jpg"
  overlay_image: "/assets/images/posts/vortex-analysis/banner.jpg"
  overlay_filter: 0.4
toc: true
toc_sticky: true
---

After running several flow visualization trials in the water tank, I ended up with hours of high-speed video footage. Manually tracking the center of the generated vortex frame-by-frame was out of the question, so I wrote a quick Python script to automate the tracking process.

## The Computer Vision Pipeline

The script relies on **OpenCV** and **NumPy** to process the contrast differences in the water. Because the fluid is seeded with particles, the core of the vortex naturally creates a low-density region that can be isolated using thresholding.

Here is the core logic used to isolate the vortex center in each frame:

```python
import cv2
import numpy as np

def find_vortex_core(frame):
    # Convert to grayscale and apply Gaussian blur to reduce noise
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    blurred = cv2.GaussianBlur(gray, (7, 7), 0)
    
    # Threshold the image to isolate the dark vortex core
    _, thresh = cv2.threshold(blurred, 45, 255, cv2.THRESH_BINARY_INV)
    
    # Find contours of the isolated shape
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    return contours
```
