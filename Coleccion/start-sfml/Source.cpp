#include "header.h"
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
balaArcanoid::balaArcanoid(int myx,int myy){
    x=myx;
    y=myy;
    siguiente=NULL;
    forma.setSize({4,10});
}
bool balaArcanoid::mover(char**poderes,int ** bloques,int n,int m,int ancho, int alto,poderArcanoid*&power,barraArcanoid&player){
    y-=10;

    if(siguiente!=NULL){
        if(siguiente->mover(poderes,bloques,n,m,ancho,alto,power,player)){
            if(siguiente->siguiente==NULL){
                delete siguiente;
                siguiente=NULL;
            }else{
                balaArcanoid *aux=siguiente;
                siguiente=siguiente->siguiente;
                delete aux;
                siguiente=NULL;
            }
        }
    }
    return colision(poderes,bloques,n,m,ancho,alto,power,player);
}
bool balaArcanoid::colision(char**poderes,int ** bloques,int n,int m,int ancho, int alto,poderArcanoid*&power,barraArcanoid&player){
    if(y<-10){
        return true;
    }
    int anchoBloque=ancho/m;
    int altoBloque=alto/(2*n);
    int x1=x/anchoBloque;
    int y1=y/altoBloque;
    int x2=(x+4)/anchoBloque;
    int y2=(y+10)/altoBloque;
    int xaux=-10,yaux=-10;
    if(y2<n){
        if(bloques[y1][x1]){
            yaux=y1;
            xaux=x1;
        }else if(bloques[y2][x1]){
            yaux=y2;
            xaux=x1;
        }else if(bloques[y1][x2]){
            yaux=y1;
            xaux=x2;
        }else if(bloques[y2][x2]){
            yaux=y2;
            xaux=x2;
        }
    }
    if(xaux>-10){
            player.puntos+=10;
        bloques[yaux][xaux]--;
        if(!bloques[yaux][xaux]){
            poderArcanoid**aux=&power;
            if(power!=NULL){
                while((*aux)!=NULL){
                    aux=&((*aux)->siguiente);
                }
            }
            if(poderes[yaux][xaux]=='l'){
                (*aux)=new poderArcanoid(xaux*anchoBloque+anchoBloque/2,yaux*altoBloque+altoBloque/2,'l');
            }else if(poderes[yaux][xaux]=='s'){
                (*aux)=new poderArcanoid(xaux*anchoBloque+anchoBloque/2,yaux*altoBloque+altoBloque/2,'s');
            }else if(poderes[yaux][xaux]=='c'){
                (*aux)=new poderArcanoid(xaux*anchoBloque+anchoBloque/2,yaux*altoBloque+altoBloque/2,'c');
            }else if(poderes[yaux][xaux]=='m'){
                (*aux)=new poderArcanoid(xaux*anchoBloque+anchoBloque/2,yaux*altoBloque+altoBloque/2,'m');
            }
        }
        return true;
    }
    return false;
}
void balaArcanoid::destruir(){
    if(siguiente!=NULL){
        siguiente->destruir();
        delete siguiente;
    }
}

poderArcanoid::poderArcanoid(int myx,int myy,char mitipo){
    x=myx;
    y=myy;
    tipo=mitipo;
    siguiente=NULL;
}
bool poderArcanoid::mover(int myx,int ancho,barraArcanoid&jugador,pelotaArcanoid&ball){
    y+=5;
    if (siguiente!=NULL){
        if(siguiente->mover(myx,ancho,jugador,ball)){
            if(siguiente->siguiente!=NULL){
                poderArcanoid*aux=siguiente->siguiente;
                siguiente->siguiente=NULL;
                delete siguiente;//Colocar destructor
                siguiente=aux;
            }else{
                delete siguiente;//Colocar destructor
                siguiente=NULL;
            }
        }
    }
    if(x>myx-8&&x<myx+ancho&&y>330&&y<360){
        if(tipo=='s'){
            jugador.xs();
        }else if(tipo=='l'){
            jugador.xl();
        }else if(tipo=='c'){
            jugador.canhon();
        }else if(tipo=='m'){
            ball.duplicar();
        }
        return true;
    }else if (y>400){
        return true;
    }
    return false;
}
void poderArcanoid::destruir(){
    if(siguiente!=NULL){
        siguiente->destruir();
        delete siguiente;
    }
}

pelotaArcanoid::pelotaArcanoid(int myx,int myy,int myvx,int myvy,int myradio){
    x=myx;
    y=myy;
    if (!myvx||!myvy){
        srand ((int)(((double)clock())*100));
        vx=(rand()%5)+3;
        vy=(rand()%5)-8;
    }else{
        vx=myvx;
        vy=myvy;
    }
    radio=myradio;
    siguiente=NULL;
}
bool pelotaArcanoid::cambiarDir(int ancho,int alto, int xbarra,int xancho){
    if(siguiente!=NULL){
        if(siguiente->cambiarDir(ancho,alto,xbarra,xancho)){
            if(siguiente->siguiente==NULL){
                delete siguiente;//Colocar destructor
                siguiente=NULL;
            }else{
                pelotaArcanoid*aux;
                aux=siguiente->siguiente;
                delete siguiente;//Colocar destructor
                siguiente=aux;
            }
        }
    }
    srand ((int)(((double)clock())*100));
    if((x+vx-ancho+12)>0){
        if((x-ancho+12)<-1){
            vx=ancho-12-x;
        }else{
            vx=(rand()%5)-8;
        }
    }else if((x+vx)<0){
        if(x>1.0){
            vx=-x;
        }else{
            vx=(rand()%5)+3;
        }
    }
    if(y>alto){
        x=(ancho/2)-12;
        y=alto-62;
        vx=-5;
        vy=-5;
        return true;
    }else if((y+vy)<0){
        if(y>1.0){
            vy=-y;
        }else{
            vy=(rand()%5)+3;
        }
    }else if((y+vy-alto+50+radio*2)>0 && y+radio<360 && x>xbarra-radio&& x<xbarra+xancho+radio){
        if((y-alto+62)<-1){
            vy=ancho-62-y;
        }else{
            vy=(rand()%5)-8;
        }
    }
    return false;
}
void pelotaArcanoid::mover(){
    x+=vx;
    y+=vy;
    if(siguiente!=NULL){
        siguiente->mover();
    }
}

void pelotaArcanoid::duplicar(){
    if(siguiente==NULL){
        siguiente=new pelotaArcanoid(x,y,vx*-1,vy,radio);
    }else{
        pelotaArcanoid*aux=siguiente;
        siguiente=new pelotaArcanoid(x,y,vx*-1,vy,radio);
        siguiente->siguiente=aux;
        aux->duplicar();
    }
}
void pelotaArcanoid::colisionBloques2(int ** bloques,char**poderes,int n,int m,int ancho, int alto,poderArcanoid*&power,barraArcanoid&player){
    int anchoBloque=ancho/m;
    int altoBloque=alto/(2*n);
    int x1=x/anchoBloque;
    int y1=y/altoBloque;
    int x2=(x+radio+radio-2)/anchoBloque;
    int y2=(y+radio+radio-2)/altoBloque;
    int xaux=-10,yaux=-10;
    if(y2<n){
        if (x1==x2){
            if(bloques[y1][x1]){
                vy*=-1;
                xaux=x1;
                yaux=y1;
            }else if(bloques[y2][x1]){
                vy*=-1;
                xaux=x1;
                yaux=y2;
            }else if(vy<0&&(y+vy/2)/altoBloque>=0&&bloques[(y+vy/2)/altoBloque][x1]){
                xaux=x1;
                yaux=(y+vy/2)/altoBloque;
                vx*=-1;
                vy*=-1;
            }else if(vy>0&&((y+vy/2+radio+radio)/altoBloque)<n-1&&bloques[(y+radio+radio+vy/2)/altoBloque][x1]){
                xaux=x1;
                yaux=(y+radio+radio+vy/2)/altoBloque;
                vx*=-1;
                vy*=-1;
            }
        }else if(y1==y2){
            if(bloques[y1][x1]){
                vx*=-1;
                xaux=x1;
                yaux=y1;
            }else if(bloques[y1][x2]){
                vx*=-1;
                xaux=x2;
                yaux=y1;
            }
        }else{
            if(bloques[y1][x1]){
                vx=abs(vx);
                vy=abs(vy);
                xaux=x1;
                yaux=y1;
            }else if(bloques[y1][x2]){
                vx=-abs(vx);
                vy=abs(vy);
                xaux=x2;
                yaux=y1;
            }else if(bloques[y2][x1]){
                vx=abs(vx);
                vy=-abs(vy);
                xaux=x1;
                yaux=y2;
            }else if(bloques[y2][x2]){
                vx=-abs(vx);
                vy=-abs(vy);
                xaux=x2;
                yaux=y2;
            }
        }
    }
    if(xaux>-10){
        if(bloques[yaux][xaux]>0){
            player.puntos+=10;
        }
        bloques[yaux][xaux]--;
        if(!bloques[yaux][xaux]){
            if(bloques[yaux][xaux]>0){
                player.puntos+=10;
            }
            poderArcanoid**aux=&power;
            if(power!=NULL){
                while((*aux)!=NULL){
                    aux=&((*aux)->siguiente);
                }
            }
            if(poderes[yaux][xaux]=='l'){
                (*aux)=new poderArcanoid(xaux*anchoBloque+anchoBloque/2,yaux*altoBloque+altoBloque/2,'l');
            }else if(poderes[yaux][xaux]=='s'){
                (*aux)=new poderArcanoid(xaux*anchoBloque+anchoBloque/2,yaux*altoBloque+altoBloque/2,'s');
            }else if(poderes[yaux][xaux]=='c'){
                (*aux)=new poderArcanoid(xaux*anchoBloque+anchoBloque/2,yaux*altoBloque+altoBloque/2,'c');
            }else if(poderes[yaux][xaux]=='m'){
                (*aux)=new poderArcanoid(xaux*anchoBloque+anchoBloque/2,yaux*altoBloque+altoBloque/2,'m');
            }
        }
    }
    if(siguiente!=NULL){
        siguiente->colisionBloques2(bloques,poderes,n,m,ancho,alto,power,player);
    }
}
void pelotaArcanoid::destruir(){
    if(siguiente!=NULL){
        siguiente->destruir();
        delete siguiente;
    }
}

barraArcanoid::barraArcanoid(){
    puntos=0;
    vidas=3;
    x=175;
    direccion=0;
    ancho=50;
    canon=false;
}
barraArcanoid::barraArcanoid(int myx,int myancho){
    puntos=0;
    vidas=3;
    x=myx;
    direccion=0;
    ancho=myancho;
    canon=false;
}
void barraArcanoid::derecha(){
    direccion=1;
}
void barraArcanoid::izquierda(){
    direccion=-1;
}
void barraArcanoid::stop(){
    direccion=0;
}

void barraArcanoid::xs(){
    if (ancho>30){
        ancho-=14;
        x+=7;
    }
}
void barraArcanoid::xl(){
    if (ancho<70){
        ancho+=14;
        x-=7;
    }
}
void barraArcanoid::canhon(){
    canon=true;
}
void barraArcanoid::disparo(balaArcanoid*&shot){
    if(shot==NULL){
        shot=new balaArcanoid(x+ancho/2,350);
    }
    else{
        disparo(shot->siguiente);
    }
}
void barraArcanoid::mover(){
    if(direccion<0 && x>4){
        x-=10;
    }else if(direccion>0 && x<396-ancho){
        x+=10;
    }
}
bool barraArcanoid::reiniciar(){
    vidas--;
    if(!vidas){
        return true;
    }
    ancho=50;
    canon=false;
    x=200-(ancho/2);
    return false;
}

BloquesArcanoid::BloquesArcanoid(){
    haybloques=false;
    bloquesx=8;
    bloquesy=10;
    matriz=new int*[bloquesy];
    poderes=new char*[bloquesy];
    for(int i=0;i<bloquesy;i++){
        matriz[i]=new int[bloquesx];
        poderes[i]=new char[bloquesx];
    }
}
BloquesArcanoid::BloquesArcanoid(int ancho, int alto){
    haybloques=false;
    bloquesx=8;
    bloquesy=10;
    matriz=new int*[bloquesy];
    poderes=new char*[bloquesy];
    for(int i=0;i<bloquesy;i++){
        matriz[i]=new int[bloquesx];
        poderes[i]=new char[bloquesx];
    }
}
void BloquesArcanoid::crearNivel(int nivel=1){
    for(int i=0;i<bloquesy;i++){
        for(int j=0;j<bloquesx;j++){
            if(rand()%15==0){
                poderes[i][j]='l';
            }else if(rand()%15==1){
                poderes[i][j]='s';
            }else if(rand()%15==2){
                poderes[i][j]='m';
            }else if(rand()%15==3){
                poderes[i][j]='c';
            }
            if (nivel==1){
                if(/*i>0*/i>3 && i<bloquesy-3/*1*/&&j>0&&j<bloquesx-1){
                    matriz[i][j]=1;
                }else{
                    poderes[i][j]=0;
                    matriz[i][j]=0;
                }
            }else if (nivel==2){
                if(i>0 && i<bloquesy-1&&j>0&&j<bloquesx-1){
                    matriz[i][j]=1;
                }else{
                    matriz[i][j]=0;
                    poderes[i][j]=0;
                }
            }else if (nivel==3){
                if(i>1 && i<bloquesy-2&&j>1&&j<bloquesx-2){
                    matriz[i][j]=1;
                }else if(i>0 && i<bloquesy-1&&j>0&&j<bloquesx-1){
                    matriz[i][j]=2;
                }else{
                    matriz[i][j]=0;
                    poderes[i][j]=0;
                }
            }else if (nivel==4){
                if(i>1 && i<bloquesy-2&&j>1&&j<bloquesx-2){
                    matriz[i][j]=3;
                }else if(i>0 && i<bloquesy-1&&j>0&&j<bloquesx-1){
                    matriz[i][j]=1;
                }else{
                    matriz[i][j]=0;
                    poderes[i][j]=0;
                }
            }
        }
    }
}
BloquesArcanoid::~BloquesArcanoid(){
    for(int i; i<bloquesy;i++){
        delete[] matriz[i];
        delete[] poderes[i];
    }
    delete[] matriz;
    delete[] poderes;
}

ModeloArcanoid::ModeloArcanoid(int myalto,int myancho,int myfps){
    alto=myalto;
    ancho=myancho;
    fps=myfps;
    nivel=1;
    power=NULL;
    ball=new pelotaArcanoid((ancho/2)-6,(alto)-62,0,0,6);
    matriz.crearNivel(nivel);
    ataque=NULL;
    disparo=0;
}

void ModeloArcanoid::guardarpuntos(){
    std::cout<<"Ingresa tu nombre";
    char nombre[3];
    std::string cadenaNombre;
    std::cin.getline(nombre,4);
    std::stringstream ss;
    ss << nombre;
    ss >> cadenaNombre;
    std::string alm;
    std::string *nombres=new std::string[10];
    int *puntajes=new int[10];
    int cont=0;
    std::ifstream archivol("datos.txt");
    std::string cadena;
    while(!archivol.eof()) {
        cadena="";
        archivol >> cadena;
        nombres[cont]=cadena;
        cadena="";
        archivol >> cadena;
        puntajes[cont]=atoi(cadena.c_str());
        cont++;
    }
    if(cont==10){
        cont--;
    }
    nombres[cont]=cadenaNombre;
    puntajes[cont]=jugador.puntos;
    std::cout<<"Puntajes:\n";
    for(int i=0;i<=cont;i++){
        int imayor=i;
        for(int j=i+1;j<=cont;j++){
            if(puntajes[j]>puntajes[imayor]){
                imayor=j;
            }
        }
        if(imayor!=i){
            int aux=puntajes[i];
            std::string sAux=nombres[i];
            puntajes[i]=puntajes[imayor];
            nombres[i]=nombres[imayor];
            puntajes[imayor]=aux;
            nombres[imayor]=sAux;
        }
        std::stringstream ss2;
        alm+=nombres[i];
        alm+="\n";
        ss2 << puntajes[i];
        cadena="";
        ss2 >> cadena;
        alm+=cadena;
        if(i<cont)
            alm+="\n";
        std::cout<< i+1<<") "<<nombres[i]<<"\t"<< puntajes[i]<<"\n";
    }
    archivol.close();
    std::ofstream archivo;
    archivo.open("datos.txt");
    archivo << alm;
    archivo.close();
    delete[]puntajes;
    delete[]nombres;
}
bool ModeloArcanoid::run(int control){
    if(jugador.canon){
        if(control>=3&&!disparo){
            jugador.disparo(ataque);
            disparo=15;
        }else{
            if (disparo>0)
                disparo--;
        }
    }
    if (control==2||control==5){
        jugador.izquierda();
    }else if (control==1||control==4){
        jugador.derecha();
    }else{
        jugador.stop();
    }
    ball->mover();
    ball->colisionBloques2(matriz.matriz,matriz.poderes,matriz.bloquesy,matriz.bloquesx,ancho, alto,power,jugador);
    if(ball->cambiarDir(ancho,alto,jugador.x,jugador.ancho)){
        if (ball->siguiente==NULL){
            if(jugador.reiniciar()){
                std::cout<<"Tu puntaje fue: "<<jugador.puntos<<"\n";
                return true;
            }
        }else{
            pelotaArcanoid*aux=ball->siguiente;
            delete ball;//Colocar destructor
            ball=aux;
        }
    }
    jugador.mover();
    if(power!=NULL){
        if(power->mover(jugador.x,jugador.ancho,jugador,*ball)){
            if(power->siguiente!=NULL){
                poderArcanoid*aux=power->siguiente;
                power->siguiente=NULL;
                delete power;//Colocar destructor
                power=aux;
            }else{
                delete power;//Colocar destructor
                power=NULL;
            }
        }
    }
    if (ataque!=NULL){
        if(ataque->mover(matriz.poderes,matriz.matriz,matriz.bloquesy,matriz.bloquesx,ancho, alto,power,jugador)){
            if(ataque->siguiente==NULL){
                delete ataque;
                ataque=NULL;
            }else{
                balaArcanoid*aux=ataque;
                ataque=ataque->siguiente;
                delete aux;
            }
        }
    }
    return false;
}
ModeloArcanoid::~ModeloArcanoid(){
    if(power!=NULL){
        power->destruir();
        delete power;
    }
    if(ball!=NULL){
        ball->destruir();
        delete ball;
    }
    if(ataque!=NULL){
        ataque->destruir();
        delete ataque;
    }
}

VistaArcanoid::VistaArcanoid(){
    int bloquesx=8;
    int bloquesy=10;
    for(int i=0;i<bloquesy;i++){
        for(int j=0;j<bloquesx;j++){
            bloques[i][j].setSize({400/bloquesx,(400/2)/bloquesy});
            bloques[i][j].setPosition((400/bloquesx)*j,((400/2)/bloquesy)*i);
        }
    }
    ball.setRadius(6);
    ball.setFillColor(sf::Color::Red);
    shot.setSize({4,10});
    bar.setSize({50,10});
    power.setSize({8,20});
}
void VistaArcanoid::dibujarPelota(pelotaArcanoid *pelot,sf::RenderWindow &win){
    ball.setPosition(pelot->x,pelot->y);
    win.draw(ball);
    if(pelot->siguiente!=NULL){
        dibujarPelota(pelot->siguiente,win);
    }
}
void VistaArcanoid::dibujarDisparo(balaArcanoid * b,sf::RenderWindow &win){
    shot.setPosition(b->x,b->y);
    win.draw(shot);
    if(b->siguiente!=NULL){
        dibujarDisparo(b->siguiente,win);
    }
}
void VistaArcanoid::dibujarPoder(poderArcanoid *p,sf::RenderWindow &win){
    power.setPosition(p->x,p->y);
    if(p->tipo=='s'){
        power.setFillColor(sf::Color::Red);
    }else if(p->tipo=='l'){
        power.setFillColor(sf::Color::Green);
    }else if(p->tipo=='m'){
        power.setFillColor(sf::Color::Magenta);
    }else if(p->tipo=='c'){
        power.setFillColor(sf::Color::Cyan);
    }
    win.draw(power);
    if(p->siguiente!=NULL){
        dibujarPoder(p->siguiente,win);
    }
}
void VistaArcanoid::dibujarBarra(int x,int ancho,sf::RenderWindow &win){
    bar.setSize({ancho,10});
    bar.setPosition(x,350);
    win.draw(bar);
}
bool VistaArcanoid::dibujarBloques(int**matriz,sf::RenderWindow &win){
    bool haybloques=false;
    for(int i=0;i<10;i++){
        for(int j=0;j<8;j++){
            if(matriz[i][j]){
                if(matriz[i][j]<0){
                    bloques[i][j].setFillColor(sf::Color::White);
                }else if(matriz[i][j]==1){
                    bloques[i][j].setFillColor(sf::Color::Blue);
                }
                else if(matriz[i][j]==2){
                    bloques[i][j].setFillColor(sf::Color::Green);
                }else if(matriz[i][j]==3){
                    bloques[i][j].setFillColor(sf::Color::Yellow);
                }
                win.draw(bloques[i][j]);
                haybloques=true;
            }
        }
    }
    return haybloques;
}
void VistaArcanoid::show(ModeloArcanoid&arc,sf::RenderWindow &win){
    win.clear();
    dibujarBarra(arc.jugador.x,arc.jugador.ancho,win);
    dibujarPelota(arc.ball,win);
    if (arc.ataque!=NULL){
        dibujarDisparo(arc.ataque,win);
    }
    if(arc.power!=NULL){
        dibujarPoder(arc.power,win);
    }
    if(!dibujarBloques(arc.matriz.matriz,win)){
        arc.nivel++;
        arc.matriz.crearNivel(arc.nivel);
    }
    dibujarVidas(arc.jugador.vidas,win);
    win.display();
    Sleep(1000/arc.fps);
}

void VistaArcanoid::dibujarVidas(int vidas,sf::RenderWindow & win){
    for(int i=1;i<vidas;i++){
        ball.setPosition(400-(i*30),370);
        win.draw(ball);
    }
}

ControlArcanoid::ControlArcanoid(){
    teclaPres=0;
}
int ControlArcanoid::detectEvents(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        teclaPres=1;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        teclaPres=2;
    }else{
        teclaPres=0;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        teclaPres+=3;
    }
    return teclaPres;
}
void arcanoidrun(){
    int ancho=400,alto=400,fps=33;
    ModeloArcanoid arc(alto,ancho,fps);
    VistaArcanoid view=VistaArcanoid();
    ControlArcanoid controller=ControlArcanoid();
    sf::RenderWindow win(sf::VideoMode(ancho, alto), "Juego");
    while (win.isOpen()){
        sf::Event event;
        while (win.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                win.close();
            }
        }
        if(arc.run(controller.detectEvents())){
            win.close();
            arc.guardarpuntos();
        }else{
            view.show(arc,win);
        }
    }
}
