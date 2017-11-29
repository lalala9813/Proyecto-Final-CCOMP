#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "Model.h"
#include "Controller.h"
#include "View.h"

class GameBomberman{
    ViewBomberman myView;
    ControllerBomberman myController;
    ModelBomberman myModel;


public:
    GameBomberman();
    void runGame();

};



#endif // GAME_H_INCLUDED
