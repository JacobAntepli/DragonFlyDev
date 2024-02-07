
//Included resources
#include "GameManager.h"
#include "LogManager.h"
#include "Clock.h"
#include "EventStep.h"
#include "DisplayManager.h"
#include <Windows.h>



namespace df{

	//Constructer definition
	GameManager::GameManager() {

		//Set type
		setType("Game Manager");

		//Initialize variables
		game_over = false;
		frame_time = FRAME_TIME_DEFAULT;
		loop_time = 0;
		intended_sleep_time = 0;
		loops = 0;
		
	}

	//Get the only instance of the game manager
	GameManager& GameManager::getInstance() {

		//The instance
		static GameManager game_manager;
		return game_manager;
	}

	//Start up game manager 
	int GameManager::startUp() {

		//Start up different managers
     	LM.startUp();
		WM.startUp();
		DM.startUp();

		//Base class start up
		Manager::startUp();

		//Set timer resolution
		timeBeginPeriod(1);

		//Ensure everything started
		if (Manager::isStarted() && game_over == false) {

			LM.writeLog("Game Manager started successfully\n");		
			return 0;
		}
		else {

			LM.writeLog(2, "Game manager did no start up correctly\n");
			return -1;
		}
	}

	//Shut down game manager and loop
	void GameManager::shutDown() {

		//Shut down other classes
		LM.writeLog(0, "Shutting down Log Manager\n");
		LM.shutDown();
		WM.shutDown();
		DM.shutDown();


		//If game loop is not shut down, do so
		if (game_over != true) {

			bool new_game_over = true;
			setGameOver(new_game_over);
		}

		//Base manager shutdown
		Manager::shutDown();

		// Clear time resolution
		timeEndPeriod(1);

		

		LM.writeLog(1, "Shut down Game Manager\n");
	}

	//Get game over status
	bool GameManager::getGameOver() const {

		return game_over;
	}

	//Set game over status
	void GameManager::setGameOver(bool new_game_over) {

		game_over = new_game_over;
		
		LM.writeLog(0, "Game over set to true\n");
	}

	//Get current frame time;
	int GameManager::getFrameTime() const {

		return frame_time;
	}

	//The game loop
	void GameManager::run() {

		//Clock object
		Clock clock;

		LM.writeLog(0, "Starting game loop\n");

		while (!getGameOver()){

			//Reset loop time
			loop_time = 0;

			//Incriment number of loops
			loops++;

			//Start timer
			clock.delta();
			loop_time = clock.split() / 1000;
			
			//Get all objects currently in the world 
			all_objects = WM.getAllObjects();
			
			//Do game stuff
			//Send all objects step event
			EventStep step(1);
			onEvent(&step);

			//Update game world
			WM.update();

			//Draw all objects
			WM.draw();

			//Swap buffer
			DM.swapBuffers();
			
			intended_sleep_time = frame_time - loop_time;//Calculate sleep time

        	Sleep(intended_sleep_time);//Sleep 

			//Commented out for cleaness, you can uncomment to check frame rate
			//printf("Frame: %d\n", intended_sleep_time);

			//Exit after 100 loops for testing
			if (loops == 100) {
				shutDown();
			}
			
		}
		LM.writeLog(0, "Exiting game loop\n");
	}

	//Sends events to all game objects in m_update
	void GameManager::onEvent(const Event *p_event) {

		ObjectListIterator it(&all_objects);
		for(it.first(); !it.isDone(); it.next()){
			it.currentObject()->eventHandler(p_event);
		}
	}
}//End of name space