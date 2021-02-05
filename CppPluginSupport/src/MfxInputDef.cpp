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

MfxInputDef& MfxInputDef::RequestAttribute(MfxAttributeAttachment attachment, const char *name, int componentCount, MfxAttributeType type, MfxAttributeSemantic semantic, bool mandatory) {
    return RequestAttribute(MfxAttribute::mfxAttrAttachmentAsString(attachment),
                            name,
                            componentCount,
                            MfxAttribute::mfxAttrTypeAsString(type),
                            MfxAttribute::mfxAttrSemanticAsString(semantic),
                            mandatory);
}

MfxInputDef& MfxInputDef::RequestPointAttribute(const char *name, int componentCount, MfxAttributeType type, MfxAttributeSemantic semantic, bool mandatory) {
    return RequestAttribute(MfxAttributeAttachment::Point, name, componentCount, type, semantic, mandatory);
}

MfxInputDef& MfxInputDef::RequestVertexAttribute(const char *name, int componentCount, MfxAttributeType type, MfxAttributeSemantic semantic, bool mandatory) {
    return RequestAttribute(MfxAttributeAttachment::Vertex, name, componentCount, type, semantic, mandatory);;
}

MfxInputDef& MfxInputDef::RequestFaceAttribute(const char *name, int componentCount, MfxAttributeType type, MfxAttributeSemantic semantic, bool mandatory) {
    return RequestAttribute(MfxAttributeAttachment::Face, name, componentCount, type, semantic, mandatory);;
}

MfxInputDef& MfxInputDef::RequestMeshAttribute(const char *name, int componentCount, MfxAttributeType type, MfxAttributeSemantic semantic, bool mandatory) {
    return RequestAttribute(MfxAttributeAttachment::Mesh, name, componentCount, type, semantic, mandatory);;
}

MfxInputDef& MfxInputDef::RequestGeometry(bool request)
{
	MFX_ENSURE(propertySuite->propSetInt(m_properties, kOfxInputPropRequestGeometry, 0, request ? 1 : 0));
	return *this;
}

MfxInputDef& MfxInputDef::RequestTransform(bool request)
{
	MFX_ENSURE(propertySuite->propSetInt(m_properties, kOfxInputPropRequestTransform, 0, request ? 1 : 0));
	return *this;
}

