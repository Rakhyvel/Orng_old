/* Code generated using Orange Translator http://josephs-projects.com */

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
	int64_t tag;
	union {
		int64_t success;
	};
};

/* Verbatim code */
int std_system_println(struct struct_1 _format, ...) {va_list _25_args;va_start(_25_args, _format.data);int retval = vprintf(_format.data, _25_args);va_end(_25_args);char newLine[2] = {'\n', '\0'};printf(newLine);return retval;}

int64_t test_testModule_main(struct struct_2 _args);
struct struct_10 test_testModule_givesAnError(struct struct_1 _filename);

#ifndef ORANGE_PROGRAM_16333
#define ORANGE_PROGRAM_16333

int64_t test_testModule_main(struct struct_2 _args)
{
	int64_t retval;
	int64_t _0;
	struct struct_10 (*_1) (struct struct_1 _filename);
	struct struct_1 _3;
	struct struct_10 _2;
	int64_t _4;
	int64_t _5;
	bool _6;
	struct struct_2 _args_0;
	int64_t _7;
	_args_0 = _args;
L6:; // incoming:1
	_1 = test_testModule_givesAnError;
	_3 = (struct struct_1) {5, "Hello"};
	_2 = _1(_3);
	_4 = _2.tag;
	_5 = 11;
	_6 = _4 == _5;
	if (!_6) {
		goto L9;
	} else {
		goto L7;
	}
L7:; // incoming:1
	_7 = _2.success;
	_0 = _7;
	goto L8;
L8:; // incoming:2
	retval = _0;
	goto end;
L9:; // incoming:1
	_0 = 0;
	goto L8;
end:;
	return retval;
}

struct struct_10 test_testModule_givesAnError(struct struct_1 _filename)
{
	struct struct_10 retval;
	int64_t (*_0) (struct struct_1 _format, ...);
	struct struct_1 _2;
	int64_t _1;
	int64_t _12;
	struct struct_3 _156_anError_0;
	int64_t _14;
	int64_t _15;
	bool _16;
	struct struct_1 _filename_0;
	int64_t (*_17) (struct struct_1 _format, ...);
	struct struct_1 _19;
	int64_t _18;
	int64_t (*_20) (struct struct_1 _format, ...);
	struct struct_1 _22;
	int64_t _21;
	_filename_0 = _filename;
L1:; // incoming:1
	_0 = std_system_println;
	_2 = (struct struct_1) {3, "Two"};
	_1 = _0(_2);
	_12 = 8;
	_156_anError_0 = (struct struct_3) {_12};
	retval = (struct struct_10) {_12};
	_14 = _156_anError_0.tag;
	_15 = 11;
	_16 = _14 == _15;
	if (!_16) {
		goto L4;
	} else {
		goto end;
	}
L4:; // incoming:1
	_17 = std_system_println;
	_19 = (struct struct_1) {3, "One"};
	_18 = _17(_19);
	_20 = std_system_println;
	_22 = (struct struct_1) {5, "Three"};
	_21 = _20(_22);
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
