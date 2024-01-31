#ifndef __OBJECT_LIST_H__
#define __OBJECT_LIST_H__

//Included resources
#include "Object.h"
#include "ObjectListIterator.h"

namespace df {

	//Max number of objects
	const int MAX_OBJECTS = 2000;



	//Using iterator
	class ObjectListIterator;

	class ObjectList {
	private:
		//Number of objcts
		int m_count;

		//Object List
		Object* m_p_obj[MAX_OBJECTS];

	public:

		//Friend of object list iterator class
		friend class ObjectListIterator;

		//Default Constructer
		ObjectList();

		//Insert object pointer in list
		//Return 0 on success, -1 on failure
		int insert(Object* p_o);

		//Remove object pointer from list.
		//Return 0 on success, -1 on failure
		int remove(Object* p_o);

		//Clear all of list
		void clear();

		//Return count of list
		int getCount() const;

		//Return true if list is empty
		bool isEmpty() const;

		//Return true if list is full
		bool isFull() const;

	};//End of class
}//End of namespace

#endif // !__OBJECT_LIST_H__

