#pragma once

#include "Object.h"
#include "Sprite.h"
#include "Vector.h"
#include "EventCollision.h"
#include "DisplayManager.h"


using namespace df;


class Enemy : df::Object {

private:

	//Filter collisions 
	void filterCollision(const df::EventCollision* p_c);

	//array of all possible sprites
	Sprite* baseSprites[25];

	//Current sprite index
	int spriteIndex;

	//Moves to right side of screen 
	void moveToStart();

	//Add sprite to array
	int addSprites();

	//array of all possible spawn points
	Vector spawnPoints[3];

	//this object's spawn point
	Vector spawnPoint;

public:
	Enemy();
	~Enemy();

	//Handles events for enemy
	int eventHandler(const df::Event* p_e) override;
};

