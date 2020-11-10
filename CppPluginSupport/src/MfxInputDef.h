#pragma once

#include "MfxBase.h"


#include "ofxCore.h"
#include "ofxMeshEffect.h"

class MfxInputDef : public MfxBase
{
private:
	friend class MfxEffect;
	MfxInputDef(const MfxHost & host, OfxMeshInputHandle input, OfxPropertySetHandle properties);

public:
	MfxInputDef & Label(const char *label);
	MfxInputDef & RequestAttribute(const char* attachment, const char* name, int componentCount, const char* type, const char* semantic, int mandatory);

private:
	OfxMeshInputHandle m_input;
	OfxPropertySetHandle m_properties;
};

