#include "global.h"
#include "administrador.h"
#include "usuario.h"
#include "libros.h"

int main()
{
    int op;
    LIMPIAR

    do{
        printf("INICIAR SESION\n");
        printf("1-iniciar sesion\n");
        printf("2-registrarse\n");
        printf("3-salir\n");
        printf("Ingresa la opcion: \n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            LIMPIAR
            iniciarSesion();
            break;

        case 2:
            LIMPIAR
            registrarUsuario();
            break;
        }

    } while (op != 3);
    return 0;
}

int administrador(int id){
    LIMPIAR
    int op;

    do{
        printf("--BIENVENIDO ADMINISTRADOR--\n\n");
        printf("1-Agregar Libro.\n");
        printf("2-Eliminar Libro.\n");
        printf("3-Editar Libro.\n");
        printf("4-Libros disponibles.\n");
        printf("5-Vistas.\n");
        printf("6-Regresar.\n");
        printf("Ingrese su opcion:");
        scanf("%i", &op);

        switch (op)
        {
        case 1:
            LIMPIAR
            crearLibro();
            break;

        case 2:
            LIMPIAR
            borrarLibro();
            break;

        case 3:
            LIMPIAR
            editarLibro();
            break;

        case 4:
            LIMPIAR
            listadoLibros(id);
            break;

        case 5:
            LIMPIAR
            administradorVistas();
            break;

        case 6:
            LIMPIAR
            return;
            break;
        }
    } while (op != 5);
}

int administradorVistas()
{
    LIMPIAR
    int op;

    do
    {
        printf("--VISTAS ADMINISTRADOR--\n\n");
        printf("1-Libros prestados.\n");
        printf("2-Libros prestados por usuario.\n");
        printf("3-Usuarios retrasados en su entrega.\n");
        printf("4-Regresar.\n");
        printf("Ingrese su opcion:");
        scanf("%i", &op);

        switch (op)
        {
        case 1:
            LIMPIAR
            librosPrestados();
            break;

        case 2:
            LIMPIAR
            prestadosUsuarios();
            break;

        case 3:
            LIMPIAR
            usuarioRetrasado();
            break;

        case 4:
            LIMPIAR
            return;
            break;
        }
    } while (op != 4);
}

int usuario(int id, char nombre[20])
{
    LIMPIAR
    int op;
    do
    {
        printf("--BIENVENIDO USUARIO--\n\n");
        printf("1-Sacar Libro.\n");
        printf("2-Entregar Libro.\n");
        printf("3-Vistas.\n");
        printf("4-Regresar.\n");
        printf("Ingrese su opcion:");
        scanf("%i", &op);

        switch (op)
        {
        case 1:
            LIMPIAR
            sacarLibro(id,nombre);
            break;

        case 2:
            LIMPIAR
            entregarLibro(id, nombre);
            break;

        case 3:
            LIMPIAR
            usuarioVistas(id);
            break;

        case 4:
            LIMPIAR
            return;
            break;
        }
    } while (op != 4);
}

int usuarioVistas(int id)
{
    LIMPIAR
    int op;

    do
    {
        printf("--VISTAS USUARIO--\n\n");
        printf("1-Libros Disponibles.\n");
        printf("2-Mis Libros.\n");
        printf("3-Regresar.\n");
        printf("Ingrese su opcion:");
        scanf("%i", &op);

        switch (op)
        {
        case 1:
            LIMPIAR
            listadoLibros(id);
            break;

        case 2:
            LIMPIAR
            misLibros(id);
            break;

        case 3:
            LIMPIAR
            return;
            break;
        }
    } while (op != 2);
}
