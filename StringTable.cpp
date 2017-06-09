/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 07.02.2004
Last Revised:	01.01.2004

This is an Implementation File

Notes:
	
*/

/*
	String Table implementation
*/

#include <windows.h>
#include <stdio.h>

#include "Log.h"
#include "StringTable.h"

namespace Sol
{

	//=============================================
	//Function: constructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 07.02.2004
	//
	//Returns: nothing
	//Parameters: nothing
	//Description:
	//	Just a CStringTable constructor
	//=============================================
	CStringTable::CStringTable()
	{
		//initialize with defaults
		numEntries = 0;
		table = NULL;
	}

	//=============================================
	//Function: destructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 07.02.2004
	//
	//Returns: nothing
	//Parameters: nothing
	//Description:
	//	Empty destructor
	//=============================================
	CStringTable::~CStringTable()
	{
	}

	//=============================================
	//Function: Init
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 01.06.2004
	//
	//Returns: true on success, false on failure
	//Parameters: file name
	//Description:
	//	Initializes StringTable from file
	//=============================================
	bool CStringTable::Init(const char *fN)
	{
	//	table = new std::string[1];
	//	table[0] = "Not Yet Implemented!";
	//	numEntries = 1;
		//===
		log <<"CStringTable::Init() - initializing from file " << fN <<"\n";
		FILE *fIn;	//string table file
		if(! (fIn = fopen(fN,"rb")))	//if failed to open in binary mode
		{
			log.Error("CStringTable::Init() - Error opening file %s!",fN);
			//error logging
			return false;
		}
		if(!LoadTable(fIn))
		{
			log.Error("CStringTable::Init() - Error loading file %s!",fN);
			return false;
		}

		fclose(fIn);
		return true;
	}

	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 27.05.2004
	//
	//Returns: true on success, false on failure
	//Parameters: buffer, and it`s size
	//Description:
	//	Initializes StringTable from a buffer
	//=============================================
	bool CStringTable::Init(const char* stringTableData, unsigned int bufferSize)
	{
		return true;
	}
	
	//=============================================
	//Function: LoadTable()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 27.05.2004
	//
	//Returns: true on success, false on failure
	//Parameters: file fandle from which (file) to load
	//Description:
	//	Loads string table from given file
	//=============================================
	bool CStringTable::LoadTable(FILE * fIn)
	{
		WORD numStringEntries;

		fread(&numStringEntries,sizeof(WORD), 1, fIn);

#ifdef __SOL_FULL_DEBUG__
		log <<"CStringTable::LoadTable() - number of string entries = " << numStringEntries << "\n";
#endif //__SOL_FULL_DEBUG__
		if(numStringEntries  <=0)
		{
			log.Error("CStringTable::LoadTable() - number of entries is greater or equal to 0; nmuber of entries: %d", numStringEntries);
			//error logging
			return false;
		}

		table = new std::string[numStringEntries];

		//==
		WORD *offsets;	//offset table
		offsets = new WORD[numStringEntries];	//offset array
		fread(offsets, sizeof(WORD),numStringEntries,fIn);	//read offsets

		char buffer[256];	//text buffer

		for(int i = 0; i < numStringEntries-1 ; i++)
		{
			memset(buffer,0,256);	//zero memory
			fseek(fIn,offsets[i], SEEK_SET);
			fread(buffer, sizeof(char), (offsets[i+1] - offsets[i]), fIn);
			table[i]+= buffer;
			table[i]+= "\0";
		}
		memset(buffer,0,256);	//zero memory
		fseek(fIn,offsets[numStringEntries-1], SEEK_SET);
		fread(buffer, sizeof(char), 256, fIn);
		table[numStringEntries-1]+= buffer;
		table[numStringEntries-1]+= "\0";

		delete[] offsets;
		
		numEntries = numStringEntries;
		log <<"CStringTable::LoadTable() - Number of strings loaded: " << numEntries <<"\n";
#ifdef __SOL_FULL_DEBUG__
		log <<"CStringTable::LoadTable() - loaded strings\n";
#endif //__SOL_FULL_DEBUG__

		return true;
	}

	//=============================================
	//Function: DeInit
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 07.02.2004
	//
	//Returns: true on success, false on failure
	//Parameters: nothing
	//Description:
	//	DeInitializes String Table
	//=============================================
	bool CStringTable::DeInit()
	{
		if(numEntries != 0)
		{
			delete[] table;	//delete string table
			numEntries = 0;	//no entries
			return true;
		}
		return false;
	}

	//=============================================
	//Function: Load
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 07.02.2004
	//
	//Returns: true on success, false on failure
	//Parameters: file name
	//Description:
	//	DeInitializes String Table and loads new one
	//=============================================
	bool CStringTable::Load(const char * fN)
	{
		if(!DeInit())	//if failed to deinitialize
		{
			return false;
		}
		return Init(fN);	//otherwise initialize
	}

	//=============================================
	//Function: GetString
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 10.02.2004
	//
	//Returns: a string in string table
	//Parameters: string ID
	//Description:
	//
	//=============================================
	std::string CStringTable::GetString(unsigned int pos)
	{
		if(pos >= numEntries || numEntries == 0)	//if out of range
		{
			log.Error("CStringTable::GetString() - requested entry from %i [string table size: %i ]", pos, numEntries );
			return std::string("null");	//return empty string
		}
		return table[pos];
	}

}