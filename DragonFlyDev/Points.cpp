
//Included resources
#include "Points.h"
#include "EventView.h"
#include "EventDeath.h"
#include "WorldManager.h"

using namespace df;

Points::Points() {

	//Set location, color, and string
	setLocation(df::TOP_RIGHT);
	setViewString(POINTS_STRING);
	setColor(df::GREEN);
}

//Checks events for points
int Points::eventHandler(const df::Event* p_e) {


	//Cast event
	const EventView* p_ve = static_cast<const EventView*> (p_e);
	if (p_e->getType() == df::DEATH_EVENT) {
		WM.markForDelete(this);
	}

	if(getValue() + p_ve->getValue() > 0) {
		// Parent handles event if score update.
		if (df::ViewObject::eventHandler(p_e)) {
			return 1;
		}
	}
	

	// If get here, have ignored this event.
	return 0;
}