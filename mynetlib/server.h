/* Reversity Network Library © 2004-2008 Reversity Studios (www.reversity.org)
* This contents may be used and/or copied only with the written permission or
* terms and conditions stipulated in agreement/contract.
-----------------------------------------------------------------------------
Authors: am!go
*/

#pragma once

#include "socket.h"
#include <vector>
#include <SFML/System.hpp>

namespace RNL
{
	
	class CServer : public CSocket
	{
	private:
		bool m_bRun;
		
		struct sConnection
		{
			sockaddr_in clientInfo;
			SOCKET client;
		};

		std::vector<sConnection> m_connections;

		class CLoopThread : public sf::Thread
		{
		private :
			virtual void Run();
		public:
			CServer *m_server;
		};

		CLoopThread m_thread;

	public:
		CServer(RNL::eProtocol protocol, unsigned int port, CController *controller);
		~CServer();

		//friend class CLoopThread;
		
	};

}