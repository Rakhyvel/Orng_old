/* Code generated using the Orng compiler http://josephs-projects.com */

#ifndef ORNG_23635
#define ORNG_23635

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
	char* data[1000];
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
void test_testModule_recursive(int64_t _x);

struct struct_3 test_testModule_main(struct struct_2 _args)
{
	struct struct_3 retval;
	void (*_0) (int64_t _x);
	int64_t _2;
	int64_t _5;
	bool _6;
	struct struct_2 _args_0;
	struct struct_1 _3;
	int64_t _8;
	int64_t _9;
	struct struct_3 _10;
	struct struct_2 _args_1;
	struct struct_2 _args_2;
	_args_0 = _args;
L1:; // incoming:1
	_0 = test_testModule_recursive;
	_2 = 0;
	_5 = _args_0.length;
	_6 = _2 < _5;
	if (!_6) {
		_args_2 = _args_0;
		goto L6;
	} else {
		_args_1 = _args_0;
		goto L4;
	}
L4:; // incoming:2
	_3 = _args_1.data[_2];
	_8 = _3.length;
	if ((&stackTrace)->length >= 1000) {
		fprintf(stderr, "error: stack overflow\n");
		stackTracePrintReverse((&stackTrace));
		exit(1);
	}
	(&stackTrace)->data[(&stackTrace)->length++] = "test/testModule.orng: \n33    | main::(args:[]String)->!() = recursive(args[0].length)\n      |                                       ^\n";
	_0(_8);
	stackTrace.length--;
	_9 = 12;
	_10 = (struct struct_3) {_9};
	retval = _10;
	goto end;
L6:; // incoming:1
	fprintf(stderr, "error: array index greater than array length\n");
	if ((&errorTrace)->length >= 1000) {
		fprintf(stderr, "error: stack overflow\n");
		stackTracePrintReverse((&errorTrace));
		exit(1);
	}
	(&errorTrace)->data[(&errorTrace)->length++] = "test/testModule.orng: \n33    | main::(args:[]String)->!() = recursive(args[0].length)\n      |                                            ^\n";
	stackTracePrintReverse(&stackTrace);
	exit(1);
	_args_1 = _args_2;
	goto L4;
end:;
	return retval;
}

void test_testModule_recursive(int64_t _x)
{
	void (*_0) (int64_t _x);
	int64_t _2;
	int64_t _3;
	int64_t _x_0;
	_x_0 = _x;
L0:; // incoming:1
	_0 = test_testModule_recursive;
	_2 = 1;
	_3 = _x_0 + _2;
	if ((&stackTrace)->length >= 1000) {
		fprintf(stderr, "error: stack overflow\n");
		stackTracePrintReverse((&stackTrace));
		exit(1);
	}
	(&stackTrace)->data[(&stackTrace)->length++] = "test/testModule.orng: \n31    | recursive::(x:Int)->() = recursive(x+1)\n      |                                   ^\n";
	_0(_3);
	stackTrace.length--;
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
