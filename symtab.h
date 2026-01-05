#ifndef SYMTAB_H
#define SYMTAB_H

#define MAX_SYMBOLS 1000

typedef struct {
    char nombre[256];
} Simbolo;

void inicializar_symtab();
void agregar_simbolo(const char *nombre);
int buscar_simbolo(const char *nombre);
void imprimir_symtab();
char **obtener_simbolos(int *count);

#endif
