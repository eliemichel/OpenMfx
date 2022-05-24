# ***** BEGIN APACHE 2 LICENSE BLOCK *****
#
# Copyright 2019-2021 Elie Michel
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# ***** END APACHE 2 LICENSE BLOCK *****

file(GLOB SRC src/*/*.cpp src/*/*.h)

# Dunno why we need to redefine this even though it has been defined
# in parent directory but don't have time now to investigate. Redefining
# here works even though it is not clean.
if (NOT TARGET OpenMfx::Core)
    add_library(OpenMfx INTERFACE)
    target_include_directories(OpenMfx INTERFACE ../include/)
    add_library(OpenMfx::Core ALIAS OpenMfx)
endif()

add_library(CppPluginSupport "${SRC}")
target_link_libraries(CppPluginSupport PUBLIC OpenMfx::Core)
target_include_directories(CppPluginSupport PUBLIC include)
add_library(OpenMfx::CppPluginSupport ALIAS CppPluginSupport)
