#ifndef __H3D_BASE_TYPES_H__
#define __H3D_BASE_TYPES_H__

/*
Project:	H3D 0.5

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 17.05.2004
Last Revised:	18.05.2004

Notes:
	
*/

/*
   This header contains typedefs for fixed-size types
*/

namespace H3D
{

	//Unsigned Char - 8 bits
	typedef unsigned char uchar8;
	typedef unsigned char uint8;
	
	//Signed Char - 8 bits
	typedef signed char schar8;
	typedef signed char sint8;
	
	//typical char
	typedef char char8;
	
	//Signed Wide Char - 2 bytes
	typedef wchar_t schar16;
	
	//Unsigned Short - 2 bytes
	typedef unsigned short uint16;
	
	//Signed Short - 2 bytes
	typedef signed short sint16;
	
	//Unsigned Int - 4 bytes
	typedef unsigned int uint32;
	
	//Signed Int - 4 bytes
	typedef signed int sint32;
	
	//4 bytes Floating Point
	typedef float float32;
	
	//8 bytes Floating Point
	typedef double float64;
	
	//64-bit integer
	
#ifdef WIN32	//Widows Platform
	#ifdef _MSC_VER	//MS VC++ Specific
		typedef unsigned __int64 uint64;
		typedef signed __int64 sint64;
	#else //_MSC_VER
		//non MS VC++
		typedef unsigned long long uint64;
		typedef signed long long sint64;
		
	#endif //_MSC_VER
#endif //WIN32
} //end of namespace H3D

#endif //__H3D_BASE_TYPES_H__

