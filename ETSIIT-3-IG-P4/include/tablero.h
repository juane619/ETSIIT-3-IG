#ifndef _TABLERO_H
#define _TABLERO_H

#include <vector>

#include "objeto3d.h"
#include "cubo.h"

#include "CImg.h"
using namespace cimg_library;

class Tablero : public Objeto3D {
private:
    float _size_casilla;
    unsigned _divisiones;

    bool enabled_tex = false;
    GLuint _textura_id;
    std::vector<float> _texturas;

    float _desp_izq = 0.0;
    float _desp_der = 1.0;


public:
    Tablero(float size_casilla, unsigned divisiones);

    void draw(ModeDraw mode);
    void prepara_textura();

    void onOffTex() {
        enabled_tex = enabled_tex ? false : true;
    }

    void liberaTextura() {
        glDeleteTextures(1, &_textura_id);
    }

    bool isEnabledTex() {
        return enabled_tex;
    }

    void giro90() ;

    void giro180() ;

    void giro270() ;

    void giro0() ;

    void despIzq() ;
};
#endif
