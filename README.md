![CMake Badge](https://github.com/eliemichel/OpenMfx/actions/workflows/cmake.yml/badge.svg)

<p align="center">
  <img alt="OpenMfx" src="doc/images/openmesheffect.png">
</p>

OpenMfx
=======

*The OpenFX Mesh Effect API.*

OpenMfx is a plug-in standard for 3D mesh processing effects built on top of [OpenFX](http://openeffects.org/), a standard originally designed for 2D image processing.

**The official documentation of the API is located at https://openmesheffect.org**

**NB** OpenMfx was first known as "Open Mesh Effect", we decided to rename it because "OpenMfx" is easier to abbreviate and was emerging from the usage anyways.

## Why a standard?

Many 3D software feature some non destructive workflow, relying on procedural geometry effect being recomputed on the fly whenever the underlying mesh data is modified. One can quote for instance Houdini SOPs, some of Maya's nodes, or Blender's modifiers. Unfortunately, usual open exchange formats do not support these, as they might be implemented differently in different software, forcing geometries to be "baked" at export. This destructive step prevents one from tweaking the procedural parameters again. A standard description of such mesh effects will lead to effect that work exactly the same way in various software, enabling exchange formats to store meshes without baking them first.

> OpenFX has been designed for 2D images, it is completely different from 3D meshes, so why using it?

The OpenFX standard has been cleverly separated into several parts, leaving its core very generic. This OpenFX Mesh Effect API leverage on this agnostic core (called `ofxCore`) but completely ignores the image related part (`ofxImageEffect`). Instead, it defined an `ofxMeshEffect`, following similar patterns where it is relevant.

For a more complete post about the motivations behind OpenMfx, see [The need for Open Mesh Effect](https://blog.exppad.com/article/the-need-for-open-mesh-effect).

## Implementations

### Hosts

Existing host software that supports OpenMfx are listed [here](https://openmesheffect.org/Implementations/HostExamples.html).

### Plug-ins

To use existing plug-ins, check out [this list of existing plug-ins](https://openmesheffect.org/Implementations/PluginExamples.html).

To write your own plug-in, see the [C++ SDK tutorial](https://openmesheffect.org/Guide/TutorialCppSdk.html).

## License

See [LICENSE.md](LICENSE.md).

## Contributing

Although the standard itself is getting stable, help is welcome to improve the ecosystem of tools. Feel free to give some feedback through the GitHub [issues](https://github.com/eliemichel/OpenMeshEffect/issues) of this repository.
