
//Included resources
#include "Object.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

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

		//Default altitude is MAX_ALTITUDE/2
		m_altitude = MAX_ALTITUDE / 2;

		//Default direction
		m_direction = Vector(0, 0);

		//Default speed
		m_speed = 0; 

		//Default solidness
		m_solidness = HARD;

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
		Vector pos = getPosition();
		return m_animation.draw(pos);
	}

	//Set altitude of object, range of [0,MAX_ALTITUDE]
	int Object::setAltitude(int new_altitude)
	{
		//Check if new altitude is within range
		if (new_altitude >= 0 && new_altitude <= MAX_ALTITUDE) {

			m_altitude = new_altitude;
			LM.writeLog(0, "SUCCESFULLY SET OBJECT %d ALTITUDE TO %d\n", getId(), new_altitude);
			return 0;
		}
		
		LM.writeLog(10, "ATTEMPTED ALTITUDE OF %d IS OUT OF RANGE 0-%d\n", new_altitude, MAX_ALTITUDE);
		return -1;
	}

	//Gets the altitude of an object
	int Object::getAltitude() const
	{
		return m_altitude;
	}

	//Set speed of object
	void Object::setSpeed(float speed)
	{
		m_speed = speed;
	}

	//Get speed of object
	float Object::getSpeed() const
	{
		return m_speed;
	}

	//Set direction of object
	void Object::setDirection(Vector new_direction)
	{
		m_direction = new_direction;
	}

	//Get direction of object
	Vector Object::getDirection() const
	{
		return m_direction;
	}

	//Get velocity of object
	void Object::setVelocity(Vector new_velocity)
	{
		//Set new speed from magnitude of velocity
		m_speed = new_velocity.getMagnitude();

		//Set new direction from normalized velocit
		new_velocity.normalize();
		m_direction = new_velocity;

	}

	//Get velocity of object
	Vector Object::getVelocity() const
	{
		Vector velocity = m_direction;
		velocity.scale(m_speed);

		return velocity;
	}

	//Predict objects position based on speed and direction
	//Return predicted position 
	Vector Object::predictPosition()
	{
		//New position is current position plus current velocity
		Vector predictedPosition = m_position + getVelocity();

		return predictedPosition;
	}

	//Check if object is hard or soft
	bool Object::isSolid() const
	{
		//Return false if spectral 
		if(m_solidness == SPECTRAL){
			return false;
		}

		return true;
	}

	//Set object solidity
	//Return 0 on success, -1 on failure
	int Object::setSolidness(Solidness new_solid)
	{
		m_solidness = new_solid;
		return m_solidness;
	}

	//Get object solidness
	Solidness Object::getSolidness() const
	{
		return m_solidness;
	}

	int Object::setSprite(string sprite_label)
	{
		//Get sprite from resource manager
		Sprite* p_sprite = RM.getSprite(sprite_label);

		//Ensure sprite exists 
		if (p_sprite == NULL) {
			return -1;
		}


		m_animation.setSprite(p_sprite);
		//Set bounding box around sprite
		setBox(m_animation.getBox());
		return 0;
	}

	void Object::setAnimation(Animation new_animation)
	{
		m_animation = new_animation;
	}

	Animation Object::getAnimation() const
	{
		return m_animation;
	}

	/*test method for animation access 
	void Object::setSlowdownCount(int new_slow)
	{
		m_animation.setSlowdownCount(new_slow);
	}
	*/

	void Object::setBox(Box new_box)
	{
		m_box = new_box;
	}

	Box Object::getBox() const
	{
		return m_box;
	}

}//End of namespace