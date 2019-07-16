
<p align="center">
  <img alt="Open Mesh Effect" src="doc/images/openmesheffect.png">
</p>

OpenFX Mesh Effect API
======================

This is a plug-in standard for 3D mesh processing effects built on top of [OpenFX](http://openeffects.org/), a standard originally designed for 2D image processing.

Recommended fore-reading: OpenFX Core Guide and Reference from the [OpenFX repository](https://github.com/ofxa/openfx).

The present repository contains:

 - The Mesh Effect API itself: [`ofxMeshEffect`](include/)
 - Examples of implementation, both for [host](examples/host/) and [plug-ins](examples/plugins/).
 - Documentation, with a [programming guide](doc/guide/) as well as [config](doc/generated/) to generate doc from header files (you can also read comments from header files directly).

**Current status of this memo** This is a work in progress DRAFT of the API. Some parts are still missing, others need intensive testing. Feel free to fill issues if you have any suggestions.

## Why a standard?

Many 3D software feature some non destructive workflow, relying on procedural geometry effect being recomputed on the fly whenever the underlying mesh data is modified. One can quote for instance Houdini SOPs, some of Maya's nodes, or Blender's modifiers. Unfortunately, usual open exchange formats do not support these, as they might be implemented differently in different software, forcing geometries to be "baked" at export. This destructive step prevents one from tweaking the procedural parameters again. A standard description of such mesh effects will lead to effect that work exactly the same way in different softwares, enabling exchange formats to store meshes without baking them first.

## Why OpenFX?

> OpenFX has been designed for 2D images, it is completely different from 3D meshes, so why using it?

The OpenFX standard has been cleverly separated into several parts, leaving its core very generic. This OpenFX Mesh Effect API leverage on this agnostic core (called `ofxCore`) but completely ignores the image related part (`ofxImageEffect`). Instead, it defined an `ofxMeshEffect`, following similar patterns where it is relevant.

## License

See [LICENSE.md](LICENSE.md).

## Contributing

This document currently is a draft. Feel free to give some feedback through the GitHub [issues](https://github.com/eliemichel/OpenMeshEffect/issues) of this repository.

## History

The need for such a standard urged when I tried to tie Blender and Houdini together while respecting the spirit of the GPL license under which Blender is released. See [the discussion on Blender Dev Talk forum](https://devtalk.blender.org/t/houdini-engine-modifier-for-blender/8218).
