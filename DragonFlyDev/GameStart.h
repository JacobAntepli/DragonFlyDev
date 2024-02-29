#pragma once
#include "ViewObject.h"
#include "EventKeyboard.h"
#include "Music.h"

class GameStart : public df::ViewObject {
private:
    void start(); //called when p pressed to play, populates world

public:
    GameStart();
    int eventHandler(const df::Event* p_e) override;
    int draw() override;
};