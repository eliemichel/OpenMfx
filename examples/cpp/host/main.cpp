#include <OpenMfx/Sdk/Cpp/Host/MfxHost>
#include <OpenMfx/Sdk/Cpp/Host/MeshEffect>
#include <OpenMfx/Sdk/C/BinaryUtils>

#include <exception>
#include <iostream>
#include <vector>
#include <array>

struct MyMeshStruct {
	std::vector<std::array<float, 3>> points;
	std::vector<std::array<int, 3>> triangles;
	bool isInput = true;
};

class MyHost : public OpenMfx::MfxHost {
	OfxStatus BeforeMeshGet(OfxMeshHandle ofxMesh) override {
		MyMeshStruct *myMesh = nullptr;
		propertySuite->propGetPointer(&ofxMesh->properties, kOfxMeshPropInternalData, 0, (void**)&myMesh);

		if (myMesh == nullptr)
			return kOfxStatErrFatal;

		if (!myMesh->isInput)
			return kOfxStatOK;

		propertySuite->propSetInt(&ofxMesh->properties, kOfxMeshPropPointCount, 0, static_cast<int>(myMesh->points.size()));
		propertySuite->propSetInt(&ofxMesh->properties, kOfxMeshPropCornerCount, 0, 3 * static_cast<int>(myMesh->triangles.size()));
		propertySuite->propSetInt(&ofxMesh->properties, kOfxMeshPropFaceCount, 0, static_cast<int>(myMesh->triangles.size()));
		propertySuite->propSetInt(&ofxMesh->properties, kOfxMeshPropConstantFaceSize, 0, 3);

		// Convert to attributes
		int attributeCount = ofxMesh->attributes.count();
		for (int i = 0; i < attributeCount; ++i) {
			auto& attribute = ofxMesh->attributes[i];
			if (attribute.attachment() == OpenMfx::AttributeAttachment::Point && attribute.name() == kOfxMeshAttribPointPosition) {
				attribute.setComponentCount(3);
				attribute.setType(OpenMfx::AttributeType::Float);
				attribute.setData((void*)myMesh->points.data());
				attribute.setByteStride(3 * sizeof(float));
			} else if (attribute.attachment() == OpenMfx::AttributeAttachment::Corner && attribute.name() == kOfxMeshAttribCornerPoint) {
				attribute.setComponentCount(1);
				attribute.setType(OpenMfx::AttributeType::Int);
				attribute.setData((void*)myMesh->triangles.data());
				attribute.setByteStride(3 * sizeof(float));
			} else if (attribute.attachment() == OpenMfx::AttributeAttachment::Face && attribute.name() == kOfxMeshAttribFaceSize) {
				attribute.setComponentCount(1);
				attribute.setType(OpenMfx::AttributeType::Int);
				attribute.setData(nullptr); // we use kOfxMeshPropConstantFaceSize instead
				attribute.setByteStride(0);
			}
		}
		
		return kOfxStatOK;
	}
	OfxStatus BeforeMeshRelease(OfxMeshHandle ofxMesh) override {
		MyMeshStruct* myMesh = nullptr;
		propertySuite->propGetPointer(&ofxMesh->properties, kOfxMeshPropInternalData, 0, (void**)&myMesh);

		if (myMesh == nullptr)
			return kOfxStatErrFatal;

		if (myMesh->isInput)
			return kOfxStatOK;

		int pointCount = 0;
		int faceCount = 0;
		int constantFaceSize = -1;
		propertySuite->propGetInt(&ofxMesh->properties, kOfxMeshPropPointCount, 0, &pointCount);
		propertySuite->propGetInt(&ofxMesh->properties, kOfxMeshPropFaceCount, 0, &faceCount);
		propertySuite->propGetInt(&ofxMesh->properties, kOfxMeshPropConstantFaceSize, 0, &constantFaceSize);

		if (constantFaceSize != 3)
			return kOfxStatErrUnsupported;

		myMesh->points.resize(pointCount);
		myMesh->triangles.resize(faceCount);

		// Convert from attributes
		int attributeCount = ofxMesh->attributes.count();
		for (int i = 0; i < attributeCount; ++i) {
			auto& attribute = ofxMesh->attributes[i];
			if (attribute.attachment() == OpenMfx::AttributeAttachment::Point && attribute.name() == kOfxMeshAttribPointPosition) {
				if (attribute.type() != OpenMfx::AttributeType::Float)
					return kOfxStatErrUnsupported;
				for (int j = 0; j < pointCount; ++j) {
					float* P = (float*)((char*)attribute.data() + attribute.byteStride() * j);
					for (int k = 0; k < 3; ++k) {
						myMesh->points[j][k] = P[k];
					}
				}
			}
			else if (attribute.attachment() == OpenMfx::AttributeAttachment::Corner && attribute.name() == kOfxMeshAttribCornerPoint) {
				if (attribute.type() != OpenMfx::AttributeType::Int)
					return kOfxStatErrUnsupported;
				for (int j = 0; j < faceCount; ++j) {
					for (int k = 0; k < 3; ++k) {
						int C = *(int*)((char*)attribute.data() + attribute.byteStride() * (3 * j + k));
						myMesh->triangles[j][k] = C;
					}
				}
			}
		}

		return kOfxStatOK;
	}
};

MyMeshStruct inputMeshData = {
	{
		{-1.0, -1.0, -1.0},
		{1.0, -1.0, -1.0},
		{-1.0, 1.0, -1.0},
		{1.0, 1.0, -1.0},
		{-1.0, -1.0, 1.0},
		{1.0, -1.0, 1.0},
		{-1.0, 1.0, 1.0},
		{1.0, 1.0, 1.0},
	},
	{
		{0, 2, 3}, {0, 3, 1},
		{4, 5, 7}, {4, 7, 6},
		{0, 1, 5}, {0, 5, 4},
		{1, 3, 7}, {1, 7, 5},
		{3, 2, 6}, {3, 6, 7},
		{2, 0, 4}, {2, 4, 6},
	},
};

void run(const char* filepath) {
	MyHost host;
	BinaryHandle effectLibrary;
	OfxPlugin *plugin;
	OfxMeshEffectHandle effectDescriptor;
	OfxMeshEffectHandle effectInstance;

	// Alias some host functions
	const auto& propSetPointer = host.propertySuite->propSetPointer;

	effectLibrary = binary_open(filepath);
	if (nullptr == effectLibrary) {
		throw std::exception("Could not load binary!");
	}

	int (*OfxGetNumberOfPlugins)(void) = (int(*)(void))binary_get_proc(effectLibrary, "OfxGetNumberOfPlugins");
	if (nullptr == OfxGetNumberOfPlugins) {
		throw "Could not find symbol 'OfxGetNumberOfPlugins'";
	}

	OfxPlugin* (*OfxGetPlugin)(int) = (OfxPlugin*(*)(int))binary_get_proc(effectLibrary, "OfxGetPlugin");
	if (nullptr == OfxGetPlugin) {
		throw "Could not find symbol 'OfxGetPlugin'";
	}

	if (OfxGetNumberOfPlugins() < 1) {
		throw "No plugin found in library";
	}

	plugin = OfxGetPlugin(0);
	if (0 != strcmp(plugin->pluginApi, kOfxMeshEffectPluginApi)) {
		throw "Plugin is not a Mesh Effect";
	}
	if (plugin->apiVersion != kOfxMeshEffectPluginApiVersion) {
		throw "Plugin uses a different version of the Mesh Effect API";
	}

	std::cout << "Using plugin '" << plugin->pluginIdentifier << "'" << std::endl;

	if (!host.LoadPlugin(plugin)) {
		throw std::exception("Could not load plugin!");
	}

	if (!host.GetDescriptor(plugin, effectDescriptor)) {
		throw std::exception("Could not get descriptor!");
	}

	if (!host.CreateInstance(effectDescriptor, effectInstance)) {
		throw std::exception("Could not create instance!");
	}

	MyMeshStruct outputMeshData;
	outputMeshData.isInput = false;

	int inputCount = effectInstance->inputs.count();
	std::cout << "Found " << inputCount << " inputs:" << std::endl;
	for (int i = 0; i < inputCount; ++i) {
		auto& input = effectInstance->inputs[i];
		std::cout << " - " << input.name() << std::endl;
		if (input.name() != kOfxMeshMainOutput) {
			// We provide a pointer to our own data structure but do convert to OpenMfx
			// yet because inputGetMesh might not be called. We will do it in
			// BeforeMeshGet instead.
			propSetPointer(&input.mesh.properties, kOfxMeshPropInternalData, 0, (void*)&inputMeshData);
		}
		else {
			propSetPointer(&input.mesh.properties, kOfxMeshPropInternalData, 0, (void*)&outputMeshData);
		}
	}

	int paramCount = effectInstance->parameters.count();
	std::cout << "Found " << paramCount << " parameters:" << std::endl;
	for (int i = 0; i < paramCount; ++i) {
		const auto& param = effectInstance->parameters[i];
		std::cout << " - " << param.name << std::endl;
	}

	host.Cook(effectInstance);

	std::cout << "Output mesh has:" << std::endl;
	std::cout << " - " << outputMeshData.points.size() << " points" << std::endl;
	std::cout << " - " << outputMeshData.triangles.size() << " triangles" << std::endl;

	host.DestroyInstance(effectInstance);

	host.ReleaseDescriptor(effectDescriptor);

	host.UnloadPlugin(plugin);

	binary_close(effectLibrary);
}

int main(int argc, char** argv) {
	const char* filepath = "../../c/plugins/Debug/OpenMfx_Example_C_Plugin_mirror.ofx";
	if (argc > 1) filepath = argv[1];

	try {
		run(filepath);
	}
	catch (std::exception err) {
		std::cerr << err.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
