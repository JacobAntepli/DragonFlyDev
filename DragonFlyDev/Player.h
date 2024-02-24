#ifndef __PLAYER_H__
#define __PLAYER_H__

//Included resources
#include "Object.h"
#include "Sprite.h"
#include "EventKeyboard.h"
#include "Vector.h"


using namespace df;
class Player : df::Object {

private:

	//Keyboard events
	void kbd(const df::EventKeyboard* p_keyboard_event);

	//Move function
	void move(Vector pos);

	//Filter collision
	void filterCollisions();

	//An array of sprites for basefont 
	Sprite* baseSprites[25];

	//Current sprite index 
	int currentIndex; 

	//Counter for sprites
	int spriteCounter;

	//Movement variables and functions
	int move_slowdown; //Limiting rate of movement 
	int move_countdown;



public:

	Player();
	~Player();

	//Move player in specficed direction
	void move(Vector direction);

	//Handles events for player
	int eventHandler(const df::Event* p_e) override;








};//End of class
#endif // !__PLAYER_H__
