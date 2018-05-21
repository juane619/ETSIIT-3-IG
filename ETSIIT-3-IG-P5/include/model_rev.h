#ifndef _MODELREV_H
#define _MODELREV_H

#include "objeto3d.h"

class Rev : public Objeto3D {
private:
    bool tiene_tapa_inferior = false, tiene_tapa_superior = false;
    bool tapas_pintadas;
    unsigned lados_long;
    unsigned n_ver_in;

    void generarRevolucion();
    void detectarTapas();
    void comprobarOrden();
public:
    Rev(const std::string &filename_p, int lad_long_p);
    Rev(const std::vector<Punto3D> &vec_p, int lad_long_p);

    void pintarTapas();
    void quitarTapas();

    void addLine();
    void deleteLine();
};
#endif
