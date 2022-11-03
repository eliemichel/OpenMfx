Documentation
-------------

### Requirements

 - `doxygen` (to extract doc from source files)
 - `sphinx` (to generate the documentation's html)
 - `lit` from https://github.com/zyedidia/Literate (for tutorials written using literate programming)

```
pip install sphinx
pip install breathe
pip install myst-parser
pip install furo
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

The documentation is generated in the `sphinx/_build/html` directory, and can be uploaded using:

```
rsync -avz sphinx/_build/html/ exppad:/home/elie/www/openmesheffect
```

### Misc

The directory `guide` is only here to ensure backward compatibility of potential external documentation links.
