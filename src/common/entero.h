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

void karatsuba(Entero a, Entero b);

void destroy_entero(Entero* e);

#endif
