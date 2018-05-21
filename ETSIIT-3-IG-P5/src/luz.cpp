#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

#include "luz.h"

int Luz::N_LUCES = 0;

//METODOS PRIVADOS

void Luz::setColorAmbiental(const GLfloat* color) {
    cafm[0] = color[0];
    cafm[1] = color[1];
    cafm[2] = color[2];
    cafm[3] = color[3];
}

void Luz::setColorDifusa(const GLfloat* color) {
    cdfm[0] = color[0];
    cdfm[1] = color[1];
    cdfm[2] = color[2];
    cdfm[3] = color[3];
}

void Luz::setColorEspecular(const GLfloat* color) {
    csfm[0] = color[0];
    csfm[1] = color[1];
    csfm[2] = color[2];
    csfm[3] = color[3];
}

///FIN METODOS PRIVADOS


//METODOS PUBLICOS

//CONSTRUCTORES

Luz::Luz(const GLfloat *caf, const GLfloat *cdf, const GLfloat *csf, const GLfloat *posf_p) : ID(N_LUCES) {
    setColorAmbiental(caf);
    setColorDifusa(cdf);
    setColorEspecular(csf);
    setDireccion(posf_p);
    glPushMatrix();
    glLightfv(GL_LIGHT0 + ID, GL_POSITION, posf);
    glPopMatrix();
    N_LUCES++;
}

//FIN CONSTRUCTORES

void Luz::setDireccion(const GLfloat *posf_p) {
    posf[0] = posf_p[0];
    posf[1] = posf_p[1];
    posf[2] = posf_p[2];
    posf[3] = posf_p[3];
    glLightfv(GL_LIGHT0+ID, GL_POSITION, posf);
}

void Luz::setLight() const {
    //glLightfv(GL_LIGHT0 + ID, GL_AMBIENT, cafm);
    glLightfv(GL_LIGHT0 + ID, GL_DIFFUSE, cdfm);
    glLightfv(GL_LIGHT0 + ID, GL_SPECULAR, csfm);
    //glLightfv(GL_LIGHT0+ID, GL_POSITION, posf);
}

void Luz::onOff() {
    if (!encendida) {
        glEnable(GL_LIGHT0 + ID); //activa la fuente de luz
        encendida = true;
        std::cout << "Encendiendo luz " << GL_LIGHT0 + ID << std::endl;
    } else {
        glDisable(GL_LIGHT0 + ID); //activa la fuente de luz
        encendida = false;
        std::cout << "Apagando luz " << GL_LIGHT0 + ID << std::endl;
    }
}

void Luz::xMas() {
    grados_giro_x += velocidad;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    if (!posicional) {
        glLoadIdentity(); // hacer M = Identidad
    }
    //glMultMatrix(A);  // A podría ser Ide, V o VN

    glRotatef(grados_giro_x, 1.0, 0.0, 0.0);

    glLightfv(GL_LIGHT0 + ID, GL_POSITION, ejeZ); // luz paralela eje Z+
    glPopMatrix();
}

void Luz::xMenos() {
    grados_giro_x -= velocidad;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    if (!posicional)
        glLoadIdentity(); // hacer M = Identidad
    // hacer M = Identidad
    //glMultMatrix(A);
    // A podría ser Ide, V o VN
    // rotación a grados en torno a eje Y
    glRotatef(grados_giro_x, 1.0, 0.0, 0.0);
    // rotación b grados en torno al eje X
    //glRotatef(b, -1.0, 0.0, 0.0);
    // luz paralela eje Z+
    glLightfv(GL_LIGHT0 + ID, GL_POSITION, ejeZ);
    glPopMatrix();
}

void Luz::yMas() {
    grados_giro_y += velocidad;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    if (!posicional)
        glLoadIdentity(); // hacer M = Identidad
    // hacer M = Identidad
    //glMultMatrix(A);
    // A podría ser Ide, V o VN
    // rotación a grados en torno a eje Y
    glRotatef(grados_giro_y, 0.0, 1.0, 0.0);
    // rotación b grados en torno al eje X
    //glRotatef(b, -1.0, 0.0, 0.0);
    // luz paralela eje Z+
    glLightfv(GL_LIGHT0 + ID, GL_POSITION, ejeZ);
    glPopMatrix();
    //posf[1] += velocidad;
    //glLightfv(GL_LIGHT0 + ID, GL_POSITION, posf);
}

void Luz::yMenos() {
    grados_giro_y -= velocidad;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    if (!posicional)
        glLoadIdentity(); // hacer M = Identidad
    // hacer M = Identidad
    //glMultMatrix(A);
    // A podría ser Ide, V o VN
    // rotación a grados en torno a eje Y
    glRotatef(grados_giro_y, 0.0, 1.0, 0.0);
    // rotación b grados en torno al eje X
    //glRotatef(b, -1.0, 0.0, 0.0);
    // luz paralela eje Z+
    glLightfv(GL_LIGHT0 + ID, GL_POSITION, ejeZ);
    glPopMatrix();
    //posf[1] += velocidad;
    //glLightfv(GL_LIGHT0 + ID, GL_POSITION, posf);
}


//FIN METODOS PUBLICOS
