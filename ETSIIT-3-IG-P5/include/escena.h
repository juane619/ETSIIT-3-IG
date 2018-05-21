#ifndef _ESCENA_H
#define _ESCENA_H

#include <string>
#include <vector>

#include "ejes.h"
#include "cubo.h"
#include "tetraedro.h"
#include "piramide.h"
#include "model_ply.h"
#include "model_rev.h"
#include "model_bar.h"
#include "model_jer.h"
#include "tablero.h"
#include "luz.h"
#include "material.h"
#include "camara.h"

using namespace std;

//enum ModeRaton{
//    MOVING_FIRST;
//};

class Escena {
private:
    // tamanio de los ejes
#define AXIS_SIZE 10000
    Ejes ejes;

    //Figuras
    Tetraedro* tetra;
    Cubo* cubo;
    Piramide* piramide;
    Ply* model_ply;

    Rev* model_rev;
    int num_lados;

    Bar* model_bar;

    //PRACTICA3
    Jer* model_jer;

    //PRACTICA4
    Luz* luz0;
    Luz* luz1;
    Material *mat1;
    Tablero* tablero;
    Suelo* suelo;

    //Enumerados: modo pintar, figura a pintar
    ModeDraw mode_draw;
    ModePolygon mode_polygon;
    ModeLuz mode_luz;
    ModeCamara mode_cam;
    bool transform_vista=false;


    //PRAC5
    vector<Camara*> camaras;
    int estado_raton;
    int xaux, yaux;
    
private:
    void clear_window();
    void draw_axis();
    void draw_objects();

    //Transformacion de camara
    void change_projection();
    //void change_observer();

    //Preparacion de textura(PRAC4)
    void prepara_textura(void);

public:
    Escena(const std::string &filename_p, const std::string &filename_rev = "");

    void inicializar(int UI_window_width, int UI_window_height);
    void redimensionar(int newWidth, int newHeight);

    // Dibujar
    void dibujar();

    // Interaccion con la escena
    int teclaPulsada(unsigned char Tecla1, int x, int y);
    void teclaEspecial(int Tecla1, int x, int y);

    //PRACTICA3: ANIMACION
    void animar();

    //PRACTICA4: TEXTURAS
    void liberaTextura();

    //PRAC5

    void clickRaton(int boton, int estado, int x, int y);

    void ratonMovido(int x, int y);

};
#endif
