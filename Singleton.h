#ifndef __SOL_SINGLETON_H__
#define __SOL_SINGLETON_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 31.05.2004
Last Revised:	31.05.2004

Implementation File: none

Notes:
	
*/

/*

*/

#include <windows.h>
#include <cassert>

namespace Sol
{

	template <typename T>
	class CSingleton
	{
		static T * ms_instance;	//our class instance

	public:

		//constructor
		CSingleton()
		{
			assert( !ms_instance );	//change to H3D Assert
			int offset = (int)(T*)1 - (int)(CSingleton<T>*)(T*)1;	//some trick with pointers that I still
					//don`t understand; it is used to find memory offset where pointer to dervived class is
			ms_instance = (T*)((int) this + offset );	//set up the pointer
		}
		//destructor
		~CSingleton()
		{
			assert( ms_instance );	//change to H3D Assert
			ms_instance = 0;	//reset pointer
		}
		//get reference to singleton class
		static T& GetSingleton()
		{
			assert( ms_instance );	//know what to do?? :)
			return ( *ms_instance );	//return reference
		}
		//get pointer to singleton class
		static T* GetSingletonPtr()
		{
			return ms_instance;	//return pointer
		}

	};	//end of class CSingleton

	template <typename T> T* CSingleton<T>::ms_instance = 0;	//set static member to 0

} //end of namespace Sol


#endif //__SOL_SINGLETON_H__