#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "escena.h"

const int AGRANDAR = 200;

Escena::Escena(const std::string &filename_p, const std::string &filename_rev) {
    Front_plane = 50;
    Back_plane = 2000;
    Observer_distance = 4 * Front_plane;
    Observer_angle_x = Observer_angle_y = 0;
    ejes.changeAxisSize(5000);

    //enumerados poligonos y modos
    mode_draw = ModeDraw::LINES;
    mode_polygon = ModePolygon::CUBE;

    //construccion de cubo,tetra,piramide y ply
    cubo = new Cubo(2.0);
    tetra = new Tetraedro(2.0);
    piramide = new Piramide(2.0, 2.0);
    model_ply = new Ply(filename_p);

    //construccion del revolucion
    num_lados = 24;
    std::vector<Punto3D> vec_pasar;

    vec_pasar.push_back(Punto3D(3.0, 5.0, 0.0));
    vec_pasar.push_back(Punto3D(3.0, 4.0, 0.0));
    vec_pasar.push_back(Punto3D(3.0, 3.0, 0.0));
    vec_pasar.push_back(Punto3D(2.0, 2.0, 0.0));
    vec_pasar.push_back(Punto3D(1.5, 1.0, 0.0));
    vec_pasar.push_back(Punto3D(1.0, 0.0, 0.0));

    if (!filename_rev.empty())
        model_rev = new Rev(filename_rev, num_lados); //construccion del revolucion desde archivo
    else
        model_rev = new Rev(vec_pasar, num_lados); //construccion del revolucion a mano

    //construccion del barrido
    model_bar = new Bar();

    //PRACTICA3
    model_jer = new Jer();
}

void Escena::inicializar(int UI_window_width, int UI_window_height) {

    glClearColor(1, 0, 1, 1); // se indica cual sera el color para limpiar la ventana	(r,v,a,al)

    glEnable(GL_DEPTH_TEST); // se habilita el z-bufer

    this->change_projection();
    Width = UI_window_width;
    Height = UI_window_height;
    glViewport(0, 0, UI_window_width, UI_window_height);
}


//**************************************************************************
// Funcion que dibuja objetos en la escena
//***************************************************************************

void Escena::draw_objects() {
    glEnable(GL_CULL_FACE);

    if (mode_polygon == ModePolygon::TETRA)
        tetra->draw(mode_draw);
    else if (mode_polygon == ModePolygon::CUBE)
        cubo->draw(mode_draw);
    else if (mode_polygon == ModePolygon::PYRAMID)
        piramide->draw(mode_draw);
    else if (mode_polygon == ModePolygon::PLY)
        model_ply->draw(mode_draw);
    else if (mode_polygon == ModePolygon::REV)
        model_rev->draw(mode_draw);
    else if (mode_polygon == ModePolygon::BAR)
        model_bar->draw(mode_draw);
    else if (mode_polygon == ModePolygon::JER) {
        model_jer->draw(mode_draw);
    }
}

void Escena::dibujar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
    change_observer();
    draw_axis();
    draw_objects();
}

void Escena::animar(){
    if (mode_polygon == ModePolygon::JER){
        model_jer->animar();
    }
}

int Escena::teclaPulsada(unsigned char Tecla1, int x, int y) {

    std::cout << "Tecla " << Tecla1 << std::endl;
    if (toupper(Tecla1) == 'Q') return 1;
    else if (toupper(Tecla1) == 'F')
        mode_draw = ModeDraw::SOLID;
    else if (toupper(Tecla1) == 'L')
        mode_draw = ModeDraw::LINES;
    else if (toupper(Tecla1) == 'P')
        mode_draw = ModeDraw::POINTS;
    else if (toupper(Tecla1) == 'C')
        mode_draw = ModeDraw::CHESS;
    else if (toupper(Tecla1) == 'T')
        mode_draw = ModeDraw::TODO;
    else if (toupper(Tecla1) == '1')
        mode_polygon = ModePolygon::TETRA;
    else if (toupper(Tecla1) == '2')
        mode_polygon = ModePolygon::CUBE;

        //PRACTICA2
    else if (toupper(Tecla1) == '3')
        mode_polygon = ModePolygon::PLY;
    else if (toupper(Tecla1) == '4')
        mode_polygon = ModePolygon::REV;
    if (mode_polygon == ModePolygon::REV) {
        if (toupper(Tecla1) == '+') {
            model_rev->addLine();
        } else if (toupper(Tecla1) == '-') {
            model_rev->deleteLine();
        } else if (toupper(Tecla1) == '/') {
            model_rev->pintarTapas();
        } else if (toupper(Tecla1) == '*') {
            model_rev->quitarTapas();
        }
    }//

        /*PRACTICA 3*/
    else if (toupper(Tecla1) == '5')
        mode_polygon = ModePolygon::JER;
    if (mode_polygon == ModePolygon::JER) {
        if (toupper(Tecla1) == 'W') {
            model_jer->avanzar();
        }else if (toupper(Tecla1) == 'S') {
            model_jer->retroceder();
        }else if (Tecla1 == 'h') {
            model_jer->aumentarSpeedPistones();
        }else if (Tecla1 == 'H') {
            model_jer->disminuirSpeedPistones();
        }else if (Tecla1 == 'j') {
            model_jer->aumentarSpeedGiroBody();
        }else if (Tecla1 == 'J') {
            model_jer->disminuirSpeedGiroBody();
        }else if (Tecla1 == 'k') {
            model_jer->aumentarSpeedMaquina();
        }else if (Tecla1 == 'K') {
            model_jer->disminuirSpeedMaquina();
        }else if (Tecla1 == 'v') {
            model_jer->abrirCazo();
        }else if (Tecla1 == 'V') {
            model_jer->cerrarCazo();
        }else if (Tecla1 == 'b') {
            model_jer->abrirBrazoCazo();
        }else if (Tecla1 == 'B') {
            model_jer->cerrarBrazoCazo();
        }else if (Tecla1 == 'n') {
            model_jer->subirBrazoCompleto();
        }else if (Tecla1 == 'N') {
            model_jer->bajarBrazoCompleto();
        }else if (Tecla1 == 'm') {
            model_jer->girarDerecha();
        }else if (Tecla1 == 'M') {
            model_jer->girarIzquierda();
        }
    }//FIN PRACTICA3

    else if (toupper(Tecla1) == '6')
        mode_polygon = ModePolygon::BAR;
    else if (toupper(Tecla1) == '7')
        mode_polygon = ModePolygon::PYRAMID;


    return 0;
}

void Escena::teclaEspecial(int Tecla1, int x, int y) {
    switch (Tecla1) {
        case GLUT_KEY_LEFT:
            Observer_angle_y--;
            break;
        case GLUT_KEY_RIGHT:
            Observer_angle_y++;
            break;
        case GLUT_KEY_UP:
            Observer_angle_x--;
            break;
        case GLUT_KEY_DOWN:
            Observer_angle_x++;
            break;
        case GLUT_KEY_PAGE_UP:
            Observer_distance *= 1.2;
            break;
        case GLUT_KEY_PAGE_DOWN:
            Observer_distance /= 1.2;
            break;
    }

    std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformaci�n de proyeccion
//***************************************************************************

void Escena::change_projection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-Width / AGRANDAR, Width / AGRANDAR, -Height / AGRANDAR, Height / AGRANDAR, Front_plane, Back_plane);
}

void Escena::redimensionar(int newWidth, int newHeight) {
    change_projection();
    Width = newWidth / 10;
    Height = newHeight / 10;
    glViewport(0, 0, newWidth, newHeight);
}


//**************************************************************************
// Funcion para definir la transformaci�n de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer() {

    // posicion del observador
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -Observer_distance);
    glRotatef(Observer_angle_x, 1, 0, 0);
    glRotatef(Observer_angle_y, 0, 1, 0);
}


//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void Escena::draw_axis() {
    ejes.draw();
}




