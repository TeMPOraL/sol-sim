/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 31.05.2004
Last Revised:	03.06.2004

This is an Implementation File:

Notes:
	
*/


/*
  
*/

#include "Log.h"
#include "Application.h"
#include "Strings_System.h"
#include "Timer.h"
#include "TextureManager.h"

namespace Sol
{

	//=============================================
	//Function: Init
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: true on success, false on failure
	//Parameters: none
	//Description:
	//	Initializes main application class
	//=============================================
	bool CApplication::Init(HINSTANCE _appInstance, LPSTR params)
	{
		log.Open("log.Sol.txt");

		log <<"CApplication::Init() - Initializing Application\n";

		log <<"->Initializing System String Table\n";
		systemStrings.Init("system.tbl");

		log <<"->Initializing Main Window\n";
		if(!window.Init(800,600,32,true))	//initialize window
		{
			log.Error("CApplication::Init() - Error initializing Application Window");
			Quit();
		}

		log <<"->Initializing Application State Manager\n";
		if(!appManager.Init())
		{
			log.Error("CApplication::Init() - Error initializing Application State Manager");
			Quit();
		}

		log <<"->Initializing High Resolution Timer\n";
		if(!timer.Init())
		{
			log.Error("CApplication::Init() - Error initializing High Resolution Timer");
			MessageBox(NULL,(systemStrings.GetString(STRING_SYS_ERROR_HI_RES_TIMER_NOT_AVAIBLE)).c_str(),(systemStrings.GetString(STRING_SYS_GAMENAME)).c_str(),MB_OK|MB_ICONSTOP);
			Quit();
		}

		log <<"->Initializing Texture Manager\n";
		textureManager.Init();

		return true;
	}

	//=============================================
	//Function: DeInit
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: true on success, false on failure
	//Parameters: none
	//Description:
	//	DeInitializes main application class
	//=============================================
	bool CApplication::DeInit()
	{
		log <<"CApplication::DeInit() - Deinitializing Application\n";

		log <<"->Deinitializing Texture Manager\n";
		textureManager.DeInit();

		log <<"->Deinitializing Application State Manager\n";
		appManager.DeInit();

		log <<"->Deinitializing Main Window\n";
		window.DeInit();

		log <<"->Deinitializing System String Table\n";
		systemStrings.DeInit();
		return true;
	}

	//=============================================
	//Function: Execute
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 03.06.2004
	//
	//Returns: true on success, false on failure
	//Parameters: none
	//Description:
	//	Executes application
	//=============================================
	bool CApplication::Execute()
	{
		log <<"\t\t..::Starting Application Execution::..\n";
		MSG msg;
		appManager.SetState(AS_SOLARSYSTEM);
		
		while(true)
		{
			if (PeekMessage(&msg,/*gameWindow.GetHWND()*/NULL,0,0,PM_REMOVE))
			{
			
				if (msg.message==WM_QUIT)
				{
					log <<"WM_QUIT Message recieved\n";
					break;
				}
				else
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			
			}
			else			
			{
				if (bShouldQuit)
				{
					log<<"Breaking main loop (bShouldQuit == true)!\n";
					break;
				}
				else
				{
					//inputSystem.Update();	//update input
					appManager.Update(timer.GetElapsedSeconds());	//update game
					SwapBuffers(window.GetDC());	//swap GL buffers
				}
			}
		}

		log <<"\t\t..::End of Game Execution::..\n";
		return true;
	}

} //end of namespace Sol