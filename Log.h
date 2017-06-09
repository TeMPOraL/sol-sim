#ifndef __SOL_LOG_H__
#define __SOL_LOG_H__
/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 31.05.2004
Last Revised:	31.05.2004

Implementation File: Log.cpp

Notes:
	
*/

/*
A simple [depends :) ] stream-based logging unit for Holodeck 3D

*/

#include <windows.h>

#include <iostream>
#include <fstream>

#include <time.h>


namespace Sol
{
	class CLog	//our log class
	{
		std::ofstream logFile;	//destination file
		std::string fileName;	//log file`s name

		bool fileOpen;	//is the log file open & ready??
		bool forceFlush;	//force a flush after every entry??

	public:
		//member functions

		CLog();	//empty constructor
		CLog(const CLog & log);	//copy constructor
		~CLog();	//destructor

		//file controll functions
		void Open();	//open the file with default filename
		void Open(const char * name);	//open the file with given file name

		void Append();	//open default file for appending
		void Append(const char * name);	//open file for appending with given filename

		void Close();	//close the file

		//basic (stdio-like) logging functions

		void __cdecl Log(const char *, ...);	//log the text
		void __cdecl Error(const char *, ...);	//log error

		//stream operations and stuff

		void SetForceFlush(bool value){forceFlush = value;}	//set FF to the given value
		void Flush();	//flush when you want

		//operators

			//equalision
		CLog & operator=(const CLog& log);	//equalision operator

			//stream write (or, left binary shift)
		
		CLog & operator<<(const char *s);	//text [const char pointer]
		CLog & operator<<(std::string s);	//text [std::string]

		CLog & operator<<(bool b);	//boolean value

		CLog & operator<<(char c);	//for char value 

		CLog & operator<<(unsigned short n);	//for unsigned short numbers
		CLog & operator<<(short n);	//for short numbers

		CLog & operator<<(unsigned int n);	//for unsigned integers
		CLog & operator<<(int n);	//for integers

		CLog & operator<<(unsigned long n);	//for unsigned long
		CLog & operator<<(long n);	//for long

		CLog & operator<<(float f);	//for floating - point numbers
		CLog & operator<<(double d);	//for double - precision floats
		CLog & operator<<(long double ld);	//for long double

		CLog & operator<<(void * unk);	//for unknown type (or pointers)

		CLog & operator<<(__int64 n);	//for 64-bit integer

	}; //end of CLog class
			//global CLog objects

		extern CLog log;	//global log file
} //end of namespace Sol


#endif //__SOL_LOG_H__