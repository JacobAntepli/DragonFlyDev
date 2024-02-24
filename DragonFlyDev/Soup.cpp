#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "Color.h"
#include "Player.h"


void loadResources(void) {

	//TODO load in all sprite files
	//for (int i = 1; i <= 25; i++) {
		RM.loadSprite("Sprites/Player Sprites/P1.txt", "P1");
	//}

}


void populateWorld(void) {

	new Player();

	//new spawner

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
