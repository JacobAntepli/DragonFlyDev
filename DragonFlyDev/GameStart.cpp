#include "GameStart.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "Points.h"
#include "Player.h"
#include "Enemy.h"
#include "Rounds.h"
#include "Lives.h"
#include "EventDeath.h"

GameStart::GameStart()
{
    EventDeath ed;
    WM.onEvent(&ed);
    //Set type
    setType("GameStart");

    //position start menu in center of screen
    df::Vector temp_pos;
    float world_horiz = WM.getBoundary().getHorizontal();
    float world_vert = WM.getBoundary().getVertical();
    df::Vector p(world_horiz / 2, world_vert / 2);
    setPosition(p);

    //set sprite
    setSprite("start");

    //in front of all other sprites
    setAltitude(5);
}

void GameStart::start()
{
    //Create point view object
    new Points;

    //Create rounds view object
    new Rounds;

    //Create lives view object
    new Lives;


    Player* p = new Player;

    //new spawner
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);
    new Enemy((Object*)p);


    WM.removeObject(this);
}


int GameStart::eventHandler(const df::Event* p_e)
{

    if (p_e->getType() == df::KEYBOARD_EVENT) {
        EventDeath ed;
        WM.onEvent(&ed);

        df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*)p_e;
        switch (p_keyboard_event->getKey()) {
        case df::Keyboard::SPACE: //play if p pressed
            start();
            break;
        case df::Keyboard::ESCAPE: //quit if esc pressed
            if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
                GM.setGameOver(true);
            }
            break;
        default: //Key is not handled
            break;
        }
        return 1;
    }
    //ignored event
    return 0;
}

int GameStart::draw()
{
    return df::Object::draw();
}
