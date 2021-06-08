.. _SdkReference:

OpenMfx SDK Reference
=====================

The SDK is a C++ library that aims at making the development of plugins easier than using the raw OpenMfx API. For the reference of the underlying C API, see :ref:`ApiReference`.

At the bare minimum a plugin defines a subclass of \ref MfxEffect and registers it using \ref MfxRegister so these are good entry points for reading.

.. toctree::
   :maxdepth: 1

   Classes/macros
   Classes/MfxAttribute
   Classes/MfxAttributeProps
   Classes/MfxBase
   Classes/MfxEffect
   Classes/MfxHost
   Classes/MfxInput
   Classes/MfxInputDef
   Classes/MfxMesh
   Classes/MfxMeshProps
   Classes/MfxParam
   Classes/MfxParamDef
   Classes/MfxRegister
   Classes/MfxSuiteException
