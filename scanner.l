%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

extern int yylineno;
%}

%option noyywrap
%option yylineno

DIGIT    [0-9]
LETTER   [a-zA-Z]
ID       {LETTER}({LETTER}|{DIGIT})*
NUM      {DIGIT}+

%%

"inicio"        { return INICIO; }
"fin"           { return FIN; }
"leer"          { return LEER; }
"escribir"      { return ESCRIBIR; }

":="            { return ASIGNACION; }
";"             { return PUNTOYCOMA; }
","             { return COMA; }
"("             { return PARIZQ; }
")"             { return PARDER; }
"+"             { return MAS; }
"-"             { return MENOS; }
"*"             { return POR; }
"/"             { return DIV; }

{ID}            { 
                    yylval.id = strdup(yytext);
                    return ID; 
                }

{NUM}           { 
                    yylval.num = atoi(yytext);
                    return NUM; 
                }

[ \t\n]+        { /* Ignorar espacios en blanco */ }

.               { 
                    fprintf(stderr, "Caracter no reconocido: %s en línea %d\n", yytext, yylineno);
                    exit(1);
                }

%%
