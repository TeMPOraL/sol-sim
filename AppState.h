#ifndef __SOL_APP_STATE_H__
#define __SOL_APP_STATE_H__

/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 01.06.2004
Last Revised:	01.06.2004

Implementation File: None

Notes:
	
*/

/*


*/

namespace Sol
{
	class CAppState
	{
	public:
		CAppState(){}	//default constructor
		virtual ~CAppState(){}	//virtual destructor

		virtual bool Init()=0;	//Initialize App State
		virtual void Update(float deltaT)=0;	//Update App State
		virtual bool DeInit()=0;	//DeInitialize App State

	};


} //end of namespace Sol

#endif //__SOL_APP_STATE_H__