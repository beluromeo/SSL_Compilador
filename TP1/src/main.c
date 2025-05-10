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
void guardarCadena(int, const char*);
void escribirCaracterSalida(char ,const char*);
typedef enum {
    q0,
    q1,
    q2,
    q3,
    q4,
    q5,
    q6
} EstadosAFD;
typedef enum {
    NO_RECONOCIDA = -1,
    OCTAL = 1,
    DECIMAL = 2,
    HEXADECIMAL = 4
} TipoConstante;

int main(int argc, char *argv[]) {
    int largoString, constEntera, iCadena = 0, matrizTT [7][6];
    char caracter;
    char cadena[50];
    if (argc != 3){
        printf ("Uso: %s <archivo_entrada> <archivo_salida>\n", argv[0]);
        printf("Ejemplo: %s datos.txt resultados.txt\n", argv[0]);
        return 1;
    }
    const char* pathEntrada = argv[1] ;
    const char* pathSalida = argv[2] ;
    cargarMatriz(matrizTT, 7);
    
    // Leer desde fichero entrada.txt
    FILE *ficheroEntrada;
    if ((ficheroEntrada = fopen(pathEntrada, "r")) == NULL){
        printf ("Error al intentar leer archivo...");
        return 1;
    }

    while((caracter = fgetc (ficheroEntrada)) != EOF)
    {
        if (caracter == ','){
            largoString = iCadena;
            constEntera = recorrerAFD(cadena, largoString, matrizTT);
            guardarCadena(constEntera, pathSalida);
            iCadena = 0;
        }else{
            escribirCaracterSalida(caracter, pathSalida);
            cadena[iCadena]=caracter;
            iCadena++;  
            }
    }

    // Agrego chequeo de ultima palabra si no finaliza con ','
    if (iCadena!=0){
        largoString = iCadena-1;
        constEntera = recorrerAFD(cadena, largoString, matrizTT);
        guardarCadena(constEntera, pathSalida);
    }

    fclose(ficheroEntrada);

    return 0;
}

int recorrerAFD(char cadenaLeida[], int largoString, int matrizTT[][6]){
    int simbolo, estadoInicial=q0, estadoActual=q0, estadoRechazo = q6,
    sgteEstado = 0, constEntera = -1;
    for (int i=0; i<largoString; i++){ 
        simbolo = calcularSimbolo(cadenaLeida[i]);
       if (i==0)
            sgteEstado = matrizTT[estadoInicial][simbolo];
        else
            sgteEstado = matrizTT[estadoActual][simbolo];

        estadoActual = sgteEstado;
        if (i == largoString-1 && estadoActual != estadoRechazo)
            // Asigno a que estado representa
            constEntera = estadoActual;
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

void guardarCadena (int constEntera, const char* pathSalida){
    FILE *ficheroSalida;
    if ((ficheroSalida = fopen(pathSalida, "a")) == NULL){
        printf("Error al acceder al archivo %s", pathSalida);
        return;
    }
        switch (constEntera)
    {
    case q1:
        fprintf(ficheroSalida, " OCTAL\n");
        break;

    case q2:
        fprintf(ficheroSalida, " DECIMAL\n");
        break;
    
    case q4:
        fprintf(ficheroSalida, " HEXADECIMAL\n");
        break;
    
    case q5:
        fprintf(ficheroSalida, " OCTAL\n");
        break;
    
    case NO_RECONOCIDA:
        fprintf(ficheroSalida, " NO RECONOCIDA\n");
        break;
    
    default:
        printf("Ocurrió un error...\n");
        break;
    }
    fclose(ficheroSalida);
    return;
}

void escribirCaracterSalida(char caracter , const char* pathSalida){
    FILE *ficheroSalida;
    if ((ficheroSalida = fopen(pathSalida, "a")) == NULL){
        printf("Error al acceder al archivo %s", pathSalida);
        return;
    }
    fputc(caracter, ficheroSalida);
    fclose(ficheroSalida);
}

void cargarMatriz(int matrizTT [][6], int filas){
    // Inicializo Matriz de TT
    // Estado inicial q0- -> '0'
    matrizTT[q0][q0]=q1;
    matrizTT[q0][q1]=q2;
    matrizTT[q0][q2]=q2;
    matrizTT[q0][q3]=q6;
    matrizTT[q0][q4]=q6;
    matrizTT[q0][q5]=q6;

    // Estado q1+ (final) -> '1'
    matrizTT[q1][q0]=q5;
    matrizTT[q1][q1]=q5;
    matrizTT[q1][q2]=q6;
    matrizTT[q1][q3]=q6;
    matrizTT[q1][q4]=q3;
    matrizTT[q1][q5]=q6;

    // Estado q2+ (final) -> '2'
    matrizTT[q2][q0]=q2;
    matrizTT[q2][q1]=q2;
    matrizTT[q2][q2]=q2;
    matrizTT[q2][q3]=q6;
    matrizTT[q2][q4]=q6;
    matrizTT[q2][q5]=q6;

    // Estado q3 -> '3'
    matrizTT[q3][q0]=q4;
    matrizTT[q3][q1]=q4;
    matrizTT[q3][q2]=q4;
    matrizTT[q3][q3]=q4;
    matrizTT[q3][q4]=q6;
    matrizTT[q3][q5]=q6;

    // Estado q4+ (final) -> '4'
    matrizTT[q4][q0]=q4;
    matrizTT[q4][q1]=q4;
    matrizTT[q4][q2]=q4;
    matrizTT[q4][q3]=q4;
    matrizTT[q4][q4]=q6;
    matrizTT[q4][q5]=q6;

    // Estado q5+ (final) -> '5'
    matrizTT[q5][q0]=q5;
    matrizTT[q5][q1]=q5;
    matrizTT[q5][q2]=q6;
    matrizTT[q5][q3]=q6;
    matrizTT[q5][q4]=q6;
    matrizTT[q5][q5]=q6;

    // Estado q6 (inválido) -> '6'
    matrizTT[q6][q0]=q6;
    matrizTT[q6][q1]=q6;
    matrizTT[q6][q2]=q6;
    matrizTT[q6][q3]=q6;
    matrizTT[q6][q4]=q6;
    matrizTT[q6][q5]=q6;
}