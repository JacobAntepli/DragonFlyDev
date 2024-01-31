#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

//Included resources 
#include <stdio.h>
#include "Manager.h"

using namespace std;
namespace df {

	//Two letter acronym 
	#define LM df::LogManager::getInstance()

	class LogManager : public df::Manager {

	private:

		//File that logs will go to 
		const char* LOGFILE_NAME = "Debug/dragonfly.log";

		//Constructer 
		LogManager();
		
		//Copy prevention
		LogManager(LogManager const&);

		//Assignment prevention
		void operator= (LogManager const&);

		//Check if log if fflush was called after write
		bool m_do_flush;
		
		//Pointer for log File
		FILE* m_p_f;

		//Minimum log level variable
		int verbosity;

	public:

		//Get the one instance of the log manager
		static LogManager& getInstance();

		//Decounstructer, closes log file
		~LogManager();

		//Start up LogManager(opens log file)
		//Return 0 if success, negative if failure
		int startUp() override;

		//Shutdown (close log file)
		//Return 0 if success, negative if failure
		void shutDown() override;

		//Set Flush of logfile after each write
		void setFlush(bool do_flush = true);

		//Write to logfile. printf formatting.
		// Return number of bytes written -1 if erroer
		int writeLog(const char* fmt, ...);

		//Write to logfile only if log_level > LogManager log_level 
		void writeLog(int log_level, const char* fmt, ...);

		
		//Get the verbosity (minimum log level) for the manager.
		int getVerbosity() const;

		//Set the verbosity (minimum log level) for the manager.
		void setVerbosity(int new_v);
		


	};//End of class
}//End of namespace

#endif//End def for __LOG_MANAGER_H__
