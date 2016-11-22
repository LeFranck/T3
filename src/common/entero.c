#include <stdlib.h>
#include "entero.h"

void karatsuba(Entero a, Entero b)
{
	if(a.cantidad == 1 && b.cantidad == 1)
	{
		int a_int = a.digitos[0] - '0';
		int b_int = b.digitos[0] - '0';
		int c = a_int * b_int;
		char str[3];
		sprintf(str, "%d", c);
		Entero* aux = malloc(sizeof(Entero));
		aux->cantidad = 2;
		aux->digitos = malloc(sizeof(char)*3);
		strcpy(aux->digitos,str);
	}else{
		int n1 = a.cantidad/2;
		int n2 = b.cantidad/2;
	}
}


void destroy_entero(Entero* e)
{
	free(e->digitos);
	free(e);
}
