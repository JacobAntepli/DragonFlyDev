
//Included resources
#include "LogManager.h"
#include "utility.h"
#include <stdarg.h>
#include <time.h>


namespace df {

	//Constructer definition
	LogManager::LogManager() {

		//Set type
		setType("Log Manager");

		//Initialize variebles
		m_p_f = NULL;
		m_do_flush = false;
		verbosity = 0; 
	}

	//Deconstructer defintion
	LogManager::~LogManager() {

		//Close file if it's still open
		if (m_p_f != NULL) {
			shutDown();
		}
	}

	//Start up log manager and open file.
	//Return 0 on success -1 on failure
	int LogManager::startUp() {

		if (!Manager::isStarted()) {

			//Open file 
			fopen_s(&m_p_f, LOGFILE_NAME, "w+");

			setFlush(true);

			//Check file and do baseclass start up 
			if (m_p_f == NULL || Manager::Manager::startUp() == -1) {

				return -1;
			}
			LM.writeLog("LOG MANAGER STARTED\n");
		}
		
		return 0;
	}

	//Shutdown LogManager
	void LogManager::shutDown() {

		//Call base class shutdown 
		Manager::Manager::shutDown();

		//Close file 
		fclose(m_p_f);
	}

	//Write log to file. Returns 
	int LogManager::writeLog(const char* fmt, ...) {

		//Check that the file is open and the manager is started
		if (m_p_f != NULL && Manager::isStarted()){

			//Temporary utility variable (remember to make that a singleton)
			Utility UT;

			//Print timestamp
			fprintf(m_p_f, "%s\n",UT.getTimeString());
			//Print initial message to file
			fprintf(m_p_f, "Message: ");
			

			//Initialize list
			va_list args;
			va_start(args, fmt);
			vfprintf(m_p_f, fmt, args);

			//Clean stack
			va_end(args);
			if (m_do_flush) {
				fflush(m_p_f);
			}
			
			return sizeof(fmt);
		}
		else {
			return -1;
		}
	}

	//Writing to log depending on the verbosity level 
	void LogManager::writeLog(int log_level, const char* fmt, ...) {

		//Checking verbosity
		if (log_level >= this->verbosity) {
			va_list args;
			va_start(args, fmt);
			writeLog(fmt,args);
		}
	}

	//Flushs log file after write
	void LogManager::setFlush(bool do_flush) {
		m_do_flush = do_flush;
	}

	//Gets the one and only instance of log manager
     LogManager& LogManager::getInstance() {
		 
		 //Make and return one and only log manager
		 static LogManager log_manager;
		 return log_manager;
	}

	 //Gets the verbosity (minimum log level) for the manager
	 int LogManager::getVerbosity() const {

		 //return verbosity
		 return verbosity;
	 }

	 //Sets the verbosity (minimum log level) for the manager
	 void LogManager::setVerbosity(int new_v) {

		 //Set new verbosity
		 verbosity = new_v;

	 }

}




