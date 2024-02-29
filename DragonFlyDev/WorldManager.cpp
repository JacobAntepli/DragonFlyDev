
//Included resources
#include "DisplayManager.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "utility.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "ViewObject.h"

namespace df {

    //Constructer defintion
    WorldManager::WorldManager() {

        //Set type
        setType("World Manager");

        //Initialize variables
        m_boundry = Box(Vector(0, 0), 0, 0);
        m_view = m_boundry;
        p_view_following = NULL;
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
        LM.writeLog(-5, "Retreiving all objects\n");
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
        LM.writeLog(-2, "Updating game world\n");

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
        Utility ut; 

        //Make iterator with updates object list
        ObjectListIterator it(&m_updates);

        for (int i = 0; i < MAX_ALTITUDE+1; i++) {
            //Call draw method for all objects
            for (it.first(); !it.isDone(); it.next()) {   
                //Bounding box for object 
                Box temp_box = ut.getWorldBox(it.currentObject());

                
                if ((ut.boxIntersectsBox(temp_box, m_view) || dynamic_cast <ViewObject*>(it.currentObject())) && (it.currentObject()->getAltitude() == i)) {
                    it.currentObject()->draw();
                }
            }
        }
    }

    //Sends events to all game objects in m_update
    void WorldManager::onEvent(const Event* p_event){

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

        //World position bounding box for object at where
        Box objectBox = ut.getWorldBox(p_o, where);
        for (it.first(); !it.isDone(); it.next()) {

            Box b_temp = ut.getWorldBox(it.currentObject());

            //Filter that it doesn't check itself and that object is solid and then finally check if boxes intersect
            if (it.currentObject() != p_o && it.currentObject()->isSolid() && ut.boxIntersectsBox(objectBox,b_temp)){
                //If all conditions met put in list
                collidedObjects.insert(it.currentObject());
                LM.writeLog(-3, "Object collision at location (%d,%d) with objects with id %d and %d\n",
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

        //Utility object for uses
        Utility ut;

        //Get original placement
        Box orig_box = ut.getWorldBox(p_o);

        //Move object 
        p_o->setPosition(where);

        //Move view if needed
        if (p_view_following = p_o) {
            setViewPosition(p_o->getPosition());
        }

        //Get new placement 
        Box new_box = ut.getWorldBox(p_o);

        //Check if object is out of window bounds by checking it''s bounding box
        if (ut.boxIntersectsBox(orig_box,m_boundry) && !ut.boxIntersectsBox(new_box,m_boundry)) {

           
            EventOut eo;
            p_o->eventHandler(&eo);
            
            LM.writeLog(-1, "Object with id %d was sent an out of bounds evet\n", p_o->getId());
        }

        return 0;
    }

    void WorldManager::setBoundary(Box new_boundary)
    {
        m_boundry = new_boundary;
    }

    Box WorldManager::getBoundary() const
    {
        return m_boundry;
    }

    void WorldManager::setView(Box new_view)
    {
        m_view = new_view;
    }

    Box WorldManager::getView() const
    {
        return m_view;
    }

    void WorldManager::setViewPosition(Vector view_pos)
    {
        //Ensure horizontal is not out of bounds
        int x = view_pos.getX() - m_view.getHorizontal() / 2;
        
        if (x + m_view.getHorizontal() > m_boundry.getHorizontal()) {
            x = m_boundry.getHorizontal() - m_view.getHorizontal();
        }

        if (x < 0) {
            x = 0; 
        }

        //Ensure vertical is not out of bounds
        int y = view_pos.getY() - m_view.getVertical() / 2;

        if (y + m_view.getVertical() > m_boundry.getVertical()) {
            y = m_boundry.getVertical() - m_view.getVertical();
        }

        if (y < 0) {
            y = 0;
        }

        //Set view 
        Vector new_corner(x, y);
        m_view.setCorner(new_corner);
    }

    int WorldManager::setViewFollowing(Object* p_new_view_following)
    {

        //Null turns off following
        if (p_new_view_following == NULL) {
            p_view_following = NULL;
            return 0; 
        }

        //Ensure that object exists
        bool exists = false;

        //Make iterator with updates object list
        ObjectListIterator it(&m_updates);
        for (it.first(); !it.isDone(); it.next()) {
            if (it.currentObject() == p_new_view_following) {
                exists = true;
            }
        }

        //Not found
        if (!exists) {
            return -1;
        }

        //Object exists, return 
        p_view_following = p_new_view_following;
        setViewPosition(p_view_following->getPosition());
        
        return 0;
    }

}//End of namespace