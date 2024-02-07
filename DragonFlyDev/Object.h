#ifndef __OBJECT_H__
#define __OBJECT_H__

//Included resources
#include <string>
#include "Vector.h"
#include "Event.h"


using namespace std;
namespace df {

	class Object {

	private:

		//Unique identifier
		int m_id;

		//Game programmer defined type
		string m_type;

		//Position in game world
		Vector m_position;

	public:

		//Construct object with default parameters
		//Add to game world
		Object();

		//Destroy object
		//Remove from game world
		virtual ~Object();

		//Set Object id
		void setId(int new_id);

		//Get Object id
		int getId() const;

		//Set type
		void setType(string new_type);

		//Get type
		string getType() const;

		//Set position
		void setPosition(Vector new_pos);

		//Get position
		Vector getPosition() const;

		//Update object
		virtual void update();

		//Event handler for objects
		virtual int eventHandler(const Event* p_event);

		//Base draw function
		virtual int draw();

	};//End of class
}//End of namespace

#endif // !__OBJECT_H__
