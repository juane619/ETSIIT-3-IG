#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "tetraedro.h"

Tetraedro::Tetraedro(float size) {
    vertices.push_back(Punto3D(0.0, 0.0, size));
    vertices.push_back(Punto3D(size, 0.0, 0.0));
    vertices.push_back(Punto3D(0.0, 0.0, 0.0));
    vertices.push_back(Punto3D(0.0, size, 0.0));

    caras.push_back(Cara(0, 1, 2));
    caras.push_back(Cara(0, 2, 3));
    caras.push_back(Cara(2, 1, 3));
    caras.push_back(Cara(0, 1, 3));
    
    calcularNormales();
}

