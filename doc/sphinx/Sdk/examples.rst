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
	};

	MfxRegister(
		MyEffect
	);

Other examples
--------------

You can look at MfxVCG and MfxVTK as example of real-life Open Mesh Effect plugins actually using the "CppPluginSupport" Sdk.
