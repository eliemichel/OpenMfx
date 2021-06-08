#include "MfxMesh.h"
#include "macros.h"

MfxMesh::MfxMesh(const MfxHost& host, OfxMeshHandle mesh, OfxPropertySetHandle properties)
	: MfxBase(host)
	, m_mesh(mesh)
	, m_properties(properties)
{}

//-----------------------------------------------------------------------------

bool MfxMesh::IsValid() const
{
	return NULL != m_mesh;
}

void MfxMesh::FetchProperties(MfxMeshProps& props)
{
	int noLooseEdge;

    MFX_ENSURE(propertySuite->propGetInt(m_properties, kOfxMeshPropPointCount, 0, &props.pointCount));
	MFX_ENSURE(propertySuite->propGetInt(m_properties, kOfxMeshPropCornerCount, 0, &props.cornerCount));
    MFX_ENSURE(propertySuite->propGetInt(m_properties, kOfxMeshPropFaceCount, 0, &props.faceCount));
    MFX_ENSURE(propertySuite->propGetInt(m_properties, kOfxMeshPropNoLooseEdge, 0, &noLooseEdge));
    MFX_ENSURE(propertySuite->propGetInt(m_properties, kOfxMeshPropConstantFaceSize, 0, &props.constantFaceSize));
    MFX_ENSURE(propertySuite->propGetInt(m_properties, kOfxMeshPropAttributeCount, 0, &props.attributeCount));

    props.noLooseEdge = (bool)noLooseEdge;
}

void MfxMesh::FetchTransform(double** matrix)
{
	MFX_ENSURE(propertySuite->propGetPointer(m_properties, kOfxMeshPropTransformMatrix, 0, (void**)matrix));
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

MfxAttribute MfxMesh::GetCornerAttribute(const char* name)
{
	return GetAttribute(kOfxMeshAttribCorner, name);
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

bool MfxMesh::HasCornerAttribute(const char* name)
{
    return HasAttribute(kOfxMeshAttribCorner, name);
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

MfxAttribute MfxMesh::AddCornerAttribute(const char* name, int componentCount, const char* type, const char* semantic)
{
	return AddAttribute(kOfxMeshAttribCorner, name, componentCount, type, semantic);
}

MfxAttribute MfxMesh::AddFaceAttribute(const char* name, int componentCount, const char* type, const char* semantic)
{
	return AddAttribute(kOfxMeshAttribFace, name, componentCount, type, semantic);
}

MfxAttribute MfxMesh::AddMeshAttribute(const char* name, int componentCount, const char* type, const char* semantic)
{
	return AddAttribute(kOfxMeshAttribMesh, name, componentCount, type, semantic);
}

void MfxMesh::Allocate(int pointCount, int cornerCount, int faceCount, bool noLooseEdge, int constantFaceSize)
{
	MFX_ENSURE(propertySuite->propSetInt(m_properties, kOfxMeshPropPointCount, 0, pointCount));
	MFX_ENSURE(propertySuite->propSetInt(m_properties, kOfxMeshPropCornerCount, 0, cornerCount));
    MFX_ENSURE(propertySuite->propSetInt(m_properties, kOfxMeshPropFaceCount, 0, faceCount));
    MFX_ENSURE(propertySuite->propSetInt(m_properties, kOfxMeshPropNoLooseEdge, 0, (int)noLooseEdge));
    MFX_ENSURE(propertySuite->propSetInt(m_properties, kOfxMeshPropConstantFaceSize, 0, constantFaceSize));
	MFX_ENSURE(meshEffectSuite->meshAlloc(m_mesh));
}
