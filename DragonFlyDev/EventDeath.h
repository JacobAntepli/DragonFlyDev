#pragma once
#include "Event.h"

namespace df {

	const std::string DEATH_EVENT = "death";

	class EventDeath : public df::Event {

	public:
		EventDeath();
	};

}