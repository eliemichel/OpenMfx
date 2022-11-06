RFC002 - Edge Representation
============================

*2020-10-13*, @tkarabela (*2022-11-06*, ported as an RFC by @eliemichel)

Referenced in RFC003, RFC010.

Current Situation
-----------------

There is no explicit representation of edges in the OpenMfx mesh structure. To define edge only meshes, one creates faces made of two vertices only.

Key limitations
---------------

### Two types of edges

This forces us to make the difference between so called "loose edges", namely edges that are not part of any face, and edges that are face borders.

### Misleading face count

With this design, the `kOfxMeshPropFaceCount` actually contains the number of proper faces (as in "with more than 2 corners") plus the number of loose edges.

### Custom edge attributes

Custom edge attributes are kind of possible but hacky. They are just corner attributes for which the corners that share the same edge have the same value (corners can be considered as corner+edge, like Blender's notion of "loop").

### Multiple code paths

On the host side, the presence of loose edges in a mesh triggers code paths quite different than when there are no such edges. Since this is not a common distinction, it is also likely to imply memory copy in one of these paths.

Inspiration
-----------

 - Houdini does not have explicit representation of edges neither (see https://www.sidefx.com/docs/houdini/model/attributes).

 - VTK has attributes for loose edges but not face edges.

 - Blender has attributes (called "layers") for all edges.

Proposals
---------

### Option A

#### Action

 - Disallow faces with less than 3 vertices.

 - Introduce new mandatory property to `OfxMesh` called `kOfxMeshPropLooseEdgeCount`. This is the number of loose edges.

 - Layout corner attribute arrays as follows:

    * The first `2 * kOfxMeshPropLooseEdgeCount` corners belong to loose edges (i.e., `kOfxMeshAttribCornerPoint[0], kOfxMeshAttribCornerPoint[1]` is first edge, `kOfxMeshAttribCornerPoint[2], kOfxMeshAttribCornerPoint[3]` is second edge, ...)

    * Corners after `2 * kOfxMeshPropLooseEdgeCount` belong to faces (i.e., like it is now: next `kOfxMeshAttribFaceSize[0]` number of corners belong to first face, then `kOfxMeshAttribFaceSize[1]` belong to the second face, ...)

#### Consequences

 - polygonal mesh - We do not need to care about edges, we may use the host's point, corner and face buffers directly.

 - edge-only wireframe - We do not need to care about faces, we may use the host's point, corner and edge buffers directly.

 - point cloud - We do not need to care about edges nor faces (this can already be optimized without the change though).

#### Drawbacks

 - The corner attribute layout is a bit convoluted. Mixing different data in the same buffers (edge extremities and face corners) does not feel right and is likely to prevent buffer reuse.

 - Buffer reuse will not be possible for meshes mixing both faces and loose edge, so this actually adds a third code path instead of reducing anything.

 - Are the cost in terms of minimalism and elegance of the API are worth the benefits?

### Option B

#### Action

Introduce a new attribute attachment for edges, called `kOfxMeshAttribEdge`. This attachment contains one element per loose edge, then one element per non loose edge.

#### Consequences

This enables per-edge attributes like in Blender.

#### Drawbacks

 - There is no clear way of ordering edges that are shared by multiple faces.

 - This is one more thing that hosts and plugins will need to handle.

### Option C

Introduce new property to `OfxMesh`, called `kOfxMeshPropLooseEdgeCount`, which will be the number of loose edges. This property is optional, if the count is set to -1 (the default), it means that there may or may not be loose edges.

#### Consequences

 - There is no need to change the attribute layout, this flags is only used to trigger accelerated code paths.

 - There is no change to make to existing plugins, as this property defaults to -1.

#### Drawbacks

 - The representation of edge-only wireframes is a bit silly, since `kOfxMeshAttribFaceSize` is an array of 2's, which almost certainly has to be allocated just for this purpose.

 - This does not do away with the edge-face confusion (not a technical issue, more conceptual/documentation).

### Option D

A variant of option C where teh integer `kOfxMeshPropLooseEdgeCount` is replaced by a simple boolean `kOfxMeshPropNoLooseEdge`.

We do not see a use case for knowing the exact edge count in mixed cases. If needed one can just iterate through face size, they would at some point anyways. It less missleading to just give a tag and not a precise count.

History
-------

 - *2020-06-23* The unclarity of this design was reported by @EleotleCram in issue [OpenMfxForBlender#27](https://github.com/eliemichel/OpenMfxForBlender/issues/27).
 - *2020-10-13* @tkarabela made the first proposal.
 - *2020-10-15* Follow-up in [OpenMfx#6](https://github.com/eliemichel/OpenMfx/issues/6)
 - *2020-10-16* @tkarabela raises the issue of edge ordering of Option B. It is abandonned. ([OpenMfx#6](https://github.com/eliemichel/OpenMfx/issues/6#issuecomment-709647993))
 - *2020-10-25* **Option D** is adopted.

Contributors
------------

@tkarabela, @eliemichel, @EleotleCram
