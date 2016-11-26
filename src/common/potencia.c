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
