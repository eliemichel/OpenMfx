.. _PluginGuide:

Writing an OpenMfx plugin
=========================

There are two levels at which it is possible to write an OpenMfx plug-in. The first one is using the low-level C API as described in the `reference </Reference>`_ section. The second one uses a higher level C++ API called `SDK </Sdk>`_ or ``CppPluginSupport``.

The easiest route is to start with the C++ SDK, and follow the tutorial :ref:`TutorialCppSdk`. This SDK has been used by `MfxVCG <https://github.com/eliemichel/MfxVCG>`_ and `MfxVTK <https://github.com/tkarabela/MfxVTK>`_ already, so you can also look these up for reference.

To write plug-ins directly using the C API, see :ref:`TutorialCApi`. You can also have a look at other examples: :ref:`PluginExamples`.
