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
	signed int x;
};

struct struct_3* new_struct_3()
{
	struct struct_3* retval = malloc(sizeof(struct struct_3));
	*retval = ((struct struct_3){0, });
	return retval;
}

struct struct_4 {
	signed int length;
	struct struct_3* data[4];
};

struct struct_4* new_struct_4(int count)
{
	struct struct_4* retval = malloc(sizeof(signed int) + sizeof(struct struct_3*) * count);
	for(int i = 0; i < count; i++) {
		retval->data[i] = 0;
	}
	retval->length = count;
	return retval;
}

/* Forward string declarations */
struct struct_1 string_23;
struct struct_1 string_24;
struct struct_1 string_25;
struct struct_1 string_26;
struct struct_1 string_30;

/* Enums */

/* Forward global declarations */

/* Forward function and procedure declarations */
signed int test_testModule_main(struct struct_2* _args);
void test_testModule_MyType_print(struct struct_3* _self, struct struct_1* _prefix1, struct struct_1* _prefx2);
signed int stdlib_system_println(struct struct_1* _format, ...);

#ifndef ORANGE_PROGRAM_12695
#define ORANGE_PROGRAM_12695

/* String definitions */
struct struct_1 string_23 = {14, {'s', 'e', 'l', 'f', ' ', 'w', 'a', 's', ' ', 'n', 'u', 'l', 'l', '!', '\0'}};
struct struct_1 string_24 = {2, {'%', 'd', '\0'}};
struct struct_1 string_25 = {0, {'\0'}};
struct struct_1 string_26 = {0, {'\0'}};
struct struct_1 string_30 = {1, {'\n', '\0'}};

/* Enum definitions */

/* Function and procedure definitions */
signed int test_testModule_main(struct struct_2* _args)
{ /* 180 */
    signed int retval;
    struct struct_4 _180_arr = ((struct struct_4){4, 0, 0, 0, 0});
    test_testModule_MyType_print(_180_arr.data[3], &string_25, &string_26);
    retval = 0;
    goto return_block_180;
return_block_180:;
    return retval;
}

void test_testModule_MyType_print(struct struct_3* _self, struct struct_1* _prefix1, struct struct_1* _prefx2)
{ /* 177 */
    if (_self == 0)
    { /* 178 */
        stdlib_system_println(&string_23);
    }
    else
    { /* 179 */
        stdlib_system_println(&string_24, _self->x);
    }
}

signed int stdlib_system_println(struct struct_1* _format, ...)
{ /* 25 */
    signed int retval;
    va_list _25_args;
    va_start(_25_args, &_format->data);
    signed int _25_retcode = vprintf(&_format->data, _25_args);
    va_end(_25_args);
    struct struct_1* _25_newLine = &string_30;
    printf(&_25_newLine->data);
    retval = _25_retcode;
    goto return_block_25;
return_block_25:;
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
