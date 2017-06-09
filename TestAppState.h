#ifndef __SOL_TEST_APP_STATE_H__
#define __SOL_TEST_APP_STATE_H__

/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 01.06.2004
Last Revised:	01.06.2004

Implementation File: TestAppState.cpp

Notes:
	
*/

/*

*/

#include "AppState.h"
#include "SolarSystem.h"

namespace Sol
{
	class CTestAppState : public CAppState
	{
	private:
		int testTextureHandle;

		CSmallPlanet * planet;
		CSmallPlanet * otherPlanet;

		CSolarSystem ssystem;

	public:
		CTestAppState();	//constructor
		~CTestAppState();	//destructor

		bool Init();	//initialize
		void Update(float dT);	//update
		bool DeInit();	//deinitialize

	};
}

#endif //__SOL_TEST_APP_STATE_H__