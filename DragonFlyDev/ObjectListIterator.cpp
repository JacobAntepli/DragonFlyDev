
//Included resources
#include "ObjectListIterator.h"
#include "LogManager.h"

namespace df {

	//Constructer which takes in an object list
	ObjectListIterator::ObjectListIterator(const ObjectList* p_l)
	{
		//Initialize variables
		m_p_list = p_l;
		m_index = 0;
		
	}

	//Set iterator to first item
	void ObjectListIterator::first()
	{
		//Set index to zero
		m_index = 0;
	}

	//Set iterator to next item
	void ObjectListIterator::next()
	{
		//Check if the index isnt at the end
		if (!isDone()) {
			m_index++;
		}
	}

	//return done when at the end of the list
	bool ObjectListIterator::isDone() const
	{
		if (m_index == m_p_list->m_count) {
			return true;
		}
		return false;
	}

	//Return current object
	Object* ObjectListIterator::currentObject() const
	{
		//Check if empty or done
		if (!m_p_list->isEmpty() && !isDone()) {
			//Return object at index
			return m_p_list->m_p_obj[m_index];
		}
	}
}//End of namespace