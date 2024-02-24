#include "Enemy.h"
#include "EventOut.h"
#include "WorldManager.h"


using namespace df;
Enemy::Enemy()
{
	setType("Enemy");

	//eventually change this to make the range close to the index of the player sprite
	spriteIndex = (int)rand() % 3;

	//Set initial sprite
	setSprite(baseSprites[spriteIndex]->getLabel());

	//set position

	//set velocity

}

Enemy::~Enemy()
{
	new Enemy;
}

int Enemy::eventHandler(const df::Event* p_e)
{
	//checks letter left screen?
	if (p_e->getType() == df::OUT_EVENT) {
		WM.markForDelete(this);
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