.. _PluginGuide:

Writing an Open Mesh Effect plugin
==================================

There are two levels at which it is possible to write Open Mesh Effect plug-ins. The first one is using the low-level C API as described in the `reference </Reference>`_ section. The second one uses a higher level C++ API called ``CppPluginSupport``.

To get a first glance of the C API, you can have a look at this tutorial, but **it is outdated**: https://github.com/eliemichel/OpenMeshEffect/blob/master/doc/guide/plugin-guide.md It has been written with for previous draft of the API in which there was no notion of custom attributes.

The ``CppPluginSupport`` utility library has been used by `MfxVCG <https://github.com/eliemichel/MfxVCG>`_ and `MfxVTK <https://github.com/tkarabela/MfxVTK>`_ already, so you can look these up for reference.

You can also have a look at other examples: :ref:`PluginExamples`

