#ifndef __EVENT_MOUSE_H__
#define __EVENT_MOUSE_H__

//Included resources
#include "Event.h"
#include "Vector.h"

namespace df {

	const std::string MSE_EVENT = "df::mouse";

	//Types of mouse actions recognize by dragonfly
	enum EventMouseAction {
		UNDEFINED_MOUSE_ACTION = -1,
		CLICKED,
		MOVED
	};

	//Keys recognized by dragonfly
	namespace Mouse {

		enum Button {
			UNDEFINED_KEY = -1,
			LEFT,
			RIGHT,
			MIDDLE,

		};//End of Button enum
	}//End of namespace Mouse

	class EventMouse : public Event {

	private:
		//Move action
		EventMouseAction m_mouse_action;
		//Mouse Button
		Mouse::Button m_mouse_button;
		//Mouse coordinates
		Vector m_mouse_xy;

	public:

		//Constructer
		EventMouse();

		//Set mouse event action
		void setMouseAction(EventMouseAction new_mouse_action);

		//Get mouse event action
		EventMouseAction getMouseAction() const;

		//Set mouse event button
		void setMouseButton(Mouse::Button new_mouse_button);

		//Get mouse event button
		Mouse::Button getMouseButton() const;

		//Set mouse event position
		void setMousePosition(Vector new_mouse_xy);

		//Get mouse event position
		Vector getMousePosition() const;



	};//End of class
}//End of namespace df
#endif