
//Included resources
#include "Sprite.h"
#include "LogManager.h"
namespace df {

	Sprite::Sprite(int max_frames)
	{
		//Initialize variables
		m_width = 0;
		m_height = 0;
		m_max_frame_count = max_frames;
		m_frame_count = 0;
		m_color = COLOR_DEFAULT;
		m_slowdown = 0;
		m_frame = new Frame[max_frames];
		m_label = "DEFAULT SPRITE LABEL";
		m_transparency = 0;
	}

	Sprite::~Sprite()
	{
		//Check if there is still a frames list
		if (m_frame != NULL) {
			delete[] m_frame;
		}
	}

	void Sprite::setWidth(int new_width)
	{
		m_width = new_width;
	}

	int Sprite::getWidth() const
	{
		return m_width;
	}

	void Sprite::setHeight(int new_height)
	{
		m_height = new_height;
	}

	int Sprite::getHeight() const
	{
		return m_height;
	}

	void Sprite::setColor(Color new_color)
	{
		m_color = new_color;
	}

	Color Sprite::getColor() const
	{
		return m_color;
	}

	int Sprite::getFrameCount() const
	{
		return m_frame_count;
	}

	int Sprite::addFrame(Frame new_frame)
	{
		//Check if sprite is full 
		if (m_frame_count >= m_max_frame_count) {
			LM.writeLog(5,"SPRITE ERROR: ATTEMMTPED TO ADD FRAME TO FULL SPRITE WITH LABEL %s\n",m_label.c_str());
			return -1;
		}
		//Add new frame and incriment count
		m_frame[m_frame_count] = new_frame;
		m_frame_count++;

		return 0;
	}

	Frame Sprite::getFrame(int frame_number) const
	{
		//Check if number is within range
		if (frame_number < 0 || frame_number >= m_frame_count) {
			Frame empty;
			return empty;
		}

		return m_frame[frame_number];
	}

	int Sprite::getMaxFrameCount() const
	{
		return m_max_frame_count;
	}

	void Sprite::setLabel(string new_label)
	{
		m_label = new_label;
	}

	string Sprite::getLabel() const
	{
		return m_label;
	}

	void Sprite::setSlowdown(int new_sprite_slowdown)
	{
		m_slowdown = new_sprite_slowdown;
	}

	int Sprite::getSlowdown() const
	{
		return m_slowdown;
	}


	void Sprite::setTransparency(char new_transparency)
	{
		m_transparency = new_transparency;
	}

	char Sprite::getTransparency() const
	{
		return m_transparency;
	}

	int Sprite::draw(int frame_number, Vector pos) const
	{
		//Check if number is within range
		if (frame_number < 0 || frame_number >= m_frame_count) {
			return -1;
		}

		//Call the frames draw function
		m_frame[frame_number].draw(pos, m_color, m_transparency);
		return 0;
	}
}//End of namespace df