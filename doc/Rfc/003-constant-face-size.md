RFC003 - Constant Face Size
===========================

*2020-10-13*, @tkarabela (*2022-11-06*, ported as an RFC by @eliemichel)

Referenced in RFC006.

Current Situation
-----------------

Most of the time, input and output meshes are "homogenous", in the sense that they are either:

 - a polygonal mesh - proper faces, no loose edges, no isolated points
 - an edge-only wireframe - no faces, only loose edges, no isolated points
 - a point cloud - no faces, no loose edges, just isolated points

But they more rarely are a mix of these options. Furthermore, a polygonal mesh can often contain only triangle faces, or only quad faces.

Key limitations
---------------

### Useless face size buffer

Edge-only, triangle-only and quad-only meshes have a buffer of face size (`kOfxMeshAttribFaceSize`) that is uniform, this could be factorized.

### Misleading face count

As already discussed in RFC002, the `kOfxMeshPropFaceCount` actually contains the number of proper faces plus the number of loose edges.

Proposals
---------

### Option A

#### Action

Add a property to `OfxMesh` called `kOfxMeshPropConstantFaceSize` and set to 2, 3 or 4 when there are respectively only edges, triangles or quads, 0 for point clouds, or -1 to mean "use `kOfxMeshAttribFaceSize`".

#### Consequences

 - Whenever the face size buffer is constant, it does not need to be allocated.

 - A host of plugin can implement a fast code path for some special scenarios (for instance plugins that use a backend which requires triangle-only meshes can skip the conversion step).

History
-------

 - *2020-10-13* Kickstarted by @tkarabela in [OpenMfxForBlender#27](https://github.com/eliemichel/OpenMfxForBlender/issues/27).
 - *2020-10-15* Follow-up in [OpenMfx#6](https://github.com/eliemichel/OpenMfx/issues/6)
 - *2020-10-25* **Option A** is adopted.

Contributors
------------

@tkarabela, @eliemichel
