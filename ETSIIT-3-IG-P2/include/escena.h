#ifndef _ESCENA_H
#define _ESCENA_H

#include <string>

#include "ejes.h"
#include "cubo.h"
#include "tetraedro.h"
#include "piramide.h"
#include "model_ply.h"
#include "model_rev.h"
#include "model_bar.h"

class Escena {
private:
    // tama�o de los ejes
#define AXIS_SIZE 5000
    Ejes ejes;
    
    //Figuras
    Tetraedro *tetra;
    Cubo *cubo;
    Piramide *piramide;
    Ply *model_ply;
    
    Rev *model_rev;
    int num_lados;
	std::string file;
    
    Bar *model_bar;
    
    //Enumerados: modo pintar, figura a pintar
    ModeDraw mode_draw;
    ModePolygon mode_polygon;

    // variables que definen la posicion de la camara en coordenadas polares
    GLfloat Observer_distance;
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat Width, Height, Front_plane, Back_plane;

private:
    void clear_window();
    void draw_axis();
    void draw_objects();

    //Transformaci�n de c�mara
    void change_projection();
    void change_observer();


public:
    Escena(const std::string &filename_p, const std::string &filename_rev="");
    //Escena(const char *filename_p);
    
    void inicializar(int UI_window_width, int UI_window_height);
    void redimensionar(int newWidth, int newHeight);

    // Dibujar
    void dibujar();

    // Interacci�n con la escena
    int teclaPulsada(unsigned char Tecla1, int x, int y);
    void teclaEspecial(int Tecla1, int x, int y);
};
#endif
