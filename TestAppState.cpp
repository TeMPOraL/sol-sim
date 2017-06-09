/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 01.06.2004
Last Revised:	03.06.2004

This is an Implementation File

Notes:
	
*/

/*

*/

#include <windows.h>

#include "Application.h"
#include "Log.h"
#include "TestAppState.h"

#include <gl/gl.h>
#include <gl/glu.h>

namespace Sol
{
	//=============================================
	//Function: Constructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CTestAppState::CTestAppState()
	{
	}

	//=============================================
	//Function: Destructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CTestAppState::~CTestAppState()
	{
	}

	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 03.06.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Initializes App State
	//=============================================
	bool CTestAppState::Init()
	{
		log << "CTestAppState::Init() - initializing Test App state\n";

		//test texture now becomes a background for solar system
		testTextureHandle = CApplication::GetSingleton().textureManager.LoadTexture("tex\\starfield.bmp");

		planet = new CSmallPlanet(10.0f,0.25f,10.0f,85.0f,H3D::math::Vector3(0.0f,0.0f,0.0f),"tex\\earthmoon.bmp",false);
		//planet->Init();

		otherPlanet = new CSmallPlanet(3.0f, 0.5f, -25.0f, 105.0f, H3D::math::Vector3(0.0f,-5.0f,0.0f), "tex\\earth.bmp",false);
		//otherPlanet->Init();
		otherPlanet->angleAxis2Orbit = 90.0f;

		ssystem.Init();
		
		ssystem.AddPlanet(planet);

		ssystem.AddPlanet(otherPlanet);

		return true;
	}

	//=============================================
	//Function: DeInit()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Deinitializes App State
	//=============================================
	bool CTestAppState::DeInit()
	{
		log <<"CTestAppState::DeInit() - deinitializing Test App state\n";
	//	planet->DeInit();

		ssystem.DeInit();

	//	otherPlanet->DeInit();

		return true;
	}

	//=============================================
	//Function: Update()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: nothing
	//Parameters: Delta Time
	//Description:
	//
	//=============================================
	void CTestAppState::Update(float dT)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear the screen and the depth buffer
		glLoadIdentity();

	/*	CApplication::GetSingleton().window.Set2DMode();

		CApplication::GetSingleton().textureManager.BindTexture(testTextureHandle);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f,0.0f);
			glVertex2f(0.0f,0.0f);

			glTexCoord2f(1.0f,0.0f);
			glVertex2f(800.0f,0.0f);

			glTexCoord2f(1.0f,1.0f);
			glVertex2f(800.0f,600.0f);

			glTexCoord2f(0.0f,1.0f);
			glVertex2f(0.0f,600.0f);
		}
		glEnd();

		CApplication::GetSingleton().window.Restore3DMode();
		*/

		glTranslatef(0.0f,0.0f,-20.0f);

		glEnable(GL_TEXTURE_2D);

		glColor4f(1.0f,1.0f,1.0f,1.0f);

		//planet->Update(dT);
		//o//therPlanet->Update(dT);

		//planet->Draw();
		//otherPlanet->Draw();

		ssystem.Update(dT);
		ssystem.Draw();
	}

} //end of namespace Sol