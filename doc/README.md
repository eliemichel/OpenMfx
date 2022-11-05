Documentation
-------------

### Requirements

 - `doxygen` (to extract doc from source files)
 - `python` (to generate the documentation's html, via sphinx)
 - `lit` from https://github.com/zyedidia/Literate (for tutorials written using literate programming)

As well as the Python packages listed in `requirements.txt`, which you can install using:

```
pip install -r requirements.txt
```

### Building

The build process is controlled by CMake. Configure the project with `OPENMFX_BUILD_DOC` and then from your build directory, call in this order:

```
cmake --build . --target OpenMfx_Doc_Doxygen
cmake --build . --target OpenMfx_Doc_Sphinx
```

The documentation is generated in the `build/install/doc` directory, and can be uploaded using:

```
rsync -avz build/install/doc/ exppad:/home/elie/www/openmesheffect
```
