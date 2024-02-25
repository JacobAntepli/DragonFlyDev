#include "Enemy.h"
#include "EventOut.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "Player.h"

using namespace df;

Enemy::Enemy()
{
	setType("Enemy");

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

	//set position
	moveToStart();

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

void Enemy::moveToStart()
{
	//Temporary vector
	df::Vector temp_pos;

	//Get world size 
	float world_horiz = WM.getBoundary().getHorizontal();
	float world_vert = WM.getBoundary().getVertical();

	// x is off right side of window
	temp_pos.setX(world_horiz + rand() % (int)world_horiz + 3.0f);

	// y is in vertical range
	temp_pos.setY(rand() % (int)(world_vert - 4) + 4.0f);

	
	// If collision, move right slightly until empty space.
	df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
	while (!collision_list.isEmpty()) {
		temp_pos.setX(temp_pos.getX() + 1);
		collision_list = WM.getCollisions(this, temp_pos);
	}
	

	//Move object 
	WM.moveObject(this, temp_pos);

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
