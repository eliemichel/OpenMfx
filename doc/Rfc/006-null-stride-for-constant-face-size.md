RFC006 - Null stride for constant face size
===========================================

```{warning}
This RFC is still a Work in Progress.
```

*2022-11-06*, @eliemichel

Current Situation
-----------------

The `kOfxMeshConstantFaceSize` property originally introduced in RFC003 seems redundant with the possibility of simply specifying a null stride on the face size buffer.

Proposals
---------

### Option A

Status Quo

### Option B

Use null stride.

#### Consequences

 - We reduce the surface of the API the at no cost in terms of features.

#### Drawbacks

 - Not sure the null stride is implemented properly by existing hosts. A null stride so far might be treated as a stride equal to the size of the elements of the buffer.

 - This is a breaking change.

History
-------

 - *2022-11-06* RFC created.

Contributors
------------

@eliemichel
