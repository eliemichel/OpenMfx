# ***** BEGIN APACHE 2 LICENSE BLOCK *****
#
# Copyright 2019-2022 Elie Michel
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

cmake_minimum_required(VERSION 3.0...3.24)
project(
	OpenMfx
	VERSION 1.0
	DESCRIPTION "A low-overhead mesh-processing plug-in API for cross-software procedural effects"
	HOMEPAGE_URL "https://openmesheffect.org"
	LANGUAGES C CXX
)

include(cmake/utils.cmake)

option(OPENMFX_BUILD_EXAMPLES "Build example projects" OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Main target (C API)
add_library(OpenMfx INTERFACE)
target_include_directories(OpenMfx INTERFACE include/)
add_library(OpenMfx::Core ALIAS OpenMfx)

# C++ API
add_subdirectory(sdk)

if (OPENMFX_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif ()
