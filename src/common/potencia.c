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
