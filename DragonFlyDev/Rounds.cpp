#include "Rounds.h"
#include "EventView.h"

using namespace df;

Rounds::Rounds()
{
	//Set location, color, and string
	setLocation(df::TOP_LEFT);
	setViewString(ROUNDS_STRING);
	setColor(df::GREEN);
}

int Rounds::eventHandler(const df::Event* p_e)
{
	//Cast event
	const EventView* p_ve = static_cast<const EventView*> (p_e);


		// Parent handles event if score update.
	if (df::ViewObject::eventHandler(p_e)) {
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}
