#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "suelo.h"

Suelo::Suelo(float size_p) {
    const GLfloat cafm1[4] = {1., 1., 1., 1.0}; // color ambiental del material
    const GLfloat cdfm1[4] = {1., 1.0, 1.0, 1.0}; // color difuso del material
    const GLfloat csfm1[4] = {0.4, 0.4, 0.4, 1.0}; // color especular del material
    const GLfloat exponente1 = 24.0;
    mat1 = new Material(cafm1, cdfm1, csfm1, exponente1);

    _size = size_p;

    vertices.push_back(Punto3D(-_size, -_size, 0.0));
    vertices.push_back(Punto3D(_size, -_size, 0.0));
    vertices.push_back(Punto3D(-_size, _size, 0.0));
    vertices.push_back(Punto3D(_size, _size, 0.0));

    caras.push_back(Cara(0, 1, 2));
    caras.push_back(Cara(1, 3, 2));

    calcularNormales();


    //    for (unsigned j = 0; j < normales_vertices.size(); j++) {
    //        normales_vertices[j].imprimir();
    //    }
}

void Suelo::draw(ModeDraw mode) {
    mat1->apply();
    glPushMatrix();
    glTranslatef(0, -1.75, 0);
    glRotatef(-90, 1, 0, 0);
    Objeto3D::draw(mode);
    glPopMatrix();
}
