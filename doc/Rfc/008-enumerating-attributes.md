RFC008 - Enumerating attributes
===============================

*2020-10-15*, @eliemichel

Current Situation
-----------------

The `OfxMesh` structure can contain arbitrary attributes and an effect can retrieve them by name (since RFC012).

Key limitations
---------------

However, an effect has no way of exploring attributes that it did not expect. This is however needed when effects is in theory able to forward any attribute it receives as input. A property `kOfxMeshPropAttributeCount` exists but there is no way of getting an attribute by index rather than by name.

Proposal
--------

### Action

 - Add a mesh effect suite entrypoint `meshGetAttributeByIndex`.

History
-------

 - *2020-10-15* Mentioned in [OpenMfx#6](https://github.com/eliemichel/OpenMfx/issues/6).
 - *2022-07-18* Proposal was **adopted**. Commit [OpenMfx@33e6352](https://github.com/eliemichel/OpenMfx/commit/33e635296caec70201cfdbd82393cc033a9c318c)

Contributors
------------

@eliemichel, @YassineMankai
