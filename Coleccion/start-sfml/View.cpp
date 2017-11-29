#include "View.h"
#include <vector>



ViewBomberman::ViewBomberman(int width, int height):
    window(sf::VideoMode(width, height), "Bomberman :v")
{};

void ViewBomberman::refreshVector(std::vector<BloqueBomberman*> actual){
    BloqueVector = actual;
}

void ViewBomberman::printBlocks(int numBloques){
    for(int i=0;i<numBloques;i++){
        BloqueVector[i]->drawBlock(BloqueVector[i]->getDestructible());
        window.draw(BloqueVector[i]->returnBloque());
    }


}

void ViewBomberman::printBombs(std::vector<BombBomberman*> bombVector,int numBombs){
    for(int i=0;i<numBombs;i++){
        bombVector[i]->drawBomb();
        window.draw(bombVector[i]->returnBomba());
    }
}

void ViewBomberman::printPlayer(PlayerBomberman jugador){
    jugador.drawPlayer();
    window.draw(jugador.returnPlayer());
}

void ViewBomberman::show(std::vector<BloqueBomberman*> BloquesVector, int numBloques,
                            PlayerBomberman myPlayer,
                            std::vector<BombBomberman*> bombVector,int numBombs,
                            PlayerBomberman myPlayer2,
                            std::vector<BombBomberman*> bombVector2,int numBombs2){
    window.clear(sf::Color::White);
    refreshVector(BloquesVector);
    printBlocks(numBloques);
    printBombs(bombVector,numBombs);
    printBombs(bombVector2,numBombs2);
    printPlayer(myPlayer);
    printPlayer(myPlayer2);
    window.display();
}
