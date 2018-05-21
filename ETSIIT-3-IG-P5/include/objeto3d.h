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
    CUBE, TETRA, PYRAMID, PLY, REV, BAR, JER, TAB
};

enum Colores {
    RED, GREEN, BLUE, BLACK, WHITE
};

const float PI = 3.14159265;
const float EPSILON = 0.0001;

#define Iguales(a,b) ((fabs(a-b)) < EPSILON)

class Objeto3D {
protected:

    std::vector<Punto3D> vertices;
    std::vector<Cara> caras;
    std::vector<float> color;
    std::vector<Punto3D> normales_vertices;
    
    

    float toGrades(float radians) const {
        return 180 * PI / radians;
    }

    float toRadians(float degrees) const {
        return degrees * PI / 180;
    }

    float module(const Punto3D &vec) const {
        return sqrt(vec.getX() * vec.getX() + vec.getY() * vec.getY() + vec.getZ() * vec.getZ());
    }

    void normaliza(Punto3D &vec) const;

    Punto3D prodVectorial(const Punto3D &vec1, const Punto3D &vec2) const;

    void calcularNormales();

    std::vector<Cara> getCarasImp() const;
    std::vector<Cara> getCarasPar() const;
    void llenarColor(Colores color_p);
    

public:
    Objeto3D();
    Objeto3D(const std::string &file_name_p);

    void draw(ModeDraw mode);
    
    int sizeV(){
        return vertices.size();
    }
};
#endif
