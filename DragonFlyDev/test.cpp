

//Included system resources
#include <SFML/Graphics.hpp> 
#include <Windows.h>
#include <math.h>

//Included managers
#include "Manager.h"
#include "LogManager.h"
#include "GameManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "InputManager.h"

//Event includes
#include "Event.h"
#include "EventStep.h"

//Object included resources
#include "Object.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"

//Other included resources
#include "Clock.h"
#include "Vector.h"
#include "Saucer.h"

using namespace std;
using namespace df;


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
    //Set timer resolution
    timeBeginPeriod(1);

    //Test clock 
    Clock c;

    //Start timer
    c.delta();

    //Test sleeping for 2 seconds
    //Sleep(2000);

    //Get how long it slept
    long int slept = (c.split()/1000);

    if (slept >= 2000 && slept <= 3000) {
        LM.writeLog(1, "Clock got an acurate sleep time\n");
        printf("Sleep Time: %ld\n", slept);
    }
    else {
        LM.writeLog(3, "Clock did not get an acurate sleep time, RECEIVED %ld\n",slept);
        printf("%ld\n",slept);
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
    float normalized = 4.0f / sqrt(32.0f);
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
    /*
    //Testing setID
    t.setId(50);
    if (t.getId() != 50) {
        LM.writeLog(3, "Set id not properly working expeted: %d, received: %d\n",50,t.getId());
    }
    */
    

    //Testing setType
    t.setType("Test");
    if(t.getType() != "Test") {
        LM.writeLog(3, "Set Type not properly working expeted: %s, received: %s\n", "Test", t.getType().c_str());
    }
  
    //Testing setPosition
    t.setPosition(Vector(1, 1));
    if (t.getPosition().getMagnitude() != sqrt(2.0f)) {
        LM.writeLog(3, "Set Position not properly working\n");
    }
}

//Test Object Lists
void testObjectList() {

    ObjectList list;
    
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
    
    //Testing isEmpty
    if (!list.isEmpty()) {
        LM.writeLog(3, "Object list isEmpty failure");
    }
    

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

    while (!iterator.isDone()) {
        printf("%s\n", iterator.currentObject()->getType().c_str());
        iterator.next();
     }

}

void testBaseEvent() {

    Event test; 

    //Testing default event name
    if (test.getType() != "df::undefined") {
        LM.writeLog(10, "DEFAULT EVENT TYPE INCORRECT, EXPECTED df::undefined, RECEIVED %s\n", test.getType());
    }

    //Testing setting event type
    test.setType("Test");
    if (test.getType() != "Test") {
        LM.writeLog(10, "DEFAULT EVENT TYPE INCORRECT, EXPECTED TEST RECEIVED % s\n", test.getType());
    }
}

void testStepEvent() {

    //Start up if needed
    EventStep step;

    //Test Type definition
    if (step.getType() != STEP_EVENT) {
        LM.writeLog(10, "DEFAULT STEP EVENT TYPE INCORRECT, EXPECTED df::step, RECEIVED %s\n", step.getType());
    }

    //Test default step count
    if (step.getStepCount() != 0) {
        LM.writeLog(10, "DEFAULT STEP COUNT INCORRECT, EXPECTED 0, RECEIVED %s\n", step.getStepCount());
    }

    //Test set step count
    step.setStepCount(3);
    if (step.getStepCount() != 3) {
        LM.writeLog(10, "DEFAULT STEP COUNT INCORRECT, EXPECTED 3, RECEIVED %s\n", step.getStepCount());
    }
}

//Testing world manager
void testWorldManager() {

    //Testing start up 
    WM.startUp();

    if (!WM.isStarted()) {
        LM.writeLog(10, "WORLD MANAGER DIDN'T STARTUP CORRECTLY\n");
    }

    //Testing adding in objects
    Object *type1 = new Object();//Objects auto insert
    Object *type2 = new Object();//Objects auto insert
    type2->setType("Type2");

    if (WM.getAllObjects().getCount() != 2) {
        LM.writeLog(10, "ADDING OBJECTS TO WORLD FAILED EXPECTED: 2, RECEIVED: %d\n", WM.getAllObjects().getCount());
    }

    //Testing getting objects of a certain type
    ObjectList filtered = WM.getObjectOfType("Type2");
    if (!filtered.contains(type2)) {
        LM.writeLog(10, "FAILED TO GET A PARTICULAR TYPE OF OBJECT FROM WORLD\n");
    }

    //Testing marking for deletion, updating, and removing objects
    WM.markForDelete(type1);
    WM.update();
    if (WM.getAllObjects().getCount() != 1) {
        LM.writeLog(10, "FAILED TO DELETE OBJECT FROM WORLD MANAGER\n");
    }

    //Testing shutdown
    WM.shutDown();
}

//Tests event handler and game loop
void testEventHandler() {

    //Start up gamemanager
    GM.startUp();

    //Make new object to send event to 
    new Saucer;

    //Run
    GM.run();
}

//Tests fonts and text in SFML
void testSFMLText() {
    //Load Font
    sf::Font font;
    if (font.loadFromFile("Fonts/df-AnonymousPro.ttf") == false) {
        LM.writeLog(10, "COULD NOT LOAD FONT PROPERLY");
        return;
    }

    //Test text display
    sf::Text text;
    text.setFont(font);
    text.setString(" Hello, world!");
    text.setCharacterSize(32);
    text.setFillColor(sf::Color::Green);
    text.setStyle(sf::Text::Bold);
    text.setPosition(96, 134);

    //Create window
    sf::RenderWindow window(sf::VideoMode(400, 300), "SFML - Hello , world !");
 
    if (!window.isOpen()) {
        LM.writeLog(10, "COULD RENDER WINDOW PROPERLY");
        return;
    }

    //Turn off mouse cursor for window
    window.setMouseCursorVisible(false);

    //Sync refresh rate
    window.setVerticalSyncEnabled(true);

    //Repeat until window is closed 
    while (1) {
        //Draw and cleaar
        window.clear();
        window.draw(text);
        window.display();

        //See if window has been closed
        sf::Event e;
        while(window.pollEvent(e)){
            if (e.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
}

//Tests display manager functions
void testDisplayManager() {

    //Testing drawing character, start up, and shutdown
    if (DM.startUp() != 0) {
        LM.writeLog(10, "DISPLAY START UP TEST FAILURE\n");
    }
    
    
    DM.drawCh(Vector(10, 5), '*', WHITE);
    DM.setBackgroundColor(BLUE);
    DM.swapBuffers();
    
    Sleep(2000);
    //Test to see if background changes
    DM.swapBuffers();
    Sleep(2000);

    //Testing writing strings and their justifications
    DM.drawString(Vector(50, 5), "HELLO WORLD\n", LEFT_JUSTIFIED, WHITE);
    DM.swapBuffers();
    Sleep(2000);

    DM.drawString(Vector(50, 5), "HELLO WORLD\n", RIGHT_JUSTIFIED, WHITE);
    DM.swapBuffers();
    Sleep(2000);

    DM.drawString(Vector(50, 5), "HELLO WORLD\n", CENTER_JUSTIFIED, WHITE);
    DM.swapBuffers();
    Sleep(2000);

    

    //Testing Object draw function
    WM.startUp();
    Saucer *bottom  = new Saucer;
    bottom->setType("LONG STRINNGGGGG");
    bottom->setAltitude(0);
    bottom->setPosition(Vector(50, 5));
    WM.draw();
    DM.swapBuffers();
    Sleep(2000);

    //Testing altitude by putting object on top of previous object
    Saucer* top = new Saucer;
    top->setType("SHORT STRING");
    top->setPosition(Vector(50, 5));
    top->setAltitude(2);
    WM.draw();
    DM.swapBuffers();
    Sleep(2000);


    DM.shutDown();
    WM.shutDown();
}

//Test input manager by making mini game loop 
void testInputManager() {

    DM.startUp();
    IM.startUp();

    new Saucer();

    bool done = false;
    //Test saucers are told to print key, if escape is pressed finish
    while (!done) {
        IM.getInput();
    }
}


int main()
{

    //Start Logmanager for required tests
    LM.startUp();


    //testGameManager(); //GAME MANAGER SHOULD BE TESTED SEPERATLY
    //testEventHandler(); //EVENT HANDELER TEST SHOULD BE DONE SEPERATLY   
    //testDisplayManager(); //DISPLAY MANAGER TESTING SHOULD BE DONE SEPERATLY 
    testInputManager(); //INPUT MANAGER TESTING SHOULD BE DONE SEPRATLY
    //testSFML();

      /*
     if(testBaseManager() == 0){
       printf("ALL TESTS FOR BASE MANAGER PASSED\n");
      }
      else {
       printf("SOMETHING WENT WRONG WITH THE BASE MANAGER\n");
     }
     */
    /*
     testClock();
     testLogManager();
     testVector();
     testObject();
     testObjectList();
     testObjectListIterator();
     testBaseEvent();
     testStepEvent();
     testWorldManager();
     */

    //testSFMLText();
    
   

     


     //Shutdown logmanager if needed
     if (LM.isStarted()) {
         LM.shutDown();
     }
}

