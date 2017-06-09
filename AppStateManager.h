#ifndef __SOL_APPLICATION_STATE_MANAGER_H__
#define __SOL_APPLICATION_STATE_MANAGER_H__

/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 01.06.2004
Last Revised:	01.06.2004

Implementation File: AppStateManager.cpp

Notes:
	
*/

/*

*/

#include "AppState.h"

enum APP_STATES
{
	AS_NONE = 0,	//no state binded
	AS_INTRO = AS_NONE + 1,	//intro state
	AS_SOLARSYSTEM = AS_NONE + 2,	//show entire solar system
	AS_SINGLEPLANET = AS_NONE + 3,	//show only one planet, and it`s info
	AS_TEST = 255	//test game state
};

namespace Sol
{
	class CAppStateMgr
	{
	private:
		APP_STATES currentState;	//current state
		APP_STATES newState;	//new state to be set

		CAppState * state;	//state object

		bool bShouldChangeState;	//should the Game State Manager change state?

		void ChangeState();	//do a state change

	public:
		CAppStateMgr():state(NULL), currentState(AS_NONE), newState(AS_NONE), bShouldChangeState(false){}
		~CAppStateMgr(){}

		bool Init();	//initialize
		bool Update(float deltaT);	//update
		bool DeInit();	//deinitialize

		bool SetState(APP_STATES newState);
	};	//end of class CAppStateMgr
} //end of namespace Sol


#endif //__SOL_APPLICATION_STATE_MANAGER_H__