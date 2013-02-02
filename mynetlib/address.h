/* Reversity Network Library © 2004-2008 Reversity Studios (www.reversity.org)
* This contents may be used and/or copied only with the written permission or
* terms and conditions stipulated in agreement/contract.
-----------------------------------------------------------------------------
Authors: am!go
*/

#pragma once

#include <winsock.h>

namespace RNL
{

	class CAddress
	{
	public:
		CAddress(const char *ip);
		inline void* GetInternalAddress() { return m_sHost; };
	private:
		hostent *m_sHost;
	};

}