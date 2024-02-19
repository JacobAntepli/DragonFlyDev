#ifndef __FRAME_H__
#define __FRAME_H__

//Included resources
#include <string>
#include "Color.h"
#include "Vector.h"

using namespace std;
namespace df {

	class Frame {

	private:
		//Frame width
		int m_width;

		//Frame height
		int m_height;

		//All frames stored as strings
		string m_frame_str;
	public:

		//Empty frame
		Frame();

		//Frame with specifications
		Frame(int new_width, int new_height, string frame_str);

		//Set frame width
		void setWidth(int new_width);

		//Get frame width
		int getWidth() const;

		//Set frame height
		void setHeight(int new_height);

		//Get frame height
		int getHeight() const;

		//Set frame characters (stored as strings)
		void setString(string new_frame_str);

		//Get frame characters
		string getString() const;

		//Draw self, centered at vector 
		//Return 0 on success, -1 on failure
		int draw(Vector position, Color color, char transparency) const;


	};//End of class
}//End of namespace df
#endif //__FRAME_H__
