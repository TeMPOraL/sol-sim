#ifndef __H3D_MATH_H__
#define __H3D_MATH_H__
/*
Project:	H3D 0.5

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 18.05.2004
Last Revised:	18.05.2004

Notes:

* !!Solve problems with Assembler on AT&T compatibile compilers!!
	
*/

/*
   This header contains math and physics connected functions and constants
*/

#include "H3DBaseTypes.h"

//for adapting into this project:
#ifdef _MSC_VER
#define H3D_INLINE __forceinline
#else
#define H3D_INLINE __forceinline
#endif

//for DevC++ and all others AT&A asm standard-comapatibile compilers - troubles with
//writing functions in ASM.
#ifndef _MSC_VER
#include <math.h>
#endif //_MSC_VER

namespace H3D
{
	namespace math
	{
		//constants
		const float32 PI = 3.141592653589793238462f;	//PI
		const float32 sqrt2 = 1.414213562419339f;	//Square Root of two. 1.414213562 !!3!! ...
							//IS NOT A CORRECT VERSION
							
		const float32 EPSILON = 0.00001f;	//Minimum values for floats
							
		//function declarations
		
		//generic functions
		
		//math functions
		H3D_INLINE float32 absf(float32 val);	//absolute value for floats
		H3D_INLINE sint32 absi(sint32 val);	//absolute value for ints
		H3D_INLINE float32 sqrtf(float32 val);	//fast square root
		H3D_INLINE float32 RSqrt(float32 val);	//reciprocal square root
		
		//===============================================
		//Here goes implementation of functions listed above
		//===============================================
		

		//Max
		template<class T>
		H3D_INLINE T Max(T a, T b)
		{
			return (a < b)? b : a;
		}
		
		//Min
		template<typename T>
		H3D_INLINE T Min(T a, T b)
		{
			return (a < b)? a : b;
		}
		
		//Clamp
		template<typename T>
		H3D_INLINE T Clamp(T val, T minVal, T maxVal)
		{
			if(val < minVal)
			{
				return minVal;
			}
			else if (maxVal < val)
			{
				return maxVal;
			}
			return val;
		}
		
		//Absolute value for floats and ints. Clears bit 31
		H3D_INLINE float32 absf(float32 val)
		{
			*(sint32*)&val &= 0x7fffffff;	//clear bit 31
			return val;
		}
		
		H3D_INLINE sint32 absi(sint32 val)
		{
			val &= 0x7fffffff;	//clear bit 31
			return val;
		}
		
		//fast square root for float
		H3D_INLINE float32 sqrtf(float32 val)
		{
		#ifdef _MSC_VER	//compiling on MS VC++
			__asm
			{
				fld val
				fsqrt
			}

		#else //_MSC_VER - compiling on other - currently AT&T compatibile
			//__asm("fld val");
   			//__asm("fsqrt");
   			return sqrt(val);

		#endif //_MSC_VER
		}
		
		//reciprocal square root
		//credit for Mirko Teran-Ravnikar a.k.a. DarkWIng
		H3D_INLINE float32 RSqrt(float32 val)
		{
			float32 halfVal = val * .5f;	//half of value
			sint32 i = * ( sint32* ) &val;
			i = 0x5f3759df - ( i >> 1 );
			val = * ( float32* ) &i;
			return val * ( 1.5f - halfVal * val * val );
		}
		
	
	} //end of namespace math
} //end of namespace math


#endif //__H3D_MATH_H__

