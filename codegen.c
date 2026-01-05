#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "symtab.h"

#define TEMP_BUFFER_SIZE 32
#define READ_BUFFER_SIZE 1024

static FILE *output_file = NULL;
static FILE *temp_file = NULL;
static int temp_count = 0;

void inicializar_codegen() {
    temp_file = tmpfile();
    if (!temp_file) {
        fprintf(stderr, "Error: No se puede crear archivo temporal\n");
        exit(1);
    }
    temp_count = 0;
}

void generar_inicio() {
    // No hacer nada aquí, se generará al final
}

void generar_fin() {
    output_file = fopen("output.c", "w");
    if (!output_file) {
        fprintf(stderr, "Error: No se puede crear el archivo de salida\n");
        exit(1);
    }
    
    int count;
    char **simbolos = obtener_simbolos(&count);
    
    // Generar encabezado
    fprintf(output_file, "#include <stdio.h>\n\n");
    fprintf(output_file, "int main() {\n");
    
    // Declarar todas las variables
    fprintf(output_file, "    /* Variables del programa Micro */\n");
    for (int i = 0; i < count; i++) {
        fprintf(output_file, "    int %s;\n", simbolos[i]);
    }
    fprintf(output_file, "\n");
    
    // Declarar temporales si fueron usados
    if (temp_count > 0) {
        fprintf(output_file, "    /* Variables temporales */\n");
        for (int i = 1; i <= temp_count; i++) {
            fprintf(output_file, "    int _t%d;\n", i);
        }
        fprintf(output_file, "\n");
    }
    
    // Copiar el código generado del archivo temporal
    fprintf(output_file, "    /* Código del programa */\n");
    rewind(temp_file);
    char buffer[READ_BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), temp_file)) {
        fprintf(output_file, "%s", buffer);
    }
    
    // Cerrar main
    fprintf(output_file, "\n    return 0;\n");
    fprintf(output_file, "}\n");
    
    fclose(temp_file);
    fclose(output_file);
}

void generar_lectura(const char *id) {
    fprintf(temp_file, "    scanf(\"%%d\", &%s);\n", id);
}

void generar_escritura(const char *expr) {
    fprintf(temp_file, "    printf(\"%%d\\n\", %s);\n", expr);
}

void generar_asignacion(const char *id, const char *expr) {
    fprintf(temp_file, "    %s = %s;\n", id, expr);
}

void generar_operacion(const char *dest, const char *op1, const char *operador, const char *op2) {
    fprintf(temp_file, "    %s = %s %s %s;\n", dest, op1, operador, op2);
}

char *generar_temporal() {
    temp_count++;
    char *temp = malloc(TEMP_BUFFER_SIZE);
    if (!temp) {
        fprintf(stderr, "Error: No se pudo asignar memoria para temporal\n");
        exit(1);
    }
    sprintf(temp, "_t%d", temp_count);
    return temp;
}
