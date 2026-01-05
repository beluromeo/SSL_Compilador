CC = gcc
CFLAGS = -Wall -g
LEX = flex
YACC = bison

# Nombre del compilador
COMPILER = micro

# Archivos fuente
SOURCES = parser.tab.c lex.yy.c symtab.c codegen.c
OBJECTS = $(SOURCES:.c=.o)

# Regla principal
all: $(COMPILER)

$(COMPILER): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(COMPILER) $(OBJECTS)

# Generar parser de Bison
parser.tab.c parser.tab.h: parser.y
	$(YACC) -d parser.y

# Generar scanner de Flex
lex.yy.c: scanner.l parser.tab.h
	$(LEX) scanner.l

# Compilar archivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Limpiar archivos generados
clean:
	rm -f $(COMPILER) $(OBJECTS) parser.tab.c parser.tab.h lex.yy.c output.c

# Limpiar todo incluyendo archivos de salida
cleanall: clean
	rm -f output.c a.out

# Regla para ayuda
help:
	@echo "Compilador del lenguaje Micro"
	@echo "Uso:"
	@echo "  make          - Compilar el compilador"
	@echo "  make clean    - Limpiar archivos generados"
	@echo "  make cleanall - Limpiar todo"
	@echo "  make test     - Compilar y ejecutar ejemplo"
	@echo ""
	@echo "Para usar el compilador:"
	@echo "  ./micro programa.micro"
	@echo "  gcc -o programa output.c"
	@echo "  ./programa"

# Regla de prueba
test: $(COMPILER)
	@echo "Compilando ejemplo..."
	./$(COMPILER) ejemplo.micro
	@echo "Generando ejecutable..."
	$(CC) -o programa output.c
	@echo "Ejecutando programa..."
	./programa

.PHONY: all clean cleanall help test
