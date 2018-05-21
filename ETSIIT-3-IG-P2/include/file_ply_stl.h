//******************************************************************************
// class to read ply files of triangles
//
// Domingo Martín Perandres (c) 2003-2013
//
// Gnu Public Licence
//******************************************************************************

#ifndef _READ_PLY
#define _READ_PLY

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "cara.h"
#include "punto3d.h"



class _file_ply {
private:
    std::ifstream File;
    
    void get_token(std::istringstream &Line_stream1, std::string &Token1);
    bool get_new_line(std::ifstream &File, std::istringstream &Line_stream);
public:
    _file_ply() {};
    
    int open(const std::string &File_name);
    void read(std::vector<Punto3D> &Vertices, std::vector<Cara> &Triangles);
    void close();
};

#endif
