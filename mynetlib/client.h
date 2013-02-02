/* Reversity Network Library © 2004-2008 Reversity Studios (www.reversity.org)
* This contents may be used and/or copied only with the written permission or
* terms and conditions stipulated in agreement/contract.
-----------------------------------------------------------------------------
Authors: am!go
*/

#pragma once

#include "socket.h"

namespace RNL
{

	class CClient : public CSocket
	{
	private:
		bool m_bRun;

		

	public:
		CServer(RNL::eProtocol protocol, unsigned int port, CController *controller);
		~CServer();

		//friend class CLoopThread;

	};

}