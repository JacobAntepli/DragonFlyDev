
//Included resources
#include "EventStep.h"
#include "LogManager.h"

namespace df {

	//Default constructer
	EventStep::EventStep()
	{
		//Initialize variables
		m_step_count = 0;
		LM.writeLog(-2, "Created Step Event\n");
		setType(STEP_EVENT);
		
	}

	//Non default constructer
	EventStep::EventStep(int init_step_count)
	{
		LM.writeLog(-2, "Created Step Event\n");
		setType(STEP_EVENT);
		setStepCount(init_step_count);
	}

	//Set step count
	void EventStep::setStepCount(int new_count)
	{
		m_step_count = new_count;
	}

	//Get step count
	int EventStep::getStepCount() const
	{
		return m_step_count;
	}

}//End of namespace
