#ifndef _CARA_H
#define _CARA_H

class Cara {
private:
    unsigned int x,y,z;
public:
    Cara();
    Cara(unsigned int x, unsigned int y, unsigned int z);
    
    Cara& operator=(const Cara &otherFace);
    void setX(unsigned int x) {
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


    void imprimir();
};
#endif
