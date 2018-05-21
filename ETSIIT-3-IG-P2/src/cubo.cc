#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "cubo.h"

Cubo::Cubo(float size) {    
    vertices.push_back(Punto3D(0.0, 0.0, size));
    vertices.push_back(Punto3D(size, 0.0, size));
    vertices.push_back(Punto3D(0.0, size, size));
    vertices.push_back(Punto3D(size, size, size));
    vertices.push_back(Punto3D(0.0, 0.0, 0.0));
    vertices.push_back(Punto3D(size, 0.0, 0.0));
    vertices.push_back(Punto3D(0.0, size, 0.0));
    vertices.push_back(Punto3D(size, size, 0.0));

    caras.push_back(Cara(0, 1, 2));
    caras.push_back(Cara(1, 3, 2));
    caras.push_back(Cara(2, 3, 7));
    caras.push_back(Cara(2, 7, 6));
    caras.push_back(Cara(1, 7, 3));
    caras.push_back(Cara(1, 5, 7));
    caras.push_back(Cara(6, 7, 4));
    caras.push_back(Cara(7, 5, 4));
    caras.push_back(Cara(0, 4, 1));
    caras.push_back(Cara(1, 4, 5));
    caras.push_back(Cara(2, 6, 4));
    caras.push_back(Cara(0, 2, 4));
}





