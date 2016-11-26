#include <stdlib.h>
#include <string.h>
#include "../common/input.h"
#include "../common/entero.h"
#include "../common/potencia.h"

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
	//Entero* e1 = init_entero(42,"943218495553123456789009876543211234567890");
	//Entero* e2 = init_entero(42,"678905641217098765432112345678900987654321");
	//printf("e1 = %s | e2 = %s\n",e1->digitos, e2->digitos);
	//Entero* s1 = suma(e1,e2);
	//Entero* s2 = resta(e1,e2);
	//Entero* s3 = karatsuba(e1,e2);
	//printf("La suma es %s\n", s1->digitos);
	//printf("La resta es %s\n", s2->digitos);
	//printf("La multiplicacion es %s\n", s3->digitos);

	//printf("\n\n");
	//Entero* e3 = init_entero(4,"2435");
	//Entero* e4 = init_entero(3,"123");
	//printf("e3 = %s | e4 = %s\n",e3->digitos, e4->digitos);
	//printf("\n\n");
	//Entero** div = division_entera1(e3,e4);
	//printf("La division da:  %s = %s * %s + %s\n", e3->digitos, e4->digitos, div[0]->digitos, div[1]->digitos);
	//Entero** div2 = division_entera1(s3,e2);
	//printf("La division da:  %s = %s * %s + %s\n", s3->digitos, e2->digitos, div2[0]->digitos, div2[1]->digitos);

	//probando exponencial
	//printf("\n\n");
	//int ki = 3;
	//Entero* e5 = init_entero(3,"122");
	//Entero* e9 = init_entero(2,"91");
	//Entero* exp = exponencial_mod_n(e5,ki,e9);
	//printf("%s^%d mod %s = %s\n",e5->digitos, ki, e9->digitos,  exp->digitos);

	int ki = 2;
	//Entero* e5 = init_entero(3,"101");
	//Entero* aux1 = init_entero(1,"1");
	//printf("%s tiene raiz %d\n",e5->digitos,ki);
	//printf("%d\n",tiene_raiz_entera(e5,ki,aux1,e5));
	//printf("%d\n",es_potencia(e5));


	Entero* e5 = init_entero(3,"101");
	Entero* e6 = init_entero(3,"401");
	Entero* max_cd = mcd(e5,e6);
	printf("mcd(%s,%s) = %s\n",e5->digitos, e6->digitos, max_cd->digitos);

	//destroy_entero(e1);
	//destroy_entero(e2);
	//destroy_entero(e3);
	//destroy_entero(e4);
	//destroy_entero(s1);
	//destroy_entero(s2);
	//destroy_entero(s3);
	//destroy_entero(div[0]);
	//destroy_entero(div[1]);
	//destroy_entero(div2[0]);
	//destroy_entero(div2[0]);
	//free(div);
	//free(div2);
	destroy_input(input);
}
