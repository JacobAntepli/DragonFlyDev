#pragma once
//Included resources
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
	Sprite* baseSprites[26];

	//Current sprite index
	int spriteIndex;

	//Add sprite to array
	int addSprites();

	//array of all possible spawn points
	Vector spawnPoints[4];

	//this object's spawn position
	Vector spawnPoint;

	//index for spawn point
	int spawnIndex;

	//adds spawn points to array, chooses spawn point for this enemy
	void configureSpawn();

	//Object affected 
	bool marked;

	//Handles out events for enemies
	void out();

	//sets velocity based on spawn point
	void configureVelocity();

	Object* p_player;


public:
	Enemy();
	Enemy(Object* player);
	~Enemy();

	//Handles events for enemy
	int eventHandler(const df::Event* p_e) override;

	//Gets the enemies spriteIndex
	int getSpriteIndex() const;
};

