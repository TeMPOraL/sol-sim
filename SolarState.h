#ifndef __SOL_SOLAR_APP_STATE_H__
#define __SOL_SOLAR_APP_STATE_H__

/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 03.06.2004
Last Revised:	04.06.2004

Implementation File: SolarState.cpp

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
	class CSolarState : public CAppState
	{
	private:

		CSolarSystem ssystem;	//solar system instance

		float cameraRotationX;	//rotation around X axis (up and down arrows)
		float cameraRotationY;	//rotation around Y axis (left and right arrows)
		float cameraDistance;	//distance to center of Solar System (sun), in AU

		bool bPaused;

		TextBox* distanceText;	//distance from sun text

		CStringTable stat_txt;	//stat_txt.tbl

		int starfieldHandle;
		
	public:
		CSolarState();	//constructor
		~CSolarState();	//destructor

		bool Init();	//initialize
		void Update(float dT);	//update
		bool DeInit();	//deinitialize

	};
}

#endif //__SOL_SOLAR_APP_STATE_H__