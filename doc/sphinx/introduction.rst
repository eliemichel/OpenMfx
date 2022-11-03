.. Introduction

Introduction
============

OpenMfx is a plug-in standard for 3D mesh processing effects built on top of `OpenFX <http://openeffects.org/>`_. It is also known as the *OpenFX Mesh Effect API* and formerly *Open Mesh Effect*.

**Recommended fore-reading** Since OpenMfx is built on top of OpenFX, the reader should know about the bases of OpenFX Core by reading `OpenFX documentation <https://openfx.readthedocs.io/en/master/>`_.

OpenFX is a plug-in standard originally designed for 2D image processing and supported for instance by Nuke, After Effects, Fusion or Natron. With OpenMfx we intend to do the same for procedural 3D effects like Houdini nodes or Blender's modifiers.

Why a standard?
---------------

Many 3D software feature some non destructive workflow, relying on procedural geometry effect being recomputed on the fly whenever the underlying mesh data is modified. One can quote for instance Houdini SOPs, some of Maya's nodes, or Blender's modifiers. Unfortunately, usual open exchange formats do not support these, as they might be implemented differently in different software, forcing geometries to be "baked" at export. This destructive step prevents one from tweaking the procedural parameters again. A standard description of such mesh effects will lead to effect that work exactly the same way in different softwares, enabling exchange formats to store meshes without baking them first.

For a more complete post about the motivations behind OpenMfx, see `The need for Open Mesh Effect <https://blog.exppad.com/article/the-need-for-open-mesh-effect>`_.

Why OpenFX?
-----------

	OpenFX has been designed for 2D images, it is completely different from 3D meshes, so why using it?

The OpenFX standard has been cleverly separated into several parts, leaving its core very generic. This OpenFX Mesh Effect API leverage on this agnostic core (called ``ofxCore``) but completely ignores the image related part (``ofxImageEffect``). Instead, it defined an ``ofxMeshEffect``, following similar patterns where it is relevant.

Documentation
-------------

The reminder of this documentation is split into:

- The Mesh Effect API reference, completing the `OpenFX reference <https://openfx.readthedocs.io/en/master/Reference/index.html>`_ with mesh effects: `The OpenMfx API reference <Reference>`_

- A programming guide to help newcomers write their own host and plugins: `The OpenMfx Programming Guide <Guide>`_

- Examples of implementation, both for `host <Implementations/Host>`_ and `plugins <Implementations/Plugins>`_: `Implementations and Related Work <Implementations>`_

- The documentation of the C++ SDK, namely a set of classes built on top of the C API that is not mandatory to use but can ease the developement of C++ plugins: `Software Development Kit <Sdk>`_

**Current status of this memo** This is a work in progress DRAFT of the API. Some parts are still missing, others need intensive testing. Feel free to `fill issues <https://github.com/eliemichel/OpenMeshEffect/issues>`_ if you have any suggestions.
