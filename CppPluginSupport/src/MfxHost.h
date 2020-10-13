#pragma once

#include "ofxCore.h"
#include "ofxMeshEffect.h"

class MfxHost
{
public:
    const OfxMeshEffectSuiteV1* meshEffectSuite = nullptr;
    const OfxPropertySuiteV1* propertySuite = nullptr;
    const OfxParameterSuiteV1* parameterSuite = nullptr;
};

