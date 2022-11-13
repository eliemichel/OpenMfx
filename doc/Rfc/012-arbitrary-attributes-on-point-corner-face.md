RFC012 - Arbitrary attributes on Point/Corner/Face
==================================================

*Around early 2020*, @eliemichel

Referenced by RFC008.

```{note}
What is now a "corner" was called "vertex" at the time (see RFC004), nonetheless this document uses the updated terminology.
```

Current Situation
-----------------

The `OfxMesh` structure has properties storing data buffers for per-point positions, per-corner point indices and per-face corner count.

Key limitations
---------------

There is no mechanism for adding additional attributes to any of these attachments. This would be required to support texture coordinates, normals, or any other user-defined attribute that is typically manipulated in a non-destructive mesh processing workflow.

Proposal
--------

### Action

 - Remove hardcoded `OfxMesh` properties `kOfxMeshPropPointData`, `kOfxMeshPropVertexData` and `OfxMeshPropFaceData`.

 - Add `kOfxMeshPropAttributeCount`

 - Create a new struct `OfxMeshAttrib` (represented as a property set) with properties `kOfxMeshAttribPropData`, `kOfxMeshAttribPropComponentCount`, and `kOfxMeshAttribPropType`.

 - `OfxMesh` is no longer represented by a simple property set. We add a new optional argument `propertySet` to mesh effect suite entry `inputGetMesh`.

 - New mesh effect suite entry `attributeDefine` to define an attribute, prior to allocating a mesh.

 - New mesh effect suite entry `meshGetAttribute` to get an attribute from a mesh by name.

 - `meshAlloc` no longer take point/corner/face counts as input. Since its behavior depends on the attributes that have been defined before, we fully commit to its stateful idiom, and it reads this from the mesh properties (`kOfxMeshPropPointCount`, etc.).

### Consequences

 - The mesh representation is much more flexible and in sync with real life use cases.

### Drawbacks

 - This slightly complexifies the API.

History
-------

 - *2020-02-08* Proposal was **adopted**. Commit [OpenMfx@099d4a3](https://github.com/eliemichel/OpenMfx/commit/099d4a3ab80999ae73eb71dc7a3cb0baaefc33d3)
