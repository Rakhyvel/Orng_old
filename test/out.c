/* Code generated using the Orng compiler http://josephs-projects.com */

#ifndef ORNG_26260
#define ORNG_26260

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
	int capacity;
	char** data;
};

struct list stackTrace;

void stackTraceInit() {
	stackTrace.length = 0;
	stackTrace.capacity = 10;
	stackTrace.data = malloc(sizeof(char*) * stackTrace.capacity);
}

void stackTracePush(char* data) {
	if (stackTrace.length >= stackTrace.capacity) {
		stackTrace.capacity *= 2;
		stackTrace.data = realloc(stackTrace.data, stackTrace.capacity);
	}
	stackTrace.data[stackTrace.length] = data;
	stackTrace.length++;
}

void stackTraceClear() {
	stackTrace.length = 0;
}

void stackTracePrint() {
	for (int i = 0; i < stackTrace.length; i++) {
		printf("%s", stackTrace.data[i]);
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
	union {
		int64_t success;
		int64_t fileNotFound;
	};
};

struct struct_9 {
	int64_t tag;
	union {
		int64_t fileNotFound;
	};
};

/* Verbatim code */
int std_system_println(struct struct_1 _format, ...) {va_list _25_args;va_start(_25_args, _format.data);int retval = vprintf(_format.data, _25_args);va_end(_25_args);char newLine[2] = {'\n', '\0'};printf(newLine);return retval;}

/* Function definitions */
struct struct_7 test_testModule_main(struct struct_2 _args);
struct struct_8 test_testModule_lol(int64_t _x);

struct struct_7 test_testModule_main(struct struct_2 _args)
{
	struct struct_7 retval;
	struct struct_8 (*_1) (int64_t _x);
	int64_t _3;
	struct struct_8 _2;
	int64_t _4;
	int64_t _5;
	bool _6;
	struct struct_2 _args_0;
	int64_t _7;
	int64_t _8;
	bool _9;
	struct struct_8 (*_12) (int64_t _x);
	int64_t _14;
	struct struct_8 _13;
	int64_t _15;
	int64_t _16;
	bool _17;
	int64_t _18;
	int64_t _19;
	bool _20;
	int64_t (*_23) (struct struct_1 _format, ...);
	struct struct_1 _25;
	int64_t _24;
	int64_t _35;
	struct struct_7 _36;
	int64_t (*_32) (struct struct_1 _format, ...);
	struct struct_1 _34;
	int64_t _33;
	_args_0 = _args;
L3:; // incoming:1
	_1 = test_testModule_lol;
	_3 = 3;
	_2 = _1(_3);
	_4 = _2.tag;
	_5 = 10;
	_6 = _4 != _5;
	if (!_6) {
		goto L18;
	} else {
		goto L4;
	}
L4:; // incoming:1
	stackTracePush("test/testModule.orng: \n      |\n37    | try lol(3)\n      |        ^\n");
	goto L5;
L5:; // incoming:2
	_7 = _2.tag;
	_8 = 10;
	_9 = _7 == _8;
	if (!_9) {
		goto L17;
	} else {
		goto L6;
	}
L6:; // incoming:1
	_12 = test_testModule_lol;
	_14 = 5;
	_13 = _12(_14);
	_15 = _13.tag;
	_16 = 10;
	_17 = _15 != _16;
	if (!_17) {
		goto L16;
	} else {
		goto L8;
	}
L8:; // incoming:1
	stackTracePush("test/testModule.orng: \n      |\n39    | try lol(5)\n      |        ^\n");
	goto L9;
L9:; // incoming:2
	_18 = _13.tag;
	_19 = 10;
	_20 = _18 == _19;
	if (!_20) {
		goto L14;
	} else {
		goto L10;
	}
L10:; // incoming:1
	_23 = std_system_println;
	_25 = (struct struct_1) {6, "Hello!"};
	_24 = _23(_25);
	_35 = 11;
	_36 = (struct struct_7) {_35};
	retval = _36;
	goto end;
L14:; // incoming:1
	retval = *((struct struct_7*) &_13);
	_32 = std_system_println;
	_34 = (struct struct_1) {6, "Hello!"};
	_33 = _32(_34);
	goto end;
L16:; // incoming:1
	stackTraceClear;
	goto L9;
L17:; // incoming:1
	retval = *((struct struct_7*) &_2);
	goto end;
L18:; // incoming:1
	stackTraceClear;
	goto L5;
end:;
	return retval;
}

struct struct_8 test_testModule_lol(int64_t _x)
{
	struct struct_8 retval;
	int64_t _2;
	bool _1;
	int64_t _x_0;
	int64_t _3;
	struct struct_7 _4;
	struct struct_8 _5;
	int64_t _6;
	struct struct_8 _7;
	int64_t _x_1;
	_x_0 = _x;
L0:; // incoming:1
	_2 = 0;
	_1 = _x_0 == _2;
	if (!_1) {
		_x_1 = _x_0;
		goto L2;
	} else {
		goto L1;
	}
L1:; // incoming:1
	_3 = 7;
	_4 = (struct struct_7) {_3};
	_5 = *((struct struct_8*) &_4);
	retval = _5;
	goto end;
L2:; // incoming:1
	_6 = 10;
	_7 = (struct struct_8) {_6, _x_1};
	retval = _7;
	goto end;
end:;
	return retval;
}

int main(int argc, char** argv)
{
	stackTraceInit();
	struct struct_2 args = {argc, calloc(sizeof(struct struct_1) * argc, 1)};
	for (int  i = 0; i < argc; i++) {
		int length = strlen(argv[i]);
		args.data[i] = (struct struct_1){length, calloc(sizeof(char) * length, 1)};
		memcpy(args.data[i].data, argv[i], length);
	}
	struct struct_7 retval = test_testModule_main(args);
	for (int  i = 0; i < argc; i++) {
		free(args.data[i].data);
	}
	free(args.data);
	stackTracePrint();
	system("pause");
	return retval.tag != 11;
}
#endif
