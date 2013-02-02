// client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <mynetlib/rnl.h>
#include <windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	RNL::CController *controller = new RNL::CController;
	controller->Init();
	RNL::CSocket *socket = new RNL::CSocket;
	socket->InitClient(RNL::PROT_TCP, RNL::CAddress("127.0.0.1"), 3000, controller);
	system("pause");
	delete socket;
	delete controller;
	return 0;
}
