/*
 * Copyright 2019-2022 Elie Michel
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

#include "meshEffectSuite.h"
#include "propertySuite.h"
#include "mesheffect.h"

#include <cstring>
#include <cstdio>
#include <cassert>

using namespace OpenMfx;

#define MFX_ENSURE(op) assert(kOfxStatOK == op)

 // CONVERSION UTILS

static AttributeAttachment mfxToInternalAttribAttachment(const char *attachment)
{
  if (0 == strcmp(attachment, kOfxMeshAttribPoint)) {
    return AttributeAttachment::Point;
  }
  else if (0 == strcmp(attachment, kOfxMeshAttribCorner)) {
    return AttributeAttachment::Corner;
  }
  else if (0 == strcmp(attachment, kOfxMeshAttribFace)) {
    return AttributeAttachment::Face;
  }
  else if (0 == strcmp(attachment, kOfxMeshAttribMesh)) {
    return AttributeAttachment::Mesh;
  }
  else {
    return AttributeAttachment::Invalid;
  }
}

// // Mesh Effect Suite Entry Points

const OfxMeshEffectSuiteV1 gMeshEffectSuiteV1 = {
    /* getPropertySet */ getPropertySet,
    /* getParamSet */ getParamSet,
    /* inputDefine */ inputDefine,
    /* inputGetHandle */ inputGetHandle,
    /* inputGetPropertySet */ inputGetPropertySet,
    /* inputRequestAttribute */ inputRequestAttribute,
    /* inputGetMesh */ inputGetMesh,
    /* inputReleaseMesh */ inputReleaseMesh,
    /* attributeDefine */ attributeDefine,
    /* meshGetAttributeByIndex */ meshGetAttributeByIndex,
    /* meshGetAttribute */ meshGetAttribute,
    /* meshGetPropertySet */ meshGetPropertySet,
    /* meshAlloc */ meshAlloc,
    /* abort */ ofxAbort};

OfxStatus getPropertySet(OfxMeshEffectHandle meshEffect, OfxPropertySetHandle *propHandle)
{
  *propHandle = &meshEffect->properties;
  return kOfxStatOK;
}

OfxStatus getParamSet(OfxMeshEffectHandle meshEffect, OfxParamSetHandle *paramSet)
{
  *paramSet = &meshEffect->parameters;
  return kOfxStatOK;
}

OfxStatus inputDefine(OfxMeshEffectHandle meshEffect,
                      const char *name,
                      OfxMeshInputHandle *input,
                      OfxPropertySetHandle *propertySet)
{
  printf("Defining input '%s' on OfxMeshEffectHandle %p\n", name, meshEffect);
  int i = meshEffect->inputs.ensure(name);
  meshEffect->inputs[i].host = meshEffect->host;
  propSetPointer(
      &meshEffect->inputs[i].mesh.properties, kOfxMeshPropInternalData, 0, NULL);
  if (NULL != input) {
    *input = &meshEffect->inputs[i];
  }
  if (NULL != propertySet) {
    *propertySet = &(meshEffect->inputs[i].properties);
  }
  return kOfxStatOK;
}

OfxStatus inputGetHandle(OfxMeshEffectHandle meshEffect,
                         const char *name,
                         OfxMeshInputHandle *input,
                         OfxPropertySetHandle *propertySet)
{
  int i = meshEffect->inputs.find(name);
  if (-1 == i) {
    return kOfxStatErrUnknown;  // bad name
  }
  *input = &meshEffect->inputs[i];
  if (NULL != propertySet) {
    *propertySet = &(meshEffect->inputs[i].properties);
  }
  return kOfxStatOK;
}

OfxStatus inputGetPropertySet(OfxMeshInputHandle input, OfxPropertySetHandle *propHandle)
{
  *propHandle = &input->properties;
  return kOfxStatOK;
}

OfxStatus inputRequestAttribute(OfxMeshInputHandle input,
    const char* attachment,
    const char* name,
    int componentCount,
    const char* type,
    const char* semantic,
    int mandatory)
{
  if (componentCount < 1 || componentCount > 4) {
    return kOfxStatErrValue;
  }
  if (0 != strcmp(type, kOfxMeshAttribTypeInt) && 0 != strcmp(type, kOfxMeshAttribTypeFloat) &&
      0 != strcmp(type, kOfxMeshAttribTypeUByte)) {
    return kOfxStatErrValue;
  }

  if (semantic != nullptr &&
      0 != strcmp(semantic, kOfxMeshAttribSemanticTextureCoordinate) &&
      0 != strcmp(semantic, kOfxMeshAttribSemanticNormal) &&
      0 != strcmp(semantic, kOfxMeshAttribSemanticColor) &&
      0 != strcmp(semantic, kOfxMeshAttribSemanticWeight)) {
    return kOfxStatErrValue;
  }

  AttributeAttachment intAttachment = mfxToInternalAttribAttachment(attachment);
  if (intAttachment == AttributeAttachment::Invalid) {
    return kOfxStatErrBadIndex;
  }

  int i = input->requested_attributes.ensure({ intAttachment, name });

  OfxPropertySetStruct *attributeProperties =
      &input->requested_attributes[i].properties;
  propSetInt(attributeProperties, kOfxMeshAttribPropComponentCount, 0, componentCount);
  propSetString(attributeProperties, kOfxMeshAttribPropType, 0, type);
  propSetString(attributeProperties, kOfxMeshAttribPropSemantic, 0, semantic);
  propSetInt(attributeProperties, kMeshAttribRequestPropMandatory, 0, mandatory);

  return kOfxStatOK;
}

OfxStatus inputGetMesh(OfxMeshInputHandle input,
                       OfxTime time,
                       OfxMeshHandle *meshHandle,
                       OfxPropertySetHandle *propertySet)
{
  (void)time;
  OfxMeshHandle inputMeshHandle = &input->mesh;
  OfxPropertySetHandle inputMeshProperties = &input->mesh.properties;
  propSetPointer(inputMeshProperties, kOfxMeshPropHostHandle, 0, (void *)input->host);
  propSetInt(inputMeshProperties, kOfxMeshPropPointCount, 0, 0);
  propSetInt(inputMeshProperties, kOfxMeshPropCornerCount, 0, 0);
  propSetInt(inputMeshProperties, kOfxMeshPropFaceCount, 0, 0);
  propSetInt(inputMeshProperties, kOfxMeshPropAttributeCount, 0, 0);

  // Default attributes
  inputMeshHandle->attributes.clear();

  attributeDefine(inputMeshHandle,
                  kOfxMeshAttribPoint,
                  kOfxMeshAttribPointPosition,
                  3,
                  kOfxMeshAttribTypeFloat,
                  NULL,
                  NULL);
  attributeDefine(inputMeshHandle,
                  kOfxMeshAttribCorner,
                  kOfxMeshAttribCornerPoint,
                  1,
                  kOfxMeshAttribTypeInt,
                  NULL,
                  NULL);
  attributeDefine(inputMeshHandle,
                  kOfxMeshAttribFace,
                  kOfxMeshAttribFaceSize,
                  1,
                  kOfxMeshAttribTypeInt,
                  NULL,
                  NULL);

  // Call internal callback before actually getting data
  OfxHost *host = input->host;
  BeforeMeshGetCbFunc beforeMeshGetCb = nullptr;
  if (nullptr != host) {
      MFX_ENSURE(propGetPointer(host->host, kOfxHostPropBeforeMeshGetCb, 0, (void**)&beforeMeshGetCb));
    if (nullptr != beforeMeshGetCb) {
        OfxStatus status = beforeMeshGetCb(host, inputMeshHandle);
        if (kOfxStatOK != status) {
            *meshHandle = nullptr;
            return status;
        }
    }
  }

  *meshHandle = inputMeshHandle;
  if (nullptr != propertySet) {
    *propertySet = inputMeshProperties;
  }

  return kOfxStatOK;
}

OfxStatus inputReleaseMesh(OfxMeshHandle meshHandle)
{
  // Call internal callback before actually releasing data
  OfxHost *host = nullptr;
  BeforeMeshReleaseCbFunc beforeMeshReleaseCb = nullptr;
  propGetPointer(&meshHandle->properties, kOfxMeshPropHostHandle, 0, (void **)&host);
  if (NULL != host) {
    propGetPointer(host->host, kOfxHostPropBeforeMeshReleaseCb, 0, (void **)&beforeMeshReleaseCb);
    if (NULL != beforeMeshReleaseCb) {
      beforeMeshReleaseCb(host, meshHandle);
    }
  }

  meshHandle->free_owned_data();

  propSetInt(&meshHandle->properties, kOfxMeshPropPointCount, 0, 0);
  propSetInt(&meshHandle->properties, kOfxMeshPropCornerCount, 0, 0);
  propSetInt(&meshHandle->properties, kOfxMeshPropFaceCount, 0, 0);

  return kOfxStatOK;
}

OfxStatus attributeDefine(OfxMeshHandle meshHandle,
                          const char *attachment,
                          const char *name,
                          int componentCount,
                          const char *type,
                          const char *semantic,
                          OfxPropertySetHandle *attributeHandle)
{
  if (componentCount < 1 || componentCount > 4) {
    return kOfxStatErrValue;
  }
  if (0 != strcmp(type, kOfxMeshAttribTypeInt) &&
      0 != strcmp(type, kOfxMeshAttribTypeFloat) &&
      0 != strcmp(type, kOfxMeshAttribTypeUByte)) {
    return kOfxStatErrValue;
  }

  if (NULL != semantic &&
      0 != strcmp(semantic, kOfxMeshAttribSemanticTextureCoordinate) &&
      0 != strcmp(semantic, kOfxMeshAttribSemanticNormal) &&
      0 != strcmp(semantic, kOfxMeshAttribSemanticColor) &&
      0 != strcmp(semantic, kOfxMeshAttribSemanticWeight)) {
    return kOfxStatErrValue;
  }

  AttributeAttachment intAttachment = mfxToInternalAttribAttachment(attachment);
  if (intAttachment == AttributeAttachment::Invalid) {
    return kOfxStatErrBadIndex;
  }

  int i = meshHandle->attributes.ensure({ intAttachment, name });

  OfxPropertySetStruct *attributeProperties = &meshHandle->attributes[i].properties;
  propSetPointer(attributeProperties, kOfxMeshAttribPropData, 0, NULL);
  propSetInt(attributeProperties, kOfxMeshAttribPropComponentCount, 0, componentCount);
  propSetString(attributeProperties, kOfxMeshAttribPropType, 0, type);
  propSetString(attributeProperties, kOfxMeshAttribPropSemantic, 0, semantic);
  propSetInt(attributeProperties, kOfxMeshAttribPropIsOwner, 0, 1);

  // Keep attribute count up-to-date
  propSetInt(&meshHandle->properties, kOfxMeshPropAttributeCount, 0, meshHandle->attributes.count());

  if (attributeHandle) {
    *attributeHandle = attributeProperties;
  }
  return kOfxStatOK;
}

OfxStatus meshGetAttributeByIndex(OfxMeshHandle meshHandle,
                                  int index,
                                  OfxPropertySetHandle *attributeHandle)
{
  if (index < 0 || index >= meshHandle->attributes.count()) {
    return kOfxStatErrBadIndex;
  }

  *attributeHandle = &meshHandle->attributes[index].properties;
  return kOfxStatOK;
}

OfxStatus meshGetAttribute(OfxMeshHandle meshHandle,
                           const char *attachment,
                           const char *name,
                           OfxPropertySetHandle *attributeHandle)
{
  AttributeAttachment intAttachment = mfxToInternalAttribAttachment(attachment);
  if (intAttachment == AttributeAttachment::Invalid) {
    return kOfxStatErrBadIndex;
  }

  int i = meshHandle->attributes.find({ intAttachment, name });

  if (i == -1) {
    return kOfxStatErrBadIndex;
  }
  else {
    *attributeHandle = &meshHandle->attributes[i].properties;
    return kOfxStatOK;
  }
}

OfxStatus meshGetPropertySet(OfxMeshHandle mesh, OfxPropertySetHandle *propHandle)
{
  *propHandle = &mesh->properties;
  return kOfxStatOK;
}

OfxStatus meshAlloc(OfxMeshHandle meshHandle)
{
  OfxStatus status;
  bool isAttributeMap = meshHandle->properties.find("OfxMeshPropIsAttributeMap") != -1;
  if (isAttributeMap) {
    int output_points_count, origin_points_pool_size;
    status = propGetInt(&meshHandle->properties, "OfxMeshPropOutputPointsCount", 0, &output_points_count);
    if (kOfxStatOK != status) {
      return status;
    }
    status = propGetInt(&meshHandle->properties, "OfxMeshPropOriginPointsTotalPoolSize", 0, &origin_points_pool_size);
    if (kOfxStatOK != status) {
      return status;
    }

    meshHandle->attributes.clear();
    int elementCount[3];

    attributeDefine(meshHandle,
                    kOfxMeshAttribMesh,
                    "OfxMeshAttribOriginPointsPoolSize",
                    1,
                    kOfxMeshAttribTypeInt,
                    NULL,
                    NULL);
    elementCount[0] = output_points_count;
    
    attributeDefine(meshHandle,
                    kOfxMeshAttribMesh,
                    "OfxMeshAttribOriginPointIndex",
                    1,
                    kOfxMeshAttribTypeInt,
                    NULL,
                    NULL);
    elementCount[1] = origin_points_pool_size;
   
    attributeDefine(meshHandle,
                    kOfxMeshAttribMesh,
                    "OfxMeshAttribOriginPointWeight",
                    1,
                    kOfxMeshAttribTypeFloat,
                    NULL,
                    NULL);
    elementCount[2] = origin_points_pool_size;

    for (int i = 0; i < meshHandle->attributes.count(); ++i) {
      OfxAttributeStruct &attribute = meshHandle->attributes[i];

      int count;
      status = propGetInt(&attribute.properties, kOfxMeshAttribPropComponentCount, 0, &count);
      if (kOfxStatOK != status) {
        return status;
      }

      char *type;
      status = propGetString(&attribute.properties, kOfxMeshAttribPropType, 0, &type);
      if (kOfxStatOK != status) {
        return status;
      }

      size_t byteSize = 0;
      if (0 == strcmp(type, kOfxMeshAttribTypeUByte)) {
        byteSize = sizeof(unsigned char);
      }
      else if (0 == strcmp(type, kOfxMeshAttribTypeInt)) {
        byteSize = sizeof(int);
      }
      else if (0 == strcmp(type, kOfxMeshAttribTypeFloat)) {
        byteSize = sizeof(float);
      }
      else {
        return kOfxStatErrBadHandle;
      }

      void *data = new char[byteSize * count * elementCount[i]];
      if (NULL == data) {
        return kOfxStatErrMemory;
      }

      status = propSetPointer(&attribute.properties, kOfxMeshAttribPropData, 0, data);
      if (kOfxStatOK != status) {
        return status;
      }

      status = propSetInt(
          &attribute.properties, kOfxMeshAttribPropStride, 0, (int)(byteSize * count));
      if (kOfxStatOK != status) {
        return status;
      }

      status = propSetInt(&attribute.properties, kOfxMeshAttribPropIsOwner, 0, 1);
      if (kOfxStatOK != status) {
        return status;
      }
    }

    return kOfxStatOK;
  }

  // Call internal callback before actually allocating data
  OfxHost *host = nullptr;
  BeforeMeshReleaseCbFunc beforeMeshAllocateCb = nullptr;
  propGetPointer(&meshHandle->properties, kOfxMeshPropHostHandle, 0, (void **)&host);
  if (NULL != host) {
    propGetPointer(host->host, kOfxHostPropBeforeMeshAllocateCb, 0, (void **)&beforeMeshAllocateCb);
    if (NULL != beforeMeshAllocateCb) {
      beforeMeshAllocateCb(host, meshHandle);
    }
  }

  // Get counts

  int elementCount[4];  // point, corner, face, mesh

  status = propGetInt(&meshHandle->properties, kOfxMeshPropPointCount, 0, &elementCount[0]);
  if (kOfxStatOK != status) {
    return status;
  }
  status = propGetInt(&meshHandle->properties, kOfxMeshPropCornerCount, 0, &elementCount[1]);
  if (kOfxStatOK != status) {
    return status;
  }
  status = propGetInt(&meshHandle->properties, kOfxMeshPropFaceCount, 0, &elementCount[2]);
  if (kOfxStatOK != status) {
    return status;
  }
  elementCount[3] = 1;

  // Allocate memory attributes

  for (int i = 0; i < meshHandle->attributes.count(); ++i) {
    OfxAttributeStruct & attribute = meshHandle->attributes[i];

    int is_owner;
    status = propGetInt(&attribute.properties, kOfxMeshAttribPropIsOwner, 0, &is_owner);
    if (kOfxStatOK != status) {
      return status;
    }

    // Don't allocate non-own attributes (i.e. attributes which are just proxy to externally
    // allocated buffers.
    if (!is_owner) {
      continue;
    }

    int count;
    status = propGetInt(&attribute.properties, kOfxMeshAttribPropComponentCount, 0, &count);
    if (kOfxStatOK != status) {
      return status;
    }

    char *type;
    status = propGetString(&attribute.properties, kOfxMeshAttribPropType, 0, &type);
    if (kOfxStatOK != status) {
      return status;
    }

    size_t byteSize = 0;
    if (0 == strcmp(type, kOfxMeshAttribTypeUByte)) {
      byteSize = sizeof(unsigned char);
    }
    else if (0 == strcmp(type, kOfxMeshAttribTypeInt)) {
      byteSize = sizeof(int);
    }
    else if (0 == strcmp(type, kOfxMeshAttribTypeFloat)) {
      byteSize = sizeof(float);
    }
    else {
      return kOfxStatErrBadHandle;
    }

    void *data = new char[byteSize * count * elementCount[(int)attribute.attachment()]];
    if (NULL == data) {
      return kOfxStatErrMemory;
    }

    status = propSetPointer(&attribute.properties, kOfxMeshAttribPropData, 0, data);
    if (kOfxStatOK != status) {
      return status;
    }

    status = propSetInt(
        &attribute.properties, kOfxMeshAttribPropStride, 0, (int)(byteSize * count));
    if (kOfxStatOK != status) {
      return status;
    }

    status = propSetInt(&attribute.properties, kOfxMeshAttribPropIsOwner, 0, 1);
    if (kOfxStatOK != status) {
      return status;
    }
  }

  return kOfxStatOK;
}

int ofxAbort(OfxMeshEffectHandle meshEffect)
{
  (void)meshEffect;
  return 0;
}
