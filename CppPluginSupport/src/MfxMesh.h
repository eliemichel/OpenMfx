#pragma once

#include "MfxBase.h"
#include "MfxAttribute.h"
#include "MfxMeshProps.h"

#include "ofxCore.h"
#include "ofxMeshEffect.h"

/**
 * Mesh data coming from an input or being sent to an output.
 * The instance of this class -- like all classes from this API except the
 * structs whose name ends with "Props" -- does not actually contain data,
 * it is only a reference and can hence be freely copied around without
 * worrying about memory usage. You MUST call \ref Release once and only once
 * though.
 */
class MfxMesh : public MfxBase
{
private:
	friend class MfxInput;
	MfxMesh(const MfxHost& host, OfxMeshHandle mesh, OfxPropertySetHandle properties);

public:
	/**
	 * A mesh may be invalid if its parent input is not connected to any incoming link.
	 * If this returns false, none of the other methods must be called.
	 */
	bool IsValid() const;

	/**
	 * Populate the provided props structure with this mesh's properties
	 */
	void FetchProperties(MfxMeshProps& props);

	/**
	 * Populate the provided pointer to float array with this mesh's transform matrix.
	 * Requires to have called RequestTransform during the describe action
	 */
	void FetchTransform(double**matrix);

	/**
	 * Get an attribute of an input or output mesh.
	 * The returned \ref MfxAttribute can be used to get the data buffer and
	 * extra information like type, component count, stride, etc.
	 * `Get*Attribute` methods are shortcuts for the different values allowed
	 * for the `attachment` argument.
	 */
    MfxAttribute GetAttribute(const char* attachment, const char* name);
    MfxAttribute GetAttribute(MfxAttributeAttachment attachment, const char* name);
	MfxAttribute GetPointAttribute(const char* name);
	MfxAttribute GetVertexAttribute(const char* name);
	MfxAttribute GetFaceAttribute(const char* name);
	MfxAttribute GetMeshAttribute(const char* name);

	/**
	 * Tells whether an attribute exists in the input or output mesh.
	 * `Has*Attribute` methods are shortcuts for the different values allowed
	 * for the `attachment` argument.
	 */
    bool HasAttribute(const char* attachment, const char* name);
    bool HasAttribute(MfxAttributeAttachment attachment, const char* name);
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
	/**
	 * Define a new attribute on an output mesh.
	 * The returned \ref MfxAttribute can be used to set additionnal properties
	 * such has whether the data is "owned" or borrowed/forwarded from an input.
	 * `Add*Attribute` methods are shortcuts for the different values allowed
	 * for the `attachment` argument.
	 *
	 * \see attributeDefine from ofxMeshEffect.h for more information.
	 *
	 * Call **only for output** meshes and before allocation:
	 * 
	 * TODO: Have the type argument use MfxAttributeType enum as defined in MfxAttributeProps.h
	 */
	MfxAttribute AddAttribute(const char* attachment, const char* name, int componentCount, const char *type, const char* semantic = NULL);
	MfxAttribute AddPointAttribute(const char* name, int componentCount, const char* type, const char* semantic = NULL);
	MfxAttribute AddVertexAttribute(const char* name, int componentCount, const char* type, const char* semantic = NULL);
	MfxAttribute AddFaceAttribute(const char* name, int componentCount, const char* type, const char* semantic = NULL);
	MfxAttribute AddMeshAttribute(const char* name, int componentCount, const char* type, const char* semantic = NULL);

    MfxAttribute AddAttribute(MfxAttributeAttachment attachment, const char* name, int componentCount, MfxAttributeType type, MfxAttributeSemantic semantic = MfxAttributeSemantic::None);
    MfxAttribute AddPointAttribute(const char* name, int componentCount, MfxAttributeType type, MfxAttributeSemantic semantic = MfxAttributeSemantic::None);
    MfxAttribute AddVertexAttribute(const char* name, int componentCount, MfxAttributeType type, MfxAttributeSemantic semantic = MfxAttributeSemantic::None);
    MfxAttribute AddFaceAttribute(const char* name, int componentCount, MfxAttributeType type, MfxAttributeSemantic semantic = MfxAttributeSemantic::None);
    MfxAttribute AddMeshAttribute(const char* name, int componentCount, MfxAttributeType type, MfxAttributeSemantic semantic = MfxAttributeSemantic::None);

	/**
	 * Allocate memory for new owned attributes according to the previously
	 * called \ref AddAttribute and likes. Non own attributes are attributes
	 * pointing to externally allocated memory (for instance memory buffers
	 * forwarded from the input) and will hence not be newly allocate.
	 * Call **only for output** meshes.
	 */
    void Allocate(int pointCount, int vertCount, int faceCount, bool noLooseEdge=true, int constantFaceCount=-1);

private:
	OfxMeshHandle m_mesh;
	OfxPropertySetHandle m_properties;
};
