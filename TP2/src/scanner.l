%{

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "structs.h"

// Inicialización de punteros globales
NodoConstante* lista_constantes_caracter = NULL;
NodoConstante* lista_constantes_enteras = NULL;
NodoPalabraReservada* lista_palabras_reservadas = NULL;
NodoIdentificadorUOperador* listaIdentificadores = NULL;
NodoIdentificadorUOperador* listaOperadoresOPuntuacion = NULL;
NodoIdentificadorUOperador* ultNodoOperadorOPuntuacion = NULL;
Tipo_Literal_Cadena* lista_cadenas_literal = NULL;
NodoNoReconocida* lista_cadenas_no_reconocidas = NULL;

// Inicialización de variables globales
int totalCadenas = 0;
int capacidadCadenas = 0;

// Definición de contadores
#define INICIO_CONTEO_LINEA 1
#define INICIO_CONTEO_COLUMNA 1

int yylval;

int linea_actual = INICIO_CONTEO_LINEA, columna_actual = INICIO_CONTEO_COLUMNA;

%}

%pointer

%option yylineno

%option noyywrap

%x tokenNoReconocido

ESPECIFICADOR_CLASE_ALMACENAMIENTO (auto|register|static|extern|typedef)
ESPECIFICADOR_TIPO (void|char|short|int|long|float|double|signed|unsigned)
CALIFICADOR_TIPO (const|volatile)
STRUCT_O_UNION (struct|union)
ENUMERACION (enum)
ETIQUETA (case|default)
SELECCION (if|else|switch)
ITERACION (do|while|for)
SALTO (goto|continue|break|return)
UNARIO (sizeof)

DIGITO_DECIMAL [0-9]
DIGITO_DECIMAL_SIN_CERO [1-9]
DIGITO_OCTAL [0-7] 
DIGITO_HEXADECIMAL [0-9a-fA-F]
NO_DIGITO [_a-zA-Z]

SUFIJO_ENTERO ({SUFIJO_LONG}|u|U)
SUFIJO_LONG (l|L)
SUFIJO_FLOTANTE ([fFlL])

PARTE_ENTERA {DIGITO_DECIMAL}+
PARTE_FRACCION ("."{DIGITO_DECIMAL}*)
PARTE_EXPONENTE (e|E)("+"|"-")?{DIGITO_DECIMAL}*

CONSTANTE_CARACTER_SIMPLE \'([^\\\n\'])\'
CONSTANTE_CARACTER_ESCAPE_SIMPLE \'\\{SECUENCIA_ESCAPE_SIMPLE}\'
CONSTANTE_CARACTER_ESCAPE_OCTAL \'\\[0-7]{1,3}\'
CONSTANTE_CARACTER_ESCAPE_HEXADECIMAL \'\\x[0-9a-fA-F]+\'
CONSTANTE_REAL ({PARTE_ENTERA}{PARTE_FRACCION}{PARTE_EXPONENTE}?{SUFIJO_FLOTANTE}?|{PARTE_FRACCION}{PARTE_EXPONENTE}?{SUFIJO_FLOTANTE}?|{PARTE_ENTERA}{PARTE_EXPONENTE}{SUFIJO_FLOTANTE}?)
CONSTANTE_CARACTER ({CONSTANTE_CARACTER_SIMPLE}|{CONSTANTE_CARACTER_ESCAPE_SIMPLE}|{CONSTANTE_CARACTER_ESCAPE_OCTAL}|{CONSTANTE_CARACTER_ESCAPE_HEXADECIMAL})

SECUENCIA_ESCAPE_SIMPLE (a|b|f|n|r|t|v|\'|\"|\?|\\)

CADENA_LITERAL \"([^\\\n"]|\\.)*\"

OPERADOR_O_CARACTER_DE_PUNTUACION (\[|\]|\(|\)|\{|\}|\.|\-\>|\+\+|\-\-|\&|\*|\+|\-|\˜|\!|\/|\%|\<\<|\>\>|\<|\>|\<\=|\>\=|\=\=|\!\=|\ˆ|\||\&\&|\|\||\=|\*\=|\/\=|\%\=|\+\=|\-\=|\<\<\=|\>\>\=|\&\=|\ˆ\=|\|\=|\?|\:|\;|\.\.\.|\,|\#|\#\#)

%%

{DIGITO_DECIMAL_SIN_CERO}{DIGITO_DECIMAL}*{SUFIJO_ENTERO}? { funcionCteEntera(yytext, DECIMAL); columna_actual += yyleng; } 
0{DIGITO_OCTAL}*{SUFIJO_ENTERO}? { funcionCteEntera(yytext, OCTAL); columna_actual += yyleng; } 
0[xX]{DIGITO_HEXADECIMAL}+{SUFIJO_ENTERO}? { funcionCteEntera(yytext, HEXADECIMAL); columna_actual += yyleng; }
{CONSTANTE_REAL} {funcionCteReal(yytext, REAL); columna_actual += yyleng; }

{ESPECIFICADOR_CLASE_ALMACENAMIENTO} { funcionPalabraReservada(yytext, ESPECIFICADOR_CLASE_ALMACENAMIENTO, linea_actual, columna_actual);  columna_actual += yyleng; }
{ESPECIFICADOR_TIPO} { funcionPalabraReservada(yytext, ESPECIFICADOR_TIPO, linea_actual, columna_actual); columna_actual += yyleng; }
{CALIFICADOR_TIPO} { funcionPalabraReservada(yytext, CALIFICADOR_TIPO, linea_actual, columna_actual);  columna_actual += yyleng; }
{STRUCT_O_UNION} { funcionPalabraReservada(yytext, STRUCT_O_UNION, linea_actual, columna_actual);  columna_actual += yyleng; }
{ENUMERACION} { funcionPalabraReservada(yytext, ENUMERACION, linea_actual, columna_actual);  columna_actual += yyleng; }
{ETIQUETA} { funcionPalabraReservada(yytext, ETIQUETA, linea_actual, columna_actual); columna_actual += yyleng; }
{SELECCION} { funcionPalabraReservada(yytext, SELECCION, linea_actual, columna_actual); columna_actual += yyleng; }
{ITERACION} { funcionPalabraReservada(yytext, ITERACION, linea_actual, columna_actual); columna_actual += yyleng; }
{SALTO} { funcionPalabraReservada(yytext, SALTO, linea_actual, columna_actual); columna_actual += yyleng; }
{UNARIO} { funcionPalabraReservada(yytext, UNARIO, linea_actual, columna_actual); columna_actual += yyleng; }

{NO_DIGITO}({NO_DIGITO}|{DIGITO_DECIMAL})* { agregarIdentificador(yytext); columna_actual += yyleng; }
{OPERADOR_O_CARACTER_DE_PUNTUACION} { agregarOperadorOPuntuacion(yytext); columna_actual += yyleng;}
{CONSTANTE_CARACTER} { funcionCteCaracter(yytext); columna_actual += yyleng; }
{CADENA_LITERAL} { funcionLiteralCadena(yytext); columna_actual += yyleng; }

[ \t]+ { columna_actual += yyleng; }

\n+ { linea_actual += yyleng; columna_actual = INICIO_CONTEO_COLUMNA; }

[^ \t\n] { yyless(0) ; BEGIN(tokenNoReconocido); }
<tokenNoReconocido>{
    <<EOF>> {
        fprintf(stderr, "\n");
        BEGIN(INITIAL);
    }
    " "|\t|\n {
        yyless(0);
        fprintf(stderr, "\n");
        BEGIN(INITIAL);
    }
    [^ \t\n]+ { 
        funcionNoReconocidas(yytext, linea_actual, columna_actual);
        columna_actual += yyleng;
        BEGIN(INITIAL);
    }
}

%%

int main(int argc, char *argv[]) {
    int existeParametroSalida = 1;
    // Verifico cantidad de argumentos
    switch (argc)
    {
    case 1:
        printf ("Se necesita al menos un parámetro, opcional, parametro archivo salida: %s <archivo_entrada> [<archivo_salida>]\n", argv[0]);
        printf("Ejemplo: %s datos.txt resultados.txt\n", argv[0]);
        return 1;
        break;

    case 2:
        existeParametroSalida = 0;
        break;
    
    default:
        // Codigo para manejar posibles errores
        break;
    }

    if (argc > 3){
        printf ("Se esperaban maximo 2 parámetros adicionales: %s <archivo_entrada> [<archivo_salida>]\n", argv[0]);
        printf("Ejemplo: %s datos.txt resultados.txt\n", argv[0]);
        printf("\n[INFO] Utilizando %s como ruta archivo entrada y %s ruta salida... ", argv[1], argv[2]);
    }

    const char* pathEntrada = argv[1];
    const char* pathSalida = NULL;

    if(existeParametroSalida){
        pathSalida = argv[2];
        yyout = fopen(pathSalida, "w");	
    }

yyin = fopen(pathEntrada, "r");

yylex();

mostrarReporte();
liberarMemoria();
return 0;
}