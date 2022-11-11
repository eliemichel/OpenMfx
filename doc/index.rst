.. OpenMfx documentation master file

OpenMfx
=======

OpenMfx is a plug-in API for procedural 3D mesh effects.

- **cross-software** -- Write a mesh processing effect once, run it in every digital content creation tool that supports OpenMfx.
- **low overhead** -- The API intends to limit as much as possible the copy of data in the communication between a plugin and the host software.
- **non-destructive interchange** -- Export a 3D scene without burning in non-destructive effects. If these effects are backed by OpenMfx plugins, they can be seamlessly imported into another piece of software and result in the very same geometry.
- **user-friendly** -- Writing your own mesh processing effect is made as straightforward as possible thanks to a C++ SDK that wraps around the portable raw C API, providing a nicer interface without scarifying performance.

Contents
--------

.. toctree::
   :maxdepth: 2
   :titlesonly:

   introduction
   QuickStart/index
   Guide/index
   Sdk/index
   Reference/index
   Implementations/index
   Rfc/index
