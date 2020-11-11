#pragma once

/**
 * Properties attached to an MfxMesh.
 * Usage:
 * ```{.cpp}
 * MfxMeshProps props;
 * mesh.FetchProperties(props);
 * ```
 */
struct MfxMeshProps
{
	/**
	 * Number of points.
	 *
	 * A point is a location in the 3D space.
	 */
    int pointCount;

    /**
     * Number of vertices.
     *
     * A vertex is a "face corner", associating a face to a point.
     * For instance UVs are typically attached to vertices because a given
     * point may have different UV coordinates depending on whether it
     * belongs to a face or another one.
     *
     * *NB: This is called a "loop" in Blender.*
     */
    int vertexCount;

    /**
     * Number of faces.
	 *
     * Faces may have 2 or more vertices. When they have only two vertices,
     * there are also called "loose edges".
     */
    int faceCount;

    /**
     * Tells whether the mesh has some 2-vertices faces. If set to true, the
     * mesh is garrantied to have at least 3 vertices per face. Otherwise, there
     * is no warranty, namely the mesh may or may not have loose edges.
     */
    bool noLooseEdge;

    /**
     * If different from -1, tells that all faces of the mesh have the same number
     * of vertices. For instance, a mesh only made of triangles may have this
     * property set to 3. A wireframe mesh, containing only loose edges, will have
     * this set to 2. When it set to -1, individual vertex counts for each face are
     * given by the \ref kOfxMeshAttribFaceCounts
     */
    int constantFaceCount;

    /**
     * Number of attributes attached to this mesh.
     * *NB: This is not useful at the moment because there is no way to discover what
     * are the names of these attributes.*
     */
    int attributeCount;
};
