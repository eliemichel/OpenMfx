#include "MfxInput.h"
#include "macros.h"

MfxInput::MfxInput(const MfxHost& host, OfxMeshInputHandle input)
	: MfxBase(host)
	, m_input(input)
{}

//-----------------------------------------------------------------------------

MfxMesh MfxInput::GetMesh()
{
	OfxTime time = 0;
	OfxMeshHandle mesh;
	OfxPropertySetHandle meshProps;
	MFX_ENSURE(meshEffectSuite->inputGetMesh(m_input, time, &mesh, &meshProps));
	return MfxMesh(host(), mesh, meshProps);
}
