#pragma once

#include "MfxBase.h"


#include "ofxCore.h"
#include "ofxMeshEffect.h"

class MfxInputDef : public MfxBase
{
private:
	friend class MfxEffect;
	MfxInputDef(const MfxHost & host, OfxPropertySetHandle properties);

public:
	MfxInputDef & Label(const char *label);

private:
	OfxPropertySetHandle m_properties;
};

