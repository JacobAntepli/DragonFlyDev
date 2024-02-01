
//Included resources
#include "EventStep.h"
#include "LogManager.h"

namespace df {

	//Default constructer
	EventStep::EventStep()
	{
		//Initialize variables
		m_step_count = 0;
		EventStep(m_step_count);
	}

	//Non default constructer
	EventStep::EventStep(int init_step_count)
	{
		LM.writeLog(0, "Created Step Event\n");
		setType(STEP_EVENT);
		setStepCount(init_step_count);
	}

	void EventStep::setStepCount(int new_count)
	{
	}

	int EventStep::getStepCount() const
	{
		return 0;
	}

}//End of namespace
