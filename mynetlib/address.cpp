/* Reversity Network Library © 2004-2008 Reversity Studios (www.reversity.org)
* This contents may be used and/or copied only with the written permission or
* terms and conditions stipulated in agreement/contract.
-----------------------------------------------------------------------------
Authors: am!go
*/

#include "address.h"
#include <stdio.h>


namespace RNL
{

	CAddress::CAddress(const char *ip)
	{
		if(!ip) m_sHost = gethostbyname("127.0.0.1");
		else m_sHost = gethostbyname(ip);
		if (m_sHost == NULL)
		{
			printf("Invalid address!\n");
			return;
		}
	};

}