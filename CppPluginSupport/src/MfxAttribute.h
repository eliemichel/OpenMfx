#pragma once

#include "MfxBase.h"
#include "MfxAttributeProps.h"

#include "ofxCore.h"
#include "ofxMeshEffect.h"

struct MfxAttribute : public MfxBase
{
private:
	friend class MfxMesh;
	friend class MfxInputDef;
	MfxAttribute(const MfxHost& host, OfxPropertySetHandle properties);

	/**
	 * Convert a type string from MeshEffect API to its local enum counterpart
	 */
	static MfxAttributeType mfxAttrTypeAsEnum(const char* mfxType);

    /**
     * Convert attribute attachment string from MeshEffect API to its local enum counterpart
     */
    static MfxAttributeAttachment mfxAttrAttachmentAsEnum(const char* mfxAttachment);

    /**
	 * Convert attribute semantic string from MeshEffect API to its local enum counterpart
	 */
    static MfxAttributeSemantic mfxAttrSemanticAsEnum(const char* mfxSemantic);

    /**
     * Convert local typestring enum to a type string from MeshEffect API
     */
    static const char* mfxAttrTypeAsString(MfxAttributeType mfxType);

    /**
     * Convert local attachment enum to an attachment string from MeshEffect API
     */
    static const char* mfxAttrAttachmentAsString(MfxAttributeAttachment mfxAttachment);

    /**
     * Convert local semantic enum to a semantic string from MeshEffect API
     */
    static const char* mfxAttrSemanticAsString(MfxAttributeSemantic mfxSemantic);

	/**
	 * Copy attribute and try to cast. If number of component is different,
	 * copy the common components only.
	 */
	static OfxStatus copyAttributeData(MfxAttributeProps & destination, const MfxAttributeProps & source, int start, int count);

public:
	/**
	 * Populate the provided props structure with this attribute's properties
	 */
	void FetchProperties(MfxAttributeProps & props);

    /**
     * Set attribute properties according to provided props structure
     */
    void SetProperties(const MfxAttributeProps & props);

    /**
     * Copy attribute data, casting if necessary
     */
	void CopyFrom(MfxAttribute& other, int start, int count);

    /**
     * Forward attribute data, pointing to existing buffers instead of copying.
     * Note that the buffer in source attribute must already be allocated.
     */
    void ForwardFrom(MfxAttribute& other);

private:
	OfxPropertySetHandle m_properties;
};
