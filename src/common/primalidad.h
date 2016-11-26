#ifndef T3_LIB_PRIMALIDAD_H
#define T3_LIB_PRIMALIDAD_H

#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "entero.h"
#include "potencia.h"

int compuesto_inmediato(Entero* e);

int proceso_4(Entero* lista, int len, Entero e);

int final(Entero* lista, int len, Entero e);

int n_es_primo(Entero* e, int param);

Entero** generate_randoms(Entero* e, int param);

Entero* generate_random(Entero* e);

#endif
