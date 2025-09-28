#ifndef UTILS_H
#define UTILS_H
#include "structs.h"

// ----------------------- VARIABLES GLOBALES -------------------

extern int totalCadenas;
extern int capacidadCadenas;
extern NodoConstante* lista_constantes_enteras;
extern NodoConstante* lista_constantes_caracter;
extern NodoPalabraReservada* lista_palabras_reservadas;
extern Tipo_Literal_Cadena* lista_cadenas_literal;
extern NodoIdentificadorUOperador* listaIdentificadores;
extern NodoIdentificadorUOperador* listaOperadoresOPuntuacion;
extern NodoIdentificadorUOperador* ultNodoOperadorOPuntuacion;
extern NodoNoReconocida* lista_cadenas_no_reconocidas;

// ----------------------- FUNCIONES ----------------------------

char* guardarCadena(char*);
void funcionCteReal(char*, TipoConstante);
void funcionCteEntera(char*, TipoConstante);
void agregarConstante(NodoConstante**, char*, int, TipoConstante);
void funcionCteCaracter(char*);
void listarConstantesCaracter();
void funcionNoReconocidas(char*, int, int);
void agregarCadenaNoReconocida(NodoNoReconocida**, char*,int, int);
void listarCadenasNoReconocidas();
void listarConstantesPorTipo(TipoConstante);
void funcionPalabraReservada(char*, TipoPalabraReservada, int, int);
void agregarPalabraReservada(NodoPalabraReservada**, char*, TipoPalabraReservada, int, int);
void listarPalabrasReservadas(TipoPalabraReservada);
NodoIdentificadorUOperador* buscarIdentificadorUOperador(char*, NodoIdentificadorUOperador*);
NodoIdentificadorUOperador* crearNodoIdentificadorUOperador(char*);
void listarIdentificadoresUOperadores(NodoIdentificadorUOperador*);
void insertarListaIdentificadores(char*);
void agregarIdentificador(char*);
void agregarOperadorOPuntuacion(char*);
void funcionLiteralCadena(char*);
void listarLiteralesCadena();
void listarConstantesReales();
void mostrarReporte();
void liberarMemoria();

#endif