RFC009 - Dynamic linking hell
=============================

```{warning}
This RFC is still a Work in Progress.
```

*2022-11-06*, @eliemichel

Current Situation
-----------------

Dynamic linking the same plugin into multiple third party programs has always been a problem. Example of MfxCascade, typically problems with TBB. How does OpenFX handle this? The VFX reference platform is not enough.

Proposals
---------

### Option A

Provide build scripts for each common host, to help plugin developpers, and formalize a mechanism for host editors to publish such build configs.

### Option B

Have hosts spawn a separate process, like the Houdini Engine can do.

#### Consequences

 - Plugins are sandboxed

#### Drawbacks

 - Might have consequences in terms of efficiency, could be enabled only on problematic effects.

 - Makes writing an host more complicated.
