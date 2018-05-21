#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "model_jer.h"

//CLASE BRAZO

Brazo::Brazo() {
    cazo = new Ply("ply_girat/cazo.ply");
    rot_cazo = 0.0;
    brazo_cazo = new Ply("ply_girat/brazo_cazo.ply");
    rot_brazo_cazo = 0.0;
    brazo_nocazo = new Ply("ply_girat/brazo_nocazo.ply");
    rot_brazo_completo = 0.0;
    speed_pistones = 0.4;

    //material negro
    const GLfloat cafm1[4] = {0., 0., 0., 1.0}; // color ambiental del material
    const GLfloat cdfm1[4] = {0., 0., 0.0, 1.0}; // color difuso del material
    const GLfloat csfm1[4] = {0.35, 0.35, 0.35, 1.0}; // color especular del material
    const GLfloat exponente1 = 24.0;
    mat1 = new Material(cafm1, cdfm1, csfm1, exponente1);

    //material gold
    const GLfloat cafm2[4] = {1., 0.70, 0., 1.0}; // color ambiental del material
    const GLfloat cdfm2[4] = {0.25, 0.21, 0.0, 1.0}; // color difuso del material
    const GLfloat csfm2[4] = {0.2, 0.2, 0.2}; // color especular del material
    const GLfloat exponente2 = 24.0;
    mat2 = new Material(cafm2, cdfm2, csfm2, exponente2);
}

void Brazo::draw(ModeDraw mode) {
    //brazo completo
    glPushMatrix();

    //brazo_nocazo+brazo_cazo
    glPushMatrix();
    mat2->apply();
    glRotatef(rot_brazo_completo, 0, 0, 1);
    glTranslatef(-0.11, -6.610, 0);

    //brazo_nocazo
    glPushMatrix();
    //glPushMatrix();
    //glPopMatrix();
    brazo_nocazo->draw(mode);
    glPopMatrix();
    //fin brazo_nocazo

    //brazo_concazo
    glPushMatrix();

    glRotatef(rot_brazo_cazo, 0, 0, 1);
    glRotatef(150, 0, 0, 1);
    glTranslatef(0.14, -3.7, 0);

    //solo_brazo_cazo
    glPushMatrix();
    brazo_cazo->draw(mode);
    glPopMatrix();
    //fin solo_brazo_cazo

    //cazo
    mat1->apply();
    glPushMatrix();
    glRotatef(rot_cazo, 0, 0, 1);
    glRotatef(150, 0, 0, 1);
    cazo->draw(mode);
    glPopMatrix();
    //fin cazo

    glPopMatrix();
    //fin brazo_concazo

    glPopMatrix();
    //fin brazo_nocazo+brazo_cazo

    glPopMatrix();
    //brazo_completo

}

//FIN DEFINICIONES CLASE BRAZO

//DEFINICIONES  CLASE BODY

Body::Body() {
    body = new Ply("ply_girat/body.ply");
    cabina = new Ply("ply_girat/cabin.ply");

    //material negro
    const GLfloat cafm1[4] = {0., 0., 0., 1.0}; // color ambiental del material
    const GLfloat cdfm1[4] = {0., 0., 0.0, 1.0}; // color difuso del material
    const GLfloat csfm1[4] = {0.35, 0.35, 0.35, 1.0}; // color especular del material
    const GLfloat exponente1 = 24.0;
    mat1 = new Material(cafm1, cdfm1, csfm1, exponente1);

    //material gold
    const GLfloat cafm2[4] = {1., 0.70, 0., 1.0}; // color ambiental del material
    const GLfloat cdfm2[4] = {0.25, 0.21, 0.0, 1.0}; // color difuso del material
    const GLfloat csfm2[4] = {0.2, 0.2, 0.2}; // color especular del material
    const GLfloat exponente2 = 24.0;
    mat2 = new Material(cafm2, cdfm2, csfm2, exponente2);
}

void Body::draw(ModeDraw mode) {
    glPushMatrix();

    // body
    mat2->apply();
    body->draw(mode);
    //fin body

    //cabina
    mat1->apply();
    cabina->draw(mode);
    //fin cabina

    glPopMatrix();
}
//FIN DEFINICIONES  CLASE BODY

//DEFINICIONES CLASE BASERUEDAS

BaseRuedas::BaseRuedas() {
    base = new Ply("ply_girat/base.ply");
    eje_base = new Ply("ply_girat/eje_giro.ply");
    rueda = new Ply("ply_girat/rueda.ply");
    giro_rueda = 0.0;
    speed_ruedas = 4.0;

    //material negro
    const GLfloat cafm1[4] = {0., 0., 0., 1.0}; // color ambiental del material
    const GLfloat cdfm1[4] = {0., 0., 0.0, 1.0}; // color difuso del material
    const GLfloat csfm1[4] = {0.35, 0.35, 0.35, 1.0}; // color especular del material
    const GLfloat exponente1 = 24.0;
    mat1 = new Material(cafm1, cdfm1, csfm1, exponente1);
}

void BaseRuedas::draw(ModeDraw mode) {
    glPushMatrix();
    mat1->apply();
    //BASE SIN RUEDAS
    glPushMatrix();
    base->draw(mode);
    eje_base->draw(mode);
    glPopMatrix();
    //FIN BASE SIN RUEDAS

    //EJE1
    glPushMatrix();
    glTranslatef(3.67, 0, 0);
    //RUEDA1
    glPushMatrix();
    glTranslatef(-1.8, -1.17, 2.18);
    glRotatef(giro_rueda, 0, 0, 1);
    glRotatef(-90, 0, 1, 0);
    glScalef(0.65, 0.65, 0.65);
    rueda->draw(mode);
    glPopMatrix();
    //FIN RUEDA1

    //RUEDA2
    glPushMatrix();
    glTranslatef(-1.8, -1.17, -2.18);
    glRotatef(giro_rueda, 0, 0, 1);
    glRotatef(90, 0, 1, 0);
    glScalef(0.65, 0.65, 0.65);
    rueda->draw(mode);
    glPopMatrix();
    //FIN RUEDA2

    glPopMatrix();
    //FIN EJE1

    //EJE2
    glPushMatrix();

    //RUEDA1
    glPushMatrix();
    glTranslatef(-1.8, -1.17, 2.18);
    glRotatef(giro_rueda, 0, 0, 1);
    glRotatef(-90, 0, 1, 0);
    glScalef(0.65, 0.65, 0.65);
    rueda->draw(mode);
    glPopMatrix();
    //FIN RUEDA1

    //RUEDA2
    glPushMatrix();
    glTranslatef(-1.8, -1.17, -2.18);
    glRotatef(giro_rueda, 0, 0, 1);
    glRotatef(90, 0, 1, 0);
    glScalef(0.65, 0.65, 0.65);
    rueda->draw(mode);
    glPopMatrix();
    //FIN RUEDA2

    glPopMatrix();
    //FIN EJE2

    glPopMatrix();
}
//FIN DEFINICIONES CLASE BASERUEDAS

//DEFINICIONES CLASE MODELO JERARQUICO COMPLETO

Jer::Jer() {
    //BRAZO
    brazo = new Brazo();

    //BODY
    body = new Body();
    giro_body = 0.0;
    speed_giro_body = 1.0;

    //BASERUEDAS
    base_ruedas = new BaseRuedas();

    //movimiento del modelo entero
    movimiento = 0.0;
    speed_movimiento = 0.015;


    //luz_cabeza = new Luz(caf1, cdf1, csf1, dirf);

    //luz_cabeza->setLight();
    //glPushMatrix();
    //glLoadIdentity();

    //glPopMatrix();
}

void Jer::draw(ModeDraw mode) {
    glPushMatrix();
    //movimiento del modelo entero
    glTranslatef(movimiento, 0, 0);

    //BASE RUEDAS
    glPushMatrix();
    base_ruedas->draw(mode);
    glPopMatrix();
    //FIN BASE RUEDAS

    //CABINA+BRAZO
    glPushMatrix();
    glRotatef(giro_body, 0, 1, 0);

    //BRAZO
    glPushMatrix();

    glRotatef(-130, 0, 0, 1);
    brazo->draw(mode);
    
    glPopMatrix();
    //FIN BRAZO

    //CABINABODY
    glPushMatrix();

    body->draw(mode);
    glPopMatrix();
    //FIN CABINABODY
    
    
    glPopMatrix();
    //FIN CABINA+BRAZO

    //const GLfloat caf1[4] = {0.4, 0.4, 0.4, 1.0}; // color ambiental de la fuente
    const GLfloat cdf1[4] = {0.4, 0.4, 0.4, 1.0}; // color difuso de la fuente
    const GLfloat csf1[4] = {0.4, 0.4, 0.4, 1.0}; // color especular de la fuente
    const GLfloat dirf[4] = {0., 10., 1.0, 1.0}; //luces direccionales (a una direccion)
    //glLightfv(GL_LIGHT0 + 3, GL_AMBIENT, caf1);
    glLightfv(GL_LIGHT0 + 3, GL_DIFFUSE, cdf1);
    glLightfv(GL_LIGHT0 + 3, GL_SPECULAR, csf1);
    glLightfv(GL_LIGHT0 + 3, GL_POSITION, dirf);
    glEnable(GL_LIGHT0 + 3);
    glPopMatrix();


}

void Jer::animar() {
    if (!fin_animacion) {
        if (!tierra_cogida) {
            if (movimiento >= -5.25)
                avanzar();
            else if (brazo->getRotBrazoCazo() >= -100.0)
                brazo->abrirBrazoCazo();
            else if (brazo->getRotBrazoCompleto() <= 20.0)
                brazo->bajarBrazoCompleto();
            else if (brazo->getRotCazo() >= -110.0)
                brazo->abrirCazo();
            else if (brazo->getRotBrazoCompleto() <= 30.0)
                brazo->bajarBrazoCompleto();
            else
                tierra_cogida = true;
        } else if (!tierra_subida) {
            if (brazo->getRotCazo() <= 0.0)
                brazo->cerrarCazo();
            else if (brazo->getRotBrazoCompleto() >= 20.0)
                brazo->subirBrazoCompleto();
            else if (brazo->getRotBrazoCazo() <= -50.0)
                brazo->cerrarBrazoCazo();
            else if (brazo->getRotBrazoCompleto() >= -5.0)
                brazo->subirBrazoCompleto();
            else if (brazo->getRotBrazoCazo() <= -30.0)
                brazo->cerrarBrazoCazo();
            else
                tierra_subida = true;
        } else {
            if (getGiroBody() <= 190.0)
                girarIzquierda();
            else if (movimiento <= 4.05)
                retroceder();
            else if (brazo->getRotBrazoCazo() >= -80.0)
                brazo->abrirBrazoCazo();
            else if (brazo->getRotCazo() >= -180.0)
                brazo->abrirCazo();
            else
                fin_animacion = true;
        }
    }
}

//FIN DEFINICIONES CLASE MODELO JERARQUICO COMPLETO
