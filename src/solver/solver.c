#include <stdlib.h>
#include <string.h>
#include "../common/input.h"
#include "../common/entero.h"

int main(int argc, int *argv[])
{
	printf("\n\n\n\n");
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

	//Probando Suma
	Entero* numero = malloc(sizeof(Entero)*2);
	numero[0].cantidad = 4;
	numero[0].digitos = malloc(sizeof(char)*4);
	numero[0].digitos = "2902";
	numero[1].cantidad = 3;
	numero[1].digitos = malloc(sizeof(char)*3);
	numero[1].digitos = "109";
	Entero* sss =  suma(numero[0],numero[1]);
	Entero* uuu = resta(numero[0],numero[1]);
	printf("|%s|\n",uuu->digitos);

	char* kilo = add_n_rights_0(numero[0].digitos,20);
	printf("|%s|\n",kilo);

	//Probando copys
	char* holo = "1234567";
	char* aaa = malloc(sizeof(char)*5);
	char* bbb = malloc(sizeof(char)*4);
	copy_first_n(holo,bbb,3);
	copy_last_n(holo,aaa,4);
	aaa[4] = '\0';
	bbb[3] = '\0';
	printf("|%s| \t |%s| \n",bbb,aaa);


	destroy_input(input);
}
