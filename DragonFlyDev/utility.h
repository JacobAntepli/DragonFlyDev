#ifndef __UTILITY_H__
#define __UTILITY_H__

//Included resources
#include "Vector.h"
#include "Box.h"
#include "Object.h"
#include <sstream>

using std::stringstream;
namespace df {
	class Utility {

	public:

		//Make a string for time when something happens 
		char* getTimeString();

		//Return true if positions intersect
		bool positionsIntersect(Vector p1, Vector p2);

		//Returns true if boxes intersect, false if they dont
		bool boxIntersectsBox(Box A, Box B);

		//Tests horizontal intersect 
		bool boxIntersectHorizontal(Box A, Box B);

		//Tests vertical intersect
		bool boxIntersectVertical(Box A, Box B);

		//Convert relative bounding box for object to absolute world box
		Box getWorldBox(const Object* p_o);
		Box getWorldBox(const Object* p_o, Vector where);

		//Convert world position to view position
		Vector worldToView(Vector world_pos);

		//Convert view position to world position
		Vector viewToWorld(Vector view_pos);

		//Convert int ot a string 
		std::string toString(int i);
	};
}//END OF NAME SPACE
#endif // !__UTILITY_H__




