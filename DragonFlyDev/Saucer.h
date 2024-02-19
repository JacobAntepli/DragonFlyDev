#ifndef __SAUCER_H__
#define __SAUCER_H__

//Included resourses 
#include "Object.h"
#include "EventStep.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventCollision.h"

class Saucer : public df::Object {

private:

public:
	
	//Default constructer
	Saucer();

	//Specified constructer
	Saucer(df::Vector spawn_pos, df::Vector velocity);

	//Deconstructer
	~Saucer();

	//Handels events for saucer
	int eventHandler(const df::Event* p_e) override;

	//Print pressed keys
	void printKey(const df::EventKeyboard* p_e);

	//Print pressed mouse buttons
	void printMSE(const df::EventMouse* p_e);

	//Print colliding objects 
	void printCollision(const df::EventCollision* p_e);

};//End of class
#endif // !__SAUCER_H__

