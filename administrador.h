#ifndef __ADMINISTRADOR_H__
#define __ADMINISTRADOR_H__
#include "global.h"

#define ADMIN_USU "p"
#define ADMIN_PAS "p"

void librosPrestados();
void prestadosUsuarios();
void usuarioRetrasado();

void cargarUsuario(int id);
void cargarLibro(int id);

#endif //__ADMINISTRADOR_H__
