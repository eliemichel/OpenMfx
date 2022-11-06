RFC007 - Requesting attributes
==============================

*2022-11-06*, @eliemichel

```{warning}
This RFC is still a Work in Progress.
```

Current Situation
-----------------

@tkarabela: How do I tell the host that (B1) I do or (B2) I don't care about certain attributes on input.

@eliemichel: An effect must be able to tell whether it needs UVs or not, or this or that specially named attribute, etc. It would enable sending only the relevant attributes, and also let the Host's UI tell the user about important missing attributes.

@tkarabela https://github.com/eliemichel/OpenMfx/issues/6#issuecomment-716243073

 - From work, I have experience with scientific/engineering visualization - having some surface/volumetric data with per-point or per-element attributes (scalar/vector/tensor) and processing them. The softwares used for that don't really care what the data is supposed to be, beyond the fundamental data type (eg. you can integrate a path through a vector field, but not scalar field).

 - However, when looking at Blender and other traditional 3D apps APIs, it seems that attribute handling is much more tailored to specific use cases (ie. you have "vertex colors" and "vertex weights" and "UV maps" which all have specific restrictions, and they are not interchangable/convertible, though at the end of the day they are all int/float attributes of the same thing).

 - This leads me to the idea of tagging attributes with "intent" (like OpenFX can hint that a float parameter is distance/angle/etc.), which would make it easier for the host to present suitable UI, especially since the different attributes can be stuffed into different namespaces in the host, like Blender does it. The effect would hint that it expects a "UV map" attribute on input, etc.

 - Perhaps it's not entirely necessary, since `2 x float` is likely a UV map, `3 x int8` is likely RGB color, etc.

 - Like with non-polygonal meshes, MfxVTK looks like a good testing vehicle for this :D For example, the "Sample points (volume)" effect computes "depth" of the points with respect to mesh surface. It would be cool to use this with instancing, using this "depth" in shader. However, as far as Blender:
   * It seems that most useful/accessible stuff (colors, UVs) is defined for vertices, not points
   * Even if I had eg. vertex colors, native object instancing still wouldn't pass the data to the instances...

@eliemichel https://github.com/eliemichel/OpenMfx/issues/6#issuecomment-716797657

I was thinking about making some attribute names conventional. This is inspired by Houdini, who tries to be as agnostic as your dataviz tools are wrt to attributes (`P` is the attribute for position, `N` for normals, `Cd` for color, `psize` for poitn size, etc.). This is already how it works for point position, vertex-point association and face counts: `kOfxMeshAttribPointPosition`, `kOfxMeshAttribVertexPoint` and `kOfxMeshAttribFaceCounts` are standardized attribtue names.

In Blender, these are called "layers" but it is quite similar. Layers that have a specific meaning like UVs are accessibles twice iirc: once as agnostic float2 layers, and once flagged as UVs. General purpose layers are not advertised anywhere in the UI but accessible for instance in Python through the BMesh module. So far the Blender implementation does not use them and only look at specific UVs because I discovered this only lately actually. I've started working on an add-on to visualize them in the viewport by the way.

In the end I think I like your idea of tagging attributes, so adding a `kOfxMeshAttribPropSubType`, it is quite consistent with the way parameter's subtypes are specified. I just wonder whether we should also specify some naming convention, like "if it starts or end with "uv" then it must be a UV or just say that "uv0, uv1, ..." are the standard texture coordinate attributes. Also, should such tags be forwarded by default to outputs? Is it the responsibility of the hosts or of the plugins?

```{seealso}
A lot of follow-ups to this thread, this was a long discussion, to be reported here.
```

Proposals
---------

Semantic

History
-------

 - *2020-10-15* Mentioned by @tkarabela in [OpenMfxForBlender#27](https://github.com/eliemichel/OpenMfxForBlender/issues/27#issuecomment-708721016).
 - *2020-10-15* Follow-up in [OpenMfx#6](https://github.com/eliemichel/OpenMfx/issues/6)

Contributors
------------

@tkarabela, @eliemichel, @ymankai
