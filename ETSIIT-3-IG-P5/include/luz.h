#ifndef _LUZ_H
#define _LUZ_H

#include <vector>

using vecf = std::vector<GLfloat>;

enum ModeLuz {
    LUZ0, LUZ1
};

class Luz {
private:
    static int N_LUCES;

    const int ID = 0;
    float posicional = 0.0;

    GLfloat cafm[4]; // color ambiental de la fuente
    GLfloat cdfm[4]; // color difuso de la fuente
    GLfloat csfm[4]; // color especular de la fuente
    GLfloat posf[4]; //luces posicionales (bombilla)
    const float ejeZ[4] = {0.0, 0.0, 1.0, posicional};

    float grados_giro_x = 0, grados_giro_y = 0, grados_giro_z = 0;
    float velocidad = 2.5;

    //parametros
    bool encendida = false;

    //asignar colores
    void setColorAmbiental(const GLfloat *caf);

    void setColorDifusa(const GLfloat *cdf);

    void setColorEspecular(const GLfloat *csf);

public:

    Luz(const GLfloat *caf, const GLfloat *cdf, const GLfloat *csf, const GLfloat *posf);

    int getID(){return ID;}
    
    void setLight() const;

    void setDireccion(const GLfloat *posf);

    void onOff();

    void xMas();

    void xMenos();

    void yMas();

    void yMenos();

};



#endif
