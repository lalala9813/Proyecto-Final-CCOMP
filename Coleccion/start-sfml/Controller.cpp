#include "Controller.h"
#include <iostream>


ControllerBomberman::ControllerBomberman():
    up(false),
    up2(false),
    down(false),
    down2(false),
    left(false),
    left2(false),
    right(false),
    right2(false),
    space(false),
    shift(false)
    {};

int ControllerBomberman::detectEvents(){
    //Controles Jugador1;
    if(myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::W){
        up = true;

    }

    if(myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::S){
        down = true;

    }

    if(myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::A){
        left = true;

    }

    if(myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::D){
        right = true;

    }

    if(myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Space){
        space = true;
    }

    if(myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Up){
        up2 = true;
    }

    if(myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Down){
        down2 = true;
    }

    if(myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Left){
        left2 = true;
    }

    if(myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::Right){
        right2 = true;
    }

    if(myEvent.type == sf::Event::KeyPressed && myEvent.key.code == sf::Keyboard::RShift){
        shift = true;
    }
    return 0;
}

void ControllerBomberman::resetEvents(){
    up = false;
    down = false;
    left = false;
    right = false;
    space = false;
    up2 = false;
    down2 = false;
    left2 = false;
    right2 = false;
    shift = false;
}

bool ControllerBomberman::getUp(){
    return up;
}

bool ControllerBomberman::getDown(){
    return down;
}

bool ControllerBomberman::getLeft(){
    return left;
}

bool ControllerBomberman::getRight(){
    return right;
}

bool ControllerBomberman::getSpace(){
    return space;
}

bool ControllerBomberman::getUp2(){
    return up2;
}

bool ControllerBomberman::getDown2(){
    return down2;
}

bool ControllerBomberman::getLeft2(){
    return left2;
}

bool ControllerBomberman::getRight2(){
    return right2;
}

bool ControllerBomberman::getShift(){
    return shift;
}
