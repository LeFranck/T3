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
		int n_a1 = (a.cantidad)/2;
		int n_a2 = n_a1 + a.cantidad%2;
		int n_b1 = (b.cantidad)/2;
		int n_b2 = n_b1 + b.cantidad%2;
		//a = a1*10^n_a2 + a2
		Entero* e = malloc(sizeof(Entero)*7);
		//a1,a2,b1,b2,c1,c2,c3
		e[0].cantidad = n_a1;
		e[1].cantidad = n_a2;
		e[2].cantidad = n_b1;
		e[3].cantidad = n_b2;

		e[0].digitos = malloc(sizeof(char)*(n_a1+1));
		e[1].digitos = malloc(sizeof(char)*(n_a2+1));
		e[2].digitos = malloc(sizeof(char)*(n_b1+1));
		e[3].digitos = malloc(sizeof(char)*(n_b2+1));

		copy_first_n(a.digitos,e[0].digitos,n_a1);
		copy_last_n(a.digitos,e[1].digitos,n_a2);
		copy_first_n(b.digitos,e[2].digitos,n_b1);
		copy_last_n(b.digitos,e[3].digitos,n_b2);

		Entero* c1 = karatsuba(e[0],e[2]);
		Entero* c2 = karatsuba(e[1],e[3]);

		Entero* s1 = suma(e[0],e[1]);
		Entero* s2 = suma(e[2],e[3]);
		//Entero* c3 = karatsuba(s1,s2);

		//La suma final con los respectivos llenados de 0

		return e;
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

void copy_first_n(char* a, char* b, int n )
{
	int i = 0;
	for(i = 0; i < n; i++)
	{
		b[i] = a[i];
	}
}

void copy_last_n(char* a, char* b, int n )
{
	int i = 0;
	int k = 1;
	int len = strlen(a);
	for(i = n-1; i > -1; i--)
	{
		b[i] = a[len-k];
		k = k+1;
	}
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
	for(i = n; i < r_len + 1 ; i++)
	{
		r[i] = s[k];
		k = k + 1;
	}
	r[r_len] = '\0';
	return r;
}

char* add_n_rights_0(char* s, int n)
{
	int len = strlen(s);
	int r_len = len + n;
	char* r = malloc(sizeof(char)*r_len+1);
	int i = 0;
	int k = 0;
	for(i = 0; i < len ; i++)
	{
		r[i] = s[k];
		k = k + 1;
	}
	for(i = len; i < r_len + 1; i++)
	{
		r[i] = '0';
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
