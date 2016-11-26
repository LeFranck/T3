#ifndef T3_LIB_POTENCIA_H
#define T3_LIB_POTENCIA_H

#include "entero.h"
#include <stdlib.h>
#include <stdio.h>

Entero* exponencial(Entero* n, int k);

Entero* exponencial_mod_n(Entero* e, int k, Entero* n);

int tiene_raiz_entera(Entero* n, int k, Entero* i, Entero* j);

#endif
