#ifndef __SOL_PSEUDO_RANDOMIZER_H__
#define __SOL_PSEUDO_RANDOMIZER_H__


/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 03.06.2004
Last Revised:	03.06.2004

Implementation File:

Notes:
	
*/

/*

	Pseudo-random numer generator

*/


namespace Sol
{
	class CPseudoRandomizer
	{
	protected:
		long seed;	//seed
		long gen1;	//value 1
		long gen2;	//value 2
	public:
		CPseudoRandomizer();
		~CPseudoRandomizer();
		void Init(long _gen2 = 3719);
		long Rand(long maxValue);	//return number from 0 to maxValue
		float FRand();	//return float [0...1]

	};

} //end of namespace Sol


#endif //__SOL_PSEUDO_RANDOMIZER_H__