#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "Color.h"
#include "Player.h"


void loadResources(void) {

	//TODO load in all sprite files
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
