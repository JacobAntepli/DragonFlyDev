//Included resources
#include "Points.h"

Points::Points() {

	//Set location, color, and string
	setLocation(df::TOP_RIGHT);
	setViewString(POINTS_STRING);
	setColor(df::YELLOW);
}

//Checks events for points
int Points::eventHandler(const df::Event* p_e) {

	// Parent handles event if score update.
	if (df::ViewObject::eventHandler(p_e)) {
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}