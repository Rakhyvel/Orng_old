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
struct struct_10 test_testModule_hmm();
struct struct_10 test_testModule_givesAnError(struct struct_1 _filename);

#ifndef ORANGE_PROGRAM_711
#define ORANGE_PROGRAM_711

int64_t test_testModule_main(struct struct_2 _args)
{
	int64_t retval;
	int64_t _0;
	struct struct_10 (*_1) ();
	struct struct_10 _2;
	int64_t _3;
	int64_t _4;
	bool _5;
	struct struct_2 _args_0;
	int64_t _6;
	_args_0 = _args;
L5:; // incoming:1
	_1 = test_testModule_hmm;
	_2 = _1();
	_3 = _2.tag;
	_4 = 11;
	_5 = _3 == _4;
	if (!_5) {
		goto L8;
	} else {
		goto L6;
	}
L6:; // incoming:1
	_6 = _2.success;
	_0 = _6;
	goto L7;
L7:; // incoming:2
	retval = _0;
	goto end;
L8:; // incoming:1
	_0 = 0;
	goto L7;
end:;
	return retval;
}

struct struct_10 test_testModule_hmm()
{
	struct struct_10 retval;
	int64_t _0;
	struct struct_10 (*_2) (struct struct_1 _filename);
	struct struct_1 _4;
	struct struct_10 _3;
	int64_t _5;
	int64_t _6;
	bool _7;
	int64_t _8;
	int64_t _1;
L1:; // incoming:1
	_0 = 11;
	_2 = test_testModule_givesAnError;
	_4 = (struct struct_1) {10, "Hello!.txt"};
	_3 = _2(_4);
	_5 = _3.tag;
	_6 = 11;
	_7 = _5 == _6;
	if (!_7) {
		goto L4;
	} else {
		goto L2;
	}
L2:; // incoming:1
	_8 = _3.success;
	_1 = _8;
	retval = (struct struct_10) {_0, _1};
	goto end;
L4:; // incoming:1
	retval = _3;
	goto end;
end:;
	return retval;
}

struct struct_10 test_testModule_givesAnError(struct struct_1 _filename)
{
	struct struct_10 retval;
	int64_t _0;
	struct struct_1 _filename_0;
	_filename_0 = _filename;
L0:; // incoming:1
	_0 = 8;
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
