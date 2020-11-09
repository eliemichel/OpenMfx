.. _ofxMeshEffectAPI:

The Mesh Effect API
===================

.. doxygendefine:: kOfxMeshEffectPluginApi


Mesh Effect API Header Files
----------------------------

The Mesh Effect API itself is provided in the `ofxMeshEffect.h <https://github.com/eliemichel/OpenMeshEffect/blob/master/include/ofxMeshEffect.h>`_ header file. Other header files are the same as the one provided with the Image Effect API:

- `ofxMeshEffect.h <https://github.com/eliemichel/OpenMeshEffect/blob/master/include/ofxMeshEffect.h>`_
- `ofxCore.h <https://github.com/eliemichel/OpenMeshEffect/blob/master/include/ofxCore.h>`_
- `ofxProperty.h <https://github.com/eliemichel/OpenMeshEffect/blob/master/include/ofxProperty.h>`_
- `ofxParam.h <https://github.com/eliemichel/OpenMeshEffect/blob/master/include/ofxParam.h>`_
- `ofxMessage.h <https://github.com/eliemichel/OpenMeshEffect/blob/master/include/ofxMessage.h>`_

The reminder of this page focuses on the objects defined in ``ofxMeshEffect.h``. For the functions that operate on these object, see :ref:`ofxMeshEffectSuite`.

Mesh Effect
-----------

A Mesh Effect is an operator that expects zero or more meshes as inputs and provides zero or more other meshes as outputs. The behavior of such effect is tunned using parameters as defined in ``ofxParam.h``. They roughly correspond to a node in a node-based 3D modeling tool like Houdini or a modifier in a stack-based generation like in Blender or Cinema 4D. A mesh effect is manipulated using the ``OfxMeshEffectHandle`` type.

.. doxygentypedef:: OfxMeshEffectHandle


.. doxygendefine__ kOfxMeshEffectContextGenerator
.. doxygendefine__ kOfxMeshEffectContextFilter
.. doxygendefine__ kOfxMeshEffectContextGeneral

**Properties:**

.. doxygendefine:: kOfxMeshEffectPropIsDeformation

.. doxygendefine__ kOfxMeshEffectPropSupportedContexts

.. doxygendefine:: kOfxMeshEffectPropPluginHandle
.. doxygendefine__ kOfxMeshEffectPropContext

Mesh Data
---------

Mesh effects operate on mesh data represented by the ``OfxMeshHandle`` type:

.. doxygentypedef:: OfxMeshHandle

**Properties:**

.. doxygendefine:: kOfxMeshPropPointCount

.. doxygendefine:: kOfxMeshPropVertexCount

.. doxygendefine:: kOfxMeshPropFaceCount

.. doxygendefine:: kOfxMeshPropAttributeCount

.. doxygendefine:: kOfxMeshPropNoLooseEdge

.. doxygendefine:: kOfxMeshPropConstantFaceCount

.. doxygendefine:: kOfxMeshPropTransformMatrix


Inputs and outputs
------------------

Inputs and outputs of a mesh effect are the same type of object, both manipulated using the ``OfxMeshInputHandle`` type:

.. doxygentypedef:: OfxMeshInputHandle

Some hosts may give a special meaning to ``kOfxMeshMainInput`` and ``kOfxMeshMainOutput``, in particular if they only support the filter context (like Blender's modifiers).

.. doxygendefine:: kOfxMeshMainInput

.. doxygendefine:: kOfxMeshMainOutput


Custom Attributes
-----------------

The Open Mesh Effect API supports attaching any custom attribute to either points, vertices or faces. A fourth attribute attachment is for attributes with only one instance (the equivalent of detail attributes in Houdini). Some of these attributes are conventional and expected to always be present.

**Attribute attachments:**

.. doxygendefine:: kOfxMeshAttribPoint

.. doxygendefine:: kOfxMeshAttribVertex

.. doxygendefine:: kOfxMeshAttribFace

.. doxygendefine:: kOfxMeshAttribMesh

**Conventional attributes:**

.. doxygendefine:: kOfxMeshAttribPointPosition

.. doxygendefine:: kOfxMeshAttribVertexPoint

.. doxygendefine:: kOfxMeshAttribFaceCounts


**Attribute properties:**

An attribute is represented by a generic ``OfxPropertySetHandle`` that provides the following keys:

.. doxygendefine:: kOfxMeshAttribPropData

.. doxygendefine:: kOfxMeshAttribPropIsOwner

.. doxygendefine:: kOfxMeshAttribPropStride

.. doxygendefine:: kOfxMeshAttribPropComponentCount

.. doxygendefine:: kOfxMeshAttribPropType

**NB** The ``plugin_support`` code in the Implementation section provides fonctions to more easily access this information for plugin writers.

**Attributes types:**

.. doxygendefine:: kOfxMeshAttribTypeUByte

.. doxygendefine:: kOfxMeshAttribTypeInt

.. doxygendefine:: kOfxMeshAttribTypeFloat
