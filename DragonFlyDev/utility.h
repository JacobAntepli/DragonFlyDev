#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "Vector.h"



namespace df {
	class Utility {

	public:

		//Make a string for time when something happens 
		char* getTimeString();

		//Return true if positions intersect
		bool positionsIntersect(Vector p1, Vector p2);

	};
}//END OF NAME SPACE
#endif // !__UTILITY_H__




