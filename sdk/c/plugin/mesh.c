#include "mesh.h"
#include "../common/common.h" // for MFX_ENSURE

OfxStatus mfxPullMeshProperties(
    const OfxPropertySuiteV1 *propertySuite,
    const OfxMeshEffectSuiteV1 *meshEffectSuite,
    const OfxMeshHandle mesh,
    MfxMeshProperties *props)
{
    OfxPropertySetHandle propHandle;
    meshEffectSuite->meshGetPropertySet(mesh, &propHandle);
    MFX_ENSURE(propertySuite->propGetInt(propHandle, kOfxMeshPropPointCount, 0, &props->point_count));
    MFX_ENSURE(propertySuite->propGetInt(propHandle, kOfxMeshPropCornerCount, 0, &props->corner_count));
    MFX_ENSURE(propertySuite->propGetInt(propHandle, kOfxMeshPropFaceCount, 0, &props->face_count));
    MFX_ENSURE(propertySuite->propGetInt(propHandle, kOfxMeshPropConstantFaceSize, 0, &props->constant_face_size));
    return kOfxStatOK;
}

OfxStatus mfxPushMeshProperties(
    const OfxPropertySuiteV1 *propertySuite,
    const OfxMeshEffectSuiteV1 *meshEffectSuite,
    OfxMeshHandle mesh,
    const MfxMeshProperties *props)
{
    OfxPropertySetHandle propHandle;
    meshEffectSuite->meshGetPropertySet(mesh, &propHandle);
    MFX_ENSURE(propertySuite->propSetInt(propHandle, kOfxMeshPropPointCount, 0, props->point_count));
    MFX_ENSURE(propertySuite->propSetInt(propHandle, kOfxMeshPropCornerCount, 0, props->corner_count));
    MFX_ENSURE(propertySuite->propSetInt(propHandle, kOfxMeshPropFaceCount, 0, props->face_count));
    MFX_ENSURE(propertySuite->propSetInt(propHandle, kOfxMeshPropConstantFaceSize, 0, props->constant_face_size));
    return kOfxStatOK;
}
