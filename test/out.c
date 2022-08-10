/* Code generated using the Orng compiler http://josephs-projects.com */

#ifndef ORNG_1708
#define ORNG_1708

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
};

/* Verbatim code */
int std_system_println(struct struct_1 _format, ...) {va_list _25_args;va_start(_25_args, _format.data);int retval = vprintf(_format.data, _25_args);va_end(_25_args);char newLine[2] = {'\n', '\0'};printf(newLine);return retval;}

/* Function definitions */
struct struct_3 test_testModule_main(struct struct_2 _args);
int64_t test_testModule_hmm();

struct struct_3 test_testModule_main(struct struct_2 _args)
{
	struct struct_3 retval;
	int64_t _0;
	int64_t (*_1) ();
	int64_t _2;
	struct struct_3 _3;
	struct struct_2 _args_0;
	_args_0 = _args;
L2:; // incoming:1
	_0 = 10;
	_1 = test_testModule_hmm;
	printf("test/testModule.orng: \n      |\n31    | main::(args:[]String)->!() = hmm()\n      |                                 ^\n");
	_2 = _1();
	_3 = (struct struct_3) {_0};
	retval = _3;
	goto end;
end:;
	return retval;
}

int64_t test_testModule_hmm()
{
	int64_t retval;
	int64_t (*_0) ();
	int64_t _1;
L0:; // incoming:1
	_0 = test_testModule_hmm;
	printf("test/testModule.orng: \n      |\n28    | hmm()\n      |    ^\n");
	_1 = _0();
	retval = _1;
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
	struct struct_3 retval = test_testModule_main(args);
	for (int  i = 0; i < argc; i++) {
		free(args.data[i].data);
	}
	free(args.data);
	system("pause");
	return retval.tag != 10;
}
#endif
