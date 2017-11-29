#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "MVC.h"
class ControllerBomberman:virtual Controller{
private:
        bool up, up2;
        bool down, down2;
        bool left, left2;
        bool right, right2;
        bool space, shift;

    public:
        sf::Event myEvent;
        ControllerBomberman();
        int detectEvents();
        void resetEvents();
        bool getUp();
        bool getDown();
        bool getLeft();
        bool getRight();
        bool getSpace();
        bool getUp2();
        bool getDown2();
        bool getLeft2();
        bool getRight2();
        bool getShift();
};



#endif // CONTROLLER_H_INCLUDED
