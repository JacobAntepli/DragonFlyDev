


//Included resources
#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include "Clock.h"
#include "LogManager.h"

namespace df {

	//Constructer defintion
	Clock::Clock() {
		LM.writeLog("Clock constructer complete\n");
		//Set previous time called to the current time;
		m_previous_t = getCurTime();
		
	}

	//Returns how long it's been since last call in microseconds
	//Resets previous time to current time
	long int Clock::delta() {

		//Get time since last call without changing previous time
	    long int returnTime = getCurTime() - m_previous_t;
		//Change previous time
		m_previous_t = getCurTime();

		return returnTime;
	}


	//Returns how long it's been since last call in microseconds
    //Does not reset previous time
	long int Clock::split(){

		//Get time since last call 
		long int splitTime = getCurTime() - m_previous_t;

		return splitTime;
	
	}

	//Get current time
	long int Clock::getCurTime() {

		//Gets the raw current time
		SYSTEMTIME currentT;
		GetSystemTime(&currentT);

		//Puts the current time together 
		return (currentT.wDay * 24 * 60 * 60 * 1000000)
			+ (currentT.wHour * 60 * 60 * 1000000)
			+ (currentT.wMinute * 60 * 1000000)
			+ (currentT.wSecond * 1000000)
			+ (currentT.wMilliseconds * 1000);
	}

}//End of name space