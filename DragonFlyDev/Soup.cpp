#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "Color.h"
#include "Player.h"
#include "Enemy.h"

void loadResources(void) {

	//TODO load in all sprite files
	char combinedFile[100];
	char combinedLabel[100];
	for (int i = 1; i < 8; i++) {
		sprintf_s(combinedFile, sizeof(combinedFile), "Sprites/Enemy Sprites/E%d.txt", i);
		sprintf_s(combinedLabel, sizeof(combinedLabel), "E%d", i);
		//printf("File: %s, label: %s", combinedFile, combinedLabel);
		RM.loadSprite(combinedFile, combinedLabel);
	}

	char combinedFileEnemy[100];
	char combinedLabelEnemy[100];
	for (int i = 1; i < 4; i++) {
		sprintf_s(combinedFileEnemy, sizeof(combinedFileEnemy), "Sprites/Player Sprites/P%d.txt", i);
		sprintf_s(combinedLabelEnemy, sizeof(combinedLabelEnemy), "P%d", i);
		//printf("File: %s, label: %s", combinedFile, combinedLabel);
		RM.loadSprite(combinedFileEnemy, combinedLabelEnemy);
	}

}


void populateWorld(void) {

	new Player();

	//new spawner
	new Enemy;
	new Enemy;
	new Enemy;
	new Enemy;
	new Enemy;

	//TODO load in all sounds

}

int main(int argc, char* argv[]) {

	//Start up game manager
	if (GM.startUp() == -1)
	{
		LM.writeLog("Error starting game manager!");
		GM.shutDown();
		return 1;
	}

	//Load game resources
	loadResources();

	//Populate world with objects
	populateWorld();

	LM.setFlush(true);

	GM.run();

	GM.shutDown();
	return 0;

}
