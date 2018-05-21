#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "model_ply.h"

Ply::Ply(const std::string &file_name_p) {
    _file_ply file_ply;
    if (file_ply.open(file_name_p)) {
        file_ply.read(vertices, caras);
        std::cout << "File read correctly" << std::endl;
    } else std::cout << "File can't be opened" << std::endl;
}


