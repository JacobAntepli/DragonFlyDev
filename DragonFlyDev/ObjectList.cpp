

//Included resources
#include "ObjectList.h"
#include "LogManager.h"

namespace df {

	//Default Constructer
	ObjectList::ObjectList()
	{
		//Initialize variables
		m_count = 0;
		m_p_obj[MAX_OBJECTS - 1] = {};

	}

	//Insert object pointer in list
	//Return 0 on success, -1 on failure
	int ObjectList::insert(Object* p_o)
	{
		//Check if list is full
		if (!isFull()) {
			m_p_obj[m_count] = p_o;
			m_count++;
			return 0;
		}
		else {
			return -1;
		}
	}

	//Remove object pointer from list.
	//Return 0 on success, -1 on failure
	int ObjectList::remove(Object* p_o)
	{
		//Check if list is empty 
		if (!isEmpty()) {

			//Iterate through list until you find the specfied object
			for (int i = 0; i < m_count; i++) {

				if (m_p_obj[i] == p_o) {
					LM.writeLog(1, "Object %d successfull found for deletetion\n", m_p_obj[i]->getId());
					m_p_obj[i] = m_p_obj[i-1];
					m_count--;
				}
			}
			return 0;
		}
		else {
			return -1;
		}
	}

	//Clear all of list
	void ObjectList::clear()
	{
		//Set count to zero 
		m_count = 0;
	}

	//Return count of list
	int ObjectList::getCount() const
	{
		return m_count;
	}

	//Return true if list is empty
	bool ObjectList::isEmpty() const
	{
		//Return if m_count == 0
		return m_count == 0;
	}

	//Return true if list is full
	bool ObjectList::isFull() const
	{
		return m_count >= MAX_OBJECTS;
	}
}//End of namespace