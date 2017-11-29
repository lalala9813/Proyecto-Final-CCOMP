#ifndef ELEMENTOS_H_INCLUDED
#define ELEMENTOS_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <vector>

class BloqueBomberman{
public:
    int posX, posY;
    bool destructible;

//public:
    sf::RectangleShape block;
    BloqueBomberman(int,int,bool);
    void drawBlock(bool);
    bool getDestructible();
    sf::RectangleShape returnBloque();

};


class ArenaBomberman{
public:
    char** Layout;
    std::vector<BloqueBomberman*> BloquesVector;
    std::string level;
    int numBloques;

    ArenaBomberman();
    void initializeLayout();
    void createMap();
    void fillVector();
    int getnumBloques();

};


class BombBomberman{
public:
    int posX,posY;
    sf::CircleShape bomba;
    bool used;
    bool explote;

    BombBomberman(int,int);
    ~BombBomberman();
    void drawBomb();
    sf::CircleShape returnBomba();
    void ExploteBomb(ArenaBomberman &);


};


class PlayerBomberman{
public:
    int posX, posY;
    sf::RectangleShape jugador;
    std::vector<BombBomberman*> bombas;
    int numBombas;
    sf::Texture textura;
    bool alive;


    PlayerBomberman(int,int);
    sf::RectangleShape returnPlayer();
    void drawPlayer();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void layBomb();


};




#endif // ELEMENTOS_H_INCLUDED
