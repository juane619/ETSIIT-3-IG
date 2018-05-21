#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "objeto3d.h"

Objeto3D::Objeto3D() {
}

void Objeto3D::llenarColor(Colores color_p) {
    color.clear();
    int n_ver= vertices.size();
    glEnableClientState(GL_COLOR_ARRAY);

    if (color_p == Colores::RED) {
        for (int i = 0; i < n_ver; i++) {
            color.push_back(1);
            color.push_back(0);
            color.push_back(0);
        }
    } else if (color_p == Colores::GREEN) {
        for (int i = 0; i < n_ver; i++) {
            color.push_back(0);
            color.push_back(1);
            color.push_back(0);
        }
    } else if (color_p == Colores::BLUE) {
        for (int i = 0; i < n_ver; i++) {
            color.push_back(0);
            color.push_back(0);
            color.push_back(1);
        }
    } else if (color_p == Colores::BLACK) {
        for (int i = 0; i < n_ver; i++) {
            color.push_back(0);
            color.push_back(0);
            color.push_back(0);
        }
    } else if (color_p == Colores::WHITE) {
        for (int i = 0; i < n_ver; i++) {
            color.push_back(1);
            color.push_back(1);
            color.push_back(1);
        }
    }

    glColorPointer(3, GL_FLOAT, 0, &color[0]);
}

std::vector<Cara> Objeto3D::getCarasImp() const {
    std::vector<Cara> caras_imp;

    for (int i = 1, j = 0; i < caras.size(); i += 2, j++)
        caras_imp.push_back(caras.at(i));

    return caras_imp;
}

std::vector<Cara> Objeto3D::getCarasPar() const {
    std::vector<Cara> caras_par;

    for (int i = 0, j = 0; i < caras.size(); i += 2, j++)
        caras_par.push_back(caras.at(i));

    return caras_par;
}

void Objeto3D::draw(ModeDraw mode) {
    GLenum draw_mode;

    switch (mode) {
        case ModeDraw::POINTS:
            draw_mode = GL_POINT;
            glPointSize(5.0);
            break;
        case ModeDraw::LINES:
            draw_mode = GL_LINE;
            break;
        default:
            draw_mode = GL_FILL;
            break;
    }


    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);

    if (mode == ModeDraw::CHESS) {

        glPolygonMode(GL_FRONT_AND_BACK, draw_mode);
        llenarColor(Colores::RED);
        glDrawElements(GL_TRIANGLES, 3 * (caras.size() / 2), GL_UNSIGNED_INT, &getCarasImp()[0]);
        llenarColor(Colores::GREEN);
        glDrawElements(GL_TRIANGLES, 3 * (caras.size() / 2), GL_UNSIGNED_INT, &getCarasPar()[0]);
    } else if (mode != ModeDraw::TODO) {
        llenarColor(Colores::WHITE);
        glPolygonMode(GL_FRONT_AND_BACK, draw_mode);
        glDrawElements(GL_TRIANGLES, 3 * caras.size(), GL_UNSIGNED_INT, &caras[0]);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        llenarColor(Colores::WHITE);
        glLineWidth(2.0);
        glDrawElements(GL_TRIANGLES, 3 * caras.size(), GL_UNSIGNED_INT, &caras[0]);

        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        llenarColor(Colores::RED);
        glPointSize(5.0);
        glDrawElements(GL_TRIANGLES, 3 * caras.size(), GL_UNSIGNED_INT, &caras[0]);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        llenarColor(Colores::BLACK);
        glDrawElements(GL_TRIANGLES, 3 * caras.size(), GL_UNSIGNED_INT, &caras[0]);
    }

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}