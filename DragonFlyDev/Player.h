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

	const int MAX_INDEX = 25;

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

	//Maximum number of lives
	int max_lives;

	//Current number of lives
	int cur_lives;

	//Number of rounds won
	int num_rounds;

	//Movement variables and functions
	int move_slowdown; //Limiting rate of movement 
	int move_countdown;

	//Smooth movementt
	void smoothMove();

	//Countdown for when the player
	void step();

	

	

public:

	//Constructer 
	Player();

	//Player destructer 
	~Player();

	//Add sprite to array
	int addSprites();

	//Handles events for player
	int eventHandler(const df::Event* p_e) override;

	//Get index of player
	int getAlphabetIndex();

	//Checks if enemy is correct
	void checkEnemyIndex(Enemy* enemy);

	//Get number of rounds
	int getRounds() const;

};//End of class

