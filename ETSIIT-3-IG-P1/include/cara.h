#ifndef _CARA_H
#define _CARA_H

class Cara {
private:
    unsigned int x,y,z;
public:
    Cara();
    Cara(unsigned int x, unsigned int y, unsigned int z);
    
    Cara& operator=(const Cara &otherFace);
    void imprimir();
};
#endif
