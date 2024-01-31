#ifndef __VECTOR_H__
#define __VECTOR_H__

namespace df {

	class Vector {

	private:
		//Horizontal 
		float m_x;
		//Vertical
		float m_y;

	public:

		//Create Vector
		Vector(float int_x, float int_y);

		//Default Vector
		Vector();

		//Get and set for x
		void setX(float new_x);
		float getX() const;

		//Get and set for y
		void setY(float new_y);
		float getY() const;

		//Set new x and y
		void setXY(float new_x, float new_y);

		//Get magnitude
		float getMagnitude() const;

		//Normalize vector
		void normalize();

		//Scale vector
		void scale(float s);

		//Add two vectors, return the sum
		Vector operator+(const Vector& other) const;

	};//End of class
}//End of namespace

#endif // !__VECTOR_H__
