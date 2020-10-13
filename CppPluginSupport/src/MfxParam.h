#pragma once

#include "MfxBase.h"

#include "ofxCore.h"
#include "ofxMeshEffect.h"

template <typename T>
class MfxParam : public MfxBase
{
private:
	friend class MfxEffect;
	MfxParam(const MfxHost & host, OfxParamHandle param);

public:
	T GetValue();

private:
	OfxParamHandle m_param;
};

