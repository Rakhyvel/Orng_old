/* Code generated using the Orng compiler http://josephs-projects.com */

#ifndef ORNG_30031
#define ORNG_30031

/* Includes */
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
	int8_t* data;
};

struct struct_2 {
	int64_t length;
	struct struct_1* data;
};

struct struct_3 {
	int64_t tag;
};

struct struct_4 {
	int64_t length;
	int64_t* data;
};

struct struct_5 {
	int64_t tag;
	union {
		struct struct_6* something;
	};
};

struct struct_6 {
	int64_t val;
	struct struct_5 next;
};

struct struct_7 {
	int64_t length;
	bool* data;
};

struct struct_8 {
	int64_t tag;
	union {
		int64_t c;
	};
};

struct struct_9 {
	int64_t tag;
	union {
		int64_t c;
		int8_t d;
	};
};

struct struct_10 {
	float re;
	float im;
};

struct struct_11 {
	int64_t tag;
	union {
		int64_t success;
	};
};

/* Verbatim code */
int std_system_println(struct struct_1 _format, ...) {va_list _25_args;va_start(_25_args, _format.data);int retval = vprintf(_format.data, _25_args);va_end(_25_args);char newLine[2] = {'\n', '\0'};printf(newLine);return retval;}

/* Function definitions */
int64_t test_testModule_main(struct struct_2 _args);
struct struct_10 test_testModule_Complex_add(struct struct_10 _c1, struct struct_10 _c2);

int64_t test_testModule_main(struct struct_2 _args)
{
	int64_t retval;
	int64_t _1;
	int64_t _2;
	struct struct_10 _159_x_0;
	int64_t _4;
	int64_t _5;
	struct struct_10 _159_y_0;
	struct struct_10 (*_6) (struct struct_10 _c1, struct struct_10 _c2);
	struct struct_10 _7;
	struct struct_2 _args_0;
	_args_0 = _args;
L1:; // incoming:1
	_1 = 0;
	_2 = 3;
	_159_x_0 = (struct struct_10) {_1, _2};
	_4 = 1;
	_5 = 4;
	_159_y_0 = (struct struct_10) {_4, _5};
	_6 = test_testModule_Complex_add;
	printf("test/testModule.orng: \n      |\n37    | z := Complex.add(x, y)\n      |                 ^\n");
	_7 = _6(_159_x_0, _159_y_0);
	retval = 0;
	goto end;
end:;
	return retval;
}

struct struct_10 test_testModule_Complex_add(struct struct_10 _c1, struct struct_10 _c2)
{
	struct struct_10 retval;
	float _1;
	float _2;
	float _3;
	float _4;
	float _5;
	float _6;
	struct struct_10 _c1_0;
	struct struct_10 _c2_0;
	_c1_0 = _c1;
	_c2_0 = _c2;
L0:; // incoming:1
	_1 = _c1_0.re;
	_2 = _c2_0.re;
	_3 = _1 + _2;
	_4 = _c1_0.im;
	_5 = _c2_0.im;
	_6 = _4 + _5;
	retval = (struct struct_10) {_3, _6};
	goto end;
end:;
	return retval;
}

int main(int argc, char** argv)
{
	struct struct_2 args = {argc, calloc(sizeof(struct struct_1) * argc, 1)};
	for (int  i = 0; i < argc; i++) {
		int length = strlen(argv[i]);
		args.data[i] = (struct struct_1){length, calloc(sizeof(char) * length, 1)};
		memcpy(args.data[i].data, argv[i], length);
	}
	int64_t retval = test_testModule_main(args);
	for (int  i = 0; i < argc; i++) {
		free(args.data[i].data);
	}
	free(args.data);
	system("pause");
	return retval;
}
#endif
