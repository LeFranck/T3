#include <stdlib.h>
#include "../common/input.h"
#include "../common/entero.h"

int main(int argc, int *argv[])
{
	Input* input = create_input(argv[1]);
	print_input(input);
	destroy_input(input);
}
