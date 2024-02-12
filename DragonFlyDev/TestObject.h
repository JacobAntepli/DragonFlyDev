#ifndef __TEST_OBJECT_H__
#define __TEST_OBJECT_H__

//Included resourses 
#include "Object.h"
#include "EventStep.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventCollision.h"

class TestObject : public df::Object {

private:

public:

	//Constructer
	TestObject();

	//Deconstructer
	~TestObject();

	//Handels events for saucer
	int eventHandler(const df::Event* p_e) override;

	//Draw something
	int draw();

	//Print pressed keys
	void printKey(const df::EventKeyboard* p_e);

	//Print pressed mouse buttons
	void printMSE(const df::EventMouse* p_e);

	//Print colliding objects 
	void printCollision(const df::EventCollision* p_e);



};//End of class






#endif
