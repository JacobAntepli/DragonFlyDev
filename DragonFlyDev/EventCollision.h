#ifndef __EVENT_COLLSION_H__
#define __EVENT_COLLSION_H__

//Included resources
#include "Event.h"
#include "Object.h"

namespace df {

	//Event type
	const std::string COLLISION_EVENT = "df::collision";

	class EventCollision : public Event {

	private:
		//Collision location
		Vector m_pos; 

		//Object causing collision(the one moving)
		Object* m_p_obj1;

		//Object receiving collision(the one being collided with)
		Object* m_p_obj2;

	public:
		//Create collision event at (0,0) ith o1 and o2 NULL
		EventCollision();

		//Create collision event at specfied values
		EventCollision(Object* p_o1, Object* p_o2, Vector pos);

		//Set Object 1
		void setObject1(Object* p_new_o1);

		//Get Object 1
		Object* getObject1() const;

		//Set Object 2
		void setObject2(Object* p_new_o2);

		//Get Object 2
		Object* getObject2() const;

		//Set position of collision
		void setPosition(Vector new_pos);

		//Get position of collision
		Vector getPosition() const;

	};//End of class
}//End of namespace
#endif
