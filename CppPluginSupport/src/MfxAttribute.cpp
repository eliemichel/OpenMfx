#include "MfxAttribute.h"
#include "macros.h"

#include <cstring>

MfxAttribute::MfxAttribute(const MfxHost& host, OfxPropertySetHandle properties)
	: MfxBase(host)
	, m_properties(properties)
{}

MfxAttributeType MfxAttribute::mfxAttrAsEnum(const char* mfxType)
{
    if (0 == strcmp(mfxType, kOfxMeshAttribTypeUByte)) {
        return MfxAttributeType::UByte;
    }
    if (0 == strcmp(mfxType, kOfxMeshAttribTypeInt)) {
        return MfxAttributeType::Int;
    }
    if (0 == strcmp(mfxType, kOfxMeshAttribTypeFloat)) {
        return MfxAttributeType::Float;
    }
    printf("Warning: inknown attribute type: %s\n", mfxType);
    return MfxAttributeType::Unknown;
}

OfxStatus MfxAttribute::copyAttributeData(MfxAttributeProps& destination, const MfxAttributeProps& source, int start, int count)
{
    // TODO: use at least OpenMP
    int componentCount =
        source.componentCount < destination.componentCount
        ? source.componentCount
        : destination.componentCount;

    if (source.type == destination.type)
    {
        size_t componentByteSize = 0;
        switch (source.type)
        {
        case MfxAttributeType::UByte:
            componentByteSize = sizeof(unsigned char);
            break;
        case MfxAttributeType::Int:
            componentByteSize = sizeof(int);
            break;
        case MfxAttributeType::Float:
            componentByteSize = sizeof(float);
            break;
        default:
            printf("Error: unsupported attribute type: %d\n", source.type);
            return kOfxStatErrFatal;
        }

        for (int i = 0; i < count; ++i) {
            const void* src = (void*)&source.data[(start + i) * source.stride];
            void* dst = (void*)&destination.data[(start + i) * destination.stride];
            memcpy(dst, src, componentCount * componentByteSize);
        }
        return kOfxStatOK;
    }

    switch (destination.type) {
    case MfxAttributeType::Float:
        switch (source.type) {
        case MfxAttributeType::UByte:
            for (int i = 0; i < count; ++i) {
                const unsigned char* src = (unsigned char*)&source.data[(start + i) * source.stride];
                float* dst = (float*)&destination.data[(start + i) * destination.stride];
                for (int k = 0; k < componentCount; ++k)
                {
                    dst[k] = (float)src[k] / 255.0f;
                }
            }
            return kOfxStatOK;
            break;
        }
        break;
    }
    printf("Warning: unsupported input/output type combinason in copyAttribute: %d -> %d\n", source.type, destination.type);
    return kOfxStatErrUnsupported;
}

//-----------------------------------------------------------------------------

void MfxAttribute::FetchProperties(MfxAttributeProps& props)
{
    char* type;
    MFX_ENSURE(propertySuite->propGetString(m_properties, kOfxMeshAttribPropType, 0, &type));
    MFX_ENSURE(propertySuite->propGetInt(m_properties, kOfxMeshAttribPropStride, 0, &props.stride));
    MFX_ENSURE(propertySuite->propGetInt(m_properties, kOfxMeshAttribPropComponentCount, 0, &props.componentCount));
    MFX_ENSURE(propertySuite->propGetPointer(m_properties, kOfxMeshAttribPropData, 0, (void**)&props.data));
    props.type = mfxAttrAsEnum(type);
}

void MfxAttribute::CopyFrom(MfxAttribute& other, int start, int count)
{
    MfxAttributeProps sourceProps, destinationProps;
    other.FetchProperties(sourceProps);
    FetchProperties(destinationProps);
    copyAttributeData(destinationProps, sourceProps, start, count);
}
