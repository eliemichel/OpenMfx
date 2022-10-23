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

set(SRC
  mfxPluginRegistry.h
  mfxPluginRegistryManager.h
  PluginRegistryManager.h

  src/Allocator.h
  src/attributes.h
  src/attributes.cpp
  src/properties.h
  src/properties.cpp
  src/parameters.h
  src/parameters.cpp
  src/inputs.h
  src/inputs.cpp
  src/mesh.h
  src/mesh.cpp
  src/mesheffect.h
  src/mesheffect.cpp
  src/messages.h
  src/messages.cpp
  src/mfxPluginRegistry.cpp
  src/mfxPluginRegistryManager.cpp
  src/PluginRegistryManager.cpp
  src/MfxHost.h
  src/MfxHost.cpp
  src/Collection.h

  src/parameterSuite.h
  src/parameterSuite.cpp
  src/propertySuite.h
  src/propertySuite.cpp
  src/meshEffectSuite.h
  src/meshEffectSuite.cpp
  src/messageSuite.h
  src/messageSuite.cpp

  util/binary_util.h
  util/mfx_util.h
  src/util/binary_util.c
  src/util/ofx_util.h
  src/util/ofx_util.c

  sdk/MfxAttributeProps.h
  sdk/MfxAttributeProps.cpp
)

add_library(OpenMfx_Sdk_Cpp_Host ${SRC})

target_include_directories(
  OpenMfx_Sdk_Cpp_Host
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
  OpenMfx_Sdk_Cpp_Host
  PUBLIC
    OpenMfx::Core
)

set_property(TARGET OpenMfx_Sdk_Cpp_Host PROPERTY FOLDER "OpenMfx/Sdk/Cpp")
add_library(OpenMfx::Sdk::Cpp::Host ALIAS OpenMfx_Sdk_Cpp_Host)
# Alternate target alias for backward compatibility
add_library(OpenMfx::Host ALIAS OpenMfx_Sdk_Cpp_Host)