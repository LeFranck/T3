#include <stdlib.h>
#include <string.h>
#include "entero.h"

//Cambiar todo a punteros, no por valor
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
		//Ver si debo completar con 0's a la izq
		int n_a1 = (a.cantidad)/2;
		int n_a2 = n_a1 + a.cantidad%2;
		int n_b1 = (b.cantidad)/2;
		int n_b2 = n_b1 + b.cantidad%2;
		//a = a1*10^n_a2 + a2
		//a1,a2,b1,b2,c1,c2,c3
		Entero* e = malloc(sizeof(Entero)*7);
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
		e[4].cantidad = c1->cantidad;
		e[4].digitos = malloc(sizeof(char)*(c1->cantidad+1));
		strcpy(e[4].digitos, c1->digitos);
		e[4].digitos[c1->cantidad] = '\0';

		Entero* c2 = karatsuba(e[1],e[3]);
		e[5].cantidad = c2->cantidad;
		e[5].digitos = malloc(sizeof(char)*(c2->cantidad+1));
		strcpy(e[5].digitos, c2->digitos);
		e[5].digitos[c2->cantidad] = '\0';

		//(a1+a2),(b1+b2),(c1 + c2), (c3 - sumas[2])
		//(sumas[3]*10^n_a2 + c2)
		//(sumas[4] + c1*10^(n_a1+n_a2))

		//Editar suma para q no regrese 0 a la izq
		Entero* sumas = malloc(sizeof(Entero)*6);
		Entero* s0 = suma(e[0],e[1]);
		sumas[0].cantidad = s0->cantidad;
		sumas[0].digitos = malloc(sizeof(char)*(s0->cantidad+1));
		strcpy(sumas[0].digitos, s0->digitos);
		sumas[0].digitos[s0->cantidad] = '\0';

		Entero* s1 = suma(e[2],e[3]);
		sumas[1].cantidad = s1->cantidad;
		sumas[1].digitos = malloc(sizeof(char)*(s1->cantidad+1));
		strcpy(sumas[1].digitos, s1->digitos);
		sumas[1].digitos[s1->cantidad] = '\0';

		Entero* c3 = karatsuba(sumas[0],sumas[1]);
		e[6].cantidad = c3->cantidad;
		e[6].digitos = malloc(sizeof(char)*(c3->cantidad+1));
		strcpy(e[6].digitos, c3->digitos);
		e[6].digitos[c3->cantidad] = '\0';

		Entero* s2 = suma(e[4],e[5]);
		sumas[2].cantidad = s2->cantidad;
		sumas[2].digitos = malloc(sizeof(char)*(s2->cantidad+1));
		strcpy(sumas[2].digitos, s2->digitos);
		sumas[2].digitos[s2->cantidad] = '\0';

		Entero* s3 = resta(e[6],sumas[2]);
		sumas[3].cantidad = s3->cantidad;
		sumas[3].digitos = malloc(sizeof(char)*(s3->cantidad+1));
		strcpy(sumas[3].digitos, s3->digitos);
		sumas[3].digitos[s3->cantidad] = '\0';

		//Generare las multiplicacion x 10
		Entero* por_diez = malloc(sizeof(Entero)*2);
		por_diez[0].cantidad = sumas[3].cantidad + n_a2;
		por_diez[0].digitos = malloc(sizeof(char)*por_diez[0].cantidad + 1);
		char* aux_0 = add_n_rights_0(sumas[3].digitos,n_a2);
		strcpy(por_diez[0].digitos, aux_0);

		Entero* s4 = suma(por_diez[0],e[5]);
		sumas[4].cantidad = s4->cantidad;
		sumas[4].digitos = malloc(sizeof(char)*(s4->cantidad+1));
		strcpy(sumas[4].digitos, s4->digitos);
		sumas[4].digitos[s4->cantidad] = '\0';
		//copy_entero(sumas[4],s4);

		por_diez[1].cantidad = e[4].cantidad + n_a2 + n_a1;
		por_diez[1].digitos = malloc(sizeof(char)*por_diez[1].cantidad + 1);
		char* aux_1 = add_n_rights_0(e[4].digitos,n_a2 + n_a1);
		strcpy(por_diez[1].digitos, aux_1);
		Entero* s5 = suma(por_diez[1],sumas[4]);
		return s5;
	}
}
//Se asume que a es mayor a b
Entero* resta(Entero a, Entero b)
{
	if(a.cantidad > b.cantidad)
	{
		int n = a.cantidad;
		Entero* new_b = malloc(sizeof(Entero));
		new_b[0].digitos = malloc(sizeof(char)*n+1);
		new_b[0].cantidad = n;
		char* digitos = add_n_lefts_0(b.digitos,a.cantidad - b.cantidad);
		strcpy(new_b[0].digitos,digitos);
		free(digitos);
		return resta_igual_largo(a,new_b[0]);
	}else{
		return resta_igual_largo(a,b);
	}
}

//Puede tener un bug cuando a == b
Entero* resta_igual_largo(Entero a, Entero b)
{
	int n = a.cantidad ;
	Entero* r = init_entero_vacio(a.cantidad);
	int i = 0;
	int carry = 0;
	for(i = a.cantidad - 1; i > -1 ; i--)
	{
		int a_int = a.digitos[i] - '0';
		int b_int = b.digitos[i] - '0';
		int c = a_int - b_int - carry;
		if(c < 0)
		{
			c = a_int + 10 - b_int - carry;
			carry = 1;
		}else{
			carry = 0;
		}
		char str[2];
		sprintf(str, "%d", c);
		r->digitos[i] = str[0];
	}
	r->digitos[n] = '\0';
	if(r->digitos[0] == '0')
	{
		int contador = 0;
		for(i = 0; i < r->cantidad; i++)
		{
			if(r->digitos[i] == '0')
			{
				contador = contador + 1;
			}else{
				i = r->cantidad;
			}
		}
		Entero* retorno = init_entero_vacio(r->cantidad - contador);
		copy_last_n(r->digitos,retorno->digitos,r->cantidad-contador);
		retorno->digitos[r->cantidad-contador] = '\0';
		free(r);
		return retorno;
	}else{
		return r;
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
		r->digitos[n] = '\0';
		return r;
	}else{
		r->digitos[0] = '0';
		r->digitos[n] = '\0';
		Entero* sin_l0 = init_entero_vacio(n-1);
		copy_last_n(r->digitos,sin_l0->digitos,n-1);
		sin_l0->digitos[n-1] = '\0';
		//free(r);
		return sin_l0;
	}
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
	free(digitos);
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

void set_entero(Entero r, int len, char* str)
{
	r.cantidad = len;
	r.digitos = malloc(sizeof(char)*len+1);
	strcpy(r.digitos,str);
}

void copy_entero(Entero dest, Entero* a)
{
	printf("digitos %s\n",a->digitos);
	dest.cantidad = a->cantidad;
	dest.digitos = malloc(sizeof(char)*(a->cantidad+1));
	strcpy(dest.digitos, a->digitos);
	dest.digitos[a->cantidad] = '\0';
}

Entero* init_entero_vacio(int len)
{
	Entero* r = malloc(sizeof(Entero));
	r->cantidad = len;
	r->digitos = malloc(sizeof(char)*len+1);
	return r;
}

void set_entero_vacio(Entero r,int len)
{
	r.cantidad = len;
	r.digitos = malloc(sizeof(char)*len+1);
}

void destroy_entero(Entero* e)
{
	free(e->digitos);
	free(e);
}
