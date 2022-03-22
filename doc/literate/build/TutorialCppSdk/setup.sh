mkdir MfxTutorial
cd MfxTutorial

git init
git submodule add https://github.com/eliemichel/OpenMfx

mkdir build
cd build
cmake ..
cmake --build .


