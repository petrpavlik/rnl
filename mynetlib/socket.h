/* Reversity Network Library © 2004-2008 Reversity Studios (www.reversity.org)
* This contents may be used and/or copied only with the written permission or
* terms and conditions stipulated in agreement/contract.
-----------------------------------------------------------------------------
Authors: am!go
*/

#pragma once

#include "controller.h"
#include "address.h"

namespace RNL
{

	enum eProtocol
	{
		PROT_TCP,
		PROT_UDP
	};

	enum eRole
	{
		ROLE_CLIENT,
		ROLE_SERVER
	};

	#define BUFSIZE 1000

	class CSocket
	{
	protected:
		bool m_bInit;
		eRole m_eRole;
		eProtocol m_eProtocol;
		CController *m_pController;

		WORD m_wVersion;
		WSADATA m_sData;
		unsigned int m_uiPort;
		SOCKET m_socket;
		sockaddr_in m_sSockName;

		hostent *m_sHost;

		BYTE m_buffer[BUFSIZE];

	public:
		CSocket();
		~CSocket();
		bool InitServer(eProtocol protocol, unsigned int port, CController *controller);
		bool InitClient(eProtocol protocol, CAddress &address, unsigned int port, CController *controller);
		void Test();
		void Send(SOCKET s);
		void Recieve(SOCKET s);
	};

}