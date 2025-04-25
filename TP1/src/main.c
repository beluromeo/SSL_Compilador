/**************************************************************************
                TP 1 - AUTOMATA FINITO DETERMINISTICO

    Consigna: Recononer las constantes enteras de ANSI C y clasificar por
    su tipo (Decimal, Octal o Hexadecimal)

***************************************************************************/

#include<stdio.h>
#include<string.h>

void cargarMatriz(int [][6], int);
int calcularSimbolo(char);
int recorrerAFD(char [], int, int[][6]);
void imprimirCadena(int, char[]);

int main(int argc, char *argv[]) {
    int largoString, constEntera, matrizTT [7][6];
    char caracter;
    cargarMatriz(matrizTT, 7);
    
    //simulo lectura y validación desde file.txt
    char cadenaLeida[] = "0xaBb1";
    largoString = strlen(cadenaLeida);
    constEntera = recorrerAFD(cadenaLeida, largoString, matrizTT);
    imprimirCadena(constEntera, cadenaLeida); // -> Luego debería escribir el FILE salida.txt
    
    return 0;
}

int recorrerAFD(char cadenaLeida[], int largoString, int matrizTT[][6]){
    int simbolo, estadoInicial=0, estadoActual=0, estadoFinal[4]={1, 2, 4, 5}, estadoRechazo = 6,
    sgteEstado = 0, rechazo = 0, constEntera = -1;
    for (int i=0; i<largoString; i++){ 
        simbolo = calcularSimbolo(cadenaLeida[i]);
        //printf("caracter %c (nro caracter: %d), corresponde a grupo de simbolos: %d\n", cadenaLeida[i], i, simbolo);
        if (i==0)
            sgteEstado = matrizTT[estadoInicial][simbolo];
        else
            sgteEstado = matrizTT[estadoActual][simbolo];
        if (sgteEstado == estadoRechazo){
            rechazo = 1;
            i = largoString;
        }
        estadoActual = sgteEstado;
        if (i == largoString-1 && estadoActual != estadoRechazo){
            // Verifico si el ultimo estado es estado final
            for (int j=0; j<4; j++){
                if(estadoActual == estadoFinal[j])
                    constEntera = estadoFinal[j];
            }
        }
    }
    return constEntera;
}

int calcularSimbolo(char caracter){
    int simbolo = 5; //Inicializo con valor por defecto caracer no valido
    // asigno a los caracteres un int (0={0}, 1=[1-7], 2= {8,9}, 3=[a-fA-F], 4={x,X}, 5=NO_VALIDO)
    if (caracter == '0')
        simbolo = 0;
    // Para rango de caracteres, utilizo tabla ASCII
    if (caracter > 48 && caracter < 56)
        simbolo = 1;
    if (caracter > 55 && caracter < 58)
        simbolo = 2;
    if ((caracter > 64 && caracter < 71) || (caracter > 96 && caracter < 103))
        simbolo = 3;
    if (caracter == 'x' || caracter == 'X')
        simbolo = 4; 
    
    return simbolo;
}

void imprimirCadena (int constEntera, char cadenaLeida[]){
    switch (constEntera)
    {
    case 1:
        printf("La cadena '%s', corresponde a una constante entera octal\n", cadenaLeida);
        break;

    case 2:
        printf("La cadena '%s', corresponde a una constante entera decimal\n", cadenaLeida);
        break;
    
    case 4:
        printf("La cadena '%s', corresponde a una constante entera hexadecimal\n", cadenaLeida);
        break;
    
    case 5:
        printf("La cadena '%s', corresponde a una constante entera octal\n", cadenaLeida);
        break;
    
    case -1:
        printf("Cadena NO reconocida...\n");
        break;
    
    default:
        printf("Ocurrió un error...\n");
        break;
    }
}

void cargarMatriz(int matrizTT [][6], int filas){
    // Inicializo Matriz de TT
    // Estado inicial q0- -> '0'
    matrizTT[0][0]=1;
    matrizTT[0][1]=2;
    matrizTT[0][2]=2;
    matrizTT[0][3]=6;
    matrizTT[0][4]=6;
    matrizTT[0][5]=6;

    // Estado q1+ (final) -> '1'
    matrizTT[1][0]=5;
    matrizTT[1][1]=5;
    matrizTT[1][2]=6;
    matrizTT[1][3]=6;
    matrizTT[1][4]=3;
    matrizTT[1][5]=6;

    // Estado q2+ (final) -> '2'
    matrizTT[2][0]=2;
    matrizTT[2][1]=2;
    matrizTT[2][2]=2;
    matrizTT[2][3]=6;
    matrizTT[2][4]=6;
    matrizTT[2][5]=6;

    // Estado q3 -> '3'
    matrizTT[3][0]=4;
    matrizTT[3][1]=4;
    matrizTT[3][2]=4;
    matrizTT[3][3]=4;
    matrizTT[3][4]=6;
    matrizTT[3][5]=6;

    // Estado q4+ (final) -> '4'
    matrizTT[4][0]=4;
    matrizTT[4][1]=4;
    matrizTT[4][2]=4;
    matrizTT[4][3]=4;
    matrizTT[4][4]=6;
    matrizTT[4][5]=6;

    // Estado q5+ (final) -> '5'
    matrizTT[5][0]=5;
    matrizTT[5][1]=5;
    matrizTT[5][2]=6;
    matrizTT[5][3]=6;
    matrizTT[5][4]=6;
    matrizTT[5][5]=6;

    // Estado q6 (inválido) -> '6'
    matrizTT[5][0]=5;
    matrizTT[5][1]=5;
    matrizTT[5][2]=6;
    matrizTT[5][3]=6;
    matrizTT[5][4]=6;
    matrizTT[5][5]=6;
}