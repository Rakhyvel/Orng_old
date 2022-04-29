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
	int8_t data[];
};

struct struct_2 {
	int64_t length;
	struct struct_1* data[];
};

struct struct_3 {
	int64_t length;
	int64_t data[];
};

struct struct_4 {
	int64_t length;
	int64_t data[2];
};

struct struct_5 {
	int64_t length;
	int64_t data[4];
};

struct struct_6 {
	int64_t val;
	struct struct_6* next;
};

struct struct_7 {
	struct struct_6* _l;
};

struct struct_8 {
	int64_t _i;
};

struct struct_9 {
	int64_t length;
	bool data[256];
};

struct struct_10 {
	struct struct_1* _str;
	int64_t _i;
	int64_t _j;
};

struct struct_11 {
	int64_t length;
	int64_t data[1];
};

struct struct_12 {
	struct struct_6* _list;
};

/* Verbatim code */
int stdlib_system_println(struct struct_1* _format, ...) {
    va_list _25_args;
    va_start(_25_args, &_format->data);
    int retval = vprintf(&_format->data, _25_args);
    va_end(_25_args);
    char newLine[2] = {'\n', '\0'};
    printf(newLine);
    return retval;
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
struct struct_1 string_20;
struct struct_1 string_21;
struct struct_1 string_22;

/* Enums */

/* Forward global declarations */

/* Forward function and procedure declarations */
void test_leetcode_test_all();
struct struct_4 test_leetcode_twoSum(struct struct_3* _nums, int64_t _target);
void test_leetcode_test_twoSum();
int64_t test_leetcode_convertToInt(struct struct_6* _l);
struct struct_6* test_leetcode_convertToList(int64_t _i);
struct struct_6* test_leetcode_addTwoNumbers(struct struct_6* _l1, struct struct_6* _l2);
void test_leetcode_test_addTwoNumbers();
int64_t test_leetcode_lengthOfLongestSubstring(struct struct_1* _str);
bool test_leetcode_areDistinct(struct struct_1* _str, int64_t _i, int64_t _j);
void test_leetcode_test_lengthOfLongestSubstring();
float test_leetcode_findMedianSortedArrays(struct struct_3* _nums1, struct struct_3* _nums2);
void test_leetcode_test_findMedianSortedArrays();
struct struct_1* test_leetcode_longestPalindrome(struct struct_1* _s);
int64_t test_leetcode_expandAroundCenter(struct struct_1* _s, int64_t _left, int64_t _right);
void test_leetcode_test_longestPalindrome();
struct struct_1* test_leetcode_convert(struct struct_1* _s, int64_t _numRows);
void test_leetcode_test_convert();
struct struct_6* test_leetcode_reverseList(struct struct_6* _list);
int64_t test_leetcode_reverse(int64_t _x);
void test_leetcode_test_reverse();
int64_t test_leetcode_myAtoi(struct struct_1* _s);
void test_leetcode_test_myAtoi();
int64_t test_testModule_main(struct struct_2* _args);
double stdlib_math_max(double _x, double _y);
bool stdlib_string_equals(struct struct_1* _a, struct struct_1* _b);
struct struct_1* stdlib_string_substring(struct struct_1* _s, int64_t _start, int64_t _end);

#ifndef ORANGE_PROGRAM_12720
#define ORANGE_PROGRAM_12720

/* String definitions */
struct struct_1 string_0 = {15, {'t', 'w', 'o', 'S', 'u', 'm', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_1 = {14, {'t', 'w', 'o', 'S', 'u', 'm', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
struct struct_1 string_2 = {22, {'a', 'd', 'd', 'T', 'w', 'o', 'N', 'u', 'm', 'b', 'e', 'r', 's', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_3 = {21, {'a', 'd', 'd', 'T', 'w', 'o', 'N', 'u', 'm', 'b', 'e', 'r', 's', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
struct struct_1 string_4 = {8, {'a', 'b', 'c', 'a', 'b', 'c', 'b', 'b', '\0'}};
struct struct_1 string_5 = {33, {'l', 'e', 'n', 'g', 't', 'h', 'O', 'f', 'L', 'o', 'n', 'g', 'e', 's', 't', 'S', 'u', 'b', 's', 't', 'r', 'i', 'n', 'g', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_6 = {35, {'l', 'e', 'n', 'g', 't', 'h', 'O', 'f', 'L', 'o', 'n', 'g', 'e', 's', 't', 'S', 'u', 'b', 's', 't', 'r', 'i', 'n', 'g', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', ' ', '%', 'd', '\0'}};
struct struct_1 string_7 = {31, {'f', 'i', 'n', 'd', 'M', 'e', 'd', 'i', 'a', 'n', 'S', 'o', 'r', 't', 'e', 'd', 'A', 'r', 'r', 'a', 'y', 's', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_8 = {30, {'f', 'i', 'n', 'd', 'M', 'e', 'd', 'i', 'a', 'n', 'S', 'o', 'r', 't', 'e', 'd', 'A', 'r', 'r', 'a', 'y', 's', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
struct struct_1 string_9 = {5, {'b', 'a', 'b', 'a', 'd', '\0'}};
struct struct_1 string_10 = {3, {'b', 'a', 'b', '\0'}};
struct struct_1 string_11 = {3, {'a', 'b', 'a', '\0'}};
struct struct_1 string_12 = {26, {'l', 'o', 'n', 'g', 'e', 's', 't', 'P', 'a', 'l', 'i', 'n', 'd', 'r', 'o', 'm', 'e', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_13 = {25, {'l', 'o', 'n', 'g', 'e', 's', 't', 'P', 'a', 'l', 'i', 'n', 'd', 'r', 'o', 'm', 'e', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
struct struct_1 string_14 = {14, {'P', 'A', 'Y', 'P', 'A', 'L', 'I', 'S', 'H', 'I', 'R', 'I', 'N', 'G', '\0'}};
struct struct_1 string_15 = {14, {'P', 'A', 'H', 'N', 'A', 'P', 'L', 'S', 'I', 'I', 'G', 'Y', 'I', 'R', '\0'}};
struct struct_1 string_16 = {16, {'c', 'o', 'n', 'v', 'e', 'r', 't', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_17 = {15, {'c', 'o', 'n', 'v', 'e', 'r', 't', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
struct struct_1 string_18 = {16, {'r', 'e', 'v', 'e', 'r', 's', 'e', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_19 = {15, {'r', 'e', 'v', 'e', 'r', 's', 'e', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
struct struct_1 string_20 = {2, {'4', '2', '\0'}};
struct struct_1 string_21 = {15, {'m', 'y', 'A', 't', 'o', 'i', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_22 = {14, {'m', 'y', 'A', 't', 'o', 'i', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};

/* Enum definitions */

/* Function and procedure definitions */
void test_leetcode_test_all()
{
// AST_CALL
// test/leetcode.orng:5
	test_leetcode_test_twoSum();
// AST_CALL
// test/leetcode.orng:6
	test_leetcode_test_addTwoNumbers();
// AST_CALL
// test/leetcode.orng:7
	test_leetcode_test_lengthOfLongestSubstring();
// AST_CALL
// test/leetcode.orng:8
	test_leetcode_test_findMedianSortedArrays();
// AST_CALL
// test/leetcode.orng:9
	test_leetcode_test_longestPalindrome();
// AST_CALL
// test/leetcode.orng:10
	test_leetcode_test_convert();
// AST_CALL
// test/leetcode.orng:11
	test_leetcode_test_reverse();
// AST_CALL
// test/leetcode.orng:12
	test_leetcode_test_myAtoi();
return_block_91:;
}

struct struct_4 test_leetcode_twoSum(struct struct_3* _nums, int64_t _target)
{
	struct struct_4 retval;
	struct struct_4 _0;
// AST_FOR
// test/leetcode.orng:19
	int32_t _1 = 0;
	int32_t _93_i = _1;
begin_93:;
	int32_t _2 = _93_i;
	struct struct_3* _3 = _nums;
	int64_t _4 = _3->length;
	int32_t _5 = 1;
	int64_t _6 = _4 - _5;
	bool _7 = _2 < _6;
	if (!_7) goto end_93;
// AST_FOR
// test/leetcode.orng:20
	int32_t _8 = _93_i;
	int32_t _9 = 1;
	int32_t _10 = _8 + _9;
	int32_t _94_j = _10;
begin_94:;
	int32_t _11 = _94_j;
	struct struct_3* _12 = _nums;
	int64_t _13 = _12->length;
	bool _14 = _11 < _13;
	if (!_14) goto end_94;
// AST_IF
// test/leetcode.orng:21
	int32_t _15 = _93_i;
	struct struct_3* _16 = _nums;
	int64_t _17 = _16->data[_15];
	int32_t _18 = _94_j;
	struct struct_3* _19 = _nums;
	int64_t _20 = _19->data[_18];
	int64_t _21 = _17 + _20;
	int64_t _22 = _target;
	bool _23 = _21 == _22;
	if (!_23) goto end_95;
	struct struct_4 _24;
// AST_RETURN
// test/leetcode.orng:22
	int32_t _25 = _93_i;
	int32_t _26 = _94_j;
	struct struct_4 _27 = {2, {_25, _26}};
	retval = _27;
	goto return_block_92;
	_24 = _27;
end_95:;
	int32_t _28 = 1;
	_94_j += _28;
	goto begin_94;
end_94:;
	int32_t _29 = 1;
	_93_i += _29;
	goto begin_93;
end_93:;
// AST_RETURN
// test/leetcode.orng:26
	int32_t _30 = 1;
	int32_t _31 = -_30;
	int32_t _32 = 1;
	int32_t _33 = -_32;
	struct struct_4 _34 = {2, {_31, _33}};
	retval = _34;
	goto return_block_92;
	_0 = _34;
	retval = _0;
return_block_92:;
	return retval;
}

void test_leetcode_test_twoSum()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:30
	int32_t _1 = 2;
	int32_t _2 = 7;
	int32_t _3 = 11;
	int32_t _4 = 15;
	struct struct_5 _5 = {4, {_1, _2, _3, _4}};
	struct struct_5 _96_nums = _5;
// AST_DEFINE
// test/leetcode.orng:31
	int32_t _6 = 9;
	int32_t _96_target = _6;
// AST_DEFINE
// test/leetcode.orng:33
	struct struct_5 _7 = _96_nums;
	struct struct_5* _8 = &_7;
	struct struct_4 _9 = test_leetcode_twoSum(_8, _96_target);
	struct struct_4 _96_ans = _9;
// AST_IFELSE
// test/leetcode.orng:35
	int64_t _10;
	int32_t _11 = 0;
	struct struct_4 _12 = _96_ans;
	int64_t _13 = _12.data[_11];
	struct struct_5 _14 = _96_nums;
	int64_t _15 = _14.data[_13];
	int32_t _16 = 1;
	struct struct_4 _17 = _96_ans;
	int64_t _18 = _17.data[_16];
	struct struct_5 _19 = _96_nums;
	int64_t _20 = _19.data[_18];
	int64_t _21 = _15 + _20;
	int32_t _22 = _96_target;
	bool _23 = _21 == _22;
	if (!_23) goto else_97;
	int64_t _24;
// AST_CALL
// test/leetcode.orng:36
	struct struct_1* _25 = &string_0;
	int64_t _26 = stdlib_system_println(_25);
	_24 = _26;
	_10 = _24;
	goto end_97;
else_97:;
	int64_t _27;
// AST_CALL
// test/leetcode.orng:38
	struct struct_1* _28 = &string_1;
	int64_t _29 = stdlib_system_println(_28);
	_27 = _29;
	_10 = _27;
end_97:;
	_0 = _10;
return_block_96:;
}

int64_t test_leetcode_convertToInt(struct struct_6* _l)
{
	int64_t retval;
	int64_t _0;
	struct struct_6* _1 = _l;
	struct struct_6* _2 = _1->next;
	void* _3 = 0;
	bool _4 = _2 == _3;
	if (!_4) goto else_99;
	int64_t _5;
// AST_DOT
// test/leetcode.orng:54
	struct struct_6* _6 = _l;
	int64_t _7 = _6->val;
	_5 = _7;
	_0 = _5;
	goto end_99;
else_99:;
	int64_t _8;
// AST_ADD
// test/leetcode.orng:56
	struct struct_6* _9 = _l;
	int64_t _10 = _9->val;
	struct struct_6* _11 = _l;
	struct struct_6* _12 = _11->next;
	int64_t _13 = test_leetcode_convertToInt(_12);
	int32_t _14 = 10;
	int64_t _15 = _13 * _14;
	int64_t _16 = _10 + _15;
	_8 = _16;
	_0 = _8;
end_99:;
	retval = _0;
return_block_100:;
	return retval;
}

struct struct_6* test_leetcode_convertToList(int64_t _i)
{
	struct struct_6* retval;
	struct struct_6* _0;
// AST_DEFINE
// test/leetcode.orng:60
	struct struct_6* _1 = calloc(sizeof(struct struct_6), 1);
	*_1 = ((struct struct_6){0, 0});
	struct struct_6* _101_retval = _1;
// AST_IFELSE
// test/leetcode.orng:61
	struct struct_6 _2;
	int64_t _3 = _i;
	int32_t _4 = 10;
	bool _5 = _3 < _4;
	if (!_5) goto else_102;
	struct struct_6 _6;
// AST_ASSIGN
// test/leetcode.orng:62
	int64_t _7 = _i;
	void* _8 = 0;
	struct struct_6 _9 = {_7, _8};
	*_101_retval = _9;
	_6 = _9;
	_2 = _6;
	goto end_102;
else_102:;
	struct struct_6 _10;
// AST_ASSIGN
// test/leetcode.orng:64
	int64_t _11 = _i;
	int32_t _12 = 10;
	int64_t _13 = _11 % _12;
	int64_t _14 = _i;
	int32_t _15 = 10;
	int64_t _16 = _14 / _15;
	struct struct_6* _17 = test_leetcode_convertToList(_16);
	struct struct_6 _18 = {_13, _17};
	*_101_retval = _18;
	_10 = _18;
	_2 = _10;
end_102:;
// AST_RETURN
// test/leetcode.orng:66
	struct struct_6* _19 = _101_retval;
	retval = _19;
	goto return_block_101;
	_0 = _19;
	retval = _0;
return_block_101:;
	return retval;
}

struct struct_6* test_leetcode_addTwoNumbers(struct struct_6* _l1, struct struct_6* _l2)
{
	struct struct_6* retval;
	int64_t _0 = test_leetcode_convertToInt(_l1);
	int64_t _1 = test_leetcode_convertToInt(_l2);
	int64_t _2 = _0 + _1;
	struct struct_6* _3 = test_leetcode_convertToList(_2);
	retval = _3;
return_block_:;
	return retval;
}

void test_leetcode_test_addTwoNumbers()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:73
	struct struct_6* _1 = calloc(sizeof(struct struct_6), 1);
	*_1 = ((struct struct_6){0, 0});
	struct struct_6* _104_l1_c = _1;
// AST_ASSIGN
// test/leetcode.orng:74
	int32_t _2 = 3;
	void* _3 = 0;
	struct struct_6 _4 = {_2, _3};
	*_104_l1_c = _4;
// AST_DEFINE
// test/leetcode.orng:75
	struct struct_6* _5 = calloc(sizeof(struct struct_6), 1);
	*_5 = ((struct struct_6){0, 0});
	struct struct_6* _104_l1_b = _5;
// AST_ASSIGN
// test/leetcode.orng:76
	int32_t _6 = 4;
	struct struct_6* _7 = _104_l1_c;
	struct struct_6 _8 = {_6, _7};
	*_104_l1_b = _8;
// AST_DEFINE
// test/leetcode.orng:77
	struct struct_6* _9 = calloc(sizeof(struct struct_6), 1);
	*_9 = ((struct struct_6){0, 0});
	struct struct_6* _104_l1 = _9;
// AST_ASSIGN
// test/leetcode.orng:78
	int32_t _10 = 2;
	struct struct_6* _11 = _104_l1_b;
	struct struct_6 _12 = {_10, _11};
	*_104_l1 = _12;
// AST_DEFINE
// test/leetcode.orng:79
	struct struct_6* _13 = calloc(sizeof(struct struct_6), 1);
	*_13 = ((struct struct_6){0, 0});
	struct struct_6* _104_l2_c = _13;
// AST_ASSIGN
// test/leetcode.orng:80
	int32_t _14 = 4;
	void* _15 = 0;
	struct struct_6 _16 = {_14, _15};
	*_104_l2_c = _16;
// AST_DEFINE
// test/leetcode.orng:81
	struct struct_6* _17 = calloc(sizeof(struct struct_6), 1);
	*_17 = ((struct struct_6){0, 0});
	struct struct_6* _104_l2_b = _17;
// AST_ASSIGN
// test/leetcode.orng:82
	int32_t _18 = 6;
	struct struct_6* _19 = _104_l2_c;
	struct struct_6 _20 = {_18, _19};
	*_104_l2_b = _20;
// AST_DEFINE
// test/leetcode.orng:83
	struct struct_6* _21 = calloc(sizeof(struct struct_6), 1);
	*_21 = ((struct struct_6){0, 0});
	struct struct_6* _104_l2 = _21;
// AST_ASSIGN
// test/leetcode.orng:84
	int32_t _22 = 5;
	struct struct_6* _23 = _104_l2_b;
	struct struct_6 _24 = {_22, _23};
	*_104_l2 = _24;
// AST_DEFINE
// test/leetcode.orng:86
	struct struct_6* _25 = test_leetcode_addTwoNumbers(_104_l1, _104_l2);
	struct struct_6* _104_ans = _25;
// AST_IFELSE
// test/leetcode.orng:88
	int64_t _26;
	bool _27 = 0;
	bool _28 = 0;
	struct struct_6* _29 = _104_ans;
	int64_t _30 = _29->val;
	int32_t _31 = 7;
	bool _32 = _30 == _31;
	if (!_32) goto over_1;
	struct struct_6* _33 = _104_ans;
	struct struct_6* _34 = _33->next;
	int64_t _35 = _34->val;
	int32_t _36 = 0;
	bool _37 = _35 == _36;
	_28 = _37;
over_1:;
	if (!_28) goto over_0;
	struct struct_6* _38 = _104_ans;
	struct struct_6* _39 = _38->next;
	struct struct_6* _40 = _39->next;
	int64_t _41 = _40->val;
	int32_t _42 = 8;
	bool _43 = _41 == _42;
	_27 = _43;
over_0:;
	if (!_27) goto else_105;
	int64_t _44;
// AST_CALL
// test/leetcode.orng:89
	struct struct_1* _45 = &string_2;
	int64_t _46 = stdlib_system_println(_45);
	_44 = _46;
	_26 = _44;
	goto end_105;
else_105:;
	int64_t _47;
// AST_CALL
// test/leetcode.orng:91
	struct struct_1* _48 = &string_3;
	int64_t _49 = stdlib_system_println(_48);
	_47 = _49;
	_26 = _47;
end_105:;
	_0 = _26;
return_block_104:;
}

int64_t test_leetcode_lengthOfLongestSubstring(struct struct_1* _str)
{
	int64_t retval;
	int32_t _0;
// AST_DEFINE
// test/leetcode.orng:101
// AST_DEFINE
// test/leetcode.orng:113
	struct struct_1* _1 = _str;
	int64_t _2 = _1->length;
	int64_t _107_n = _2;
// AST_DEFINE
// test/leetcode.orng:114
	int32_t _3 = 0;
	int32_t _107_res = _3;
// AST_FOR
// test/leetcode.orng:118
	int32_t _4 = 0;
	int32_t _111_i = _4;
begin_111:;
	int32_t _5 = _111_i;
	int64_t _6 = _107_n;
	bool _7 = _5 < _6;
	if (!_7) goto end_111;
// AST_FOR
// test/leetcode.orng:119
	int32_t _8 = _111_i;
	int32_t _112_j = _8;
begin_112:;
	int32_t _9 = _112_j;
	int64_t _10 = _107_n;
	bool _11 = _9 < _10;
	if (!_11) goto end_112;
// AST_IF
// test/leetcode.orng:120
	bool _12 = test_leetcode_areDistinct(_str, _111_i, _112_j);
	if (!_12) goto end_113;
	int32_t _13;
// AST_ASSIGN
// test/leetcode.orng:121
	int32_t _14 = _112_j;
	int32_t _15 = _111_i;
	int32_t _16 = _14 - _15;
	int32_t _17 = 1;
	int32_t _18 = _16 + _17;
	double _19 = stdlib_math_max(_107_res, _18);
	int32_t _20 = (int64_t)_19;
	_107_res = _20;
	_13 = _20;
end_113:;
	int32_t _21 = 1;
	_112_j += _21;
	goto begin_112;
end_112:;
	int32_t _22 = 1;
	_111_i += _22;
	goto begin_111;
end_111:;
// AST_RETURN
// test/leetcode.orng:126
	int32_t _23 = _107_res;
	retval = _23;
	goto return_block_107;
	_0 = _23;
	retval = _0;
return_block_107:;
	return retval;
}

bool test_leetcode_areDistinct(struct struct_1* _str, int64_t _i, int64_t _j)
{
	bool retval;
	bool _0;
// AST_DEFINE
// test/leetcode.orng:103
	struct struct_9 _108_visited = ((struct struct_9){256, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
// AST_FOR
// test/leetcode.orng:104
	bool _1;
	int64_t _2 = _i;
	int64_t _109_k = _2;
begin_109:;
	int64_t _3 = _109_k;
	int64_t _4 = _j;
	bool _5 = _3 <= _4;
	if (!_5) goto end_109;
	bool _6;
// AST_DEFINE
// test/leetcode.orng:105
	int64_t _7 = _109_k;
	struct struct_1* _8 = _str;
	int8_t _9 = _8->data[_7];
	int64_t _10 = (int64_t)_9;
	int64_t _109_charCode = _10;
// AST_IF
// test/leetcode.orng:106
	int64_t _11 = _109_charCode;
	struct struct_9 _12 = _108_visited;
	bool _13 = _12.data[_11];
	if (!_13) goto end_110;
	bool _14;
// AST_RETURN
// test/leetcode.orng:107
	bool _15 = 0;
	retval = _15;
	goto return_block_108;
	_14 = _15;
end_110:;
// AST_ASSIGN
// test/leetcode.orng:109
	bool _16 = 1;
	int64_t _17 = _109_charCode;
	_108_visited.data[_17] = _16;
	_6 = _16;
	_1 = _6;
	int32_t _18 = 1;
	_109_k += _18;
	goto begin_109;
end_109:;
	_1 = _6;
// AST_RETURN
// test/leetcode.orng:111
	bool _19 = 1;
	retval = _19;
	goto return_block_108;
	_0 = _19;
	retval = _0;
return_block_108:;
	return retval;
}

void test_leetcode_test_lengthOfLongestSubstring()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:130
	struct struct_1* _1 = &string_4;
	struct struct_1* _114_s = _1;
// AST_DEFINE
// test/leetcode.orng:132
	int64_t _2 = test_leetcode_lengthOfLongestSubstring(_114_s);
	int64_t _114_ans = _2;
// AST_IFELSE
// test/leetcode.orng:134
	int64_t _3;
	int64_t _4 = _114_ans;
	int32_t _5 = 3;
	bool _6 = _4 == _5;
	if (!_6) goto else_115;
	int64_t _7;
// AST_CALL
// test/leetcode.orng:135
	struct struct_1* _8 = &string_5;
	int64_t _9 = stdlib_system_println(_8);
	_7 = _9;
	_3 = _7;
	goto end_115;
else_115:;
	int64_t _10;
// AST_CALL
// test/leetcode.orng:137
	struct struct_1* _11 = &string_6;
	int64_t _12 = stdlib_system_println(_11, _114_ans);
	_10 = _12;
	_3 = _10;
end_115:;
	_0 = _3;
return_block_114:;
}

float test_leetcode_findMedianSortedArrays(struct struct_3* _nums1, struct struct_3* _nums2)
{
	float retval;
	int defer_0 = 0;
	float _0;
// AST_DEFINE
// test/leetcode.orng:146
	struct struct_3* _1 = _nums1;
	int64_t _2 = _1->length;
	struct struct_3* _3 = _nums2;
	int64_t _4 = _3->length;
	int64_t _5 = _2 + _4;
	struct struct_3* _6 = malloc(sizeof(signed int) + sizeof(int64_t) * _5);
	_6->length = _5;
	for(int i = 0; i < _5; i++) {_6->data[i] = 0;}
	struct struct_3* _117_merged = _6;
// AST_DEFER
// test/leetcode.orng:147
	defer_0 = 1;
// AST_DEFINE
// test/leetcode.orng:149
	int32_t _7 = 0;
	int32_t _117_i = _7;
// AST_DEFINE
// test/leetcode.orng:150
	int32_t _8 = 0;
	int32_t _117_j = _8;
// AST_FOR
// test/leetcode.orng:151
begin_118:;
	int32_t _9 = _117_i;
	int32_t _10 = _117_j;
	int32_t _11 = _9 + _10;
	struct struct_3* _12 = _117_merged;
	int64_t _13 = _12->length;
	bool _14 = _11 < _13;
	if (!_14) goto end_118;
// AST_IFELSE
// test/leetcode.orng:152
	bool _15 = 0;
	int32_t _16 = _117_i;
	struct struct_3* _17 = _nums1;
	int64_t _18 = _17->length;
	bool _19 = _16 < _18;
	if (!_19) goto over_0;
	int32_t _20 = _117_j;
	struct struct_3* _21 = _nums2;
	int64_t _22 = _21->length;
	bool _23 = _20 < _22;
	_15 = _23;
over_0:;
	if (!_15) goto else_119;
	int32_t _24;
// AST_IFELSE
// test/leetcode.orng:153
	int32_t _25;
	int32_t _26 = _117_i;
	struct struct_3* _27 = _nums1;
	int64_t _28 = _27->data[_26];
	int32_t _29 = _117_j;
	struct struct_3* _30 = _nums2;
	int64_t _31 = _30->data[_29];
	bool _32 = _28 < _31;
	if (!_32) goto else_120;
	int32_t _33;
// AST_ASSIGN
// test/leetcode.orng:154
	int32_t _34 = _117_i;
	struct struct_3* _35 = _nums1;
	int64_t _36 = _35->data[_34];
	int32_t _37 = _117_i;
	int32_t _38 = _117_j;
	int32_t _39 = _37 + _38;
	struct struct_3* _40 = _117_merged;
	_40->data[_39] = _36;
// AST_ADD_ASSIGN
// test/leetcode.orng:155
	int32_t _41 = 1;
	_117_i += _41;
	_33 = _41;
	_25 = _33;
	goto end_120;
else_120:;
	int32_t _42;
// AST_ASSIGN
// test/leetcode.orng:157
	int32_t _43 = _117_j;
	struct struct_3* _44 = _nums2;
	int64_t _45 = _44->data[_43];
	int32_t _46 = _117_i;
	int32_t _47 = _117_j;
	int32_t _48 = _46 + _47;
	struct struct_3* _49 = _117_merged;
	_49->data[_48] = _45;
// AST_ADD_ASSIGN
// test/leetcode.orng:158
	int32_t _50 = 1;
	_117_j += _50;
	_42 = _50;
	_25 = _42;
end_120:;
	_24 = _25;
	goto end_119;
else_119:;
	int32_t _51 = _117_i;
	struct struct_3* _52 = _nums1;
	int64_t _53 = _52->length;
	bool _54 = _51 < _53;
	if (!_54) goto else_122;
	int32_t _55;
// AST_ASSIGN
// test/leetcode.orng:161
	int32_t _56 = _117_i;
	struct struct_3* _57 = _nums1;
	int64_t _58 = _57->data[_56];
	int32_t _59 = _117_i;
	int32_t _60 = _117_j;
	int32_t _61 = _59 + _60;
	struct struct_3* _62 = _117_merged;
	_62->data[_61] = _58;
// AST_ADD_ASSIGN
// test/leetcode.orng:162
	int32_t _63 = 1;
	_117_i += _63;
	_55 = _63;
	goto end_122;
else_122:;
	int32_t _64 = _117_j;
	struct struct_3* _65 = _nums2;
	int64_t _66 = _65->length;
	bool _67 = _64 < _66;
	if (!_67) goto end_123;
	int32_t _68;
// AST_ASSIGN
// test/leetcode.orng:164
	int32_t _69 = _117_j;
	struct struct_3* _70 = _nums2;
	int64_t _71 = _70->data[_69];
	int32_t _72 = _117_i;
	int32_t _73 = _117_j;
	int32_t _74 = _72 + _73;
	struct struct_3* _75 = _117_merged;
	_75->data[_74] = _71;
// AST_ADD_ASSIGN
// test/leetcode.orng:165
	int32_t _76 = 1;
	_117_j += _76;
	_68 = _76;
end_123:;
end_122:;
end_119:;
	goto begin_118;
end_118:;
// AST_IFELSE
// test/leetcode.orng:169
	float _77;
	struct struct_3* _78 = _117_merged;
	int64_t _79 = _78->length;
	int32_t _80 = 2;
	int64_t _81 = _79 % _80;
	int32_t _82 = 0;
	bool _83 = _81 == _82;
	if (!_83) goto else_124;
	int64_t _84;
// AST_DIVIDE
// test/leetcode.orng:170
	struct struct_3* _85 = _117_merged;
	int64_t _86 = _85->length;
	int32_t _87 = 2;
	int64_t _88 = _86 / _87;
	struct struct_3* _89 = _117_merged;
	int64_t _90 = _89->data[_88];
	struct struct_3* _91 = _117_merged;
	int64_t _92 = _91->length;
	int32_t _93 = 2;
	int64_t _94 = _92 / _93;
	int32_t _95 = 1;
	int64_t _96 = _94 + _95;
	struct struct_3* _97 = _117_merged;
	int64_t _98 = _97->data[_96];
	int64_t _99 = _90 + _98;
	int64_t _100 = _99;
	float _101 = 2.000000;
	int64_t _102 = _100 / _101;
	_84 = _102;
	_77 = _84;
	goto end_124;
else_124:;
	float _103;
// AST_CAST
// test/leetcode.orng:172
	struct struct_3* _104 = _117_merged;
	int64_t _105 = _104->length;
	int32_t _106 = 2;
	int64_t _107 = _105 / _106;
	struct struct_3* _108 = _117_merged;
	int64_t _109 = _108->data[_107];
	float _110 = (float)_109;
	_103 = _110;
	_77 = _103;
end_124:;
	_0 = _77;
	retval = _0;
return_block_117:;
	if (defer_0) {
	struct struct_3* _111 = _117_merged;
	free(_111);
	}
	return retval;
}

void test_leetcode_test_findMedianSortedArrays()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:177
	int32_t _1 = 1;
	int32_t _2 = 3;
	struct struct_4 _3 = {2, {_1, _2}};
	struct struct_4 _126_nums1 = _3;
// AST_DEFINE
// test/leetcode.orng:178
	int32_t _4 = 2;
	struct struct_11 _5 = {1, {_4}};
	struct struct_11 _126_nums2 = _5;
// AST_DEFINE
// test/leetcode.orng:180
	struct struct_4 _6 = _126_nums1;
	struct struct_4* _7 = &_6;
	struct struct_11 _8 = _126_nums2;
	struct struct_11* _9 = &_8;
	float _10 = test_leetcode_findMedianSortedArrays(_7, _9);
	float _126_ans = _10;
// AST_IFELSE
// test/leetcode.orng:182
	int64_t _11;
	float _12 = _126_ans;
	int32_t _13 = 2;
	bool _14 = _12 == _13;
	if (!_14) goto else_127;
	int64_t _15;
// AST_CALL
// test/leetcode.orng:183
	struct struct_1* _16 = &string_7;
	int64_t _17 = stdlib_system_println(_16);
	_15 = _17;
	_11 = _15;
	goto end_127;
else_127:;
	int64_t _18;
// AST_CALL
// test/leetcode.orng:185
	struct struct_1* _19 = &string_8;
	int64_t _20 = stdlib_system_println(_19);
	_18 = _20;
	_11 = _18;
end_127:;
	_0 = _11;
return_block_126:;
}

struct struct_1* test_leetcode_longestPalindrome(struct struct_1* _s)
{
	struct struct_1* retval;
	struct struct_1* _0;
// AST_DEFINE
// test/leetcode.orng:193
// AST_DEFINE
// test/leetcode.orng:203
	int32_t _1 = 0;
	int32_t _129_start = _1;
// AST_DEFINE
// test/leetcode.orng:204
	int32_t _2 = 0;
	int32_t _129_end = _2;
// AST_FOR
// test/leetcode.orng:205
	int32_t _3 = 0;
	int32_t _132_i = _3;
begin_132:;
	int32_t _4 = _132_i;
	struct struct_1* _5 = _s;
	int64_t _6 = _5->length;
	bool _7 = _4 < _6;
	if (!_7) goto end_132;
// AST_DEFINE
// test/leetcode.orng:206
	int64_t _8 = test_leetcode_expandAroundCenter(_s, _132_i, _132_i);
	int64_t _132_len1 = _8;
// AST_DEFINE
// test/leetcode.orng:207
	int32_t _9 = _132_i;
	int32_t _10 = 1;
	int32_t _11 = _9 + _10;
	int64_t _12 = test_leetcode_expandAroundCenter(_s, _132_i, _11);
	int64_t _132_len2 = _12;
// AST_DEFINE
// test/leetcode.orng:208
	double _13 = stdlib_math_max(_132_len1, _132_len2);
	double _132_len = _13;
// AST_IF
// test/leetcode.orng:209
	double _14 = _132_len;
	int32_t _15 = _129_end;
	int32_t _16 = _129_start;
	int32_t _17 = _15 - _16;
	bool _18 = _14 > _17;
	if (!_18) goto end_133;
	int32_t _19;
// AST_ASSIGN
// test/leetcode.orng:210
	int32_t _20 = _132_i;
	double _21 = _132_len;
	int32_t _22 = 1;
	double _23 = _21 - _22;
	double _24 = _23;
	int32_t _25 = 2;
	double _26 = _24 / _25;
	int32_t _27 = _20 - _26;
	_129_start = _27;
// AST_ASSIGN
// test/leetcode.orng:211
	int32_t _28 = _132_i;
	double _29 = _132_len;
	int32_t _30 = 2;
	double _31 = _29 / _30;
	int32_t _32 = _28 + _31;
	_129_end = _32;
	_19 = _32;
end_133:;
	int32_t _33 = 1;
	_132_i += _33;
	goto begin_132;
end_132:;
// AST_CALL
// test/leetcode.orng:214
	int32_t _34 = _129_end;
	int32_t _35 = 1;
	int32_t _36 = _34 + _35;
	struct struct_1* _37 = stdlib_string_substring(_s, _129_start, _36);
	_0 = _37;
	retval = _0;
return_block_129:;
	return retval;
}

int64_t test_leetcode_expandAroundCenter(struct struct_1* _s, int64_t _left, int64_t _right)
{
	int64_t retval;
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:194
	int64_t _1 = _left;
	int64_t _130_L = _1;
// AST_DEFINE
// test/leetcode.orng:195
	int64_t _2 = _right;
	int64_t _130_R = _2;
// AST_FOR
// test/leetcode.orng:196
	int64_t _3;
begin_131:;
	bool _4 = 0;
	bool _5 = 0;
	int64_t _6 = _130_L;
	int32_t _7 = 0;
	bool _8 = _6 >= _7;
	if (!_8) goto over_1;
	int64_t _9 = _130_R;
	struct struct_1* _10 = _s;
	int64_t _11 = _10->length;
	bool _12 = _9 < _11;
	_5 = _12;
over_1:;
	if (!_5) goto over_0;
	int64_t _13 = _130_L;
	struct struct_1* _14 = _s;
	int8_t _15 = _14->data[_13];
	int64_t _16 = _130_R;
	struct struct_1* _17 = _s;
	int8_t _18 = _17->data[_16];
	bool _19 = _15 == _18;
	_4 = _19;
over_0:;
	if (!_4) goto end_131;
	int64_t _20;
// AST_SUB_ASSIGN
// test/leetcode.orng:197
	int32_t _21 = 1;
	_130_L -= _21;
// AST_ADD_ASSIGN
// test/leetcode.orng:198
	int32_t _22 = 1;
	_130_R += _22;
	_20 = _22;
	_3 = _20;
	goto begin_131;
end_131:;
	_3 = _20;
// AST_SUBTRACT
// test/leetcode.orng:200
	int64_t _23 = _130_R;
	int64_t _24 = _130_L;
	int64_t _25 = _23 - _24;
	int32_t _26 = 1;
	int64_t _27 = _25 - _26;
	_0 = _27;
	retval = _0;
return_block_130:;
	return retval;
}

void test_leetcode_test_longestPalindrome()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:218
	struct struct_1* _1 = &string_9;
	struct struct_1* _134_s = _1;
// AST_DEFINE
// test/leetcode.orng:220
	struct struct_1* _2 = test_leetcode_longestPalindrome(_134_s);
	struct struct_1* _134_ans = _2;
// AST_IFELSE
// test/leetcode.orng:222
	int64_t _3;
	bool _4 = 1;
	struct struct_1* _5 = &string_10;
	bool _6 = stdlib_string_equals(_134_ans, _5);
	if (_6) goto over_0;
	struct struct_1* _7 = &string_11;
	bool _8 = stdlib_string_equals(_134_ans, _7);
	_4 = _8;
over_0:;
	if (!_4) goto else_135;
	int64_t _9;
// AST_CALL
// test/leetcode.orng:223
	struct struct_1* _10 = &string_12;
	int64_t _11 = stdlib_system_println(_10);
	_9 = _11;
	_3 = _9;
	goto end_135;
else_135:;
	int64_t _12;
// AST_CALL
// test/leetcode.orng:225
	struct struct_1* _13 = &string_13;
	int64_t _14 = stdlib_system_println(_13);
	_12 = _14;
	_3 = _12;
end_135:;
	_0 = _3;
return_block_134:;
}

struct struct_1* test_leetcode_convert(struct struct_1* _s, int64_t _numRows)
{
	struct struct_1* retval;
	int defer_0 = 0;
	struct struct_1* _0;
// AST_DEFINE
// test/leetcode.orng:234
	struct struct_1* _1 = _s;
	int64_t _2 = _1->length;
	struct struct_2* _3 = malloc(sizeof(signed int) + sizeof(struct struct_1*) * _2);
	_3->length = _2;
	for(int i = 0; i < _2; i++) {_3->data[i] = 0;}
	struct struct_2* _137_board = _3;
// AST_FOR
// test/leetcode.orng:235
	struct struct_1* _4;
	int32_t _5 = 0;
	int32_t _138_i = _5;
begin_138:;
	int32_t _6 = _138_i;
	struct struct_1* _7 = _s;
	int64_t _8 = _7->length;
	bool _9 = _6 < _8;
	if (!_9) goto end_138;
	struct struct_1* _10;
// AST_ASSIGN
// test/leetcode.orng:236
	int64_t _11 = _numRows;
	struct struct_1* _12 = malloc(sizeof(signed int) + sizeof(int8_t) * _11);
	_12->length = _11;
	for(int i = 0; i < _11; i++) {_12->data[i] = 0;}
	int32_t _13 = _138_i;
	struct struct_2* _14 = _137_board;
	_14->data[_13] = _12;
	_10 = _12;
	_4 = _10;
	int32_t _15 = 1;
	_138_i += _15;
	goto begin_138;
end_138:;
	_4 = _10;
// AST_DEFER
// test/leetcode.orng:238
	defer_0 = 1;
// AST_DEFINE
// test/leetcode.orng:245
	int32_t _16 = 0;
	int32_t _137_x = _16;
// AST_DEFINE
// test/leetcode.orng:246
	int32_t _17 = 0;
	int32_t _137_y = _17;
// AST_DEFINE
// test/leetcode.orng:247
	bool _18 = 0;
	bool _137_diagnolizing = _18;
// AST_FOR
// test/leetcode.orng:248
	int32_t _19 = 0;
	int32_t _141_i = _19;
begin_141:;
	int32_t _20 = _141_i;
	struct struct_1* _21 = _s;
	int64_t _22 = _21->length;
	bool _23 = _20 < _22;
	if (!_23) goto end_141;
// AST_ASSIGN
// test/leetcode.orng:249
	int32_t _24 = _141_i;
	struct struct_1* _25 = _s;
	int8_t _26 = _25->data[_24];
	int32_t _27 = _137_y;
	int32_t _28 = _137_x;
	struct struct_2* _29 = _137_board;
	struct struct_1* _30 = 	_29->data[_28];
_30->data[_27] = _26;
// AST_IFELSE
// test/leetcode.orng:250
	bool _31 = _137_diagnolizing;
	if (!_31) goto else_142;
// AST_SUB_ASSIGN
// test/leetcode.orng:251
	int32_t _32 = 1;
	_137_y -= _32;
// AST_ADD_ASSIGN
// test/leetcode.orng:252
	int32_t _33 = 1;
	_137_x += _33;
// AST_IF
// test/leetcode.orng:253
	int32_t _34 = _137_y;
	int32_t _35 = 0;
	bool _36 = _34 == _35;
	if (!_36) goto end_143;
	bool _37;
// AST_ASSIGN
// test/leetcode.orng:254
	bool _38 = 0;
	_137_diagnolizing = _38;
	_37 = _38;
end_143:;
	goto end_142;
else_142:;
// AST_ADD_ASSIGN
// test/leetcode.orng:257
	int32_t _39 = 1;
	_137_y += _39;
// AST_IF
// test/leetcode.orng:258
	int32_t _40 = _137_y;
	int64_t _41 = _numRows;
	bool _42 = _40 == _41;
	if (!_42) goto end_145;
	int32_t _43;
// AST_ASSIGN
// test/leetcode.orng:259
	bool _44 = 1;
	_137_diagnolizing = _44;
// AST_SUB_ASSIGN
// test/leetcode.orng:260
	int32_t _45 = 2;
	_137_y -= _45;
// AST_ADD_ASSIGN
// test/leetcode.orng:261
	int32_t _46 = 1;
	_137_x += _46;
	_43 = _46;
end_145:;
end_142:;
	int32_t _47 = 1;
	_141_i += _47;
	goto begin_141;
end_141:;
// AST_DEFINE
// test/leetcode.orng:266
	struct struct_1* _48 = _s;
	int64_t _49 = _48->length;
	struct struct_1* _50 = malloc(sizeof(signed int) + sizeof(int8_t) * _49);
	_50->length = _49;
	for(int i = 0; i < _49; i++) {_50->data[i] = 0;}
	struct struct_1* _137_retval = _50;
// AST_DEFINE
// test/leetcode.orng:267
	int32_t _51 = 0;
	int32_t _137_k = _51;
// AST_FOR
// test/leetcode.orng:268
	int32_t _52 = 0;
	int32_t _146_j = _52;
begin_146:;
	int32_t _53 = _146_j;
	int64_t _54 = _numRows;
	bool _55 = _53 < _54;
	if (!_55) goto end_146;
// AST_FOR
// test/leetcode.orng:269
	int32_t _56 = 0;
	int32_t _147_i = _56;
begin_147:;
	int32_t _57 = _147_i;
	struct struct_1* _58 = _s;
	int64_t _59 = _58->length;
	bool _60 = _57 < _59;
	if (!_60) goto end_147;
// AST_IF
// test/leetcode.orng:270
	int32_t _61 = _146_j;
	int32_t _62 = _147_i;
	struct struct_2* _63 = _137_board;
	struct struct_1* _64 = _63->data[_62];
	int8_t _65 = _64->data[_61];
	int8_t _66 = '\0';
	bool _67 = _65 != _66;
	if (!_67) goto end_148;
	int32_t _68;
// AST_ASSIGN
// test/leetcode.orng:271
	int32_t _69 = _146_j;
	int32_t _70 = _147_i;
	struct struct_2* _71 = _137_board;
	struct struct_1* _72 = _71->data[_70];
	int8_t _73 = _72->data[_69];
	int32_t _74 = _137_k;
	struct struct_1* _75 = _137_retval;
	_75->data[_74] = _73;
// AST_ADD_ASSIGN
// test/leetcode.orng:272
	int32_t _76 = 1;
	_137_k += _76;
	_68 = _76;
end_148:;
	int32_t _77 = 1;
	_147_i += _77;
	goto begin_147;
end_147:;
	int32_t _78 = 1;
	_146_j += _78;
	goto begin_146;
end_146:;
// AST_IDENT
// test/leetcode.orng:277
	struct struct_1* _79 = _137_retval;
	_0 = _79;
	retval = _0;
return_block_137:;
	if (defer_0) {
// AST_FOR
// test/leetcode.orng:239
	int32_t _80 = 0;
	int32_t _177_i = _80;
begin_177:;
	int32_t _81 = _177_i;
	struct struct_1* _82 = _s;
	int64_t _83 = _82->length;
	bool _84 = _81 < _83;
	if (!_84) goto end_177;
// AST_FREE
// test/leetcode.orng:240
	int32_t _85 = _177_i;
	struct struct_2* _86 = _137_board;
	struct struct_1* _87 = _86->data[_85];
	free(_87);
	int32_t _88 = 1;
	_177_i += _88;
	goto begin_177;
end_177:;
// AST_FREE
// test/leetcode.orng:242
	struct struct_2* _89 = _137_board;
	free(_89);
	}
	return retval;
}

void test_leetcode_test_convert()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:281
	struct struct_1* _1 = &string_14;
	int32_t _2 = 3;
	struct struct_1* _3 = test_leetcode_convert(_1, _2);
	struct struct_1* _149_ans = _3;
// AST_IFELSE
// test/leetcode.orng:283
	int64_t _4;
	struct struct_1* _5 = &string_15;
	bool _6 = stdlib_string_equals(_149_ans, _5);
	if (!_6) goto else_150;
	int64_t _7;
// AST_CALL
// test/leetcode.orng:284
	struct struct_1* _8 = &string_16;
	int64_t _9 = stdlib_system_println(_8);
	_7 = _9;
	_4 = _7;
	goto end_150;
else_150:;
	int64_t _10;
// AST_CALL
// test/leetcode.orng:286
	struct struct_1* _11 = &string_17;
	int64_t _12 = stdlib_system_println(_11);
	_10 = _12;
	_4 = _10;
end_150:;
	_0 = _4;
return_block_149:;
}

struct struct_6* test_leetcode_reverseList(struct struct_6* _list)
{
	struct struct_6* retval;
	struct struct_6* _0;
// AST_DEFINE
// test/leetcode.orng:296
	struct struct_6* _1 = 0;
	struct struct_6* _152_prev = _1;
// AST_DEFINE
// test/leetcode.orng:297
	struct struct_6* _2 = _list;
	struct struct_6* _152_curr = _2;
// AST_DEFINE
// test/leetcode.orng:298
	struct struct_6* _3 = 0;
	struct struct_6* _152_next = _3;
// AST_FOR
// test/leetcode.orng:299
	struct struct_6* _4;
begin_153:;
	struct struct_6* _5 = _152_curr;
	void* _6 = 0;
	bool _7 = _5 != _6;
	if (!_7) goto end_153;
	struct struct_6* _8;
// AST_ASSIGN
// test/leetcode.orng:300
	struct struct_6* _9 = _152_curr;
	struct struct_6* _10 = _9->next;
	_152_next = _10;
// AST_ASSIGN
// test/leetcode.orng:301
	struct struct_6* _11 = _152_prev;
	_152_curr->next = _11;
// AST_ASSIGN
// test/leetcode.orng:302
	struct struct_6* _12 = _152_curr;
	_152_prev = _12;
// AST_ASSIGN
// test/leetcode.orng:303
	struct struct_6* _13 = _152_next;
	_152_curr = _13;
	_8 = _13;
	_4 = _8;
	goto begin_153;
end_153:;
	_4 = _8;
// AST_ASSIGN
// test/leetcode.orng:305
	struct struct_6* _14 = _152_prev;
	_list = _14;
// AST_RETURN
// test/leetcode.orng:306
	struct struct_6* _15 = _list;
	retval = _15;
	goto return_block_152;
	_0 = _15;
	retval = _0;
return_block_152:;
	return retval;
}

int64_t test_leetcode_reverse(int64_t _x)
{
	int64_t retval;
	struct struct_6* _0 = test_leetcode_convertToList(_x);
	struct struct_6* _1 = test_leetcode_reverseList(_0);
	int64_t _2 = test_leetcode_convertToInt(_1);
	retval = _2;
return_block_:;
	return retval;
}

void test_leetcode_test_reverse()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:311
	int32_t _1 = 123;
	int64_t _2 = test_leetcode_reverse(_1);
	int64_t _154_ans = _2;
// AST_IFELSE
// test/leetcode.orng:313
	int64_t _3;
	int64_t _4 = _154_ans;
	int32_t _5 = 321;
	bool _6 = _4 == _5;
	if (!_6) goto else_155;
	int64_t _7;
// AST_CALL
// test/leetcode.orng:314
	struct struct_1* _8 = &string_18;
	int64_t _9 = stdlib_system_println(_8);
	_7 = _9;
	_3 = _7;
	goto end_155;
else_155:;
	int64_t _10;
// AST_CALL
// test/leetcode.orng:316
	struct struct_1* _11 = &string_19;
	int64_t _12 = stdlib_system_println(_11);
	_10 = _12;
	_3 = _10;
end_155:;
	_0 = _3;
return_block_154:;
}

int64_t test_leetcode_myAtoi(struct struct_1* _s)
{
	int64_t retval;
	int32_t _0;
// AST_DEFINE
// test/leetcode.orng:325
	int64_t _1 = 0;
	int64_t _157_x = _1;
// AST_DEFINE
// test/leetcode.orng:326
	int64_t _2 = 0;
	int64_t _157_i = _2;
// AST_DEFINE
// test/leetcode.orng:327
	bool _3 = 1;
	bool _157_sign = _3;
// AST_FOR
// test/leetcode.orng:330
	int64_t _4;
begin_158:;
	bool _5 = 0;
	int64_t _6 = _157_i;
	struct struct_1* _7 = _s;
	int64_t _8 = _7->length;
	bool _9 = _6 < _8;
	if (!_9) goto over_0;
	int64_t _10 = _157_i;
	struct struct_1* _11 = _s;
	int8_t _12 = _11->data[_10];
	int8_t _13 = ' ';
	bool _14 = _12 == _13;
	_5 = _14;
over_0:;
	if (!_5) goto end_158;
	int64_t _15;
// AST_ADD_ASSIGN
// test/leetcode.orng:330
	int32_t _16 = 1;
	_157_i += _16;
	_15 = _16;
	_4 = _15;
	goto begin_158;
end_158:;
	_4 = _15;
// AST_IFELSE
// test/leetcode.orng:333
	int64_t _17 = _157_i;
	struct struct_1* _18 = _s;
	int64_t _19 = _18->length;
	bool _20 = _17 == _19;
	if (!_20) goto else_159;
	int32_t _21;
// AST_RETURN
// test/leetcode.orng:334
	int32_t _22 = 0;
	retval = _22;
	goto return_block_157;
	_21 = _22;
	goto end_159;
else_159:;
	int64_t _23 = _157_i;
	struct struct_1* _24 = _s;
	int8_t _25 = _24->data[_23];
	int8_t _26 = '+';
	bool _27 = _25 == _26;
	if (!_27) goto else_160;
	int64_t _28;
// AST_ASSIGN
// test/leetcode.orng:336
	bool _29 = 1;
	_157_sign = _29;
// AST_ADD_ASSIGN
// test/leetcode.orng:337
	int32_t _30 = 1;
	_157_i += _30;
	_28 = _30;
	goto end_160;
else_160:;
	int64_t _31 = _157_i;
	struct struct_1* _32 = _s;
	int8_t _33 = _32->data[_31];
	int8_t _34 = '-';
	bool _35 = _33 == _34;
	if (!_35) goto end_161;
	int64_t _36;
// AST_ASSIGN
// test/leetcode.orng:339
	bool _37 = 0;
	_157_sign = _37;
// AST_ADD_ASSIGN
// test/leetcode.orng:340
	int32_t _38 = 1;
	_157_i += _38;
	_36 = _38;
end_161:;
end_160:;
end_159:;
// AST_FOR
// test/leetcode.orng:344
	int64_t _39;
begin_162:;
	bool _40 = 0;
	int64_t _41 = _157_i;
	struct struct_1* _42 = _s;
	int64_t _43 = _42->length;
	bool _44 = _41 < _43;
	if (!_44) goto over_1;
	int64_t _45 = _157_i;
	struct struct_1* _46 = _s;
	int8_t _47 = _46->data[_45];
	bool _48 = isdigit(_47);
	_40 = _48;
over_1:;
	if (!_40) goto end_162;
	int64_t _49;
// AST_ASSIGN
// test/leetcode.orng:345
	int64_t _50 = _157_x;
	int32_t _51 = 10;
	int64_t _52 = _50 * _51;
	int64_t _53 = _157_i;
	struct struct_1* _54 = _s;
	int8_t _55 = _54->data[_53];
	int64_t _56 = (int64_t)_55;
	int64_t _57 = _52 + _56;
	int8_t _58 = '0';
	int64_t _59 = (int64_t)_58;
	int64_t _60 = _57 - _59;
	_157_x = _60;
	_49 = _60;
	_39 = _49;
	int32_t _61 = 1;
	_157_i += _61;
	goto begin_162;
end_162:;
	_39 = _49;
// AST_IFELSE
// test/leetcode.orng:348
	int32_t _62;
	bool _63 = _157_sign;
	if (!_63) goto else_163;
	int64_t _64;
// AST_IDENT
// test/leetcode.orng:348
	int64_t _65 = _157_x;
	_64 = _65;
	_62 = _64;
	goto end_163;
else_163:;
	int64_t _66 = _157_x;
	int32_t _67 = -_66;
	_62 = _67;
end_163:;
	_0 = _62;
	retval = _0;
return_block_157:;
	return retval;
}

void test_leetcode_test_myAtoi()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:352
	struct struct_1* _1 = &string_20;
	struct struct_1* _164_s = _1;
// AST_DEFINE
// test/leetcode.orng:354
	int64_t _2 = test_leetcode_myAtoi(_164_s);
	int64_t _164_ans = _2;
// AST_IFELSE
// test/leetcode.orng:356
	int64_t _3;
	int64_t _4 = _164_ans;
	int32_t _5 = 42;
	bool _6 = _4 == _5;
	if (!_6) goto else_165;
	int64_t _7;
// AST_CALL
// test/leetcode.orng:357
	struct struct_1* _8 = &string_21;
	int64_t _9 = stdlib_system_println(_8);
	_7 = _9;
	_3 = _7;
	goto end_165;
else_165:;
	int64_t _10;
// AST_CALL
// test/leetcode.orng:359
	struct struct_1* _11 = &string_22;
	int64_t _12 = stdlib_system_println(_11);
	_10 = _12;
	_3 = _10;
end_165:;
	_0 = _3;
return_block_164:;
}

int64_t test_testModule_main(struct struct_2* _args)
{
	int64_t retval;
	int32_t _0;
// AST_CALL
// test/testModule.orng:3
	test_leetcode_test_all();
// AST_INT
// test/testModule.orng:4
	int32_t _1 = 0;
	_0 = _1;
	retval = _0;
return_block_175:;
	return retval;
}

double stdlib_math_max(double _x, double _y)
{
	double retval;
	double _0;
// AST_IFELSE
// stdlib/math.orng:9
	double _1;
	double _2 = _x;
	double _3 = _y;
	bool _4 = _2 > _3;
	if (!_4) goto else_4;
	double _5;
// AST_RETURN
// stdlib/math.orng:10
	double _6 = _x;
	retval = _6;
	goto return_block_3;
	_5 = _6;
	_1 = _5;
	goto end_4;
else_4:;
	double _7;
// AST_RETURN
// stdlib/math.orng:12
	double _8 = _y;
	retval = _8;
	goto return_block_3;
	_7 = _8;
	_1 = _7;
end_4:;
	_0 = _1;
	retval = _0;
return_block_3:;
	return retval;
}

bool stdlib_string_equals(struct struct_1* _a, struct struct_1* _b)
{
	bool retval;
	bool _0;
// AST_IFELSE
// stdlib/string.orng:30
	bool _1;
	struct struct_1* _2 = _a;
	int64_t _3 = _2->length;
	struct struct_1* _4 = _b;
	int64_t _5 = _4->length;
	bool _6 = _3 != _5;
	if (!_6) goto else_13;
	bool _7;
// AST_RETURN
// stdlib/string.orng:31
	bool _8 = 0;
	retval = _8;
	goto return_block_12;
	_7 = _8;
	_1 = _7;
	goto end_13;
else_13:;
	bool _9;
// AST_FOR
// stdlib/string.orng:33
	int32_t _10 = 0;
	int32_t _15_i = _10;
begin_15:;
	int32_t _11 = _15_i;
	struct struct_1* _12 = _a;
	int64_t _13 = _12->length;
	bool _14 = _11 < _13;
	if (!_14) goto end_15;
// AST_IF
// stdlib/string.orng:34
	int32_t _15 = _15_i;
	struct struct_1* _16 = _a;
	int8_t _17 = _16->data[_15];
	int32_t _18 = _15_i;
	struct struct_1* _19 = _b;
	int8_t _20 = _19->data[_18];
	bool _21 = _17 != _20;
	if (!_21) goto end_16;
	bool _22;
// AST_RETURN
// stdlib/string.orng:35
	bool _23 = 0;
	retval = _23;
	goto return_block_12;
	_22 = _23;
end_16:;
	int32_t _24 = 1;
	_15_i += _24;
	goto begin_15;
end_15:;
// AST_RETURN
// stdlib/string.orng:38
	bool _25 = 1;
	retval = _25;
	goto return_block_12;
	_9 = _25;
	_1 = _9;
end_13:;
	_0 = _1;
	retval = _0;
return_block_12:;
	return retval;
}

struct struct_1* stdlib_string_substring(struct struct_1* _s, int64_t _start, int64_t _end)
{
	struct struct_1* retval;
	struct struct_1* _0;
// AST_DEFINE
// stdlib/string.orng:43
	int64_t _1 = _end;
	int64_t _2 = _start;
	int64_t _3 = _1 - _2;
	struct struct_1* _4 = malloc(sizeof(signed int) + sizeof(int8_t) * _3);
	_4->length = _3;
	for(int i = 0; i < _3; i++) {_4->data[i] = 0;}
	struct struct_1* _17_retval = _4;
// AST_FOR
// stdlib/string.orng:44
	int8_t _5;
	int32_t _6 = 0;
	int32_t _18_i = _6;
begin_18:;
	int32_t _7 = _18_i;
	struct struct_1* _8 = _17_retval;
	int64_t _9 = _8->length;
	bool _10 = _7 < _9;
	if (!_10) goto end_18;
	int8_t _11;
// AST_ASSIGN
// stdlib/string.orng:45
	int64_t _12 = _start;
	int32_t _13 = _18_i;
	int64_t _14 = _12 + _13;
	struct struct_1* _15 = _s;
	int8_t _16 = _15->data[_14];
	int32_t _17 = _18_i;
	struct struct_1* _18 = _17_retval;
	_18->data[_17] = _16;
	_11 = _16;
	_5 = _11;
	int32_t _19 = 1;
	_18_i += _19;
	goto begin_18;
end_18:;
	_5 = _11;
// AST_RETURN
// stdlib/string.orng:47
	struct struct_1* _20 = _17_retval;
	retval = _20;
	goto return_block_17;
	_0 = _20;
	retval = _0;
return_block_17:;
	return retval;
}

int main(int argc, char** argv)
{
	struct struct_2* args = calloc(sizeof(struct struct_2*) + sizeof(struct struct_1*) * argc, 1);
	args->length = argc;
	for (int  i = 0; i < argc; i++) {
		args->data[i] = calloc(sizeof(struct struct_1*) + sizeof(char) * strlen(argv[i]) + 1, 1);
		args->data[i]->length = strlen(argv[i] + 1);
		memcpy(&args->data[i]->data, argv[i], strlen(argv[i]) + 1);
	}
	int retval = test_testModule_main(args);
	free(args);
	return retval;
}
#endif
