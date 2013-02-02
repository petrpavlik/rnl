/* Reversity Network Library © 2004-2008 Reversity Studios (www.reversity.org)
* This contents may be used and/or copied only with the written permission or
* terms and conditions stipulated in agreement/contract.
-----------------------------------------------------------------------------
Authors: am!go
*/

#pragma once

#include <stdio.h>

namespace RNL
{

	enum eOutputMsg
	{
		OUTMSG_INFO,
		OUTMSG_ERR,
		OUTMSG_DBG
	};

	class COutput
	{
	public:
		virtual void OutputMsg(eOutputMsg msgtype, const char *msg)
		{
			if(msgtype == OUTMSG_INFO) printf("INFO: %s\n", msg);
			else if(msgtype == OUTMSG_ERR) printf("ERROR: %s\n", msg);
			else if(msgtype == OUTMSG_DBG) printf("DEBUG: %s\n", msg);
		}
	};

}