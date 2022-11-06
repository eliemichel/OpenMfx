Writing an OpenMfx plugin
=========================

Plugins may be written in various languages, provided they can interface with the raw C API. The easiest route is to use C++ and the helper SDK provided by the OpenMfx project.

Requirements
------------

To follow these instructions, you will need the following standard C++ development tools:

 - [Git](https://git-scm.com/download)
 - [CMake](https://cmake.org/download)
 - A C++ building toolchain ([Visual Studio](https://visualstudio.microsoft.com/downloads), `gcc`+`make`, ...)

```{important}
Make sure that `git` and `cmake` commands are available in your `PATH`.
```

Building MfxExamples
--------------------

In order to get started with writing your first plugin, we will simply modify the [MfxExamples](https://github.com/eliemichel/MfxExamples) project. Let us start by building the project as is:

 1. Clone the *MfxExamples* repository:

```bash
git clone https://github.com/eliemichel/MfxExamples.git
cd MfxExamples
```

 2. Configure the build:

```bash
mkdir build
cd build
cmake ..
```

 3. Build the project, either by opening the Visual Studio solution generated in the `MfxExamples/build` directory, or by running:

```bash
cmake --build .
```

You should have a `mfx_examples.ofx` file created in eiter `MfxExamples/build`, `MfxExamples/build/Debug` or `MfxExamples/build/Release` depending on your configuration.

Adding an effect
----------------

We now add a new effect to the, which we call "MyCoolEffect".

 1. Create a new file for your effect, called `MyCoolEffect.hpp`.

 2. In [`plugin.cpp`](https://github.com/eliemichel/MfxExamples/blob/main/plugin.cpp), include your hpp file and add your effect to the end of the `MfxRegister` call:

```C++
// [...]
#include "MyCoolEffect.hpp"

// [...]

MfxRegister(
    // [...]
    BoxGeneratorEffect,
    ExplodeEffect,
    MyCoolEffect // make sure not to add a comma after the last effect!
)
```

 3. In `MyCoolEffect.hpp`, we include the Plugin SDK and define a subclass of `MfxEffect`:

```C++
#include <OpenMfx/Sdk/Cpp/Plugin/MfxEffect>

class MyCoolEffect : public MfxEffect {
	// [...]
}
```

 4. We define 3 members in the `MyCoolEffect` class:

```C++
class MyCoolEffect : public MfxEffect {
public:
	// Return the human-readable name of the effect
	const char* GetName() override {
		return "MyCoolEffect";
	}

protected:
	// Declare the list of expected input/outputs and parameters of the effect
	OfxStatus Describe(OfxMeshEffectHandle) override;

	// Compute the output of the effect
	OfxStatus Cook(OfxMeshEffectHandle) override;
}
```

 5. We declare 1 input, 1 output and 1 parameter in `Describe`

```C++
OfxStatus MyCoolEffect::Describe(OfxMeshEffectHandle) {
	AddInput(kOfxMeshMainInput);
	AddInput(kOfxMeshMainOutput);

	AddParam("translation", double3{0.0, 0.0, 0.0})
	.Label("Translation") // Name used for display
	.Range(double3{-10.0, -10.0, -10.0}, double3{10.0, 10.0, 10.0});
	
	return kOfxStatOK;
}
```

```{note}
The "input" called `kOfxMeshMainOutput` is considered as the output. There is at most one output in an effect, and since an output behaves very similarly to an input, one interacts with it using the functions and types in the OpenMfx API.
```

 6. We implement the core behavior in `Cook`. This code is detailed in [the C++ Plugin SDK Guide](../Guide/TutorialCppSdk.rst).

```C++
OfxStatus MyCoolEffect::Cook(OfxMeshEffectHandle) {
	MfxMesh input_mesh = GetInput(kOfxMeshMainInput).GetMesh();
	MfxAttributeProps input_positions;
	input_mesh.GetPointAttribute(kOfxMeshAttribPointPosition)
		.FetchProperties(input_positions);

	double3 translation = GetParam<double3>("translation").GetValue();

	MfxMeshProps meshProps;
	input_mesh.FetchProperties(meshProps);

	MfxMesh output_mesh = GetInput(kOfxMeshMainOutput).GetMesh();

	output_mesh.GetCornerAttribute(kOfxMeshAttribCornerPoint)
		.ForwardFrom(input_mesh.GetCornerAttribute(kOfxMeshAttribCornerPoint));

	if (meshProps.constantFaceSize < 0) {
		output_mesh.GetFaceAttribute(kOfxMeshAttribFaceSize)
			.ForwardFrom(input_mesh.GetFaceAttribute(kOfxMeshAttribFaceSize));
	}

	output_mesh.Allocate(meshProps);

	MfxAttributeProps output_positions;
	output_mesh.GetPointAttribute(kOfxMeshAttribPointPosition)
		.FetchProperties(output_positions);

	// (NB: This can totally benefit from parallelization using e.g. OpenMP)
	for (int i = 0; i < meshProps.pointCount; ++i) {
		float* in_p = input_positions.at<float>(i);
		float* out_p = output_positions.at<float>(i);
		out_p[0] = in_p[0] + static_cast<float>(translation[0]);
		out_p[1] = in_p[1] + static_cast<float>(translation[1]);
		out_p[2] = in_p[2] + static_cast<float>(translation[2]);
	}

	output_mesh.Release();
	input_mesh.Release();

	return kOfxStatOK;
}
```
