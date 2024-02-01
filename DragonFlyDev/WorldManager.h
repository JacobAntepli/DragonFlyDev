#ifndef __WORLD_MANAGER_H__
#define __WORLD_MANAGER_H__


#include "Manager.h"
#include "ObjectList.h"

using namespace std;
namespace df {

	//Two letter acronym 
	#define WM df::WorldManager::getInstance()

	class WorldManager : public Manager {

	private:
		
		//Private constructer
		WorldManager();

		//Copy prevention
		WorldManager(WorldManager const&);

		//Assignment prevention
		void operator= (WorldManager const&);

		//Objects to be update
		ObjectList m_updates;
		
		//Objects to be deleted
		ObjectList m_deletion;
		
	public:

		//Get single instance of the world manager
		static WorldManager& getInstance();

		//Start up world and set all lists to zero
		//Return 0 on success, -1 on failure
		int startUp();

		//Shutdown up world and destroy all objects
		void shutDown();

		//Insert object into world
		//Return 0 on success, -1 on failure
		int insertObject(Object* p_o);

		//Remove object from world
		//Return 0 on success, -1 on failure
		int removeObject(Object* p_o);

		//Return all objects in current list
		ObjectList getAllObjects() const;

		//Get objects of a certain type
		ObjectList getObjectOfType(string type) const;

		//Update world
		//Delete all objects marked for deletion
		void update();

		//Mark an object for deletion
		//Return 0 on success, -1 on failure
		int markForDelete(Object* p_o);

	};//End of class
}//End of name space
#endif // !__WORLD_MANAGER_H__

