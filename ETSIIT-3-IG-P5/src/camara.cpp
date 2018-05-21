#ifdef _WIN32
#include <windows.h>
#endif

#include "camara.h"

Camara::Camara(GLfloat widthp, GLfloat heightp, GLfloat frontp, GLfloat backp) {
    pos_z = 4 * frontp;
    front_plane = frontp;
    back_plane = backp;
    width = widthp;
    height = heightp;
}

void Camara::changeProjection() {
    //std::cout << -Width / 200.0 << " " << Width / 200.0 << " " << -Height / 200.0 << " " << Height / 200.0 << " " << Front_plane << " " << Back_plane << "\n";
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-width / 200.0, width / 200.0,
            -height / 200.0, height / 200.0,
            front_plane, back_plane);
}

void Camara::changeObserver() {
    // posicion del observador
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(pos_x, 0, -pos_z);
    glRotatef(observer_angle_x, 1, 0, 0);
    glRotatef(observer_angle_y, 0, 1, 0);
}

void Camara::avanzar() {
    pos_z -= velocidad_movimiento;
}

void Camara::retroceder() {
    pos_z += velocidad_movimiento;
}

void Camara::moveLeft() {
    pos_x += velocidad_movimiento;
}

void Camara::moveRight() {
    pos_x -= velocidad_movimiento;
}

void Camara::resetPosition() {
    pos_x=0;pos_z=4 * front_plane;
}

void Camara::girar(int x, int y) {
    //std::cout << x << " " << y << std::endl;
    observer_angle_x+=y;
    observer_angle_y+=x;
}