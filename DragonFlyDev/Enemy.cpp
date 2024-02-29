#include "Enemy.h"
#include "EventOut.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "Vector.h"
#include "Player.h"
#include "Rounds.h"

using namespace df;
Enemy::Enemy()
{
	setType("Enemy");

	configureSpawn();

	//Set hardness 
	setSolidness(df::SOFT);

	//eventually change this to make the range close to the index of the player sprite
	spriteIndex = (int)rand() % 24;

	//Add sprites to array
	addSprites();

	//Set initial sprite
	setSprite(baseSprites[spriteIndex]->getLabel());

	//set velocity
	configureVelocity();


	//Marked
	marked = false;
}

Enemy::Enemy(Object* player)
{
	setType("Enemy");

	configureSpawn();

	//Set hardness 
	setSolidness(df::SOFT);



	//set velocity
	p_player = player;
	Vector velocity = Vector((p_player->getPosition().getX() - rand() % 7) - getPosition().getX(),
							 (p_player->getPosition().getY() - rand() % 7) - getPosition().getY());
	velocity.normalize();
	velocity.scale(.2);
	printf("Object made with velocity (%f,%f)\n", velocity.getX(), velocity.getY());
	setVelocity(velocity);

	//eventually change this to make the range close to the index of the player sprite
	Player* play = (Player*)p_player;
	if (play->getAlphabetIndex() < 20) {
		//spriteIndex = play->getAlphabetIndex() + ((int)rand() % +(play->getAlphabetIndex() + 4));
		spriteIndex = rand() % ((play->getAlphabetIndex() + 4) - play->getAlphabetIndex()) + play->getAlphabetIndex();
	}
	else {
		//spriteIndex = 20 + ((int)rand() % +24);
		spriteIndex = rand() % (26 - 20) + 20;
	}

	//Add sprites to array
	addSprites();

	//Set initial sprite
	setSprite(baseSprites[spriteIndex]->getLabel());
	

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
		printf("Received out event at position (%.02f,%.02f)\n",getPosition().getX(),getPosition().getY());
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
		new Enemy(p_player);
		marked = true;
	}
	if(p_c->getObject2()->getType() == "Player" && !marked) {
		Player* player = (Player*)p_c->getObject2();
		player->checkEnemyIndex(this);
		WM.markForDelete(this);
		new Enemy(p_player);
		marked = true;
		
	}
}

int Enemy::addSprites()
{
	char combined[32];
	for (int i = 0; i < 26; i++) {
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
	spawnPoints[3] = Vector(DM.getHorizontal()+10, DM.getVertical()/ 2);		//right

	//set spawn index to number randomly from 0 to 3
	spawnIndex = (int)rand() % 4;

	spawnPoint = spawnPoints[spawnIndex];

	//set position to corresponding spawn point
	WM.moveObject(this, spawnPoint);

	printf("Spawn position: (%.02f,%.02f) from spawnindex %d\n", getPosition().getX(), getPosition().getY(),spawnIndex);

}

void Enemy::out()
{
	switch (spawnIndex)
	{
	case (0): //if spawned in at top of screen
		if (getPosition().getY() > 0)
		{
			WM.markForDelete(this);
			//Spawn new enemy
			new Enemy(p_player);
		}
		break;
	case (1): //if spawned in bottom of screen
		if (getPosition().getY() < DM.getVertical())
		{
			WM.markForDelete(this);
			//Spawn new enemy
			new Enemy(p_player);
		}
		break;
	case (2): //if spawned in left of screen
		if (getPosition().getX() > 0)
		{
			WM.markForDelete(this);
			//Spawn new enemy
			new Enemy(p_player);
		}
		break;
	case(3): //if spawned in right of screen
		if (getPosition().getX() < DM.getHorizontal())
		{
			WM.markForDelete(this);
			//Spawn new enemy
			new Enemy(p_player);
		}
		break;
	default:
		break;
	}

}

void Enemy::configureVelocity()
{
	switch (spawnIndex)
	{
	case (0): //if spawned in at top of screen
		setVelocity(Vector(2 - rand() % 4, 0.2));
		break;
	case (1): //if spawned in bottom of screen
		setVelocity(Vector(2 - rand() % 4, -.2));
		break;
	case (2): //if spawned in left of screen
		setVelocity(Vector(0.8, 1 - rand() % 2));
		break;
	case(3): //if spawned in right of screen
		setVelocity(Vector(0.8, 1 - rand() % 2));
		break;
	default:
		break;
	}
}
