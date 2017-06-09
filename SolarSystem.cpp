/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 01.06.2004
Last Revised:	03.06.2004

This is an Implementation File;

Notes:
	
*/

/*

*/
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <vector>
#include "Application.h"
#include "H3D_Vector3.h"

#include "SolarSystem.h"


namespace Sol
{

	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: true on success; false on failure
	//Parameters: none
	//Description:
	//	Initializes small planet
	//=============================================
	bool CSmallPlanet::Init()
	{
		rotation = 0;
		drawingObject = gluNewQuadric();
		gluQuadricDrawStyle(drawingObject, GLU_FILL);
		gluQuadricTexture(drawingObject, GL_TRUE);
		gluQuadricNormals(drawingObject,GLU_SMOOTH);
		gluQuadricOrientation(drawingObject, GLU_OUTSIDE);

		if(bHasRings)
		{
			ringsHandle = CApplication::GetSingleton().textureManager.LoadTexture("tex\\rings.bmp");
		}
		if(bHasAtmosphere)
		{
			atmosphereHandle = CApplication::GetSingleton().textureManager.LoadTexture("tex\\clouds.bmp");
		}

		return true;
	}

	//=============================================
	//Function: DeInit()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: true on succes, false on failure
	//Parameters: none
	//Description:
	//
	//=============================================
	bool CSmallPlanet::DeInit()
	{
		gluDeleteQuadric(drawingObject);
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
	void CSmallPlanet::Update(float dT)
	{
		rotation += orbitalAnglePerSecond * dT;
		
		if(rotation > 360)
		{
			rotation = rotation - 360;
		}
		else if(rotation <0)
		{
			rotation = rotation + 360;
		}

		rotationAngle += rotationAnglePerSecond * dT;

		if(rotationAngle > 360)
		{
			rotationAngle = rotationAngle - 360;
		}
		else if(rotationAngle <0)
		{
			rotationAngle = rotationAngle + 360;
		}
	}

	//=============================================
	//Function: Draw()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 03.06.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//	draws planet and it`s orbit
	//=============================================
	void CSmallPlanet::Draw()
	{
		glPushMatrix();	//push current matrix
		{
			centerPoint.Translate();

			glRotatef(xOrbitRotation,1.0f,0.0f,0.0f);	//rotate orbit
			glDisable(GL_TEXTURE_2D);

			glColor4f(0.0f,0.0f,1.0f,1.0f);
			gluDisk(drawingObject, orbitRadius -0.125f, orbitRadius +0.125f, 40, 2);

			glEnable(GL_TEXTURE_2D);

			glColor4f(1.0f,1.0f,1.0f,1.0f);
			glRotatef(rotation, 0.0f,0.0f,1.0f);	//rotate to planet position
			glTranslatef(orbitRadius,0.0f,0.0f);	//translate to planet position

			glRotatef(angleAxis2Orbit, 0.0f, 1.0f ,0.0f);	//rotate planet`s axis
			glRotatef(rotationAngle, 0.0f,0.0f,1.0f);	//rotate around axis

			CApplication::GetSingleton().textureManager.BindTexture(textureHandle);
			gluSphere(drawingObject, radius, 20, 20);	//draw planet

			if(bHasRings)
			{
				//rings texture
				CApplication::GetSingleton().textureManager.BindTexture(ringsHandle);
				gluDisk(drawingObject, radius + radius*0.25, radius+radius*0.75,30,3);
			}
			
			if(bHasAtmosphere)	//draw atmosphere
			{
				CApplication::GetSingleton().textureManager.BindTexture(atmosphereHandle);
				glRotatef( (-rotationAngle * 0.5), 0.0f,0.0f,1.0f);

				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				glColor4f(0.5f,0.5f,0.5f,0.05f);
				gluSphere(drawingObject, radius * 1.055f, 20, 20);	//draw planet
			}

			//IMPLEMENT RINGS HERE
		}
		glPopMatrix();
	}


	//=============================================
	//CSolarSystem
	//=============================================

	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 03.06.2004
	//
	//Returns: true on success; false on failure
	//Parameters: none
	//Description:
	//	Initializes solar system
	//=============================================
	bool CSolarSystem::Init()
	{

		float ambientLight[] = {0.5f,0.5f,0.5f, 1.0f};
		float diffuseLight[] = {1.0f,1.0f,1.0f,1.0f};
		float lightPos[] = {0.0f,0.0f,0.0f,1.0f};

		float matAmbient[] = {1.0f,1.0f,1.0f,1.0f};
		float matDiff[] = {1.0f,1.0f,1.0f,1.0f};

		glShadeModel(GL_SMOOTH);

		glEnable(GL_LIGHTING);	//enable lights
		glEnable(GL_LIGHT0);

		glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

		glEnable(GL_LIGHT0);

		sunTexture = CApplication::GetSingleton().textureManager.LoadTexture("tex\\sun.bmp");
		
		sunObject = gluNewQuadric();

		
		gluQuadricDrawStyle(sunObject, GLU_FILL);
		
		gluQuadricTexture(sunObject, GL_TRUE);

		randomizer.Init();

		sunEffectRotator = H3D::math::Vector3(0.0f,0.0f,0.0f);
		
		return true;
	}

	//=============================================
	//Function: DeInit()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: true on success; false on failure
	//Parameters: none
	//Description:
	//	Deinitializes solar system
	//=============================================
	bool CSolarSystem::DeInit()
	{
		gluDeleteQuadric(sunObject);

		for(std::vector<CSmallPlanet*>::iterator itor = planets.begin() ; itor != planets.end() ; )
		{
			(*itor)->DeInit();

			delete (*itor);
			planets.erase(itor);
		}
		return true;
	}

	//=============================================
	//Function: AddPlanet()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: nothing
	//Parameters: new small planet to add
	//Description:
	//	Initializes solar system
	//=============================================
	void CSolarSystem::AddPlanet(CSmallPlanet* planet)
	{
		planet->Init();
		planets.push_back(planet);	//add to the list
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
	//	Updates entire system
	//=============================================
	void CSolarSystem::Update(float dT)
	{
		for(std::vector<CSmallPlanet*>::iterator itor = planets.begin() ; itor != planets.end() ; ++itor)
		{
			(*itor)->Update(dT);
		}

		sunEffectRotator += H3D::math::Vector3(0.01*dT, 0.016*dT, 0.007*dT);

		if(sunEffectRotator.x >= 1)sunEffectRotator.x -= 1;
		else if (sunEffectRotator.x <= 0)sunEffectRotator.x += 1;

		
		if(sunEffectRotator.y >= 1)sunEffectRotator.y -= 1;
		else if (sunEffectRotator.y <= 0)sunEffectRotator.y += 1;

		
		if(sunEffectRotator.z >= 1)sunEffectRotator.z -= 1;
		else if (sunEffectRotator.z <= 0)sunEffectRotator.z += 1;
	}

	//=============================================
	//Function: Draw()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//	Draws entire system
	//=============================================
	void CSolarSystem::Draw()
	{
		position.Translate();
		rotation.Rotate();

		glEnable(GL_TEXTURE_2D);
		glColor4f(1.0f,1.0f,1.0f,1.0f);

		glMatrixMode(GL_TEXTURE);	//switch to texture matrix
		glLoadIdentity();	//load identity matrix to textuer matrix

		//do effect on texture matrix
		sunEffectRotator.Translate();

		glMatrixMode(GL_MODELVIEW);

		CApplication::GetSingleton().textureManager.BindTexture(sunTexture);

		gluSphere(sunObject, sunRadius, 20, 20);	//draw sun


		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();	//reset texture Matrix for other objects
		glMatrixMode(GL_MODELVIEW);

		for(std::vector<CSmallPlanet*>::iterator itor = planets.begin() ; itor != planets.end() ; ++itor)
		{
			(*itor)->Draw();
		}
	}
} //end of namespace Sol