/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 01.06.2004
Last Revised:	03.06.2004

This is an Implementation File:

Notes:
	
*/

/*

  CAppStateMgr class

*/

#include <Windows.h>
#include "AppStateManager.h"
#include "AppState.h"
#include "Log.h"
#include "TestAppState.h"
#include "SolarState.h"
#include "PlanetState.h"

namespace Sol
{
	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Initializes App State Manager
	//=============================================
	bool CAppStateMgr::Init()
	{
		log << "CAppStateMgr::Init() - Initializing Application State Manager\n";
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
	//	Deinitializes App State Manager
	//=============================================
	bool CAppStateMgr::DeInit()
	{
		if(state != NULL)
		{
			state->DeInit();	//disable state
			delete state;	//delete state
			state = NULL;	//set pointer to nothing
		}
		log << "CAppStateMgr::DeInit() - Deinitializing Application State Manager\n";
		return true;
	}

	//=============================================
	//Function: Update()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: Delta Time
	//Description:
	//	Updates active state
	//=============================================
	bool CAppStateMgr::Update(float deltaT)
	{
		if(bShouldChangeState)	//if need to change states
		{
			ChangeState();	//change state
			bShouldChangeState = false;	//zero flag
		}
		if(state == NULL)	//if no state active
		{
			return true;
		}
		
		state->Update(deltaT);	//update state
		return true;	//return
	}

	//=============================================
	//Function: SetState()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: new state ID
	//Description:
	//
	//=============================================
	bool CAppStateMgr::SetState(APP_STATES newState)
	{
		this->newState = newState;	//set new state
		bShouldChangeState = true;	//mark request of state change
		return true;
	}


	//=============================================
	//Function: ChangeState()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 03.06.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//	Changes app state
	//=============================================
	void CAppStateMgr::ChangeState()
	{
		if(currentState == newState)	//if the new state is the same as the old one
		{
			//reinitialize
			state->DeInit();
			state->Init();
			return;
		}
		if(state != NULL)
		{
			state->DeInit();	//deinitialize state
			delete state;	//delete old state
		}

		switch(newState)	//select new state
		{
			case AS_TEST:
			{
				state = new CTestAppState();	//new test app state
				break;
			}
			case AS_INTRO:	//intro mode
			{
			//	state  = new CIntro();	//new intro state
				break;
			}
			case AS_SOLARSYSTEM:
			{
				state = new CSolarState();
				break;
			}
			case AS_SINGLEPLANET:
			{
				state = new CPlanetState();
				break;
			}
						
			//AS_NONE and unhandled states
			case AS_NONE:
			default:
			{
				state = NULL;
				break;
			}
		}
		if(state!=NULL)	//if state != GS_NULL
		{
			state->Init();	//initialize state
		}
		currentState = newState;	//set current state
		newState = AS_NONE;	//set new state to none
		return;
	}

} //end of namespace Sol