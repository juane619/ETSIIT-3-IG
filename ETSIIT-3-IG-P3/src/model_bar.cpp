#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

#include "model_bar.h"

Bar::Bar() {
    //GENERAR BARRIDO POR TRASLACION
    vertices.push_back(Punto3D(0.0, 0.0, 0.0));
    vertices.push_back(Punto3D(2.0, 4.0, 0.0));
    vertices.push_back(Punto3D(4.0, 0.0, 0.0));
    caras.push_back(Cara(0, 1, 2));
    calcularNormales();
    generarBarTras(2);

    //GENERAR BARRIDO POR REVOLUCION

    //    vertices.push_back(Punto3D(1.0, 0.0, 0.0));
    //    vertices.push_back(Punto3D(0.1, 4.0, 0.0));
    //    vertices.push_back(Punto3D(2.0, 7.0, 0.0));
    //    vertices.push_back(Punto3D(6.0, 4.0, 0.0));
    //    vertices.push_back(Punto3D(5.0, 0.0, 0.0));
    //    
    //    caras.push_back(Cara(0,1,2));
    //    caras.push_back(Cara(0,2,4));
    //    caras.push_back(Cara(2,3,4));
    //    
    //    generarBarRev(12,true);
}

Bar::Bar(const std::string &file_name_p, unsigned lad_long_p) {
    _file_ply file_ply;
    if (file_ply.open(file_name_p)) {
        file_ply.read(vertices, caras);
        caras.clear();
        std::cout << "File read correctly" << std::endl;
    } else std::cout << "File can't be opened" << std::endl;

    generarBarRev(lad_long_p,true);
}

void Bar::generarBarRev(unsigned lados_long, bool pintar_tapas) {
    float grados_rot_rad;
    unsigned n_ver = vertices.size();

    //DETECTAMOS SI EL PERFIL TIENE TAPAS PARA NO GENERAR EL PRIMER Y ULTIMO VERTICE
    bool tiene_tapa_inferior = false, tiene_tapa_superior = false;

    if Iguales(vertices[0].getX(), 0.0) {
        tiene_tapa_inferior = true;
        vertices.erase(vertices.begin());
    }
    if Iguales(vertices[n_ver - 1].getX(), 0.0) {
        vertices.erase(vertices.end() - 1);
        tiene_tapa_superior = true;
    }

    n_ver = vertices.size();
    //

    //GENERAMOS VERTICES (insertando los primer y ultimo puntos si tuviera tapas)
    float grados_rot_deg = 360 / lados_long;

    for (unsigned j = 1; j <= lados_long; j++) {
        grados_rot_rad = toRadians(grados_rot_deg * j);
        for (unsigned i = 0; i < n_ver; i++) {
            vertices.push_back(Punto3D(
                    cos(grados_rot_rad) * vertices[i].getX() + sin(grados_rot_rad) * vertices[i].getZ(),
                    vertices[i].getY(),
                    -sin(grados_rot_rad) * vertices[i].getX() + cos(grados_rot_rad) * vertices[i].getZ()
                    ));
        }
    }

    //



    //FORMAMOS CARAS

    for (unsigned j = 0; j < n_ver * lados_long; j += n_ver) {
        for (unsigned i = 0 + j; i < n_ver - 1 + j; i++) {
            caras.push_back(Cara(i + 1, i, i + n_ver));
            caras.push_back(Cara(i + n_ver, i + n_ver + 1, i + 1));
        }
    }

    //FORMAMOS TAPAS

    if (pintar_tapas) {
        if (!tiene_tapa_inferior)
            vertices.push_back(Punto3D(0, vertices[0].getY(), vertices[0].getZ()));
        if (!tiene_tapa_superior)
            vertices.push_back(Punto3D(0, vertices[n_ver - 1].getY(), vertices[n_ver - 1].getZ()));

        for (unsigned j = 0; j < n_ver * lados_long; j += n_ver) {
            caras.push_back(Cara((vertices.size() - 2), j, j + n_ver));
        }

        for (unsigned j = 0; j < n_ver * lados_long; j += n_ver) {
            caras.push_back(Cara(j + n_ver - 1, (vertices.size() - 1), n_ver + n_ver - 1 + j));
        }
    }
}

void Bar::generarBarTras(float mult) {
    unsigned n_caras = caras.size();

    for (unsigned i = 0; i < n_caras; i++) {
        Punto3D punto_x(
                vertices[caras[i].getX()].getX() + normales[i].getX() * mult,
                vertices[caras[i].getX()].getY() + normales[i].getY() * mult,
                vertices[caras[i].getX()].getZ() + normales[i].getZ() * mult);
        Punto3D punto_y(
                vertices[caras[i].getY()].getX() + normales[i].getX() * mult,
                vertices[caras[i].getY()].getY() + normales[i].getY() * mult,
                vertices[caras[i].getY()].getZ() + normales[i].getZ() * mult);
        Punto3D punto_z(
                vertices[caras[i].getZ()].getX() + normales[i].getX() * mult,
                vertices[caras[i].getZ()].getY() + normales[i].getY() * mult,
                vertices[caras[i].getZ()].getZ() + normales[i].getZ() * mult);

        vertices.push_back(punto_x);
        vertices.push_back(punto_y);
        vertices.push_back(punto_z);
        
    }
    //unsigned n_ver=vertices.size();
//        
//    for(unsigned i=0; i<n_ver; i++)
//        vertices[i].imprimir();
    
        caras.push_back(Cara(3,4,5));
        
        
//            for (unsigned int i = 0; i < n_ver - 1; i++) {
//                caras.push_back(Cara(i + 1, i, i + n_ver));
//                caras.push_back(Cara(i + n_ver, i + n_ver + 1, i + 1));
//            }

}



