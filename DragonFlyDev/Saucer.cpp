
//Included resources
#include "DisplayManager.h"
#include "Saucer.h"
#include "EventStep.h"



//Construcer defintion
Saucer::Saucer()
{
	//Set type
	setType("Saucer");
}

//Deconstrucer defintion
Saucer::~Saucer()
{
}

//Handles events for saucer
int Saucer::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::STEP_EVENT) {

		printf("SAUCER RECOGNIZED STEP EVENT\n");
		return 1;
	}
	return 0;
}

//Object draws itself
//0 on success
int Saucer::draw(){

	if (DM.getWindow() != NULL) {
		DM.drawString(Object::getPosition(), Object::getType(), df::CENTER_JUSTIFIED, df::WHITE);
		return 0;
	}
	else {
		return -1;
	}

}


