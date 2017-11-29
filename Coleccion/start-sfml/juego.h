#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include "MVC.h"
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

class VistaNaves:virtual View
{
    public:
        VistaNaves();
        ~VistaNaves();
        void gotoxy(int x, int y);
        void OcultarCursor();
        void color(int X);
        void bordes();
        void show();
};
//*********************************************************************************************************************************************************
class ModeloNaves:virtual Model
{
    public:
    ModeloNaves();
    ~ModeloNaves();
    class Nave
    {
        private:
            int x,y;
            int corazones;
            int vidas;
            VistaNaves v1;
        public:
            Nave(int _x, int _y, int _corazones, int _vidas); //CONSTRUCTOR
            ~Nave();//Destructor
            //Controller c1;
            int X();/*Metodos para acceder a la coordenada X*/
            int Y();/*Metodos para acceder a la coordenada Y*/
            int VID();
            void COR();/*Funcion que hace que corazones disminuya */
            void dibujar();
            void borrar();
            void volar();
            void pintarcorazones();
            void morir();
    };
//*********************************************************************************************************************************************************
    class Ast
    {
        private:
            int x,y;
            VistaNaves v2;
        public:
            Ast(int _x, int _y);
            ~Ast();
            void pintar();
            void mover();
            /*Detecta la coordenada de cada uno de los asterorides con la nave de acuerdo a la posicion*/
            void choque(class Nave &nave);/*Se pasa por referencia porque se van a estar modificando los valores*/
            /* Le pasamos un objeto para acceder a sus metodos*/
    };
    void run();
};
//*********************************************************************************************************************************************************
class ControlerNaves:virtual Controller
{
public:
    ControlerNaves();
    ~ControlerNaves();
    void mov();
    int detectEvents(int where);
};

#endif // JUEGO_H_INCLUDED
