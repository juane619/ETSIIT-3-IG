#ifdef _WIN32
#include <windows.h>
#endif

#include "punto3d.h"

Punto3D::Punto3D() {
}

Punto3D::Punto3D(float x_p, float y_p, float z_p) {
    x = x_p;
    y = y_p;
    z = z_p;
}

Punto3D& Punto3D::operator=(const Punto3D &otherPoint) {
    if (&otherPoint != this) {
        x = otherPoint.x;
        y = otherPoint.y;
        z = otherPoint.z;
    }
    return *this;
}

Punto3D Punto3D::operator-(const Punto3D &other_point){
    return Punto3D(x-other_point.x, y-other_point.y, z-other_point.z);
}

Punto3D& Punto3D::operator+=(const Punto3D& other_point){
    x+= other_point.x;
    y+= other_point.y;
    z+= other_point.z;
    
    return *this;
}





