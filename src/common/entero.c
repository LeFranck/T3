#include <stdlib.h>
#include "entero.h"

void destroy_entero(Entero* e)
{
	free(e->digitos);
	free(e);
}
