pushd doxygen
doxygen Doxyfile
REM doxygen Sdk.Doxyfile
popd

pushd sphinx
make html
popd
