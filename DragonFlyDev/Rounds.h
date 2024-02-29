#pragma once

//Included resources
#include "ViewObject.h"
#include "Event.h"

#define ROUNDS_STRING "Rounds"


class Rounds : public df::ViewObject {
public:
    //Construcer for rounds 
    Rounds();

    //Handles incrimenting or decrimenting rounds
    int eventHandler(const df::Event* p_e) override;
};