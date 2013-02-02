/* Reversity Network Library © 2004-2008 Reversity Studios (www.reversity.org)
* This contents may be used and/or copied only with the written permission or
* terms and conditions stipulated in agreement/contract.
-----------------------------------------------------------------------------
Authors: am!go
*/

#pragma once

#include <winsock.h>
#include "output.h"

namespace RNL
{
	
	class CController
	{
	public:
		CController();
		~CController();
		inline bool IsInitialized() { return m_bInit; };
		//const COutput* Output();
		bool Init(COutput *useroutput = 0);
		void OutputMsg(eOutputMsg type, const char* text, ...);
	private:
		bool m_bInit;
		COutput *m_pOutput;

		WORD m_wVersion;
		WSADATA m_sData;
	};

	

}