#ifndef __ANIMATION_H__
#define __ANIMATION_H__


//Included resources
#include <string>
#include "Sprite.h"
#include "Box.h"

using namespace std;
namespace df {

	class Animation {

	private:
		//Sprite to be animated
		Sprite* m_p_sprite;
		//Sprite name in resource
		string m_name;
		//Current index for frame
		int m_index;
		//Slowdown counter
		int m_slowdown_count;

	public:
		//Animation constructer
		Animation();

		//Set associated Sprite to new one 
		//Note, Sprite is managed by resource manager
		//Set Sprite index to 0(first frame)
		void setSprite(Sprite* p_new_sprite);

		//Get sprite
		Sprite* getSprite() const;

		//Set sprite name in RM
		void setName(string new_name);

		//Get sprite name 
		string getName() const;

		//Set index of current sprite to be frame to be displayed
		void setIndex(int new_index);

		//Get index of current Sprite frame to be displayed 
		int getIndex() const;

		//Set animation slowdown count(-1 means stop animation)
		void setSlowdownCount(int new_slowdown_count);

		//Get animation slowdown count
		int getSlowdownCount() const;

		//Draw single frame centered at position(x,y)
		//Drawing accounts for slowdown, and advances Sprite frame. 
		//Return 0 on success, -1 on failure
		int draw(Vector position);

		//Get bounding box associated with sprite
		Box getBox() const;

	};//End of class
}//End of namespace df
#endif // __ANIMATION_H__