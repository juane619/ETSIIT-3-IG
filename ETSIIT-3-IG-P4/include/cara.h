#ifndef _CARA_H
#define _CARA_H

#include <iostream>

class Cara {
private:
    unsigned x, y, z;
public:
    Cara();
    Cara(unsigned x, unsigned y, unsigned z);

    Cara& operator=(const Cara &otherFace);

    void setX(unsigned x) {
        this->x = x;
    }

    void setY(unsigned int y) {
        this->y = y;
    }

    void setZ(unsigned int z) {
        this->z = z;
    }

    unsigned int getX() const {
        return x;
    }

    unsigned int getY() const {
        return y;
    }

    unsigned int getZ() const {
        return z;
    }

    void imprimir() const {
        std::cout << x << " " << y << " " << z << std::endl;
    }
};
#endif
