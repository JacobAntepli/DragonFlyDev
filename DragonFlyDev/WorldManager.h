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

		//World boundry
		Box m_boundry;
		
		//Player view
		Box m_view;

		//Object view is following
		Object* p_view_following;

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

		//Tell all objects to draw themselves
		void draw();

		//Sends events to all game objects in m_update
		void onEvent(const Event* p_event);

		//Return list of what object a given object has collided with
		//Collisions only with solid object but does not consider if object is solid or not 
		ObjectList getCollisions(const Object* p_o, Vector where) const;

		//Move Object
		//If collision with solid send event
		//Only move if there isn't 
		int moveObject(Object* p_o, Vector where);

		// Set game world boundary.
		void setBoundary(Box new_boundary);

		// Get game world boundary.
		Box getBoundary() const;

		// Set player view of game world.
		void setView(Box new_view);

		// Get player view of game world.
		Box getView() const;

		// Set view to center window on position view pos.
		// View edge will not go beyond world boundary.
		void setViewPosition(Vector view_pos);

		// Set view to center window on Object.
		// Set to NULL to stop following.
		// If p new view following not legit, return -1 else return 0.
		int setViewFollowing(Object* p_new_view_following);

	};//End of class
}//End of name space
#endif // !__WORLD_MANAGER_H__

