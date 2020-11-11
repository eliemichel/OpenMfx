#pragma once

#include "MfxBase.h"


#include "ofxCore.h"
#include "ofxMeshEffect.h"

/**
 * An input definition is manipulated during the \ref MfxEffect::Describe
 * action to tell the host what is expected to flow through the input at
 * cook time. It differs from \ref MfxInput that is the input instance during
 * the cooking, in particular the input definition does not contain any mesh.
 */
class MfxInputDef : public MfxBase
{
private:
	friend class MfxEffect;
	MfxInputDef(const MfxHost & host, OfxMeshInputHandle input, OfxPropertySetHandle properties);

public:
	/**
	 * Define the human readable label to display next to this input
	 * (in hosts supporting it).
	 */
	MfxInputDef & Label(const char *label);

	/**
	 * Notify the host that the effect requires (if \e mandatory is true)
	 * or would make good use of a given attribute. If the attribute is
	 * mandatory, it is ensured to be present with at least \e componentCount
	 * components of the requested type. If not mandatory, it is the
	 * responsibility of this effect to check at cook time whether the attribute
	 * exist or not and whether it has enough components and the right type.
	 * 
	 * The semantics can be used to tell the intended use of the of the attribute
	 * to help the host suggest some attributes to send to the effect to the user.
	 * Possible values are \ref kOfxMeshAttribSemanticTextureCoordinate,
	 * \ref kOfxMeshAttribSemanticNormal, \ref kOfxMeshAttribSemanticColor
	 * or \ref kOfxMeshAttribSemanticWeight. It may also just be null.
	 */
	MfxInputDef & RequestAttribute(const char* attachment, const char* name, int componentCount, const char* type, const char* semantic, bool mandatory);

private:
	OfxMeshInputHandle m_input;
	OfxPropertySetHandle m_properties;
};

