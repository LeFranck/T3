#include <stdlib.h>
#include <string.h>
#include "entero.h"

//Cambiar todo a punteros, no por valor
Entero* karatsuba(Entero* a, Entero* b)
{
	if(a->cantidad == 1 && b->cantidad == 1)
	{
		//Caso base
		int a_int = a->digitos[0] - '0';
		int b_int = b->digitos[0] - '0';
		int c = a_int * b_int;
		char str[3];
		sprintf(str, "%d", c);
		int len = strlen(str);
		return init_entero(len,str);
	}else{
		//Ver si debo completar con 0's a la izq
		if(a->cantidad > b->cantidad)
		{
			char* addl0 = add_n_lefts_0(b->digitos,a->cantidad - b->cantidad);
			b = init_entero(a->cantidad, addl0);
			free(addl0);
		}else if(a->cantidad < b->cantidad)
		{
			char* addl0 = add_n_lefts_0(a->digitos, b->cantidad - a->cantidad);
			a = init_entero(b->cantidad, addl0);
			free(addl0);
		}else{ printf("");}

		int n_a1 = (a->cantidad)/2;
		int n_a2 = n_a1 + a->cantidad%2;
		int n_b1 = (b->cantidad)/2;
		int n_b2 = n_b1 + b->cantidad%2;
		//a = a1*10^n_a2 + a2
		//a1,a2,b1,b2,c1,c2,c3
		Entero** e = malloc(sizeof(Entero*)*7);
		e[0] = init_entero_vacio(n_a1);
		e[1] = init_entero_vacio(n_a2);
		e[2] = init_entero_vacio(n_b1);
		e[3] = init_entero_vacio(n_b2);

		copy_first_n(a->digitos,e[0]->digitos,n_a1);
		e[0]->digitos[n_a1] = '\0';
		copy_last_n(a->digitos,e[1]->digitos,n_a2);
		e[1]->digitos[n_a2] = '\0';
		copy_first_n(b->digitos,e[2]->digitos,n_b1);
		e[2]->digitos[n_b1] = '\0';
		copy_last_n(b->digitos,e[3]->digitos,n_b2);
		e[3]->digitos[n_b2] = '\0';

		e[4] = karatsuba(e[0],e[2]);
		e[5] = karatsuba(e[1],e[3]);

		//(a1+a2),(b1+b2),(c1 + c2), (c3 - sumas[2])
		//(sumas[3]*10^n_a2 + c2)
		//(sumas[4] + c1*10^(n_a1+n_a2))

		//Editar suma para q no regrese 0 a la izq
		Entero** sumas = malloc(sizeof(Entero*)*5);
		sumas[0] = suma(e[0],e[1]);
		sumas[1] = suma(e[2],e[3]);
		e[6] = karatsuba(sumas[0],sumas[1]);
		sumas[2] = suma(e[4],e[5]);
		sumas[3] = resta(e[6],sumas[2]);
		//Generare las multiplicacion x 10
		//Entero* por_diez = malloc(sizeof(Entero)*2);

		char* aux_0 = add_n_rights_0(sumas[3]->digitos,n_a2);
		Entero* pd_1 = init_entero(sumas[3]->cantidad + n_a2, aux_0 );

		sumas[4] = suma(pd_1,e[5]);
		char* aux_1 = add_n_rights_0(e[4]->digitos,n_a2 + n_a2);
		Entero* pd_2 = init_entero(e[4]->cantidad + n_a2 + n_a2 , aux_1);

		Entero* retorno = suma(pd_2,sumas[4]);

		int k = 0;
		destroy_entero(pd_1);
		destroy_entero(pd_2);
		free(aux_0);
		free(aux_1);
		//Entero* ret = sumas[5];
		for(k = 0; k < 7; k++)
		{
			destroy_entero(e[k]);
		}

		for(k = 0; k < 5; k++)
		{
			destroy_entero(sumas[k]);
		}
		free(e);
		free(sumas);
		if(retorno->digitos[0] == '0')
		{
			return eliminate_lefts_0(retorno);
		}else{
			return retorno;
		}
	}
}

//asume que a > b
Entero** division_entera1(Entero* a, Entero* b)
{
	int a_can = a->cantidad;
	int b_can = b->cantidad;
	int puedo_restar = 0;
	int contador_restas = 0;
	int r_fase = 0;
	char** resultado_array = malloc(sizeof(char*)*(a_can-b_can +2));
	printf("r array tiene %d\n",a_can-b_can+1 );
	//char* resultado = malloc(sizeof(char)*(a_can - b_can + 2));
	char* resto = malloc(sizeof(char)*b_can+1);
	int can_0 = a_can-b_can;
	//e sera el entero que va a sufrir las operaciones
	Entero* e = init_entero(a->cantidad,a->digitos);
	char* b_pd = add_n_rights_0(b->digitos,can_0);
	Entero* restando = init_entero(b_can+can_0,b_pd);

	while(puedo_restar == 0)
	{
		if(e->cantidad >= restando->cantidad && es_mayor_que(e->digitos,b->digitos,b_can) != -1)
		{
			e = resta(e,restando);
			r_fase = r_fase + 1;
			printf("e: %s\n",e->digitos);
		}else{
			char* aux = malloc(sizeof(char)*2);
			aux[0] = r_fase + '0';
			aux[1] = '\0';
			resultado_array[contador_restas] = add_n_rights_0(aux,can_0);
			can_0 = can_0 - 1;
			contador_restas = contador_restas + 1;
			r_fase = 0;
			b_pd = add_n_rights_0(b->digitos,can_0);
			restando = init_entero(b_can+can_0,b_pd);

			if(e->cantidad == 0)
			{
				strcpy(resto,"0");
				puedo_restar = 1;
			}

			if(can_0 < 0)
			{
				strcpy(resto,e->digitos);
				puedo_restar = 1;
			}
		}

	}

	Entero** retorno = malloc(sizeof(Entero*)*2);
	int i = 0;
	retorno[0] = init_entero_vacio(strlen(resultado_array[0]));
	for(i = 0; i < retorno[0]->cantidad; i++)
	{
		retorno[0]->digitos[i] = '0';
	}
	retorno[0]->digitos[retorno[0]->cantidad] = '\0';
	for(i = 0; i < a_can - b_can +1  ; i++)
	{
		printf("HITO %d\n",i);
		if(resultado_array[i]!=NULL)
		{
			if(resultado_array[i][0] != '0')
			{
				Entero* auxaux = init_entero(strlen(resultado_array[i]),resultado_array[i]);
				retorno[0] = suma(auxaux, retorno[0]);
			}
		}
	}

	printf("%s\n",resto);
	retorno[1] = init_entero(strlen(resto),resto);
	return retorno;
}

//Se asume que a es mayor a b
Entero* resta(Entero* a, Entero* b)
{
	if(a->cantidad > b->cantidad)
	{
		int n = a->cantidad;
		Entero* new_b = init_entero_vacio(n);
		//new_b[0].digitos = malloc(sizeof(char)*n+1);
		//new_b[0].cantidad = n;
		char* digitos = add_n_lefts_0(b->digitos,a->cantidad - b->cantidad);
		strcpy(new_b->digitos,digitos);
		free(digitos);
		return resta_igual_largo(a,new_b);
	}else{
		return resta_igual_largo(a,b);
	}
}

//Puede tener un bug cuando a == b
Entero* resta_igual_largo(Entero* a, Entero* b)
{
	int n = a->cantidad ;
	Entero* r = init_entero_vacio(a->cantidad);
	int i = 0;
	int carry = 0;
	for(i = a->cantidad - 1; i > -1 ; i--)
	{
		int a_int = a->digitos[i] - '0';
		int b_int = b->digitos[i] - '0';
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
		return eliminate_lefts_0(r);
	}else{
		return r;
	}
}

Entero* suma(Entero* a, Entero* b)
{
	if(a->cantidad == b->cantidad)
	{
		return sumar_enteros_mismo_largo(a,b);
	}else if(a->cantidad > b->cantidad)
	{
		return sumar_enteros_distinto_largo(a,b);
	}else{
		return sumar_enteros_distinto_largo(b,a);
	}
}

Entero* sumar_enteros_mismo_largo(Entero* a, Entero* b)
{
	int n = a->cantidad + 1;
	Entero* r = init_entero_vacio(n);

	int i = 0;
	int carry = 0;
	for(i = a->cantidad - 1; i > -1 ; i--)
	{
		int a_int = a->digitos[i] - '0';
		int b_int = b->digitos[i] - '0';
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
		destroy_entero(r);
		return sin_l0;
	}
}

//a tiene mayor largo
Entero* sumar_enteros_distinto_largo(Entero* a, Entero* b)
{
	int n = a->cantidad + 1;
	Entero* new_b = init_entero_vacio(n-1);
	//Entero* new_b = malloc(sizeof(Entero));
	//new_b[0].digitos = malloc(sizeof(char)*n);
	//new_b[0].cantidad = n-1;
	char* digitos = add_n_lefts_0(b->digitos, a->cantidad - b->cantidad);
	strcpy(new_b->digitos,digitos);
	free(digitos);
	return sumar_enteros_mismo_largo(a, new_b);
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

//1: a > b 	-1: b < a	0: a == b
int es_mayor_que(char* a, char* b, int n)
{
	int i = 0;
	for(i = 0; i < n; i++)
	{
		int a_int = a[i] + '0';
		int b_int = b[i] + '0';
		if(a_int > b_int){return 1;
		}else if(a_int < b_int){return -1;
		}else{printf("");}
	}
	return 0;
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


Entero* eliminate_lefts_0(Entero* r)
{
	int contador = 0;
	int i = 0;
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
	destroy_entero(r);
	return retorno;
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
