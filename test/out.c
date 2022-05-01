/* Code generated using Orange Translator http://josephs-projects.com */

/* Includes used by the program */
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
	struct struct_3 _height;
	int64_t _max;
};

/* Verbatim code */
int std_system_println(struct struct_1 _format, ...) {va_list _25_args;va_start(_25_args, _format.data);int retval = vprintf(_format.data, _25_args);va_end(_25_args);char newLine[2] = {'\n', '\0'};printf(newLine);return retval;
}

/* Forward string declarations */
struct struct_1 string_33;
struct struct_1 string_34;

/* Enums */

/* Forward global declarations */

/* Forward function and procedure declarations */
int64_t test_leetcode_maxArea(struct struct_3 _height, int64_t _max);
void test_leetcode_test_maxArea();
int64_t test_testModule_main(struct struct_2 _args);
double std_math_max(double _x, double _y);
double std_math_min(double _x, double _y);

#ifndef ORANGE_PROGRAM_21871
#define ORANGE_PROGRAM_21871

/* String definitions */
struct struct_1 string_33 = {16, (char[]){'m', 'a', 'x', 'A', 'r', 'e', 'a', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_34 = {15, (char[]){'m', 'a', 'x', 'A', 'r', 'e', 'a', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};

/* Enum definitions */

/* Function and procedure definitions */
int64_t test_leetcode_maxArea(struct struct_3 _height, int64_t _max)
{
	int64_t retval;
	int64_t _0;
	int64_t _1 = 0;
	int64_t _191_i = _1;
begin_191:;
	int64_t _2 = _191_i;
	struct struct_3 _3 = _height;
	int64_t _4 = _3.length;
	int64_t _5 = 1;
	int64_t _6 = _4 - _5;
	bool _7 = _2 < _6;
	if (!_7) goto end_191;
	int64_t _8;
// AST_FOR
// test/leetcode.orng:453
	int64_t _9;
	int64_t _10 = _191_i;
	int64_t _11 = 1;
	int64_t _12 = _10 + _11;
	int64_t _192_j = _12;
begin_192:;
	int64_t _13 = _192_j;
	struct struct_3 _14 = _height;
	int64_t _15 = _14.length;
	bool _16 = _13 < _15;
	if (!_16) goto end_192;
	int64_t _17;
// AST_ASSIGN
// test/leetcode.orng:454
	int64_t _18 = _191_i;
	int64_t _19 = _192_j;
	int64_t _20 = _18 - _19;
	int64_t _21 = abs(_20);
	int64_t _22 = _191_i;
	struct struct_3 _23 = _height;
	int64_t _24 = _23.data[_22];
	int64_t _25 = _192_j;
	struct struct_3 _26 = _height;
	int64_t _27 = _26.data[_25];
	double _28 = std_math_min(_24, _27);
	double _29 = _21 * _28;
	double _30 = std_math_max(_max, _29);
	int64_t _31 = (int64_t)_30;
	_max = _31;
	_17 = _31;
	_9 = _17;
	int64_t _32 = 1;
	_192_j += _32;
	goto begin_192;
end_192:;
	_9 = _17;
	_8 = _9;
	_0 = _8;
	int64_t _33 = 1;
	_191_i += _33;
	goto begin_191;
end_191:;
	_0 = _8;
	retval = _0;
return_block_191:;
	return retval;
}

void test_leetcode_test_maxArea()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:459
	int64_t _1 = 1;
	int64_t _2 = 8;
	int64_t _3 = 6;
	int64_t _4 = 2;
	int64_t _5 = 5;
	int64_t _6 = 4;
	int64_t _7 = 8;
	int64_t _8 = 3;
	int64_t _9 = 7;
	struct struct_3 _10 = {9, (int64_t[]){_1, _2, _3, _4, _5, _6, _7, _8, _9}};
	struct struct_3 _193_height = _10;
// AST_DEFINE
// test/leetcode.orng:461
	int64_t _34 = 0;
	int64_t _11 = test_leetcode_maxArea(_193_height, _34);
	int64_t _193_ans = _11;
// AST_IFELSE
// test/leetcode.orng:463
	int64_t _12;
	int64_t _13 = _193_ans;
	int64_t _14 = 49;
	bool _15 = _13 == _14;
	if (!_15) goto else_194;
	int64_t _16;
// AST_CALL
// test/leetcode.orng:464
	struct struct_1 _17 = string_33;
	int64_t _18 = std_system_println(_17);
	_16 = _18;
	_12 = _16;
	goto end_194;
else_194:;
	int64_t _19;
// AST_CALL
// test/leetcode.orng:466
	struct struct_1 _20 = string_34;
	int64_t _21 = std_system_println(_20);
	_19 = _21;
	_12 = _19;
end_194:;
	_0 = _12;
return_block_193:;
}

int64_t test_testModule_main(struct struct_2 _args)
{
	int64_t retval;
	int64_t _0;
// AST_CALL
// test/testModule.orng:3
	test_leetcode_test_maxArea();
// AST_INT
// test/testModule.orng:4
	int64_t _1 = 0;
	_0 = _1;
	retval = _0;
return_block_196:;
	return retval;
}

double std_math_max(double _x, double _y)
{
	double retval;
	double _0;
	double _1 = _x;
	double _2 = _y;
	bool _3 = _1 > _2;
	if (!_3) goto else_3;
	double _4;
// AST_IDENT
// std/math.orng:8
	double _5 = _x;
	_4 = _5;
	_0 = _4;
	goto end_3;
else_3:;
	double _6;
// AST_IDENT
// std/math.orng:8
	double _7 = _y;
	_6 = _7;
	_0 = _6;
end_3:;
	retval = _0;
return_block_4:;
	return retval;
}

double std_math_min(double _x, double _y)
{
	double retval;
	double _0;
	double _1 = _x;
	double _2 = _y;
	bool _3 = _1 < _2;
	if (!_3) goto else_5;
	double _4;
// AST_IDENT
// std/math.orng:9
	double _5 = _x;
	_4 = _5;
	_0 = _4;
	goto end_5;
else_5:;
	double _6;
// AST_IDENT
// std/math.orng:9
	double _7 = _y;
	_6 = _7;
	_0 = _6;
end_5:;
	retval = _0;
return_block_6:;
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
	int retval = test_testModule_main(args);
	for (int  i = 0; i < argc; i++) {
		free(args.data[i].data);
	}
	free(args.data);
	return retval;
}
#endif
