
//Included resources
#include "DisplayManager.h"
#include "Saucer.h"




//Construcer defintion
Saucer::Saucer()
{
	//Set type
	setType("Saucer");
}

//Deconstrucer defintion
Saucer::~Saucer()
{
}

//Handles events for saucer
int Saucer::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::STEP_EVENT) {

		printf("SAUCER RECOGNIZED STEP EVENT\n");
		return 1;
	}
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		//Cast to keyboard event
		const df::EventKeyboard* p_keyboard_event = dynamic_cast <const df::EventKeyboard*> (p_e);
		printKey(p_keyboard_event);
	}
    if (p_e->getType() == df::MSE_EVENT) {
        //Cast to keyboard event
        const df::EventMouse* p_keyboard_event = dynamic_cast <const df::EventMouse*> (p_e);
        printMSE(p_keyboard_event);
    }
	return 0;
}

//Object draws itself
//0 on success
int Saucer::draw(){
	if (DM.getWindow() != NULL) {
		DM.drawString(Object::getPosition(), Object::getType(), df::CENTER_JUSTIFIED, df::WHITE);
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
        case df::Keyboard::SPACE:
            printf("KEY PRESSED: SPACE\n");
            break;
        case df::Keyboard::RETURN:
            printf("KEY PRESSED: RETURN\n");
            break;
        case df::Keyboard::ESCAPE:
            printf("KEY PRESSED: ESCAPE\n");
            break;
        case df::Keyboard::TAB:
            printf("KEY PRESSED: TAB\n");
            break;
        case df::Keyboard::LEFTARROW:
            printf("KEY PRESSED: LEFT ARROW\n");
            break;
        case df::Keyboard::RIGHTARROW:
            printf("KEY PRESSED: RIGHT ARROW\n");
            break;
        case df::Keyboard::UPARROW:
            printf("KEY PRESSED: UP ARROW\n");
            break;
        case df::Keyboard::DOWNARROW:
            printf("KEY PRESSED: DOWN ARROW\n");
            break;
        case df::Keyboard::PAUSE:
            printf("KEY PRESSED: PAUSE\n");
            break;
        case df::Keyboard::MINUS:
            printf("KEY PRESSED: MINUS\n");
            break;
        case df::Keyboard::PLUS:
            printf("KEY PRESSED: PLUS\n");
            break;
        case df::Keyboard::TILDE:
            printf("KEY PRESSED: TILDE\n");
            break;
        case df::Keyboard::PERIOD:
            printf("KEY PRESSED: PERIOD\n");
            break;
        case df::Keyboard::COMMA:
            printf("KEY PRESSED: COMMA\n");
            break;
        case df::Keyboard::SLASH:
            printf("KEY PRESSED: SLASH\n");
            break;
        case df::Keyboard::LEFTCONTROL:
            printf("KEY PRESSED: LEFT CONTROL\n");
            break;
        case df::Keyboard::RIGHTCONTROL:
            printf("KEY PRESSED: RIGHT CONTROL\n");
            break;
        case df::Keyboard::LEFTSHIFT:
            printf("KEY PRESSED: LEFT SHIFT\n");
            break;
        case df::Keyboard::RIGHTSHIFT:
            printf("KEY PRESSED: RIGHT SHIFT\n");
            break;
        case df::Keyboard::F1:
            printf("KEY PRESSED: F1\n");
            break;
        case df::Keyboard::F2:
            printf("KEY PRESSED: F2\n");
            break;
        case df::Keyboard::F3:
            printf("KEY PRESSED: F3\n");
            break;
        case df::Keyboard::F4:
            printf("KEY PRESSED: F4\n");
            break;
        case df::Keyboard::F5:
            printf("KEY PRESSED: F5\n");
            break;
        case df::Keyboard::F6:
            printf("KEY PRESSED: F6\n");
            break;
        case df::Keyboard::F7:
            printf("KEY PRESSED: F7\n");
            break;
        case df::Keyboard::F8:
            printf("KEY PRESSED: F8\n");
            break;
        case df::Keyboard::F9:
            printf("KEY PRESSED: F9\n");
            break;
        case df::Keyboard::F10:
            printf("KEY PRESSED: F10\n");
            break;
        case df::Keyboard::F11:
            printf("KEY PRESSED: F11\n");
            break;
        case df::Keyboard::F12:
            printf("KEY PRESSED: F12\n");
            break;
        case df::Keyboard::A:
            printf("KEY PRESSED: A\n");
            break;
        case df::Keyboard::B:
            printf("KEY PRESSED: B\n");
            break;
        case df::Keyboard::C:
            printf("KEY PRESSED: C\n");
            break;
        case df::Keyboard::D:
            printf("KEY PRESSED: D\n");
            break;
        case df::Keyboard::E:
            printf("KEY PRESSED: E\n");
            break;
        case df::Keyboard::F:
            printf("KEY PRESSED: F\n");
            break;
        case df::Keyboard::G:
            printf("KEY PRESSED: G\n");
            break;
        case df::Keyboard::H:
            printf("KEY PRESSED: H\n");
            break;
        case df::Keyboard::I:
            printf("KEY PRESSED: I\n");
            break;
        case df::Keyboard::J:
            printf("KEY PRESSED: J\n");
            break;
        case df::Keyboard::K:
            printf("KEY PRESSED: K\n");
            break;
        case df::Keyboard::L:
            printf("KEY PRESSED: L\n");
            break;
        case df::Keyboard::M:
            printf("KEY PRESSED: M\n");
            break;
        case df::Keyboard::N:
            printf("KEY PRESSED: N\n");
            break;
        case df::Keyboard::O:
            printf("KEY PRESSED: O\n");
            break;
        case df::Keyboard::P:
            printf("KEY PRESSED: P\n");
            break;
        case df::Keyboard::Q:
            printf("KEY PRESSED: Q\n");
            break;
        case df::Keyboard::R:
            printf("KEY PRESSED: R\n");
            break;
        case df::Keyboard::S:
            printf("KEY PRESSED: S\n");
            break;
        case df::Keyboard::T:
            printf("KEY PRESSED: T\n");
            break;
        case df::Keyboard::U:
            printf("KEY PRESSED: U\n");
            break;
        case df::Keyboard::V:
            printf("KEY PRESSED: V\n");
            break;
        case df::Keyboard::W:
            printf("KEY PRESSED: W\n");
            break;
        case df::Keyboard::X:
            printf("KEY PRESSED: X\n");
            break;
        case df::Keyboard::Y:
            printf("KEY PRESSED: Y\n");
            break;
        case df::Keyboard::Z:
            printf("KEY PRESSED: Z\n");
            break;
        case df::Keyboard::NUM1:
            printf("KEY PRESSED: NUM1\n");
            break;
        case df::Keyboard::NUM2:
            printf("KEY PRESSED: NUM2\n");
            break;
        case df::Keyboard::NUM3:
            printf("KEY PRESSED: NUM3\n");
            break;
        case df::Keyboard::NUM4:
            printf("KEY PRESSED: NUM4\n");
            break;
        case df::Keyboard::NUM5:
            printf("KEY PRESSED: NUM5\n");
            break;
        case df::Keyboard::NUM6:
            printf("KEY PRESSED: NUM6\n");
            break;
        case df::Keyboard::NUM7:
            printf("KEY PRESSED: NUM7\n");
            break;
        case df::Keyboard::NUM8:
            printf("KEY PRESSED: NUM8\n");
            break;
        case df::Keyboard::NUM9:
            printf("KEY PRESSED: NUM9\n");
            break;
        case df::Keyboard::NUM0:
            printf("KEY PRESSED: NUM0\n");
            break;
        default:
            printf("KEY PRESSED: UNDEFINED\n");
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




