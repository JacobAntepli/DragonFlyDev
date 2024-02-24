

//Included resources 
#include "Player.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "EventStep.h"


using namespace df;

Player::Player()
{
	//Initialize variables
	spriteIndex = 0; 
	move_slowdown = 0;
	move_countdown = 0;

	//Set initial sprite
	setSprite(baseSprites[spriteIndex]->getLabel());

	//Set type
	setType("Player");

	//Set initial pos to center of screen
	setPosition(Vector(WM.getBoundary().getHorizontal()/2, WM.getBoundary().getVertical()/2));

}

Player::~Player()
{
}

void Player::move()
{
}

int Player::eventHandler(const df::Event* p_e)
{
	return 0;
}

int Player::getIndex()
{
	return spriteIndex;
}

void Player::kbd(const df::EventKeyboard* p_keyboard_event)
{
	switch (p_keyboard_event->getKey()) {

	case df::Keyboard::Q:	 // quit
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			WM.markForDelete(this);
		break;


	case df::Keyboard::W:    // Move up
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			//move(-1);
		break;

	case df::Keyboard::S:    // Move down
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			//move(+1);
		break;

	case df::Keyboard::SPACE: // Nuke'm
		if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASE)
			//nuke();
		break;

	}
}

void Player::move(Vector pos)
{
}

void Player::filterCollisions()
{
}


