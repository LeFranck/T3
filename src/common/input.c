#include "input.h"
#include <string.h>

Input* create_input(char* filename)
{
	Input* i = malloc(sizeof(Input));
	set_cantidad_de_pares(i,filename);
	fill_input(i,filename);
	return i;
}

void fill_input(Input* i, char* filename)
{
	FILE* fr = fopen(filename,"r");
	int j = 0;
	char Numero[256];
	char Basura[10];
	int param;
	for(j = 0; j < i->cantidad; j++)
	{
		fscanf(fr,"%s %d %s",Numero,&param,Basura);
		i->parametros[j] = param;
		int k = strlen(Numero);
		i->numeros[j].digitos = malloc(sizeof(char)*(k));
		strncpy(i->numeros[j].digitos,Numero,k-1);
		i->numeros[j].digitos[k-1] = '\0';
		i->numeros[j].cantidad = k-1;
	}
	fclose(fr);
}

void set_cantidad_de_pares(Input* i, char* filename)
{
	FILE* fr = fopen(filename, "r");
	int c = 'c';
	int k = 0;
	if(fr == NULL)
	{
		printf("Archivo no existente\n");
	}else{
		while(c != EOF)
		{
			c = fgetc(fr);
			if(c == ',')
			{
				k = k + 1;
			}
		}
	}
	fclose(fr);
	i->cantidad = (k + 1)/2;
	i->parametros = malloc(sizeof(int)*i->cantidad);
	i->numeros = malloc(sizeof(Entero)*i->cantidad);
}

void print_input(Input* i)
{
	printf("El input tiene %d pares\n",i->cantidad);
	int j = 0;
	for(j = 0; j < i->cantidad; j++)
	{
		printf("%d)\t%s\t%d\t%d\n",j,i->numeros[j].digitos,i->numeros[j].cantidad,i->parametros[j]);
	}
}

void destroy_input(Input* i)
{
	free(i->parametros);
	int j = 0;
	for(j = 0; j < i->cantidad; j++)
	{
		free(i->numeros[j].digitos);
	}
	free(i->numeros);
	free(i);
}
