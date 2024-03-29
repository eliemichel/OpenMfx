/*
 * Copyright 2019 - 2022 Elie Michel
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "Properties.h"
#include "Attributes.h"

struct OfxMeshStruct {
 public:
  OfxMeshStruct();
  ~OfxMeshStruct();

  // Disable copy, we handle it explicitely
  OfxMeshStruct(const OfxMeshStruct &) = delete;
  OfxMeshStruct &operator=(const OfxMeshStruct &) = delete;

  OfxMeshStruct(OfxMeshStruct&&) = default;
  OfxMeshStruct& operator=(OfxMeshStruct&&) = default;

  void deep_copy_from(const OfxMeshStruct &other);

  void free_owned_data();

 public:
  OfxPropertySetStruct properties;
  OfxAttributeSetStruct attributes;
};

namespace OpenMfx {
typedef OfxMeshStruct Mesh;
} // namespace OpenMfx
