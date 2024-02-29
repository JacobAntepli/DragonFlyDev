#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "Color.h"
#include "Player.h"
#include "Enemy.h"
#include "Points.h"
#include "Rounds.h"
#include "Lives.h"

void loadResources(void) {

	//TODO load in all sprite files
	char combinedFile[100];
	char combinedLabel[100];
	for (int i = 1; i < 27; i++) {
		sprintf_s(combinedFile, sizeof(combinedFile), "Sprites/Enemy Sprites/E%d.txt", i);
		sprintf_s(combinedLabel, sizeof(combinedLabel), "E%d", i);
		//printf("File: %s, label: %s", combinedFile, combinedLabel);
		RM.loadSprite(combinedFile, combinedLabel);
	}

	char combinedFileEnemy[100];
	char combinedLabelEnemy[100];
	for (int i = 1; i < 26; i++) {
		sprintf_s(combinedFileEnemy, sizeof(combinedFileEnemy), "Sprites/Player Sprites/P%d.txt", i);
		sprintf_s(combinedLabelEnemy, sizeof(combinedLabelEnemy), "P%d", i);
		//printf("File: %s, label: %s", combinedFile, combinedLabel);
		RM.loadSprite(combinedFileEnemy, combinedLabelEnemy);
	}

	RM.loadMusic("Audio/Music/alphabet_soup.mp3", "music");

	RM.loadSound("Audio/Sounds/loseLetter.mp3", "LL");
	RM.loadSound("Audio/Sounds/collectLetter.mp3", "Collect");
	RM.loadSound("Audio/Sounds/winRound.mp3", "win");


}


void populateWorld(void) {

	//Create point view object
	new Points;

	//Create rounds view object
	new Rounds;

	//Create lives view object
	new Lives;


	Player* p = new Player;

	//new spawner
	new Enemy((Object*)p);
	new Enemy((Object*)p);
	new Enemy((Object*)p);
	new Enemy((Object*)p);
	new Enemy((Object*)p);
	new Enemy((Object*)p);
	new Enemy((Object*)p);
	new Enemy((Object*)p);
	new Enemy((Object*)p);
	//new Enemy;
	//new Enemy;


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
