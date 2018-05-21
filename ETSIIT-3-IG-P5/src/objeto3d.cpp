#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "objeto3d.h"

using namespace std;

Objeto3D::Objeto3D() {
}

void Objeto3D::llenarColor(Colores color_p) {
    color.clear();
    unsigned n_ver = vertices.size();
    glEnableClientState(GL_COLOR_ARRAY);

    if (color_p == Colores::RED) {
        for (unsigned i = 0; i < n_ver; i++) {
            color.push_back(1);
            color.push_back(0);
            color.push_back(0);
        }
    } else if (color_p == Colores::GREEN) {
        for (unsigned i = 0; i < n_ver; i++) {
            color.push_back(0);
            color.push_back(1);
            color.push_back(0);
        }
    } else if (color_p == Colores::BLUE) {
        for (unsigned i = 0; i < n_ver; i++) {
            color.push_back(0);
            color.push_back(0);
            color.push_back(1);
        }
    } else if (color_p == Colores::BLACK) {
        for (unsigned i = 0; i < n_ver; i++) {
            color.push_back(0);
            color.push_back(0);
            color.push_back(0);
        }
    } else if (color_p == Colores::WHITE) {
        for (unsigned i = 0; i < n_ver; i++) {
            color.push_back(1);
            color.push_back(1);
            color.push_back(1);
        }
    }

    glColorPointer(3, GL_FLOAT, 0, &color[0]);
}

std::vector<Cara> Objeto3D::getCarasImp() const {
    std::vector<Cara> caras_imp;

    for (unsigned i = 1, j = 0; i < caras.size(); i += 2, j++)
        caras_imp.push_back(caras.at(i));

    return caras_imp;
}

std::vector<Cara> Objeto3D::getCarasPar() const {
    std::vector<Cara> caras_par;

    for (unsigned i = 0, j = 0; i < caras.size(); i += 2, j++)
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

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, &normales_vertices[0]);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);



    if (mode == ModeDraw::CHESS) {
        glPolygonMode(GL_FRONT_AND_BACK, draw_mode);
        llenarColor(Colores::RED);
        glDrawElements(GL_TRIANGLES, 3 * (caras.size() / 2), GL_UNSIGNED_INT, &getCarasImp()[0]);
        llenarColor(Colores::GREEN);
        glDrawElements(GL_TRIANGLES, 3 * (caras.size() / 2), GL_UNSIGNED_INT, &getCarasPar()[0]);
    } else if (mode != ModeDraw::TODO) {
        //llenarColor(Colores::WHITE);
        //glPointSize(2.0);
        //glDrawArrays(GL_POINTS, 0, vertices.size());
        glPolygonMode(GL_FRONT_AND_BACK, draw_mode);
        glDrawElements(GL_TRIANGLES, 3 * caras.size(), GL_UNSIGNED_INT, &caras[0]);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        llenarColor(Colores::WHITE);
        //glLineWidth(2.0);
        glDrawElements(GL_TRIANGLES, 3 * caras.size(), GL_UNSIGNED_INT, &caras[0]);

        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        llenarColor(Colores::RED);
        //glPointSize(5.0);
        glDrawElements(GL_TRIANGLES, 3 * caras.size(), GL_UNSIGNED_INT, &caras[0]);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        llenarColor(Colores::BLACK);
        glDrawElements(GL_TRIANGLES, 3 * caras.size(), GL_UNSIGNED_INT, &caras[0]);
    }

    //if (mode == TAB) {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    //}
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

//PRACTICA4

void Objeto3D::normaliza(Punto3D &vec) const {
    float len = module(vec);

    len = 1.0 / len;

    vec.setX(vec.getX() * len);
    vec.setY(vec.getY() * len);
    vec.setZ(vec.getZ() * len);
}

Punto3D Objeto3D::prodVectorial(const Punto3D &vec1, const Punto3D &vec2) const {
    Punto3D prod_vec;

    prod_vec.setX(vec1.getY() * vec2.getZ() - vec1.getZ() * vec2.getY());
    prod_vec.setY(vec1.getZ() * vec2.getX() - vec1.getX() * vec2.getZ());
    prod_vec.setZ(vec1.getX() * vec2.getY() - vec1.getY() * vec2.getX());

    return prod_vec;
}

void Objeto3D::calcularNormales() {
    std::vector<Punto3D> normales_caras;
    for (unsigned j = 0; j < vertices.size(); j++) {
        Punto3D normal_vertice(0, 0, 0);
        normales_vertices.push_back(normal_vertice);
    }
    for (unsigned i = 0; i < caras.size(); i++) {
        //De cada cara, creamos dos vectores: vec1= cara.y-cara.x, vec2= cara.z-cara.x
        Punto3D vec1 = vertices.at(caras.at(i).getY()) - vertices.at(caras.at(i).getX());
        Punto3D vec2 = vertices.at(caras.at(i).getZ()) - vertices.at(caras.at(i).getX());

        Punto3D normal_cara = prodVectorial(vec1, vec2);
        normaliza(normal_cara);
        normales_caras.push_back(normal_cara);

        normales_vertices[caras[i].getX()] += normal_cara;
        normales_vertices[caras[i].getY()] += normal_cara;
        normales_vertices[caras[i].getZ()] += normal_cara;
    }

    for (unsigned j = 0; j < normales_vertices.size(); j++) {
        normaliza(normales_vertices[j]);
    }

    //    for (unsigned j = 0; j < normales_caras.size(); j++) {
    //        normales_caras[j].imprimir();
    //    }

}
