#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "utils.h" 

char* guardarCadena(char* yytext) {
    char* cadena = malloc(strlen(yytext) + 1);
    if (cadena == NULL) {
        fprintf(stderr, "Error al reservar memoria para el lexema (identificador)\n");
        liberarMemoria(); // Libero recursos
        exit(EXIT_FAILURE);
    }
    strcpy(cadena, yytext);
    return cadena;
}

/* - CONSTANTES REALES - */

void funcionCteReal(char* yytext, TipoConstante tipo) {
    double valorEntero;
    valorEntero = strtod(yytext, NULL);
    agregarConstante(&lista_constantes_enteras, yytext, valorEntero, tipo); 
}

/* - CONSTANTES ENTERAS - */

void funcionCteEntera(char* yytext, TipoConstante tipo){
    int valor = strtol(yytext, NULL, 10);
    agregarConstante(&lista_constantes_enteras, yytext, valor, tipo);
}

void agregarConstante(NodoConstante** lista, char* yytext, int valor, TipoConstante tipo) {
    NodoConstante* nuevo = malloc(sizeof(NodoConstante));
    if (!nuevo) {
        fprintf(stderr, "Error de memoria al agregar constante\n");
        liberarMemoria(); // Libero recursos
        exit(1);
    }
    if (tipo == REAL) {
        char* parteDecimal = malloc(strlen(yytext) + 1);
        if (parteDecimal == NULL) {
            fprintf(stderr, "Error de memoria\n");
            liberarMemoria(); // Libero recursos
            exit(1);
        }
        char* parteEntera;
        float mantisa = 0.0f;
        const char* punto = strchr(yytext, '.');
        size_t lenEntera = punto - yytext;
        parteEntera = malloc(lenEntera + 1);
        if (parteEntera == NULL) {
            fprintf(stderr, "Error de memoria\n");
            liberarMemoria(); // Libero recursos
            exit(1);
        }
        strncpy(parteEntera, yytext, lenEntera);
        parteEntera[lenEntera] = '\0';
        strcpy(parteDecimal, punto + 1);  
        nuevo->yytext = guardarCadena(yytext);
        nuevo->tipo = tipo;
        nuevo->valorReal = (double)strtol(parteEntera, NULL, 10);
        mantisa = strtof(parteDecimal, NULL);
        for (size_t i = 0; i < strlen(parteDecimal); i++)
            mantisa /= 10.0f;
        nuevo->valorMantisa = mantisa;
        free(parteEntera);
        free(parteDecimal);
    }    
    else {
        nuevo->yytext = guardarCadena(yytext);  // Copia del string leído
        nuevo->valor = valor;
        nuevo->tipo = tipo;
    }
    nuevo->siguiente = NULL;
    // Criterio QUEUE (FIFO)
    if (*lista == NULL) {
        // Primer nodo
        *lista = nuevo;
    } else {
        // Insertar al final
        NodoConstante* actual = *lista;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

void funcionCteCaracter(char* yytext) {
    NodoConstante* nuevo = malloc(sizeof(NodoConstante));
    if (!nuevo) {
        fprintf(stderr, "Error de memoria al agregar constante carácter\n");
        liberarMemoria(); // Libero recursos
        exit(1);
    }
    nuevo->yytext = guardarCadena(yytext); 
    nuevo->siguiente = NULL;
    if (lista_constantes_caracter == NULL) {
        lista_constantes_caracter = nuevo;
    } else {
        NodoConstante* actual = lista_constantes_caracter;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

void listarConstantesCaracter() {
    printf("\n* Listado de constantes caracter enumerados:\n");
    if (!lista_constantes_caracter) {
        printf("-\n");
        return;
    }
    int i = 1;
    NodoConstante* aux = lista_constantes_caracter;
    while (aux) {
        printf("%d) %s\n", i++, aux->yytext);
        aux = aux->siguiente;
    }
}

/* - CADENAS NO RECONOCIDAS - */

void funcionNoReconocidas(char* yytext, int fila, int columna){
    agregarCadenaNoReconocida(&lista_cadenas_no_reconocidas, yytext, fila, columna);
}

void agregarCadenaNoReconocida(NodoNoReconocida** lista, char* yytext,int linea, int columna) {
    NodoNoReconocida* nuevo = malloc(sizeof(NodoNoReconocida));
    if (!nuevo) {
        fprintf(stderr, "Error de memoria al agregar constante carácter\n");
        liberarMemoria(); // Libero recursos
        exit(1);
    }
    nuevo->yytext = guardarCadena(yytext); 
    nuevo->linea = linea;
    nuevo->columna = columna;
    nuevo->siguiente = NULL;
        // Criterio QUEUE (FIFO)
    if (*lista == NULL) {
        // Primer nodo
        *lista = nuevo;
    } else {
        // Insertar al final
        NodoNoReconocida* actual = *lista;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

void listarCadenasNoReconocidas() {
    NodoNoReconocida* aux = lista_cadenas_no_reconocidas;
    if (!aux) {
        printf("-\n");
    }
    while (aux){
        printf("%s: linea %d, columna %d\n", aux->yytext, aux->linea, aux->columna);
        aux = aux->siguiente;
    }
}

/* - Listar constantes enteras - */

void listarConstantesPorTipo(TipoConstante tipo) {
    NodoConstante* aux = lista_constantes_enteras;
    int existeTipo = 0;
    int suma = 0;
    switch (tipo) {
        case DECIMAL:
            printf("* Listado de constantes enteras decimales:\n");
            break;
        case HEXADECIMAL:
            printf("* Listado de constantes enteras hexadecimales:\n");
            break;
        case OCTAL:
            printf("* Listado de constantes enteras octales:\n");
            break;
        default:
            printf("* Tipo de constante desconocido\n");
            return;
    }
    while (aux) {
        if (aux->tipo == tipo) {
            existeTipo = 1;
            int valorDecimal = aux->valor;
            if (tipo == HEXADECIMAL) {
                valorDecimal = (int)strtol(aux->yytext, NULL, 16);
                aux->valor = valorDecimal;
                printf("%s: valor entero decimal %d\n", aux->yytext, valorDecimal);
            } else if (tipo == OCTAL) {
                valorDecimal = (int)strtol(aux->yytext, NULL, 8);
                aux->valor = valorDecimal;
                printf("%s: valor entero decimal %d\n", aux->yytext, valorDecimal);
            } else {
                printf("%s: valor %d\n", aux->yytext, valorDecimal);
                suma += valorDecimal;
            }
        }
        aux = aux->siguiente;
    }
    if (tipo == DECIMAL && existeTipo) {
        printf("Total acumulado de sumar todas las constantes decimales: %d\n", suma);
    }
    if (!existeTipo) {
        printf("-\n");
    }
    printf("\n");
}

/* - PALABRAS RESERVADAS - */

void funcionPalabraReservada(char* yytext, TipoPalabraReservada tipo, int contadorDeLinea, int columna_actual){
    agregarPalabraReservada(&lista_palabras_reservadas, yytext, tipo, contadorDeLinea, columna_actual);
}

void agregarPalabraReservada(NodoPalabraReservada** lista, char* yytext, TipoPalabraReservada tipo, int linea, int columna) {
    NodoPalabraReservada* nuevo = malloc(sizeof(NodoPalabraReservada));
    if (!nuevo) {
        fprintf(stderr, "Error de memoria al agregar constante\n");
        liberarMemoria(); // Libero recursos
        exit(1);
    }
    nuevo->yytext = guardarCadena(yytext);
    nuevo->tipo = tipo;
    nuevo->linea = linea;
    nuevo->columna = columna;
    nuevo->siguiente = NULL;
    // Criterio QUEUE (FIFO)
    if (*lista == NULL) {
        // Primer nodo
        *lista = nuevo;
    } else {
        // Insertar al final
        NodoPalabraReservada* actual = *lista;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

void listarPalabrasReservadas(TipoPalabraReservada tipo) { 
    int existeTipo = 0;
    NodoPalabraReservada* aux = lista_palabras_reservadas;
    char* tipos[]={
        "clase de almacenamiento",
        "especificadores de tipo",
        "calificadores de tipo",
        "struct o union",
        "enumeracion",
        "etiqueta",
        "seleccion",
        "iteracion",
        "salto",
        "unario"
    };
    printf("\n* Listado de palabras reservadas (%s):\n", tipos[tipo]);
    while (aux) {
        if (aux->tipo == tipo) {
            existeTipo = 1;
            printf("%s: linea %d, columna %d\n", aux->yytext, aux->linea, aux->columna);
        }
        aux = aux->siguiente;
    }
    if (!existeTipo) {
        printf("-\n");
    }
}

/* Funciones comunes entre IDENTIFICADORES y OPERADORES/CARACTERES DE PUNTUACIÓN */

NodoIdentificadorUOperador* buscarIdentificadorUOperador(char* yytext, NodoIdentificadorUOperador* lista) {
    NodoIdentificadorUOperador* aux = lista;
    while (aux != NULL && strcmp(yytext, aux->lexema) != 0)
        aux = aux->siguiente;
    return aux;
}

NodoIdentificadorUOperador* crearNodoIdentificadorUOperador(char* yytext) {
    NodoIdentificadorUOperador* nuevoNodo = malloc(sizeof(NodoIdentificadorUOperador));
    if (!nuevoNodo) {
        fprintf(stderr, "Error al reservar memoria para el identificador\n");
        exit(EXIT_FAILURE);
    }
    nuevoNodo->lexema = malloc(strlen(yytext) + 1);
    if (nuevoNodo->lexema == NULL) {
        fprintf(stderr, "Error al reservar memoria para el lexema (identificador)\n");
        free(nuevoNodo);
        liberarMemoria(); // Libero recursos
        exit(EXIT_FAILURE);
    }
    strcpy(nuevoNodo->lexema, yytext);
    nuevoNodo->cantidad = 1;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

void listarIdentificadoresUOperadores(NodoIdentificadorUOperador* lista) {
    NodoIdentificadorUOperador* aux = lista;
    if (!aux) {
        printf("-\n");
        return;
    }
    while(aux) {
        if (aux->cantidad == 1)
            printf("%s: aparece 1 vez\n", aux->lexema);
        else
            printf("%s: aparece %d veces\n", aux->lexema, aux->cantidad);
        aux = aux->siguiente;
    }
}

/* - IDENTIFICADORES - */

void insertarListaIdentificadores(char* yytext) {
    NodoIdentificadorUOperador* nuevoNodo = crearNodoIdentificadorUOperador(yytext);
    if (listaIdentificadores == NULL || strcmp(yytext, listaIdentificadores->lexema) < 0) {
        nuevoNodo->siguiente = listaIdentificadores;
        listaIdentificadores = nuevoNodo;
    }
    else {
        NodoIdentificadorUOperador* aux = listaIdentificadores;
        while (aux->siguiente != NULL && strcmp(yytext, aux->siguiente->lexema) > 0)
            aux = aux->siguiente;
        nuevoNodo->siguiente = aux->siguiente;
        aux->siguiente = nuevoNodo;
    }
}

void agregarIdentificador(char* yytext) {
    NodoIdentificadorUOperador* aux = buscarIdentificadorUOperador(yytext, listaIdentificadores);
    if (!aux)
        insertarListaIdentificadores(yytext);
    else
        aux->cantidad++;
}

/* - OPERADORES/CARACTERES DE PUNTUACIÓN - */

void agregarOperadorOPuntuacion(char* yytext) {
    NodoIdentificadorUOperador* aux = buscarIdentificadorUOperador(yytext, listaOperadoresOPuntuacion);
    if (!aux) {
        NodoIdentificadorUOperador* nuevoNodo = crearNodoIdentificadorUOperador(yytext);
        if (!listaOperadoresOPuntuacion)
            listaOperadoresOPuntuacion = nuevoNodo;
        else
            ultNodoOperadorOPuntuacion->siguiente = nuevoNodo;
        ultNodoOperadorOPuntuacion = nuevoNodo;
    }
    else {
        aux->cantidad++;
    }
}

void funcionLiteralCadena(char* yytext) {
    if (totalCadenas == capacidadCadenas) {
        capacidadCadenas = (capacidadCadenas == 0) ? 10 : capacidadCadenas * 2;
        lista_cadenas_literal = realloc(lista_cadenas_literal, capacidadCadenas * sizeof(Tipo_Literal_Cadena));
        if (!lista_cadenas_literal) {
            fprintf(stderr, "Error de memoria al redimensionar lista de literales cadena\n");
            liberarMemoria(); // Libero recursos
            exit(1);
        }
    }
    int longitud = strlen(yytext) - 2;
    lista_cadenas_literal[totalCadenas].lexema = guardarCadena(yytext);
    lista_cadenas_literal[totalCadenas].longitud = longitud;
    lista_cadenas_literal[totalCadenas].orden = totalCadenas + 1;
    totalCadenas++;
}

void listarLiteralesCadena() {
    if (totalCadenas == 0) {
        printf("-\n");
        return;
    }
    // orderby long ascendente, desempatar por orden
    for (int i = 0; i < totalCadenas - 1; i++) {
        for (int j = i + 1; j < totalCadenas; j++) {
            Tipo_Literal_Cadena a = lista_cadenas_literal[i];
            Tipo_Literal_Cadena b = lista_cadenas_literal[j];
            if (a.longitud > b.longitud || (a.longitud == b.longitud && a.orden > b.orden)) {
                Tipo_Literal_Cadena temp = lista_cadenas_literal[i];
                lista_cadenas_literal[i] = lista_cadenas_literal[j];
                lista_cadenas_literal[j] = temp;
            }
        }
    }
    for (int i = 0; i < totalCadenas; i++) {
        printf("%s: longitud %d\n", lista_cadenas_literal[i].lexema, lista_cadenas_literal[i].longitud);
    }
}

/*
    - LISTAR CONSTANTES REALES -
    Recorre la lista de constantes y muestra aquellas de tipo REAL,
    imprimiendo su parte entera y mantisa.
*/

void listarConstantesReales() {
    NodoConstante* aux = lista_constantes_enteras;
    int existeTipo = 0;
    printf("* Listado de constantes reales:\n");
    while (aux) {
        if (aux->tipo == REAL) {
            existeTipo = 1;
            printf("%s: parte entera %.6f, mantisa %.6f\n", aux->yytext, aux->valorReal, aux->valorMantisa);
        }
        aux = aux->siguiente;
    }
    if (!existeTipo)
        printf("-\n");
}

void mostrarReporte() {
    printf("\n* Listado de identificadores encontrados:\n");
    listarIdentificadoresUOperadores(listaIdentificadores);

    printf("\n* Listado de literales cadena encontrados:\n");
    listarLiteralesCadena();

    // Listado de palabras reservadas
    for (int i = 0; i < 10; i++)
        listarPalabrasReservadas(i);
    printf("\n");

    // Listado de constantes enteras
    for (int i = 0; i < 3; i++)
        listarConstantesPorTipo(i);

    // Listado de constantes reales
    listarConstantesReales();

    // Listado de constantes caracter
    listarConstantesCaracter();

    printf("\n* Listado de operadores/caracteres de puntuación:\n");
    listarIdentificadoresUOperadores(listaOperadoresOPuntuacion);

    printf("\n* Listado de cadenas no reconocidas:\n");
    listarCadenasNoReconocidas();
}

/*
 * liberarMemoria libera todos los recursos dinámicamente asignados durante la ejecución del programa,
 * incluyendo listas de constantes, identificadores, operadores, y otros elementos léxicos.
 * Es importante llamar a esta función antes de finalizar el programa para evitar memory leaks.
 */

void liberarMemoria() {
    // Liberar lista de constantes enteras y reales
    NodoConstante* aux;
    while (lista_constantes_enteras) {
        aux = lista_constantes_enteras;
        lista_constantes_enteras = lista_constantes_enteras->siguiente;
        free(aux->yytext); 
        free(aux);
    }

    // Liberar lista de constantes de carácter
    NodoConstante* auxCaracter;
    while (lista_constantes_caracter) {
        auxCaracter = lista_constantes_caracter;
        lista_constantes_caracter = lista_constantes_caracter->siguiente;
        free(auxCaracter->yytext);
        free(auxCaracter);
    }

    // Liberar lista de identificadores
    NodoIdentificadorUOperador* auxIdentificadorUOperador;
    while (listaIdentificadores) {
        auxIdentificadorUOperador = listaIdentificadores;
        listaIdentificadores = listaIdentificadores->siguiente;
        free(auxIdentificadorUOperador->lexema);
        free(auxIdentificadorUOperador);
    }

    // Liberar lista de operadores/caracteres de puntuación
    auxIdentificadorUOperador = NULL;
    while (listaOperadoresOPuntuacion) {
        auxIdentificadorUOperador = listaOperadoresOPuntuacion;
        listaOperadoresOPuntuacion = listaOperadoresOPuntuacion->siguiente;
        free(auxIdentificadorUOperador->lexema);
        free(auxIdentificadorUOperador);
    }
    ultNodoOperadorOPuntuacion = NULL;

    // Liberar lista de palabras reservadas
    NodoPalabraReservada* auxPalabraReservada;
    while (lista_palabras_reservadas) {
        auxPalabraReservada = lista_palabras_reservadas;
        lista_palabras_reservadas = lista_palabras_reservadas->siguiente;
        free(auxPalabraReservada->yytext);
        free(auxPalabraReservada);
    }

    // Liberar lista de cadenas no reconocidas
    NodoNoReconocida* auxCadenaNoReconocida;
    while (lista_cadenas_no_reconocidas) {
        auxCadenaNoReconocida = lista_cadenas_no_reconocidas;
        lista_cadenas_no_reconocidas = lista_cadenas_no_reconocidas->siguiente;
        free(auxCadenaNoReconocida->yytext);
        free(auxCadenaNoReconocida);
    }

    // Liberar literales de cadena
    for (int i = 0; i < totalCadenas; i++) {
        free(lista_cadenas_literal[i].lexema);
    }
    free(lista_cadenas_literal);
    auxIdentificadorUOperador = NULL;
    while (listaOperadoresOPuntuacion) {
        auxIdentificadorUOperador = listaOperadoresOPuntuacion;
        listaOperadoresOPuntuacion = listaOperadoresOPuntuacion->siguiente;
        free(auxIdentificadorUOperador->lexema);
        free(auxIdentificadorUOperador);
    }
    ultNodoOperadorOPuntuacion = NULL;
}