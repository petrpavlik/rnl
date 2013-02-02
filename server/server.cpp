// server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <mynetlib/rnl.h>
#include <windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	RNL::CController *controller = new RNL::CController;
	controller->Init();
	RNL::CServer *server = new RNL::CServer(RNL::PROT_TCP, 3000, controller);
	system("pause");
	delete server;
	delete controller;
	return 0;
}

