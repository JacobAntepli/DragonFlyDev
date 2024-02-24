#include "Enemy.h"
#include "EventOut.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "Vector.h"

using namespace df;

Enemy::Enemy()
{
	setType("Enemy");

	spawnPoints[0] = Vector(-10, DM.getHorizontal() / 2);
	spawnPoints[1] = Vector(DM.getVertical() + 10, DM.getHorizontal() / 2);
	spawnPoints[2] = Vector(DM.getVertical()/2, -10);
	spawnPoints[3] = Vector(DM.getVertical() / 2, DM.getHorizontal() + 10);

	//Set hardness 
	setSolidness(df::SOFT);

	//eventually change this to make the range close to the index of the player sprite
	spriteIndex = (int)rand() % 3;

	//set spawn point to random of four
	spawnPoint = spawnPoints[(int)rand() % 3];

	//Add sprites to array
	addSprites();

	//Set initial sprite
	setSprite(baseSprites[spriteIndex]->getLabel());

	//set velocity
	setVelocity(df::Vector(-.25, 0));

	//set position
	moveToStart();
}

Enemy::~Enemy()
{
	new Enemy;
}

int Enemy::eventHandler(const df::Event* p_e)
{
	//checks letter left screen?
	if (p_e->getType() == df::OUT_EVENT) {
		//WM.markForDelete(this);
		return 1;
	}
	//checks saucer collided with something?
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		filterCollision(p_collision_event); //handled by hit()
		return 1;
	}
	return 0; //otherwise ignored
}


void Enemy::filterCollision(const df::EventCollision* p_c)
{
	//only respond to collisions with player
	if ((p_c->getObject1()->getType() == "Player") &&
		(p_c->getObject2()->getType() == "Player"))
		WM.markForDelete(this);
}

void Enemy::moveToStart()
{
	//Move object 
	WM.moveObject(this, spawnPoint);

}

int Enemy::addSprites()
{
	char combined[10];
	for (int i = 0; i < 4; i++) {
		sprintf_s(combined, sizeof(combined), "E%d", i + 1);
		//printf("%s", combined);
		baseSprites[i] = RM.getSprite(combined);
	}
	return 0;
}
