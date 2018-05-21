#ifndef _MODELBAR_H
#define _MODELBAR_H

#include "objeto3d.h"

class Bar : public Objeto3D {
private:
    void generarBarTras(float mult);
    void generarBarRev(unsigned lados_long, bool pintar_tapas);
public:
    Bar(const std::string &filename_p, unsigned lad_long_p);
    Bar();
};
#endif
