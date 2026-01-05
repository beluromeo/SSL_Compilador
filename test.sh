#!/bin/bash
# Script de prueba para el compilador Micro
# Ejecuta todos los ejemplos y muestra los resultados

echo "========================================="
echo "COMPILADOR MICRO - PRUEBAS AUTOMATIZADAS"
echo "========================================="
echo ""

# Verificar que el compilador existe
if [ ! -f "./micro" ]; then
    echo "Error: Compilador no encontrado. Ejecuta 'make' primero."
    exit 1
fi

# Test 1: Suma de dos números
echo "Test 1: Suma de dos números (ejemplo.micro)"
echo "  Entrada: 5 3"
echo -n "  Salida esperada: 8 | Salida obtenida: "
echo "5 3" | (./micro ejemplo.micro > /dev/null 2>&1 && gcc -o programa output.c >/dev/null 2>&1 && ./programa 2>/dev/null)
echo ""

# Test 2: Expresión aritmética compleja
echo "Test 2: Expresión aritmética (ejemplo2.micro)"
echo "  Entrada: 2 3 4"
echo "  Salida esperada: 2 3 4 10 (a*b+c = 2*3+4 = 10)"
echo -n "  Salida obtenida: "
echo "2 3 4" | (./micro ejemplo2.micro > /dev/null 2>&1 && gcc -o programa output.c >/dev/null 2>&1 && ./programa 2>/dev/null)
echo ""

# Test 3: Operaciones con literales
echo "Test 3: Operaciones con literales (ejemplo3.micro)"
echo "  Código: x:=10; y:=20; z:=x+y*2"
echo "  Salida esperada: 10 20 50"
echo -n "  Salida obtenida: "
./micro ejemplo3.micro > /dev/null 2>&1 && gcc -o programa output.c >/dev/null 2>&1 && ./programa 2>/dev/null
echo ""

# Test 4: Todas las operaciones
echo "Test 4: Todas las operaciones (ejemplo4.micro)"
echo "  Código: suma:=100+200; resta:=200-100; prod:=100*3; div:=200/2"
echo "  Salida esperada: 300 100 300 100"
echo -n "  Salida obtenida: "
./micro ejemplo4.micro > /dev/null 2>&1 && gcc -o programa output.c >/dev/null 2>&1 && ./programa 2>/dev/null
echo ""

# Test 5: Expresiones con paréntesis
echo "Test 5: Expresiones con paréntesis (ejemplo5.micro)"
echo "  Código: resultado := (10+20)*(30-15)/5"
echo "  Salida esperada: 90"
echo -n "  Salida obtenida: "
./micro ejemplo5.micro > /dev/null 2>&1 && gcc -o programa output.c >/dev/null 2>&1 && ./programa 2>/dev/null
echo ""

# Limpiar archivos temporales
rm -f programa output.c

echo "========================================="
echo "PRUEBAS COMPLETADAS"
echo "========================================="
