/* Code generated using the Orng compiler http://josephs-projects.com */

#ifndef ORNG_9514
#define ORNG_9514

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
		int64_t success;
		int64_t fileNotFound;
	};
};

/* Verbatim code */
int std_system_println(struct struct_1 _format, ...) {va_list _25_args;va_start(_25_args, _format.data);int retval = vprintf(_format.data, _25_args);va_end(_25_args);char newLine[2] = {'\n', '\0'};printf(newLine);return retval;}

/* Function definitions */
int64_t test_testModule_main(struct struct_2 _args);
struct struct_12 test_testModule_hmm();
struct struct_11 test_testModule_givesAnError();

int64_t test_testModule_main(struct struct_2 _args)
{
	int64_t retval;
	int64_t _0;
	struct struct_12 (*_1) ();
	struct struct_12 _2;
	int64_t _3;
	int64_t _4;
	bool _5;
	struct struct_2 _args_0;
	int64_t _6;
	_args_0 = _args;
L4:; // incoming:1
	_1 = test_testModule_hmm;
	printf("test/testModule.orng: \n      |\n32    | main::(args:[]String)->Int = hmm() catch 0\n      |                                  ^\n");
	_2 = _1();
	_3 = _2.tag;
	_4 = 11;
	_5 = _3 == _4;
	if (!_5) {
		goto L7;
	} else {
		goto L5;
	}
L5:; // incoming:1
	_6 = _2.success;
	_0 = _6;
	goto L6;
L6:; // incoming:2
	retval = _0;
	goto end;
L7:; // incoming:1
	_0 = 0;
	goto L6;
end:;
	return retval;
}

struct struct_12 test_testModule_hmm()
{
	struct struct_12 retval;
	struct struct_11 (*_0) ();
	struct struct_11 _1;
	struct struct_12 _2;
	struct struct_12 _156_x_0;
	int64_t _3;
	int64_t _4;
	bool _5;
	int64_t (*_6) (struct struct_1 _format, ...);
	struct struct_1 _8;
	int64_t _7;
L1:; // incoming:1
	_0 = test_testModule_givesAnError;
	printf("test/testModule.orng: \n      |\n27    | x:FileError||AllocationError!Int = givesAnError()\n      |                                                ^\n");
	_1 = _0();
	_2 = *((struct struct_12*) &_1);
	_156_x_0 = _2;
	retval = _2;
	_3 = _156_x_0.tag;
	_4 = 11;
	_5 = _3 == _4;
	if (!_5) {
		goto L3;
	} else {
		goto end;
	}
L3:; // incoming:1
	_6 = std_system_println;
	_8 = (struct struct_1) {4, "hmm2"};
	printf("test/testModule.orng: \n      |\n26    | errdefer std.system.println(\"hmm2\")\n      |                            ^\n");
	_7 = _6(_8);
	goto end;
end:;
	return retval;
}

struct struct_11 test_testModule_givesAnError()
{
	struct struct_11 retval;
	int64_t _0;
	struct struct_11 _1;
L0:; // incoming:1
	_0 = 8;
	_1 = (struct struct_11) {_0};
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
	int64_t retval = test_testModule_main(args);
	for (int  i = 0; i < argc; i++) {
		free(args.data[i].data);
	}
	free(args.data);
	system("pause");
	return retval;
}
#endif
