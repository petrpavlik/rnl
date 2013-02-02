/* Reversity Network Library © 2004-2008 Reversity Studios (www.reversity.org)
* This contents may be used and/or copied only with the written permission or
* terms and conditions stipulated in agreement/contract.
-----------------------------------------------------------------------------
Authors: am!go
*/

#pragma once

#include "controller.h"

namespace RNL
{
	
	COutput *g_pOutput = 0;
	
	CController::CController()
	{
	
	}

	bool CController::Init(COutput *useroutput /* = 0 */)
	{
		if(useroutput) m_pOutput = useroutput;
		else m_pOutput = new COutput;

		g_pOutput = m_pOutput;

		m_wVersion = MAKEWORD(2,2);
		if(WSAStartup(m_wVersion, &m_sData) != 0)
		{
			//m_pOutput->OutputMsg(OUTMSG_ERR, "Sockets initializing error!");    
			m_bInit = false;
			return false;
		}

		m_pOutput->OutputMsg(OUTMSG_INFO, "Controller ok.");
		m_bInit = true;
		return true;
		printf("yes!");
	}

	CController::~CController()
	{
		if(m_pOutput) delete m_pOutput;
		g_pOutput = 0;
		WSACleanup();
	}

	void CController::OutputMsg(eOutputMsg type, const char* text, ...)
	{
		char buffer[1024];
		va_list argList;
		va_start(argList, text);
		vsprintf_s(buffer,text,argList);
		va_end(argList);

		m_pOutput->OutputMsg(type, buffer);
	}

}