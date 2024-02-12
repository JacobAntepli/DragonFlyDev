
//Included resources
#include "DisplayManager.h"
#include "Saucer.h"
#include "GameManager.h"



//Default construcer defintion
Saucer::Saucer()
{
	//Set type
	setType("Saucer");

    //Set posistion
    setPosition(df::Vector(0,DM.getVertical() / 2));

    //Set velocity
    setVelocity(df::Vector(.25, 0));

    //Set solidness
    setSolidness(df::SPECTRAL);
}

//Specified constructer
Saucer::Saucer(df::Vector spawn_pos, df::Vector velocity)
{
    //Set type
    setType("Saucer");

    //Set posistion
    setPosition(spawn_pos);

    //Set velocity
    setVelocity(velocity);
}

//Deconstrucer defintion
Saucer::~Saucer()
{
}

//Handles events for saucer
int Saucer::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::STEP_EVENT) {

		//printf("SAUCER RECOGNIZED STEP EVENT\n");
		return 1;
	}
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		//Cast to keyboard event
		const df::EventKeyboard* p_keyboard_event = dynamic_cast <const df::EventKeyboard*> (p_e);
		printKey(p_keyboard_event);
	}
    if (p_e->getType() == df::MSE_EVENT) {
        //Cast to keyboard event
        const df::EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
        printMSE(p_mouse_event);
    }
    if (p_e->getType() == df::COLLISION_EVENT) {
        //Cast to collision event
        const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
        printCollision(p_collision_event);
    }

	return 0;
}

//Object draws itself
//0 on success
int Saucer::draw(){
	if (DM.getWindow() != NULL) {
		DM.drawString(Object::getPosition(), "SAUCER", df::CENTER_JUSTIFIED, df::WHITE);
		return 0;
	}
	else {
		return -1;
	}
}

//Print out pressed and released keys
void Saucer::printKey(const df::EventKeyboard* p_e)
{
        switch (p_e->getKey()) {
        case df::Keyboard::ESCAPE:
            GM.setGameOver(true);
            break;
        
        }
}

//Print out pressed and released mouse button as well as its new position 
void Saucer::printMSE(const df::EventMouse* p_e)
{
    switch (p_e->getMouseButton()) {
    case df::Mouse::LEFT:
        printf("MOUSE BUTTON PRESSED: LEFT\n");
        printf("MOUSE LOCATION IS(%f,%f)\n", p_e->getMousePosition().getX(), p_e->getMousePosition().getY());
        break;
    case df::Mouse::RIGHT:
        printf("MOUSE BUTTON PRESSED: RIGHT\n");
        printf("MOUSE LOCATION IS(%f,%f)\n", p_e->getMousePosition().getX(), p_e->getMousePosition().getY());
        break;
    case df::Mouse::MIDDLE:
        printf("MOUSE BUTTON PRESSED: MIDDLE\n");
        printf("MOUSE LOCATION IS(%f,%f)\n", p_e->getMousePosition().getX(), p_e->getMousePosition().getY());
        break;
    }
}

//Print colliding objects 
void Saucer::printCollision(const df::EventCollision* p_e)
{
    //Comment out whichever collision type you dont wish to see
    /*
    if (this->getSolidness() == df::HARD) {
        printf("COLLISION OCCURED BETWEEN OBJECT WITH ID %d and %d\n", p_e->getObject1()->getId(), p_e->getObject2()->getId());
    }
    */
    if (this->getSolidness() == df::SOFT) {
        printf("COLLISION OCCURED BETWEEN OBJECT WITH ID %d and %d\n", p_e->getObject1()->getId(), p_e->getObject2()->getId());
    }
    if (this->getSolidness() == df::SPECTRAL) {
        printf("THIS SHOULD NEVER PRINT\n");
    }

}




