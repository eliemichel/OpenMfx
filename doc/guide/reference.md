
OpenFX Mesh Effect API - Programming Reference
==============================================

*TODO*

Before looking at the mesh effect API itself, you must get familiarized with the generic OpenFX API, reading its programming reference at http://openeffects.org/documentation/reference/.

Then, you can read the docstrings of the Mesh Effect API in [include/ofxMeshEffect.h](../../include/ofxMeshEffect.h).

Key differences with OpenFX
---------------------------

### The OfxSetBundleDirectory symbol

Open Mesh Effect introduced an extra symbol that a plugin binary may export: the `OfxSetBundleDirectory` symbol. Since this is an extension of the original core OpenFX standard, it is not mandatory. Hosts must not fail at loading the plug-ins if it is not implemented.

The rational for this new symbol is for plug-in binaries whose number of plug-ins depends on some resource file. The OpenFX standard specifies that binaries are distributed within a *bundle*, that may include binaries for different architectures and may also contain resource files. But at the time `OfxGetNumberOfPlugins` is called, the binary has no mean of knowing where these resources are.

If it is implemented, `OfxSetBundleDirectory` must be called by the host *before* `OfxGetNumberOfPlugins` to tell the binary the path to the root of the bundle in which it is located. The binary is responsible for caching this information. `OfxSetBundleDirectory` is never called again, the bundle directory cannot change while the binary is loaded.

