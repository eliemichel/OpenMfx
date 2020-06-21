This documentation uses sphinx. To generate it, install sphinx, as well as breathe, the link between sphinx (html generator) and doxygen (C docstring parser). We also use sphinxjp for the sphinx theme.

```
pip install sphinx
pip install breathe
pip install sphinxjp.themes.basicstrap
```

NB: This requires `pip`, Python's package manager, to be installed.

Then just run:

```
make html
```
