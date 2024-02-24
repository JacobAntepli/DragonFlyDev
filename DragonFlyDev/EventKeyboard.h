#ifndef __EVENT_KEYBOARD_H__
#define __EVENT_KEYBOARD_H__

//Included resources
#include "Event.h"

namespace df {

	//Event identifier 
	const std::string KEYBOARD_EVENT = "df::keyboard";

	//Types of keyboard actions recognize by dragonfly
	enum EventKeyboardAction {
		UNDEFINED_KEYBOARD_ACTION = -1,
		KEY_PRESSED,
		KEY_RELEASE,
		KEY_DOWN
	};

	//Keys recognized by dragonfly
	namespace Keyboard {

		enum Key {
				UNDEFINED_KEY = 01,
				SPACE, RETURN, ESCAPE, TAB, LEFTARROW, RIGHTARROW, UPARROW, DOWNARROW,
				PAUSE, MINUS, PLUS, TILDE, PERIOD, COMMA, SLASH, LEFTCONTROL,
				RIGHTCONTROL, LEFTSHIFT, RIGHTSHIFT, F1, F2, F3, F4, F5, F6, F7, F8,
				F9, F10, F11, F12, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q,
				R, S, T, U, V, W, X, Y, Z, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7,
				NUM8, NUM9, NUM0,

		};//End of Key enum
	}//End of namespace keyboard


	class EventKeyboard : public Event {

	private:
		//Value of key
		Keyboard::Key m_key_val;
		//Action of key
		EventKeyboardAction m_keyboard_action;

	public:

		//Constructer
		EventKeyboard();

		//Set key in event
		void setKey(Keyboard::Key new_key);

		//Set action in event
		void setKeyboardAction(EventKeyboardAction new_action);

		//Get key in event
		Keyboard::Key getKey() const;

		//Get action in event
		EventKeyboardAction getKeyboardAction() const;

	};
}//End of namespace df
#endif
