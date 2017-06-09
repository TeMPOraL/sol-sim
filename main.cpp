/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 31.05.2004
Last Revised:	31.05.2004

Notes:
	
*/

/*
	Main file for Sol Project.
*/

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>

#include "Sol.h"


//=============================================
//Function: WinMain()
//
//Programmer: Jacek "TeMPOraL" Zlydach
//Last Revised: 31.05.2004
//
//Returns: int - error code
//Parameters: Application Instance, command line parameters, window display options
//Description:
//	Entry Point.
//=============================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	new Sol::CApplication();	//create application

	Sol::CApplication::GetSingleton().Init(hInstance, lpCmdLine);	//initialize application

	
	Sol::CApplication::GetSingleton().Execute();	//run application

	Sol::CApplication::GetSingleton().DeInit();	//deinitialize application

	delete Sol::CApplication::GetSingletonPtr();	//delete application
	return 0;
}