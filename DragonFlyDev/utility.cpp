

//Included resources 
#include <time.h>
#include <stdio.h>
#include "utility.h"


namespace df {

	char* Utility::getTimeString() {

		//String for the entire returned string
		static char time_str[30];

		//Get times
		time_t current;
		time(&current);
		struct tm p_time;
	    localtime_s(&p_time,&current);

		//Make a nice string file showing the current time and 
		sprintf_s(time_str, "%02d: %02d : %02d", p_time.tm_hour, p_time.tm_min, p_time.tm_sec);

		return time_str;
	}
}
