#pragma once

#include <ofxProperty.h>
#include <ofxMeshEffect.h>

// This file is close to MfxAttributeEnums but the Plugin SDK and the Host SDK
// follow different naming conventions (maybe this should change)

namespace OpenMfx {

enum class AttributeType {
    Unknown = -1,
    UByte, // kOfxMeshAttribTypeUByte
    Int,   // kOfxMeshAttribTypeInt
    Float, // kOfxMeshAttribTypeFloat
};

enum class AttributeAttachment {
    Invalid = -1,
    Point,  // kOfxMeshAttribPoint
    Corner, // kOfxMeshAttribCorner
    Face,   // kOfxMeshAttribFace
    Mesh,   // kOfxMeshAttribMesh
};

enum class AttributeSemantic {
    None = -1,
    TextureCoordinate, // kOfxMeshAttribSemanticTextureCoordinate
    Normal,            // kOfxMeshAttribSemanticNormal
    Color,             // kOfxMeshAttribSemanticColor
    Weight,            // kOfxMeshAttribSemanticWeight
};

/**
 * Convert a type string from MeshEffect API to its local enum counterpart
 */
AttributeType attributeTypeAsEnum(const char* mfxType);

/**
 * Convert local typestring enum to a type string from MeshEffect API
 */
const char* attributeTypeAsString(AttributeType type);

/**
 * Return the size in bytes of a type
 */
int byteSizeOf(AttributeType type);

/**
 * Convert an attachment string from MeshEffect API to its local enum counterpart
 */
AttributeAttachment attributeAttachmentAsEnum(const char* mfxAttachment);

/**
 * Convert local attachment enum to an attachment string from MeshEffect API
 */
const char* attributeAttachmentAsString(AttributeAttachment attachment);

/**
 * Convert a semantic string from MeshEffect API to its local enum counterpart
 */
AttributeSemantic attributeSemanticAsEnum(const char* mfxSemantic);

/**
 * Convert local semantic enum to a semantic string from MeshEffect API
 */
const char* attributeSemanticAsString(AttributeSemantic semantic);

} // namespace OpenMfx

