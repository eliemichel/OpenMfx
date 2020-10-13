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
	MFX_ENSURE(propertySuite->propGetInt(m_properties, kOfxMeshPropPointCount, 0, &props.pointCount));
	MFX_ENSURE(propertySuite->propGetInt(m_properties, kOfxMeshPropVertexCount, 0, &props.vertexCount));
	MFX_ENSURE(propertySuite->propGetInt(m_properties, kOfxMeshPropFaceCount, 0, &props.faceCount));
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

void MfxMesh::Release()
{
	MFX_ENSURE(meshEffectSuite->inputReleaseMesh(m_mesh));
}

//-----------------------------------------------------------------------------

MfxAttribute MfxMesh::AddAttribute(const char* attachment, const char* name, int componentCount, const char* type)
{
	OfxPropertySetHandle attribute;
	MFX_ENSURE(meshEffectSuite->attributeDefine(m_mesh, attachment, name, componentCount, type, &attribute));
	MFX_ENSURE(propertySuite->propSetInt(attribute, kOfxMeshAttribPropIsOwner, 0, 1));
	return MfxAttribute(host(), attribute);
}

MfxAttribute MfxMesh::AddPointAttribute(const char* name, int componentCount, const char* type)
{
	return AddAttribute(kOfxMeshAttribPoint, name, componentCount, type);
}

MfxAttribute MfxMesh::AddVertexAttribute(const char* name, int componentCount, const char* type)
{
	return AddAttribute(kOfxMeshAttribVertex, name, componentCount, type);
}

MfxAttribute MfxMesh::AddFaceAttribute(const char* name, int componentCount, const char* type)
{
	return AddAttribute(kOfxMeshAttribFace, name, componentCount, type);
}

MfxAttribute MfxMesh::AddMeshAttribute(const char* name, int componentCount, const char* type)
{
	return AddAttribute(kOfxMeshAttribMesh, name, componentCount, type);
}

void MfxMesh::Allocate(int pointCount, int vertCount, int faceCount)
{
	MFX_ENSURE(propertySuite->propSetInt(m_properties, kOfxMeshPropPointCount, 0, pointCount));
	MFX_ENSURE(propertySuite->propSetInt(m_properties, kOfxMeshPropVertexCount, 0, vertCount));
	MFX_ENSURE(propertySuite->propSetInt(m_properties, kOfxMeshPropFaceCount, 0, faceCount));
	MFX_ENSURE(meshEffectSuite->meshAlloc(m_mesh));
}
