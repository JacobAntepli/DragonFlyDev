#include "Enemy.h"
#include "EventOut.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "Vector.h"
#include "Player.h"

using namespace df;

Enemy::Enemy()
{
	setType("Enemy");

	configureSpawn();

	//Set hardness 
	setSolidness(df::SOFT);

	//eventually change this to make the range close to the index of the player sprite
	spriteIndex = (int)rand() % 3;

	//Add sprites to array
	addSprites();

	//Set initial sprite
	setSprite(baseSprites[spriteIndex]->getLabel());

	//set velocity
	setVelocity(df::Vector(-.25, 0));

	//Marked
	marked = false;
}

Enemy::~Enemy()
{
	
}

int Enemy::eventHandler(const df::Event* p_e)
{
	//checks letter left screen?
	if (p_e->getType() == df::OUT_EVENT) {
		out();
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

int Enemy::getSpriteIndex() const
{
	return spriteIndex;
}


void Enemy::filterCollision(const df::EventCollision* p_c)
{

	//only respond to collisions with player
	if (p_c->getObject1()->getType() == "Player" && !marked) {
		Player* player = (Player*)p_c->getObject1();
		player->checkEnemyIndex(this);
		WM.markForDelete(this);
		new Enemy;
		marked = true;
	}
	if(p_c->getObject2()->getType() == "Player" && !marked) {
		Player* player = (Player*)p_c->getObject2();
		player->checkEnemyIndex(this);
		WM.markForDelete(this);
		new Enemy;
		marked = true;
		
	}
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

void Enemy::configureSpawn()
{
	//add all spawn points to array of spawns
	spawnPoints[0] = Vector(DM.getHorizontal() / 2 , -10);						//top
	spawnPoints[1] = Vector(DM.getHorizontal() / 2, DM.getVertical() + 10);		//bottom
	spawnPoints[2] = Vector(-10, DM.getVertical() / 2);							//left
	spawnPoints[3] = Vector(DM.getHorizontal() + 10, DM.getVertical() / 2);		//right

	//set spawn index to number randomly from 0 to 3
	spawnIndex = (int)rand() % 3;

	spawnPoint = spawnPoints[spawnIndex];

	//set position to corresponding spawn point
	WM.moveObject(this, spawnPoint);

}

void Enemy::out()
{
	switch (spawnIndex)
	{
	case (0): //if spawned in at top of screen
		if (getPosition().getY() > 0)
		{
			WM.markForDelete(this);
		}
		break;
	case (1): //if spawned in bottom of screen
		if (getPosition().getY() < DM.getVertical())
		{
			WM.markForDelete(this);
		}
		break;
	case (2): //if spawned in left of screen
		if (getPosition().getX() > 0)
		{
			WM.markForDelete(this);
		}
		break;
	case(3): //if spawned in right of screen
		if (getPosition().getX() < DM.getHorizontal())
		{
			WM.markForDelete(this);
		}
		break;
	default:
		break;
	}
}
