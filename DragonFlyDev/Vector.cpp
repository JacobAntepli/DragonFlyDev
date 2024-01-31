
#include "Vector.h"
#include <math.h>

namespace df {

	//Default constructer definition
	Vector::Vector() {

		//Default values are (0,0)
		m_x = 0;
		m_y = 0;
	}

	//Non default constructer definition
	Vector::Vector(float int_x, float int_y) {

		m_x = int_x;
		m_y = int_y;
	}

	//Set x component
	void Vector::setX(float new_x) {

		m_x = new_x;
	}

	//Get x component
	float Vector::getX() const {

		return m_x;
	}

	//Set y component
	void Vector::setY(float new_y) {

		m_y = new_y;
	}

	//Get y component 
	float Vector::getY() const {

		return m_y;
	}

	//Set x and y components
	void Vector::setXY(float new_x, float new_y) {

		m_x = new_x;
		m_y = new_y;
	}

	//Get magnitude
	float Vector::getMagnitude() const {

		return sqrt(m_x * m_x + m_y * m_y);
	}

	//Scale vector
	void Vector::scale(float s) {

		m_x = m_x * s;
		m_y = m_y * s;
	}

	//Normalize vector
	void Vector::normalize() {

		//Get magnitude of current vector 
		float mg = getMagnitude();

		//If the magnitude is greater then 0 normalize the values by the magnitude
		if (mg > 0) {
			m_x = m_x / mg;
			m_y = m_y / mg;
		}
	}

	//Operater to add vectors
	Vector Vector::operator+(const Vector& other) const {

		//New vector
		Vector v;

		//Add vectors
		v.m_x = m_x + other.getX();
		v.m_y = m_y + other.getY();

		return v;	
	}

}//End of namespace