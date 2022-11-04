.. _HostExamples:

Examples of OpenMfx hosts
=========================

This page intends to list all the implementations of the OpenMfx API as a host, i.e. all the software that can handle OpenMfx plugins.

The most notable one so far is the `OpenMfx for Blender <https://github.com/eliemichel/OpenMeshEffectForBlender>`_ branch. The need for such a standard urged when trying to tie Blender and Houdini together while respecting the spirit of the GPL license under which Blender is released. See `the discussion on Blender Dev Talk forum <https://devtalk.blender.org/t/houdini-engine-modifier-for-blender/8218>`_.

There is also a `Host Example <https://github.com/eliemichel/OpenMeshEffect/examples/host/>`_ in the OpenMfx repository. It is basically the part of the code extracted from the Blender branch that is not forced to lie under the GPL license. It might be less up to date so it is better to refer to directly the Blender branch, in particular to the directory ``intern/openmesheffect``.
