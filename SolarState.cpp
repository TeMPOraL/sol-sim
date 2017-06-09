/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 03.06.2004
Last Revised:	04.06.2004

This is an Implementation File:

Notes:
	
*/

/*

*/


#include <windows.h>

#include "Application.h"
#include "Log.h"
#include "SolarState.h"

#include <gl/gl.h>
#include <gl/glu.h>

#include "Strings_stat_txt.h"

namespace Sol
{

	//=============================================
	//Function: Constructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 03.06.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CSolarState::CSolarState()
	{
		bPaused = false;
	}

	//=============================================
	//Function: Destructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 03.06.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CSolarState::~CSolarState()
	{
	}

	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 04.06.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Initializes App State
	//=============================================
	bool CSolarState::Init()
	{
		log <<"CSolarState::DeInit() - initializing Solar state\n";

		glEnable(GL_POLYGON_SMOOTH);	//enable polygon antialiasing to make orbits look better

		//load default data for camera - connected variables
		cameraDistance = -20.0f;
		cameraRotationX = 0.0f;
		cameraRotationY = 0.0f;

		distanceText = new TextBox(40,400,40,400);

		stat_txt.Init("stat_txt.tbl");	//string table

		starfieldHandle = CApplication::GetSingleton().textureManager.LoadTexture("tex\\starfield.bmp");
		
		distanceText->SetMode(TEXT_DRAW_BACKGROUND | TEXT_DRAW_SPACES | TEXT_WRAP_SPACES);

		ssystem.Init();

		CSmallPlanet * planet;	//our new planet pointer
		//set up all planets
		//Mercury:
		planet = new CSmallPlanet(15+3.871f, 0.5f, 14.0f, 97.004f, H3D::math::Vector3(0.0f,0.0f,0.0f), "tex\\mercury.bmp", false);
		planet->rotationAnglePerSecond = 25.0f;
		planet->angleAxis2Orbit = 180 + 2.0f;
		ssystem.AddPlanet(planet);

		//Venus:
		planet = new CSmallPlanet(15+7.233f, 0.5f, 18.0f, 93.394f, H3D::math::Vector3(0.0f,0.0f,0.0f), "tex\\venus.bmp", false);
		planet->rotationAnglePerSecond = -25.0f;
		planet->angleAxis2Orbit = 180 + 177.3f;
		ssystem.AddPlanet(planet);

		//Earth:
		planet = new CSmallPlanet(15+10.0f, 0.7f, 12.0f, 90.0f, H3D::math::Vector3(0.0f,0.0f,0.0f), "tex\\earth.bmp", false);
		planet->rotationAnglePerSecond = 25.0f;
		planet->angleAxis2Orbit = 180 + 23.44f;
		//planet->bHasAtmosphere = true;
		ssystem.AddPlanet(planet);

		//Mars:
		planet = new CSmallPlanet(15+15.237f, 0.5f, 15.0f , 91.85f, H3D::math::Vector3(0.0f,0.0f,0.0f), "tex\\mars.bmp", false);
		planet->rotationAnglePerSecond = 25.0f;
		planet->angleAxis2Orbit = 180 + 6.68f;
		ssystem.AddPlanet(planet);

		//Jupiter:
		planet = new CSmallPlanet(15+52.028f, 5.5f, 15.0f, 91.308f, H3D::math::Vector3(0.0f,0.0f,0.0f), "tex\\jupiter.bmp", false);
		planet->rotationAnglePerSecond = 25.0f;
		planet->angleAxis2Orbit = 180 + 3.12f;
		ssystem.AddPlanet(planet);

		//Saturn:
		planet = new CSmallPlanet(15+95.388f, 4.5f, 10.0f, 92.448f, H3D::math::Vector3(0.0f,0.0f, 0.0f), "tex\\saturn.bmp", true);
		planet->rotationAnglePerSecond = 25.0f;
		planet->angleAxis2Orbit = 180 + 26.71f;
		ssystem.AddPlanet(planet);

		//Uranus:
		planet = new CSmallPlanet(15+191.914f, 2.0f, 8.0f, 90.774f, H3D::math::Vector3(0.0f,0.0f,0.0f), "tex\\uranus.bmp", false);
		planet->rotationAnglePerSecond = -25.0f;
		planet->angleAxis2Orbit = 180 + 97.86f;
		ssystem.AddPlanet(planet);

		//Neptune
		planet = new CSmallPlanet(15+300.611f, 2.0f, 8.0f, 91.774f, H3D::math::Vector3(0.0f,0.0f,0.0f), "tex\\neptune.bmp", false);
		planet->rotationAnglePerSecond = 25.0f;
		planet->angleAxis2Orbit = 180 + 29.6f;
		ssystem.AddPlanet(planet);

		//Pluto
		planet = new CSmallPlanet(15+395.294f, 0.1f, 9.0f, 117.148f, H3D::math::Vector3(0.0f,0.0f,0.0f), "tex\\pluto.bmp", true);
		planet->rotationAnglePerSecond = -25.0f;
		planet->angleAxis2Orbit = 180 + 122.46f;
		ssystem.AddPlanet(planet);

		return true;
	}

	//=============================================
	//Function: DeInit()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 04.06.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Deinitializes App State
	//=============================================
	bool CSolarState::DeInit()
	{
		log <<"CSolarState::DeInit() - deinitializing Solar state\n";

		ssystem.DeInit();

		delete distanceText;
		stat_txt.DeInit();
	
		return true;
	}

	//=============================================
	//Function: Update()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 04.06.2004
	//
	//Returns: nothing
	//Parameters: Delta Time
	//Description:
	//
	//=============================================
	void CSolarState::Update(float dT)
	{
		//process input

		//move closer and further to the sun
		if(CApplication::GetSingleton().window.keys['A'] == true)
		{
			cameraDistance += CApplication::GetSingleton().window.keys[VK_SHIFT] ? (60.0f * dT) : (15.0f * dT);
		}

		if(CApplication::GetSingleton().window.keys['Z'] == true)
		{
			cameraDistance -= CApplication::GetSingleton().window.keys[VK_SHIFT] ? (60.0f * dT) : (15.0f * dT);
		}

		//rotate vertically around the sun
		if(CApplication::GetSingleton().window.keys[VK_UP] == true)
		{
			cameraRotationX += CApplication::GetSingleton().window.keys[VK_SHIFT] ? (60.0f * dT) : (15.0f * dT);
			if(cameraRotationX >= 360)
			{
				cameraRotationX -= 360;
			}
		}

		if(CApplication::GetSingleton().window.keys[VK_DOWN] == true)
		{
			cameraRotationX -= CApplication::GetSingleton().window.keys[VK_SHIFT] ? (60.0f * dT) : (15.0f * dT);
			if(cameraRotationX <= 0)
			{
				cameraRotationX += 360;
			}
		}

		//rotate horizontally around the sun
		if(CApplication::GetSingleton().window.keys[VK_LEFT] == true)
		{
			cameraRotationY += CApplication::GetSingleton().window.keys[VK_SHIFT] ? (60.0f * dT) : (15.0f * dT);
			if(cameraRotationY >= 360)
			{
				cameraRotationY -= 360;
			}
		}

		if(CApplication::GetSingleton().window.keys[VK_RIGHT] == true)
		{
			cameraRotationY -= CApplication::GetSingleton().window.keys[VK_SHIFT] ? (60.0f * dT) : (15.0f * dT);
			if(cameraRotationY <= 0)
			{
				cameraRotationY += 360;
			}
		}

		if(CApplication::GetSingleton().window.keys['P'] == true)
		{
			bPaused = !bPaused;
			CApplication::GetSingleton().window.keys['P'] = false;
		}

		if(CApplication::GetSingleton().window.keys['L'] == true)
		{
			CApplication::GetSingleton().appManager.SetState(AS_SINGLEPLANET);
			CApplication::GetSingleton().window.keys['L'] = false;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear the screen and the depth buffer
		glLoadIdentity();

		//starfield background [still does not work]

		CApplication::GetSingleton().textureManager.BindTexture(starfieldHandle);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f,0.0f); glVertex3f(-400.0f,-400.0f,-900.0f);
			glTexCoord2f(1.0f,0.0f); glVertex3f(400.0f,-400.0f,-900.0f);
			glTexCoord2f(1.0f,1.0f); glVertex3f(400.0f,400.0f,-900.0f);
			glTexCoord2f(0.0f,1.0f); glVertex3f(-400.0f,400.0f,-900.0f);

		}
		glEnd();

		//glTranslatef(0.0f,0.0f,-5.0f);
		glTranslatef(0.0f,0.0f,cameraDistance);		//translate to camera position

		glRotatef(cameraRotationX, 1.0f ,0.0f, 0.0f);
		glRotatef(cameraRotationY, 0.0f ,1.0f, 0.0f);

		//draw Solar System
		if(!bPaused)
		{
			ssystem.Update(dT);
		}
		ssystem.Draw();

		distanceText->Clear();
		//distanceText->Printf("\n\n\nDistance from Sun: %.2f AU", H3D::math::absf((cameraDistance+15)/10));
		distanceText->Printf(const_cast<char*>(stat_txt.GetString(STRING_STAT_TXT_DISTANCE_FROM_SUN).c_str()), H3D::math::absf((cameraDistance+15)/10));
		distanceText->Printf(const_cast<char*>(stat_txt.GetString(STRING_STAT_TXT_ANGLE_TO_EARTH_ORBIT).c_str()), H3D::math::absf(cameraRotationX));
		distanceText->Draw();

	}


} //end of namespace Sol