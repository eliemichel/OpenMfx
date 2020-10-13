#pragma once

#include "MfxBase.h"

#include "ofxCore.h"
#include "ofxMeshEffect.h"

template <typename T>
class MfxParamDef : public MfxBase
{
private:
	friend class MfxEffect;
	MfxParamDef(const MfxHost& host, OfxPropertySetHandle properties);

public:
	MfxParamDef & Label(const char *label);
	MfxParamDef & Range(const T & minimum, const T & maximum);

private:
	OfxPropertySetHandle m_properties;
};

