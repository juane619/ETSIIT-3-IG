#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "tablero.h"

#include <iostream>

using namespace std;

Tablero::Tablero(float size_casilla, unsigned divisiones) {
    _divisiones = divisiones;
    _size_casilla = size_casilla;

    //vertices
    for (unsigned i = 0; i <= _divisiones * _size_casilla; i += _size_casilla) {
        for (unsigned j = 0; j <= _divisiones * _size_casilla; j += _size_casilla) {
            vertices.push_back(Punto3D(1.0 * j, 1.0 * i, 0.0));
        }
    }
    //    vertices.push_back(Punto3D(0, 0, 0));
    //    vertices.push_back(Punto3D(10.0, 0, 0));
    //    vertices.push_back(Punto3D(10.0, 5.0, 0));
    //    vertices.push_back(Punto3D(0, 5.0, 0));

    //caras

    for (unsigned i = 0; i < _divisiones * (_divisiones + 1); i += _divisiones + 1) {
        for (unsigned j = 0; j < _divisiones; j++) {
            caras.push_back(Cara(j + i, j + i + 1, j + i + _divisiones + 2));
            caras.push_back(Cara(j + i + _divisiones + 2, j + i + _divisiones + 1, j + i));
        }
    }
    //    caras.push_back(Cara(0, 1, 2));
    //    caras.push_back(Cara(2, 3, 0));
    //std::cout << _divisiones << " " << _size_casilla<<std::endl;
    //coordenadas textura
    float avance=1.0/_divisiones;
    for (float t = 1.0; t >= 0; t-=avance) {
        for (float s = 0; s <= 1; s+=avance) {
            _texturas.push_back(s);
            _texturas.push_back(t);

            //std::cout << j << " " << i << std::endl;
        }
    }
    //    _texturas.push_back(0.0);
    //    _texturas.push_back(1.0);
    //    _texturas.push_back(1.0);
    //    _texturas.push_back(1.0);
    //    _texturas.push_back(1.0);
    //    _texturas.push_back(0.0);
    //    _texturas.push_back(0.0);
    //    _texturas.push_back(0.0);

    for (unsigned j = 0; j < _texturas.size(); j += 2) {
        std::cout << _texturas[j] << ", " << _texturas[j + 1] << std::endl;
    }

    calcularNormales();

    //    for (unsigned j = 0; j < normales_vertices.size(); j++) {
    //        normales_vertices[j].imprimir();
    //    }
}

void Tablero::draw(ModeDraw mode) {
    if (enabled_tex)
        glEnable(GL_TEXTURE_2D);
    else
        glDisable(GL_TEXTURE_2D);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY_EXT);
    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textura_id);
    glTexCoordPointer(2, GL_FLOAT, 0, &_texturas[0]);
    //glEnable(GL_TEXTURE_GEN_S);
    //glEnable(GL_TEXTURE_GEN_T);

    Objeto3D::draw(mode);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY_EXT);
    if (enabled_tex)
        glDisable(GL_TEXTURE_2D);
}

void Tablero::prepara_textura() {
    std::vector<unsigned char> data;

    CImg<unsigned char> logo;
    logo.load("./logo.jpg");


    // empaquetamos bien los datos
    for (long y = 0; y < logo.height(); y++)
        for (long x = 0; x < logo.width(); x++) {
            unsigned char *r = logo.data(x, y, 0, 0);
            unsigned char *g = logo.data(x, y, 0, 1);
            unsigned char *b = logo.data(x, y, 0, 2);
            data.push_back(*r);
            data.push_back(*g);
            data.push_back(*b);
        }


    glGenTextures(1, &_textura_id);
    glBindTexture(GL_TEXTURE_2D, _textura_id);

    glActiveTexture(GL_TEXTURE0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // TRASFIERE LOS DATOS A GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, logo.width(), logo.height(),
            0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
}

void Tablero::giro90() {
        _texturas.clear();

        float avance = 1.0 / _divisiones;
        for (float t = 1.0; t >= 0; t -= avance) {
            for (float s = 1.0; s >= 0.0; s -= avance) {
                _texturas.push_back(s);
                _texturas.push_back(t);

                //std::cout << j << " " << i << std::endl;
            }
        }
    }

    void Tablero::giro180() {
        _texturas.clear();

        float avance = 1.0 / _divisiones;
        for (float s = 1.0; s >= 0; s -= avance) {
            for (float t = 1.0; t >= 0.0; t -= avance) {
                _texturas.push_back(s);
                _texturas.push_back(t);

                //std::cout << j << " " << i << std::endl;
            }
        }
    }

    void Tablero::giro270() {
        _texturas.clear();

        float avance = 1.0 / _divisiones;
        for (float s = 0.0; s <= 1.0; s += avance) {
            for (float t = 1.0; t >= 0.0; t -= avance) {
                _texturas.push_back(s);
                _texturas.push_back(t);

                //std::cout << j << " " << i << std::endl;
            }
        }
    }

    void Tablero::giro0() {
        _texturas.clear();
        float avance = 1.0 / _divisiones;
        for (float t = 1.0; t >= 0; t -= avance) {
            for (float s = 0; s <= 1; s += avance) {
                _texturas.push_back(s);
                _texturas.push_back(t);

                //std::cout << j << " " << i << std::endl;
            }
        }
    }

    void Tablero::despIzq() {
        if (_desp_izq >= 1.0)
            _desp_izq = 0.0;
        else
            _desp_izq += 1.0 / _divisiones;
        float avance = 1.0 / _divisiones;
        float avance_s = 1.0 / (_divisiones + _desp_izq);
        _texturas.clear();
        for (float t = 1.0; t >= 0; t -= avance) {
            for (float s = _desp_izq; s <= 1 + _desp_izq; s += avance_s) {
                _texturas.push_back(s);
                _texturas.push_back(t);

                //std::cout << s << " " << t << std::endl;
            }
        }
    }




