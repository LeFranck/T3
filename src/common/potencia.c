#include "entero.h"

Entero* exponencial(Entero* n, int k)
{
	if(k == 1)
	{
		return n;
	}else if(k%2 == 0)
	{
		Entero* val = exponencial(n,k/2);
		return karatsuba(val,val);
	}else{
		Entero* val = exponencial(n,(k-1)/2);
		return karatsuba(karatsuba(val,val),n);
	}
}

Entero* exponencial_mod_n(Entero* e, int k, Entero* n)
{
	if(k == 1)
	{
		Entero** aux = division_entera1(e,n);
		return aux[1];
	}else if(k%2 == 0)
	{
		Entero* val = exponencial_mod_n(e,k/2,n);
		Entero** aux = division_entera1(karatsuba(val,val),n);
		return aux[1];
	}else{
		Entero* val = exponencial_mod_n(e,(k-1)/2,n);
		Entero** aux = division_entera1(karatsuba(karatsuba(val,val),e),n);
		return aux[1];
	}
}

Entero* exponencial_mod_n2(Entero* e, Entero* k, Entero* n)
{
	Entero* aux1 = init_entero(1,"1");
	Entero* aux2 = init_entero(1,"2");
	Entero* k_menos1 = resta(k,aux1);
	int paridad = 0;
	char last = k->digitos[k->cantidad-1];
	if(last == '0' || last == '2' || last == '4' || last == '6' || last == '8')
	{
		paridad = 1;
	}
	if(iguales(aux1,k)==1)
	{
		Entero** aux = division_entera1(e,n);
		return aux[1];
	}else if(paridad == 1)
	{
		Entero** auxaux = division_entera1(k,aux2);
		Entero* val = exponencial_mod_n2(e,auxaux[0],n);
		Entero** aux = division_entera1(karatsuba(val,val),n);
		return aux[1];
	}else{
		Entero** auxaux = division_entera1(k_menos1,aux2);
		Entero* val = exponencial_mod_n2(e,auxaux[0],n);
		Entero** aux = division_entera1(karatsuba(karatsuba(val,val),e),n);
		return aux[1];
	}
}


int tiene_raiz_entera(Entero* n, int k, Entero* i, Entero* j)
{
	if(iguales(i,j) == 1)
	{
		Entero* exp = exponencial(i,k);
		if(iguales(exp,n) == 1)
		{
			return 1;
		}else{
			return 0;
		}
	}else if(a_menor_b(i,j) == 1)
	{
		Entero* aux2 = init_entero(1,"2");
		Entero** s = division_entera1(suma(i,j),aux2);
		Entero* val = exponencial(s[0],k);
		if(iguales(val,n) == 1)
		{
			return 1;
		}else if(a_menor_b(val,n) == 1)
		{
			Entero* aux = init_entero(1,"1");
			return tiene_raiz_entera(n,k,suma(aux,s[0]),j);
		}else{
			Entero* aux = init_entero(1,"1");
			return tiene_raiz_entera(n,k,i,resta(s[0],aux));
		}
	}else{
		return 0;
	}
}

int es_potencia(Entero* n)
{
	Entero* aux3 = init_entero(1,"3");
	Entero* aux1 = init_entero(1,"1");
	if(iguales(n,aux3) == 1 || a_menor_b(n,aux3) == 1)
	{
		return 0;
	}else{
		int k = 0;
		double log2_10 = 3.3;
		int log2_n = log2_10*(n->cantidad + 1);
		printf("log %d\n",log2_n);
		for(k = 2; k < log2_n; k++)
		{
			if(tiene_raiz_entera(n,k,aux1,n)==1)
			{
				return 1;
			}
		}
		return 0;
	}
}

Entero* mcd(Entero* a, Entero* b)
{
	if(a_menor_b(a,b)==1)
	{
		return mcd(b,a);
	}else if(iguales(a,b)== 1)
	{
		return a;
	}else{
		if(b->cantidad == 0)
		{
			return a;
		}else{
			Entero** mod = division_entera1(a,b);
			return mcd(b,mod[1]);
		}
	}
}
