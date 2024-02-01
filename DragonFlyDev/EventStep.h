#ifndef __EVENT_STEP_H__
#define __EVENT_STEP_H__

//Included resources
#include "Event.h"

const std::string STEP_EVENT = "df::step";
namespace df {

	class EventStep : public Event {

	private:

		//How many steps needed to go through
		int m_step_count;

	public:

		//Constructer
		EventStep();

		//Constructer with initial sleepcount
		EventStep(int init_step_count);

		//Set step count
		void setStepCount(int new_count);

		//Get step count
		int getStepCount() const;

	};//End of class
}//End of namespace
#endif // !__EVENT_STEP_H__
