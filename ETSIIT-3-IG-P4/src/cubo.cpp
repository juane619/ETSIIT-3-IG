#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "cubo.h"

Cubo::Cubo(float size_p) {  
    _size= size_p;
    
    vertices.push_back(Punto3D(0.0, 0.0, _size));
    vertices.push_back(Punto3D(_size, 0.0, _size));
    vertices.push_back(Punto3D(0.0, _size, _size));
    vertices.push_back(Punto3D(_size, _size, _size));
    vertices.push_back(Punto3D(0.0, 0.0, 0.0));
    vertices.push_back(Punto3D(_size, 0.0, 0.0));
    vertices.push_back(Punto3D(0.0, _size, 0.0));
    vertices.push_back(Punto3D(_size, _size, 0.0));

    caras.push_back(Cara(0, 1, 3));
    caras.push_back(Cara(0, 3, 2));
    caras.push_back(Cara(1, 5, 3));
    caras.push_back(Cara(3, 5, 7));
    caras.push_back(Cara(3, 7, 6));
    caras.push_back(Cara(3, 6, 2));
    caras.push_back(Cara(2, 6, 4));
    caras.push_back(Cara(2, 4, 0));
    caras.push_back(Cara(0, 4, 1));
    caras.push_back(Cara(1, 4, 5));
    caras.push_back(Cara(7, 5, 4));
    caras.push_back(Cara(7, 4, 6));
    
    calcularNormales();
    
//    for (unsigned j = 0; j < normales_vertices.size(); j++) {
//        normales_vertices[j].imprimir();
//    }
}





