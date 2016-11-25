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

Entero* karatsuba(Entero* a, Entero* b);

Entero** division_entera1(Entero* a, Entero* b);

Entero* resta(Entero* a, Entero* b);

Entero* resta_igual_largo(Entero* a, Entero* b);

Entero* suma(Entero* a, Entero* b);

Entero* sumar_enteros_mismo_largo(Entero* a, Entero* b);

Entero* sumar_enteros_distinto_largo(Entero* a, Entero* b);

//izq a derecha
void copy_first_n(char* a, char* b, int n);

void copy_last_n(char* a, char* b, int n );

int es_mayor_que(char* a , char* b, int n);

Entero* eliminate_lefts_0(Entero* e);

char* add_n_lefts_0(char* s, int n );

char* add_n_rights_0(char* s, int n );

Entero* init_entero(int len, char* str);

Entero* init_entero_vacio(int len);

void set_entero(Entero e, int len, char* str);

void copy_entero(Entero dest, Entero a);

void set_entero_vacio(Entero e, int len);

void destroy_entero(Entero* e);

#endif
