#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "Elementos.h"
#include <vector>
#include "MVC.h"
class ViewBomberman:virtual View{
public:
    sf::RenderWindow window;
    ViewBomberman(int,int);
    std::vector<BloqueBomberman*> BloqueVector;
    void refreshVector(std::vector<BloqueBomberman*>);
    void printBlocks(int);
    void printBombs(std::vector<BombBomberman*>,int);
    void printPlayer(PlayerBomberman);
    void show(std::vector<BloqueBomberman*>,int,PlayerBomberman,std::vector<BombBomberman*>,int,PlayerBomberman,std::vector<BombBomberman*>,int);
};


#endif // VIEW_H_INCLUDED
