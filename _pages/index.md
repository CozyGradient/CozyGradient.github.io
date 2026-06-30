---
layout: single
title: "Innovating at the Intersection of Engineering & Art"
permalink: /
author_profile: true
classes: wide
---

Welcome! I am a multi-disciplinary creator focused on mechanical design, aerodynamic testing, and digital art. My work bridges the gap between physical hardware fabrication and creative visual expression.

---

## 🚀 Featured Projects

Move the slider or click on any card to dive deep into the full design documentations, CAD pipelines, and data analysis.

{% include project-slider.html %}

---

## 🛠️ Core Capabilities

I love taking ideas completely from concept to functional reality. Here is a quick snapshot of the domains I play in:

| Engineering & Hardware | Creative & Digital Art |
| :--- | :--- |
| **Rapid Prototyping:** Fused Deposition Modeling (FDM) & printer mechanics tuning. | **Digital Illustration:** Concept art, sketching, and stylized rendering pipelines. |
| **Fluid Dynamics:** Wind tunnel design, water tank flow visualizers, and flow straighteners. | **3D Sculpting:** Hard-surface mechanical assets and organic character modeling. |
| **Automation & Code:** Computer vision tracking loops using OpenCV and NumPy data arrays. | **Visual Media:** Experimental effects, lighting, and smoke/fluid photography integration. |

---

### 📝 Recent Insights & Lab Notes

When I am not actively machining parts or sketching out shapes, I write about my technical breakthroughs, project failures, and lessons learned. Check out my latest blog entries below:

<ul class="post-list">
  {% for post in site.posts limit:3 %}
    <li>
      <article>
        <strong><a href="{{ post.url | relative_url }}">{{ post.title }}</a></strong> <small>— {{ post.date | date: "%B %d, %Y" }}</small>
        <p style="margin-top: 5px; font-size: 0.9em; opacity: 0.85;">{{ post.excerpt | strip_html | truncatewords: 20 }}</p>
      </article>
    </li>
  {% endfor %}
</ul>

<a href="{{ '/blog/' | relative_url }}" class="btn btn--info">View All Lab Notes</a>
