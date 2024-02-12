
//Included resources
#include "DisplayManager.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "utility.h"
#include "EventCollision.h"
#include "EventOut.h"

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

        for (it.first(); !it.isDone(); it.next()) {
            if (it.currentObject()->getType() == type) {
                filtered.insert(it.currentObject());
            }
        }

        return filtered;
    }
    
    //Update world
    //Delete all objects marked for deletion
    void WorldManager::update()
    {
        LM.writeLog(0, "Updating game world\n");

        //Move and check for collisions
        ObjectListIterator moveIt(&m_updates);
        for (moveIt.first(); !moveIt.isDone(); moveIt.next()) {
            //Check that object is moving, if it isn't no need to move it
            
            if (moveIt.currentObject()->getVelocity().getMagnitude() != Vector(0, 0).getMagnitude()) {
                    //Get predicted postion
                    Vector pred_pos = moveIt.currentObject()->predictPosition();
                    moveObject(moveIt.currentObject(), pred_pos);
            }
            
        }

        //Copy list for iteration
        ObjectList del = m_deletion;
        ObjectListIterator it(&del);

        //Delete items in list
        for (it.first(); !it.isDone(); it.next()){
            delete(it.currentObject());
        }

        //Clear list
        m_deletion.clear();
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

    //Tell all objects to draw 
    void WorldManager::draw()
    {
        //Make iterator with updates object list
        ObjectListIterator it(&m_updates);

        for (int i = 0; i < MAX_ALTITUDE; i++) {
            //Call draw method for all objects
            for (it.first(); !it.isDone(); it.next()) {
                if(it.currentObject()->getAltitude() == i)
                it.currentObject()->draw();
            }
        }
    }

    //Sends events to all game objects in m_update
    void WorldManager::onEvent(const Event* p_event) {

        ObjectListIterator it(&m_updates);
        for (it.first(); !it.isDone(); it.next()) {
            it.currentObject()->eventHandler(p_event);
        }
    }

    //Return list of what object a given object has collided with
    //Collisions only with solid objects but does not consider if object is solid or not
    ObjectList WorldManager::getCollisions(const Object* p_o, Vector where) const
    {
        //Uttility
        Utility ut;
        //Iterator for current objects in world 
        ObjectListIterator it(&m_updates);
        ObjectList collidedObjects;
        for (it.first(); !it.isDone(); it.next()) {
            //Filter that it doesn't check itself and that object is solid
            if (it.currentObject() != p_o && it.currentObject()->isSolid()  
                && ut.positionsIntersect(p_o->getPosition(), it.currentObject()->getPosition())){

                //If all conditions met put in list
                collidedObjects.insert(it.currentObject());
                LM.writeLog(0, "Object collision at location (%d,%d) with objects with id %d and %d\n",
                    where.getX(), where.getY(), p_o->getId(), it.currentObject()->getId());
            }
        }

        return collidedObjects;
    }

    //Move Object
    //If collision with solid send event
    //Only move if not colliding with a hard object
    //REturn 0 if moved 
    int WorldManager::moveObject(Object* p_o, Vector where)
    {
        //Check solidness
        if (p_o->isSolid()) {
            //Get collided objects
            ObjectList collided = getCollisions(p_o, where);

            //Check that list is not empty
            if (!collided.isEmpty()) {

                //Boolean that controls movement
                bool do_move = true;

                //Make iterator
                ObjectListIterator it(&collided);

                for (it.first(); !it.isDone(); it.next()) {

                    //Create pointer to current object
                    Object* p_temp_o = it.currentObject();

                    //Create collision event
                    EventCollision ec(p_o, p_temp_o, where);

                    p_o->eventHandler(&ec);
                    p_temp_o->eventHandler(&ec);

                    //If both are hard don't move
                    if (p_o->getSolidness() == HARD && p_temp_o->getSolidness() == HARD) {
                        do_move = false;
                    }
                }//End of for loop
                
                //See if object can move
                if (!do_move) {
                    return -1;
                }
            }//End of if(!collided.isEmpty())
        }//End of if(p_o->isSolid())

        //Move object 
        p_o->setPosition(where);

        //Check if object is out of window bounds
        if (p_o->getPosition().getX() > DM.getHorizontal() || p_o->getPosition().getY() > DM.getVertical()) {

            LM.writeLog(0, "Object with id %d was sent an out of bounds evet\n", p_o->getId());
            EventOut eo;
            p_o->eventHandler(&eo);
        }

        return 0;
    }

}//End of namespace