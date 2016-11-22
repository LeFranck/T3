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

Entero* suma(Entero a, Entero b);

Entero* karatsuba(Entero a, Entero b);

Entero* init_entero(int len, char* str);

Entero* init_entero_vacio(int len);

void destroy_entero(Entero* e);

#endif
