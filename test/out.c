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

/* String definitions */

/* Enums */
#define test_testModule_Color_RED 0
#define test_testModule_Color_GREEN 1
#define test_testModule_Color_BLUE 2
struct struct_1* test_testModule_Color_toString(int x);
int test_testModule_Color_length;

/* Forward global declarations */

/* Forward function declarations */
signed int test_testModule_main(struct struct_2* _args);

#ifndef ORANGE_PROGRAM_25960
#define ORANGE_PROGRAM_25960

/* Enum definitions */
struct struct_1 test_testModule_Color_RED_str = {25, {'t', 'e', 's', 't', '_', 't', 'e', 's', 't', 'M', 'o', 'd', 'u', 'l', 'e', '_', 'C', 'o', 'l', 'o', 'r', '_', 'R', 'E', 'D', '\0'}};
struct struct_1 test_testModule_Color_GREEN_str = {27, {'t', 'e', 's', 't', '_', 't', 'e', 's', 't', 'M', 'o', 'd', 'u', 'l', 'e', '_', 'C', 'o', 'l', 'o', 'r', '_', 'G', 'R', 'E', 'E', 'N', '\0'}};
struct struct_1 test_testModule_Color_BLUE_str = {26, {'t', 'e', 's', 't', '_', 't', 'e', 's', 't', 'M', 'o', 'd', 'u', 'l', 'e', '_', 'C', 'o', 'l', 'o', 'r', '_', 'B', 'L', 'U', 'E', '\0'}};
struct struct_1* test_testModule_Color_toString(unsigned int x)
{
	switch(x)
	{
	case test_testModule_Color_RED:
		return &test_testModule_Color_RED_str;
	case test_testModule_Color_GREEN:
		return &test_testModule_Color_GREEN_str;
	case test_testModule_Color_BLUE:
		return &test_testModule_Color_BLUE_str;
	}
}
unsigned int test_testModule_Color_length = 3;

/* Function definitions */
signed int test_testModule_main(struct struct_2* _args)
{ /* 169 */
    signed int retval;
    signed int _169_hmm = test_testModule_Color_GREEN;
    retval = 0;
    goto return_block_169;
return_block_169:;
    return retval;
}

int main(int argc, char** argv)
{
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
