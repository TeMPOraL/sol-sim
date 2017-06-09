#ifndef __H3D_MATH_H__
#define __H3D_MATH_H__

/*
Couple of math functions. Created for Holodeck 3D Engine.

Most of the functions here are written in Assembler, and almost all
are not mine.

Function implementations can be found in H3D_Math.cpp.

By Jacek "TeMPOraL" Zlydach.
*/ 

#include "H3D_GlobalValues.h"


namespace H3DMath{


inline float absf(float value);	//fast absolute value

// ..:: Powers and roots ::..
inline float sqrtf(float r);	//fast square root
inline float RSqrt(float number);	//some other square root

}

#endif //__H3D_MATH_H__