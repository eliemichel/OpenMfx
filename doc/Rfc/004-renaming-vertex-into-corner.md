RFC004 - Renaming Vertex into Corner
====================================

*Around early 2021*, @eliemichel

Referenced in RFC012 and RFC013.

Current Situation
-----------------

Mesh attributes are attached to one of the following entities:

 - points
 - **vertices**
 - faces
 - mesh (where there is only one entry for the whole mesh)

Faces connect multiple points, and a vertex represents the indirection between face corners and points. This indirection is needed to carry the connectivity information. It is important to distinguish a case where two face corners share the very same point (they are connected) from the case where the two face corners are (by chance) at the same location (they point to two different point entities that happen to have equal positions).

Key limitations
---------------

The term *Vertex* is very misleading. It has a different meaning in different APIs, for instance in Blender it corresponds to what we call here *Point*, while in Houdini it corresponds to our definition (because it is where we drew inspiration).

Furthermore, this term does not carry very clearly the information that it corresponds to a corner of a face, making the understanding of its role complex at first glance.

On a side note, another misleading name is the one of attribute `kOfxMeshAttribFaceCounts`. It seems to designate the number of faces present somewhere, while what it contains is actually a corner count for each face. The same remark stands for `kOfxMeshPropConstantFaceCount` as well. Also, `kOfxMeshAttribFaceCounts` takes a plural form that is inconsistent with other attribute names.

Proposals
---------

### Option A

#### Action

 - Rename "Vertex" into "Corner".

 - Rename `kOfxMeshPropConstantFaceCount` into `kOfxMeshPropConstantFaceSize` and `kOfxMeshAttribFaceCounts` into `kOfxMeshAttribFaceSize`.

#### Consequences

 - The role of the attachment is made clear.
 - There is no more ambiguity with other APIs (a corner is a Vertex in Houdini, a Loop in Blender).

#### Drawbacks

 - This is a breaking change.
 - Important change, which requires to rename in the API, the SDK, and the doc.


### Option B

#### Action

Same as Option A, except change `FaceCounts` into `FaceCornerSize` rather then `FaceSize`.

#### Drawbacks

 - It is longer to write, and the benefits in terms of clarity is moderate.

History
-------

 - *2021-06-08* **Option A** was adopted. Commit [OpenMfx@d376183](https://github.com/eliemichel/OpenMfx/commit/d376183517c175571d31542f039ba4b95f8cbd13)
