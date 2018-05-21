#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <algorithm>
#include "model_rev.h"

Rev::Rev(const std::vector<Punto3D> &vec_p, int lad_long_p) {
    vertices.clear();
    /*    
            vertices.push_back(Punto3D(0.0, -1.4, 0.0));
        vertices.push_back(Punto3D(1.0, -1.4, 0.0));
        vertices.push_back(Punto3D(1.0, -1.1, 0.0));
        vertices.push_back(Punto3D(0.5, -0.7, 0.0));
        vertices.push_back(Punto3D(0.4, -0.4, 0.0));
        vertices.push_back(Punto3D(0.4, 0.5, 0.0));
        vertices.push_back(Punto3D(0.5, 0.6, 0.0));
        vertices.push_back(Punto3D(0.3, 0.6, 0.0));
        vertices.push_back(Punto3D(0.5, 0.8, 0.0));
        vertices.push_back(Punto3D(0.55, 1.0, 0.0));
        vertices.push_back(Punto3D(0.5, 1.2, 0.0));
        vertices.push_back(Punto3D(0.3, 1.4, 0.0));
        vertices.push_back(Punto3D(0.0, 1.4, 0.0));
     */
    for (unsigned i = 0; i < vec_p.size(); i++) {
        vertices.push_back(vec_p[i]);
    }

    //comprobarOrden();
    lados_long = lad_long_p;
    detectarTapas();
    n_ver_in = vertices.size();

    generarRevolucion();
    
    calcularNormales();
}

Rev::Rev(const std::string &file_name_p, int lad_long_p) {
    vertices.clear();
    _file_ply file_ply;
    if (file_ply.open(file_name_p)) {
        file_ply.read(vertices, caras);
        caras.clear();
        std::cout << "File read correctly" << std::endl;
    } else std::cout << "File can't be opened" << std::endl;

    //comprobarOrden();
    lados_long = lad_long_p;
    detectarTapas();
    n_ver_in = vertices.size();

    generarRevolucion();
}

void Rev::detectarTapas() {
    //DETECTAMOS SI EL PERFIL TIENE TAPAS PARA NO MULTIGENERAR EL PRIMER Y ULTIMO VERTICES
    if Iguales(vertices[0].getX(), 0.0) {
        tiene_tapa_inferior = true;
        vertices.erase(vertices.begin());
    }
    if Iguales(vertices[vertices.size() - 1].getX(), 0.0) {
        vertices.erase(vertices.end() - 1);
        tiene_tapa_superior = true;
    }
    tapas_pintadas = false;
}

void Rev::generarRevolucion() {
    float grados_rot_rad;

    //GENERAMOS VERTICES
    float grados_rot_deg = 360.0 / lados_long;

    for (unsigned j = 1; j <= lados_long; j++) {
        grados_rot_rad = toRadians(grados_rot_deg * j);
        for (unsigned i = 0; i < n_ver_in; i++) {
            vertices.push_back(Punto3D(
                    cos(grados_rot_rad) * vertices[i].getX() + sin(grados_rot_rad) * vertices[i].getZ(),
                    vertices[i].getY(),
                    -sin(grados_rot_rad) * vertices[i].getX() + cos(grados_rot_rad) * vertices[i].getZ()
                    ));
        }
    }

    //FORMAMOS CARAS

    for (unsigned j = 0; j < n_ver_in * lados_long; j += n_ver_in) {
        for (unsigned i = 0 + j; i < n_ver_in - 1 + j; i++) {
            caras.push_back(Cara(i + 1, i, i + n_ver_in));
            caras.push_back(Cara(i + n_ver_in + 1, i + 1, i + n_ver_in));
        }
    }

    //FORMAMOS TAPAS
    if (tiene_tapa_inferior)
        vertices.push_back(Punto3D(0, vertices[0].getY(), 0));


    if (tiene_tapa_superior)
        vertices.push_back(Punto3D(0, vertices[n_ver_in - 1].getY(), 0));
    
    pintarTapas();
}

void Rev::comprobarOrden() {
    bool encontrado = false;
    std::vector<Punto3D> v_aux;
    for (unsigned i = 1; i < vertices.size() - 1 && !encontrado; i++) {
        if (vertices[i].getY() > vertices[i + 1].getY()) {
            std::reverse(vertices.begin(), vertices.end());
            encontrado = true;
        }
    }
}

void Rev::pintarTapas() {
    if (!tapas_pintadas) {

        if (!tiene_tapa_superior)
            vertices.push_back(Punto3D(0, vertices[0].getY(), 0));
        if (!tiene_tapa_inferior)
            vertices.push_back(Punto3D(0, vertices[n_ver_in - 1].getY(), 0));

        for (unsigned j = 0; j < n_ver_in * lados_long; j += n_ver_in) {
            caras.push_back(Cara(j + n_ver_in, j, (vertices.size() - 2)));
        }

        for (unsigned j = 0; j < n_ver_in * lados_long; j += n_ver_in) {
            caras.push_back(Cara(n_ver_in + n_ver_in - 1 + j, (vertices.size() - 1), j + n_ver_in - 1));
        }

        tapas_pintadas = true;
    }
}

void Rev::quitarTapas() {
    if (tapas_pintadas) {
        caras.erase(caras.end()-(2 * lados_long), caras.end());
        tapas_pintadas = false;
    }
}

void Rev::addLine() {
    bool tapas = tapas_pintadas;
    lados_long++;
    vertices.erase(vertices.begin() + n_ver_in, vertices.end());
    caras.clear();
    detectarTapas();
    generarRevolucion();
    if (tapas) {
        pintarTapas();
    }
}

void Rev::deleteLine() {
    bool tapas = tapas_pintadas;
    lados_long--;
    vertices.erase(vertices.begin() + n_ver_in, vertices.end());
    caras.clear();
    detectarTapas();
    generarRevolucion();
    if (tapas) {
        pintarTapas();
    }
}




