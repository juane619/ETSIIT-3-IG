#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

#include "material.h"

int Material::N_MATS = 0;

//METODOS PRIVADOS

void Material::setColorAmbiental(const GLfloat* color) {
    cafm[0] = color[0];
    cafm[1] = color[1];
    cafm[2] = color[2];
    cafm[3] = color[3];
}

void Material::setColorDifusa(const GLfloat* color) {
    cdfm[0] = color[0];
    cdfm[1] = color[1];
    cdfm[2] = color[2];
    cdfm[3] = color[3];
}

void Material::setColorEspecular(const GLfloat* color) {
    csfm[0] = color[0];
    csfm[1] = color[1];
    csfm[2] = color[2];
    csfm[3] = color[3];
}

void Material::setShine(const float v) {
    exponente = v;
}
//FIN METODOS PRIVADOS

Material::Material(const GLfloat *caf, const GLfloat *cdf, const GLfloat *csf, const GLfloat v) : ID(N_MATS) {
    setColorAmbiental(caf);
    setColorDifusa(cdf);
    setColorEspecular(csf);
    setShine(v);
    N_MATS++;
}

void Material::apply() {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cafm);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cdfm);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, csfm);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, exponente);
}


