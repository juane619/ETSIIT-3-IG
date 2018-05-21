#ifndef _MODELJER_H
#define _MODELJER_H

#include "model_ply.h"

//CLASE BRAZO

class Brazo {
private:
    //topes giros
    const float tope_brazo_completo_abierto = -20.0;
    const float tope_brazo_completo_cerrado = 35.0;
    const float tope_brazo_cazo_abierto = -142.0;
    const float tope_brazo_cazo_cerrado = 19.9;
    const float tope_cazo_abierto = -211.0;
    const float tope_cazo_cerrado = 24.5;

    float speed_pistones;

    Ply *cazo;
    float rot_cazo;
    Ply *brazo_cazo;
    float rot_brazo_cazo;
    Ply *brazo_nocazo;
    float rot_brazo_completo;
public:
    Brazo();

    float getRotBrazoCazo() const {
        return rot_brazo_cazo;
    }

    float getRotBrazoCompleto() const {
        return rot_brazo_completo;
    }

    float getRotCazo() const {
        return rot_cazo;
    }

    void abrirCazo() {
        if (rot_cazo >= tope_cazo_abierto)
            rot_cazo -= speed_pistones;
        std::cout << "Abrir cazo: " << rot_cazo << std::endl;
    }

    void cerrarCazo() {
        if (rot_cazo <= tope_cazo_cerrado)
            rot_cazo += speed_pistones;
        std::cout << "Cerrar cazo: " << rot_cazo << std::endl;
    }

    void abrirBrazoCazo() {
        if (rot_brazo_cazo >= tope_brazo_cazo_abierto)
            rot_brazo_cazo -= speed_pistones;
        std::cout << "Abrir brazo cazo: " << rot_brazo_cazo << std::endl;
    }

    void cerrarBrazoCazo() {
        if (rot_brazo_cazo <= tope_brazo_cazo_cerrado)
            rot_brazo_cazo += speed_pistones;
        std::cout << "Cerrar brazo cazo: " << rot_brazo_cazo << std::endl;
    }

    void subirBrazoCompleto() {
        if (rot_brazo_completo >= tope_brazo_completo_abierto)
            rot_brazo_completo -= speed_pistones;
        std::cout << "Subir brazo grande: " << rot_brazo_completo << std::endl;
    }

    void bajarBrazoCompleto() {
        if (rot_brazo_completo <= tope_brazo_completo_cerrado)
            rot_brazo_completo += speed_pistones;
        std::cout << "Bajar brazo grande: " << rot_brazo_completo << std::endl;
    }

    void aumentarSpeed() {
        speed_pistones += 0.1;
    }

    void disminuirSpeed() {
        speed_pistones -= 0.1;
    }

    void draw(ModeDraw mode);
};
//FIN CLASE BRAZO

//CLASE BODYCABINA

class Body {
private:
    Ply *body;
    Ply *cabina;

public:
    Body();

    void draw(ModeDraw mode);
};
//FIN CLASE BODYCABINA

//CLASE BASERUEDAS

class BaseRuedas {
private:
    Ply *base;
    Ply *eje_base;

    Ply *rueda;
    float giro_rueda;
    float speed_ruedas;
public:
    BaseRuedas();

    void draw(ModeDraw mode);

    void giroRuedaDerecha() {
        giro_rueda += speed_ruedas;
    }

    void giroRuedaIzquierda() {
        giro_rueda -= speed_ruedas;
    }

    void aumentarSpeed() {
        speed_ruedas += 0.34;
    }

    void disminuirSpeed() {
        speed_ruedas -= 0.34;
    }

};
//FIN CLASE BASERUEDAS

//CLASE MODELO JERARQUICO COMPLETO

class Jer {
private:
    Brazo *brazo;

    Body *body;
    float giro_body;
    float speed_giro_body;

    BaseRuedas *base_ruedas;
    float movimiento;
    float speed_movimiento;

    //ANIMACION
    bool tierra_cogida = false;
    bool tierra_subida = false;
    bool fin_animacion = false;
public:
    Jer();
    void draw(ModeDraw mode);

    void animar();

    /*METODOS INLINE*/

    float getMovimiento() const {
        return movimiento;
    }

    float getGiroBody() const {
        return giro_body;
    }

    void abrirCazo() {
        brazo->abrirCazo();
    }

    void cerrarCazo() {
        brazo->cerrarCazo();
    }

    void abrirBrazoCazo() {
        brazo->abrirBrazoCazo();
    }

    void cerrarBrazoCazo() {
        brazo->cerrarBrazoCazo();
    }

    void subirBrazoCompleto() {
        brazo->subirBrazoCompleto();
    }

    void bajarBrazoCompleto() {
        brazo->bajarBrazoCompleto();
    }

    void girarIzquierda() {
        giro_body += speed_giro_body;
        std::cout << "GIro body izquierda: " << giro_body << std::endl;
    }

    void girarDerecha() {
        giro_body -= speed_giro_body;
        std::cout << "Giro body derecha: " << giro_body << std::endl;
    }

    void avanzar() {
        base_ruedas->giroRuedaDerecha();
        movimiento -= speed_movimiento;
        std::cout << "Avanzamos Movimiento: " << movimiento << std::endl;
    }

    void retroceder() {
        base_ruedas->giroRuedaIzquierda();
        movimiento += speed_movimiento;
        std::cout << "REtrocedemos Movimiento: " << movimiento << std::endl;
    }

    void aumentarSpeedMaquina() {
        speed_movimiento += 0.005;
        base_ruedas->aumentarSpeed();
        std::cout << "Aumento velocidad movimiento: " << std::endl;
    }

    void disminuirSpeedMaquina() {
        speed_movimiento -= 0.005;
        base_ruedas->disminuirSpeed();
        std::cout << "Disminuir velocidad movimiento: " << std::endl;
    }

    void aumentarSpeedGiroBody() {
        speed_giro_body += 0.5;
        std::cout << "Aumento speed giro body: " << std::endl;
    }

    void disminuirSpeedGiroBody() {
        speed_giro_body -= 0.5;
        std::cout << "Disminuir speed giro body: " << std::endl;
    }

    void aumentarSpeedPistones() {
        brazo->aumentarSpeed();
        std::cout << "Aumentar speed pistones: " << std::endl;
    }

    void disminuirSpeedPistones() {
        brazo->disminuirSpeed();
        std::cout << "Disminuir speed pistones: " << std::endl;
    }

    /*FIN METODOS INLINE*/


};
//FIN CLASE MODELO JERARQUICO COMPLETO


#endif
