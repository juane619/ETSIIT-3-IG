#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "piramide.h"

Piramide::Piramide(float size, float altura) {    
    vertices.push_back(Punto3D(-size, 0.0, size));
    vertices.push_back(Punto3D(size, 0.0, size));
    vertices.push_back(Punto3D(size, 0, -size));
    vertices.push_back(Punto3D(-size, 0.0, -size));
    vertices.push_back(Punto3D(0.0, altura, 0.0));

    caras.push_back(Cara(0,1,2));
    caras.push_back(Cara(0,2,3));
    caras.push_back(Cara(0,1,4));
    caras.push_back(Cara(3,0,4));
    caras.push_back(Cara(2,3,4));
    caras.push_back(Cara(1,2,4));
    
}




