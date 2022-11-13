.. _HostExamples:

Available hosts
===============

This page intends to list all the implementations of the OpenMfx API as a host, i.e., all the creation tools that can handle OpenMfx plugins.

The most notable one so far is the `OpenMfx for Blender <https://github.com/eliemichel/OpenMeshEffectForBlender>`_ branch. The need for such a standard urged when trying to tie Blender and Houdini together while respecting the spirit of the GPL license under which Blender is released. See `the discussion on Blender Dev Talk forum <https://devtalk.blender.org/t/houdini-engine-modifier-for-blender/8218>`_.

`UnityMfx <https://github.com/eliemichel/UnityMfx>`_ is a Unity-based implementation of OpenMfx.

`PythonMfx <https://github.com/eliemichel/PythonMfx>`_ is a python-only implementation of an OpenMfx host. It is meant more for developing validation tools for plugins/hosts than for performance.

`WebMfx <https://github.com/eliemichel/WebMfx>`_ is PoC running OpenMfx plugins on the web, using emscripten.

Detailed pages
--------------

.. toctree::
   :maxdepth: 2
   :titlesonly:

   Hosts/Blender
