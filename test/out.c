/* Code generated using the Orng compiler http://josephs-projects.com */

#ifndef ORNG_15085
#define ORNG_15085

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
		int64_t fileNotFound;
	};
};

struct struct_12 {
	int64_t tag;
	union {
		int64_t fileNotFound;
	};
};

struct struct_13 {
	int64_t tag;
	union {
		int64_t success;
		int64_t fileNotFound;
	};
};

/* Verbatim code */
int std_system_println(struct struct_1 _format, ...) {va_list _25_args;va_start(_25_args, _format.data);int retval = vprintf(_format.data, _25_args);va_end(_25_args);char newLine[2] = {'\n', '\0'};printf(newLine);return retval;}

/* Function definitions */
int64_t test_testModule_main(struct struct_2 _args);
struct struct_13 test_testModule_hmm(int64_t _x);
struct struct_11 test_testModule_givesAnError();

int64_t test_testModule_main(struct struct_2 _args)
{
	int64_t retval;
	int64_t _0;
	struct struct_13 (*_1) (int64_t _x);
	int64_t _3;
	struct struct_13 _2;
	int64_t _4;
	int64_t _5;
	bool _6;
	struct struct_2 _args_0;
	int64_t _7;
	_args_0 = _args;
L7:; // incoming:1
	_1 = test_testModule_hmm;
	_3 = 5;
	printf("test/testModule.orng: \n      |\n38    | main::(args:[]String)->Int = hmm(5) catch 0\n      |                                 ^\n");
	_2 = _1(_3);
	_4 = _2.tag;
	_5 = 12;
	_6 = _4 == _5;
	if (!_6) {
		goto L10;
	} else {
		goto L8;
	}
L8:; // incoming:1
	_7 = _2.success;
	_0 = _7;
	goto L9;
L9:; // incoming:2
	retval = _0;
	goto end;
L10:; // incoming:1
	_0 = 0;
	goto L9;
end:;
	return retval;
}

struct struct_13 test_testModule_hmm(int64_t _x)
{
	struct struct_13 retval;
	int64_t _1;
	bool _2;
	int64_t _x_0;
	struct struct_13 (*_3) (int64_t _x);
	int64_t _5;
	int64_t _6;
	struct struct_13 _4;
	int64_t _7;
	int64_t _8;
	bool _9;
	int64_t _x_1;
	int64_t (*_20) (struct struct_1 _format, ...);
	struct struct_1 _22;
	int64_t _21;
	struct struct_11 (*_10) ();
	struct struct_11 _11;
	struct struct_13 _12;
	int64_t _13;
	int64_t _14;
	bool _15;
	_x_0 = _x;
L1:; // incoming:1
	_1 = 0;
	_2 = _x_0 > _1;
	if (!_2) {
		goto L5;
	} else {
		_x_1 = _x_0;
		goto L2;
	}
L2:; // incoming:1
	_3 = test_testModule_hmm;
	_5 = 1;
	_6 = _x_1 - _5;
	printf("test/testModule.orng: \n      |\n32    | return hmm(x-1)\n      |           ^\n");
	_4 = _3(_6);
	retval = _4;
	_7 = _4.tag;
	_8 = 12;
	_9 = _7 == _8;
	if (!_9) {
		goto L4;
	} else {
		goto end;
	}
L4:; // incoming:2
	_20 = std_system_println;
	_22 = (struct struct_1) {5, "Gone!"};
	printf("test/testModule.orng: \n      |\n30    | errdefer std.system.println(\"Gone!\")\n      |                            ^\n");
	_21 = _20(_22);
	goto end;
L5:; // incoming:1
	_10 = test_testModule_givesAnError;
	printf("test/testModule.orng: \n      |\n34    | return givesAnError()\n      |                    ^\n");
	_11 = _10();
	_12 = *((struct struct_13*) &_11);
	retval = _12;
	_13 = _12.tag;
	_14 = 12;
	_15 = _13 == _14;
	if (!_15) {
		goto L4;
	} else {
		goto end;
	}
end:;
	return retval;
}

struct struct_11 test_testModule_givesAnError()
{
	struct struct_11 retval;
	int64_t _0;
	struct struct_11 _1;
	struct struct_11 _2;
L0:; // incoming:1
	_0 = 8;
	_1 = (struct struct_11) {_0};
	_2 = *((struct struct_11*) &_1);
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
	int64_t retval = test_testModule_main(args);
	for (int  i = 0; i < argc; i++) {
		free(args.data[i].data);
	}
	free(args.data);
	system("pause");
	return retval;
}
#endif
