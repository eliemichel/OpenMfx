#pragma once

#include "MfxHost.h"

/**
 * Provide basic access to host's suites, use for any class but for MfxPlugin
 * (which must own the MfxHost, not just a reference to it).
 */
class MfxBase {
protected:
	MfxBase(const MfxHost& host) : m_host(host) {}

	const MfxHost& host() const { return m_host; }

private:
	const MfxHost& m_host;
};

