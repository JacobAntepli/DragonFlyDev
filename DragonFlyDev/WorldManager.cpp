
//Included resources
#include "WorldManager.h"
#include "LogManager.h"

namespace df {

    //Constructer defintion
    WorldManager::WorldManager() {

        //Set type
        setType("World Manager");
    }

    //Gets the only instance of world manager.
    WorldManager& df::WorldManager::getInstance()
    {
        //Make the one and only copy of the world manager
        static WorldManager worldManager;
        return worldManager;
    }

    //Start up world and set all lists to zero
    //Return 0 on success, -1 on failure
    int WorldManager::startUp()
    {
        LM.writeLog(1, "Starting World Manager\n");
        //Base manager start up
        Manager::startUp();

        //Clear object lists
        m_updates.clear();
        m_deletion.clear();

        //Ensure all need variables are correct
        if (Manager::isStarted() && m_updates.isEmpty() && m_deletion.isEmpty()) {

            LM.writeLog(1, "World Manager started succesfully\n");
            return 0;
        }
        else {
            LM.writeLog(10, "World Manager FAILED TO START UP\n");
            return -1;
        }
    }

    //Shutdown up world and destroy all objects
    void WorldManager::shutDown()
    {
        LM.writeLog(0, "Shutting down world manager\n");
        //Copy list for iteration
        ObjectList shutList = m_updates;
        ObjectListIterator it(&shutList);
       
        //Delete every object
        while (!it.isDone() && it.currentObject() != NULL) {
            delete(it.currentObject());
            it.next();
        }
        Manager::shutDown();
    }

    //Insert object into world
    //Return 0 on success, -1 on failure
    int WorldManager::insertObject(Object* p_o)
    {
        
        return m_updates.insert(p_o);
    }

    //Remove object from world
    //Return 0 on success, -1 on failure
    int WorldManager::removeObject(Object* p_o)
    {
        return m_updates.remove(p_o);
    }

    //Return all objects in current list
    ObjectList WorldManager::getAllObjects() const
    {
        LM.writeLog(0, "Retreiving all objects\n");
        return m_updates;
    }

    //Get objects of a certain type
    ObjectList WorldManager::getObjectOfType(string type) const
    {
        LM.writeLog(1, "Retrieving list of type %s\n", type.c_str());
        ObjectList filtered;
        ObjectListIterator it(&m_updates);

        while (!it.isDone()) {
            if (it.currentObject()->getType() == type) {
                filtered.insert(it.currentObject());
            }
            it.next();
        }

        return filtered;
    }
    
    //Update world
    //Delete all objects marked for deletion
    void WorldManager::update()
    {
        LM.writeLog(0, "Updating game world\n");
        //Copy list for iteration
        ObjectList del = m_deletion;
        ObjectListIterator it(&del);

        //Delete items in list
        while (!it.isDone()) {

            delete(it.currentObject());
            it.next();
        }

        //Clear list
        del.clear();
    }

    //Mark an object for deletion
    //Return 0 on success, -1 on failure
    int WorldManager::markForDelete(Object* p_o)
    {
        //Ensure object is not already in the list
        if (!m_deletion.contains(p_o)) {
            
            LM.writeLog(0, "OBJECT %d MARKED FOR DELETION SUCCESSFULLY\n", p_o->getId());
            //Mark object
            m_deletion.insert(p_o);
            return 0;
        }

        LM.writeLog(3, "OBJECT %d NOT MARKED FOR DELETION SUCCESSFULLY\n", p_o->getId());
        return -1;
    }

}//End of namespace