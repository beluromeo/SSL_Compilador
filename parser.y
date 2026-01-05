%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "symtab.h"

extern int yylex();
extern int yylineno;
extern FILE *yyin;

void yyerror(const char *s);
%}

%union {
    char *id;
    int num;
}

%token INICIO FIN LEER ESCRIBIR
%token ASIGNACION PUNTOYCOMA COMA
%token PARIZQ PARDER
%token MAS MENOS POR DIV
%token <id> ID
%token <num> NUM

%left MAS MENOS
%left POR DIV

%type <id> expresion primaria

%%

programa:
    INICIO {
        generar_inicio();
    }
    lista_sentencias FIN {
        generar_fin();
    }
    ;

lista_sentencias:
    sentencia
    | lista_sentencias sentencia
    ;

sentencia:
    ID ASIGNACION expresion PUNTOYCOMA {
        agregar_simbolo($1);
        generar_asignacion($1, $3);
        free($1);
        free($3);
    }
    | LEER PARIZQ lista_ids PARDER PUNTOYCOMA {
    }
    | ESCRIBIR PARIZQ lista_expresiones PARDER PUNTOYCOMA {
    }
    ;

lista_ids:
    ID {
        agregar_simbolo($1);
        generar_lectura($1);
        free($1);
    }
    | lista_ids COMA ID {
        agregar_simbolo($3);
        generar_lectura($3);
        free($3);
    }
    ;

lista_expresiones:
    expresion {
        generar_escritura($1);
        free($1);
    }
    | lista_expresiones COMA expresion {
        generar_escritura($3);
        free($3);
    }
    ;

expresion:
    primaria {
        $$ = $1;
    }
    | expresion MAS expresion {
        $$ = generar_temporal();
        generar_operacion($$, $1, "+", $3);
        free($1);
        free($3);
    }
    | expresion MENOS expresion {
        $$ = generar_temporal();
        generar_operacion($$, $1, "-", $3);
        free($1);
        free($3);
    }
    | expresion POR expresion {
        $$ = generar_temporal();
        generar_operacion($$, $1, "*", $3);
        free($1);
        free($3);
    }
    | expresion DIV expresion {
        $$ = generar_temporal();
        generar_operacion($$, $1, "/", $3);
        free($1);
        free($3);
    }
    | PARIZQ expresion PARDER {
        $$ = $2;
    }
    ;

primaria:
    ID {
        agregar_simbolo($1);
        $$ = strdup($1);
        free($1);
    }
    | NUM {
        char buffer[32];
        sprintf(buffer, "%d", $1);
        $$ = strdup(buffer);
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error de sintaxis en línea %d: %s\n", yylineno, s);
    exit(1);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <archivo.micro>\n", argv[0]);
        return 1;
    }
    
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Error: No se puede abrir el archivo %s\n", argv[1]);
        return 1;
    }
    
    inicializar_symtab();
    inicializar_codegen();
    
    int result = yyparse();
    
    fclose(yyin);
    
    if (result == 0) {
        printf("Compilación exitosa. Código C generado en output.c\n");
    }
    
    return result;
}
