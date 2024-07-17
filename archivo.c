#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *archive;

    archive = fopen("documento.txt", "w");
    if (archive == NULL) {
        perror("Error al abrir el archivo para escribir");
        return 1;
    }

    fprintf(archive, "La contaminacion es un viaje con destino a la distopia\n");
    fclose(archive);

    archive = fopen("documento.txt", "r");
    if (archive == NULL) {
        perror("Error al abrir el archivo para leer");
        return 1;
    }

    char buffer[100];
    printf("El texto dentro del documento actualmente es:\n");
    while (fgets(buffer, 100, archive) != NULL) {
        printf("%s", buffer);
    }
    fclose(archive);

    char buffer2[100];
    printf("\nIngrese aqui el texto que reemplazara al anterior:\n");
    fgets(buffer2, 100, stdin);

    archive = fopen("documento.txt", "w");
    if (archive == NULL) {
        perror("Error al abrir el archivo para escribir");
        return 1;
    }

    fprintf(archive, "%s", buffer2);
    fclose(archive);

    archive = fopen("documento.txt", "r");
    if (archive == NULL) {
        perror("Error al abrir el archivo para leer");
        return 1;
    }

    printf("\nEl nuevo texto dentro del documento es:\n");
    while (fgets(buffer, 100, archive) != NULL) {
        printf("%s", buffer);
    }
    fclose(archive);

    return 0;
}