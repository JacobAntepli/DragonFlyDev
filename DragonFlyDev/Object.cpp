
//Included resources
#include "Object.h"

using namespace std;
namespace df {

	//Object constructer which sets values to default
	//Adds object to game world
	Object::Object() {

		//Keep track of how many objects have been spawned and set Object id
		static int num_objects;
		setId(num_objects);
		num_objects++;

		//Default type is just Object
		setType("Object");

		//Default position is (0,0)
		m_position = Vector(0, 0);

		//Add object to gameworld
	}

	//Destroys object 
	//Removes object from gameworld
	Object::~Object() {
		
	}

	//Sets object unique id
	void Object::setId(int new_id) {

		m_id = new_id;
	}

	//Gets object unique id
	int Object::getId() const {

		return m_id;
	}

	//Set type of object
	void Object::setType(string new_type) {

		m_type = new_type;
	}

	//Get object type
	string Object::getType() const{

		return m_type;
	}

	//Set position of object
	void Object::setPosition(Vector new_pos) {

		m_position = new_pos;
	}

	//Get position of object
	Vector Object::getPosition() const {

		return m_position;
	}
}//End of namespace