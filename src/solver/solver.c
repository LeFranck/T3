#include <stdlib.h>
#include "../common/input.h"
#include "../common/entero.h"

int main(int argc, int *argv[])
{
	//Manejo del input
	Input* input = create_input(argv[1]);
	print_input(input);

	//Probando primalidad
	int i = 0;
	for(i = 0; i < input->cantidad; i++)
	{
		printf("%s\t",input->numeros[i].digitos);
		int retorno = compuesto_inmediato(input->numeros[i]);
		if(retorno == 0)
		{
			printf("es primo\n");
		}else if(retorno == 1){
			printf("es compuesto \n");
		}else{
			printf("no se sabe aun\n");
		}
	}

	printf("\n\n\n\n");
	//Probando karatsuba
	Entero* numero = malloc(sizeof(Entero)*2);
	numero[0].cantidad = 1;
	numero[0].digitos = malloc(sizeof(char)*2);
	numero[0].digitos = "2";
	numero[1].cantidad = 1;
	numero[1].digitos = malloc(sizeof(char)*2);
	numero[1].digitos = "4";
	karatsuba(numero[0],numero[1]);

	destroy_input(input);
}
