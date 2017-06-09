#ifndef __SOL_WINDOW_H__
#define __SOL_WINDOW_H__

/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 31.05.2004
Last Revised:	03.06.2004

Implementation File: Window.cpp

Notes:
	
*/

/*
	Just a simle[?] Window class
*/

#include <windows.h>

namespace Sol
{
	class CWindow
	{
	protected:
		HWND hWnd;	//window`s handle
		HDC hDC;	//window`s Device Context
		HGLRC hRC;	//window`s Rendering Context
		WNDCLASS wndClass;	//window class

		DEVMODE dmScreenSettings;	//Device Mode

		int width;	//width
		int height;	//height
		int bpp;	//bits per pixel

		bool isFullScreen;	//full screen flag

		//bool InitWindowClass();	//fill up the window class
		//bool InitDeviceMode();	//initialize DevMode
		//bool InitPixelFormat();	//set up pixel format

		
	public:

		bool keys[256];	//heheh, lool :) the most noob style of implementing input, but it`s fast to do :D

		LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);	//window procedure


		bool Init(int _width, int _height, int _bpp, bool fullscreen = false);
		bool DeInit();

		bool InitGL();
		void Resize(int newWidth, int newHeight);

		void Set2DMode();	//set two dimmensional display mode
		void Restore3DMode();	//used after drawing in 2D; restores original mode



		//accessors
		HWND GetHWND()	//get Window Handle
		{
			return hWnd;
		}

		HDC GetDC()
		{
			return hDC;
		}

		HGLRC GetGLRC()
		{
			return hRC;
		}
	};
} //end of namespace Sol

#endif //__SOL_WINDOW_H__