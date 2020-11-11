.. _SdkExamples:

Open Mesh Effect SDK Examples
=============================

Simple example
--------------

.. sourcecode:: cpp

	#include <PluginSupport/MfxEffect>
	#include <PluginSupport/MfxRegister>

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

Other examples
--------------

You can look at `MfxVCG <https://github.com/eliemichel/MfxVCG>`_ and `MfxVTK <https://github.com/tkarabela/MfxVTK>`_ as example of real-life Open Mesh Effect plugins actually using the "CppPluginSupport" Sdk.
