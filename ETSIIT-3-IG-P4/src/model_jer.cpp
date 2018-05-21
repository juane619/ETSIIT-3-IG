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
    
}

void Brazo::draw(ModeDraw mode) {
    //brazo completo
    glPushMatrix();

    //brazo_nocazo+brazo_cazo
    glPushMatrix();
    glRotatef(rot_brazo_completo, 0, 0, 1);
    glTranslatef(-0.11, -6.610, 0);

    //brazo_nocazo
    glPushMatrix();
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
}

void Body::draw(ModeDraw mode) {
    glPushMatrix();

    // body
    body->draw(mode);
    //fin body

    //cabina
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
}

void BaseRuedas::draw(ModeDraw mode) {
    glPushMatrix();

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


