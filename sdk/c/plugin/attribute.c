#include "attribute.h"
#include "../common/common.h" // for MFX_ENSURE

OfxStatus mfxPullAttributeProperties(
    const OfxPropertySuiteV1 *propertySuite,
    const OfxPropertySetHandle attrib,
    MfxAttributeProperties *props)
{
    MFX_ENSURE(propertySuite->propGetInt(attrib, kOfxMeshAttribPropComponentCount, 0, &props->component_count));
    MFX_ENSURE(propertySuite->propGetString(attrib, kOfxMeshAttribPropType, 0, &props->type));
    MFX_ENSURE(propertySuite->propGetString(attrib, kOfxMeshAttribPropSemantic, 0, &props->semantic));
    MFX_ENSURE(propertySuite->propGetPointer(attrib, kOfxMeshAttribPropData, 0, &props->data));

    int byte_stride;
    MFX_ENSURE(propertySuite->propGetInt(attrib, kOfxMeshAttribPropStride, 0, &byte_stride));
    props->byte_stride = (size_t)byte_stride;

    MFX_ENSURE(propertySuite->propGetInt(attrib, kOfxMeshAttribPropIsOwner, 0, &props->is_owner));
    return kOfxStatOK;
}

OfxStatus mfxPushAttributeProperties(
    const OfxPropertySuiteV1 *propertySuite,
    OfxPropertySetHandle attrib,
    const MfxAttributeProperties *props)
{
    MFX_ENSURE(propertySuite->propSetInt(attrib, kOfxMeshAttribPropComponentCount, 0, props->component_count));
    MFX_ENSURE(propertySuite->propSetString(attrib, kOfxMeshAttribPropType, 0, props->type));
    MFX_ENSURE(propertySuite->propSetString(attrib, kOfxMeshAttribPropSemantic, 0, props->semantic));
    MFX_ENSURE(propertySuite->propSetPointer(attrib, kOfxMeshAttribPropData, 0, props->data));
    MFX_ENSURE(propertySuite->propSetInt(attrib, kOfxMeshAttribPropStride, 0, (int)props->byte_stride));
    MFX_ENSURE(propertySuite->propSetInt(attrib, kOfxMeshAttribPropIsOwner, 0, props->is_owner));
    return kOfxStatOK;
}
