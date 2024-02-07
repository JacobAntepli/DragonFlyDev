#ifndef __OBJECT_H__
#define __OBJECT_H__

//Included resources
#include <string>
#include "Vector.h"
#include "Event.h"

using namespace std;
namespace df {

	//Maximum number of drawing layers known as altitudes
	const int MAX_ALTITUDE = 4;

	class Object {

		

	private:

		//Unique identifier
		int m_id;

		//Game programmer defined type
		string m_type;

		//Position in game world
		Vector m_position;

		//Drawing altitude
		int m_altitude;

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

		//Set altitude of object, range of [0,MAX_ALTITUDE]
		int setAltitude(int new_altitude);

		//Gets the altitude of an object
		int getAltitude() const;

	};//End of class
}//End of namespace

#endif // !__OBJECT_H__
