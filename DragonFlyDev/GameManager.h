#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "Manager.h"
#include "Event.h"
#include "WorldManager.h"

namespace df {

#define GM df::GameManager::getInstance()

	//Default fps in milliseconds
	const int FRAME_TIME_DEFAULT = 33; 

	class GameManager : public Manager {

	private:

		//Constructer 
		GameManager();

		//Copy prevention
		GameManager(GameManager const&);

		//Assignment prevention
		void operator= (GameManager const&);

		//Boolean controlling if the game runs or not
		bool game_over;

		//Target time per loop
		int frame_time;

		//Loop time
		int loop_time;

		//Intended sleep time
		int intended_sleep_time;

		//Number of loops done
		int loops;

		//Object list for all objects in world
		ObjectList all_objects;


	public:

		//Get single instance
		static GameManager& getInstance();

		//Start up
		//Return 0 on success, -1 on failure
		int startUp();

		//Shutdown
		//Return 0 if success, negative if failure
		void shutDown();

		//Set game over to be true
		void setGameOver(bool new_game_over = true);

		//Get game over status
		bool getGameOver() const;

		//Return frame time
		int getFrameTime() const;

		//Run game loop
		void run();

		//Sends events to all game objects in m_update
		void onEvent(const Event *p_event);

	};//End of class
}//End of namespace 














#endif // !__GAME_MANAGER_H__

