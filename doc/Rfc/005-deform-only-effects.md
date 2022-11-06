RFC005 - Deform-only effects
============================

```{warning}
This RFC is still a Work in Progress.
```

*2022-11-06*, @eliemichel

Current Situation
-----------------

Some effects only move points, but do not affect connectivity. This is usually handled in a special way by host software to avoid copying unchanged connectivity data.

@tkarabela: How do I tell the host that it should copy connectivity from input mesh (kOfxMeshMainInput?) to output (kOfxMeshMainOutput).

**Attribute forwarding** little advertised fact: It is possible already to point the output at the same buffer as the input, for unchanged attributes, and in particular for connectivity information when the effect only is a modifier.

Proposals
---------

### Option A

Add a new property to `OfxMesh`, called `kOfxMeshPropDeformOnly`.

### Option B

Create a new action, a bit like for IsIdentity.

#### Drawbacks

 - It is an action to check whether an effect with a given valuation of its parameters is the Identity, but for deformers we need to know whether the effect is *intrinsically* a deformer, which ever values its parameters have (deformers for only some parameters' valuation are handled by attribute forwarding). So this must actually be a property of an effect. I suggest kOfxMeshEffectPropIsDeformation (set to false by default).

### Option C

Add a new boolean property to `OfxMeshEffect` called `kOfxMeshEffectPropIsDeformation`, set to false by default.

Unsolved issue
--------------

@tkarabela: it might be a minor issue that by the time the output mesh is inputReleaseMesh()-ed, the mesh with the forwarded attribute may have already been inputReleaseMesh()-ed before, as order of releasing is undefined. For kOfxMeshAttribPropIsOwner == true, that sounds like trouble, but the inputs should ideally be proxied anyway, and I assume most of the time all host input buffers outlive cooking time. Still, I think it should be adressed in the spec in some way (while mentioning that "attribute forwarding" is a thing and that it's encouraged).

As of *2022-11-06*, this is still not implemented in the Blender host because the deform only property of modifiers has to be declared statically.

History
-------

 - *2020-10-15* Mentioned by @tkarabela in [OpenMfxForBlender#27](https://github.com/eliemichel/OpenMfxForBlender/issues/27#issuecomment-708721016).
 - *2020-10-15* Follow-up in [OpenMfx#6](https://github.com/eliemichel/OpenMfx/issues/6)
 - *2020-10-25* Abandoning Option B, proposing Option C ([OpenMfx#6](https://github.com/eliemichel/OpenMfx/issues/6#issuecomment-716202947))
 - *2020-10-25* **Option C** is adopted.

Contributors
------------

@tkarabela, @eliemichel
