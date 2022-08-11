/* Code generated using the Orng compiler http://josephs-projects.com */

#ifndef ORNG_8002
#define ORNG_8002

/* Includes */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
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
	int64_t tag;
	union {
		int64_t c;
	};
};

struct struct_5 {
	int64_t tag;
	union {
		int64_t c;
		int8_t d;
	};
};

struct struct_6 {
	float re;
	float im;
};

struct struct_7 {
	int64_t tag;
	union {
		int64_t fileNotFound;
	};
};

struct struct_8 {
	int64_t tag;
	union {
		int64_t success;
		int64_t fileNotFound;
	};
};

struct struct_9 {
	int64_t tag;
	union {
		int64_t fileNotFound;
	};
};

/* Verbatim code */
int std_system_println(struct struct_1 _format, ...) {va_list _25_args;va_start(_25_args, _format.data);int retval = vprintf(_format.data, _25_args);va_end(_25_args);char newLine[2] = {'\n', '\0'};printf(newLine);return retval;}

/* Function definitions */
struct struct_7 test_testModule_main(struct struct_2 _args);
struct struct_8 test_testModule_lol();

struct struct_7 test_testModule_main(struct struct_2 _args)
{
	struct struct_7 retval;
	struct struct_8 (*_1) ();
	struct struct_8 _2;
	int64_t _3;
	int64_t _4;
	bool _5;
	struct struct_2 _args_0;
	int64_t _8;
	struct struct_7 _9;
	_args_0 = _args;
L2:; // incoming:1
	_1 = test_testModule_lol;
	printf("test/testModule.orng: \n      |\n33    | try lol() -- If type does not match for !(), implicit return of success\n      |        ^\n");
	_2 = _1();
	_3 = _2.tag;
	_4 = 10;
	_5 = _3 == _4;
	if (!_5) {
		goto L6;
	} else {
		goto L3;
	}
L3:; // incoming:1
	_8 = 11;
	_9 = (struct struct_7) {_8};
	retval = _9;
	goto end;
L6:; // incoming:1
	retval = *((struct struct_7*) &_2);
	goto end;
end:;
	return retval;
}

struct struct_8 test_testModule_lol()
{
	struct struct_8 retval;
	int64_t _0;
	struct struct_7 _1;
	struct struct_8 _2;
L0:; // incoming:1
	_0 = 7;
	_1 = (struct struct_7) {_0};
	_2 = *((struct struct_8*) &_1);
	retval = _2;
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
	struct struct_7 retval = test_testModule_main(args);
	for (int  i = 0; i < argc; i++) {
		free(args.data[i].data);
	}
	free(args.data);
	system("pause");
	return retval.tag != 11;
}
#endif
