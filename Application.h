#ifndef __SOL_APPLICATION_H__
#define __SOL_APPLICATION_H__

/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 31.05.2004
Last Revised:	01.06.2004

Implementation File: Application.cpp

Notes:
	
*/

/*
	Application class
*/

#include "Singleton.h"
#include "StringTable.h"
#include "Window.h"
#include "AppStateManager.h"
#include "Timer.h"
#include "TextureManager.h"

namespace Sol
{
	class CApplication : public CSingleton<CApplication>
	{
	private:
		HINSTANCE appInstance;	//application instance
		bool bShouldQuit;	//should the app exit?

	public:
		std::string runParams;	//command line parameters
		bool bDebugMode;	//is debug mode?

		CStringTable systemStrings;	//system strings
		CWindow window;	//app window
		CAppStateMgr appManager;	//app state manager
		CHiResTimer timer;	//high resolution timer
		CTextureManager textureManager;	//texture manager

		CApplication() : bShouldQuit(false), bDebugMode(true), appInstance(0)
		{
		}

		~CApplication()
		{
		}

		bool Init(HINSTANCE hInstance, LPSTR lpParams);	//initialize application
		bool Execute();	//execute application
		bool DeInit();	//deinitialize application

		void Quit()
		{
			bShouldQuit = true;
		}

	};

} //end of namespace Sol


#endif //__SOL_APPLICATION_H__