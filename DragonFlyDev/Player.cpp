

//Included resources 
#include "Player.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "ResourceManager.h"
#include "Enemy.h"

using namespace df;

Player::Player()
{
	//Starting sprite index
	current_index = 0; 

	//Move slowdown 
	move_slowdown = 2;
	move_countdown = 0;

	addSprites();

	//Set initial sprite
	setSprite(baseSprites[current_index]->getLabel());

	//Set type
	setType("Player");

	//Set initial pos to center of screen
	setPosition(Vector(WM.getBoundary().getHorizontal()/2, WM.getBoundary().getVertical()/2));
}

Player::~Player()
{
}

int Player::addSprites()
{
	char combined[10];

	for (int i = 0; i < 7; i++) {
		sprintf_s(combined,sizeof(combined), "P%d", i+1);
		//printf("%s", combined);
		baseSprites[i] = RM.getSprite(combined);
	}
	return 0;
}



void Player::move(Vector direction)
{
	//Only move if allowed 
	/*
	if (move_countdown > 0) {
		return;
	}
	*/
	move_countdown = move_slowdown;

	//Get new position
	df::Vector new_pos(getPosition() + direction);

	//Ensure player stays in bounds 
	if ((new_pos.getY() > 0 && new_pos.getY() < WM.getBoundary().getVertical() - 1)
		&&(new_pos.getX() > 0 && new_pos.getX() < WM.getBoundary().getHorizontal() -1)){

		WM.moveObject(this, new_pos);
	}		
}

int Player::eventHandler(const df::Event* p_e)
{
	//Checks for keyboard events
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
		filterCollisions(p_collision_event);
	}

	return 0;
}

int Player::getIndex()
{
	return current_index;
}

void Player::kbd(const df::EventKeyboard* p_keyboard_event)
{
	switch (p_keyboard_event->getKey()) {

	case df::Keyboard::Q:// quit
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			WM.markForDelete(this);
		}
		break;


	case df::Keyboard::W:// Move up
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			move(Vector(0, -1));
		}
		break;

	case df::Keyboard::S:// Move down
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			move(Vector(0, 1));
		}
		break;

	case df::Keyboard::D://Move right
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			move(Vector(1, 0));
		}
		break;

	case df::Keyboard::A://Move left
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			move(Vector(-1, 0));
		}
		break;

	case df::Keyboard::RIGHTARROW://Incriment up
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			adjustIndex(+1);
		}
		break;


	case df::Keyboard::LEFTARROW://Incriment down
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			adjustIndex(-1);
		}
		break;

	}
}

void Player::filterCollisions(const EventCollision* p_c)
{
	//Ensure if it's an enemy 
	if (p_c->getObject1()->getType() == "Enemy") {

		//Get the enemy via a cast
		const Enemy* enemy = dynamic_cast <const Enemy*> (p_c->getObject1());

		if()



		

	}
	if(p_c->getObject2()->getType() == "Enemy") {

		//Get the enemy via a cast
		const Enemy* enemy = dynamic_cast <const Enemy*> (p_c->getObject1());



	}
}

void Player::adjustIndex(int modifier)
{
	//Incriment index by the modifier 
	current_index += modifier;

	//Check to see if it's the last letter needed 
	if (current_index >= MAX_INDEX || current_index < 0) {
		//Increase  point count

		current_index = 0; 
		setSprite(baseSprites[current_index]->getLabel());
	}
	else {
		setSprite(baseSprites[current_index]->getLabel());
	}





}


