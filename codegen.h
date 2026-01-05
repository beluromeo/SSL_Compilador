#ifndef CODEGEN_H
#define CODEGEN_H

void inicializar_codegen();
void generar_inicio();
void generar_fin();
void generar_lectura(const char *id);
void generar_escritura(const char *expr);
void generar_asignacion(const char *id, const char *expr);
void generar_operacion(const char *dest, const char *op1, const char *operador, const char *op2);
char *generar_temporal();

#endif
