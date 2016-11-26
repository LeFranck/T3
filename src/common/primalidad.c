#include "primalidad.h"
#include "entero.h"
#include "potencia.h"
#include <time.h>
#include <stdlib.h>

//0->es primo, 1 es compuesto, 2 no se sabe
int compuesto_inmediato(Entero* e)
{
	char last = e->digitos[e->cantidad-1];
	int r = 2;
	if(e->cantidad == 1)
	{
		if(last == '2' || last == '5')
		{
			r = 0;
		}
	}else{
		if(last == '0' || last == '2' || last == '4' || last == '5' || last == '6' || last == '8')
		{
			r = 1;
		}else{
			r = 2;
		}
	}
	return r;
}

int n_es_primo(Entero* e, int param)
{
	Entero* aux1 = init_entero(1,"1");
	Entero* aux2 = init_entero(1,"2");
	Entero* aux5 = init_entero(1,"5");
	Entero* n_menos1 = resta(e,aux1);
	Entero** div_n_medio = division_entera1(n_menos1,aux2);
	if(iguales(e,aux2) == 1){return 1;}
	if(iguales(e,aux5) == 1){return 1;}
	if(compuesto_inmediato(e) == 1){return 0;}
	if(es_potencia(e)==1)
	{
		return 0;
	}
	Entero** randoms = generate_randoms(e,param);
	int i = 0;
	for(i = 0; i < param; i++)
	{
		if(a_menor_b(aux1,mcd(randoms[i],e)) == 1)
		{
			return 0;
		}else{
			randoms[i] = exponencial_mod_n2(randoms[i],div_n_medio[0],e);
		}
	}
	int neg = 0;
	for(i = 0; i < param; i++)
	{
		if(iguales(randoms[i],n_menos1)==1)
		{
			neg = neg + 1;
		}else if(iguales(randoms[i],aux1) == 0 )
		{
			return 0;
		}
	}
	if(neg == 0)
	{
		return 0;
	}else{
		return 1;
	}
}


Entero** generate_randoms(Entero* e, int param)
{
	Entero** r = malloc(sizeof(Entero*)*param);
	int i = 0;
	for(i = 0; i < param; i++)
	{
		r[i] = generate_random(e);
	}
	return r;
}

Entero* generate_random(Entero* e)
{
	int i = 0;
	int libre = 0;
	int no_es0 = 0;
	char* aux = malloc(sizeof(char)*(e->cantidad + 1));
	while(no_es0 == 0)
	{
		for(i = 0; i < e->cantidad; i++)
		{
			int j = rand() % 10;
			if(libre == 1)
			{
				char c = j + '0';
				aux[i] = c;
				if(j != 0){no_es0 = 1;}
			}else{
				if( j < (e->digitos[i]-'0'))
				{
					libre = 1;
					char c = j + '0';
					aux[i] = c;
					if(j != 0){no_es0 = 1;}
				}else if( j == (e->digitos[i]-'0'))
				{
					char c = j + '0';
					aux[i] = c;
					if(j != 0){no_es0 = 1;}
				}else{
					i = i -1;
				}
			}
		}
		aux[e->cantidad] = '\0';
		Entero* kilo = init_entero(e->cantidad,aux);
		if(iguales(kilo,e) == 1)
		{
			no_es0 = 0;
		}
		destroy_entero(kilo);
	}
	aux[e->cantidad] = '\0';
	Entero* ret = init_entero(e->cantidad, aux);
	return eliminate_lefts_0(ret);
}
