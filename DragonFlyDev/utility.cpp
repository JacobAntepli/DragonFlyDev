

//Included resources 
#include <time.h>
#include <stdio.h>
#include "utility.h"
#include <math.h>


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

	//Return true if positions intersect
	bool Utility::positionsIntersect(Vector p1, Vector p2)
	{
		if (fabs(p1.getX() - p2.getX()) <= 1 && fabs(p1.getY() - p2.getY()) <= 1){
			return true;
		}
		return false;
	}
}
