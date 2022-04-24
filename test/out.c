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
struct struct_1 string_23 = {23, {'t', 'h', 'e', 'r', 'e', ' ', 'a', 'r', 'e', ' ', 'a', ' ', 'l', 'o', 't', ' ', 'o', 'f', ' ', 'a', 'r', 'g', 's', '\0'}};
struct struct_1 string_24 = {20, {'n', 'o', ' ', 'm', 'e', 's', 's', 'a', 'g', 'e', ' ', 's', 'p', 'e', 'c', 'i', 'f', 'i', 'e', 'd', '\0'}};
struct struct_1 string_25 = {18, {'a', 's', 's', 'e', 'r', 't', 'i', 'o', 'n', ' ', 'f', 'a', 'i', 'l', 'e', 'd', ':', ' ', '\0'}};
struct struct_1 string_28 = {1, {'\n', '\0'}};

/* Enums */

/* Forward global declarations */

/* Forward function declarations */
signed int test_testModule_main(struct struct_2* _args);
void stdlib_debug_assert(bool _predicate, struct struct_1* _msg);
signed int stdlib_system_err(struct struct_1* _format, ...);
signed int stdlib_system_errln(struct struct_1* _format, ...);

#ifndef ORANGE_PROGRAM_23383
#define ORANGE_PROGRAM_23383

/* Enum definitions */

/* Function definitions */
signed int test_testModule_main(struct struct_2* _args)
{ /* 169 */
    signed int retval;
    stdlib_debug_assert(_args->length > 100, &string_23);
    retval = 0;
    goto return_block_169;
return_block_169:;
    return retval;
}

void stdlib_debug_assert(bool _predicate, struct struct_1* _msg)
{ /* 1 */
    if (!_predicate)
    { /* 2 */
        stdlib_system_err(&string_25);
        stdlib_system_errln(_msg);
        exit(1);
    }
}

signed int stdlib_system_err(struct struct_1* _format, ...)
{ /* 26 */
    signed int retval;
    va_list _26_args;
    va_start(_26_args, &_format->data);
    signed int _26_retcode = vfprintf(stderr, &_format->data, _26_args);
    va_end(_26_args);
    retval = _26_retcode;
    goto return_block_26;
return_block_26:;
    return retval;
}

signed int stdlib_system_errln(struct struct_1* _format, ...)
{ /* 27 */
    signed int retval;
    va_list _27_args;
    va_start(_27_args, &_format->data);
    signed int _27_retcode = vfprintf(stderr, &_format->data, _27_args);
    va_end(_27_args);
    struct struct_1* _27_newLine = &string_28;
    printf(&_27_newLine->data);
    retval = _27_retcode;
    goto return_block_27;
return_block_27:;
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
