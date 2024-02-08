
//Included resources 
#include "EventKeyboard.h"

namespace df {

	//Constructer definition 
	EventKeyboard::EventKeyboard()
	{
		//Set type
		setType(KEYBOARD_EVENT);

		//Initialize variables
		m_key_val = Keyboard::UNDEFINED_KEY;
		m_keyboard_action = UNDEFINED_KEYBOARD_ACTION;
	}

	//Set key in event
	void EventKeyboard::setKey(Keyboard::Key new_key)
	{
		m_key_val = new_key;
	}

	//Set action in event
	void EventKeyboard::setKeyboardAction(EventKeyboardAction new_action)
	{
		m_keyboard_action = new_action;
	}

	//Get key in event
	Keyboard::Key EventKeyboard::getKey() const
	{
		return m_key_val;
	}

	//Get action in event
	EventKeyboardAction EventKeyboard::getKeyboardAction() const
	{
		return m_keyboard_action;
	}

}//End of namespace