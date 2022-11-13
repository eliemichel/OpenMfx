OpenMfx for Blender
===================

The [OpenMfxForBlender](https://github.com/eliemichel/OpenMfxForBlender) project is a branch of Blender where OpenMfx effects can be used either as **modifiers** or as **geometry nodes**.

Usage
-----

A quick introduction of how to use this branch is given in [Using OpenMfx](../QuickStart/using-openmfx.md).

Building
--------

The usual [instructions for building Blender](https://wiki.blender.org/wiki/Building_Blender) apply.

The first difference is the repository to clone:

```
cd blender-git
git clone https://github.com/eliemichel/OpenMfxForBlender.git
make update
```

Then after `make update` you may have to switch the dependencies to the version on which the fork is based.

```
cd blender-git/lib/win64_vc15
svn up -r63009
```

The name `win64_vc15` will depend on your platform, and revision `63009` changes at each sync with the main branch, check out the release notes of the last version of the fork.

If the branch is based on a version, you can easily find the revision using tags, e.g., for Blender 3.3 instead of `svn up -r63009` one can type:

```
svn switch "^/tags/blender-3.3-release/lib/win64_vc15"
```

Contributing
------------

### How can I help?

 - By building the branch for MacOS and sharing the build with us
 - By testing the branch and [reporting any issue](https://github.com/eliemichel/OpenMfxForBlender/issues)
 - By trying to address the limitations you find, either in the code or in the documentation!

### A little guide for syncing with Blender's main branch

Provided the upstream repository is added as `upstream` (if not, run `git remote add upstream git://git.blender.org/blender.git`) and that you are on branch `openmfx`:

    git fetch upstream
    git tag  # find the tag X.X.X you want to merge
    git merge vX.X.X

Then call `make update` to sync the dependencies.

Run a `git status` to see all files marked as `both modified` or `both added`. For files `A`, `B`, `C`, etc. that are not related to OpenMfx nor to the integration of OpenMfx as a modifer, you can run

    git checkout --theirs A B C ...

For unrelated files that are `deleted by them`:

    git rm A B C ...

Other files require manual inspection! Example of files that must be handled manually:

    source/blender/makesdna/DNA_modifier_types.h
	source/blender/makesrna/intern/rna_modifier.c

Look for `>>>>>>>` and treat cases where the conflict area contains mentions to OpenMfx.

Finally, try to build and fix issues.
