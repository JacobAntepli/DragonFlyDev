#ifndef __OBJECT_LIST_ITERATOR_H__
#define __OBJECT_LIST_ITERATOR_H__


//Included resources
#include "Object.h"
#include "ObjectList.h"

namespace df {

	//Using Object list 
	class ObjectList;

	class ObjectListIterator {
	private:

		//Constructer must take in list
		ObjectListIterator();
		int m_index;
		const ObjectList* m_p_list;

	public:
		//Constructer takes in an object list
		ObjectListIterator(const ObjectList* p_l);

		//Set iterator to first item
		void first();

		//Set iterator to next item
		void next();

		//return true when at the end of the list
		bool isDone() const;
		
		//Return current object, null if empty or done
		Object* currentObject() const;


	};//End of class
}//End of namespace

#endif // !__OBJECT_LIST_ITERATOR_H__
