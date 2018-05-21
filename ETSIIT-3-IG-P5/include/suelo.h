#ifndef _SUELO_H
#define _SUELO_H

#include "objeto3d.h"
#include "material.h"

class Suelo : public Objeto3D {
    float _size;
    Material* mat1;
public:
    Suelo(float size);

    void draw(ModeDraw mode);

    float getSize() {
        return _size;
    }
};
#endif
