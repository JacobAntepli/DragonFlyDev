
//Included resources
#include "InputManager.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "WorldManager.h"

namespace df {

	//Constructer definition
	InputManager::InputManager() 
    {
        //Set type
        setType("InputManager");
	}

	//Get the singleton for input manager
	InputManager& InputManager::getInstance()
	{
		static InputManager inputManager;
		return inputManager;
	}

	//Get window ready for input capture
	//Return 0 on success, -1 on failure
	int InputManager::startUp()
	{
		//Check that the display manager is started
		if (!DM.isStarted()) {
			LM.writeLog(10, "UNABLE TO START INPUT MANAGER AS DISPLAY MANAGER IS OFF\n");
			return -1;
		}
		
		//Get window
		sf::RenderWindow* window = DM.getWindow();

		//Prevent keyboard repeat 
		//window->setKeyRepeatEnabled(false);

		//Base class start up
		Manager::startUp();

		return 0;
	}

	//Revert back to normal window mode
	void InputManager::shutDown()
	{
		//Only revert if there is still a window
		if (DM.isStarted()) {
			//Get window
			sf::RenderWindow* window = DM.getWindow();

			//Renable key repeat
			window->setKeyRepeatEnabled(true);
		}

		//Base class shut down
		Manager::shutDown();
	}

    //Translate SFML key events to dragonfly mouse events
    static Mouse::Button SFMLToDFMouse(sf::Mouse::Button e_button)
    {
        switch (e_button) {

        case sf::Mouse::Left:
            return Mouse::Button::LEFT;
            break;
        case sf::Mouse::Right:
            return Mouse::Button::RIGHT;
            break;
        case sf::Mouse::Middle:
            return Mouse::Button::MIDDLE;
            break;
        default:
            return Mouse::Button::UNDEFINED_KEY;
            break;
        }
    }

    //Translate SFML key events to dragonfly key events
    static Keyboard::Key SFMLToDFKey(sf::Keyboard::Key e_key)
    {
        switch (e_key) {
        case sf::Keyboard::Space:
            return Keyboard::Key::SPACE;
            break;
        case sf::Keyboard::Return:
            return Keyboard::Key::RETURN;
            break;
        case sf::Keyboard::Escape:
            return Keyboard::Key::ESCAPE;
            break;
        case sf::Keyboard::Tab:
            return Keyboard::Key::TAB;
            break;
        case sf::Keyboard::Left:
            return Keyboard::Key::LEFTARROW;
            break;
        case sf::Keyboard::Right:
            return Keyboard::Key::RIGHTARROW;
            break;
        case sf::Keyboard::Up:
            return Keyboard::Key::UPARROW;
            break;
        case sf::Keyboard::Down:
            return Keyboard::Key::DOWNARROW;
            break;
        case sf::Keyboard::Pause:
            return Keyboard::Key::PAUSE;
            break;
        case sf::Keyboard::Dash:
            return Keyboard::Key::MINUS;
            break;
        case sf::Keyboard::Equal:
            return Keyboard::Key::PLUS;
            break;
        case sf::Keyboard::Tilde:
            return Keyboard::Key::TILDE;
            break;
        case sf::Keyboard::Period:
            return Keyboard::Key::PERIOD;
            break;
        case sf::Keyboard::Comma:
            return Keyboard::Key::COMMA;
            break;
        case sf::Keyboard::Slash:
            return Keyboard::Key::SLASH;
            break;
        case sf::Keyboard::LControl:
            return Keyboard::Key::LEFTCONTROL;
            break;
        case sf::Keyboard::RControl:
            return Keyboard::Key::RIGHTCONTROL;
            break;
        case sf::Keyboard::LShift:
            return Keyboard::Key::LEFTSHIFT;
            break;
        case sf::Keyboard::RShift:
            return Keyboard::Key::RIGHTSHIFT;
            break;
        case sf::Keyboard::F1:
            return Keyboard::Key::F1;
            break;
        case sf::Keyboard::F2:
            return Keyboard::Key::F2;
            break;
        case sf::Keyboard::F3:
            return Keyboard::Key::F3;
            break;
        case sf::Keyboard::F4:
            return Keyboard::Key::F4;
            break;
        case sf::Keyboard::F5:
            return Keyboard::Key::F5;
            break;
        case sf::Keyboard::F6:
            return Keyboard::Key::F6;
            break;
        case sf::Keyboard::F7:
            return Keyboard::Key::F7;
            break;
        case sf::Keyboard::F8:
            return Keyboard::Key::F8;
            break;
        case sf::Keyboard::F9:
            return Keyboard::Key::F9;
            break;
        case sf::Keyboard::F10:
            return Keyboard::Key::F10;
            break;
        case sf::Keyboard::F11:
            return Keyboard::Key::F11;
            break;
        case sf::Keyboard::F12:
            return Keyboard::Key::F12;
            break;
        case sf::Keyboard::A:
            return Keyboard::Key::A;
            break;
        case sf::Keyboard::B:
            return Keyboard::Key::B;
            break;
        case sf::Keyboard::C:
            return Keyboard::Key::C;
            break;
        case sf::Keyboard::D:
            return Keyboard::Key::D;
            break;
        case sf::Keyboard::E:
            return Keyboard::Key::E;
            break;
        case sf::Keyboard::F:
            return Keyboard::Key::F;
            break;
        case sf::Keyboard::G:
            return Keyboard::Key::G;
            break;
        case sf::Keyboard::H:
            return Keyboard::Key::H;
            break;
        case sf::Keyboard::I:
            return Keyboard::Key::I;
            break;
        case sf::Keyboard::J:
            return Keyboard::Key::J;
            break;
        case sf::Keyboard::K:
            return Keyboard::Key::K;
            break;
        case sf::Keyboard::L:
            return Keyboard::Key::L;
            break;
        case sf::Keyboard::M:
            return Keyboard::Key::M;
            break;
        case sf::Keyboard::N:
            return Keyboard::Key::N;
            break;
        case sf::Keyboard::O:
            return Keyboard::Key::O;
            break;
        case sf::Keyboard::P:
            return Keyboard::Key::P;
            break;
        case sf::Keyboard::Q:
            return Keyboard::Key::Q;
            break;
        case sf::Keyboard::R:
            return Keyboard::Key::R;
            break;
        case sf::Keyboard::S:
            return Keyboard::Key::S;
            break;
        case sf::Keyboard::T:
            return Keyboard::Key::T;
            break;
        case sf::Keyboard::U:
            return Keyboard::Key::U;
            break;
        case sf::Keyboard::V:
            return Keyboard::Key::V;
            break;
        case sf::Keyboard::W:
            return Keyboard::Key::W;
            break;
        case sf::Keyboard::X:
            return Keyboard::Key::X;
            break;
        case sf::Keyboard::Y:
            return Keyboard::Key::Y;
            break;
        case sf::Keyboard::Z:
            return Keyboard::Key::Z;
            break;
        case sf::Keyboard::Num1:
            return Keyboard::Key::NUM1;
            break;
        case sf::Keyboard::Num2:
            return Keyboard::Key::NUM2;
            break;
        case sf::Keyboard::Num3:
            return Keyboard::Key::NUM3;
            break;
        case sf::Keyboard::Num4:
            return Keyboard::Key::NUM4;
            break;
        case sf::Keyboard::Num5:
            return Keyboard::Key::NUM5;
            break;
        case sf::Keyboard::Num6:
            return Keyboard::Key::NUM6;
            break;
        case sf::Keyboard::Num7:
            return Keyboard::Key::NUM7;
            break;
        case sf::Keyboard::Num8:
            return Keyboard::Key::NUM8;
            break;
        case sf::Keyboard::Num9:
            return Keyboard::Key::NUM9;
            break;
        case sf::Keyboard::Num0:
            return Keyboard::Key::NUM0;
            break;
        default:
            return Keyboard::Key::UNDEFINED_KEY;
        }
    }
	

	//Get input keyboard and mouse and pass events to objects 
    void InputManager::getInput() 
    {
        //The event
        sf::Event e;
        /*
        EventKeyboard heldEvent;
        heldEvent.setKeyboardAction(KEY_DOWN);
        heldEvent.setKey(Keyboard::UNDEFINED_KEY);
        */
       

        //Get events from window while it's open
        while (DM.getWindow()->pollEvent(e)) {
            //Check type of event
            //KEYBOARD
            

            if (e.type == sf::Event::KeyPressed) {
                //Create event
                EventKeyboard keyEvent;
                //Set action
                keyEvent.setKeyboardAction(KEY_PRESSED);
                //Set key
                keyEvent.setKey(SFMLToDFKey(e.key.code));
                //Send event to objects
                WM.onEvent(&keyEvent);
            }
            if (e.type == sf::Event::KeyReleased) {
                //Create event
                EventKeyboard keyEvent;
                //Set action
                keyEvent.setKeyboardAction(KEY_RELEASE);
                //Set key
                keyEvent.setKey(SFMLToDFKey(e.key.code));
                //Send event to objects
                WM.onEvent(&keyEvent);
            }
            //MOUSE
            if (e.type == sf::Event::MouseButtonPressed) {
                //Create event
                EventMouse mouseEvent;
                //Set action
                mouseEvent.setMouseAction(CLICKED);
                //Set button
                mouseEvent.setMouseButton(SFMLToDFMouse(e.mouseButton.button));
                //Set position of mouse 
                mouseEvent.setMousePosition(Vector(static_cast<float>(e.mouseButton.x), e.mouseButton.y));
                //Send event to objects
                WM.onEvent(&mouseEvent);
            }
            if (e.type == sf::Event::MouseMoved) {
                //Create event
                EventMouse mouseEvent;
                //Set action
                mouseEvent.setMouseAction(MOVED);
                //Set position of mouse 
                mouseEvent.setMousePosition(Vector(e.mouseButton.x, e.mouseButton.y));
                //Send event to objects
                WM.onEvent(&mouseEvent);
            }
        }
    }



 
}//End of namespace