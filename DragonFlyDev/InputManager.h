#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

//Inlcuded resources
#include "Manager.h"

namespace df {

	//Two letter acronym 
	#define IM df::InputManager::getInstance()

	class InputManager : public Manager {

	private:

		//Singleton assurance methods and constructers
		InputManager();
		InputManager(InputManager const&);
		void operator=(InputManager const&);

	public:
		
		//Get the singleton for input manager
		static InputManager& getInstance();

		//Get window ready for input capture
		//Return 0 on success, -1 on failure
		int startUp();

		//Revert back to normal window mode
		void shutDown();

		//Get input keyboard and mouse and pass events to objects 
		void getInput() const;

	

		



	};//End of class
}//End of namespace

#endif
