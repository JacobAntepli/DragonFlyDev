
//Included resources
#include "Object.h"
#include "WorldManager.h"

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
		WM.insertObject(this);
	}

	//Destroys object 
	//Removes object from gam eworld
	Object::~Object() {

		//Remove from game world
		WM.removeObject(this);
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

	//Object can update itelf
	void Object::update()
	{
	}

	//Handles events for objects
	int Object::eventHandler(const Event* p_event)
	{
		return 0;
	}

	//Base draw function
	int Object::draw()
	{
		return 0;
	}

}//End of namespace