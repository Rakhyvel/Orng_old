/* Code generated using Orange Translator http://josephs-projects.com */

/* Includes used by the program */
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Struct definitions */
struct struct_1 {
	int64_t length;
	int8_t data[];
};

struct struct_2 {
	int64_t length;
	struct struct_1* data[];
};

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
struct struct_1 string_23;

/* Enums */

/* Forward global declarations */

/* Forward function and procedure declarations */
int64_t test_testModule_main(struct struct_2* _args);

#ifndef ORANGE_PROGRAM_15061
#define ORANGE_PROGRAM_15061

/* String definitions */
struct struct_1 string_23 = {4, {'h', 'a', 'h', 'a', '\0'}};

/* Enum definitions */

/* Function and procedure definitions */
int64_t test_testModule_main(struct struct_2* _args)
{
	int64_t retval;
	int32_t _0;
// AST_SWITCH
// test/testModule.orng:3
	switch (3)
	{
	case 3:
	{
	int defer_0 = 0;
// AST_DEFER
// test/testModule.orng:5
	defer_0 = 1;
// AST_BREAK
// test/testModule.orng:6
	goto break_defer_176;
	goto continue_176;
break_defer_176:;
	if (defer_0) {
	struct struct_1* _1 = &string_23;
	int64_t _2 = stdlib_system_println(_1);
	}
	goto end_176;
continue_176:;
	if (defer_0) {
	struct struct_1* _3 = &string_23;
	int64_t _4 = stdlib_system_println(_3);
	}
end_176:;
	break;
	}
	default:
	{
// AST_BREAK
// test/testModule.orng:9
	goto end_177;
end_177:;
	break;
	}
	}
// AST_INT
// test/testModule.orng:11
	int32_t _5 = 0;
	_0 = _5;
	retval = _0;
return_block_175:;
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
