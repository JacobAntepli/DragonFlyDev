

//Included resources
#include "Animation.h"
#include "LogManager.h"

namespace df {

	Animation::Animation()
	{
		//Set variable
		m_p_sprite = NULL;
		m_name = "DEFAULT ANIMATION NAME";
		m_index = 0;
		m_slowdown_count = 0;
	}

	void Animation::setSprite(Sprite* p_new_sprite)
	{
		m_p_sprite = p_new_sprite;
	}

	Sprite* Animation::getSprite() const
	{
		return m_p_sprite;
	}

	void Animation::setName(string new_name)
	{
		m_name = new_name;
	}

	string Animation::getName() const
	{
		return m_name;
	}

	void Animation::setIndex(int new_index)
	{
		m_index = new_index;
	}

	int Animation::getIndex() const
	{
		return m_index;
	}

	void Animation::setSlowdownCount(int new_slowdown_count)
	{
		m_slowdown_count = new_slowdown_count;
	}

	int Animation::getSlowdownCount() const
	{
		return m_slowdown_count;
	}

	int Animation::draw(Vector position)
	{

		//Check if the sprite is null
		if (m_p_sprite == NULL) {
			LM.writeLog(5, "Animaiton Error: Attempted to animate a NULL sprite\n");
			return -1;
		}

		//Draw current frame
		int index = getIndex();
		m_p_sprite->draw(index, position);

		//Animation is frozen
		if (getSlowdownCount() == -1) {
			return 0;
		}
		
		//Incriment count
		int count = getSlowdownCount();
		count++;

		if (count >= m_p_sprite->getSlowdown()) {
			count = 0;

			//Incriment index
			index++;

			if (index >= m_p_sprite->getFrameCount()) {
				index = 0;
			}

			setIndex(index);
		}

		setSlowdownCount(count);

		return 0;
	}

	Box Animation::getBox() const
	{

		//If there is no sprite, return box centered at (0,0)
		if (m_p_sprite == NULL) {
			Box box(Vector(-0.5, -0.5), 0.99, 0.99);
			return box;
		}

		//Create box around sprite
		Vector corner(-1 * m_p_sprite->getWidth() / 2.0, -1 * m_p_sprite->getHeight() / 2.0);
		Box box(corner, m_p_sprite->getWidth(), m_p_sprite->getHeight());

		return box;
	}

}//End of namespace