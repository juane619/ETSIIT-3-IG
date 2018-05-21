#ifndef _PUNTO3D_H
#define _PUNTO3D_H

#include <iostream>

class Punto3D {
private:
    float x, y, z;
public:
    Punto3D();
    Punto3D(float x, float y, float z);

    Punto3D& operator=(const Punto3D &otherPoint);

    void setX(float x_p) {
        this->x = x_p;
    }

    void setY(float y_p) {
        this->y = y_p;
    }

    void setZ(float z_p) {
        this->z = z_p;
    }

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    float getZ() const {
        return z;
    }

    void imprimir() {
        std::cout << x << " " << y << " " << z << std::endl;
    }
};
#endif
