#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include "cara.h"

Cara::Cara() {
}

Cara::Cara(unsigned int x_p, unsigned int y_p, unsigned int z_p) {
    x = x_p;
    y = y_p;
    z = z_p;
}

Cara& Cara::operator=(const Cara &otherFace) {
    if (&otherFace != this) {
        x = otherFace.x;
        y = otherFace.y;
        z = otherFace.z;
    }
    return *this;
}

void Cara::imprimir(){
    std::cout << x << " " << y << " " << z << std::endl;
}




