Documentation
-------------

### Requirements

 - `doxygen` (to extract doc from source files)
 - `sphinx` (to generate the documentation's html)
 - `lit` from https://github.com/zyedidia/Literate (for tutorials written using literate programming)

```
pip install sphinx
pip install breathe
pip install sphinxjp.themes.basicstrap
pip install myst-parser
```

### Building

Just call `make.bat`.

To do it manually, run `doxygen` in the `doxygen/` directory, then `make install` in the `sphinx/` directory:

```
cd doxygen
doxygen
cd ../sphinx
make html
```

The documentation is generated in the `sphinx/_build/html` directory.

### Misc

The directory `guide` is only here to ensure backward compatibility of potential external documentation links.
