#include "usuario.h"
#include "administrador.h"
#include "libros.h"

void iniciarSesion()
{
    FILE *user;
    user = fopen("usuarios.bin", "rb");

    char nombre[20];
    char password[20];
    int existe = 0;
    int intentos = 0;
    char opcion;
    tusuario usuarios;
    do
    {
        fflush(stdin);
        printf("Usuario: ");
        gets(nombre);
        fflush(stdin);
        printf("Password: ");
        gets(password);

        if (strcmp(ADMIN_USU, nombre) == 0 && strcmp(ADMIN_PAS, password) == 0){
            administrador();
            existe = 1;
        }
        while (fread(&usuarios, sizeof(tusuario), 1, user))
        {
            if (strcmp(usuarios.nombre, nombre) == 0 && strcmp(usuarios.password, password) == 0){
                usuario(usuarios.id, usuarios.nombre);
                existe = 1;
            }
        }
        if (existe == 0)
            {
                printf("usuario o clave incorrecta\n");
                intentos++;
                if(intentos >= 3){
                    printf("haz fallado los tres intentos\n Desea Registrarse?(s/n)\n");
                    scanf("%c",&opcion);
                    if(opcion == 'S' || opcion == 's'){
                        LIMPIAR
                        registrarUsuario();
                        existe = 1;
                    }else{
                        LIMPIAR
                        return;
                    }
                }
                LIMPIAR
            }
    } while (existe == 0);
    fclose(user);
    return;
}

int validar(char nombre[20], char password[20])
{
    FILE *user;
    user = fopen("usuarios.bin", "rb");
    if (user == NULL)
    {
        printf("No hay usuarios disponibles\n");
        PAUSE
        LIMPIAR
        return;
    }

    tusuario usuario;
    int existe = 0;

    if (strcmp(nombre, ADMIN_USU) == 0)
    {
        printf("\n\nel usuario ya existe como administrador\n\n");
        existe = 1;
        PAUSE
    }
    while (fread(&usuario, sizeof(tusuario), 1, user))
    {
        if (strcmp(usuario.nombre, nombre) == 0)
        {
            printf("el usuario ya existe\n\n");
            existe = 1;
            PAUSE
        }
    }

    fclose(user);
    return existe;
}

void registrarUsuario()
{
    FILE *user;
    user = fopen("usuarios.bin", "a+b");

    tusuario usuario;
    char nombre[20];
    char password[20];
    int existe = 0;

    int ultimoID = 0;
    while (fread(&usuario, sizeof(tusuario), 1, user) == 1)
    {
        ultimoID = usuario.id;
    }

    usuario.id = ultimoID + 1;

    printf("REGISTRAR USUARIO\n\n");

    fflush(stdin);
    printf("Ingresa un nombre de usuario: ");
    gets(nombre);

    fflush(stdin);
    printf("Ingresa una clave: ");
    gets(password);

    existe = validar(nombre, password);

    if (existe == 0)
    {
        strcpy(usuario.nombre, nombre);
        strcpy(usuario.password, password);
        usuario.bloqueo = 0;
        fwrite(&usuario, sizeof(tusuario), 1, user);
        printf("la cuenta se creo correctamente :)\n");
        PAUSE
    }
    LIMPIAR
    fclose(user);
}

void listadoUsuarios()
{
    FILE *user;
    tusuario usuario;
    int leidos;

    user = fopen("usuarios.bin", "rb");
    if (user == NULL)
    {
        printf("No hay usuarios disponibles\n");
        PAUSE
        LIMPIAR
        return;
    }

    while ((fread(&usuario, sizeof(tusuario), 1, user)))
    {
        printf("%i %s %s\n", usuario.id, usuario.nombre, usuario.password);
    }

    fclose(user);
    getch();
    LIMPIAR
    return;
}

void restarCantidadLibro(int codigo)
{
    FILE *book;
    book = fopen("libros.bin", "r+b");
    if (book == NULL)
    {
        printf("El archivo esta vacio\n");
        PAUSE
        fclose(book);
        LIMPIAR
        return;
    }

    tlibro libro;

    fread(&libro, sizeof(tlibro), 1, book);
    while (!feof(book))
    {
        if (libro.id == codigo)
        {
            libro.cant = libro.cant - 1;
            int pos = ftell(book) - sizeof(tlibro);
            fseek(book, pos, SEEK_SET);
            fwrite(&libro, sizeof(tlibro), 1, book);
            break;
        }
        fread(&libro, sizeof(tlibro), 1, book);
    }
    fclose(book);
}

void sumarCantidadLibro(int codigo)
{
    FILE *book;
    book = fopen("libros.bin", "r+b");
    if (book == NULL)
    {
        printf("El archivo esta vacio\n");
        PAUSE
        fclose(book);
        LIMPIAR
        return;
    }

    tlibro libro;

    fread(&libro, sizeof(tlibro), 1, book);
    while (!feof(book))
    {
        if (libro.id == codigo)
        {
            libro.cant = libro.cant + 1;
            int pos = ftell(book) - sizeof(tlibro);
            fseek(book, pos, SEEK_SET);
            fwrite(&libro, sizeof(tlibro), 1, book);
            break;
        }
        fread(&libro, sizeof(tlibro), 1, book);
    }
    fclose(book);
}

void sacarLibro(int id, char nombre[20]){
    validarDevolucion(id);
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

    FILE *book;
    book = fopen("libros.bin", "r+b");
    if (book == NULL){
        printf("El archivo esta vacio\n");
        PAUSE
        fclose(book);
        LIMPIAR
        return;
    }

    FILE *user;
    user = fopen ("usuarios.bin", "rb");

    int codigo;
    int existe = 0;
    tusuario usuario;
    tlibro libro;
    tlibroToma toma;
    char fechaH[20];

    while(fread(&usuario,sizeof(tusuario),1,user)){
        if(id == usuario.id){
            break;
        }
    }
    
    while(fread(&toma,sizeof(tlibroToma),1,tomado)){
        if(toma.idP == id){
            break;
        }
    }

    if (usuario.bloqueo == 0){
        printf("=====LIBROS DISPONIBLES=====");
        libroTomado(id); 
        listadoLibros(id);
        printf("Ingrese el ID del libro a llevar:");
        scanf("%d", &codigo);

        while (fread(&libro, sizeof(tlibro), 1, book))
        {
            if (libro.id == codigo && libro.cant > 0){
                    toma.idP = id;
                    toma.idL = libro.id;
                    toma.bloqueo = 0;
                    strcpy(toma.nombreP, nombre);
                    strcpy(toma.nombreL, libro.titulo);
                    strcpy(toma.descripcion, libro.descripcion);
                    fechaEntrega(fechaH);
                    strcpy(toma.fechaEntrega, fechaH);
                    fwrite(&toma, sizeof(tlibroToma), 1, tomado);
                    printf("\nEl libro %s ha sido tomado\n", libro.titulo);
                    existe = 1;
                    restarCantidadLibro(codigo);
                    break;
            }
        }
        if (existe == 0) printf("\nEl codigo del libro no existe o no hay disponibilidad :'(\n");
    }else{
        LIMPIAR
        printf("tu cuenta esta bloqueada porfavor entregar el libro\n");
    }
    fclose(tomado);
    fclose(book);
    PAUSE
    LIMPIAR
    return;
}

void entregarLibro(int id, char nombre[20])
{
    FILE *tomado;
    tomado = fopen("librosTomados.bin", "r+b");
    if (tomado == NULL)
    {
        printf("El archivo esta vacio\n");
        PAUSE
        fclose(tomado);
        LIMPIAR
        return;
    }

    int codigo;
    int existe = 0;
    tlibro libro;
    tlibroToma toma;

    printf("=====MIS LIBROS=====\n");
    misLibros(id);

    printf("Ingrese el ID del libro a regresar:");
    scanf("%d", &codigo);

    while (fread(&toma, sizeof(tlibroToma), 1, tomado))
    {
        if (toma.idL == codigo && id == toma.idP)
        {
            sumarCantidadLibro(codigo);
            printf("\nEl libro %s ha sido regresado\n", toma.nombreL);
            memset(&toma, 0x00, sizeof(tlibroToma));
            int pos = ftell(tomado) - sizeof(tlibroToma);
            fseek(tomado, pos, SEEK_SET);
            fwrite(&toma, sizeof(tlibroToma), 1, tomado);
            existe = 1;
            desbloqueoUsuario(id);
            break;
        }
    }

    if (existe == 0) printf("\nNo tiene ese ID del libro\n");

    fclose(tomado);
    PAUSE
    LIMPIAR
    return;
}

void misLibros(int id){
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

    tlibroToma toma;
    char fechaHora[20];

    while ((fread(&toma, sizeof(tlibroToma), 1, tomado)))
    {
        if (toma.idL <= 0) continue;
        if (toma.idP != id) continue;
        printf("\n==========%i==========\n", toma.idL);
        printf("-----%s-----\n\n", toma.nombreL);
        printf("-----DESCRIPCION-----\n %s\n", toma.descripcion);
        fechaEntrega(fechaHora);
        printf("Fecha en la que se tomo el libro: %s\n", fechaHora);
    }

    fclose(tomado);
    getch();
    LIMPIAR
    return;
}

void fechaEntrega(char*f[20]) {
    time_t t = time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    char fechaHora[20];
    char *formato = "%Y-%m-%d %H:%M:%S";
    tiempoLocal.tm_min +=1;
    int bytesEscritos = strftime(fechaHora, sizeof fechaHora, formato, &tiempoLocal);
    if (bytesEscritos != 0){
        printf("El libro se tomo: %s\n", fechaHora);
    }else{
        printf("Error formateando fecha");
    }
    strcpy(f, fechaHora);
}

void validarDevolucion(int idP){
    FILE *tomado = fopen("librosTomados.bin", "r+b");
    if (tomado == NULL){
        printf("El archivo esta vacio\n");
        PAUSE
        fclose(tomado);
        LIMPIAR
        return;
    }

    tlibroToma toma;
    
    time_t tiempoActual = time(NULL);
    while (fread(&toma, sizeof(tlibroToma), 1, tomado)){
        if (toma.idP == idP){
            printf("\n%s\n", toma.fechaEntrega);
            // verificar si ha pasado el tiempo límite desde la fecha de entrega
            struct tm fechaEntrega;
            int year, month, day, hour, min, sec;
            sscanf(toma.fechaEntrega, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &min, &sec);
            fechaEntrega.tm_year = year - 1900;
            fechaEntrega.tm_mon = month - 1;
            fechaEntrega.tm_mday = day;
            fechaEntrega.tm_hour = hour;
            fechaEntrega.tm_min = min;
            fechaEntrega.tm_sec = sec;
            time_t tiempoEntrega = mktime(&fechaEntrega);
            if (difftime(tiempoActual, tiempoEntrega) > 0 && toma.bloqueo == 0)
            {
                // ha pasado el tiempo límite y el libro no está bloqueado
                toma.bloqueo = 1;
                fseek(tomado, -sizeof(tlibroToma), SEEK_CUR);
                fwrite(&toma, sizeof(tlibroToma), 1, tomado);
                bloqueo_usuario(idP);
                break;
            }
        }
    }
    fclose(tomado);
}

void bloqueo_usuario(int idP){
    FILE *user;
    user = fopen ("usuarios.bin", "r+b");

    tusuario usuario;

    while(fread(&usuario,sizeof(tusuario),1,user)){
        if(idP == usuario.id){
            usuario.bloqueo = 1;
            int pos=ftell(user)-sizeof(tusuario);
            fseek(user,pos,SEEK_SET);
            fwrite(&usuario, sizeof(tusuario), 1, user);
            break;
        }
    }
    fclose(user);
    return;
}

void desbloqueoUsuario(int idP){
    FILE *user;
    user = fopen ("usuarios.bin", "r+b");

    tusuario usuario;

    while(fread(&usuario,sizeof(tusuario),1,user)){
        if(idP == usuario.id){
            usuario.bloqueo = 0;
            int pos=ftell(user)-sizeof(tusuario);
            fseek(user,pos,SEEK_SET);
            fwrite(&usuario, sizeof(tusuario), 1, user);
            break;
        }
    }
    fclose(user);
    return;
}

void libroTomado(int id){
    FILE *tomado = fopen("librosTomados.bin", "rb");
    if (tomado == NULL) {
        printf("El archivo de libros tomados esta vacio\n");
        PAUSE
        return;
    }

    FILE *book = fopen("libros.bin", "rb");
    if (book == NULL) {
        printf("El archivo de libros esta vacio\n");
        PAUSE
        fclose(tomado);
        return;
    }

    tlibro libro;
    tlibroToma toma;
    int encontrado = 0;

    while (fread(&libro, sizeof(tlibro), 1, book)) {
        fseek(tomado, 0, SEEK_SET);
        encontrado = 0;

        while (fread(&toma, sizeof(tlibroToma), 1, tomado)) {
            if (libro.id == toma.idL ) {
                encontrado = 1;
                break;
            }
        }

        if (encontrado) {
            printf("\nEl libro %s esta tomado\n", libro.titulo);
        }
    }

    fclose(tomado);
    fclose(book);
    return;
}