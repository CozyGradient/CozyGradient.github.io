---
layout: archive
title: "Blog Posts"
permalink: /blog/
author_profile: true
---

<div class="blog-grid">
{% for post in site.posts %}
{% include archive-single.html type="grid" %}
{% endfor %}
</div>
