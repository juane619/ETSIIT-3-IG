#ifndef _PUNTO3D_H
#define _PUNTO3D_H

class Punto3D {
private:
    float x,y,z;
public:
    Punto3D();
    Punto3D(float x, float y, float z);
    
    Punto3D& operator=(const Punto3D &otherPoint);
    void imprimir();
};
#endif
