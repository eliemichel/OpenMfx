#pragma once

#include "MfxBase.h"
#include "MfxAttribute.h"
#include "MfxMeshProps.h"

#include "ofxCore.h"
#include "ofxMeshEffect.h"

class MfxMesh : public MfxBase
{
private:
	friend class MfxInput;
	MfxMesh(const MfxHost& host, OfxMeshHandle mesh, OfxPropertySetHandle properties);

public:
	/**
	 * Populate the provided props structure with this attribute's properties
	 */
	void FetchProperties(MfxMeshProps& props);

	MfxAttribute GetAttribute(const char* attachment, const char* name);
	MfxAttribute GetPointAttribute(const char* name);
	MfxAttribute GetVertexAttribute(const char* name);
	MfxAttribute GetFaceAttribute(const char* name);
	MfxAttribute GetMeshAttribute(const char* name);

    bool HasAttribute(const char* attachment, const char* name);
    bool HasPointAttribute(const char* name);
    bool HasVertexAttribute(const char* name);
    bool HasFaceAttribute(const char* name);
    bool HasMeshAttribute(const char* name);

	/**
	 * Always call this at some point, don't use the object afterwise.
	 * (This is not in the dtor because there may be copies of the instance but
	 * Release must be called only once)
	 */
	void Release();

public:
	// Only for output meshes and before allocation:
	MfxAttribute AddAttribute(const char* attachment, const char* name, int componentCount, const char *type, const char* semantic = NULL);
	MfxAttribute AddPointAttribute(const char* name, int componentCount, const char* type, const char* semantic = NULL);
	MfxAttribute AddVertexAttribute(const char* name, int componentCount, const char* type, const char* semantic = NULL);
	MfxAttribute AddFaceAttribute(const char* name, int componentCount, const char* type, const char* semantic = NULL);
	MfxAttribute AddMeshAttribute(const char* name, int componentCount, const char* type, const char* semantic = NULL);

    void Allocate(int pointCount, int vertCount, int faceCount, bool noLooseEdge=true, int constantFaceCount=-1);

private:
	OfxMeshHandle m_mesh;
	OfxPropertySetHandle m_properties;
};
