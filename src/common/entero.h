#ifndef T3_LIB_ENTERO_H
#define T3_LIB_ENTERO_H

#include <stdio.h>
#include <stdlib.h>

struct entero
{
	int cantidad;
	char* digitos;
};

typedef struct entero Entero;

Entero* karatsuba(Entero a, Entero b);

Entero* suma(Entero a, Entero b);

Entero* sumar_enteros_mismo_largo(Entero a, Entero b);

Entero* sumar_enteros_distinto_largo(Entero a, Entero b);

char* add_n_lefts_0(char* s, int n );

Entero* init_entero(int len, char* str);

Entero* init_entero_vacio(int len);

void destroy_entero(Entero* e);

#endif
