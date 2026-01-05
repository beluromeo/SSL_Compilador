#include <stdio.h>
#include <string.h>
#include "symtab.h"

static Simbolo tabla_simbolos[MAX_SYMBOLS];
static int num_simbolos = 0;

void inicializar_symtab() {
    num_simbolos = 0;
}

int buscar_simbolo(const char *nombre) {
    for (int i = 0; i < num_simbolos; i++) {
        if (strcmp(tabla_simbolos[i].nombre, nombre) == 0) {
            return i;
        }
    }
    return -1;
}

void agregar_simbolo(const char *nombre) {
    if (buscar_simbolo(nombre) == -1) {
        if (num_simbolos < MAX_SYMBOLS) {
            strncpy(tabla_simbolos[num_simbolos].nombre, nombre, sizeof(tabla_simbolos[num_simbolos].nombre) - 1);
            tabla_simbolos[num_simbolos].nombre[sizeof(tabla_simbolos[num_simbolos].nombre) - 1] = '\0';
            num_simbolos++;
        } else {
            fprintf(stderr, "Error: Tabla de símbolos llena\n");
        }
    }
}

void imprimir_symtab() {
    printf("\n=== Tabla de Símbolos ===\n");
    for (int i = 0; i < num_simbolos; i++) {
        printf("%d: %s\n", i, tabla_simbolos[i].nombre);
    }
}

char **obtener_simbolos(int *count) {
    static char *simbolos[MAX_SYMBOLS];
    *count = num_simbolos;
    for (int i = 0; i < num_simbolos; i++) {
        simbolos[i] = tabla_simbolos[i].nombre;
    }
    return simbolos;
}
