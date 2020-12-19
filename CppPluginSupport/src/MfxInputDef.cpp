#include "MfxInputDef.h"
#include "macros.h"

MfxInputDef::MfxInputDef(const MfxHost& host, OfxMeshInputHandle input, OfxPropertySetHandle properties)
	: MfxBase(host)
	, m_input(input)
	, m_properties(properties)
{}

//-----------------------------------------------------------------------------

MfxInputDef & MfxInputDef::Label(const char *label)
{
	MFX_ENSURE(propertySuite->propSetString(m_properties, kOfxPropLabel, 0, label));
	return *this;
}

MfxInputDef& MfxInputDef::RequestAttribute(const char* attachment, const char* name, int componentCount, const char* type, const char* semantic, bool mandatory)
{
	MFX_ENSURE(meshEffectSuite->inputRequestAttribute(m_input, attachment, name, componentCount, type, semantic, mandatory));
	return *this;
}

MfxInputDef& MfxInputDef::RequestPointAttribute(const char* name, int componentCount, const char* type, const char* semantic, bool mandatory)
{
	return RequestAttribute(kOfxMeshAttribPoint, name, componentCount, type, semantic, mandatory);
}

MfxInputDef& MfxInputDef::RequestVertexAttribute(const char* name, int componentCount, const char* type, const char* semantic, bool mandatory)
{
	return RequestAttribute(kOfxMeshAttribVertex, name, componentCount, type, semantic, mandatory);
}

MfxInputDef& MfxInputDef::RequestFaceAttribute(const char* name, int componentCount, const char* type, const char* semantic, bool mandatory)
{
	return RequestAttribute(kOfxMeshAttribFace, name, componentCount, type, semantic, mandatory);
}

MfxInputDef& MfxInputDef::RequestMeshAttribute(const char* name, int componentCount, const char* type, const char* semantic, bool mandatory)
{
	return RequestAttribute(kOfxMeshAttribMesh, name, componentCount, type, semantic, mandatory);
}
