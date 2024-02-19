

//Included resources 
#include "utility.h"
#include "WorldManager.h"
#include <time.h>
#include <stdio.h>
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


	bool Utility::boxIntersectsBox(Box A, Box B)
	{
		//Booleans for indicating overlap
		bool x_overlap = false;
		bool y_overlap = false;

		//Test horizontal 
		if (boxIntersectHorizontal(A,B) || boxIntersectHorizontal(B, A)) {
			x_overlap = true;
		}

		//Test vertical
		if (boxIntersectVertical(A, B) || boxIntersectVertical(B, A)) {
			y_overlap = true;
		}

		//Check if there was an intersection
		if (x_overlap && y_overlap) {
			return true;
		}

		return false;
	}

	bool Utility::boxIntersectHorizontal(Box A, Box B)
	{
		float Ax1 = A.getCorner().getX();
		float Bx1 = B.getCorner().getX();

		float Ax2 = Ax1 + A.getHorizontal();
		float Bx2 = Bx1 + B.getHorizontal();
		if ((Bx1 <= Ax1) && (Ax1 <= Bx2)) {
			return true;
		}
		return false;
	}

	bool Utility::boxIntersectVertical(Box A, Box B)
	{
		float Ay1 = A.getCorner().getY();
		float By1 = B.getCorner().getY();

		float Ay2 = Ay1 + A.getVertical();
		float By2 = By1 + B.getVertical();

		if ((By1 <= Ay1) && (Ay1 <= By2)) {
			return true;
		}
		return false;
	}

	Box Utility::getWorldBox(const Object* p_o)
	{
		return getWorldBox(p_o, p_o->getPosition());
	}

	Box Utility::getWorldBox(const Object* p_o, Vector where)
	{
		//Get the objects box information
		Box box = p_o->getBox();
		Vector corner = box.getCorner();

		//Set XY values 
		corner.setX(corner.getX() + where.getX());
		corner.setY(corner.getY() + where.getY());
		box.setCorner(corner);

		return box;
	}
	Vector Utility::worldToView(Vector world_pos)
	{
		//Get view information
		Vector view_origin = WM.getView().getCorner();
		int view_x = view_origin.getX();
		int view_y = view_origin.getY();

		//Create new view pos
		Vector view_pos(world_pos.getX() - view_x, world_pos.getY() - view_y);

		return view_pos;
	}
}
