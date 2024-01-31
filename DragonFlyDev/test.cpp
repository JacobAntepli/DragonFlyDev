
//Included resources
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <math.h>
#include <string>

#include "Manager.h"
#include "LogManager.h"
#include "Clock.h"
#include "GameManager.h"
#include "Vector.h"
#include "Object.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"


using namespace df;
using namespace std;
//Test function for the base manager class
int testBaseManager() {

    Manager managerTest = Manager::Manager();

    managerTest.startUp();

    printf("Running tests for Manager:\n");

    //Testing if manager started up correctly
    if (managerTest.isStarted()) {
        printf("[startUp]: SUCCESS\n");
    }
    else {
        printf("[startUp]: FAILURE\n");
        return -1;
    }

    //Testing to see if manager is right type
    if (managerTest.getType()._Equal("Manager")) {
        printf("[getType]: SUCCESS\n");
    }
    else {
        printf("[getType]: FAILURE\n");
        return -1;
    }

    //Testing to see if manager shutsdown correctly
    managerTest.~Manager();
    if (!managerTest.isStarted()) {
        printf("[shutDown]: SUCCESS\n");
    }
    else {
        printf("[shutDown]: FAILURE\n");
        return -1;
    }

    return 0;
}

//Test function for SFML library set up 
int testSFML() {

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}

//Test function for the log manager
void testLogManager() {

    LM.startUp();

   //__________________
   // Testing start up 
   //------------------

    //Testing initial start up
    if (LM.isStarted()) {
        printf("LogManager started succesfully\n");
    }
    else {
        printf("LogManager did not start successfully\n");
    }

    //____________________________________
    // Testing write up without log level 
    //------------------------------------

    //Testing if log sends for one
    LM.writeLog("HELLO WORLD\n");

    //Testing if log returns proper byte size
    if (LM.writeLog("HELLO WORLD\n") != sizeof("HELLO WORLD\n")) {
        LM.writeLog("Write log returning incorrect size, expected %d, received %d\n", sizeof("HELLO WORLD\n"), LM.writeLog("HELLO WORLD\n"));
    }


    //Loop for stress test and testing int argument input
    /*
    for (int i = 0; i < 10000; i++) {
        LM.writeLog("Test #%d\n",i);
    }
    */

    //Testing other argumentitive inputs
    LM.writeLog("%s %d or %f","Message\n", 2,2.0);



    //________________________________________
    // Testing verbosity and related functions
    //----------------------------------------

    //Testing get and set verbosity
    if (LM.getVerbosity() == 1) {
        LM.writeLog("Default Verbosity is correct at 1\n");
    }
    else {
        LM.writeLog("Default Verbosity is incorrectly set at %d\n",LM.getVerbosity());
    }
    
    LM.setVerbosity(4);

    if (LM.getVerbosity() == 4) {
        LM.writeLog("Set Verbosity works correctly\n");
        LM.setVerbosity(1);
    }
    else {
        LM.writeLog("Set Verbosity failed: Attempted to set to 4, received %d\n", LM.getVerbosity());
    }


    //___________________________________
    // Testing write ups with log levels 
    //-----------------------------------

    //Testing if log_level < LogManager log_level
    LM.writeLog(0, "This should not print\n");

    //Testing if log_level > LogManager log_level
    LM.writeLog(2, "This should print #1\n");

    //Testing if log_level = LogManager log_level
    LM.writeLog(1, "This should print #2\n");
}

//Test function for the clock class
void testClock() {

    //Start up log manager if needed
    LM.startUp();

    //Set timer resolution
    timeBeginPeriod(1);

    //Test clock 
    Clock c;

    //Start timer
    c.delta();

    //Test sleeping for 2 seconds
    Sleep(2000);

    //Get how long it slept
    long int slept = c.split()/1000;

    if (slept > 2000 && slept < 2500) {
        LM.writeLog(1, "Clock got an acurate sleep time\n");
        printf("%ld", slept);
    }
    else {
        LM.writeLog(3, "Clock did not get an acurate sleep time\n");
        printf("%ld",slept);
    }

    //Clear time resolution
    timeEndPeriod(1);

}

//Test functions for the game manager
void testGameManager() {


    GM.startUp();
    GM.run();
}

//Test vector functions 
void testVector() {

    //________________________________
    //TESTING CONSTRUCTION OF VECTORS
    //--------------------------------

    //Testing default vector construction
    Vector v1;
    if (v1.getX() == 0.0f && v1.getY() == 0.0f) {

        LM.writeLog(1, "Vector default construction succesful\n");
    }
    else {
        LM.writeLog(2, "Vector default construction failure\n");
    }

    Vector v2(2.0f, 3.0f);
    if (v2.getX() == 2.0f && v2.getY() == 3.0f) {

        LM.writeLog(1, "Vector non-default construction succesful\n");
    }
    else {
        LM.writeLog(3, "Vector non-default construction failure\n");
    }

    //__________________________________
    //TESTING SETTING VECTOR COMPONENTS
    //----------------------------------
    
    //Testing setX()
    v1.setX(1.0f);
    if (v1.getX() == 1.0f) {
        LM.writeLog(0, "Setting x of vector succesful\n");
    }
    else {
        LM.writeLog(3, "Setting x of vector failure\n");
    }
    
    //Testing setY()
    v1.setY(1.0f);
    if (v1.getY() == 1.0f) {
        LM.writeLog(0, "Setting y of vector succesful\n");
    }
    else {
        LM.writeLog(3, "Setting y of vector failure\n");
    }

    //Testing setXY
    v2.setXY(2.0f, 2.0f);
    if (v2.getX() == 2.0f && v2.getY() == 2.0f) {
        LM.writeLog(0, "Setting x and y of vector succesful\n");
    }
    else {
        LM.writeLog(3, "Setting x and y of vector failure\n");
    }


    //_________________________
    //TESTING VECTOR OPERATIONS
    //--------------------------

     //Testing + operater
    Vector v3 = v1 + v2;

    if (v3.getX() == 3.0f && v3.getY() == 3.0f) {
        LM.writeLog(0, "Vector addition succesful\n");
    }
    else {
        LM.writeLog(3, "Vector addition failure\n");
    }

    v3.setXY(2.0f,2.0f);

    //Testing getting magnitude
    if (v3.getMagnitude() == sqrt(8.0f)) {
        LM.writeLog(0, "Vector getMagnitude() succesful\n");
    }
    else {
        LM.writeLog(3, "Vector getMagnitude() failure\n");
    }
   
    //Testing scale
    v3.scale(2);
    if (v3.getX() == 4.0f && v3.getY() == 4.0f) {

        LM.writeLog(0, "Vector scaling succesful\n");
    }
    else {
        LM.writeLog(0, "Vector scaling failure\n");
    }

    //Testing normalize
    v3.normalize();
    float normalized = 4 / sqrt(32.);
    if (v3.getX() == normalized && v3.getY() == normalized) {
        LM.writeLog(0, "Vector normalizing succesful\n");
    }
    else {
        LM.writeLog(3, "Vector normalizing failure\n");
    }

}

//Test Object 
void testObject() {

    //________________________________________
    //TESTING DEFAULT CONSTRUCTION OF OBJECTS
    //----------------------------------------
    for (int i = 0; i < 5; i++) {
        Object o;
        //Testing id
        if (o.getId() != i) {
            LM.writeLog(3, "Default Object id not setting properly\n");
        }

        //Testing type
        if (o.getType() != "Object") {
            LM.writeLog(3, "Default Object type not setting properly\n");
        }

        //Testing position
        if (o.getPosition().getMagnitude() != 0) {
            LM.writeLog(3, "Default Object position not setting properly\n");
        }
    }

    //________________________________
    //TESTING SET FUNCTIONS OF OBJECT
    //--------------------------------
    Object t;

    //Testing setID
    t.setId(50);
    if (t.getId() != 50) {
        LM.writeLog(3, "Set id not properly working expeted: %d, received: %d\n",50,t.getId());
    }

    //Testing setType
    t.setType("Test");
    if(t.getType() != "Test") {
        LM.writeLog(3, "Set Type not properly working expeted: %s, received: %s\n", "Test", t.getType().c_str());
    }
  
    //Testing setPosition
    t.setPosition(Vector(1, 1));
    if (t.getPosition().getMagnitude() != 2) {
        LM.writeLog(3, "Set Position not properly working\n");
    }
}

//Test Object Lists
void testObjectList() {
    
    //Start up log manager if needed
    LM.startUp();

    ObjectList list;
    Object* trash;
    
    
    //Testing insert 
    for (int i = 0; i < 10; i++) {
        Object st;
        list.insert(&st);
    }
    
    if (list.getCount() != 10) {
        LM.writeLog(3, "Object list insert failure, expected %d, received %d\n",10,list.getCount());
    }

    //Testing remove
    Object o;
    list.insert(&o);
    list.remove(&o);

    if (list.getCount() != 10) {
        LM.writeLog(3, "Object list remove failure, expected %d, received %d\n", 10, list.getCount());
    }
    

    
    //Testing clear
    list.clear();
    if (list.getCount() != 0) {
        LM.writeLog(3, "Object list clear failure, expected %d, received %d\n", 0, list.getCount());
    }
    /*
    //Testing isEmpty
    if (!list.isEmpty()) {
        LM.writeLog(3, "Object list isEmpty failure");
    }
    */

    /*Disabled for debuging other things
    
    //Testing isFull
    for (int j = 0; j < 1999; j++) {
        Object sp;
        list.insert(&sp);
    }

    if (!list.isFull()) {
        LM.writeLog(3, "Object list isFull failure, current count: %d",list.getCount());
    }
    */
    
}

//Test Object List iterators
void testObjectListIterator() {

   
    //Start up log manager if needed
    LM.startUp();

    //Test list
    ObjectList li;

    //Fill list with 3 different objects
    Object o_1;
    Object o_2;
    Object o_3;
    o_1.setType("Red");
    o_2.setType("Yellow");
    o_3.setType("Green");
    li.insert(&o_1);
    li.insert(&o_2);
    li.insert(&o_3);

    //Give list to iterator
    ObjectListIterator iterator(&li);

    //Set it to the first object
    iterator.first();

    //Go through and print the id of every object
    while (!iterator.isDone()) {
        printf("Hello %s\n", iterator.currentObject()->getType().c_str());

        LM.writeLog(0, "CURRENT OBJECT: %s\n",iterator.currentObject()->getType());
        iterator.next();
    }
}



int main()
{
    //testSFML();
    /*
   if(testBaseManager() == 0){
       printf("ALL TESTS FOR BASE MANAGER PASSED\n");
   }
   else {
       printf("SOMETHING WENT WRONG WITH THE BASE MANAGER\n");
   }
   */
    //testGameManager();
    
    //testClock();

    //testLogManager();
    
    //testVector();

    testObject();
    testObjectList();
    testObjectListIterator();

}

