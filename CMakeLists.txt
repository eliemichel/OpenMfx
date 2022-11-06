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

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(utils)

# The second argument is the default config when built as a standalone repository
option_if_not_defined(OPENMFX_BUILD_EXAMPLES "Build example projects" OFF ON)
option_if_not_defined(OPENMFX_BUILD_DOC "Build example projects" OFF ON)
option_if_not_defined(OPENMFX_EXCLUDE_FROM_ALL "Exclude all OpenMfx targets from the BUILD_ALL target" ON OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Main target (C API)
add_library(OpenMfx INTERFACE)
target_include_directories(OpenMfx INTERFACE include/)
add_library(OpenMfx::Core ALIAS OpenMfx)

# C++ API
add_subdirectory(sdk)

if (OPENMFX_BUILD_DOC)
	# Documentation
	add_subdirectory(doc)
endif()

# If this module is included as a subdirectory (or using FetchContent), we
# remove all targets from BUILD_ALL so that the parts of the SDK that are not
# used are not built by default
if (OPENMFX_EXCLUDE_FROM_ALL)
	message(STATUS "Removing OpenMfx targets from BUILD_ALL")
	get_all_targets(${CMAKE_CURRENT_SOURCE_DIR} all_targets NO_INTERFACE)
	set_target_properties(
		${all_targets}
		PROPERTIES
			EXCLUDE_FROM_ALL 1
			EXCLUDE_FROM_DEFAULT_BUILD 1
	)
endif()
