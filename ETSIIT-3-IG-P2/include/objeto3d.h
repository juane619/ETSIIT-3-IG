#ifndef _OBJETO3D_H
#define _OBJETO3D_H

#include <vector>
#include <string>

#include <cmath>
#include "punto3d.h"
#include "cara.h"
#include "file_ply_stl.h"

enum ModeDraw {
    POINTS, LINES, SOLID, CHESS, TODO
};

enum ModePolygon {
    CUBE, TETRA, PYRAMID, PLY, REV, BAR
};

enum Colores {
    RED, GREEN, BLUE, BLACK, WHITE
};

const float PI = 3.14159265;
const float EPSILON = 0.0001;

#define Iguales(a,b) ((fabs(a-b)) < EPSILON)

class Objeto3D {
protected:

    std::vector<Punto3D> normales;
    std::vector<Punto3D> vertices;
    std::vector<Cara> caras;
    std::vector<float> color;

    float toGrades(float radians) {
        return 180 * PI / radians;
    }

    float toRadians(float degrees) {
        return degrees * PI / 180;
    }

    float module(const Punto3D &vec) {
        return sqrt(vec.getX() * vec.getX() + vec.getY() * vec.getY() + vec.getZ() * vec.getZ());
    }

    void normaliza(Punto3D &vec) {
        float len = module(vec);

        len = 1.0 / len;

        vec.setX(vec.getX() * len);
        vec.setY(vec.getY() * len);
        vec.setZ(vec.getZ() * len);
    }

    Punto3D prodVectorial(const Punto3D &vec1, const Punto3D &vec2) {
        Punto3D prod_vec;

        prod_vec.setX(vec1.getY() * vec2.getZ() - vec1.getZ() * vec2.getY());
        prod_vec.setY(vec1.getZ() * vec2.getX() - vec1.getX() * vec2.getZ());
        prod_vec.setZ(vec1.getX() * vec2.getY() - vec1.getY() * vec2.getX());

        return prod_vec;
    }

    void calcularNormales() {

        for (int i = 0; i < caras.size(); i++) {
            Punto3D normal = prodVectorial(
                    Punto3D(vertices[caras[i].getY()].getX(), vertices[caras[i].getY()].getY(), vertices[caras[i].getY()].getZ()),
                    Punto3D(vertices[caras[i].getZ()].getX(), vertices[caras[i].getZ()].getY(), vertices[caras[i].getZ()].getZ()));
            normaliza(normal);
            normales.push_back(normal);
        }

    }


public:
    Objeto3D();
    Objeto3D(const std::string &file_name_p);

    void draw(ModeDraw mode);
    std::vector<Cara> getCarasImp() const;
    std::vector<Cara> getCarasPar() const;
    void llenarColor(Colores color_p);
};
#endif
