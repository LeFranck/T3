#include <stdlib.h>
#include "entero.h"

Entero* suma(Entero a, Entero b)
{
	int n_final = a.cantidad + 1;
	if(n_final <= b.cantidad){n_final = b.cantidad + 1;}
	Entero* r = init_entero_vacio(n_final);
	int i = 0;
	for(i = 0; i < n_final; i++)
	{
		//Sumar desde derecha a izq y poner los carrys
		printf("");
	}
	return r;
}

Entero* karatsuba(Entero a, Entero b)
{
	if(a.cantidad == 1 && b.cantidad == 1)
	{
		//Caso base
		int a_int = a.digitos[0] - '0';
		int b_int = b.digitos[0] - '0';
		int c = a_int * b_int;
		char str[3];
		sprintf(str, "%d", c);
		int len = strlen(str);

		return init_entero(len,str);
	}else{
		int n11 = a.cantidad/2;
		int n21 = b.cantidad/2;
		int n12 = n11 + a.cantidad%2;
		int n22 = n21 + b.cantidad%2;

		Entero* c1 = malloc(sizeof(Entero));
		Entero* c2 = malloc(sizeof(Entero));
		Entero* c3 = malloc(sizeof(Entero));

		return c1;
	}
}


Entero* init_entero(int len, char* str)
{
	Entero* r = malloc(sizeof(Entero));
	r->cantidad = len;
	r->digitos = malloc(sizeof(char)*len+1);
	strcpy(r->digitos,str);
	return r;
}

Entero* init_entero_vacio(int len)
{
	Entero* r = malloc(sizeof(Entero));
	r->cantidad = len;
	r->digitos = malloc(sizeof(char)*len+1);
	return r;
}

void destroy_entero(Entero* e)
{
	free(e->digitos);
	free(e);
}
