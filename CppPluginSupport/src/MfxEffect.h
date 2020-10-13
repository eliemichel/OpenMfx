#pragma once

#include "MfxInputDef.h"
#include "MfxParamDef.h"
#include "MfxInput.h"
#include "MfxParam.h"
#include "MfxHost.h"
#include "macros.h"

#include "ofxCore.h"
#include "ofxMeshEffect.h"

#include <array>

class MfxEffect
{
public:
	// Override this in subclasses to give the effect a name
	virtual const char* GetName()
	{ return "MfxEffect"; }

	void SetHost(OfxHost* host);

	OfxStatus MainEntry(const char *action,
                        const void *handle,
                        OfxPropertySetHandle inArgs,
                        OfxPropertySetHandle outArgs);

protected:
	// Actions, to be defined in subclasses

	virtual OfxStatus Load()
	{ return kOfxStatOK; }

	virtual OfxStatus Unload()
	{ return kOfxStatOK; }

	virtual OfxStatus Describe(OfxMeshEffectHandle descriptor)
	{ return kOfxStatOK; }

	virtual OfxStatus CreateInstance(OfxMeshEffectHandle instance)
	{ return kOfxStatOK; }

	virtual OfxStatus DestroyInstance(OfxMeshEffectHandle instance)
	{ return kOfxStatOK; }

	virtual OfxStatus Cook(OfxMeshEffectHandle instance)
	{ return kOfxStatOK; }

protected:
	// Utility methods to be used during the Describe() action only:

	MfxInputDef AddInput(const char *name);

	MfxParamDef<int> AddParam(const char *name, int defaultValue);
	MfxParamDef<int2> AddParam(const char *name, const int2 & defaultValue);
	MfxParamDef<int3> AddParam(const char *name, const int3 & defaultValue);
	MfxParamDef<double> AddParam(const char *name, double defaultValue);
	MfxParamDef<double2> AddParam(const char *name, const double2 & defaultValue);
	MfxParamDef<double3> AddParam(const char *name, const double3 & defaultValue);
	MfxParamDef<bool> AddParam(const char* name, bool defaultValue);

protected:
	// Utility methods to be used during the Cook() action only:

	MfxInput GetInput(const char* name);

	template <typename T>
	MfxParam<T> GetParam(const char* name);

private:
	/**
	 * Check that common suites are available
	 */
	bool CheckSuites();

	/**
	 * Cache the current descriptor and its parameter set to avoid providing
	 * it to each call to AddInput and AddParameter while describing the effect
	 * in the Describe() action.
	 */
	void SetupDescribe(OfxMeshEffectHandle descriptor);

	/**
	 * Cache the current instance and its parameter set to avoid providing
	 * it to each call to GetInput and GetParameter while cooking the effect
	 * in the Cook() action.
	 */
	void SetupCook(OfxMeshEffectHandle instance);

protected:
	const MfxHost & host() const { return m_host; }

	// Access to raw Open Mesh Effect suites, might be used when implementing actions
	// (these member variables are not prefixed by 'm_' for more convenience)
	const OfxMeshEffectSuiteV1 *meshEffectSuite = nullptr;
    const OfxPropertySuiteV1 *propertySuite = nullptr;
    const OfxParameterSuiteV1 *parameterSuite = nullptr;

private:
	MfxHost m_host;

	// Valid only during Describe()
	OfxMeshEffectHandle m_descriptor = nullptr;
	// Valid only during Cook()
	OfxMeshEffectHandle m_instance = nullptr;
	// Valid only during Describe() and Cook()
	OfxParamSetHandle m_parameters = nullptr;
};
