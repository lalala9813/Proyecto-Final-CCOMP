#include "Model.h"
#include "Elementos.h"
#include <iostream>


ModelBomberman::ModelBomberman():
    myPlayer(5,6),
    myPlayer2(5,7),
    pasos1(0),
    pasos2(0)
    {};

void ModelBomberman::initializeModel(){
    myArena.initializeLayout();
    myArena.createMap();
    myArena.fillVector();
}

void ModelBomberman::movePlayer(bool up,bool down,bool left,bool right, bool space){
    if(up && myArena.Layout[myPlayer.posX-1][myPlayer.posY] == '0'){
        myPlayer.moveUp();
        exploteBomb();
    }
    if(down && myArena.Layout[myPlayer.posX+1][myPlayer.posY] == '0'){
        myPlayer.moveDown();
        exploteBomb();
    }
    if(left && myArena.Layout[myPlayer.posX][myPlayer.posY-1] == '0'){
        myPlayer.moveLeft();
        exploteBomb();
    }
    if(right && myArena.Layout[myPlayer.posX][myPlayer.posY+1] == '0'){
        myPlayer.moveRight();
        exploteBomb();
    }
    if(space){
        myPlayer.layBomb();
        pasos1=4;
    }

}

void ModelBomberman::movePlayer2(bool up,bool down,bool left,bool right, bool space){
    if(up && myArena.Layout[myPlayer2.posX-1][myPlayer2.posY] == '0'){
        myPlayer2.moveUp();
        exploteBomb2();
    }
    if(down && myArena.Layout[myPlayer2.posX+1][myPlayer2.posY] == '0'){
        myPlayer2.moveDown();
        exploteBomb2();
    }
    if(left && myArena.Layout[myPlayer2.posX][myPlayer2.posY-1] == '0'){
        myPlayer2.moveLeft();
        exploteBomb2();
    }
    if(right && myArena.Layout[myPlayer2.posX][myPlayer2.posY+1] == '0'){
        myPlayer2.moveRight();
        exploteBomb2();
    }
    if(space){
        myPlayer2.layBomb();
        pasos2=4;
    }
}

void ModelBomberman::exploteBomb(){
    if (pasos1>0){
        pasos1--;
    }else if(pasos1==0&&myPlayer.bombas.size()>0){
        myPlayer.bombas[0]->ExploteBomb(myArena);


        myPlayer.bombas.pop_back();

        myPlayer.numBombas--;
    }
}
void ModelBomberman::exploteBomb2(){
    if (pasos2>0){
        pasos2--;
    }else if(pasos2==0&&myPlayer2.bombas.size()>0){
        myPlayer2.bombas[0]->ExploteBomb(myArena);


        myPlayer2.bombas.pop_back();

        myPlayer2.numBombas--;
    }
}
