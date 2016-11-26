#ifndef T3_LIB_INPUT_H
#define T3_LIB_INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include "entero.h"

struct input
{
	int cantidad;
	int* parametros;
	Entero** numeros;
};

typedef struct input Input;

Input* create_input(char* filename);

void fill_input(Input* i,char* filename);

void set_cantidad_de_pares(Input* i, char* filename);

void print_input(Input* i);

void destroy_input(Input* i);

#endif
