#include "primalidad.h"

//0->es primo, 1 es compuesto, 2 no se sabe
int compuesto_inmediato(Entero e)
{
	char last = e.digitos[e.cantidad-1];
	int r = 2;
	if(e.cantidad == 1)
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
