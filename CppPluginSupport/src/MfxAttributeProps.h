#pragma once

enum class MfxAttributeType {
    Unknown = -1,
    UByte,
    Int,
    Float,
};

/**
 * Mfx*Props classes are a little different: for caching and convenience, they
 * store some data and care must be taken not to copy it around too much
 * (though it does not directly store the attribute data, only metadata).
 */
struct MfxAttributeProps
{
    MfxAttributeType type;
    int stride;
    int componentCount;
    char* data;
};
