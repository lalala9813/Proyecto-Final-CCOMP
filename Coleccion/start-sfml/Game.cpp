#include "Game.h"


GameBomberman::GameBomberman():
    myView(750,650)
{};


void GameBomberman::runGame(){
    myModel.initializeModel();

    while(myView.window.isOpen()){

        while(myView.window.pollEvent(myController.myEvent)){
            myController.detectEvents();
            myModel.movePlayer(myController.getUp(),
                                        myController.getDown(),
                                        myController.getLeft(),
                                        myController.getRight(),
                                        myController.getSpace());
            myModel.movePlayer2(myController.getUp2(),
                                myController.getDown2(),
                                myController.getLeft2(),
                                myController.getRight2(),
                                myController.getShift());

            myController.resetEvents();
            if (myController.myEvent.type == sf::Event::Closed)
                myView.window.close();
        }
        myView.show(myModel.myArena.BloquesVector,
                                myModel.myArena.getnumBloques(),
                               myModel.myPlayer,
                               myModel.myPlayer.bombas, myModel.myPlayer.numBombas,
                               myModel.myPlayer2,
                               myModel.myPlayer2.bombas,myModel.myPlayer2.numBombas);
    }
}
