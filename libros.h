#ifndef __LIBROS_H__ 
#define __LIBROS_H__
#include "global.h"

#define MAX 50
typedef struct{
    int id;
    int cant;
    int disponible;
    char titulo[MAX];
    char descripcion[MAX];
} tlibro;

typedef struct{
    int idP;
    int idL;
    int bloqueo;
    char nombreP[MAX];
    char nombreL[MAX];
    char descripcion[MAX];
    char fechaEntrega[20];
} tlibroToma;

void crearLibro();
void listadoLibros(int id);
void editarLibro();
void borrarLibro();

#endif //__LIBROS_H__  