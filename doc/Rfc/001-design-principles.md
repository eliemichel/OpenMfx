RFC001 - Design Principles
==========================

```{warning}
This RFC is still a Work in Progress.
```

*2022-11-06*, @eliemichel

Avoid useless memory copies
---------------------------

Mesh data can be very heavy, we assume that it can get close to exceeding the hardware's memory and designed an API that does not require the host program to copy memory prior to providing data to the plugins. Of course, this is not always possible, but we tend to limit it whenever we can.

Optimize for more likely cases
------------------------------

Weird corner cases of mesh data are not equaly probable in real-life use cases. We provide optimized code paths for more likely cases. For instance, homogenous meshes, where all faces have the same number of corners, do not need to provide a list of corner counts per face.

But account for a diversity of scenario
---------------------------------------

We do not assume that meshes will always be well formed manifolds.
