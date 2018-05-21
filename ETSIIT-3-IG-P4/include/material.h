#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <vector>

using vecf = std::vector<GLfloat>;

class Material {
private:
    static int N_MATS;
    const int ID = 0;

    GLfloat cafm[4]; // color ambiental deL material
    GLfloat cdfm[4]; // color ambiental deL material
    GLfloat csfm[4]; // color ambiental deL material
    GLfloat exponente;
   
    void setColorAmbiental(const GLfloat *color);

    void setColorDifusa(const GLfloat *color);

    void setColorEspecular(const GLfloat *color);

    void setShine(const float v);
public:

    Material(const GLfloat *caf, const GLfloat *cdf, const GLfloat *csf, const GLfloat v) ;

    void apply();
};



#endif
