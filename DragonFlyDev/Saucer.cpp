
//Included resources
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


