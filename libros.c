#include "libros.h"

void crearLibro(){
    FILE *book;
    book = fopen("libros.bin", "a+b");
    if (book == NULL){
        printf("El archivo esta vacio\n");
        PAUSE
        fclose(book);
        LIMPIAR
        return;
    }
    tlibro libro;

    int ultimoID = 0;
    while (fread(&libro, sizeof(tlibro), 1, book) == 1) {
        ultimoID = libro.id;
    }

    libro.id = ultimoID + 1;

    fflush(stdin);
    printf("Ingrese el titulo del libro:");
    gets(libro.titulo);
    if (strcmp(libro.titulo,"")==0) {
        printf("No debe estar vacio\n");
        PAUSE
        LIMPIAR
        return;
    }

    fflush(stdin);
    printf("Ingrese una breve descripcion:");
    gets(libro.descripcion);
    if (strcmp(libro.descripcion,"")==0) {
        printf("No debe estar vacio\n");
        PAUSE
        LIMPIAR
        return;
    }

    printf("Ingrese los ejemplares disponibles:");
    scanf("%d",&libro.cant);

    fwrite(&libro, sizeof(tlibro), 1, book);

    fclose(book);
    getch();
    LIMPIAR
    return;
}

void listadoLibros(int id){
    FILE *book;
    book = fopen("libros.bin", "rb");
    if (book == NULL){
        printf("No hay libros disponibles\n");
        PAUSE
        LIMPIAR
        return;
    }

    FILE *tomado;
    tomado = fopen("librosTomados.bin", "ab");
    if (tomado == NULL)
    {
        printf("El archivo esta vacio\n");
        PAUSE
        fclose(tomado);
        LIMPIAR
        return;
    }

    tlibro libro;
    tlibroToma toma;
    int encontrado;

    while ((fread(&libro, sizeof(tlibro), 1, book)))
    {
        if (libro.cant <= 0)
            continue;
        if (encontrado && toma.idP == id && toma.idL == libro.id)
        {
            if (fread(&toma, sizeof(tlibroToma), 1, tomado))
            {
                encontrado = 1;
            }
            else
            {
                encontrado = 0;
            }
            continue;
        }
        printf("\n==========%i==========\n", libro.id);
        printf("-----Titulo-----\n %s\n", libro.titulo);
        printf("-----DESCRIPCION-----\n %s\n", libro.descripcion);
        printf("\nEjemplares disponibles = %d\n", libro.cant);
    }

    fclose(book);
    fclose(tomado);
    getch();
    LIMPIAR
    return;
}

void borrarLibro() {
    FILE *book;
    book = fopen("libros.bin", "rb+");
    if (book == NULL) {
        printf("No hay libros disponibles\n");
        return;
    }

    int cod;
    printf("Ingrese el codigo del libro: ");
    scanf("%i", &cod);

    tlibro libro;
    int existe = 0;
    while (fread(&libro, sizeof(tlibro), 1, book) != 0) {
        if (cod == libro.id) {
            printf("%i\n %s\n %s\n %d\n", libro.id, libro.titulo, libro.descripcion, libro.cant);
            existe = 1;

            fseek(book, -sizeof(tlibro), SEEK_CUR);
            tlibro libro_vacio = {0};

            fwrite(&libro_vacio, sizeof(tlibro), 1, book);
            printf("El libro ha sido borrado exitosamente\n");
            break;
        }
    }
    if (existe == 0) printf("No existe el libro con dicho codigo\n");

    fclose(book);
    getch();
    LIMPIAR
}

void editarLibro(){
    FILE *book;
    book = fopen("libros.bin", "r+b");
    if (book == NULL) return;

    int cod;
    printf("Ingrese el codigo del libro para modificarlo:");
    scanf("%i", &cod);

    tlibro libro;

    int existe = 0;
    fread(&libro, sizeof(tlibro), 1, book);

    while (!feof(book)){
        if (cod == libro.id){
            printf("%i\n %s\n %s\n %d\n", libro.id, libro.titulo, libro.descripcion, libro.cant);

            fflush(stdin);
            printf("Ingrese el nuevo nombre del libro:");
            gets(libro.titulo);
            if (strcmp(libro.titulo, "") == 0){
                printf("No debe estar vacio\n");
                PAUSE
                LIMPIAR
                return;
            }

            fflush(stdin);
            printf("Ingrese la nueva descripcion:");
            gets(libro.descripcion);
            if (strcmp(libro.descripcion, "") == 0){
                printf("No debe estar vacio\n");
                PAUSE
                LIMPIAR
                return;
            }

            printf("Ingrese la nueva cantidad de ejemplares:");
            scanf("%d", &libro.cant);

            int pos = ftell(book) - sizeof(tlibro);
            fseek(book, pos, SEEK_SET);
            fwrite(&libro, sizeof(tlibro), 1, book);
            printf("Se modifico el libro correctamente.\n");
            existe = 1;
            break;
        }
        fread(&libro, sizeof(tlibro), 1, book);
    }
    if (existe == 0) printf("No existe un libro con dicho codigo\\n");
    fclose(book);
    getch();
    LIMPIAR
}