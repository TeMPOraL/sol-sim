#ifndef __SOL_STRING_TABLE_H__
#define __SOL_STRING_TABLE_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 31.05.2004
Last Revised:	31.05.2004

Implementation File: StringTable.cpp

Notes:
	
*/

/*
	Header for String Table Object
*/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include <string>

namespace Sol
{
	class CStringTable
	{
	protected:
		std::string * table;	//table of strings
		unsigned int numEntries;	//number of string entries

	public:
		CStringTable();	//constructor
		~CStringTable();//destructor

		bool Init(const char * fN);	//initialize from file
		bool Init(const char * stringTableData, unsigned int bufferSize);	//initialize from file

		bool LoadTable(FILE * fIn);	//load table from file, giving file handle ptr.

		bool DeInit();	//deinitialize

		bool Load(const char * fN);	//load from file

		std::string GetString(unsigned int pos);	//get string
		unsigned int GetEntriesCount()	//get number of string entries
		{
			return numEntries;
		}

		bool EntryExists(unsigned int entry)
		{
			return ( (entry < numEntries) ? true : false );
		}


	};

} //end of namespace Sol


#endif //__SOL_STRING_TABLE_H__