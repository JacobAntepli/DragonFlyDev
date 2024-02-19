#ifndef __SPRITE_H__
#define __SPRITE_H__

//Included resources
#include "Frame.h"

using namespace std;
namespace df {
	class Sprite {

	private:
		//Width of sprite
		int m_width;
		//Height of sprite
		int m_height;
		//Max number of frames a sprite can have
		int m_max_frame_count;
		//Actual number of frames 
		int m_frame_count;
		//Optional color for entire sprite
		Color m_color;
		//Animation slowdown
		int m_slowdown;
		//Array of frames
		Frame* m_frame;
		//Identifying text label
		string m_label;

		//Transparancy level, 0 by default
		char m_transparency;

		//No none parameter constructer
		Sprite();
	public:

		//Create sprite with max frames
		Sprite(int max_frames);

		//Destroy sprite, deallocate frames
		~Sprite();

		//Set frame width
		void setWidth(int new_width);

		//Get frame width
		int getWidth() const;

		//Set frame height
		void setHeight(int new_height);

		//Get frame height
		int getHeight() const;

		//Set color
		void setColor(Color new_color);

		//Get color
		Color getColor() const;

		//Get total frame count
		int getFrameCount() const;
		
		//Add frame to sprite 
		//Return  0 on success, -1 on failure
		int addFrame(Frame new_frame);

		//Get next sprite frame indicated by number
		//Return empty frrame if out of range
		Frame getFrame(int frame_number) const;

		//Get max frames
		int getMaxFrameCount() const;

		//Get next sprite frame
		//Return  0 on success, -1 on failure
		void setLabel(string new_label);

		//Get label
		string getLabel() const;

		//Set animation slowdown
		void setSlowdown(int new_sprite_slowdown);

		//Get animation slowdown
		int getSlowdown() const;

		//Set transparency (0 means none)
		void setTransparency(char new_transparency);

		//Get transparency
		char getTransparency() const;

		//Draw indicated frame centered at vector 
		int draw(int frame_number, Vector pos) const;

		
	};//End of class
}//End of namespace df

#endif //__SPRITE_H__