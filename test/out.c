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
	int64_t tag;
	union {
		int64_t _int;
		struct struct_1 str;
	};
};

struct struct_4 {
	int64_t tag;
};

struct struct_5 {
	int64_t length;
	int8_t* data;
};

/* Verbatim code */
int std_system_println(struct struct_1 _format, ...) {va_list _25_args;va_start(_25_args, _format.data);int retval = vprintf(_format.data, _25_args);va_end(_25_args);char newLine[2] = {'\n', '\0'};printf(newLine);return retval;
}

/* Forward string declarations */
struct struct_1 string_0;
struct struct_1 string_1;
struct struct_1 string_2;
struct struct_1 string_3;
struct struct_1 string_4;
struct struct_1 string_5;
struct struct_1 string_6;
struct struct_1 string_7;
struct struct_1 string_8;
struct struct_1 string_9;
struct struct_1 string_10;
struct struct_1 string_11;
struct struct_1 string_12;
struct struct_1 string_13;
struct struct_1 string_14;
struct struct_1 string_15;
struct struct_1 string_16;
struct struct_1 string_17;
struct struct_1 string_18;
struct struct_1 string_19;

/* Forward global declarations */

/* Forward function and procedure declarations */
struct struct_3 test_testModule_testFn();
int64_t test_testModule_main(struct struct_2 _args);
void std_debug_assert(bool _predicate, struct struct_1 _msg);
FILE* std_system_open(struct struct_1 _filename, struct struct_1 _mode);
int64_t std_system_readChar(FILE* _file);
int64_t std_system_pushChar(int8_t _c, FILE* _file);
int64_t std_system_print(struct struct_1 _format, ...);
int64_t std_system_err(struct struct_1 _format, ...);
int64_t std_system_errln(struct struct_1 _format, ...);
int64_t std_math_abs(int64_t _x);
double std_math_max(double _x, double _y);
double std_math_min(double _x, double _y);
bool std_string_compare(struct struct_1 _str1, struct struct_1 _str2);
struct struct_1 std_string_copy(struct struct_1 _src);
int64_t std_string_concat(struct struct_1 _dst, int64_t _dstSize, struct struct_1 _src, int64_t _srcSize);
bool std_string_containsChar(struct struct_1 _str, int8_t _c);
bool std_string_equals(struct struct_1 _a, struct struct_1 _b);
struct struct_1 std_string_substring(struct struct_1 _s, int64_t _start, int64_t _end);
int8_t* std_string_itoa(int64_t __int);
struct struct_1 std_string_format(int64_t _n, struct struct_1 _f, ...);

#ifndef ORANGE_PROGRAM_28021
#define ORANGE_PROGRAM_28021

/* String definitions */
struct struct_1 string_0 = {18, (char[]){'a', 's', 's', 'e', 'r', 't', 'i', 'o', 'n', ' ', 'f', 'a', 'i', 'l', 'e', 'd', ':', ' ', '\0'}};
struct struct_1 string_1 = {20, (char[]){'n', 'o', ' ', 'm', 'e', 's', 's', 'a', 'g', 'e', ' ', 's', 'p', 'e', 'c', 'i', 'f', 'i', 'e', 'd', '\0'}};
struct struct_1 string_2 = {10, (char[]){'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0'}};
struct struct_1 string_3 = {11, (char[]){'<', 's', 't', 'd', 'b', 'o', 'o', 'l', '.', 'h', '>', '\0'}};
struct struct_1 string_4 = {9, (char[]){'<', 'c', 't', 'y', 'p', 'e', '.', 'h', '>', '\0'}};
struct struct_1 string_5 = {8, (char[]){'<', 'm', 'a', 't', 'h', '.', 'h', '>', '\0'}};
struct struct_1 string_6 = {10, (char[]){'<', 's', 't', 'd', 'a', 'r', 'g', '.', 'h', '>', '\0'}};
struct struct_1 string_7 = {10, (char[]){'<', 's', 't', 'd', 'i', 'n', 't', '.', 'h', '>', '\0'}};
struct struct_1 string_8 = {9, (char[]){'<', 's', 't', 'd', 'i', 'o', '.', 'h', '>', '\0'}};
struct struct_1 string_9 = {10, (char[]){'<', 's', 't', 'd', 'l', 'i', 'b', '.', 'h', '>', '\0'}};
struct struct_1 string_10 = {10, (char[]){'<', 's', 't', 'r', 'i', 'n', 'g', '.', 'h', '>', '\0'}};
struct struct_1 string_11 = {8, (char[]){'<', 't', 'i', 'm', 'e', '.', 'h', '>', '\0'}};
struct struct_1 string_12 = {225, (char[]){'i', 'n', 't', ' ', 's', 't', 'd', '_', 's', 'y', 's', 't', 'e', 'm', '_', 'p', 'r', 'i', 'n', 't', 'l', 'n', '(', 's', 't', 'r', 'u', 'c', 't', ' ', 's', 't', 'r', 'u', 'c', 't', '_', '1', ' ', '_', 'f', 'o', 'r', 'm', 'a', 't', ',', ' ', '.', '.', '.', ')', ' ', '{', 'v', 'a', '_', 'l', 'i', 's', 't', ' ', '_', '2', '5', '_', 'a', 'r', 'g', 's', ';', 'v', 'a', '_', 's', 't', 'a', 'r', 't', '(', '_', '2', '5', '_', 'a', 'r', 'g', 's', ',', ' ', '_', 'f', 'o', 'r', 'm', 'a', 't', '.', 'd', 'a', 't', 'a', ')', ';', 'i', 'n', 't', ' ', 'r', 'e', 't', 'v', 'a', 'l', ' ', '=', ' ', 'v', 'p', 'r', 'i', 'n', 't', 'f', '(', '_', 'f', 'o', 'r', 'm', 'a', 't', '.', 'd', 'a', 't', 'a', ',', ' ', '_', '2', '5', '_', 'a', 'r', 'g', 's', ')', ';', 'v', 'a', '_', 'e', 'n', 'd', '(', '_', '2', '5', '_', 'a', 'r', 'g', 's', ')', ';', 'c', 'h', 'a', 'r', ' ', 'n', 'e', 'w', 'L', 'i', 'n', 'e', '[', '2', ']', ' ', '=', ' ', '{', '\'', '\n', '\'', ',', ' ', '\'', '\0', '\'', '}', ';', 'p', 'r', 'i', 'n', 't', 'f', '(', 'n', 'e', 'w', 'L', 'i', 'n', 'e', ')', ';', 'r', 'e', 't', 'u', 'r', 'n', ' ', 'r', 'e', 't', 'v', 'a', 'l', ';', '\0'}};
struct struct_1 string_13 = {1, (char[]){'}', '\0'}};
struct struct_1 string_14 = {2, (char[]){'%', 's', '\0'}};
struct struct_1 string_15 = {2, (char[]){'%', 'd', '\0'}};
struct struct_1 string_16 = {3, (char[]){'R', 'e', 'd', '\0'}};
struct struct_1 string_17 = {5, (char[]){'G', 'r', 'e', 'e', 'n', '\0'}};
struct struct_1 string_18 = {4, (char[]){'B', 'l', 'u', 'e', '\0'}};
struct struct_1 string_19 = {5, (char[]){'H', 'e', 'l', 'l', 'o', '\0'}};

/* Function and procedure definitions */
struct struct_3 test_testModule_testFn()
{
	struct struct_3 retval;
	struct struct_3 _0;
// AST_RETURN
// test/testModule.orng:15
	int64_t _1 = 0;
	struct struct_3 _2;
	_2.tag = 0;
	_2._int = _1;
	retval = _2;
	goto return_block_35;
	_0 = _2;
	retval = _0;
return_block_35:;
	return retval;
}

int64_t test_testModule_main(struct struct_2 _args)
{
	int64_t retval;
	int64_t _0;
// AST_DEFINE
// test/testModule.orng:22
	struct struct_4 _1;
	_1.tag = 0;
	struct struct_4 _36_y = _1;
// AST_DEFINE
// test/testModule.orng:23
	int64_t _2 = 4;
	struct struct_3 _3;
	_3.tag = 0;
	_3._int = _2;
	struct struct_3 _36_x = _3;
// Unknown ASTNode type
// test/testModule.orng:27
	struct struct_3 _4 = _36_x;
	switch (_4.tag) {
	case 0:
	{
	struct struct_1 _5 = string_14;
	struct struct_3 _6 = _36_x;
	int64_t _7 = _6._int;
	int64_t _8 = std_system_println(_5, _7);
	break;
	} // end case
	case 1:
	{
	struct struct_1 _9 = string_15;
	struct struct_3 _10 = _36_x;
	struct struct_1 _11 = _10.str;
	int64_t _12 = std_system_println(_9, _11);
	break;
	} // end case
	case 2:
	{
	break;
	} // end case
	} // end switch
// Unknown ASTNode type
// test/testModule.orng:34
	struct struct_4 _13 = _36_y;
	switch (_13.tag) {
	case 0:
	{
	struct struct_1 _14 = string_16;
	int64_t _15 = std_system_println(_14);
	break;
	} // end case
	case 1:
	{
	struct struct_1 _16 = string_17;
	int64_t _17 = std_system_println(_16);
	break;
	} // end case
	case 2:
	{
	struct struct_3 _18;
// AST_CALL
// test/testModule.orng:37
	struct struct_1 _19 = string_18;
	int64_t _20 = std_system_println(_19);
// AST_ASSIGN
// test/testModule.orng:37
	struct struct_1 _21 = string_19;
	struct struct_3 _22;
	_22.tag = 1;
	_22.str = _21;
	_36_x = _22;
	_18 = _22;
	break;
	} // end case
	} // end switch
// AST_INT
// test/testModule.orng:40
	int64_t _23 = 0;
	_0 = _23;
	retval = _0;
return_block_36:;
	return retval;
}

void std_debug_assert(bool _predicate, struct struct_1 _msg)
{
// AST_IF
// std/debug.orng:11
	bool _0 = _predicate;
	bool _1 = !_0;
	if (!_1) goto else_2;
// AST_CALL
// std/debug.orng:8
	struct struct_1 _2 = string_0;
	int64_t _3 = std_system_err(_2);
// AST_CALL
// std/debug.orng:9
	int64_t _4 = std_system_errln(_msg);
// AST_CALL
// std/debug.orng:10
	int64_t _5 = 1;
	(_5);
	goto end_2;
else_2:;
end_2:;
return_block_1:;
}

FILE* std_system_open(struct struct_1 _filename, struct struct_1 _mode)
{
	FILE* retval;
	FILE* _0;
// AST_RETURN
// std/system.orng:14
	struct struct_1 _1 = _filename;
	int8_t* _2 = _1.data;
	struct struct_1 _3 = _mode;
	int8_t* _4 = _3.data;
	FILE* _5 = (_2, _4);
	retval = _5;
	goto return_block_29;
	_0 = _5;
	retval = _0;
return_block_29:;
	return retval;
}

int64_t std_system_readChar(FILE* _file)
{
	int64_t retval;
	int64_t _0;
// AST_RETURN
// std/system.orng:18
	int64_t _1 = (_file);
	retval = _1;
	goto return_block_30;
	_0 = _1;
	retval = _0;
return_block_30:;
	return retval;
}

int64_t std_system_pushChar(int8_t _c, FILE* _file)
{
	int64_t retval;
	int64_t _0;
// AST_RETURN
// std/system.orng:22
	int64_t _1 = (_c, _file);
	retval = _1;
	goto return_block_31;
	_0 = _1;
	retval = _0;
return_block_31:;
	return retval;
}

int64_t std_system_print(struct struct_1 _format, ...)
{
	int64_t retval;
	int64_t _0;
// AST_DEFINE
// std/system.orng:31
	va_list _32_args;
// AST_CALL
// std/system.orng:32
	struct struct_1 _1 = _format;
	int8_t* _2 = _1.data;
	(_32_args, _2);
// AST_DEFINE
// std/system.orng:33
	struct struct_1 _3 = _format;
	int8_t* _4 = _3.data;
	int64_t _5 = (_4, _32_args);
	int64_t _32_retcode = _5;
// AST_CALL
// std/system.orng:34
	(_32_args);
// AST_RETURN
// std/system.orng:35
	int64_t _6 = _32_retcode;
	retval = _6;
	goto return_block_32;
	_0 = _6;
	retval = _0;
return_block_32:;
	return retval;
}

int64_t std_system_err(struct struct_1 _format, ...)
{
	int64_t retval;
	int64_t _0;
// AST_DEFINE
// std/system.orng:39
	va_list _33_args;
// AST_CALL
// std/system.orng:40
	struct struct_1 _1 = _format;
	int8_t* _2 = _1.data;
	(_33_args, _2);
// AST_DEFINE
// std/system.orng:41
	struct struct_1 _3 = _format;
	int8_t* _4 = _3.data;
	int64_t _5 = (_4, _33_args);
	int64_t _33_retcode = _5;
// AST_CALL
// std/system.orng:42
	(_33_args);
// AST_RETURN
// std/system.orng:43
	int64_t _6 = _33_retcode;
	retval = _6;
	goto return_block_33;
	_0 = _6;
	retval = _0;
return_block_33:;
	return retval;
}

int64_t std_system_errln(struct struct_1 _format, ...)
{
	int64_t retval;
	int64_t _0;
// AST_DEFINE
// std/system.orng:46
	va_list _34_args;
// AST_CALL
// std/system.orng:47
	struct struct_1 _1 = _format;
	int8_t* _2 = _1.data;
	(_34_args, _2);
// AST_DEFINE
// std/system.orng:48
	struct struct_1 _3 = _format;
	int8_t* _4 = _3.data;
	int64_t _5 = (_4, _34_args);
	int64_t _34_retcode = _5;
// AST_CALL
// std/system.orng:49
	(_34_args);
// AST_RETURN
// std/system.orng:50
	int64_t _6 = _34_retcode;
	retval = _6;
	goto return_block_34;
	_0 = _6;
	retval = _0;
return_block_34:;
	return retval;
}

int64_t std_math_abs(int64_t _x)
{
	int64_t retval;
	int64_t _0;
	int64_t _1 = _x;
	int64_t _2 = 0;
	bool _3 = _1 > _2;
	if (!_3) goto else_3;
	int64_t _4;
// AST_IDENT
// std/math.orng:3
	int64_t _5 = _x;
	_4 = _5;
	_0 = _4;
	goto end_3;
else_3:;
	int64_t _6;
// AST_NEG
// std/math.orng:3
	int64_t _7 = _x;
	int64_t _8 = -_7;
	_6 = _8;
	_0 = _6;
end_3:;
	retval = _0;
return_block_4:;
	return retval;
}

double std_math_max(double _x, double _y)
{
	double retval;
	double _0;
	double _1 = _x;
	double _2 = _y;
	bool _3 = _1 > _2;
	if (!_3) goto else_5;
	double _4;
// AST_IDENT
// std/math.orng:7
	double _5 = _x;
	_4 = _5;
	_0 = _4;
	goto end_5;
else_5:;
	double _6;
// AST_IDENT
// std/math.orng:7
	double _7 = _y;
	_6 = _7;
	_0 = _6;
end_5:;
	retval = _0;
return_block_6:;
	return retval;
}

double std_math_min(double _x, double _y)
{
	double retval;
	double _0;
	double _1 = _x;
	double _2 = _y;
	bool _3 = _1 < _2;
	if (!_3) goto else_7;
	double _4;
// AST_IDENT
// std/math.orng:8
	double _5 = _x;
	_4 = _5;
	_0 = _4;
	goto end_7;
else_7:;
	double _6;
// AST_IDENT
// std/math.orng:8
	double _7 = _y;
	_6 = _7;
	_0 = _6;
end_7:;
	retval = _0;
return_block_8:;
	return retval;
}

bool std_string_compare(struct struct_1 _str1, struct struct_1 _str2)
{
	bool retval;
	bool _0;
// AST_RETURN
// std/string.orng:4
	struct struct_1 _1 = _str1;
	int8_t* _2 = _1.data;
	struct struct_1 _3 = _str2;
	int8_t* _4 = _3.data;
	int64_t _5 = (_2, _4);
	int64_t _6 = 0;
	bool _7 = _5 == _6;
	retval = _7;
	goto return_block_9;
	_0 = _7;
	retval = _0;
return_block_9:;
	return retval;
}

struct struct_1 std_string_copy(struct struct_1 _src)
{
	struct struct_1 retval;
	struct struct_1 _0;
// AST_DEFINE
// std/string.orng:10
	struct struct_1 _1 = _src;
	int64_t _2 = _1.length;
	int64_t _3 = 1;
	int64_t _4 = _2 + _3;
	struct struct_1 _5 = {_4, malloc(sizeof(int8_t) * _4)};
	_5.length = _4;
	for(int i = 0; i < _4; i++) {_5.data[i] = 0;}
	struct struct_1 _10_retval = _5;
// AST_CALL
// std/string.orng:11
	struct struct_1 _6 = _10_retval;
	int8_t* _7 = _6.data;
	int64_t _8 = 0;
	struct struct_1 _9 = _10_retval;
	int64_t _10 = _9.length;
	void* _11 = (_7, _8, _10);
// AST_CALL
// std/string.orng:12
	struct struct_1 _12 = _10_retval;
	int8_t* _13 = _12.data;
	struct struct_1 _14 = _src;
	int64_t _15 = _14.length;
	int64_t _16 = 1;
	int64_t _17 = _15 + _16;
	struct struct_1 _18 = _src;
	int8_t* _19 = _18.data;
	struct struct_1 _20 = _src;
	int64_t _21 = _20.length;
	int64_t _22 = 1;
	int64_t _23 = _21 + _22;
	int64_t _24 = (_13, _17, _19, _23);
// AST_RETURN
// std/string.orng:13
	struct struct_1 _25 = _10_retval;
	retval = _25;
	goto return_block_10;
	_0 = _25;
	retval = _0;
return_block_10:;
	return retval;
}

int64_t std_string_concat(struct struct_1 _dst, int64_t _dstSize, struct struct_1 _src, int64_t _srcSize)
{
	int64_t retval;
	int64_t _0;
// AST_RETURN
// std/string.orng:16
	struct struct_1 _1 = _dst;
	int8_t* _2 = _1.data;
	struct struct_1 _3 = _src;
	int8_t* _4 = _3.data;
	int64_t _5 = (_2, _dstSize, _4, _srcSize);
	retval = _5;
	goto return_block_11;
	_0 = _5;
	retval = _0;
return_block_11:;
	return retval;
}

bool std_string_containsChar(struct struct_1 _str, int8_t _c)
{
	bool retval;
	bool _0;
// AST_FOR
// std/string.orng:24
	int64_t _1 = 0;
	int64_t _13_i = _1;
begin_14:;
	int64_t _2 = _13_i;
	struct struct_1 _3 = _str;
	int8_t _4 = _3.data[_2];
	int8_t _5 = '\0';
	bool _6 = _4 != _5;
	if (!_6) goto end_14;
// AST_IF
// std/string.orng:23
	int64_t _7 = _13_i;
	struct struct_1 _8 = _str;
	int8_t _9 = _8.data[_7];
	int8_t _10 = _c;
	bool _11 = _9 == _10;
	if (!_11) goto else_15;
	bool _12;
// AST_RETURN
// std/string.orng:22
	bool _13 = 1;
	retval = _13;
	goto return_block_12;
	_12 = _13;
	goto end_15;
else_15:;
end_15:;
	// for post
	int64_t _14 = 1;
	_13_i += _14;
	goto begin_14;
end_14:;
// AST_RETURN
// std/string.orng:25
	bool _15 = 0;
	retval = _15;
	goto return_block_12;
	_0 = _15;
	retval = _0;
return_block_12:;
	return retval;
}

bool std_string_equals(struct struct_1 _a, struct struct_1 _b)
{
	bool retval;
	bool _0;
// AST_IF
// std/string.orng:38
	bool _1;
	struct struct_1 _2 = _a;
	int64_t _3 = _2.length;
	struct struct_1 _4 = _b;
	int64_t _5 = _4.length;
	bool _6 = _3 != _5;
	if (!_6) goto else_17;
	bool _7;
// AST_RETURN
// std/string.orng:30
	bool _8 = 0;
	retval = _8;
	goto return_block_16;
	_7 = _8;
	_1 = _7;
	goto end_17;
else_17:;
	bool _9;
// AST_FOR
// std/string.orng:36
	int64_t _10 = 0;
	int64_t _19_i = _10;
begin_20:;
	int64_t _11 = _19_i;
	struct struct_1 _12 = _a;
	int64_t _13 = _12.length;
	bool _14 = _11 < _13;
	if (!_14) goto end_20;
// AST_IF
// std/string.orng:35
	int64_t _15 = _19_i;
	struct struct_1 _16 = _a;
	int8_t _17 = _16.data[_15];
	int64_t _18 = _19_i;
	struct struct_1 _19 = _b;
	int8_t _20 = _19.data[_18];
	bool _21 = _17 != _20;
	if (!_21) goto else_21;
	bool _22;
// AST_RETURN
// std/string.orng:34
	bool _23 = 0;
	retval = _23;
	goto return_block_16;
	_22 = _23;
	goto end_21;
else_21:;
end_21:;
	// for post
	int64_t _24 = 1;
	_19_i += _24;
	goto begin_20;
end_20:;
// AST_RETURN
// std/string.orng:37
	bool _25 = 1;
	retval = _25;
	goto return_block_16;
	_9 = _25;
	_1 = _9;
end_17:;
	_0 = _1;
	retval = _0;
return_block_16:;
	return retval;
}

struct struct_1 std_string_substring(struct struct_1 _s, int64_t _start, int64_t _end)
{
	struct struct_1 retval;
	struct struct_1 _0;
// AST_DEFINE
// std/string.orng:42
	int64_t _1 = _end;
	int64_t _2 = _start;
	int64_t _3 = _1 - _2;
	struct struct_1 _4 = {_3, malloc(sizeof(int8_t) * _3)};
	_4.length = _3;
	for(int i = 0; i < _3; i++) {_4.data[i] = 0;}
	struct struct_1 _22_retval = _4;
// AST_FOR
// std/string.orng:45
	int8_t _5;
	int64_t _6 = 0;
	int64_t _23_i = _6;
begin_24:;
	int64_t _7 = _23_i;
	struct struct_1 _8 = _22_retval;
	int64_t _9 = _8.length;
	bool _10 = _7 < _9;
	if (!_10) goto end_24;
	int8_t _11;
// AST_ASSIGN
// std/string.orng:44
	int64_t _12 = _start;
	int64_t _13 = _23_i;
	int64_t _14 = _12 + _13;
	struct struct_1 _15 = _s;
	int8_t _16 = _15.data[_14];
	int64_t _17 = _23_i;
	_22_retval.data[_17] = _16;
	_11 = _16;
	_5 = _11;
	// for post
	int64_t _18 = 1;
	_23_i += _18;
	goto begin_24;
end_24:;
	_5 = _11;
// AST_RETURN
// std/string.orng:46
	struct struct_1 _19 = _22_retval;
	retval = _19;
	goto return_block_22;
	_0 = _19;
	retval = _0;
return_block_22:;
	return retval;
}

int8_t* std_string_itoa(int64_t __int)
{
	int8_t* retval;
	int8_t* _0;
// AST_DEFINE
// std/string.orng:54
	struct struct_1 _25_buf = ((struct struct_1){26, (int8_t*[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}});
// AST_DEFINE
// std/string.orng:55
	int64_t _1 = 30;
	int64_t _25_i = _1;
// AST_DIV_ASSIGN
// std/string.orng:56
	int64_t _2 = 10;
	__int *= _2;
// AST_FOR
// std/string.orng:60
	int8_t _3;
begin_27:;
	bool _4 = 0;
	int64_t _5 = __int;
	int64_t _6 = 0;
	bool _7 = _5 > _6;
	if (!_7) goto over_0;
	int64_t _8 = _25_i;
	int64_t _9 = 0;
	bool _10 = _8 > _9;
	_4 = _10;
over_0:;
	if (!_4) goto end_27;
	int8_t _11;
// AST_DIV_ASSIGN
// std/string.orng:58
	int64_t _12 = 10;
	__int /= _12;
// AST_ASSIGN
// std/string.orng:59
	int64_t _13 = __int;
	int64_t _14 = 10;
	int64_t _15 = _13 % _14;
	struct struct_1 _16 = string_2;
	int8_t _17 = _16.data[_15];
	int64_t _18 = _25_i;
	_25_buf.data[_18] = _17;
	_11 = _17;
	_3 = _11;
	// for post
	int64_t _19 = 1;
	_25_i -= _19;
	goto begin_27;
end_27:;
	_3 = _11;
// AST_RETURN
// std/string.orng:61
	int64_t _20 = _25_i;
	int64_t _21 = 2;
	int64_t _22 = _20 + _21;
	struct struct_1 _23 = _25_buf;
	int8_t _24 = _23.data[_22];
	int8_t* _25 = &_24;
	retval = _25;
	goto return_block_25;
	_0 = _25;
	retval = _0;
return_block_25:;
	return retval;
}

struct struct_1 std_string_format(int64_t _n, struct struct_1 _f, ...)
{
	struct struct_1 retval;
	struct struct_1 _0;
// AST_DEFINE
// std/string.orng:67
	int64_t _1 = _n;
	struct struct_1 _2 = {_1, malloc(sizeof(int8_t) * _1)};
	_2.length = _1;
	for(int i = 0; i < _1; i++) {_2.data[i] = 0;}
	struct struct_1 _28_retval = _2;
// AST_CALL
// std/string.orng:68
	struct struct_1 _3 = _28_retval;
	int8_t* _4 = _3.data;
	struct struct_1 _5 = _f;
	int8_t* _6 = _5.data;
	int64_t _7 = sprintf(_4, _6);
// AST_IDENT
// std/string.orng:69
	struct struct_1 _8 = _28_retval;
	_0 = _8;
	retval = _0;
return_block_28:;
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
