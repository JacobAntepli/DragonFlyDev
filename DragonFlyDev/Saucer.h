#ifndef __SAUCER_H__
#define __SAUCER_H__

//Included resourses 
#include "Object.h"

class Saucer : public df::Object {

private:

public:
	
	//Constructer
	Saucer();

	//Deconstructer
	~Saucer();

	//Handels events for saucer
	int eventHandler(const df::Event* p_e) override;



};//End of class
#endif // !__SAUCER_H__

