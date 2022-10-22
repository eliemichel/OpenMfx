#ifndef __MFX_SDK_PLUGIN_MESH__
#define __MFX_SDK_PLUGIN_MESH__

#include <ofxCore.h>
#include <ofxMeshEffect.h>
#include <ofxProperty.h>

typedef struct MfxMeshProperties {
  int point_count;
  int corner_count;
  int face_count;
  int constant_face_size;
} MfxMeshProperties;

OfxStatus mfxPullMeshProperties(
    const OfxPropertySuiteV1 *propertySuite,
    const OfxMeshEffectSuiteV1 *meshEffectSuite,
    const OfxMeshHandle mesh,
    MfxMeshProperties *props);

OfxStatus mfxPushMeshProperties(
    const OfxPropertySuiteV1 *propertySuite,
    const OfxMeshEffectSuiteV1 *meshEffectSuite,
    OfxMeshHandle mesh,
    const MfxMeshProperties *props);

#endif // __MFX_SDK_PLUGIN_MESH__
