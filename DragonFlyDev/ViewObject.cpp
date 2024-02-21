
//Included resource
#include "ViewObject.h"
#include "WorldManager.h"
#include "utility.h"
#include "DisplayManager.h"
#include "EventView.h"


namespace df {

	ViewObject::ViewObject()
	{
		//Initialize Object variables
		setSolidness(SPECTRAL);
		setAltitude(MAX_ALTITUDE);
		setType("ViewObject");

		//Initialize viewobject variables
		setValue(0);
		setDrawValue();
		setBorder(true);
		setLocation(TOP_CENTER);
		setColor(COLOR_DEFAULT);
	}

	int ViewObject::draw()
	{
		Utility ut;
		string tempstr;
		//Display at view_string + value
		if (m_border) {
			tempstr = "" + getViewString() + " " + ut.toString(m_value) + " ";
		}
		else {
			tempstr = "" + getViewString() + "" + ut.toString(m_value);
		}

		//Draw at position
		Vector pos = ut.viewToWorld(getPosition());
		
		DM.drawString(pos, tempstr, CENTER_JUSTIFIED, getColor());

		if (m_border) {
			Box box(Vector(pos.getX() - tempstr.size() * 0.5f, pos.getY() - 0), tempstr.size(), 1);
		}

		return 0;
	}

	int ViewObject::eventHandler(const Event* p_e)
	{
		//Check event type
		if (p_e->getType() == VIEW_EVENT) {

			//Cast event
			const EventView* p_ve = static_cast<const EventView*> (p_e);

			//Was it for this one
			if (p_ve->getTag() == getViewString()) {
				//Add
				if (p_ve->getDelta()) {
					setValue(getValue() + p_ve->getValue());
				}
				//Set
				else {
					setValue(p_ve->getValue());
				}
			}

			return 0;
		}
	
		//Error if not here
		return -1;
	}

	void ViewObject::setLocation(ViewObjectLocation new_location)
	{
		Vector pos;
		float y_delta = 0;

		// Set new position based on location.
		switch (new_location) {
		case TOP_LEFT:
			pos.setXY(WM.getView().getHorizontal() * 1 / 6, 1);
			if (!getBorder()) {
				y_delta = -1;
			}
			break;
		case TOP_CENTER:
			pos.setXY(WM.getView().getHorizontal() * 3 / 6, 1);
			if (!getBorder()) {
				y_delta = -1;
			}
			break;
		case TOP_RIGHT:
			pos.setXY(WM.getView().getHorizontal() * 5 / 6, 1);
			if (!getBorder()) {
				y_delta = -1;
			}
			break;
		case CENTER_LEFT:
			pos.setXY(WM.getView().getHorizontal() * 1 / 6, WM.getView().getVertical() * 1 / 2);
			y_delta = 0;
			break;
		case CENTER_CENTER:
			pos.setXY(WM.getView().getHorizontal() * 3 / 6, WM.getView().getVertical() * 1 / 2);
			y_delta = 0;
			break;
		case CENTER_RIGHT:
			pos.setXY(WM.getView().getHorizontal() * 5 / 6, WM.getView().getVertical() * 1 / 2);
			y_delta = 0;
			break;
		case BOTTOM_LEFT:
			pos.setXY(WM.getView().getHorizontal() * 1 / 6, WM.getView().getVertical() - 1);
			if (!getBorder()) {
				y_delta = 1;
			}
			break;
		case BOTTOM_CENTER:
			pos.setXY(WM.getView().getHorizontal() * 3 / 6, WM.getView().getVertical() - 1);
			if (!getBorder()) {
				y_delta = 1;
			}
			break;
		case BOTTOM_RIGHT:
			pos.setXY(WM.getView().getHorizontal() * 5 / 6, WM.getView().getVertical() - 1);
			if (!getBorder()) {
				y_delta = 1;
			}
			break;
		}

		// Shift, as needed based on border
		pos.setY(pos.getY() + y_delta);

		//Set position of object to new position
		setPosition(pos);

		// Set new location.
		m_location = new_location;
	}

	ViewObjectLocation ViewObject::getLocation() const
	{
		return m_location;
	}

	void ViewObject::setValue(int new_value)
	{
		m_value = new_value;
	}

	int ViewObject::getValue() const
	{
		return m_value;
	}

	void ViewObject::setBorder(bool new_border)
	{
		//Ensure its not the same border
		if (m_border != new_border) {
			m_border = new_border;

			//Reset location to account for border settings
			setLocation(getLocation());
		}
	}

	bool ViewObject::getBorder() const
	{
		return m_border;
	}

	void ViewObject::setColor(Color new_color)
	{
		m_color = new_color;
	}

	Color ViewObject::getColor() const
	{
		return m_color;
	}

	void ViewObject::setViewString(std::string new_view_string)
	{
		view_string = new_view_string;
	}

	std::string ViewObject::getViewString() const
	{
		return view_string;
	}

	void ViewObject::setDrawValue(bool new_draw_value)
	{
		m_draw_value = new_draw_value;
	}

	bool ViewObject::getDrawValue() const
	{
		return m_draw_value;
	}

}//End of namespace