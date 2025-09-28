#ifndef STRUCTS_H
#define STRUCTS_H

// ----------------------- ESTRUCTURAS --------------------

typedef struct NodoIdentificadorUOperador {
    char* lexema;
    int cantidad;
    struct NodoIdentificadorUOperador* siguiente;
} NodoIdentificadorUOperador;

typedef struct {
    char *lexema;
    int cantidad;
    int orden;
} Tipo_Identificador;

typedef struct {
    char *lexema;
    int longitud;
    int orden;
} Tipo_Literal_Cadena;

typedef enum {
    ESPECIFICADOR_CLASE_ALMACENAMIENTO,
    ESPECIFICADOR_TIPO,
    CALIFICADOR_TIPO,
    STRUCT_O_UNION,
    ENUMERACION,
    ETIQUETA,
    SELECCION,
    ITERACION,
    SALTO,
    UNARIO
} TipoPalabraReservada;

// Para evitar repetir codigo, armamos un solo nodo para las palabras reservadas
typedef struct NodoPalabraReservada {
    char* yytext;
    TipoPalabraReservada tipo;
    int linea;
    int columna;
    struct NodoPalabraReservada* siguiente; 
} NodoPalabraReservada;

// Para evitar lógica repetida armamos un solo struct para las constantes enteras, con diferencia de tipo mediante enum
typedef enum { 
    DECIMAL, HEXADECIMAL, OCTAL, REAL, CARACTER
} TipoConstante; 

typedef struct NodoConstante {
    char* yytext;
    union {
        int valor; // Para enteras
        double valorReal; // Para reales
        float valorMantisa; // Para reales
    }; // Convertimos de string a int 
    TipoConstante tipo;
    int linea;
    int columna;
    struct NodoConstante* siguiente; 
} NodoConstante;

// Estructura para constantes reales
typedef struct{
    float mantisa;
    int parteEntera;
} Tipo_Real;

typedef struct {
    char caracter;
    int orden;
} Tipo_Caracter;

typedef struct NodoNoReconocida {
    char* yytext;
    int linea;
    int columna;
    struct NodoNoReconocida* siguiente;
} NodoNoReconocida;

typedef struct {
    char* lexema;
    int linea;
    int columna;
} Tipo_Cadena_No_Reconocida; 

#endif