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
	int64_t tag;
	union {
		struct struct_7* something;
	};
};

struct struct_7 {
	int64_t val;
	struct struct_6 next;
};

struct struct_8 {
	int64_t length;
	bool* data;
};

struct struct_9 {
	int64_t length;
	int64_t* data;
};

/* Verbatim code */
int std_system_println(struct struct_1 _format, ...) {va_list _25_args;va_start(_25_args, _format.data);int retval = vprintf(_format.data, _25_args);va_end(_25_args);char newLine[2] = {'\n', '\0'};printf(newLine);return retval;}

int64_t test_testModule_main(struct struct_2 _args);
struct struct_1 test_leetcode_fizzbuzz(int64_t _n);
struct struct_1 std_string_format(int64_t _n, struct struct_1 _f, ...);

#ifndef ORANGE_PROGRAM_6583
#define ORANGE_PROGRAM_6583

int64_t test_testModule_main(struct struct_2 _args)
{
	int64_t retval;
	int64_t (*_0) (struct struct_1 _format, ...);
	struct struct_1 _2;
	struct struct_1 (*_3) (int64_t _n);
	int64_t _5;
	struct struct_1 _4;
	int64_t _1;
	struct struct_2 _args_0;
	_args_0 = _args;
L16:; // incoming:1
	_0 = std_system_println;
	_2 = (struct struct_1) {2, "%s"};
	_3 = test_leetcode_fizzbuzz;
	_5 = _args_0.length;
	_4 = _3(_5);
	_1 = _0(_2, _4);
	retval = _1;
	goto end;
end:;
	return retval;
}

struct struct_1 test_leetcode_fizzbuzz(int64_t _n)
{
	struct struct_1 retval;
	struct struct_1 _0;
	int64_t _1;
	int64_t _2;
	int64_t _3;
	bool _4;
	int64_t _n_0;
	struct struct_1 _5;
	struct struct_1 _7;
	int64_t _8;
	int64_t _9;
	int64_t _10;
	bool _11;
	int64_t _n_1;
	struct struct_1 _12;
	struct struct_1 _14;
	int64_t _15;
	int64_t _16;
	int64_t _17;
	bool _18;
	int64_t _n_2;
	struct struct_1 _19;
	struct struct_1 (*_21) (int64_t _n, struct struct_1 _f, ...);
	int64_t _23;
	struct struct_1 _24;
	struct struct_1 _22;
	int64_t _n_3;
	_n_0 = _n;
L2:; // incoming:1
	_1 = 15;
	_2 = _n_0 % _1;
	_3 = 0;
	_4 = _2 == _3;
	if (!_4) {
		_n_1 = _n_0;
		goto L6;
	} else {
		goto L3;
	}
L3:; // incoming:1
	_5 = (struct struct_1) {8, "fizzbuzz"};
	_0 = _5;
	goto L5;
L5:; // incoming:2
	retval = _0;
	goto end;
L6:; // incoming:1
	_8 = 3;
	_9 = _n_1 % _8;
	_10 = 0;
	_11 = _9 == _10;
	if (!_11) {
		_n_2 = _n_1;
		goto L10;
	} else {
		goto L7;
	}
L7:; // incoming:1
	_12 = (struct struct_1) {4, "fizz"};
	_7 = _12;
	goto L9;
L9:; // incoming:2
	_0 = _7;
	goto L5;
L10:; // incoming:1
	_15 = 5;
	_16 = _n_2 % _15;
	_17 = 0;
	_18 = _16 == _17;
	if (!_18) {
		_n_3 = _n_2;
		goto L14;
	} else {
		goto L11;
	}
L11:; // incoming:1
	_19 = (struct struct_1) {4, "buzz"};
	_14 = _19;
	goto L13;
L13:; // incoming:2
	_7 = _14;
	goto L9;
L14:; // incoming:1
	_21 = std_string_format;
	_23 = 255;
	_24 = (struct struct_1) {2, "%d"};
	_22 = _21(_23, _24, _n_3);
	_14 = _22;
	goto L13;
end:;
	return retval;
}

struct struct_1 std_string_format(int64_t _n, struct struct_1 _f, ...)
{
	struct struct_1 retval;
	int8_t _1;
	struct struct_1 _0;
	struct struct_1 _28_retval_0;
	int64_t (*_2) (int8_t* _str, int8_t* _f, ...);
	int8_t* _4;
	int8_t* _5;
	int64_t _3;
	int64_t _n_0;
	struct struct_1 _f_0;
	_n_0 = _n;
	_f_0 = _f;
L0:; // incoming:1
	_1 = 0;
	_0 = (struct struct_1) {_n_0, malloc(sizeof(int8_t) * _n_0)}; for (int i_n_0 = 0; i_n_0 < _n_0; i_n_0++) {_0.data[i_n_0] = _1;}
	_28_retval_0 = _0;
	_2 = sprintf;
	_4 = _28_retval_0.data;
	_5 = _f_0.data;
	_3 = _2(_4, _5);
	retval = _0;
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
