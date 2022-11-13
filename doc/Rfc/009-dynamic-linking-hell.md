RFC009 - Dynamic linking hell
=============================

*2022-11-06*, @eliemichel

Current Situation
-----------------

An OpenMfx plugin is dynamically loaded into the host's main process.

Key limitations
---------------

Dynamic linking the same plugin into multiple third party programs has always been a problem. When the plugin itself depends on dynamically linked libraries, the latter may conflict with the host's symbols.

A very representative example is the one of MfxCascade, a plugin based on the [OpenCascade](https://dev.opencascade.org/) CAD kernel. OpenCascade uses Intel's [TBB](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onetbb.html), and the Blender host as well. However, they do not link against the same version, hence Blender is not able to load the MfxCascade plugin at runtime.

Proposals
---------

### Option A

As this issue is often raised in the Visual Effects industry, studios and software vendors came with the [VFX Reference Platform](https://vfxplatform.com/), a list of standardize versions of all major libraries linked by VFX software tools.

We can require from the effect that they comply strictly with this reference sheet.

#### Drawbacks

 - This is incompatible with bridging with mesh processing libraries initially meant for other industries, like OpenCascade.
 - The VFX Reference Platform may or may not hold forever.

### Option B

Based on the VFX Reference Platform idea, we can provide for each host a build script, so that it is easy enough for plugin vendors to batch build for all hosts. We could also formalize a mechanism for host vendors to publish such build configs.

#### Drawbacks

 - This may require multiple builds for each OS.
 - This might be hard to maintain.

### Option C

Add the possibility to run problematic plugins in a different process, like the Houdini Engine can do. Data buffers are communicated using shared memory.

#### Consequences

 - Plugins can be sandboxed
 - They cannot crash the main process

#### Drawbacks

 - This comes with an overhead because it requires to copy host buffers into the shared memory pages.
 - Writing an host gets more complicated, though this feature would be optional.

History
-------

 - *Around 2019* The issue was met regarding linking the Houdini Engine to Blender. Fortunately the Houdini Engine provides a split process mode to circumvent the issue.
 - *Around 2020* The issue is encountered with MfxCascade. This plugin is put on hold.
 - *2022-11-06* Discussions lead to rethinking the problem as being serious enough to need attention.

Contributors
------------

@eliemichel
