#pragma once

#include "Object.h"
#include "Sprite.h"
#include "Vector.h"


using namespace df;
class Enemy : df::Object {

private:

	//Filter collisions 
	void filterCollision(const df::EventCollision* p_c);

	//array of all possible sprites
	Sprite* baseSprites[3];

	//Current sprite index
	int spriteIndex;


public:
	Enemy();
	~Enemy();

	//Handles events for enemy
	int eventHandler(const df::Event* p_e) override;
}

