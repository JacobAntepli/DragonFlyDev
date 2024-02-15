
//Included resources
#include "Frame.h"
#include "DisplayManager.h"
using namespace std;
namespace df {

	//Empty frame
	Frame::Frame()
	{
		//Initialize variables
		m_height = 0;
		m_width = 0;
		m_frame_str = "";
	}

	//Frame with specifications
	Frame::Frame(int new_width, int new_height, string frame_str)
	{
		//Initialize variables
		m_height = new_height;
		m_width = new_width;
		m_frame_str = frame_str;
	}

	//Set frame width
	void Frame::setWidth(int new_width)
	{
		m_width = new_width;
	}

	//Get frame width
	int Frame::getWidth() const
	{
		return m_width;
	}

	//Set frame height
	void Frame::setHeight(int new_height)
	{
		m_height = new_height;
	}

	//Get frame height
	int Frame::getHeight() const
	{
		return m_height;
	}

	//Set frame characters (stored as strings)
	void Frame::setString(string new_frame_str)
	{
		m_frame_str = new_frame_str;
	}

	//Draw self, centered at vector 
	//Return 0 on success, -1 on failure
	int Frame::draw(Vector position, Color color, char transparency) const
	{
		//Check if empty
		if (m_frame_str.empty()) {
			return -1;
		}

		//Determine offset
		int x_offset = getWidth()/2;
		int y_offset = getHeight()/2;

		//Draw character by character 
		for (int y = 0; y < m_height; y++) {
			for (int x = 0; x < m_width; x++) {
				if (transparency == 0 || m_frame_str[y * getWidth() + x] != transparency) {
					Vector temp_pos(position.getX() + x - x_offset, position.getY() + y - y_offset);
					DM.drawCh(temp_pos, m_frame_str[y * m_width + x], color);
				}
			}//End of x loop
		}//End of y for loop 

		return 0;
	}

}//End of namespace df