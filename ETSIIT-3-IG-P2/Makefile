# fichero Makefile
#
# nombre del fichero ejecutable
#
TARGETS= practica2

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuración
#
CFLAGS=    -g -I/usr/include -I$(INCLUDE)
CXXFLAGS=  -std=c++11 -O2 -g -I/usr/include -I$(INCLUDE)

#DIRECTORIOS
BIN= bin
SRC= src
OBJ= obj
LIB= lib
INCLUDE= include

# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
LDFLAGS=  -lGLU -lGL -lglut

# definicion del compilador
#
CC = g++

# definicion de objetos
#
OBJECTS= $(OBJ)/practica2.o $(OBJ)/escena.o $(OBJ)/ejes.o $(OBJ)/punto3d.o \
 $(OBJ)/objeto3d.o $(OBJ)/cubo.o $(OBJ)/tetraedro.o $(OBJ)/cara.o $(OBJ)/piramide.o \
$(OBJ)/file_ply_stl.o $(OBJ)/model_ply.o $(OBJ)/model_rev.o $(OBJ)/model_bar.o


# orden que sera ejecutada por defecto
#
default : $(BIN)/$(TARGETS)

#TODO sin comprimir
all: clean $(TARGETS)

# regla de ejecucion ($^ se refiere a las dependencias)
#
$(BIN)/$(TARGETS) : $(OBJECTS) 
	@echo "---------------------------------\nCompilando\n---------------------------------"
	@mkdir -p $(BIN) $(OBJ)
	$(CC) -o $@ $(CXXFLAGS) $^ $(LDFLAGS) 

#OBJETOS .o que dependan de archivos cc (% recorre todos los archivos .o)
$(OBJ)/%.o: $(SRC)/%.cc
	@mkdir -p $(BIN) $(OBJ)
	@$(CC) -c -o $@ $(CXXFLAGS) $<

$(OBJ)/%.o: $(INC)/%.h
	@mkdir -p $(BIN) $(OBJ)
	@$(CC) -c -o $@ $(CXXFLAGS) $<

#OBJETOS .o dependientes de archivos cpp
#$(OBJ)/%.o: $(SRC)/%.ccp

#
#PHONY indica a make que no cree el archivo especificado.

.PHONY: clean
clean:
	@echo "---------------------------------\nLimpiando\n---------------------------------"
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/$(TARGETS)


#
#COMPRIMIDO Y LIMPIEZA RAR
.PHONY: tgz
tgz:
	@echo "---------------------------------\nLimpiando y comprimiendo en tgz\n---------------------------------"
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/$(TARGETS)
	tar -zcvf $(TARGETS).tgz *


#COMPRIMIDO Y LIMPIEZA ZIP
.PHONY: zip
zip:
	@echo "---------------------------------\nLimpiando y comprimiendo en ZIP\n---------------------------------"
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/$(TARGETS)
	zip $(TARGETS) -r *
