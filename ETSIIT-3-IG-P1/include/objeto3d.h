#ifndef _OBJETO3D_H
#define _OBJETO3D_H

#include <vector>
#include "punto3d.h"
#include "cara.h"

enum ModeDraw{POINTS, LINES, SOLID, CHESS, TODO};
enum ModePolygon{CUBE, TETRA, PIRAMIDE};
enum Colores{RED, GREEN, BLUE, BLACK, WHITE};

class Objeto3D {
protected:
    std::vector<Punto3D> vertices;
    std::vector<Cara> caras;
    std::vector<float> color;
public:
    
    Objeto3D();
    void draw(ModeDraw mode);
    std::vector<Cara> getCarasImp() const;
    std::vector<Cara> getCarasPar() const;
    void llenarColor(Colores color_p);
};
#endif
