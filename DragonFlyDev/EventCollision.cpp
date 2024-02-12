
//Included resources
#include "EventCollision.h"

namespace df {
	//Create collision event at (0,0) ith o1 and o2 NULL
	EventCollision::EventCollision()
	{
		//Set type
		setType(COLLISION_EVENT);

		//Initialize variables
		m_pos = Vector(0, 0);
		m_p_obj1 = NULL;
		m_p_obj2 = NULL;
	}

	//Create collision event at specified values
	EventCollision::EventCollision(Object* p_o1, Object* p_o2, Vector pos)
	{
		//Set type
		setType(COLLISION_EVENT);
		//Set Objects
		setObject1(p_o1);
		setObject2(p_o2);
		//Position
		setPosition(pos);
	}

	//Set Object 1
	void EventCollision::setObject1(Object* p_new_o1)
	{
		m_p_obj1 = p_new_o1;
	}

	//Get Object 1
	Object* EventCollision::getObject1() const
	{
		return m_p_obj1;
	}

	//Set Object 2
	void EventCollision::setObject2(Object* p_new_o2)
	{
		m_p_obj2 = p_new_o2;
	}

	//Get Object 2
	Object* EventCollision::getObject2() const
	{
		return m_p_obj2;
	}

	//Set position of collision
	void EventCollision::setPosition(Vector new_pos)
	{
		m_pos = new_pos;
	}

	//Get position of collision
	Vector EventCollision::getPosition() const
	{
		return m_pos;
	}

}//End of name space