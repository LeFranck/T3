#include <stdlib.h>
#include <string.h>
#include "../common/input.h"
#include "../common/entero.h"
#include "../common/potencia.h"
#include "../common/primalidad.h"

int main(int argc, int *argv[])
{
	if(argc == 3)
	{
		Entero* e = init_entero(strlen(argv[1]),argv[1]);
		int k = atoi(argv[2]);
		int primalidadd = n_es_primo(e,k);
		if(primalidadd == 1)
		{
			printf("PRIMO, ");
		}else{
			printf("COMPUESTO, ");
		}
	}else{
		Input* input = create_input(argv[1]);
		int i = 0;
		for(i = 0; i < input->cantidad; i++)
		{
			int primalidadd = n_es_primo(input->numeros[i],input->parametros[i]);
			if(primalidadd == 0)
			{
				printf("COMPUESTO, ");
			}else{
				printf("PRIMO, ");
			}
		}
		destroy_input(input);
	}
}
