/* Reversity Network Library © 2004-2008 Reversity Studios (www.reversity.org)
* This contents may be used and/or copied only with the written permission or
* terms and conditions stipulated in agreement/contract.
-----------------------------------------------------------------------------
Authors: am!go
*/

#include "socket.h"

namespace RNL
{
	
	extern COutput *g_pOutput;
	
	CSocket::CSocket()
	{
		g_pOutput->OutputMsg(OUTMSG_INFO, "socket"); 
		m_pController = 0;
	}

	CSocket::~CSocket()
	{
		m_pController = 0;
		closesocket(m_socket); 
	}
	
	bool CSocket::InitServer(RNL::eProtocol protocol, unsigned int port, CController *controller)
	{
		m_uiPort = port;
		m_pController = controller;

		if ((m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
		{
			g_pOutput->OutputMsg(OUTMSG_ERR, "Cannot create socket!"); 
			return false;
		}

		m_sSockName.sin_family = AF_INET;
		m_sSockName.sin_port = htons(m_uiPort);
		m_sSockName.sin_addr.s_addr = INADDR_ANY;

		if (bind(m_socket, (sockaddr *)&m_sSockName, sizeof(m_sSockName)) == SOCKET_ERROR)
		{
			g_pOutput->OutputMsg(OUTMSG_ERR, "Socket naming error!"); 
			return false;
		}

		if (listen(m_socket, 10) == SOCKET_ERROR)	//TODO: Allow the users to set this number.
		{
			g_pOutput->OutputMsg(OUTMSG_ERR, "Que creating error!");
			return false;
		}

		m_bInit = true;
		return true;
	}

	bool CSocket::InitClient(eProtocol protocol, CAddress &address, unsigned int port, CController *controller)
	{
		m_uiPort = port;
		m_pController = controller;

		m_sHost = (hostent*)address.GetInternalAddress();
		if (m_sHost == NULL)
		{
			g_pOutput->OutputMsg(OUTMSG_ERR, "Invalid address!");
			return false;
		}
		
		if ((m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
		{
			g_pOutput->OutputMsg(OUTMSG_ERR, "Cannot create socket!");
			return false;
		}

		m_sSockName.sin_family = AF_INET;
		m_sSockName.sin_port = htons(m_uiPort);
		m_sSockName.sin_addr.s_addr = INADDR_ANY;
		memcpy(&(m_sSockName.sin_addr), m_sHost->h_addr, m_sHost->h_length);

		if (connect(m_socket, (sockaddr *)&m_sSockName, sizeof(m_sSockName)) == -1)
		{
			g_pOutput->OutputMsg(OUTMSG_ERR, "Cannot connect!");
			return false;
		}

		g_pOutput->OutputMsg(OUTMSG_INFO, "Connected;");
		m_bInit = true;
		return true;
	}

	void CSocket::Test()
	{
		g_pOutput->OutputMsg(OUTMSG_INFO, "Waiting for connection...\n");
		sockaddr_in clientInfo;
		int addrlen = sizeof(clientInfo);
		SOCKET client = accept(m_socket, (sockaddr*)&clientInfo, &addrlen);

		if (client == INVALID_SOCKET)
		{
			g_pOutput->OutputMsg(OUTMSG_ERR, "Client connection error!\n");
			return;
		}

		char msg[512];
		sprintf_s(msg, "New connection with address %s.\n", inet_ntoa((in_addr)clientInfo.sin_addr));
		g_pOutput->OutputMsg(OUTMSG_INFO, msg);

		g_pOutput->OutputMsg(OUTMSG_INFO, "Shooting down.\n");

		closesocket(client);
	}

	void CSocket::Send(SOCKET s)
	{
		char *msg = "Hi there!";
		int remlen = strlen(msg);
		int sizesent = 0;
		while(remlen > 0)
		{
			sizesent = send(s, msg, remlen, 0);
			if(sizesent == SOCKET_ERROR)
			{
				m_pController->OutputMsg(OUTMSG_ERR, "Packet sending error!");
				return;
			}
			remlen -= sizesent;
		}
	}

	void CSocket::Recieve(SOCKET s)
	{

	}

}