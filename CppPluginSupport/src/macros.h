#pragma once

#include "MfxSuiteException.h"

#include <array>

// Utility macro to wrap suite calls

#define MFX_CHECK(call) \
status = call; \
if (kOfxStatOK != status) { \
  printf("[MFX] Suite method call '" #call "' returned status %d (%s)\n", status, getOfxStateName(status)); \
}

// like MFX_CHECK but throw an exception if status is not OK
#define MFX_ENSURE(call) { \
	OfxStatus status = this->host().call; \
	if (kOfxStatOK != status) { \
		throw MfxSuiteException(status, #call); \
	} \
}

// Typedefs for value types

using int2 = std::array<int,2>;
using int3 = std::array<int,3>;
using double2 = std::array<double,2>;
using double3 = std::array<double,3>;
