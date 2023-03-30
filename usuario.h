#ifndef __USUARIO_H__
#define __USUARIO_H__
#include "global.h"

typedef struct
{
    int id;
    char nombre[20];
    char password[20];
    int bloqueo;
} tusuario;

void iniciarSesion();

void registrarUsuario();
void listadoUsuarios();

void sacarLibro(int id, char nombre[20]);
void entregarLibro(int id, char nombre[20]);
void misLibros(int id);

void fechaEntrega(char*f[20]); 
void validarDevolucion(int idP);

#endif //__USUARIO_H__