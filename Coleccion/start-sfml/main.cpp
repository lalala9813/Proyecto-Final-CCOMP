#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include "header.h"
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include "juego.h"
#include <time.h>
#include "Controller.h"
#include "Elementos.h"
#include "View.h"
#include "Model.h"
#include "Game.h"
using namespace std;
int main(){
    while(true){
        std::cout<<"Elige el juego que deseas jugar (1)Arkanoid (2)Naves (3)Bomberman";
        char a;
        std::cin.getline(&a,2);
        system("cls");
        if(a=='1'){
            arcanoidrun();
        }
        else if(a =='2'){
            VistaNaves v;
            ModeloNaves m;
            ControlerNaves c;
            v.show();
            m.run();
            c.mov();
        }
        else if(a =='3'){
            GameBomberman myGame;
            myGame.runGame();
        }
    }
    return 0;
}
