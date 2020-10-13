#include "MfxInputDef.h"
#include "macros.h"

MfxInputDef::MfxInputDef(const MfxHost& host, OfxPropertySetHandle properties)
	: MfxBase(host)
	, m_properties(properties)
{}

//-----------------------------------------------------------------------------

MfxInputDef & MfxInputDef::Label(const char *label)
{
	MFX_ENSURE(propertySuite->propSetString(m_properties, kOfxPropLabel, 0, label));
	return *this;
}
