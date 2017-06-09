/*
Project:	Sol

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 31.05.2004
Last Revised:	31.05.2004

This is an implementation file

Notes:
	
*/

/*
A simple [depends :) ] stream-based logging unit for Holodeck 3D.

*/

#include "Log.h"

namespace Sol
{
	//=============================================
	//Function: constructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 31.05.2004
	//
	//Returns: nothing
	//Parameters: nothing
	//Description:
	//
	//=============================================
	CLog::CLog()
	{
		fileName = "log.TSW.txt";	//default file name
		forceFlush = true;	//set force flush
		fileOpen = false;	//file is not open
	}

	//=============================================
	//Function: copy constructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 31.05.2004
	//
	//Returns: nothing
	//Parameters: reference to another logfile from whitch to copy
	//Description:
	//
	//=============================================
	CLog::CLog(const CLog & log)
	{
		fileName = log.fileName;	//copy the name
		forceFlush = true;	//set force flush
		fileOpen = false;	//file is not open
	}

	//=============================================
	//Function: destructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 31.05.2004
	//
	//Returns: nothing
	//Parameters: nothing
	//Description:
	//	Closes log file
	//=============================================
	CLog::~CLog()
	{
		Close();	//close the log file
	}

	//=============================================
	//Function: Open()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 21.11.2003
	//
	//Returns: nothing
	//Parameters: nothing
	//Description:
	//	Opens file with default file name
	//=============================================
	void CLog::Open()
	{
		Open(fileName.c_str());
	}

	//=============================================
	//Function: Open(const char * name)
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 31.05.2004
	//
	//Returns: nothing
	//Parameters: nothing
	//Description:
	//	Opens file with given file name
	//=============================================
	void CLog::Open(const char * name)
	{
		fileName = name;	//set the new name

		logFile.open(fileName.c_str());	//open log file
		fileOpen = true;	//file is open

		char timesign [128];	//temporary buffer for holding date / time stuff
		
		_strdate(timesign);	//load current date

		logFile <<"[Log file opened at: " << timesign;	//first half of date/time info

		_strtime(timesign);	//load current time

		logFile <<" " << timesign <<"]\n";	//... and the second half of date/time stuff

		//title
		logFile <<"[======================================================]\n";
		logFile <<"[Logging unit created for TSW                          ]\n";
		logFile <<"[By Jacek \"TeMPOraL\" Zlydach                           ]\n";
		logFile <<"[======================================================]\n";

		//and that`s all :)
	}

	//=============================================
	//Function: Append()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 31.05.2004
	//
	//Returns: nothing
	//Parameters: nothing
	//Description:
	//	Opens file with default file name for append
	//=============================================
	void CLog::Append()
	{
		Append(fileName.c_str());	//open for append
	}

	//=============================================
	//Function: Append(const char * name)
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 31.05.2004
	//
	//Returns: nothing
	//Parameters: name of file to open
	//Description:
	//	Opens file with given file name for append
	//=============================================
	void CLog::Append(const char * name)
	{
		fileName = name;	//set new file name

		logFile.open(fileName.c_str(),std::ios::app);	//open for appending
		fileOpen = true;	//file is open

		char timesign[128];	//for date / time stuff

		_strdate(timesign);	//load date

		logFile <<"[File opened for append at: " << timesign;	// first half of info...

		_strtime(timesign);	//load time

		logFile <<" " <<timesign <<"]\n";	//rest of the info

		//thats all :)
	}

	//=============================================
	//Function: Close()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 31.05.2004
	//
	//Returns: nothing
	//Parameters: nothing
	//Description:
	//	Closes the log file
	//=============================================
	void CLog::Close()
	{
		if(!fileOpen) return;	//we close file only if it is open

		char timesign[128];	//for date / time info
		_strdate(timesign);	//load date

		logFile <<"[Log file closed at: " << timesign;	//first half

		_strtime(timesign);	//load time

		logFile <<" " <<timesign <<"]\n";	//second half

		logFile.flush();	//flush everything
		logFile.close();	//close the log file

		fileOpen = false;	//file is not open
	}

	//=============================================
	//Function: Log(const char * text,...)
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 31.05.2004
	//
	//Returns: nothing
	//Parameters: format text and text params
	//Description:
	//	Log in ugly - stdio way
	//=============================================
	void __cdecl CLog::Log(const char * text, ...)
	{
		if(fileOpen){
			va_list argList;		//argument list
			char tempText[1024];	//array for our string

			if(text == NULL) return;	//no text - do nothing

			va_start(argList,text);	

			int size = _vsnprintf(tempText, sizeof(tempText), text, argList);
			if(size == -1) return;	//failed!

			logFile << tempText <<"\n";

			if(forceFlush) logFile.flush();
		}
	}

	//=============================================
	//Function: Error(const char * text,...)
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 31.05.2004
	//
	//Returns: nothing
	//Parameters: format text and text params
	//Description:
	//	Log errors in ugly - stdio way
	//=============================================

	void __cdecl CLog::Error(const char * text, ...)
	{
		if(fileOpen){
			va_list argList;		//argument list
			char tempText[1024];	//array for our string

			if(text == NULL) return;	//no text - do nothing

			va_start(argList,text);	

			int size = _vsnprintf(tempText, sizeof(tempText), text, argList);
			if(size == -1) return;	//failed!

			logFile <<"[!! "<< tempText << " !!]\n";

			if(forceFlush) logFile.flush();
		}
	}

	//=============================================
	//Function: Flush()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 31.05.2004
	//
	//Returns: nothing
	//Parameters: nothing
	//Description:
	//	Flush log file
	//=============================================
	void CLog::Flush()
	{
		logFile.flush();	//flush log file stream
	}

	//=============================================
	//Function: operator= (const CLog& log)
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 31.05.2004
	//
	//Returns: reference to this CLog object
	//Parameters: right side of = operator - reference to CLog
	//Description:
	//	equalision operator
	//=============================================
	CLog & CLog::operator=(const CLog& log)
	{
		fileName = fileName;	//cpy file name

		//defaults
		forceFlush = true;
		fileOpen = false;

		return *this;	//return reference to this object
	}

	//=============================================
	//Function: operator<< [series]
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 31.05.2004
	//
	//Returns: reference to this CLog
	//Parameters: various variable types
	//Description:
	//	This header stands for all << operators
	//=============================================

	CLog & CLog::operator<<(const char * s)
	{
		if(!fileOpen) return *this;	//if file is not open, saves nothing, but makes writing safe
		logFile << s;	//save data
		if(forceFlush) logFile.flush();	//force flush
		return * this;	//return reference to this CLog
	}

	CLog & CLog::operator<<(std::string s)
	{
		if(!fileOpen) return *this;	//if file is not open, saves nothing, but makes writing safe
		logFile << s.c_str();	//save data
		if(forceFlush) logFile.flush();	//force flush
		return * this;	//return reference to this CLog
	}

	CLog & CLog::operator<<(bool b)
	{
		if(!fileOpen) return *this;	//if file is not open, saves nothing, but makes writing safe
		logFile <<  (b ? "true" : "false");	//save data
		if(forceFlush) logFile.flush();	//force flush
		return * this;	//return reference to this CLog
	}

	CLog & CLog::operator<<(char c)
	{
		if(!fileOpen) return *this;	//if file is not open, saves nothing, but makes writing safe
		logFile << c;	//save data
		if(forceFlush) logFile.flush();	//force flush
		return * this;	//return reference to this CLog
	}

	CLog & CLog::operator<<(unsigned short n)
	{
		if(!fileOpen) return *this;	//if file is not open, saves nothing, but makes writing safe
		logFile << n;	//save data
		if(forceFlush) logFile.flush();	//force flush
		return * this;	//return reference to this CLog
	}

	CLog & CLog::operator<<(short n)
	{
		if(!fileOpen) return *this;	//if file is not open, saves nothing, but makes writing safe
		logFile << n;	//save data
		if(forceFlush) logFile.flush();	//force flush
		return * this;	//return reference to this CLog
	}

	CLog & CLog::operator<<(unsigned int n)
	{
		if(!fileOpen) return *this;	//if file is not open, saves nothing, but makes writing safe
		logFile << n;	//save data
		if(forceFlush) logFile.flush();	//force flush
		return * this;	//return reference to this CLog
	}

	CLog & CLog::operator<<(int n)
	{
		if(!fileOpen) return *this;	//if file is not open, saves nothing, but makes writing safe
		logFile << n;	//save data
		if(forceFlush) logFile.flush();	//force flush
		return * this;	//return reference to this CLog
	}

	CLog & CLog::operator<<(unsigned long n)
	{
		if(!fileOpen) return *this;	//if file is not open, saves nothing, but makes writing safe
		logFile << n;	//save data
		if(forceFlush) logFile.flush();	//force flush
		return * this;	//return reference to this CLog
	}

	CLog & CLog::operator<<(long n)
	{
		if(!fileOpen) return *this;	//if file is not open, saves nothing, but makes writing safe
		logFile << n;	//save data
		if(forceFlush) logFile.flush();	//force flush
		return * this;	//return reference to this CLog
	}

	CLog & CLog::operator<<(float f)
	{
		if(!fileOpen) return *this;	//if file is not open, saves nothing, but makes writing safe
		logFile << f;	//save data
		if(forceFlush) logFile.flush();	//force flush
		return * this;	//return reference to this CLog
	}

	CLog & CLog::operator<<(double d)
	{
		if(!fileOpen) return *this;	//if file is not open, saves nothing, but makes writing safe
		logFile << d;	//save data
		if(forceFlush) logFile.flush();	//force flush
		return * this;	//return reference to this CLog
	}

	CLog & CLog::operator<<(long double ld)
	{
		if(!fileOpen) return *this;	//if file is not open, saves nothing, but makes writing safe
		logFile << ld;	//save data
		if(forceFlush) logFile.flush();	//force flush
		return * this;	//return reference to this CLog
	}

	CLog & CLog::operator<<(void *unk)
	{
		if(!fileOpen) return *this;	//if file is not open, saves nothing, but makes writing safe
		logFile << unk;	//save data
		if(forceFlush) logFile.flush();	//force flush
		return * this;	//return reference to this CLog
	}
/*
	CLog & CLog::operator<<(__int64 n)
	{
		if(!fileOpen) return *this;	//if file is not open, saves nothing, but makes writing safe
		logFile << n;	//save data
		if(forceFlush) logFile.flush();	//force flush
		return * this;	//return reference to this CLog
	}
*/
	//=============================================
	//global log files
	CLog log;	//global log file

} //end of namespace Sol