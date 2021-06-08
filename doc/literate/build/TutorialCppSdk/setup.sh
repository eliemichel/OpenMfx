mkdir MfxTutorial
cd MfxTutorial

git init
git submodule add https://github.com/eliemichel/OpenMeshEffect

mkdir build
cd build
cmake ..
cmake --build .


