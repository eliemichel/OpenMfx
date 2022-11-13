RFC014 - Buffer Protocol
========================

*2020-06-21*, @eliemichel

Current Situation
-----------------

An attribute is represented by a data pointer, a type (float, int, ubyte) and a component count (to represent vectors of such types).

Key limitations
---------------

The data buffer needs to be contiguous. This is forces a representation based on an array of structs. However, some host software may store attributes in a struct of array instead.

Currently, when encountering this case we have to allocate a new buffer and copy its data for each attribute.

Another limitation that prevents from pointing effects directly to the original host-allocated buffers is that there is no mechanism to distinguish the case of newly allocated buffer vs. original buffer when it comes to freeing the data. This is even less clear when the output mesh points to the same data address than its input (to limit copies).

Proposal
--------

### Action

 - Add an integer property to `OfxMeshAttrib`, called `kOfxMeshAttribPropStride`. It represents the byte count between the beginning two consecutive entries in the attribute buffer. For a contiguous buffer, it must be set to `ComponentCount * sizeof(Type)`;

 - Add a boolean property to `OfxMeshAttrib`, called `kOfxMeshAttribPropIsOwner`. It is true when the mesh owns the data buffer, meaning that it must free it when it is destroyed.

### Consequences

 - The number of cases where it is possible to reuse host-allocated buffers as is is largely increased (especially for the Blender implementation).

 - To forward an attribute from an input to an output, the effect can simply copy the `Data` and `Stride` properties, and set `IsOwner` to `false` (`0`).

History
-------

 - *2020-06-21* Proposal was **adopted**. Commit [OpenMfx@28714fa](https://github.com/eliemichel/OpenMfx/commit/28714fae4ec6d004bad130bbc6c0d050be813889)

Contributors
------------

@eliemichel
