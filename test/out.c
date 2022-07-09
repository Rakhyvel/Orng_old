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

int64_t test_testModule_main(struct struct_2 _args);
struct struct_3 test_testModule_twoSum(struct struct_3 _numArg, int64_t _targetArg);

#ifndef ORANGE_PROGRAM_17282
#define ORANGE_PROGRAM_17282

int64_t test_testModule_main(struct struct_2 _args)
{
	int64_t retval;
	register int64_t _1;
	register int64_t _2;
	register int64_t _3;
	register int64_t _4;
	register struct struct_3 _158_nums_0;
	register int64_t _158_target_0;
	register struct struct_3 (*_6) (struct struct_3 _numArg, int64_t _targetArg);
	register struct struct_3 _7;
	_args_0 = _args;
L2:; // incoming:1
	_1 = 2;
	_2 = 7;
	_3 = 11;
	_4 = 15;
	_158_nums_0 = (struct struct_3) {4, (int64_t[]){_1, _2, _3, _4}};
	_158_target_0 = 9;
	_6 = test_testModule_twoSum;
	_7 = _6(_158_nums_0, _158_target_0);
	retval = 0;
	goto end;
end:;
	return retval;
}

struct struct_3 test_testModule_twoSum(struct struct_3 _numArg, int64_t _targetArg)
{
	struct struct_3 retval;
	register int64_t _1;
	register int64_t _2;
	_numArg_0 = _numArg;
	_targetArg_0 = _targetArg;
L0:; // incoming:1
	_1 = 3;
	_2 = 4;
	retval = (struct struct_3) {2, (int64_t[]){_1, _2}};
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
