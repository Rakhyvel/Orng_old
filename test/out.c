/* Code generated using the Orng compiler http://josephs-projects.com */

#ifndef ORNG_22886
#define ORNG_22886

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

/* Debug */
struct list {
	int length;
	char* data[10000];
};

struct list stackTrace;
struct list errorTrace;

void stackTracePrint(struct list* list) {
	for (int i = 0; i < list->length; i++) {
		fprintf(stderr, "%s", list->data[i]);
	}
}

void stackTracePrintReverse(struct list* list) {
	for (int i = list->length - 1; i >= 0; i--) {
		fprintf(stderr, "%s", list->data[i]);
	}
}

void stackTracePush(struct list* list, char* data) {
	if (list->length >= 10000) {
		fprintf(stderr, "error: stack overflow\n");
		stackTracePrintReverse(list);
		exit(1);
	}
	list->data[list->length] = data;
	list->length++;
}

void stackTracePop(struct list* list) {
	list->length--;
}

void stackTraceClear(struct list* list) {
	list->length = 0;
}

char* tagGetFieldName(int tag) {
	switch(tag) {
	case 0:
		return "nothing";
	case 1:
	case 2:
		return "something";
	case 3:
		return "a";
	case 4:
		return "b";
	case 5:
		return "c";
	case 6:
		return "d";
	case 7:
		return "e";
	case 8:
		return "fileNotFound";
	case 9:
		return "resourceBusy";
	case 10:
		return "outOfMemory";
	case 11:
	case 12:
		return "success";
	}
}

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

struct struct_13 {
	int64_t tag;
};

/* Verbatim code */
int std_system_println(struct struct_1 _format, ...) {va_list _25_args;va_start(_25_args, _format.data);int retval = vprintf(_format.data, _25_args);va_end(_25_args);char newLine[2] = {'\n', '\0'};printf(newLine);return retval;}
int std_system_err(struct struct_1 _format, ...) {va_list _25_args;va_start(_25_args, _format.data);int retval = vfprintf(stderr, _format.data, _25_args);va_end(_25_args);char newLine[2] = {'\n', '\0'};return retval;}
int std_system_errln(struct struct_1 _format, ...) {va_list _25_args;va_start(_25_args, _format.data);int retval = vfprintf(stderr, _format.data, _25_args);va_end(_25_args);char newLine[2] = {'\n', '\0'};fprintf(stderr, newLine);return retval;}

/* Function definitions */
struct struct_3 test_testModule_main(struct struct_2 _args);
void std_debug_assert(bool _predicate, struct struct_1 _msg);

struct struct_3 test_testModule_main(struct struct_2 _args)
{
	struct struct_3 retval;
	void (*_0) (bool _predicate, struct struct_1 _msg);
	bool _2;
	struct struct_1 _3;
	int64_t _4;
	struct struct_3 _5;
	struct struct_2 _args_0;
	_args_0 = _args;
L5:; // incoming:1
	_0 = std_debug_assert;
	_2 = 0;
	_3 = (struct struct_1) {19, "this should be true"};
	stackTracePush(&stackTrace, "test/testModule.orng: \n33    | main::(args:[]String)->!() = std.debug.assert(.msg=\"this should be true\", .predicate=false, .lmao=4)\n      |                                              ^\n");
	_0(_2, _3);
	stackTracePop(&stackTrace);
	_4 = 12;
	_5 = (struct struct_3) {_4};
	retval = _5;
	goto end;
end:;
	return retval;
}

void std_debug_assert(bool _predicate, struct struct_1 _msg)
{
	bool _0;
	bool _predicate_0;
	struct struct_1 _msg_0;
	int64_t (*_1) (struct struct_1 _format, ...);
	struct struct_1 _3;
	int64_t _2;
	int64_t (*_4) (struct struct_1 _format, ...);
	int64_t _5;
	struct struct_1 _msg_1;
	_predicate_0 = _predicate;
	_msg_0 = _msg;
L0:; // incoming:1
	_0 = !_predicate_0;
	if (!_0) {
		goto end;
	} else {
		_msg_1 = _msg_0;
		goto L1;
	}
L1:; // incoming:1
	_1 = std_system_err;
	_3 = (struct struct_1) {18, "assertion failed: "};
	stackTracePush(&stackTrace, "std/debug.orng: \n4     | system.err(\"assertion failed: \")\n      |           ^\n");
	_2 = _1(_3);
	stackTracePop(&stackTrace);
	_4 = std_system_errln;
	stackTracePush(&stackTrace, "std/debug.orng: \n5     | system.errln(msg)\n      |             ^\n");
	_5 = _4(_msg_1);
	stackTracePop(&stackTrace);
	fprintf(stderr, "error: unreachable\n");
	stackTracePush(&stackTrace, "std/debug.orng: \n6     | unreachable\n      | ^^^^^^^^^^^\n");
	stackTracePrintReverse(&stackTrace);
	exit(1);
	goto end;
end:;
	return;
}

void pause() {system("pause");}

int main(int argc, char** argv)
{
	atexit(pause);
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
	if (errorTrace.length > 0) {
		fprintf(stderr, "error: %s\n", tagGetFieldName(retval.tag));
	}
	stackTracePrint(&errorTrace);
	return retval.tag != 12;
}
#endif
