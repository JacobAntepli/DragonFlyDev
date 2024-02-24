

//Included resources 
#include "Player.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "EventStep.h"


using namespace df;

Player::Player()
{
	//Starting sprite index
	currentIndex = 0; 

	//Counter sprite
	spriteCounter = 0; 
	
	//Move slowdown 
	move_slowdown = 2;
	move_countdown = 0;

	//Set initial sprite
	setSprite(baseSprites[currentIndex]->getLabel());

	//Set type
	setType("Player");

	//Set initial pos to center of screen
	setPosition(Vector(WM.getBoundary().getHorizontal()/2, WM.getBoundary().getVertical()/2));
}

Player::~Player()
{
}

void Player::move(Vector direction)
{
	//Only move if allowed 
	if (move_countdown > 0) {
		return;
	}
	move_countdown = move_slowdown;

	//Get new position
	df::Vector new_pos(getPosition() + direction);

	//Ensure player stays in bounds 
	if ((new_pos.getY() > 3 && new_pos.getY() < WM.getBoundary().getVertical() - 1)
		&&(new_pos.getX() > 3 && new_pos.getX() < WM.getBoundary().getHorizontal() -1)){

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

	return 0;
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
			move(Vector(0, 1));
		}
		break;

	case df::Keyboard::S:// Move down
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			move(Vector(0, -1));
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
	}
}

void Player::filterCollisions()
{
}


