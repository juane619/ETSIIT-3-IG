#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdio>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>

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
    mode_luz = ModeLuz::LUZ0;

    //construccion de cubo,tetra,piramide y ply
    cubo = new Cubo(1.0);
    tetra = new Tetraedro(1.0);
    piramide = new Piramide(1.0, 1.0);
    model_ply = new Ply(filename_p);

    //construccion del revolucion examen
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

    //PRACTICA3: modelo jerarquico
    model_jer = new Jer();

    //PRACTICA4
    //CONSTRUCCION LUCES
    const GLfloat caf0[4] = {0., 0.4, 0., 1.0}; // color ambiental de la fuente
    const GLfloat cdf0[4] = {1.0, 0.0, 0.0, 1.0}; // color difuso de la fuente
    const GLfloat csf0[4] = {0.0, 0.0, 0.0, 1.0}; // color especular de la fuente
    const GLfloat posf[4] = {0.0, 0.0, 0.0, 1.0}; //luces posicionales (bombilla)
    luz0 = new Luz(caf0, cdf0, csf0, posf);

    const GLfloat caf1[4] = {0., 0., 0., 1.0}; // color ambiental de la fuente
    const GLfloat cdf1[4] = {1., 1., 1., 1.0}; // color difuso de la fuente
    const GLfloat csf1[4] = {0., 0., 0., 1.0}; // color especular de la fuente
    const GLfloat dirf[4] = {0., 0., 0., 0.0}; //luces direccionales (a una direccion)
    luz1 = new Luz(caf1, cdf1, csf1, dirf);

    //CONSTRUCCION MATERIALES
    //mat1
    const GLfloat cafm1[4] = {0., 1., 0., 1.0}; // color ambiental del material
    const GLfloat cdfm1[4] = {1., 0.0, 0.0, 1.0}; // color difuso del material
    const GLfloat csfm1[4] = {0.0, 0.0, 0.0, 1.0}; // color especular del material
    const GLfloat exponente1 = 24.0;
    mat1 = new Material(cafm1, cdfm1, csfm1, exponente1);

    //mat2
    const GLfloat cafm2[4] = {0.0, 0.0, 0.0, 1.0}; // color ambiental del material
    const GLfloat cdfm2[4] = {0.0, 1.0, 0.0, 1.0}; // color difuso del material
    const GLfloat csfm2[4] = {0.0, 0.0, 0.0, 1.0}; // color especular del material
    const GLfloat exponente2 = 24.0;
    mat2 = new Material(cafm2, cdfm2, csfm2, exponente2);

    //mat3
    const GLfloat cafm3[4] = {0.0, 0.0, 0.0, 1.0}; // color ambiental del material
    const GLfloat cdfm3[4] = {0.0, 0.0, 1.0, 1.0}; // color difuso del material
    const GLfloat csfm3[4] = {0.0, 0.0, 0.0, 1.0}; // color especular del material
    const GLfloat exponente3 = 24.0;
    mat3 = new Material(cafm3, cdfm3, csfm3, exponente3);

    //COnstruccion tablero
    tablero = new Tablero(1, 8);
}

void Escena::inicializar(int UI_window_width, int UI_window_height) {

    glClearColor(0.8, 0.8, 1.0, 0); // se indica cual sera el color para limpiar la ventana	(r,g,b,al)

    glEnable(GL_DEPTH_TEST); // se habilita el z-bufer
    glEnable(GL_NORMALIZE);

    this->change_projection();
    Width = UI_window_width;
    Height = UI_window_height;
    glViewport(0, 0, UI_window_width, UI_window_height);

    tablero->prepara_textura();
}

void Escena::dibujar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
    glEnable(GL_CULL_FACE);

    glEnable(GL_LIGHTING);
    float global_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    glShadeModel(GL_SMOOTH);

    change_observer(); //set camera

    luz0->setLight();
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    draw_axis();


    draw_objects();
}

//**************************************************************************
// Funcion que dibuja objetos en la escena
//***************************************************************************

void Escena::draw_objects() {
    if (!glIsEnabled(GL_LIGHTING)) glEnable(GL_LIGHTING);

    if (mode_polygon == ModePolygon::TETRA)
        tetra->draw(mode_draw);
    else if (mode_polygon == ModePolygon::CUBE) {
        cubo->draw(mode_draw);
    } else if (mode_polygon == ModePolygon::PYRAMID)
        piramide->draw(mode_draw);
    else if (mode_polygon == ModePolygon::PLY)
        model_ply->draw(mode_draw);
    else if (mode_polygon == ModePolygon::REV)
        model_rev->draw(mode_draw);
    else if (mode_polygon == ModePolygon::BAR)
        model_bar->draw(mode_draw);
    else if (mode_polygon == ModePolygon::JER)
        model_jer->draw(mode_draw);
    else if (mode_polygon == ModePolygon::TAB)
        tablero->draw(mode_draw);

}

void Escena::animar() {
    if (mode_polygon == ModePolygon::JER) {
        //model_jer->animar();
    }
}

void Escena::liberaTextura() {
    tablero->liberaTextura();
}

int Escena::teclaPulsada(unsigned char Tecla1, int x, int y) {
    std::cout << "Tecla " << Tecla1 << std::endl;
    if (toupper(Tecla1) == 'Q') return 1;
        //PRACTICA1: MODOS PINTADO
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
        //

        //PRACTICA2: MODELOS A PINTAR
    else if (toupper(Tecla1) == '1')
        mode_polygon = ModePolygon::TETRA;
    else if (toupper(Tecla1) == '2')
        mode_polygon = ModePolygon::CUBE;
    else if (toupper(Tecla1) == '3')
        mode_polygon = ModePolygon::PLY;
    else if (toupper(Tecla1) == '4')
        mode_polygon = ModePolygon::REV;
    else if (toupper(Tecla1) == '5')
        mode_polygon = ModePolygon::JER;
    else if (toupper(Tecla1) == '6')
        mode_polygon = ModePolygon::BAR;
    else if (toupper(Tecla1) == '7')
        mode_polygon = ModePolygon::PYRAMID;
    else if (toupper(Tecla1) == '8')
        mode_polygon = ModePolygon::TAB;
    //

    //Parametros modelo revolucion
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

        //Parametros modelo jerarquico(prac3)
    else if (mode_polygon == ModePolygon::JER) {
        if (toupper(Tecla1) == 'W') {
            model_jer->avanzar();
        } else if (toupper(Tecla1) == 'S') {
            model_jer->retroceder();
        } else if (Tecla1 == 'h') {
            model_jer->aumentarSpeedPistones();
        } else if (Tecla1 == 'H') {
            model_jer->disminuirSpeedPistones();
        } else if (Tecla1 == 'j') {
            model_jer->aumentarSpeedGiroBody();
        } else if (Tecla1 == 'J') {
            model_jer->disminuirSpeedGiroBody();
        } else if (Tecla1 == 'k') {
            model_jer->aumentarSpeedMaquina();
        } else if (Tecla1 == 'K') {
            model_jer->disminuirSpeedMaquina();
        } else if (Tecla1 == 'v') {
            model_jer->abrirCazo();
        } else if (Tecla1 == 'V') {
            model_jer->cerrarCazo();
        } else if (Tecla1 == 'b') {
            model_jer->abrirBrazoCazo();
        } else if (Tecla1 == 'B') {
            model_jer->cerrarBrazoCazo();
        } else if (Tecla1 == 'n') {
            model_jer->subirBrazoCompleto();
        } else if (Tecla1 == 'N') {
            model_jer->bajarBrazoCompleto();
        } else if (Tecla1 == 'm') {
            model_jer->girarDerecha();
        } else if (Tecla1 == 'M') {
            model_jer->girarIzquierda();
        }
    }//

    //Luces(prac4)
    if (toupper(Tecla1) == 'I') {
        if (mode_luz == ModeLuz::LUZ0)
            luz0->onOff();
        else if (mode_luz == ModeLuz::LUZ1)
            luz1->onOff();
    }

    if (Tecla1 == 'x') {
        if (mode_luz == ModeLuz::LUZ0)
            luz0->xMas();
        else
            luz1->xMas();
    } else if (Tecla1 == 'X') {
        if (mode_luz == ModeLuz::LUZ0)
            luz0->xMenos();
        else
            luz1->xMenos();
    } else if (Tecla1 == 'y') {
        if (mode_luz == ModeLuz::LUZ0)
            luz0->yMas();
        else
            luz1->yMas();
    } else if (Tecla1 == 'Y') {
        if (mode_luz == ModeLuz::LUZ0)
            luz0->yMenos();
        else
            luz1->yMenos();
    }
    
    if(mode_polygon==TAB){
        if(toupper(Tecla1) == 'T')
            tablero->onOffTex();
        if(tablero->isEnabledTex()){
            if(toupper(Tecla1) == 'C')
                tablero->giro90();
            else if(toupper(Tecla1) == 'V')
                tablero->giro180();
            else if(toupper(Tecla1) == 'B')
                tablero->giro270();
            else if(toupper(Tecla1) == 'N')
                tablero->giro0();
            else if(toupper(Tecla1) == 'A')
                tablero->despIzq();
        }
    }


    return 0;
}

void Escena::teclaEspecial(int Tecla1, int x, int y) {
    switch (Tecla1) {
        case GLUT_KEY_LEFT:
            Observer_angle_y -= 2;
            break;
        case GLUT_KEY_RIGHT:
            Observer_angle_y += 2;
            break;
        case GLUT_KEY_UP:
            Observer_angle_x -= 2;
            break;
        case GLUT_KEY_DOWN:
            Observer_angle_x += 2;
            break;
        case GLUT_KEY_PAGE_UP:
            Observer_distance *= 1.2;
            break;
        case GLUT_KEY_PAGE_DOWN:
            Observer_distance /= 1.2;
            break;
            //PRAC4
        case GLUT_KEY_F1:
            mode_luz = ModeLuz::LUZ0;
            break;
        case GLUT_KEY_F2:
            mode_luz = ModeLuz::LUZ1;
            break;
        case GLUT_KEY_F5:
            mat1->apply();
            break;
        case GLUT_KEY_F6:
            mat2->apply();
            break;
        case GLUT_KEY_F7:
            mat3->apply();
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
    if (glIsEnabled(GL_LIGHTING)) glDisable(GL_LIGHTING);
    ejes.draw();
}