#include "juego.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

using namespace std;
//*********************************************************************************************************************************************************
VistaNaves::VistaNaves(){}

void VistaNaves::gotoxy(int x, int y)
{
    HANDLE hCon;  //Creando un identificador
    hCon = GetStdHandle(STD_OUTPUT_HANDLE); //Recuperar el identificador de la consola
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);
}

void VistaNaves::OcultarCursor()
{
    HANDLE hCon;  //Creando un identificador
    hCon = GetStdHandle(STD_OUTPUT_HANDLE); //Recuperar el identificador de la consola
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;

    SetConsoleCursorInfo(hCon, &cci);
}

void VistaNaves::color(int X)
{
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),X);
}

void VistaNaves::bordes()
{
    for(int i = 2; i<79 ; i++)
    {
        gotoxy(i,3); cout << (char)178;
        gotoxy(i,34); cout << (char)178;
    }

    for(int i = 4; i<34 ; i++)
    {
        gotoxy(2,i); cout << (char)186;
        gotoxy(78,i); cout << (char)186;
    }

    gotoxy(2,3); cout << (char)201;
    gotoxy(2,34); cout << (char)200;
    gotoxy(78,3); cout << (char)187;
    gotoxy(78,34); cout << (char)188;
}

void VistaNaves::show()
{
    VistaNaves v;
    v.OcultarCursor();
    v.color(10);
    v.bordes();
}

VistaNaves::~VistaNaves(){
}
//*********************************************************************************************************************************************************
ControlerNaves::ControlerNaves(){}
int ControlerNaves::detectEvents(int where)
{
        char tecla;
        if(where == 0)
        {
            tecla == IZQUIERDA;
        }
        if(where == 1)
        {
            tecla == DERECHA;
        }
        if(where == 2)
        {
            tecla == ARRIBA;
        }
        if(where == 3)
        {
            tecla == ABAJO;
        }
}

void ControlerNaves::mov()
{
      ControlerNaves c1;
      c1.detectEvents(0);
      c1.detectEvents(1);
      c1.detectEvents(2);
      c1.detectEvents(3);

}

ControlerNaves::~ControlerNaves(){}
//*********************************************************************************************************************************************************
ModeloNaves::ModeloNaves(){};

ModeloNaves::Nave::Nave(int _x, int _y, int _corazones, int _vidas)
{
        x = _x;
        y = _y;
        corazones = _corazones;
        vidas = _vidas;
}

int ModeloNaves::Nave::X()
{
    return x;
}/*Metodos para acceder a la coordenada X*/

int ModeloNaves::Nave::Y()
{
    return y;
}

int ModeloNaves::Nave::VID()
{
    return vidas;
}

void ModeloNaves::Nave::COR()
{
    corazones--;
}

void ModeloNaves::Nave::dibujar()
{

    v1.color(13);
    v1.gotoxy(x,y);   cout << "  " << (char)30 << "  ";
    v1.gotoxy(x,y+1); cout << " " << (char)4 << (char)169 << (char)4 <<" ";
    v1.gotoxy(x,y+2); cout << (char)17 << (char)201 << " " << (char)187 << (char)16;
}

void ModeloNaves::Nave::borrar()
{
    v1.gotoxy(x,y);   cout << "     ";
    v1.gotoxy(x,y+1); cout << "     ";
    v1.gotoxy(x,y+2); cout << "     ";
}

void ModeloNaves::Nave::volar()
{
     if (_kbhit())//Revisa si una tecla pulsada está disponible
     {
        int velocidad = 3;
        char tecla = getch();
        ControlerNaves c;
        borrar();
        if(tecla == IZQUIERDA && c.detectEvents(0) && x > 4) x-= velocidad;
        if(tecla == DERECHA  && c.detectEvents(1) && x+5 < 76) x += velocidad;
        if(tecla == ARRIBA && c.detectEvents(2) && y > 6) y -= velocidad;
        if(tecla == ABAJO && c.detectEvents(3) && y+3 < 32) y += velocidad;
        pintarcorazones();

     }

    dibujar();
}

void ModeloNaves::Nave::pintarcorazones()
{
    v1.color(14);
    v1.gotoxy(50,2); cout << "VIDAS -> " << vidas;
    v1.gotoxy(64,2); cout << "SALUD";
    v1.gotoxy(70,2); cout << "      ";
    for(int i = 0; i<corazones; i++)
    {

        v1.color(12);
        v1.gotoxy(70+i,2); cout << (char)3;
    }
}


void ModeloNaves::Nave::morir()
{
    if(corazones == 0)
    {
        v1.color(12);
        borrar();
        v1.gotoxy(x,y);   cout << "  **  ";
        v1.gotoxy(x,y+1); cout << " **** ";
        v1.gotoxy(x,y+2); cout << "  **  ";
        Sleep(300);

        v1.color(14);
        borrar();
        v1.gotoxy(x,y);   cout << "  **  ";
        v1.gotoxy(x,y+1); cout << " **** ";
        v1.gotoxy(x,y+2); cout << "  **  ";
        Sleep(200);

        borrar();
        ModeloNaves::Nave::vidas--;
        corazones = 3;
        pintarcorazones();
        dibujar();
    }

}

void ModeloNaves::run()
{
        /*sf::Music music;
        if (!music.openFromFile("msc.ogg"))
        return -1;
        music.play();*/
        VistaNaves v;
        ModeloNaves::Nave n(37,30,3,3);
        n.dibujar();
        n.pintarcorazones();
        int puntos = 0;
        string nombre;

        ModeloNaves::Ast a(10,4), a2(20,8), a3(50,6), a4(70,5), a5(30,5);

        bool finJuego = false;
        while(!finJuego)
        {
            v.color(14);
            v.gotoxy(3,2);
            puntos += 1;
            cout << "PUNTAJE --> " << puntos;

            a.mover();
            a.choque(n);
            a2.mover();
            a2.choque(n);
            a3.mover();
            a3.choque(n);
            a4.mover();
            a4.choque(n);
            a5.mover();
            a5.choque(n);


            if(n.VID() == 0)
            {
                finJuego = true;
                puntos +=0;
                system("cls");
                //music.pause();
                cout <<  "\n\n" <<"Tu nombre --> ";
                cin >> nombre;
                //Crenado archivo para guardar puntajes
                ofstream puntajes;
                puntajes.open("puntajes.txt",ios::app);//Abriendo el archivo
                puntajes << "\n" <<nombre << " -------> " << puntos;
                puntajes.close();//Cerrando el archivo
            }

            n.morir();
            n.volar();
            Sleep(30);
        }
        system("cls");
        system("color 0A");
        v.gotoxy(32,2);
        cout << nombre << " " << puntos << "\n\n";

        v.gotoxy(20,4);
        cout << "PERDISTE HERMANO SUERTE A LA PROXIMA \n";
        v.gotoxy(20,5);
        cout << "PERDISTE HERMANO SUERTE A LA PROXIMA \n";
        v.gotoxy(20,6);
        cout << "PERDISTE HERMANO SUERTE A LA PROXIMA \n";
        v.gotoxy(20,7);
        cout << "PERDISTE HERMANO SUERTE A LA PROXIMA \n";
        v.gotoxy(20,8);
        cout << "PERDISTE HERMANO SUERTE A LA PROXIMA \n";
}



ModeloNaves::Ast::Ast(int _x, int _y)
{
    x = _x;
    y = _y;
}

void ModeloNaves::Ast::pintar()
{
    v2.color(11);
    v2.gotoxy(x,y); cout << (char)201 << (char)2 << (char)187 ;
}

void ModeloNaves::Ast::mover()
{
    v2.gotoxy(x,y); cout << "   ";
    int velocidad = 2;
    y+= velocidad;
    if(y > 32)
    {
        x = rand()%71 + 4;//numero entre 0 + 4 y 71 + 4
        y = 4;
    }
    pintar();
}

void ModeloNaves::Ast::choque(class Nave &nave)
{
    if(x >= nave.X()/*mas a la izquierda*/ && x < nave.X()+5/*mas a la derecha*/ && y >= nave.Y()/*mas arriba*/ && y <= nave.Y()+2/*mas abajo*/)
    {
        nave.COR();
        nave.dibujar();
        nave.pintarcorazones();
        x = rand()%71 + 4;//numero entre 0 + 4 y 71 + 4
        y = 4;

    }
}

ModeloNaves::Nave::~Nave(){}
ModeloNaves::Ast::~Ast(){}
ModeloNaves::~ModeloNaves(){}




