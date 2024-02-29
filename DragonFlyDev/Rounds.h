#pragma once

//Included resources
#include "ViewObject.h"
#include "Event.h"

#define ROUNDS_STRING "Rounds"

//10 points are earned everytime the alphabet is complete
//1 point is earned when you get a letter
//1 point is lossed when you lose a letter (per letter)
class Rounds : public df::ViewObject {

public:
    //Construcer for points 
    Rounds();

    //Handles incrimenting or decrimenting points
    int eventHandler(const df::Event* p_e) override;
};