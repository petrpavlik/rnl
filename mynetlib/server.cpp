/* Reversity Network Library © 2004-2008 Reversity Studios (www.reversity.org)
* This contents may be used and/or copied only with the written permission or
* terms and conditions stipulated in agreement/contract.
-----------------------------------------------------------------------------
Authors: am!go
*/

#include "server.h"

namespace RNL
{

	extern COutput *g_pOutput;

	CServer::CServer(RNL::eProtocol protocol, unsigned int port, CController *controller)
	{
		m_thread.m_server = this;
		if(!InitServer(protocol, port, controller)) return;
		//ioctl(sd, FIOSNBIO, &arg);
		int nonblocking = 1;
		ioctlsocket(m_socket, FIONBIO, (unsigned long*) &nonblocking);
		m_bRun = true;
		m_thread.Launch();
	}

	CServer::~CServer()
	{
		g_pOutput->OutputMsg(OUTMSG_INFO, "Releasing remaining connections.");
		for(unsigned int i=0; i<m_connections.size(); i++) closesocket(m_connections[i].client);
		m_bRun = false;
	}

	void CServer::CLoopThread::Run()
	{
		while(m_server->m_bRun)
		{

			fd_set set;
			FD_ZERO(&set);
			FD_SET(m_server->m_socket, &set);
			TIMEVAL v; //no timeout, direct feedback
			v.tv_sec = 0;
			v.tv_usec = 500000;
			unsigned int result = select(0, 0,0, &set, &v);

			//temporary recv
			for(unsigned int i=0; i<m_server->m_connections.size(); i++)
			{
				int size = recv(m_server->m_connections[i].client, (char*)m_server->m_buffer, BUFSIZE - 1, 0);
				if(size == 0)
				{
					m_server->m_pController->OutputMsg(OUTMSG_INFO, "client disconnected");
				}
			}
			
			//g_pOutput->OutputMsg(OUTMSG_INFO, "Waiting for connection...\n");
			m_server->m_pController->OutputMsg(OUTMSG_INFO, "Waiting for connection...");

			sConnection newconnection;

			int addrlen = sizeof(newconnection.clientInfo);
			newconnection.client = accept(m_server->m_socket, (sockaddr*)&newconnection.clientInfo, &addrlen);

			if (newconnection.client == -1)  //wouldblock
			{
				continue;
			}

			if (newconnection.client == INVALID_SOCKET)
			{
				g_pOutput->OutputMsg(OUTMSG_ERR, "Client connection error!\n");
				return;
			}

			char msg[512];
			sprintf_s(msg, "New connection with address %s.\n", inet_ntoa((in_addr)newconnection.clientInfo.sin_addr));
			g_pOutput->OutputMsg(OUTMSG_INFO, msg);

			m_server->m_connections.push_back(newconnection);

		}

	}
}