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
	int64_t length;
	int64_t* data;
};

struct struct_4 {
	int64_t length;
	int64_t* data;
};

struct struct_5 {
	int64_t length;
	int8_t* data;
};

struct struct_6 {
	int64_t length;
	bool* data;
};

struct struct_7 {
	int64_t length;
	int64_t* data;
};

struct struct_8 {
	int64_t tag;
	union {
		struct struct_9* something;
	};
};

struct struct_9 {
	int64_t val;
	struct struct_8 next;
};

struct struct_10 {
	int64_t tag;
};

/* Verbatim code */
int std_system_println(struct struct_1 _format, ...) {va_list _25_args;va_start(_25_args, _format.data);int retval = vprintf(_format.data, _25_args);va_end(_25_args);char newLine[2] = {'\n', '\0'};printf(newLine);return retval;}

int64_t test_testModule_main(struct struct_2 _args);
struct struct_10 test_testModule_testFn();

#ifndef ORANGE_PROGRAM_16910
#define ORANGE_PROGRAM_16910

int64_t test_testModule_main(struct struct_2 _args)
{
	int64_t retval;
	struct struct_10 (*_0) ();
	struct struct_10 _1;
	struct struct_10 _156_lol_0;
	int64_t _2;
	int64_t _3;
	int64_t _4;
	bool _5;
	struct struct_2 _args_0;
	_args_0 = _args;
L1:; // incoming:1
	_0 = test_testModule_testFn;
	_1 = _0();
	_156_lol_0 = _1;
	_3 = _156_lol_0.tag;
	_4 = 3;
	_5 = _3 != _4;
	if (!_5) {
		goto L7;
	} else {
		goto L3;
	}
L3:; // incoming:1
	_2 = 5;
	goto L5;
L5:; // incoming:2
	retval = _2;
	goto end;
L7:; // incoming:1
	_2 = 0;
	goto L5;
end:;
	return retval;
}

struct struct_10 test_testModule_testFn()
{
	struct struct_10 retval;
	int64_t _0;
L0:; // incoming:1
	_0 = 2;
	retval = (struct struct_10) {_0};
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
