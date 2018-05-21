#ifndef _CUBO_H
#define _CUBO_H

#include "objeto3d.h"

class Cubo : public Objeto3D {
    float _size;
public:
    Cubo(float size);
    
    float getSize(){
        return _size;
    }
};
#endif
