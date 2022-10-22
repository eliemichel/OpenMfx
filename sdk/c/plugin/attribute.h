#ifndef __MFX_SDK_PLUGIN_ATTRIBUTE__
#define __MFX_SDK_PLUGIN_ATTRIBUTE__

#include <ofxCore.h>
#include <ofxMeshEffect.h>
#include <ofxProperty.h>

typedef struct MfxAttributeProperties {
  int component_count;
  char *type;
  char *semantic;
  void *data;
  size_t byte_stride;
  int is_owner;
} MfxAttributeProperties;

OfxStatus mfxPullAttributeProperties(
    const OfxPropertySuiteV1 *propertySuite,
    const OfxPropertySetHandle attrib,
    MfxAttributeProperties *props);

OfxStatus mfxPushAttributeProperties(
    const OfxPropertySuiteV1 *propertySuite,
    OfxPropertySetHandle attrib,
    const MfxAttributeProperties *props);

#endif // __MFX_SDK_PLUGIN_ATTRIBUTE__
