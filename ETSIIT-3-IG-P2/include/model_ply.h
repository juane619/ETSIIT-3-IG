#ifndef _MODELPLY_H
#define _MODELPLY_H

#include "objeto3d.h"

class Ply : public Objeto3D {
public:
    Ply(const std::string &filename_p);
};
#endif
