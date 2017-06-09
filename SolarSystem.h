#ifndef __SOL_SOLAR_SYSTEM_H__
#define __SOL_SOLAR_SYSTEM_H__

/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 01.06.2004
Last Revised:	03.06.2004

Implementation File: SolarSystem.cpp

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
#include "PseudoRandomizer.h"

namespace Sol
{

	//this class represents a small planet moving in the big solar system model
	class CSmallPlanet
	{
	public:
		float orbitRadius;	//radius of orbit;
		float radius;	//planet radius
		float orbitalAnglePerSecond;	//angles per second to rotate on orbit
		float rotation;	//planet`s rotation (on orbit)

		float angleAxis2Orbit;	//angle between orbit plane and the Y axis of planet [-90]
		float rotationAngle;	//rotation of this planet
		float rotationAnglePerSecond;	//how many angles the planet rotates per sec.
		bool bHasAtmosphere;	//do we have to load an Earth - type atmosphere?

		float xOrbitRotation;	//rotation of orbit along x axis

		H3D::math::Vector3 centerPoint;	//center point (to orbit aroud)

		int textureHandle;
		int atmosphereHandle;	//handle for atmosphere texture
		int ringsHandle;	//handle for ring texture
		bool bHasRings;	//rings are (planet radius + planet radius/2) => (planet radius * 2)

		GLUquadricObj* drawingObject;	//drawer for planet

		CSmallPlanet(float oR, float r, float oAS, float xOR, H3D::math::Vector3 center, const char * textureName, bool rings) :orbitRadius(oR), radius(r), orbitalAnglePerSecond(oAS), xOrbitRotation(xOR), centerPoint(center), bHasRings(rings), rotation(0)
		{
			textureHandle = CApplication::GetSingleton().textureManager.LoadTexture(textureName);
			angleAxis2Orbit = 0.0f;
			rotationAngle = 0.0f;
			rotationAnglePerSecond = 55.0f;
			bHasAtmosphere = false;
		}

		bool Init();	//initialize
		bool DeInit();	//deintialize
		void Update(float dT);
		void Draw();	//draw this small planet
	};


	class CSolarSystem
	{
	public:
		std::vector<CSmallPlanet*> planets;	//list of all planets

		H3D::math::Vector3 rotation;	//rotation vector in x,y,z
		H3D::math::Vector3 position;	//position of solar system in space

		H3D::math::Vector3 sunEffectRotator;	//rotator for texture matrix effects for sun

		CPseudoRandomizer randomizer;	//random value generator

		int sunTexture;	//texture of sun
		float sunRadius;	//radius of sun
		GLUquadricObj* sunObject;	//sun quadric drawer

		CSolarSystem() : rotation(H3D::math::Vector3(0,0,0)), position(H3D::math::Vector3(0,0,0)), sunTexture(0), sunRadius(8.0f)
		{
		}

		bool Init();	//initialize
		bool DeInit();	//deintialize

		void AddPlanet(CSmallPlanet* planet);	//adds planet to the system
		void Update(float dT);
		void Draw();	//draw entire system

	};

} //end of namespace sol


#endif //__SOL_SOLAR_SYSTEM_H__
