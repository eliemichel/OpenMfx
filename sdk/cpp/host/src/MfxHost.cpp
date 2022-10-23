#include "MfxHost.h"

#include "mesheffect.h"
#include "properties.h"

#include "parameterSuite.h"
#include "propertySuite.h"
#include "meshEffectSuite.h"
#include "messageSuite.h"

#include "util/ofx_util.h"
#include "ofxExtras.h"
#include "Logger.h"

#include <cstring>

using namespace OpenMfx;

// ----------------------------------------------------
// Static constructor

MfxHost* MfxHost::FromOfxHost(OfxHost* ofxHost)
{
	int i = ofxHost->host->find(kOfxMeshPropHostHandle);
	if (i == -1) {
		return nullptr;
	}
	void* ptr = (*ofxHost->host)[i].value[0].as_pointer;
	return reinterpret_cast<MfxHost*>(ptr);
}

// ----------------------------------------------------
// Base methods

MfxHost::MfxHost()
{
	OfxPropertySetHandle props = new OfxPropertySetStruct(PropertySetContext::Host);
	m_host.host = props;
	m_host.fetchSuite = FetchSuite;

	// TODO: fetch suites only when they are actually needed? This has low overhead though.
	propertySuite = (const OfxPropertySuiteV1*)FetchSuite(props, kOfxPropertySuite, 1);
	parameterSuite = (const OfxParameterSuiteV1*)FetchSuite(props, kOfxParameterSuite, 1);
	messageSuite = (const OfxMessageSuiteV2*)FetchSuite(props, kOfxMessageSuite, 2);
	meshEffectSuite = (const OfxMeshEffectSuiteV1*)FetchSuite(props, kOfxMeshEffectSuite, 1);

	propertySuite->propSetPointer(props, kOfxHostPropBeforeMeshGetCb, 0, (void**)&BeforeMeshGetCb);
	propertySuite->propSetPointer(props, kOfxHostPropBeforeMeshReleaseCb, 0, (void**)&BeforeMeshReleaseCb);
	propertySuite->propSetPointer(props, kOfxHostPropBeforeMeshAllocateCb, 0, (void**)&BeforeMeshAllocateCb);
	propertySuite->propSetPointer(props, kOfxMeshPropHostHandle, 0, (void**)this);
}

MfxHost::~MfxHost()
{
	delete m_host.host;
}

// ----------------------------------------------------
// Utility wrappers around plugin->mainEntry

bool MfxHost::LoadPlugin(OfxPlugin* plugin) {
	OfxStatus status;

	plugin->setHost(RawHost());

	status = plugin->mainEntry(kOfxActionLoad, NULL, NULL, NULL);
	LOG << kOfxActionLoad << " action returned status " << status << "(" << getOfxStatusName(status) << ")";

	switch (status) {
	case kOfxStatReplyDefault:
		WARN_LOG << "The plugin " << plugin->pluginIdentifier << " ignored load action.";
		return true;

	case kOfxStatFailed:
		ERR_LOG << "The load action failed, no further actions will be passed to the plug-in '" << plugin->pluginIdentifier << "'.";
		return false;

	case kOfxStatErrFatal:
		ERR_LOG << "Fatal error while loading the plug-in '" << plugin->pluginIdentifier << "'.";
		return false;

	default:
		return true;
	}
}


void MfxHost::UnloadPlugin(OfxPlugin* plugin) {
	OfxStatus status;

	status = plugin->mainEntry(kOfxActionUnload, NULL, NULL, NULL);
	LOG << kOfxActionUnload << " action returned status " << status << "(" << getOfxStatusName(status) << ")";

	switch (status) {
	case kOfxStatReplyDefault:
		WARN_LOG << "The plugin " << plugin->pluginIdentifier << " ignored unload action.";
		break;

	case kOfxStatErrFatal:
		ERR_LOG << "Fatal error while unloading the plug-in '" << plugin->pluginIdentifier << "'.";
		break;
	}

	plugin->setHost(NULL);
}

bool MfxHost::GetDescriptor(OfxPlugin* plugin, OfxMeshEffectHandle & effectDescriptor)
{
	OfxStatus status;
	OfxMeshEffectHandle effectHandle;

	effectDescriptor = NULL;
	effectHandle = new OfxMeshEffectStruct(RawHost(), plugin);

	status = plugin->mainEntry(kOfxActionDescribe, effectHandle, NULL, NULL);
	LOG << kOfxActionDescribe << " action returned status " << status << "(" << getOfxStatusName(status) << ")";

	switch (status) {
	case kOfxStatErrMissingHostFeature:
		ERR_LOG << "The plugin '" << plugin->pluginIdentifier << "' lacks some host feature.";
		break;

	case kOfxStatErrMemory:
		ERR_LOG << "Not enough memory for plug-in '" << plugin->pluginIdentifier << "'";
		break;

	case kOfxStatFailed:
		ERR_LOG << "Error while describing plug-in '" << plugin->pluginIdentifier << "'";
		break;

	case kOfxStatErrFatal:
		ERR_LOG << "Fatal error while describing plug-in '" << plugin->pluginIdentifier << "'";
		break;

	default:
		effectDescriptor = effectHandle;
		break;
	}

	if (NULL == effectDescriptor) {
		delete effectHandle;
		return false;
	}
	return true;
}

void MfxHost::ReleaseDescriptor(OfxMeshEffectHandle effectDescriptor)
{
	delete effectDescriptor;
}


bool MfxHost::CreateInstance(OfxMeshEffectHandle effectDescriptor, OfxMeshEffectHandle & effectInstance)
{
	OfxStatus status;
	OfxMeshEffectHandle instance;
	OfxPlugin* plugin = effectDescriptor->plugin;

	effectInstance = NULL;

	instance = new OfxMeshEffectStruct(effectDescriptor->host, plugin);
	instance->deep_copy_from(*effectDescriptor);

	// Set default values to parameters
	for (int i = 0; i < instance->parameters.count(); ++i) {
		OfxParamStruct& param = instance->parameters[i];
		OfxPropertySetStruct& props = param.properties;
		int default_idx = props.find(kOfxParamPropDefault);
		if (default_idx > -1) {
			memcpy(param.value, props[default_idx].value, 4 * sizeof(OfxParamValueStruct));
		}
	}

	status = plugin->mainEntry(kOfxActionCreateInstance, instance, NULL, NULL);
	LOG << kOfxActionCreateInstance << " action returned status " << status << "(" << getOfxStatusName(status) << ")";

	switch (status) {
	case kOfxStatErrMemory:
		ERR_LOG << "Not enough memory for plug-in '" << plugin->pluginIdentifier << "'";
		break;

	case kOfxStatFailed:
		ERR_LOG << "Error while creating an instance of plug-in '" << plugin->pluginIdentifier << "'";
		break;

	case kOfxStatErrFatal:
		ERR_LOG << "Fatal error while creating an instance of plug-in '" << plugin->pluginIdentifier << "'";
		break;

	default:
		effectInstance = instance;
		break;
	}
	
	if (NULL == effectInstance) {
		delete instance;
		return false;
	}

	// Init inputs
	for (int i = 0; i < instance->inputs.count(); ++i) {
		InitInput(instance->inputs[i]);
	}

	return true;
}

void MfxHost::DestroyInstance(OfxMeshEffectHandle effectInstance) {
	OfxStatus status;
	OfxPlugin* plugin = effectInstance->plugin;

	status = plugin->mainEntry(kOfxActionDestroyInstance, effectInstance, NULL, NULL);
	LOG << kOfxActionDestroyInstance << " action returned status " << status << "(" << getOfxStatusName(status) << ")";

	switch (status) {
	case kOfxStatFailed:
		ERR_LOG << "Error while destroying an instance of plug-in '" << plugin->pluginIdentifier << "'";
		break;

	case kOfxStatErrFatal:
		ERR_LOG << "Fatal error while destroying an instance of plug-in '" << plugin->pluginIdentifier << "'";
		break;
	}

	delete effectInstance;
}

bool MfxHost::IsIdentity(OfxMeshEffectHandle effectInstance, bool* isIdentity, char** inputToPassThrough) {
	OfxStatus status;
	OfxPlugin* plugin = effectInstance->plugin;

	OfxPropertySetStruct inArgs(PropertySetContext::ActionIdentityIn);
	OfxPropertySetStruct outArgs(PropertySetContext::ActionIdentityOut);

	propertySuite->propSetInt(&inArgs, kOfxPropTime, 0, 0);
	propertySuite->propSetString(&outArgs, kOfxPropName, 0, "");
	propertySuite->propSetInt(&outArgs, kOfxPropTime, 0, 0);

	*isIdentity = false;

	status = plugin->mainEntry(kOfxMeshEffectActionIsIdentity, effectInstance, &inArgs, &outArgs);
	LOG << kOfxMeshEffectActionIsIdentity << " action returned status " << status << "(" << getOfxStatusName(status) << ")";

	switch (status) {
	case kOfxStatErrMemory:
		ERR_LOG << "Not enough memory for plug-in '" << plugin->pluginIdentifier << "'";
		return false;

	case kOfxStatFailed:
		ERR_LOG << "Error while checking for identity in an instance of plug-in '" << plugin->pluginIdentifier << "'";
		return false;

	case kOfxStatErrFatal:
		ERR_LOG << "Fatal error while checking for identity an instance of plug-in '" << plugin->pluginIdentifier << "'";
		return false;

	case kOfxStatOK:
		*isIdentity = true;
		if (nullptr != inputToPassThrough) {
			propertySuite->propGetString(&outArgs, kOfxPropName, 0, inputToPassThrough);
		}
		return true;

	default:
		return true;
	}
}

bool MfxHost::Cook(OfxMeshEffectHandle effectInstance) {
	OfxStatus status;
	OfxPlugin* plugin = effectInstance->plugin;

	status = plugin->mainEntry(kOfxMeshEffectActionCook, effectInstance, NULL, NULL);
	LOG << kOfxMeshEffectActionCook << " action returned status " << status << "(" << getOfxStatusName(status) << ")";

	switch (status) {
	case kOfxStatErrMemory:
		ERR_LOG << "Not enough memory for cooking an instance of plug-in '" << plugin->pluginIdentifier << "'";
		return false;

	case kOfxStatFailed:
		ERR_LOG << "Error while cooking an instance of plug-in '" << plugin->pluginIdentifier << "'";
		return false;

	case kOfxStatErrFatal:
		ERR_LOG << "Fatal error while cooking an instance of plug-in '" << plugin->pluginIdentifier << "'";
		return false;
	}

	return true;
}

// ----------------------------------------------------
// Static callbacks

OfxStatus MfxHost::BeforeMeshGetCb(OfxHost* ofxHost, OfxMeshHandle ofxMesh)
{
	MfxHost* mfxHost = MfxHost::FromOfxHost(ofxHost);
	if (nullptr == mfxHost) {
		return kOfxStatErrFatal;
	}
	else {
		return mfxHost->BeforeMeshGet(ofxMesh);
	}
}

OfxStatus MfxHost::BeforeMeshReleaseCb(OfxHost* ofxHost, OfxMeshHandle ofxMesh)
{
	MfxHost *mfxHost = MfxHost::FromOfxHost(ofxHost);
	if (nullptr == mfxHost) {
		return kOfxStatErrFatal;
	}
	else {
		return mfxHost->BeforeMeshRelease(ofxMesh);
	}
}

OfxStatus MfxHost::BeforeMeshAllocateCb(OfxHost *ofxHost, OfxMeshHandle ofxMesh)
{
	MfxHost *mfxHost = MfxHost::FromOfxHost(ofxHost);
	if (nullptr == mfxHost) {
		return kOfxStatErrFatal;
	}
	else {
		return mfxHost->BeforeMeshAllocate(ofxMesh);
	}
}

const void* MfxHost::FetchSuite(OfxPropertySetHandle host, const char* suiteName, int suiteVersion)
{
	if (0 == strcmp(suiteName, kOfxMeshEffectSuite) && suiteVersion == 1) {
		switch (suiteVersion) {
		case 1:
			return &gMeshEffectSuiteV1;
		default:
			ERR_LOG << "Suite '" << suiteName << "' is only supported in version 1.";
			return NULL;
		}
	}
	if (0 == strcmp(suiteName, kOfxParameterSuite) && suiteVersion == 1) {
		switch (suiteVersion) {
		case 1:
			return &gParameterSuiteV1;
		default:
			ERR_LOG << "Suite '" << suiteName << "' is only supported in version 1.";
			return NULL;
		}
	}
	if (0 == strcmp(suiteName, kOfxPropertySuite) && suiteVersion == 1) {
		switch (suiteVersion) {
		case 1:
			return &gPropertySuiteV1;
		default:
			ERR_LOG << "Suite '" << suiteName << "' is only supported in version 1.";
			return NULL;
		}
	}
	if (0 == strcmp(suiteName, kOfxMessageSuite) && suiteVersion <= 2) {
		switch (suiteVersion) {
		case 1: // V2 is backward compatible
		case 2:
			return &gMessageSuiteV2;
		default:
			ERR_LOG << "Suite '" << suiteName << "' is only supported in version 1.";
			return NULL;
		}
	}

	ERR_LOG << "Suite '" << suiteName << "' is not supported by this host.";
	return NULL;
}
