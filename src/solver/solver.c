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
	//Probando Suma
	Entero* numero = malloc(sizeof(Entero)*2);
	numero[0].cantidad = 26;
	numero[0].digitos = malloc(sizeof(char)*2);
	numero[0].digitos = "11111111111111111111111111";
	numero[1].cantidad = 40;
	numero[1].digitos = malloc(sizeof(char)*2);
	numero[1].digitos = "9999999999999999999999999999999999999999";
	Entero* r = suma(numero[0],numero[1]);
	printf("\n 9999999999999999999999999999999999999999\n");
	printf("\n 0000000000000011111111111111111111111111\n");
	printf("\n%s\n",r->digitos);

	destroy_input(input);
}
