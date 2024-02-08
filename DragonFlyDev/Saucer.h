#ifndef __SAUCER_H__
#define __SAUCER_H__

//Included resourses 
#include "Object.h"
#include "EventStep.h"
#include "EventKeyboard.h"
#include "EventMouse.h"

class Saucer : public df::Object {

private:

public:
	
	//Constructer
	Saucer();

	//Deconstructer
	~Saucer();

	//Handels events for saucer
	int eventHandler(const df::Event* p_e) override;

	//Draw something
	int draw();

	//Print pressed keys
	void printKey(const df::EventKeyboard* p_e);

	//Print pressed mouse buttons
	void printMSE(const df::EventMouse* p_e);



};//End of class
#endif // !__SAUCER_H__

