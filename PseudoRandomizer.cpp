/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 03.06.2004
Last Revised:	03.06.2004

This is an Implementation File;

Notes:
	
*/

/*

	Pseudo-random numer generator

*/
#include <windows.h>
#include "PseudoRandomizer.h"

namespace Sol
{
	//=============================================
	//Function: constructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 03.06.2004
	//
	//Returns: nothing
	//Parameters: nothing
	//Description:
	//
	//=============================================
	CPseudoRandomizer::CPseudoRandomizer(): seed(0)
	{
	}

	//=============================================
	//Function: destrucotr
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 03.06.2004
	//
	//Returns: nothing
	//Parameters: nothing
	//Description:
	//
	//=============================================
	CPseudoRandomizer::~CPseudoRandomizer()
	{
	}

	//=============================================
	//Function: Init
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 03.06.2004
	//
	//Returns: nothing
	//Parameters: gen2 value (default to 3719)
	//Description:
	//	Initializes pseudo-random number generator
	//=============================================
	void CPseudoRandomizer::Init(long _gen2)
	{
		seed = ::GetTickCount();
		gen2 = _gen2;
		gen1 = (gen2/2);
	}

	//=============================================
	//Function: Rand
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 03.06.2004
	//
	//Returns: long - the random value
	//Parameters: max value
	//Description:
	//	Randomizes a value
	//=============================================
	long CPseudoRandomizer::Rand(long maxValue)
	{
		long newSeed = seed;	//new seed
		long retVal;	//return value

		newSeed = ((gen1 * newSeed) + gen2);

		seed = newSeed;	//set new seed
		retVal = newSeed % maxValue;	//make sure that retVal does not goes over maxVal
		return retVal;
	}
	
	//=============================================
	//Function: FRand
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 03.06.2004
	//
	//Returns: float [0...1]
	//Parameters: nothing
	//Description:
	//	Randomizes float (range from 0 to 1)
	//=============================================
	float CPseudoRandomizer::FRand()
	{
		return (static_cast<float>( Rand(65535) )  / static_cast<float>( 65535) );	//randomize from 0 to 1
	}

} //end of namespace Sol