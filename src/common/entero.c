#include <stdlib.h>
#include <string.h>
#include "entero.h"

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


Entero* suma(Entero a, Entero b)
{
	if(a.cantidad == b.cantidad)
	{
		return sumar_enteros_mismo_largo(a,b);
	}else if(a.cantidad > b.cantidad)
	{
		return sumar_enteros_distinto_largo(a,b);
	}else{
		return sumar_enteros_distinto_largo(b,a);
	}
}

Entero* sumar_enteros_mismo_largo(Entero a, Entero b)
{
	int n = a.cantidad + 1;
	Entero* r = init_entero_vacio(n);

	int i = 0;
	int carry = 0;
	for(i = a.cantidad - 1; i > -1 ; i--)
	{
		int a_int = a.digitos[i] - '0';
		int b_int = b.digitos[i] - '0';
		int c = a_int + b_int + carry;
		char str[3];
		sprintf(str, "%d", c);
		int len = strlen(str);
		if(len == 1)
		{
			r->digitos[i+1] = str[0];
			carry = 0;
		}else{
			r->digitos[i+1] = str[1];
			carry = 1;
		}
	}
	if(carry == 1){
		r->digitos[0] = '1';
	}else{
		r->digitos[0] = '0';
	}
	r->digitos[n] = '\0';
	return r;
}

//a tiene mayor largo
Entero* sumar_enteros_distinto_largo(Entero a, Entero b)
{
	int n = a.cantidad + 1;
	Entero* new_b = malloc(sizeof(Entero));
	new_b[0].digitos = malloc(sizeof(char)*n);
	new_b[0].cantidad = n-1;
	char* digitos = add_n_lefts_0(b.digitos, a.cantidad - b.cantidad);
	strcpy(new_b[0].digitos,digitos);
	return sumar_enteros_mismo_largo(a, new_b[0]);
}

char* add_n_lefts_0(char* s, int n)
{
	int len = strlen(s);
	int r_len = len + n;
	char* r = malloc(sizeof(char)*r_len+1);
	int i = 0;
	for(i = 0; i < n; i++)
	{
		r[i] = '0';
	}
	int k = 0;
	printf("\n\n");
	for(i = n; i < r_len + 1 ; i++)
	{
		r[i] = s[k];
		k = k + 1;
	}
	r[r_len] = '\0';
	return r;
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
