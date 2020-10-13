#pragma once

#include "MfxBase.h"
#include "MfxAttributeProps.h"

#include "ofxCore.h"
#include "ofxMeshEffect.h"

struct MfxAttribute : public MfxBase
{
private:
	friend class MfxMesh;
	MfxAttribute(const MfxHost& host, OfxPropertySetHandle properties);

	/**
	 * Convert a type string from MeshEffect API to its local enum counterpart
	 */
	static MfxAttributeType mfxAttrAsEnum(const char* mfxType);
	/**
	 * Copy attribute and try to cast. If number of component is different,
	 * copy the common components only.
	 */
	static OfxStatus copyAttributeData(MfxAttributeProps & destination, const MfxAttributeProps & source, int start, int count);

public:
	/**
	 * Populate the provided props structure woth this attribute's properties
	 */
	void FetchProperties(MfxAttributeProps & props);

	void CopyFrom(MfxAttribute& other, int start, int count);

private:
	OfxPropertySetHandle m_properties;
};

