#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <fstream>
class barraArcanoid;
class pelotaArcanoid;
class ModeloArcanoid;
class poderArcanoid{
public:
    int x,y;
    char tipo;
    poderArcanoid*siguiente;
    poderArcanoid(int myx,int myy,char mitipo);
    bool mover(int myx,int ancho,barraArcanoid&jugador,pelotaArcanoid&ball);
    void destruir();
};
class balaArcanoid{
public:
    int x,y;
    sf::RectangleShape forma;
    balaArcanoid *siguiente;
    balaArcanoid(int myx,int myy);
    bool mover(char**poderes,int ** bloques,int n,int m,int ancho, int alto,poderArcanoid*&power,barraArcanoid&);
    bool colision(char**poderes,int ** bloques,int n,int m,int ancho, int alto,poderArcanoid*&power,barraArcanoid&);
    void destruir();
};
class pelotaArcanoid{
public:
    int x,y,vx,vy,radio;
    pelotaArcanoid*siguiente;
    pelotaArcanoid(int myx,int myy,int myvx,int myvy,int myradio);
    bool cambiarDir(int ancho,int alto, int xbarra,int xancho);
    void mover();
    void duplicar();
    void colisionBloques2(int ** bloques,char**poderes,int n,int m,int ancho, int alto,poderArcanoid*&power,barraArcanoid&);
    void destruir();
};
class barraArcanoid{
public:
    int vidas;
    int puntos;
    int x;
    int ancho;
    int direccion;
    bool canon;
    barraArcanoid();
    barraArcanoid(int myx,int myancho);
    void derecha();
    void izquierda();
    void stop();
    void xs();
    void xl();
    void canhon();
    void disparo(balaArcanoid*&shot);
    void mover();
    bool reiniciar();
};
class BloquesArcanoid{
public:
    bool haybloques;
    int bloquesx,bloquesy;
    int** matriz;
    char** poderes;
    BloquesArcanoid();
    BloquesArcanoid(int,int);
    void crearNivel(int);
    ~BloquesArcanoid();
};

class ControlArcanoid{
    int teclaPres;
public:
    ControlArcanoid();
    int teclado();
};
class VistaArcanoid{
private:
    sf::RectangleShape power;
    sf::RectangleShape shot;
    sf::CircleShape ball;
    sf::RectangleShape bar;
    sf::RectangleShape bloques[10][8];
    void dibujarPoder(poderArcanoid *,sf::RenderWindow &);
    void dibujarDisparo(balaArcanoid *,sf::RenderWindow &);
    void dibujarPelota(pelotaArcanoid *,sf::RenderWindow &);
    void dibujarVidas(int,sf::RenderWindow &);
    void dibujarBarra(int ,int,sf::RenderWindow &);
    bool dibujarBloques(int**,sf::RenderWindow &);
public:
    VistaArcanoid();
    void show(ModeloArcanoid&,sf::RenderWindow &);
};
class ModeloArcanoid{
public:
    int alto,ancho,fps,nivel;
    poderArcanoid* power;
    BloquesArcanoid matriz=BloquesArcanoid();
    pelotaArcanoid *ball;
    barraArcanoid jugador=barraArcanoid();
    balaArcanoid *ataque;
    int disparo;
    ModeloArcanoid(int,int,int);
    bool run(int);
    void guardarpuntos();
    ~ModeloArcanoid();
};
void arcanoidrun();
/*class arcanoid{
public:
    arcanoid();
    run();
};*/


#endif // HEADER_H_INCLUDED
