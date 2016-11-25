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

	//Probando Karatsuba
	//Entero* numero = malloc(sizeof(Entero)*2);
	Entero* e1 = init_entero(12,"543218495553");
	Entero* e2 = init_entero(12,"678905641217");
	printf("e1 = %s | e2 = %s\n",e1->digitos, e2->digitos);
	Entero* s1 = suma(e1,e2);
	Entero* s2 = resta(e1,e2);
	Entero* s3 = karatsuba(e1,e2);
	printf("La suma es %s\n", s1->digitos);
	printf("La resta es %s\n", s2->digitos);
	printf("La multiplicacion es %s\n", s3->digitos);

	//numero[0].cantidad = 2;
	//numero[0].digitos = malloc(sizeof(char)*2);
	//numero[0].digitos = "91";
	//numero[1].cantidad = 2;
	//numero[1].digitos = malloc(sizeof(char)*2);
	//numero[1].digitos = "88";
	//Entero* sss =  suma(numero[0],numero[1]);
	//printf("suma  = |%s|\n",sss->digitos);
	//Entero* uuu = resta(numero[0],numero[1]);
	//printf("resta = |%s|\n",uuu->digitos);
	//Entero* kara = karatsuba(numero[0],numero[1]);
	//printf("karat = |%s|\n",kara->digitos);

	//free(numero);
	//free(sss->digitos);
	//free(sss);
	//free(uuu->digitos);
	//free(uuu);

	destroy_entero(e1);
	destroy_entero(e2);
	destroy_entero(s1);
	destroy_entero(s2);
	destroy_entero(s3);
	destroy_input(input);
}
