Introduction
============

OpenMfx is a plug-in API for sharing 3D mesh processing effects across different creation tools. It is built on top of [OpenFX](http://openeffects.org/>), which satisfies a similar need for non-destructive video compositing effects. OpenMfx is also known as the *OpenFX Mesh Effect API* and was formerly called *Open Mesh Effect*.

Why a standard?
---------------

Many 3D digital creation tools feature some non destructive workflow, relying on procedural geometry effect being recomputed on the fly whenever the underlying mesh data is modified. There are for instance Houdini SOPs, some of Maya's nodes, Blender's modifiers, Blender's geometry nodes.

Unfortunately, usual open exchange formats do not support these, as they might be implemented differently in different software, forcing geometries to be "baked" at export. This destructive step prevents one from tweaking the procedural parameters again. A standard description of such mesh effects will lead to effect that work exactly the same way in different software packages, enabling exchange formats to store meshes without baking them first.

For a more complete post about the motivations behind OpenMfx, see the introductory blog post [The need for Open Mesh Effect](https://blog.exppad.com/article/the-need-for-open-mesh-effect).

Why OpenFX?
-----------

OpenFX is a plug-in standard originally designed for 2D image processing and supported for instance by Nuke, After Effects, Fusion or Natron. With OpenMfx we intend to do the same for procedural 3D effects like Houdini nodes or Blender's modifiers.

> OpenFX has been designed for 2D images, it is completely different from 3D meshes, so why using it?

The OpenFX standard has been cleverly separated into several parts, leaving its core very generic. This OpenFX Mesh Effect API leverage on this agnostic core (called `ofxCore`) but completely ignores the image related part (`ofxImageEffect`). Instead, it defined an `ofxMeshEffect`, following similar patterns where it is relevant.

Current Status
--------------

*Last update: November 2022*

After 3.5 years of development, the core plugin API is mature enough to support a large variety of effects and backends, both on the host side and on the plugin side (different libraries for representing mesh data). The last breaking change in the API is more than 1 year old, even though as long as the user base remains very low we still allow ourselves to do so without increasing the API version number.

In order to ease the development of plugins, we developed a C++ SDK, and more recently we did the same for helping host development. This comes from the factorization of the code for our Blender and Unity implementations.

None of the implementations support the packaging system proposed by the original OpenFX standard, so far the examples embed everything they need in a single binary file, but it remains a goal.

As the representation of individual mesh effects is getting stable, we started to look into exchange formats for graphs (or stacks) of such effects. We presented for instance this part of the project at the ASFW's USD Working Group (see our slides about [USD x OpenMfx](https://docs.google.com/presentation/d/1pwBQQyLKe6Jt1U9XhXHRoWSxv7l9iCrknTzgbR0nHk0/edit?usp=sharing)).

We are getting close to show a full interchange of a node graph back and forth between geometry nodes and our Unity nodes, this is one of the key ongoing projects.

More generally, one can follow the chronology of the project by consulting our [Requests for comments](Rfc/index.md).

Support
-------

```{image} _static/Epic_MegaGrants_Recipient_logo_black128.png
:alt: Epic MegaGrant Recipient logo
:class: only-light
```

```{image} _static/Epic_MegaGrants_Recipient_logo_white128.png
:alt: Epic MegaGrant Recipient logo
:class: only-dark
```

The project received in 2021 the support of Epic MegaGrant. The funding was used to hire a master student during 6 months, which greatly impacted the project.

The project could be presented as a poster at SIGGRAPH '21 ([doi:10.1145/3450618.3469168](https://dl.acm.org/doi/10.1145/3450618.3469168)).
