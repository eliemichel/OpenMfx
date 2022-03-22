cmake_minimum_required(VERSION 3.0...3.18.4)
# Name of the project
project(MfxTutorial)

# Add OpenMfx to define CppPluginSupport, the C++ helper API
add_subdirectory(OpenMfx)

# Define the plugin target, called for instance mfx_tutorial
# You may list additional source files after "plugin.cpp"
add_library(mfx_tutorial SHARED plugin.cpp)

# Set up the target to depend on CppPluginSupport and output a file
# called .ofx (rather than the standard .dll or .so)
target_link_libraries(mfx_tutorial PRIVATE CppPluginSupport)
set_target_properties(mfx_tutorial PROPERTIES SUFFIX ".ofx")

