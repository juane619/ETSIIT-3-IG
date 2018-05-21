#ifndef _CAMARA_H
#define _CAMARA_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

enum ModeCamara {
    CAM0, CAM1, CAM2
};

class Camara {
private:
    GLfloat width, height;
    GLfloat front_plane, back_plane;
    
    GLfloat pos_z;
    GLfloat pos_x=0;
    
    GLfloat observer_angle_x=0;
    GLfloat observer_angle_y=0;
    int xant, yant;
    
    GLfloat velocidad_movimiento=2.0;
public:
    Camara(GLfloat widthp, GLfloat Heightp, GLfloat frontp, GLfloat backp);
    
    void changeProjection();
    void changeObserver();
    
    void avanzar();
    void retroceder();
    void moveLeft();
    void moveRight();
    void resetPosition();
    
    void girar(int x, int y);
    void guardarPos(int x, int y){
        xant=x; 
        yant=y;
    }
    
    int getXAnt(){
        return xant;
    }
    
    int getYAnt(){
        return yant;
    }
};
#endif
