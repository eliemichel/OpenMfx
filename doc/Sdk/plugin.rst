.. _PluginSdkReference:

Plugin SDK
==========

The Plugin SDK is a C++ library that aims at making the development of plugins easier than using the raw OpenMfx API. For the reference of the underlying C API, see :ref:`ApiReference`.

To get started with the SDK, it is recommended to follow the tutorial: the tutorial :ref:`TutorialCppSdk`. At the bare minimum a plugin defines a subclass of :ref:`MfxEffect` and registers it using :ref:`MfxRegister` so these are good entry points for reading.

When using CMake, link your project to the target ``OpenMfx::Sdk::Cpp::Plugin`` to use this SDK.

Contents
--------

.. toctree::
   :maxdepth: 1

   Plugin/macros
   Plugin/MfxAttribute
   Plugin/MfxAttributeProps
   Plugin/MfxBase
   Plugin/MfxEffect
   Plugin/MfxHost
   Plugin/MfxInput
   Plugin/MfxInputDef
   Plugin/MfxMesh
   Plugin/MfxMeshProps
   Plugin/MfxParam
   Plugin/MfxParamDef
   Plugin/MfxRegister
   Plugin/MfxSuiteException
