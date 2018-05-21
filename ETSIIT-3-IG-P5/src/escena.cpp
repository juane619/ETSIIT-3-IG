#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdio>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>

#include "escena.h"

Escena::Escena(const std::string &filename_p, const std::string &filename_rev) {
    ejes.changeAxisSize(AXIS_SIZE);

    //enumerados poligonos y modos
    mode_draw = ModeDraw::LINES;
    mode_polygon = ModePolygon::CUBE;
    mode_luz = ModeLuz::LUZ0;
    mode_cam = ModeCamara::CAM0;

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

    //SUELO
    suelo = new Suelo(15.0);

    //CONSTRUCCION LUCES
    const GLfloat caf0[4] = {0.45, 0.45, 0.45, 1.0}; // color ambiental de la fuente
    const GLfloat cdf0[4] = {0.35, 0.35, 0.35, 1.0}; // color difuso de la fuente
    const GLfloat csf0[4] = {0.6, 0.6, 0.6, 1.0}; // color especular de la fuente
    const GLfloat posf[4] = {0.0, 0.0, 0.0, 1.0}; //luces posicionales (bombilla)
    luz0 = new Luz(caf0, cdf0, csf0, posf);


    const GLfloat caf1[4] = {0., 1.0, 0., 1.0}; // color ambiental de la fuente
    const GLfloat cdf1[4] = {0., 0.35, 0., 1.0}; // color difuso de la fuente
    const GLfloat csf1[4] = {0., 0., 0., 1.0}; // color especular de la fuente
    const GLfloat dirf[4] = {0., 0., 0., 0.0}; //luces direccionales (a una direccion)
    luz1 = new Luz(caf1, cdf1, csf1, dirf);


    //CONSTRUCCION MATERIALES
    //mat1
    const GLfloat cafm1[4] = {0., 0., 1., 1.0}; // color ambiental del material
    const GLfloat cdfm1[4] = {0., 0.0, 1.0, 1.0}; // color difuso del material
    const GLfloat csfm1[4] = {0.1, 0.1, 0.4, 1.0}; // color especular del material
    const GLfloat exponente1 = 24.0;
    mat1 = new Material(cafm1, cdfm1, csfm1, exponente1);

    //COnstruccion tablero
    tablero = new Tablero(1, 8);

    //PRAC5
    estado_raton = 0; //0: no_pulsado, 1: pulsado.


}

void Escena::inicializar(int UI_window_width, int UI_window_height) {
    glClearColor(0.8, 0.8, 1.0, 0); // se indica cual sera el color para limpiar la ventana	(r,g,b,al)

    glEnable(GL_DEPTH_TEST); // se habilita el z-bufer
    glEnable(GL_NORMALIZE);

    //PRAC5
    Camara* cam1 = new Camara(UI_window_width, UI_window_height, 20, 1500);
    camaras.push_back(cam1);

    camaras[0]->changeProjection();

    glViewport(0, 0, UI_window_width, UI_window_height);

    tablero->prepara_textura();
}

//**************************************************************************
// Funcion para definir la transformacion de proyeccion
//***************************************************************************
//
//void Escena::change_projection() {
//    std::cout << -Width / 200.0 << " " << Width / 200.0 << " " << -Height / 200.0 << " " << Height / 200.0 << " " << Front_plane << " " << Back_plane << "\n";
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glFrustum(-Width / 200.0, Width / 200.0,
//            -Height / 200.0, Height / 200.0,
//            Front_plane, Back_plane);
//}

void Escena::dibujar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
    glEnable(GL_CULL_FACE);

    //set camera
    camaras[mode_cam]->changeObserver();

    /*Set Ilumination*/
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    luz0->setLight();
    luz1->setLight();

    draw_axis();
    draw_objects();
}

//**************************************************************************
// Funcion para definir la transformaci�n de vista (posicionar la camara)
//***************************************************************************

//void Escena::change_observer() {
//    // posicion del observador
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glTranslatef(0, 0, -Observer_distance);
//    glRotatef(Observer_angle_x, 1, 0, 0);
//    glRotatef(Observer_angle_y, 0, 1, 0);
//}

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
    else if (mode_polygon == ModePolygon::JER) {
        model_jer->draw(mode_draw);
        suelo->draw(mode_draw);
    } else if (mode_polygon == ModePolygon::TAB)
        tablero->draw(mode_draw);
}

void Escena::clickRaton(int boton, int estado, int x, int y) {
    if (boton == GLUT_RIGHT_BUTTON) {
        if (estado == GLUT_DOWN) {
            //entramos en estado moviendo raton
            estado_raton = 1;
            camaras[mode_cam]->guardarPos(x, y);
            //std::cout << x << " " << y << std::endl;
        } else {
            //salimos del estado moviendo raton
            estado_raton = 0;
            camaras[mode_cam]->guardarPos(0, 0);
        }
    }
}

void Escena::ratonMovido(int x, int y) {
    if (estado_raton == 1) {
        
        xaux = camaras[mode_cam]->getXAnt();
        yaux = camaras[mode_cam]->getYAnt();
        
        camaras[mode_cam]->girar(x-xaux, y-yaux);
        
        camaras[mode_cam]->guardarPos(x, y);
        
//        if (x > xaux && y > yaux)
//            camaras[mode_cam]->girar(2, 2);
//        else if (x > xaux && y < yaux)
//            camaras[mode_cam]->girar(2, -2);
//        else if (x < xaux && y < yaux)
//            camaras[mode_cam]->girar(-2, -2);
//        else if (x < xaux && y > yaux)
//            camaras[mode_cam]->girar(-2, 2);
    }
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
        if (!transform_vista) {
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
        } //
    }
    if (transform_vista) {
        if (toupper(Tecla1) == 'W') {
            camaras[mode_cam]->avanzar();
        } else if (toupper(Tecla1) == 'S') {
            camaras[mode_cam]->retroceder();
        } else if (toupper(Tecla1) == 'A') {
            camaras[mode_cam]->moveLeft();
        } else if (toupper(Tecla1) == 'D') {
            camaras[mode_cam]->moveRight();
        } else if (toupper(Tecla1) == 'R') {
            camaras[mode_cam]->resetPosition();
        }
    }

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

    if (mode_polygon == TAB) {
        if (toupper(Tecla1) == 'T')
            tablero->onOffTex();
        if (tablero->isEnabledTex()) {
            if (toupper(Tecla1) == 'C')
                tablero->giro90();
            else if (toupper(Tecla1) == 'V')
                tablero->giro180();
            else if (toupper(Tecla1) == 'B')
                tablero->giro270();
            else if (toupper(Tecla1) == 'N')
                tablero->giro0();
            else if (toupper(Tecla1) == 'A')
                tablero->despIzq();
        }
    }

    return 0;
}

void Escena::teclaEspecial(int Tecla1, int x, int y) {
    switch (Tecla1) {
        case GLUT_KEY_LEFT:
            //Observer_angle_y -= 2;
            break;
        case GLUT_KEY_RIGHT:
            //Observer_angle_y += 2;
            break;
        case GLUT_KEY_UP:
            //Observer_angle_x -= 2;
            break;
        case GLUT_KEY_DOWN:
            //Observer_angle_x += 2;
            break;
        case GLUT_KEY_PAGE_UP:
            //Observer_distance *= 1.2;
            break;
        case GLUT_KEY_PAGE_DOWN:
            //Observer_distance /= 1.2;
            break;
            //PRAC4
        case GLUT_KEY_F1:
            mode_luz = ModeLuz::LUZ0;
            break;
        case GLUT_KEY_F2:
            mode_luz = ModeLuz::LUZ1;
            break;
            //prac5
        case GLUT_KEY_F3:
            mode_cam = ModeCamara::CAM0;
            break;
        case GLUT_KEY_F4:
            mode_cam = ModeCamara::CAM1;
            break;
        case GLUT_KEY_F5:
            mode_cam = ModeCamara::CAM2;
            break;
        case GLUT_KEY_F6:
            if (transform_vista) {
                transform_vista = false;
            } else {
                transform_vista = true;
            }
            break;
        case GLUT_KEY_F7:
            break;
    }

    //std::cout << Observer_distance << std::endl;
}





//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void Escena::draw_axis() {
    if (glIsEnabled(GL_LIGHTING)) glDisable(GL_LIGHTING);
    ejes.draw();
}


//Funcion para animar el modelo jerarquico

void Escena::animar() {
    if (mode_polygon == ModePolygon::JER) {
        //model_jer->animar();
    }
}

//Funcion para liberar textura al salir del programa

void Escena::liberaTextura() {
    tablero->liberaTextura();
}

//Funcion que se llama al redimensionar la pantalla

void Escena::redimensionar(int newWidth, int newHeight) {
    camaras[mode_cam]->changeProjection();
    glViewport(0, 0, newWidth, newHeight);
}

