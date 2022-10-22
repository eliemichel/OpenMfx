/*
 * Copyright 2019 Elie Michel
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __MFX_OFX_UTIL_H__
#define __MFX_OFX_UTIL_H__

#include "ofxCore.h"

#ifdef __cplusplus
extern "C" {
#endif

const char *getOfxStateName(OfxStatus status);

#ifdef __cplusplus
}
#endif

#endif // __MFX_OFX_UTIL_H__
