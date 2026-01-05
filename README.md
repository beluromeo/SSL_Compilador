# SSL_Compilador

Compilador del lenguaje procedimental "Micro", desarrollado en C utilizando Flex y Bison. Implementa análisis léxico mediante scanner (Flex) y análisis sintáctico mediante parser (Bison), generando código C funcional a partir de programas escritos en Micro.

## Descripción

Este proyecto implementa un compilador completo para el lenguaje Micro, un lenguaje procedimental simple diseñado con fines educativos. El compilador realiza:

- **Análisis Léxico**: Mediante Flex, identifica tokens del lenguaje (palabras reservadas, identificadores, números, operadores)
- **Análisis Sintáctico**: Mediante Bison, verifica la estructura del programa según la gramática definida
- **Generación de Código**: Produce código C estándar que puede ser compilado y ejecutado

## Características del Lenguaje Micro

### Palabras Reservadas
- `inicio`: Marca el inicio del programa
- `fin`: Marca el fin del programa
- `leer`: Lee valores desde entrada estándar
- `escribir`: Escribe valores a salida estándar

### Operadores
- Asignación: `:=`
- Aritméticos: `+`, `-`, `*`, `/`
- Paréntesis: `(`, `)`
- Delimitadores: `;`, `,`

### Tipos de Datos
- Variables: Identificadores que comienzan con letra (mayúscula o minúscula)
- Números: Literales enteros

### Sintaxis Básica

```
inicio
    leer(variable1, variable2);
    resultado := variable1 + variable2;
    escribir(resultado);
fin
```

## Estructura del Proyecto

```
SSL_Compilador/
├── scanner.l        # Especificación del analizador léxico (Flex)
├── parser.y         # Especificación del analizador sintáctico (Bison)
├── symtab.h/c       # Tabla de símbolos
├── codegen.h/c      # Generación de código C
├── Makefile         # Script de compilación
├── ejemplo.micro    # Programa de ejemplo 1
├── ejemplo2.micro   # Programa de ejemplo 2
├── ejemplo3.micro   # Programa de ejemplo 3
└── README.md        # Este archivo
```

## Requisitos

Para compilar y ejecutar el compilador necesitas:

- GCC (GNU Compiler Collection)
- Flex (Fast Lexical Analyzer)
- Bison (GNU Parser Generator)
- Make

### Instalación en Ubuntu/Debian

```bash
sudo apt-get update
sudo apt-get install gcc flex bison make
```

### Instalación en Fedora/RHEL

```bash
sudo dnf install gcc flex bison make
```

### Instalación en macOS

```bash
brew install flex bison gcc make
```

## Compilación

Para compilar el compilador Micro:

```bash
make
```

Esto generará el ejecutable `micro`.

## Uso

### 1. Compilar un programa Micro

```bash
./micro programa.micro
```

Esto generará un archivo `output.c` con el código C equivalente.

### 2. Compilar el código C generado

```bash
gcc -o programa output.c
```

### 3. Ejecutar el programa

```bash
./programa
```

### Ejemplo Completo

```bash
# Compilar el compilador
make

# Compilar un programa Micro de ejemplo
./micro ejemplo.micro

# Compilar el código C generado
gcc -o programa output.c

# Ejecutar el programa
./programa
```

O usar el target de prueba:

```bash
make test
```

## Ejemplos de Programas

### Ejemplo 1: Suma de dos números

```
inicio
    leer(x, y);
    suma := x + y;
    escribir(suma);
fin
```

Uso:
```bash
./micro ejemplo.micro
gcc -o suma output.c
./suma
# Ingresa dos números, por ejemplo: 5 y 3
# Salida: 8
```

### Ejemplo 2: Expresión aritmética compleja

```
inicio
    leer(a, b, c);
    resultado := a * b + c;
    escribir(a, b, c);
    escribir(resultado);
fin
```

### Ejemplo 3: Operaciones con literales

```
inicio
    x := 10;
    y := 20;
    z := x + y * 2;
    escribir(x, y, z);
fin
```

## Gramática del Lenguaje

```
programa → inicio lista_sentencias fin

lista_sentencias → sentencia
                 | lista_sentencias sentencia

sentencia → ID := expresion ;
          | leer ( lista_ids ) ;
          | escribir ( lista_expresiones ) ;

lista_ids → ID
          | lista_ids , ID

lista_expresiones → expresion
                  | lista_expresiones , expresion

expresion → primaria
          | expresion + expresion
          | expresion - expresion
          | expresion * expresion
          | expresion / expresion
          | ( expresion )

primaria → ID
         | NUM
```

## Arquitectura del Compilador

### 1. Análisis Léxico (scanner.l)

El scanner identifica:
- Palabras reservadas: `inicio`, `fin`, `leer`, `escribir`
- Identificadores: secuencias que comienzan con letra
- Números: secuencias de dígitos
- Operadores y delimitadores

### 2. Análisis Sintáctico (parser.y)

El parser:
- Verifica la estructura del programa
- Construye el árbol de análisis sintáctico
- Gestiona la precedencia de operadores
- Invoca funciones de generación de código

### 3. Tabla de Símbolos (symtab.c)

Mantiene registro de:
- Variables declaradas
- Permite búsqueda eficiente
- Previene redeclaraciones

### 4. Generación de Código (codegen.c)

Genera código C:
- Declaraciones de variables
- Variables temporales para expresiones
- Sentencias de lectura/escritura
- Asignaciones y operaciones

## Comandos del Makefile

- `make` o `make all`: Compila el compilador
- `make clean`: Elimina archivos generados
- `make cleanall`: Limpieza completa incluyendo output.c
- `make test`: Ejecuta una prueba completa con ejemplo.micro
- `make help`: Muestra ayuda

## Manejo de Errores

El compilador detecta:
- Caracteres no reconocidos en el análisis léxico
- Errores de sintaxis en el análisis sintáctico
- Problemas de lectura/escritura de archivos

Los errores incluyen número de línea para facilitar la depuración.

## Limitaciones

- Solo soporta números enteros
- No hay soporte para estructuras de control (if, while, etc.)
- No hay soporte para funciones definidas por el usuario
- No hay verificación de tipos
- No hay optimización de código

## Extensiones Futuras

Posibles mejoras:
- Soporte para números de punto flotante
- Estructuras de control (if-then-else, while, for)
- Funciones y procedimientos
- Arrays y estructuras
- Verificación semántica más robusta
- Optimización de código
- Mensajes de error más descriptivos

## Autor

Proyecto desarrollado como parte del curso de Sintaxis y Semántica de los Lenguajes.

## Licencia

Este proyecto es de código abierto y está disponible para fines educativos.
