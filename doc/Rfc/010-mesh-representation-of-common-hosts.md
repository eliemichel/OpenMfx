RFC010 - Mesh representation of common hosts
============================================

```{warning}
This RFC needs to be properly formatted according to the general guidelines.
```

*2020-10-24* @tkarabela

*While looking at a solution for representing edges (see RFC002):*

I looked into some of the APIs, here's what I gathered:

**Maya**

- Mesh consists of
  - Vertices (like OFX points, coordinates in 3D space)
  - Edges (ordered pairs of vertices)
  - Faces (defined by edges)
  - Face-vertices (like OFX vertices)
- There is support for arbitrary face attributes ("Blind data"), int/float/bool/string...
- References
  - http://docs.autodesk.com/MAYAUL/2014/ENU/Maya-API-Documentation/files/Polygon_API_How_polygons_are_handled_internally.htm
  - https://help.autodesk.com/view/MAYAUL/2020/ENU/?guid=__developer_Maya_SDK_MERGED_Polygon_API_The_five_basic_polygonal_API_html
  - https://download.autodesk.com/global/docs/maya2014/en_us/files/Blind_data_What_is_blind_data_.htm

**3DS Max**

- Two kinds of meshes:
  - `Mesh` has
    - Vertices (like OFX points, coordinates in 3D space)
    - Faces (triangles, defined by 3 vertices)
    - no explicit edges
    - can have per-vertex float attributes (`PerData`)
  - `MNMesh` has
    - Vertices (`MNVert`)
    - Edges (`MNEdge`, pairs of vertices with reference to face)
    - Faces (`MNFace`, refers to vertices and edges)
    - can have per-vertex and per-edge float attributes (`PerData`)
- References
  - https://help.autodesk.com/view/MAXDEV/2021/ENU/?guid=__developer_3ds_max_sdk_features_modeling_meshes_html
  - https://help.autodesk.com/view/MAXDEV/2021/ENU/?guid=__cpp_ref_class_m_n_edge_html

**Cinema4D**

- Meshes can have point data (OFX point attributes) or polygon point data (OFX vertex attributes)
- I didn't find reference to the internal representation, looks like the public API is a bit higher level
  (eg. `GetPolygonCount()` docs says "While this function may sound trivial and cheap, internally it is not.")
- References
  - https://developers.maxon.net/docs/Cinema4DCPPSDK/html/page_manual_customdatatag.html

**Universal Scene Description format**

- Uses the same representation as OFX (points, face-vertices and face-vertex counts)
- References
  - https://graphics.pixar.com/usd/docs/api/class_usd_geom_mesh.html

It seems to me that edge representation is motivated by efficient mesh traversal, not just storing per-edge data. Personally I quite like the current point/vertex/face representation (à la Houdini or USD), I think it's easy to work with and agnostic w.r.t. plugin/host implementation details. Committing to a particular edge representation seems to add complexity and increase impedance mismatch when converting to/from OFX mesh. The Maya model doesn't look bad, but I'd rather just generate faces/vertices and not have to worry about edges and any deduplication that may be required.

Regarding edge attributes themselves, it would be handy that "if the effect preserves topology, make it preserve any edge attributes as well" (this can be a host implementation detail), however I don't know of a particular use case for them in an effect which couldn't be solved with vertex/face attributes. (In the special case of loose edges, we have "loose edge attributes" already in form of face attributes.)

History
-------

 - *2020-10-24* Published in [OpenMfx#6](https://github.com/eliemichel/OpenMfx/issues/6#issuecomment-715966550).
