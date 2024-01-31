

//Included resources
#include "Manager.h"
#include "LogManager.h"


using namespace std;
namespace df {
	//Constructer definition
	Manager::Manager() {

		//SetType
		setType("Manager");

		//intialize variables
		m_is_started = false;
	}

	//Deconstructer defintion
	Manager::~Manager() {

		if (m_is_started) {
			//Close Manager
			shutDown();
		}
	}

	//Start up manager
	int Manager::startUp() {

		//set started bool to true
		m_is_started = true;

		//Ensure it's set to true, return 
		if (m_is_started) {
			return 0;
		}
		else {
			return -1;
		}

	}

	//Shut down manager
	void Manager::shutDown() {

		//set started bool to false
		m_is_started = false;
	}

	//Get type of manager.
	string Manager::getType() const {

		//Return type string
		return m_type;
	}

	//Check to see if manager is started up yet.
	bool Manager::isStarted() const {

		//Return isStarted boolean
		return m_is_started;
	}


	//Set type of manager
	void Manager::setType(std::string type) {

		//Set type to type inputed
		m_type = type;

	}
}


