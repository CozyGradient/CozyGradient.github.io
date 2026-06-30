---
layout: single
title: "Homepage"
permalink: /
author_profile: true
classes: wide
---
---
Hello, I’m Levent. I’m a mechanical engineer who loves making things. I’m big on industrial design, simulation, and renewable technology, and I’m driven by the goal of making a real, positive impact. This site is a collection of my engineering projects, experiments, and whatever other interesting ideas I’m currently digging into. Hope you find the work interesting.

## Featured Projects
A look at what I’ve been building lately, this includes everything from hardware prototypes to simulations.

{% include project-slider.html %}

## Recent Work
This is where I dump my thoughts. It’s a mix of technical deep-dives, project post-mortems, and the random experiments I’m playing with. Check out my latest entries below.

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
