#pragma once

enum class MfxAttributeType {
    Unknown = -1,
    UByte,
    Int,
    Float,
};

enum class MfxAttributeAttachment {
    Unknown = -1,
    Point,
    Vertex,
    Face,
    Mesh,
};

enum class MfxAttributeSemantic {
    Unknown = -1,
    None,
    TextureCoordinate,
    Normal,
    Color,
    Weight,
};

/**
 * Mfx*Props classes are a little different: for caching and convenience, they
 * store some data and care must be taken not to copy it around too much
 * (though it does not directly store the attribute data, only metadata).
 */
struct MfxAttributeProps
{
    MfxAttributeProps() : type(MfxAttributeType::Unknown), stride(0), componentCount(0), data(NULL), isOwner(false) {}

    MfxAttributeType type;
    int stride;
    int componentCount;
    char* data;
    bool isOwner;
};
