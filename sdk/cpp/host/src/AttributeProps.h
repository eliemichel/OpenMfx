#pragma once

#include "AttributeEnums.h"

#include <ofxProperty.h>
#include <ofxMeshEffect.h>

// This file is close to MfxAttributeProps but the Plugin SDK and the Host SDK
// follow different naming conventions (maybe this should change)

namespace OpenMfx {

struct AttributeProps
{
    AttributeProps()
        : type(AttributeType::Unknown)
        , stride(0)
        , componentCount(0)
        , data(nullptr)
        , isOwner(false)
    {}

    AttributeType type;
    int stride;
    int componentCount;
    char* data;
    bool isOwner;

    // These are for hosts only
    OfxStatus fetchProperties(const OfxPropertySuiteV1* propertySuite, OfxPropertySetHandle properties);
    OfxStatus fetchProperties(const OfxPropertySuiteV1* propertySuite, const OfxMeshEffectSuiteV1 *meshEffectSuite, OfxMeshHandle mesh, const char *attachment, const char *name);
    OfxStatus setProperties(const OfxPropertySuiteV1* propertySuite, OfxPropertySetHandle properties) const;

    template<typename T> inline T *at(int index) {
      return reinterpret_cast<T *>(data + static_cast<size_t>(index) * static_cast<size_t>(stride));
    }

    template<typename T> inline const T *at(int index) const {
      return reinterpret_cast<const T *>(data + static_cast<size_t>(index) * static_cast<size_t>(stride));
    }
};

} // namespace OpenMfx

