#pragma once

#include "MfxMesh.h"
#include "MfxBase.h"

#include "ofxCore.h"
#include "ofxMeshEffect.h"

class MfxInput : public MfxBase
{
private:
	friend class MfxEffect;
	MfxInput(const MfxHost& host, OfxMeshInputHandle input);

public:
	MfxMesh GetMesh();

private:
	OfxMeshInputHandle m_input;
};

