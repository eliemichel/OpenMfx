.. _OfxMeshEffectActions:

Actions Passed to a Mesh Effect
===============================

OpenFX defines a unified way to interact with plug-ins through the notion of `action <https://openfx.readthedocs.io/en/master/Reference/ofxCoreAPI.html#the-plug-in-main-entry-point-and-actions>`_. Actions passed to an OpenMfx' plug-in main entry point are either some actions from OpenFX core, used with the same meaning, or dedicated actions.

For generic actions, the ``handle`` passed to to main entry point is an
:cpp:type:`OfxMeshEffectHandle`.

Actions specific to Mesh Effects
--------------------------------

.. doxygendefine:: kOfxMeshEffectActionCook

.. doxygendefine:: kOfxMeshEffectActionIsIdentity

.. doxygendefine_ kOfxMeshEffectActionDescribeInContext

Core OpenFX Actions supported by Mesh Effects
---------------------------------------------

These actions are already presented in the `Image Effect OpenFX API <https://openfx.readthedocs.io/en/master/Reference/ofxImageEffectActions.html>`_ but are listed here for the sake of completeness.

.. doxygendefine:: kOfxActionLoad

.. doxygendefine:: kOfxActionUnload

.. doxygendefine:: kOfxActionDescribe

.. doxygendefine:: kOfxActionCreateInstance

.. doxygendefine:: kOfxActionDestroyInstance
