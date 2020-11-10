#include "MfxMesh.h"
#include "macros.h"

MfxMesh::MfxMesh(const MfxHost& host, OfxMeshHandle mesh, OfxPropertySetHandle properties)
	: MfxBase(host)
	, m_mesh(mesh)
	, m_properties(properties)
{}

//-----------------------------------------------------------------------------

void MfxMesh::FetchProperties(MfxMeshProps& props)
{
	int noLooseEdge;

    MFX_ENSURE(propertySuite->propGetInt(m_properties, kOfxMeshPropPointCount, 0, &props.pointCount));
	MFX_ENSURE(propertySuite->propGetInt(m_properties, kOfxMeshPropVertexCount, 0, &props.vertexCount));
    MFX_ENSURE(propertySuite->propGetInt(m_properties, kOfxMeshPropFaceCount, 0, &props.faceCount));
    MFX_ENSURE(propertySuite->propGetInt(m_properties, kOfxMeshPropNoLooseEdge, 0, &noLooseEdge));
    MFX_ENSURE(propertySuite->propGetInt(m_properties, kOfxMeshPropConstantFaceCount, 0, &props.constantFaceCount));

    props.noLooseEdge = (bool)noLooseEdge;
}

MfxAttribute MfxMesh::GetAttribute(const char* attachment, const char* name)
{
	OfxPropertySetHandle attribute;
	MFX_ENSURE(meshEffectSuite->meshGetAttribute(m_mesh, attachment, name, &attribute));
	return MfxAttribute(host(), attribute);
}

MfxAttribute MfxMesh::GetPointAttribute(const char* name)
{
	return GetAttribute(kOfxMeshAttribPoint, name);
}

MfxAttribute MfxMesh::GetVertexAttribute(const char* name)
{
	return GetAttribute(kOfxMeshAttribVertex, name);
}

MfxAttribute MfxMesh::GetFaceAttribute(const char* name)
{
	return GetAttribute(kOfxMeshAttribFace, name);
}

MfxAttribute MfxMesh::GetMeshAttribute(const char* name)
{
	return GetAttribute(kOfxMeshAttribMesh, name);
}

bool MfxMesh::HasAttribute(const char* attachment, const char* name)
{
    OfxPropertySetHandle attribute;
    OfxStatus status = this->host().meshEffectSuite->meshGetAttribute(m_mesh, attachment, name, &attribute);

    if (kOfxStatOK == status) {
        return true;
    } else if (kOfxStatErrBadIndex == status) {
        return false;
    } else {
        throw MfxSuiteException(status, "meshEffectSuite->meshGetAttribute(m_mesh, attachment, name, &attribute)");
    }
}

bool MfxMesh::HasPointAttribute(const char* name)
{
    return HasAttribute(kOfxMeshAttribPoint, name);
}

bool MfxMesh::HasVertexAttribute(const char* name)
{
    return HasAttribute(kOfxMeshAttribVertex, name);
}

bool MfxMesh::HasFaceAttribute(const char* name)
{
    return HasAttribute(kOfxMeshAttribFace, name);
}

bool MfxMesh::HasMeshAttribute(const char* name)
{
    return HasAttribute(kOfxMeshAttribMesh, name);
}

void MfxMesh::Release()
{
	MFX_ENSURE(meshEffectSuite->inputReleaseMesh(m_mesh));
}

//-----------------------------------------------------------------------------

MfxAttribute MfxMesh::AddAttribute(const char* attachment, const char* name, int componentCount, const char* type, const char* semantic)
{
	OfxPropertySetHandle attribute;
	MFX_ENSURE(meshEffectSuite->attributeDefine(m_mesh, attachment, name, componentCount, type, semantic, &attribute));
	MFX_ENSURE(propertySuite->propSetInt(attribute, kOfxMeshAttribPropIsOwner, 0, 1));
	return MfxAttribute(host(), attribute);
}

MfxAttribute MfxMesh::AddPointAttribute(const char* name, int componentCount, const char* type, const char* semantic)
{
	return AddAttribute(kOfxMeshAttribPoint, name, componentCount, type, semantic);
}

MfxAttribute MfxMesh::AddVertexAttribute(const char* name, int componentCount, const char* type, const char* semantic)
{
	return AddAttribute(kOfxMeshAttribVertex, name, componentCount, type, semantic);
}

MfxAttribute MfxMesh::AddFaceAttribute(const char* name, int componentCount, const char* type, const char* semantic)
{
	return AddAttribute(kOfxMeshAttribFace, name, componentCount, type, semantic);
}

MfxAttribute MfxMesh::AddMeshAttribute(const char* name, int componentCount, const char* type, const char* semantic)
{
	return AddAttribute(kOfxMeshAttribMesh, name, componentCount, type, semantic);
}

void MfxMesh::Allocate(int pointCount, int vertCount, int faceCount, bool noLooseEdge, int constantFaceCount)
{
	MFX_ENSURE(propertySuite->propSetInt(m_properties, kOfxMeshPropPointCount, 0, pointCount));
	MFX_ENSURE(propertySuite->propSetInt(m_properties, kOfxMeshPropVertexCount, 0, vertCount));
    MFX_ENSURE(propertySuite->propSetInt(m_properties, kOfxMeshPropFaceCount, 0, faceCount));
    MFX_ENSURE(propertySuite->propSetInt(m_properties, kOfxMeshPropNoLooseEdge, 0, (int)noLooseEdge));
    MFX_ENSURE(propertySuite->propSetInt(m_properties, kOfxMeshPropConstantFaceCount, 0, constantFaceCount));
	MFX_ENSURE(meshEffectSuite->meshAlloc(m_mesh));
}
