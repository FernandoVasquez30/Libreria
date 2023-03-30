#include "administrador.h"
#include "libros.h"
#include "usuario.h"

void librosPrestados()
{
    FILE *tomado;
    tomado = fopen("librosTomados.bin", "rb");
    if (tomado == NULL)
    {
        printf("El archivo esta vacio\n");
        PAUSE
        fclose(tomado);
        LIMPIAR
        return;
    }

    FILE *user;
    user = fopen("usuarios.bin", "rb");

    tlibroToma toma;
    tusuario usuario;

    while (fread(&toma, sizeof(tlibroToma), 1, tomado) && fread(&usuario, sizeof(tusuario), 1, user))
    {
        while (!feof (tomado))
        {
            if (toma.idL == usuario.id)
            {
                printf("=====%s=====\n", toma.nombreL);
                cargarLibro(toma.idL);
                break;
            }
            fread(&toma, sizeof(tlibroToma), 1, tomado);
        }
    }

    fclose(tomado);
    getch();
    LIMPIAR
    return;
}

void prestadosUsuarios()
{
    FILE *tomado;
    tomado = fopen("librosTomados.bin", "rb");
    if (tomado == NULL)
    {
        printf("El archivo esta vacio\n");
        PAUSE
        fclose(tomado);
        LIMPIAR
        return;
    }
    FILE *user;
    user = fopen("usuarios.bin", "rb");

    tlibroToma ltomado;
    tusuario usuario;

    while (fread(&usuario, sizeof(tusuario), 1, user) && fread(&ltomado, sizeof(tlibroToma), 1, tomado))
    {
        while (!feof (tomado))
        {
            if (usuario.id == ltomado.idP)
            {
                printf("Usuario: %s\n", usuario.nombre);
                cargarUsuario(usuario.id);
                break;
            }
            fread(&ltomado, sizeof(tlibroToma), 1, tomado);
        }
    }

    fclose(tomado);
    fclose(user);
    getch();
    LIMPIAR
    return;
}

void usuarioRetrasado(){
    FILE *tomado;
    tomado = fopen("librosTomados.bin", "rb");
    if (tomado == NULL)
    {
        printf("El archivo esta vacio\n");
        PAUSE
        fclose(tomado);
        LIMPIAR
        return;
    }
    FILE *user;
    user = fopen("usuarios.bin", "rb");

    tlibroToma ltomado;
    tusuario usuario;

    printf("Estas personas estan bloqueados\n\n");

    while(fread(&usuario,sizeof(tusuario),1,user)){
        if(usuario.bloqueo == 1){
            printf("usuario: %s\n",usuario.nombre);
        }
    }

    fclose(tomado);
    fclose(user);
    getch();
    LIMPIAR
    return;
}

void cargarUsuario(int id){
    FILE *tomado;
    tomado = fopen("librosTomados.bin", "rb");
    if (tomado == NULL){
        printf("El archivo esta vacio\n");
        PAUSE
        fclose(tomado);
        LIMPIAR
        return;
    }

    tlibroToma ltomado;
    
    while (fread(&ltomado, sizeof(tlibroToma), 1, tomado))
    {
        if (id == ltomado.idP)
        {
            printf("%d %s\n", ltomado.idL ,ltomado.nombreL);
        }
    }
    printf("\n\n");
    fclose(tomado);
    return;
}

void cargarLibro(int id){
    FILE *tomado;
    tomado = fopen("librosTomados.bin", "rb");
    if (tomado == NULL){
        printf("El archivo esta vacio\n");
        PAUSE
        fclose(tomado);
        LIMPIAR
        return;
    }

    tlibroToma ltomado;
    
    while (fread(&ltomado, sizeof(tlibroToma), 1, tomado))
    {
        if (id == ltomado.idL)
        {
            printf("Usuario: %s\n", ltomado.nombreP);
        }
    }
    printf("\n\n");
    fclose(tomado);
    return;
}