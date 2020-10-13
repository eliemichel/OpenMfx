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
	 * Populate the provided props structure woth this attribute's properties
	 */
	void FetchProperties(MfxMeshProps& props);

	MfxAttribute GetAttribute(const char* attachment, const char* name);
	MfxAttribute GetPointAttribute(const char* name);
	MfxAttribute GetVertexAttribute(const char* name);
	MfxAttribute GetFaceAttribute(const char* name);
	MfxAttribute GetMeshAttribute(const char* name);

	/**
	 * Always call this at some point, don't use the object afterwise.
	 * (This is not in the dtor because there may be copies of the instance but
	 * Release must be called only once)
	 */
	void Release();

public:
	// Only for output meshes and before allocation:
	MfxAttribute AddAttribute(const char* attachment, const char* name, int componentCount, const char *type);
	MfxAttribute AddPointAttribute(const char* name, int componentCount, const char* type);
	MfxAttribute AddVertexAttribute(const char* name, int componentCount, const char* type);
	MfxAttribute AddFaceAttribute(const char* name, int componentCount, const char* type);
	MfxAttribute AddMeshAttribute(const char* name, int componentCount, const char* type);

	void Allocate(int pointCount, int vertCount, int faceCount);

private:
	OfxMeshHandle m_mesh;
	OfxPropertySetHandle m_properties;
};
