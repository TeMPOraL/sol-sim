#ifndef __SOL_PLANET_APP_STATE_H__
#define __SOL_PLANET_APP_STATE_H__

/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 04.06.2004
Last Revised:	04.06.2004

Implementation File: PlanetState.cpp

Notes:
	
*/

/*

*/

#include "AppState.h"
#include "SolarSystem.h"
#include "StringTable.h"

#include "GPG//TEXT.h"

namespace Sol
{

	enum PLANET_ID
	{
		PLID_NONE = 0,
		PLID_MERCURY = PLID_NONE + 1,
		PLID_VENUS = PLID_MERCURY + 1,
		PLID_EARTH = PLID_VENUS + 1,
		PLID_MARS = PLID_EARTH + 1,
		PLID_JUPITER = PLID_MARS + 1,
		PLID_SATURN = PLID_JUPITER + 1,
		PLID_URANUS = PLID_SATURN + 1,
		PLID_NEPTUNE = PLID_URANUS + 1,
		PLID_PLUTO = PLID_NEPTUNE + 1,
		PLID_MOON = PLID_PLUTO + 1	//ok, our Moon is not a planet :)
	};

	class CPlanetState : public CAppState
	{
	private:

		CSmallPlanet* planet;	//shown planet
		CSmallPlanet* moon;	//shown planet`s moon
		int shownPlanet;	//what planet is currently displayed

		float cameraRotationX;	//rotation around X axis (up and down arrows)
		float cameraRotationY;	//rotation around Y axis (left and right arrows)
		float cameraDistance;	//distance to center of planet

		bool bPaused;

		TextBox* descriptionText;	//description text

		CStringTable stat_txt;	//stat_txt.tbl

		int starfieldHandle;
		
	public:
		CPlanetState();	//constructor
		~CPlanetState();	//destructor

		bool Init();	//initialize
		void Update(float dT);	//update
		bool DeInit();	//deinitialize

		void SetPlanet(int planetID);	//set displayed planet

	};
}

#endif //__SOL_PLANET_APP_STATE_H__