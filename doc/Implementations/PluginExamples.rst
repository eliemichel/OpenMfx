.. _PluginExamples:

Examples of OpenMfx plugins
===========================

This page intends to list all the publicly available OpenMfx plugins.

To begin with, there are sample plugins in the OpenMfx repository: `examples/plugins <https://github.com/eliemichel/OpenMeshEffect/examples/plugins/>`_. Some of them are outdated, relevant examples are for instance ``mfx_test_parameters_plugin`` and ``mfx_uv_transform``.
 
`MfxVCG <https://github.com/eliemichel/MfxVCG>`_ is an example of OpenMfx plug-in that provides mesh filters from `VCGlib <http://www.vcglib.net/>`_, the core library of `MeshLab <http://www.meshlab.net/>`_.

`MfxVTK <https://github.com/tkarabela/MfxVTK>`_ provides effects from the `Visualization ToolKit <https://gitlab.kitware.com/vtk/vtk>`_ as an OpenMfx plug-in.

`MfxHoudini <https://github.com/eliemichel/MfxHoudini>`_ is an OpenMfx plug-in that calls the `Houdini Engine <https://www.sidefx.com/products/houdini-engine/>`_ to be able to run any Houdini Digital Asset as a mesh effect.

`MfxExamples <https://github.com/eliemichel/MfxExamples>`_ is a simple repository using the C++ SDK that one can use as a starter pack.

Simple example
--------------

Here is a really simple example of how to use the API

.. sourcecode:: cpp

	#include <OpenMfx/Sdk/Cpp/Plugin/MfxEffect>
	#include <OpenMfx/Sdk/Cpp/Plugin/MfxRegister>

	class MyEffect : public MfxEffect {
	protected:
		OfxStatus Describe(OfxMeshEffectHandle descriptor) override {
			AddInput(kOfxMeshMainInput);
			AddInput(kOfxMeshMainOutput);

			AddParam("axis", 1)
			.Label("Axis")
			.Range(0, 2);

			AddParam("translation", { 0.0, 0.0 })
			.Label("Translation");

			return kOfxStatOK;
		}

		OfxStatus Cook(OfxMeshEffectHandle instance) override {
			// ...
		}
	};

	MfxRegister(
		MyEffect
	);
