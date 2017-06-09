/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 31.05.2004
Last Revised:	03.06.2004

This is an Implementation File:

Notes:
	
*/

/*
	Just a simle[?] Window class
*/

#include <windows.h>
#include "Resource.h"

#include "Strings_System.h"
#include "Application.h"
#include "Window.h"
#include "Log.h"

LRESULT CALLBACK UniversalWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Sol
{

	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 31.05.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: name, width, height, bpp, full screen flag
	//Description:
	//	Initializes OpenGL Window with given parameters
	//=============================================
	bool CWindow::Init( int _width, int _height, int _bpp, bool fullscreen)
	{
		width = _width;	//window`s width
		height = _height;	//window`s height
		bpp = _bpp;	//bits per pixel
		isFullScreen = fullscreen;	//is full screen?
		HINSTANCE hInstance = GetModuleHandle(NULL);
		std::string name(CApplication::GetSingleton().systemStrings.GetString(STRING_SYS_GAMENAME));
		if(CApplication::GetSingleton().bDebugMode == true)
		{
			name += " [ ";
			name += CApplication::GetSingleton().runParams;
			name += " ]";
		}

		DWORD dwStyle, dwExStyle;	//additional data

		int PixelFormat;	//temporary variable for storing Pixel Format

		log <<"CWindow::Init() - trying to create GL Window at width: " << _width <<" height: " << _height;
		log <<" bits per pixel: " << _bpp <<" mode: " << ((fullscreen) ? "full screen" : "windowed") << "\n";

		//window class initialization
		log << "CWindow::Init() - Filling window class data...\n";

		wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	//window style
		wndClass.lpfnWndProc = (WNDPROC) UniversalWndProc;	//window procedure
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = hInstance;	//application`s instance handle
		wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINICON));	//load icon
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//load cursor
		wndClass.hbrBackground = NULL;	//no background color
		wndClass.lpszClassName = name.c_str();	//class name
		wndClass.lpszMenuName = NULL;
		wndClass.lpfnWndProc = (WNDPROC) UniversalWndProc;	//window procedure
		//wndClass.lpszClassName = "lol";	//class name
	//	InitWindowClass();	//initialize Window class
		
		//
		if( !RegisterClass(&wndClass) )	//failed to register WndClass
		{
			log.Error("CWindow::Init() - Failed to register Window Class!\n");
			return false;	//error
		}

		if( fullscreen )
		{	
			memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	//zero memory
			
			dmScreenSettings.dmSize=sizeof(dmScreenSettings);	//structure`s size
			dmScreenSettings.dmPelsWidth	= _width;	//width
			dmScreenSettings.dmPelsHeight	= _height;	//height
			dmScreenSettings.dmBitsPerPel	= _bpp;	//bits per pixel
			dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;	//valid fields

			if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
			{
				log <<"CWindow::Init() - failed to set fullscreen mode at width = " << _width <<", height = " << _height <<", bpp = " << _bpp <<"!\n";
				if (MessageBox(NULL,(CApplication::GetSingleton().systemStrings.GetString(STRING_SYS_VIDEO_MODE_NOT_SUPPORTED)).c_str(),(CApplication::GetSingleton().systemStrings.GetString(STRING_SYS_GAMENAME)).c_str(),MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
				{
					log <<"CWindow::Init() - user choosed to continue at windowed mode\n";
					isFullScreen = false;
				}
				else
				{
					MessageBox(NULL,(CApplication::GetSingleton().systemStrings.GetString(STRING_SYS_PROGRAM_WILL_NOW_CLOSE)).c_str(),(CApplication::GetSingleton().systemStrings.GetString(STRING_SYS_GAMENAME)).c_str(),MB_OK|MB_ICONSTOP);
					log <<"CWindow::Init() - user choosed to exit program\n";
					return false;
				}
			}
		}

		if( fullscreen )
		{
		
			/*
			if( !InitDeviceMode() )	//initialize DevMode
			{
				H3D::core::log.Error("CWindow::Init() - failed to initialize Device Mode\n");
				return false;
			}*/
			dwStyle = WS_POPUP;	//popup window
			dwExStyle = WS_EX_APPWINDOW;//appwindow
			ShowCursor(false);	//hide mouse cursor
		}
		else
		{
			dwStyle = WS_OVERLAPPEDWINDOW;
			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		}
		if(!(hWnd = CreateWindowEx(NULL, name.c_str(),name.c_str(), dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, 0, width, height, NULL, NULL, hInstance, NULL)))
		{
			log.Error("CWindow::Init() - Error Creating Window");
			MessageBox(NULL,(CApplication::GetSingleton().systemStrings.GetString(STRING_SYS_FAILED_CREATING_WINDOW)).c_str(),(CApplication::GetSingleton().systemStrings.GetString(STRING_SYS_GAMENAME)).c_str(),MB_OK|MB_ICONSTOP);

			DeInit();
			return false;
		}
		static	PIXELFORMATDESCRIPTOR pfd=
		{

			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW |
			PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			bpp,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			16,
			0,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		if(! (hDC = ::GetDC(hWnd) ) )	//aquiring Device Context
		{
			log.Error("CWindow::Init() - Error aquiring Device Context");
			MessageBox(NULL,(CApplication::GetSingleton().systemStrings.GetString(STRING_SYS_FAILED_AQUIRING_DC)).c_str(),(CApplication::GetSingleton().systemStrings.GetString(STRING_SYS_GAMENAME)).c_str(),MB_OK|MB_ICONSTOP);

			DeInit();
			return false;
		}

		log << "CWindow::Init() - Device Context aquired\n";

		if(!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	//choosing Pixel Format
		{
			log.Error("CWindow::Init() - Error while choosing Pixel Format");
			MessageBox(NULL,(CApplication::GetSingleton().systemStrings.GetString(STRING_SYS_FAILED_CHOOSING_PIXELFORMAT)).c_str(),(CApplication::GetSingleton().systemStrings.GetString(STRING_SYS_GAMENAME)).c_str(),MB_OK|MB_ICONSTOP);
			
			DeInit();
			return false;
		}

		log << "CWindow::Init() - Choosed Pixel Format\n";

		if(! ( SetPixelFormat(hDC,PixelFormat,&pfd) ) )	//set selected PixelFormat
		{
			log.Error("CWindow::Init() - Error setting Pixel Format");
			MessageBox(NULL,(CApplication::GetSingleton().systemStrings.GetString(STRING_SYS_FAILED_SETTING_PIXELFORMAT)).c_str(),(CApplication::GetSingleton().systemStrings.GetString(STRING_SYS_GAMENAME)).c_str(),MB_OK|MB_ICONSTOP);

			DeInit();
			return false;
		}

		log << "CWindow::Init() - Set Pixel Format\n";

		if(! (hRC = wglCreateContext(hDC) ) )	//creating rendering context
		{
			log.Error("CWindow::Init() - Error creating Rendering Context");
			MessageBox(NULL,(CApplication::GetSingleton().systemStrings.GetString(STRING_SYS_FAILED_CREATING_RC)).c_str(),(CApplication::GetSingleton().systemStrings.GetString(STRING_SYS_GAMENAME)).c_str(),MB_OK|MB_ICONSTOP);

			DeInit();
			return false;
		}

		log << "CWindow::Init() - Created Rendering Context\n";

		if( !wglMakeCurrent(hDC,hRC) )	//activate rendering context
		{
			log.Error("CWindow::Init() - Error activating Rendering Context");
			MessageBox(NULL,(CApplication::GetSingleton().systemStrings.GetString(STRING_SYS_FAILED_ACTIVATING_RC)).c_str(),(CApplication::GetSingleton().systemStrings.GetString(STRING_SYS_GAMENAME)).c_str(),MB_OK|MB_ICONSTOP);

			DeInit();
			return false;
		}

		log << "CWindow::Init() - Activated Rendering Context\n";

		ShowWindow(hWnd,SW_SHOW);	//forced window display
		SetForegroundWindow(hWnd);	//??
		SetFocus(hWnd);	//set focus
		Resize(width, height);	//resize gl scene to window`s width and height

		if ( !InitGL() )	//init window-related GL stuff
		{
			log.Error("CWindow::Init() - Error initializing OpenGL");
			MessageBox(NULL,(CApplication::GetSingleton().systemStrings.GetString(STRING_SYS_ERROR_INITIALIZING_OPENGL)).c_str(),(CApplication::GetSingleton().systemStrings.GetString(STRING_SYS_GAMENAME)).c_str(),MB_OK|MB_ICONSTOP);

			DeInit();
			return false;
		}

		log << "CWindow::Init() - OpenGL Initialization Successful\n";

		log << "CWindow::Init() - Window Initialization Successful\n";

		return true;

	}
	
	//=============================================
	//Function: DeInit()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 31.05.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Denitializes OpenGL Window
	//=============================================
	bool CWindow::DeInit()
	{

		if (hRC)	//if we have Rendering Context
		{
			if (!wglMakeCurrent(NULL,NULL))	//disable usage of RC
			{
				log.Error("CWindow::DeInit() - Release of Device Context and Rendering Context failed!");
			}

			if (!wglDeleteContext(hRC))	//delete Rendering Context
			{
				log.Error("CWindow::DeInit() - Release of Rendering Context failed");
			}
			hRC=NULL;	//set handle to null
		}
		log << "CWindow::DeInit() - Rendering Context Released\n";
		
		if (hDC && !ReleaseDC(hWnd,hDC))	//delete Device Context
		{
			log.Error("CWindow::DeInit() - Release of Device Context failed");
			hDC=NULL;	//set handle to null
		}

		log << "CWindow::DeInit() - Device Context Released\n";

		if (hWnd && !DestroyWindow(hWnd))	//destroy window
		{
			log.Error("CWindow::DeInit() - Failed to destroy window");
			hWnd=NULL;	//set window handle to null
		}
		log << "CWindow::DeInit() - HWND Released!\n";

		if (isFullScreen)	//if we are in fullscreen mode, we need to fix display mode
		{
			log << "CWindow::DeInit() - Restoring previous display mode...\n";
			ChangeDisplaySettings(NULL,0);	//set previous display mode
			ShowCursor(true);	//show Windows cursor
		}

		log <<"CWindow::DeInit() - Deinitialization Successful\n";
		return true;
	}

	//=============================================
	//Function: InitGL()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 03.06.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Initializes OpenGL
	//=============================================
	bool CWindow::InitGL()
	{
		glShadeModel(GL_SMOOTH);	//Gouard shading
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	//screen clear color
		glClearDepth(1.0f);	//clearig depth buffer
		glEnable(GL_DEPTH_TEST);	//enable depth testing
		glDepthFunc(GL_LEQUAL);	//depth testing method

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	//perspective correction

		return true;
	}
	
	//=============================================
	//Function: Resize()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 03.06.2004
	//
	//Returns: none
	//Parameters: new width and height
	//Description:
	//	Resizes OpenGL Scene to fit the window
	//=============================================
	void CWindow::Resize(int newWidth, int newHeight)
	{

		width = newWidth;	//set new width
		height = newHeight;	//set new height

		
		if (height==0)
		{
			height=1;	//prevent division by 0 [we can make window 0-lenght]
		}

		glViewport(0,0,width,height);	//set new viewport

		glMatrixMode(GL_PROJECTION);	//projection mode
		glLoadIdentity();	//reset matrix

		gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,1000.0f);	//calculate perspective
		//glOrtho(0.0, 800.0, 600.0, 0.0, -1.0, 1.0);

		glMatrixMode(GL_MODELVIEW);	//modelview matrix
		glLoadIdentity();	//reset matrix

		return;
	}

	//=============================================
	//Function: Set2DMode()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 03.06.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//	Activates 2D Mode (ortho), saving previous mode onto GL matrix stack
	//=============================================
	void CWindow::Set2DMode()
	{

		// Push the neccessary Matrices on the stack
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0, width, height, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();

		// Push the neccessary Attributes on the stack
	glPushAttrib(GL_TEXTURE_BIT|GL_ENABLE_BIT);

	}

	//=============================================
	//Function: Restore3DMode()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 03.06.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//	Restores projection mode saved by Set2DMode. Using it without calling Set2DMode before
	//	will cause GL Matrix Stack underflow
	//=============================================
	void CWindow::Restore3DMode()
	{
		// Return to previous Matrix and Attribute states. Easy cleanup!
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glPopAttrib();
	}

	//=============================================
	//Function: WndProc()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 31.05.2004
	//
	//Returns: LRESULT
	//Parameters: hWnd, msg, wparam, lparam
	//Description:
	//	Standard Windows` message handling function
	//=============================================
	LRESULT CWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch(msg)	//switch windows messages
		{
			case WM_CLOSE:	//close message
			{
				log <<"CWindow::WndProc() - Received WM_CLOSE message, posting WM_QUIT\n";
				PostQuitMessage(0);
				return 0;
			}

			case WM_KEYDOWN:	//pressed a key
			{
				keys[wParam] = true;	//activate key

				return 0;	//processed message
			}

			case WM_KEYUP:
			{
				keys[wParam] = false;	//deactivate key

				return 0;	//processed message
			}

		}

		return DefWindowProc(hWnd, msg, wParam, lParam);	//default Windows` Window Procedure
	}

} //end of namespace Sol
LRESULT CALLBACK UniversalWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return Sol::CApplication::GetSingleton().window.WndProc(hWnd, msg, wParam, lParam);
}