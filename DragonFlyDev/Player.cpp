

//Included resources 
#include "Player.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "Points.h"
#include "EventView.h"
#include "Rounds.h"


using namespace df;



Player::Player()
{
	//Starting sprite index
	current_index = 0; 

	//Move slowdown 
	move_slowdown = 2;
	move_countdown = move_slowdown;

	addSprites();

	//Set initial sprite
	setSprite(baseSprites[current_index]->getLabel());

	//Set type
	setType("Player");

	//Set initial pos to center of screen
	setPosition(Vector(WM.getBoundary().getHorizontal()/2, WM.getBoundary().getVertical()/2));

	RM.getMusic("music")->play(true);
}

Player::~Player()
{
}

int Player::addSprites()
{
	char combined[32];

	for (int i = 0; i < 25; i++) {
		sprintf_s(combined,sizeof(combined), "P%d", i+1);
		//printf("%s", combined);
		baseSprites[i] = RM.getSprite(combined);
	}
	return 0;
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
	if ((new_pos.getY() > 0 && new_pos.getY() < WM.getBoundary().getVertical() - 1)
		&&(new_pos.getX() > 0 && new_pos.getX() < WM.getBoundary().getHorizontal() -1)){

		WM.moveObject(this, new_pos);
	}		
}

int Player::eventHandler(const df::Event* p_e)
{

	smoothMove();

	//Checks for step events
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	//Checks for keyboard events
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}

	return 0;
}

int Player::getAlphabetIndex()
{
	return current_index;
}


void Player::kbd(const df::EventKeyboard* p_keyboard_event)
{
	switch (p_keyboard_event->getKey()) {


	case df::Keyboard::ESCAPE:// quit
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			GM.setGameOver(true);
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

void Player::checkEnemyIndex(Enemy* enemy)
{
	//Adjust player index accordingly based on if it's the next letter in the alphabets
	if (enemy->getSpriteIndex() == current_index + 1) {
		adjustIndex(1);
	}
	else {
		adjustIndex(-1);
	}
}

void Player::adjustIndex(int modifier)
{
	//Incriment index by the modifier 
	current_index += modifier;

	//Check to see if it's the last letter needed 
	if (current_index >= MAX_INDEX || current_index < 0) {
		//Increase  point count
		//Add 10 points.
		if (!(current_index < 0)) {
			df::EventView ev(POINTS_STRING, 10, true);
			WM.onEvent(&ev);
			df::EventView evr(ROUNDS_STRING, 1, true);
			WM.onEvent(&evr);
			RM.getSound("win")->play();
		}
		else {
			df::EventView ev(POINTS_STRING, -2, true);
			WM.onEvent(&ev);
			RM.getSound("LL")->play();
		}
		current_index = 0; 
		setSprite(baseSprites[current_index]->getLabel());

	}
	else{
		if (modifier < 0) {
			df::EventView ev(POINTS_STRING,-2, true);
			WM.onEvent(&ev);
			RM.getSound("LL")->play();
		}
		else {
			df::EventView ev(POINTS_STRING,1, true);
			WM.onEvent(&ev);
			RM.getSound("Collect")->play();
		}
		//Set new sprite based on index
		setSprite(baseSprites[current_index]->getLabel());
	}
}


void Player::smoothMove()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		move(Vector(0, -1));
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		move(Vector(0, 1));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		move(Vector(-1.5, 0));
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		move(Vector(1.5, 0));
	}
}

void Player::step()
{
	// Move countdown.
	move_countdown--;
	if (move_countdown < 0)
		move_countdown = 0;
}



