

//Included resources
#include "Event.h"
#include "LogManager.h"

namespace df {

	//Constructer definition
	Event::Event()
	{
		//Set type to default
		m_event_type = UNDEFINED_EVENT;

		LM.writeLog(0, "NEW EVENT MADE\n");

		
	}

	//Deconstructer definition
	Event::~Event()
	{
	}

	//Set the type of an event
	void Event::setType(string new_type)
	{
		if (!new_type.empty()) {
			m_event_type = new_type;
		}
	}

	//Get the tpe of the event
	string Event::getType() const
	{
		//Check if null then return
		if (!m_event_type.empty()) {
			return m_event_type;
		}
	}

}//End of namespace