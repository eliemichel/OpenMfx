
<p align="center">
  <img alt="Open Mesh Effect" src="doc/images/openmesheffect.png">
</p>

OpenFX Mesh Effect API
======================

This is a plug-in standard for 3D mesh processing effects built on top of [OpenFX](http://openeffects.org/), a standard originally designed for 2D image processing.

**The official documentation of the API is now located at https://openmesheffect.org**

## Why a standard?

Many 3D software feature some non destructive workflow, relying on procedural geometry effect being recomputed on the fly whenever the underlying mesh data is modified. One can quote for instance Houdini SOPs, some of Maya's nodes, or Blender's modifiers. Unfortunately, usual open exchange formats do not support these, as they might be implemented differently in different software, forcing geometries to be "baked" at export. This destructive step prevents one from tweaking the procedural parameters again. A standard description of such mesh effects will lead to effect that work exactly the same way in different softwares, enabling exchange formats to store meshes without baking them first.

For a more complete post about the motivations behind Open Mesh Effect, see [The need for Open Mesh Effect](https://blog.exppad.com/article/the-need-for-open-mesh-effect).

## Why OpenFX?

> OpenFX has been designed for 2D images, it is completely different from 3D meshes, so why using it?

The OpenFX standard has been cleverly separated into several parts, leaving its core very generic. This OpenFX Mesh Effect API leverage on this agnostic core (called `ofxCore`) but completely ignores the image related part (`ofxImageEffect`). Instead, it defined an `ofxMeshEffect`, following similar patterns where it is relevant.

## Implementations

### Hosts

 - Example of [host](examples/host/) from this repository
 - [OpenMeshEffectForBlender](https://github.com/eliemichel/OpenMeshEffectForBlender), a host integratint Open Mesh Effect plug-ins in Blender as *modifiers*.

*NB: None of these implementations are complete. The Blender implementation is based on the example from this repository.*

### Plug-ins

 - Examples of [plugins](examples/plugins/) from this repository
 - [MfxVCG](https://github.com/eliemichel/MfxVCG) is an example of Open Mesh Effect plug-in that provides mesh filters from [VCGlib](http://www.vcglib.net/), the core library of [MeshLab](http://www.meshlab.net/).
 - [MfxVTK](https://github.com/tkarabela/MfxVTK) by @tkarabela provides effects from the [Visualization ToolKit](https://gitlab.kitware.com/vtk/vtk) as an OpenMeshEffect plugin.

## License

See [LICENSE.md](LICENSE.md).

## Contributing

This document currently is a draft. Feel free to give some feedback through the GitHub [issues](https://github.com/eliemichel/OpenMeshEffect/issues) of this repository.

## History

The need for such a standard urged when I tried to tie Blender and Houdini together while respecting the spirit of the GPL license under which Blender is released. See [the discussion on Blender Dev Talk forum](https://devtalk.blender.org/t/houdini-engine-modifier-for-blender/8218).
