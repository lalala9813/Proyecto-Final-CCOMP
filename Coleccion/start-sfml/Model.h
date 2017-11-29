#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED
#include "Elementos.h"
#include "MVC.h"
class ModelBomberman:virtual Model{
public:
    ArenaBomberman myArena;
    PlayerBomberman myPlayer;
    PlayerBomberman myPlayer2;

    int pasos1;
    int pasos2;

    ModelBomberman();

    void initializeModel();
    void movePlayer(bool,bool,bool,bool,bool);
    void movePlayer2(bool,bool,bool,bool,bool);
    void exploteBomb();
    void exploteBomb2();


};


#endif // MODEL_H_INCLUDED
