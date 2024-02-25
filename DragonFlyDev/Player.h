#pragma once
//Included resources
#include "Object.h"
#include "Sprite.h"
#include "EventKeyboard.h"
#include "Vector.h"
#include "EventCollision.h"
#include "Enemy.h"


using namespace df;
class Player : df::Object {

	const int MAX_INDEX = 3;

private:

	//Keyboard events
	void kbd(const df::EventKeyboard* p_keyboard_event);


	//Move player in specficed direction
	void move(Vector direction);

	//Change index
	void adjustIndex(int modifier);

	//An array of sprites for basefont 
	Sprite* baseSprites[25];

	//Current sprite index 
	int current_index; 

	//Movement variables and functions
	int move_slowdown; //Limiting rate of movement 
	int move_countdown;

	

public:

	//Constructer 
	Player();

	//Player destructer 
	~Player();

	//Add sprite to array
	int addSprites();

	//Handles events for player
	int eventHandler(const df::Event* p_e) override;

	int getIndex();

	//Checks if enemy is correct
	void checkEnemyIndex(Enemy* enemy);

};//End of class

