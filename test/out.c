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
	signed int z;
	signed int y;
};

struct struct_3* new_struct_3()
{
	struct struct_3* retval = malloc(sizeof(struct struct_3));
	*retval = ((struct struct_3){3, 10});
	return retval;
}

/* Verbatim code */
int stdlib_system_println(struct struct_1* _format, ...) {
    va_list _25_args;
    va_start(_25_args, &_format->data);
    int retval = vprintf(&_format->data, _25_args);
    va_end(_25_args);
    char newLine[2] = {'\n', '\0'};
    printf(newLine);
    return retval;
}

/* Forward string declarations */

/* Enums */

/* Forward global declarations */

/* Forward function and procedure declarations */
signed int test_testModule_main(struct struct_2* _args);

#ifndef ORANGE_PROGRAM_13244
#define ORANGE_PROGRAM_13244

/* String definitions */

/* Enum definitions */

/* Function and procedure definitions */
signed int test_testModule_main(struct struct_2* _args)
{
	signed int retval;
// AST_DEFINE
// test/testModule.orng:3
	struct struct_3* _0 = calloc(sizeof(struct struct_3), 1);
	*_0 = ((struct struct_3){3, 10});
	struct struct_3* _176_x = _0;
// AST_RETURN
// test/testModule.orng:4
	signed int _1 = 0;
	retval = _1;
	goto return_block_176;
return_block_176:;
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
