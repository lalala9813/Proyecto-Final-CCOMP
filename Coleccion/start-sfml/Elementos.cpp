#include "Elementos.h"
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

//Funciones De la Clase Bloque
BloqueBomberman::BloqueBomberman(int x, int y, bool destructible):
    posX(x),
    posY(y),
    destructible(destructible)
    {};


void BloqueBomberman::drawBlock(bool destructible){
    block.setSize(sf::Vector2f(50,50));
    block.setOutlineThickness(1);
    block.setOutlineColor(sf::Color::Black);
    if(destructible){
        block.setFillColor(sf::Color(150,22,11));
        block.setPosition(posX,posY);

    }
    else{
        block.setFillColor(sf::Color(143,143,143));
        block.setPosition(posX,posY);

    }

}

bool BloqueBomberman::getDestructible(){
    return destructible;
}

sf::RectangleShape BloqueBomberman::returnBloque(){
    return block;
}

//Funciones de la clase Arena

ArenaBomberman::ArenaBomberman():
    Layout(NULL),
    numBloques(0)
{};


void ArenaBomberman::initializeLayout(){
    Layout = new char*[13];

    for(int i=0;i<13;i++){
        Layout[i] = new char[15];
    }
}

void ArenaBomberman::createMap(){
    std::string line;
    std::ifstream infile("map.txt");


    while(!infile.eof()){
        std::getline(infile,line);
        if(line=="end"){
            infile.close();
            break;
        }
        level+=line;

    }

    int b=0;
    for(int i=0;i<13;i++){
        for(int j=0;j<15;j++){
            Layout[i][j]=level[b];
            b++;
        }

    }

}



void ArenaBomberman::fillVector(){

    for(int i=0;i<13;i++){
        for(int j=0;j<15;j++){
            if(Layout[i][j] == '1'){
                BloquesVector.push_back(new BloqueBomberman(j*50,i*50,false));
                numBloques++;

            }
            else if(Layout[i][j] == '2'){
                BloquesVector.push_back(new BloqueBomberman(j*50,i*50,true));
                numBloques++;

            }
        }
    }

}

int ArenaBomberman::getnumBloques(){
    return numBloques;
}

//Funciones de la Clase Bomb
BombBomberman::BombBomberman(int x, int y):
    posX(x),
    posY(y),
    used(false),
    explote(false)

{};

BombBomberman::~BombBomberman(){
    delete this;
}

void BombBomberman::drawBomb(){
    bomba.setRadius(25);
    bomba.setFillColor(sf::Color::Black);
    bomba.setPosition((posX*50),(posY*50));
}

sf::CircleShape BombBomberman::returnBomba(){
    return bomba;
}

void BombBomberman::ExploteBomb(ArenaBomberman &myArena){

    for(int i=-2;i<3;i++){
        if(posX+i>=0&&posX+i<15){
            if(myArena.Layout[posY][posX+i]=='2'){
                myArena.Layout[posY][posX+i]='0';
                for(int j=0;j<myArena.BloquesVector.size();j++){
                    if((posX+i)*50==myArena.BloquesVector[j]->posX&&posY*50==myArena.BloquesVector[j]->posY&&myArena.BloquesVector[j]->destructible){
                        myArena.BloquesVector.erase (myArena.BloquesVector.begin()+j);
                    }

                }
            }
        }
        if(posY+i>=0&&posY+i<13){
            if(myArena.Layout[posY+i][posX]=='2'){
                myArena.Layout[posY+i][posX]='0';
                for(int j=0;j<myArena.BloquesVector.size();j++){
                    if(posX*50==myArena.BloquesVector[j]->posX&&(posY+i)*50==myArena.BloquesVector[j]->posY){//&&myArena.BloquesVector[j]->destructible){
                        myArena.BloquesVector.erase (myArena.BloquesVector.begin()+j);
                    }
                }
            }
        }
    }

}

//Funciones de la Clase Player

PlayerBomberman::PlayerBomberman(int x, int y):
    posX(x),
    posY(y),
    numBombas(0),
    alive(true)
    {};

void PlayerBomberman::drawPlayer(){
    jugador.setSize(sf::Vector2f(50,50));
    textura.loadFromFile("player.png");
    jugador.setTexture(&textura);
    jugador.setPosition(posY*50,posX*50);
}

sf::RectangleShape PlayerBomberman::returnPlayer(){
    return jugador;
}

void PlayerBomberman::moveUp(){
    if((posX-1)>=0)
        posX-=1;
}

void PlayerBomberman::moveDown(){
    if(posX+1<=13)
        posX+=1;
}

void PlayerBomberman::moveLeft(){
    if(posY-1>=0)
        posY-=1;
}

void PlayerBomberman::moveRight(){
    if(posY<=15)
        posY+=1;
}

void PlayerBomberman::layBomb(){
    bombas.push_back(new BombBomberman(posY,posX));
    numBombas++;
}


