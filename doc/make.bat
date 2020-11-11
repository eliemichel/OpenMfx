pushd doxygen
doxygen Doxyfile
doxygen Sdk.Doxyfile
popd

pushd sphinx
make html
popd
