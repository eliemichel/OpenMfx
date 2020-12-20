# ***** BEGIN APACHE 2 LICENSE BLOCK *****
#
# Copyright 2019 Elie Michel
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

cmake_minimum_required(VERSION 3.0...3.18.4)
project(OpenMeshEffect)

option(OPENMESHEFFECT_BUILD_EXAMPLES "Build example projects" OFF)

# Main target (C API)
add_library(openmesheffect INTERFACE)
target_include_directories(openmesheffect INTERFACE include)

# C++ API
add_subdirectory(CppPluginSupport)

if (OPENMESHEFFECT_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif ()