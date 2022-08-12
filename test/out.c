/* Code generated using the Orng compiler http://josephs-projects.com */

#ifndef ORNG_29911
#define ORNG_29911

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

struct struct_3 test_testModule_main(struct struct_2 _args)
{
	struct struct_3 retval;
	int64_t _0;
	struct struct_9 _1;
	struct struct_9 _137__enum_0;
	int8_t _2;
	int64_t _3;
	int64_t (*_5) (struct struct_1 _format, ...);
	struct struct_1 _7;
	int64_t _9;
	int64_t _10;
	bool _11;
	struct struct_2 _args_0;
	struct struct_9 _137__enum_1;
	int8_t _8;
	int64_t _6;
	int64_t _14;
	struct struct_3 _15;
	struct struct_9 _137__enum_2;
	_args_0 = _args;
L0:; // incoming:1
	_0 = 5;
	_1 = (struct struct_9) {_0};
	_137__enum_0 = _1;
	_2 = 65;
	_3 = (int64_t) _2;
	_137__enum_0.c = _3;
	_5 = std_system_println;
	_7 = (struct struct_1) {2, "%c"};
	_9 = _137__enum_0.tag;
	_10 = 6;
	_11 = _9 != _10;
	if (!_11) {
		_137__enum_2 = _137__enum_0;
		goto L2;
	} else {
		_137__enum_1 = _137__enum_0;
		goto L1;
	}
L1:; // incoming:1
	fprintf(stderr, "error: field not active\n");
	if ((&stackTrace)->length >= 1000) {
		fprintf(stderr, "error: stack overflow\n");
		stackTracePrintReverse((&stackTrace));
		exit(1);
	}
	(&stackTrace)->data[(&stackTrace)->length++] = "test/testModule.orng: \n34    | std.system.println(\"%c\", enum.d)\n      |                               ^\n";
	stackTracePrintReverse(&stackTrace);
	exit(1);
	_137__enum_2 = _137__enum_1;
	goto L2;
L2:; // incoming:2
	_8 = _137__enum_2.d;
	if ((&stackTrace)->length >= 1000) {
		fprintf(stderr, "error: stack overflow\n");
		stackTracePrintReverse((&stackTrace));
		exit(1);
	}
	(&stackTrace)->data[(&stackTrace)->length++] = "test/testModule.orng: \n34    | std.system.println(\"%c\", enum.d)\n      |                   ^\n";
	_6 = _5(_7, _8);
	stackTrace.length--;
	_14 = 12;
	_15 = (struct struct_3) {_14};
	retval = _15;
	goto end;
end:;
	return retval;
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
