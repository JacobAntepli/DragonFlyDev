
//Included resources
#include "InputManager.h"
#include "DisplayManager.h"
#include "LogManager.h"

namespace df {

	//Constructer definition
	InputManager::InputManager() {
	}

	//Get the singleton for input manager
	InputManager& InputManager::getInstance()
	{
		static InputManager inputManager;
		return inputManager;
	}

	//Get window ready for input capture
	//Return 0 on success, -1 on failure
	int InputManager::startUp()
	{
		//Check that the display manager is started
		if (!DM.isStarted()) {
			LM.writeLog(10, "UNABLE TO START INPUT MANAGER AS DISPLAY MANAGER IS OFF\n");
			return -1;
		}
		
		//Get window
		sf::RenderWindow* window = DM.getWindow();

		//Prevent keyboard repeat 
		window->setKeyRepeatEnabled(false);

		//Base class start up
		Manager::startUp();

		return 0;
	}

	//Revert back to normal window mode
	void InputManager::shutDown()
	{
		//Only revert if there is still a window
		if (DM.isStarted()) {
			//Get window
			sf::RenderWindow* window = DM.getWindow();

			//Renable key repeat
			window->setKeyRepeatEnabled(true);
		}

		//Base class shut down
		Manager::shutDown();
	}

	//Get input keyboard and mouse and pass events to objects 
	void InputManager::getInput() const
	{
		//The event
		sf::Event e;

		//Get events from window while it's open
		while (DM.getWindow()->pollEvent(e)) {

			switch (e.type) {

			}

		}
	}
}//End of namespace