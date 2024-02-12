#ifndef __EVENT_OUT_H__
#define __EVENT_OUT_H__

//Included resources
#include "Event.h"
#include "Object.h"

namespace df {

	//Event type
	const std::string OUT_EVENT = "df::out";

	class EventOut : public Event {

	public:
		//Constructer
		EventOut();

	};//End of class
}//End of namespace
#endif
