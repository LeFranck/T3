#ifndef T3_LIB_PRIMALIDAD_H
#define T3_LIB_PRIMALIDAD_H

#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "entero.h"
#include "mcd.h"
#include "potencia.h"

int compuesto_inmediato(Entero e);

int es_potencia(Entero e);

Entero* generate_randoms(Entero* e, int param);

int proceso_4(Entero* lista, int len, Entero e);

int final(Entero* lista, int len, Entero e);

#endif
