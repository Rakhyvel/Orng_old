/* Code generated using Orange Translator http://josephs-projects.com */

/* Includes used by the program */
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Struct definitions */
struct struct_1 {
	signed int length;
	signed char data[];
};

struct struct_1* new_struct_1(int count)
{
	struct struct_1* retval = malloc(sizeof(signed int) + sizeof(signed char) * count);
	for(int i = 0; i < count; i++) {
		retval->data[i] = 0;
	}
	retval->length = count;
	return retval;
}

struct struct_2 {
	signed int length;
	struct struct_1* data[];
};

struct struct_2* new_struct_2(int count)
{
	struct struct_2* retval = malloc(sizeof(signed int) + sizeof(struct struct_1*) * count);
	for(int i = 0; i < count; i++) {
		retval->data[i] = 0;
	}
	retval->length = count;
	return retval;
}

struct struct_3 {
	signed int test_testModule_g_x;
};

struct struct_3* new_struct_3()
{
	struct struct_3* retval = malloc(sizeof(struct struct_3));
	*retval = ((struct struct_3){0});
	return retval;
}

/* String definitions */

/* Enums */

/* Forward global declarations */
float test_testModule_g;

/* Forward function and procedure declarations */
float test_testModule_f(signed int _x);
signed int test_testModule_main(struct struct_2* _args);

#ifndef ORANGE_PROGRAM_658
#define ORANGE_PROGRAM_658

/* Enum definitions */

/* Function and procedure definitions */
float test_testModule_f(signed int _x)
{ /* 171 */
    float retval;
    retval = _x;
    goto return_block_171;
return_block_171:;
    return retval;
}

signed int test_testModule_main(struct struct_2* _args)
{ /* 172 */
    signed int retval;
    test_testModule_f(5);
    test_testModule_g(5);
    retval = 0;
    goto return_block_172;
return_block_172:;
    return retval;
}

int main(int argc, char** argv)
{
	float (*test_testModule_g) (signed int test_testModule_g_x) = test_testModule_f;
	struct struct_2* args = calloc(sizeof(struct struct_2*) + sizeof(struct struct_1*) * argc, 1);
	args->length = argc;
	for (int  i = 0; i < argc; i++) {
		args->data[i] = calloc(sizeof(struct struct_1*) + sizeof(char) * strlen(argv[i]) + 1, 1);
		args->data[i]->length = strlen(argv[i] + 1);
		memcpy(&args->data[i]->data, argv[i], strlen(argv[i]) + 1);
	}
	int retval = test_testModule_main(args);
	free(args);
	return retval;
}
#endif
