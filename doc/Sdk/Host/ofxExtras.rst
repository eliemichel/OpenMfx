ofxExtras
=========

Implementation specific extensions to OpenMfx API.
These MUST NOT be used by plugins, but are here for communication between
the core host and application-specific code (in mfxModifier). This is (among
others) a way to keep this part of the code under the Apache 2 license while
the host application might be released under GPL.

.. doxygendefine:: kOfxMeshPropInternalData

.. doxygendefine:: kOfxMeshPropHostHandle

.. doxygendefine:: kOfxHostPropBeforeMeshReleaseCb

.. doxygentypedef:: BeforeMeshReleaseCbFunc

.. doxygendefine:: kOfxHostPropBeforeMeshGetCb

.. doxygentypedef:: BeforeMeshGetCbFunc

.. doxygendefine:: kOfxHostPropBeforeMeshAllocateCb

.. doxygentypedef:: BeforeMeshAllocateCbFunc

.. doxygendefine:: kMeshAttribRequestPropMandatory

