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
	int64_t val;
	struct struct_4* next;
};

struct struct_5 {
	struct struct_4* _l;
};

struct struct_6 {
	int64_t _i;
};

struct struct_7 {
	int64_t length;
	bool* data;
};

struct struct_8 {
	struct struct_1 _str;
	int64_t _i;
	int64_t _j;
};

struct struct_9 {
	int64_t length;
	struct struct_1* data;
};

struct struct_10 {
	struct struct_4* _list;
};

/* Verbatim code */
int stdlib_system_println(struct struct_1 _format, ...) {
    va_list _25_args;
    va_start(_25_args, _format.data);
    int retval = vprintf(_format.data, _25_args);
    va_end(_25_args);
    char newLine[2] = {'\n', '\0'};
    printf(newLine);
    return retval;
}

/* Forward string declarations */
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
struct struct_1 string_23;
struct struct_1 string_24;
struct struct_1 string_25;
struct struct_1 string_26;
struct struct_1 string_27;
struct struct_1 string_28;

/* Enums */

/* Forward global declarations */

/* Forward function and procedure declarations */
void test_leetcode_test_all();
struct struct_3 test_leetcode_twoSum(struct struct_3 _nums, int64_t _target);
void test_leetcode_test_twoSum();
int64_t test_leetcode_convertToInt(struct struct_4* _l);
struct struct_4* test_leetcode_convertToList(int64_t _i);
struct struct_4* test_leetcode_addTwoNumbers(struct struct_4* _l1, struct struct_4* _l2);
void test_leetcode_test_addTwoNumbers();
int64_t test_leetcode_lengthOfLongestSubstring(struct struct_1 _str);
bool test_leetcode_areDistinct(struct struct_1 _str, int64_t _i, int64_t _j);
void test_leetcode_test_lengthOfLongestSubstring();
float test_leetcode_findMedianSortedArrays(struct struct_3 _nums1, struct struct_3 _nums2);
void test_leetcode_test_findMedianSortedArrays();
struct struct_1 test_leetcode_longestPalindrome(struct struct_1 _s);
int64_t test_leetcode_expandAroundCenter(struct struct_1 _s, int64_t _left, int64_t _right);
void test_leetcode_test_longestPalindrome();
struct struct_1 test_leetcode_convert(struct struct_1 _s, int64_t _numRows);
void test_leetcode_test_convert();
struct struct_4* test_leetcode_reverseList(struct struct_4* _list);
int64_t test_leetcode_reverse(int64_t _x);
void test_leetcode_test_reverse();
int64_t test_leetcode_myAtoi(struct struct_1 _s);
void test_leetcode_test_myAtoi();
bool test_leetcode_isPalindrome(int64_t _x);
void test_leetcode_test_isPalindrome();
int64_t test_testModule_main(struct struct_2 _args);
double stdlib_math_max(double _x, double _y);
bool stdlib_string_equals(struct struct_1 _a, struct struct_1 _b);
struct struct_1 stdlib_string_substring(struct struct_1 _s, int64_t _start, int64_t _end);

#ifndef ORANGE_PROGRAM_27390
#define ORANGE_PROGRAM_27390

/* String definitions */
struct struct_1 string_4 = {15, (char[]){'t', 'w', 'o', 'S', 'u', 'm', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_5 = {20, (char[]){'t', 'w', 'o', 'S', 'u', 'm', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', ' ', '%', 'd', ' ', '%', 'd', '\0'}};
struct struct_1 string_6 = {22, (char[]){'a', 'd', 'd', 'T', 'w', 'o', 'N', 'u', 'm', 'b', 'e', 'r', 's', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_7 = {21, (char[]){'a', 'd', 'd', 'T', 'w', 'o', 'N', 'u', 'm', 'b', 'e', 'r', 's', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
struct struct_1 string_8 = {8, (char[]){'a', 'b', 'c', 'a', 'b', 'c', 'b', 'b', '\0'}};
struct struct_1 string_9 = {33, (char[]){'l', 'e', 'n', 'g', 't', 'h', 'O', 'f', 'L', 'o', 'n', 'g', 'e', 's', 't', 'S', 'u', 'b', 's', 't', 'r', 'i', 'n', 'g', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_10 = {35, (char[]){'l', 'e', 'n', 'g', 't', 'h', 'O', 'f', 'L', 'o', 'n', 'g', 'e', 's', 't', 'S', 'u', 'b', 's', 't', 'r', 'i', 'n', 'g', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', ' ', '%', 'd', '\0'}};
struct struct_1 string_11 = {31, (char[]){'f', 'i', 'n', 'd', 'M', 'e', 'd', 'i', 'a', 'n', 'S', 'o', 'r', 't', 'e', 'd', 'A', 'r', 'r', 'a', 'y', 's', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_12 = {33, (char[]){'f', 'i', 'n', 'd', 'M', 'e', 'd', 'i', 'a', 'n', 'S', 'o', 'r', 't', 'e', 'd', 'A', 'r', 'r', 'a', 'y', 's', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', ' ', '%', 'f', '\0'}};
struct struct_1 string_13 = {5, (char[]){'b', 'a', 'b', 'a', 'd', '\0'}};
struct struct_1 string_14 = {3, (char[]){'b', 'a', 'b', '\0'}};
struct struct_1 string_15 = {3, (char[]){'a', 'b', 'a', '\0'}};
struct struct_1 string_16 = {26, (char[]){'l', 'o', 'n', 'g', 'e', 's', 't', 'P', 'a', 'l', 'i', 'n', 'd', 'r', 'o', 'm', 'e', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_17 = {25, (char[]){'l', 'o', 'n', 'g', 'e', 's', 't', 'P', 'a', 'l', 'i', 'n', 'd', 'r', 'o', 'm', 'e', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
struct struct_1 string_18 = {14, (char[]){'P', 'A', 'Y', 'P', 'A', 'L', 'I', 'S', 'H', 'I', 'R', 'I', 'N', 'G', '\0'}};
struct struct_1 string_19 = {14, (char[]){'P', 'A', 'H', 'N', 'A', 'P', 'L', 'S', 'I', 'I', 'G', 'Y', 'I', 'R', '\0'}};
struct struct_1 string_20 = {16, (char[]){'c', 'o', 'n', 'v', 'e', 'r', 't', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_21 = {15, (char[]){'c', 'o', 'n', 'v', 'e', 'r', 't', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
struct struct_1 string_22 = {16, (char[]){'r', 'e', 'v', 'e', 'r', 's', 'e', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_23 = {15, (char[]){'r', 'e', 'v', 'e', 'r', 's', 'e', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
struct struct_1 string_24 = {2, (char[]){'4', '2', '\0'}};
struct struct_1 string_25 = {15, (char[]){'m', 'y', 'A', 't', 'o', 'i', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_26 = {14, (char[]){'m', 'y', 'A', 't', 'o', 'i', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
struct struct_1 string_27 = {21, (char[]){'i', 's', 'P', 'a', 'l', 'i', 'n', 'd', 'r', 'o', 'm', 'e', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_28 = {20, (char[]){'i', 's', 'P', 'a', 'l', 'i', 'n', 'd', 'r', 'o', 'm', 'e', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};

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
// AST_CALL
// test/leetcode.orng:13
	test_leetcode_test_isPalindrome();
return_block_92:;
}

struct struct_3 test_leetcode_twoSum(struct struct_3 _nums, int64_t _target)
{
	struct struct_3 retval;
	struct struct_3 _0;
// AST_DEFINE
// test/leetcode.orng:34
	int64_t _1 = 2;
	struct struct_3 _2 = {_1, malloc(sizeof(int64_t) * _1)};
	_2.length = _1;
	for(int i = 0; i < _1; i++) {_2.data[i] = 0;}
	struct struct_3 _97_ans = _2;
// AST_ASSIGN
// test/leetcode.orng:35
	int64_t _3 = 1;
	int64_t _4 = -_3;
	int64_t _5 = 0;
	_97_ans.data[_5] = _4;
// AST_ASSIGN
// test/leetcode.orng:36
	int64_t _6 = 1;
	int64_t _7 = -_6;
	int64_t _8 = 1;
	_97_ans.data[_8] = _7;
// AST_FOR
// test/leetcode.orng:37
	int64_t _9 = 0;
	int64_t _98_i = _9;
begin_98:;
	int64_t _10 = _98_i;
	struct struct_3 _11 = _nums;
	int64_t _12 = _11.length;
	int64_t _13 = 1;
	int64_t _14 = _12 - _13;
	bool _15 = _10 < _14;
	if (!_15) goto end_98;
// AST_FOR
// test/leetcode.orng:38
	int64_t _16 = _98_i;
	int64_t _17 = 1;
	int64_t _18 = _16 + _17;
	int64_t _99_j = _18;
begin_99:;
	int64_t _19 = _99_j;
	struct struct_3 _20 = _nums;
	int64_t _21 = _20.length;
	bool _22 = _19 < _21;
	if (!_22) goto end_99;
// AST_IF
// test/leetcode.orng:39
	int64_t _23 = _98_i;
	struct struct_3 _24 = _nums;
	int64_t _25 = _24.data[_23];
	int64_t _26 = _99_j;
	struct struct_3 _27 = _nums;
	int64_t _28 = _27.data[_26];
	int64_t _29 = _25 + _28;
	int64_t _30 = _target;
	bool _31 = _29 == _30;
	if (!_31) goto end_100;
	struct struct_3 _32;
// AST_ASSIGN
// test/leetcode.orng:40
	int64_t _33 = _98_i;
	int64_t _34 = 0;
	_97_ans.data[_34] = _33;
// AST_ASSIGN
// test/leetcode.orng:41
	int64_t _35 = _99_j;
	int64_t _36 = 1;
	_97_ans.data[_36] = _35;
// AST_RETURN
// test/leetcode.orng:42
	struct struct_3 _37 = _97_ans;
	retval = _37;
	goto return_block_97;
	_32 = _37;
end_100:;
	int64_t _38 = 1;
	_99_j += _38;
	goto begin_99;
end_99:;
	int64_t _39 = 1;
	_98_i += _39;
	goto begin_98;
end_98:;
// AST_RETURN
// test/leetcode.orng:46
	struct struct_3 _40 = _97_ans;
	retval = _40;
	goto return_block_97;
	_0 = _40;
	retval = _0;
return_block_97:;
	return retval;
}

void test_leetcode_test_twoSum()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:50
	int64_t* _1 = 2;
	int64_t* _2 = 7;
	int64_t* _3 = 11;
	int64_t* _4 = 15;
	struct struct_3 _5 = {4, (int64_t*[]){_1, _2, _3, _4}};
	struct struct_3 _101_nums = _5;
// AST_DEFINE
// test/leetcode.orng:51
	int64_t _6 = 9;
	int64_t _101_target = _6;
// AST_DEFINE
// test/leetcode.orng:53
	struct struct_3 _7 = test_leetcode_twoSum(_101_nums, _101_target);
	struct struct_3 _101_ans = _7;
// AST_IFELSE
// test/leetcode.orng:55
	int64_t _8;
	int64_t _9 = 0;
	struct struct_3 _10 = _101_ans;
	int64_t _11 = _10.data[_9];
	struct struct_3 _12 = _101_nums;
	int64_t _13 = _12.data[_11];
	int64_t _14 = 1;
	struct struct_3 _15 = _101_ans;
	int64_t _16 = _15.data[_14];
	struct struct_3 _17 = _101_nums;
	int64_t _18 = _17.data[_16];
	int64_t _19 = _13 + _18;
	int64_t _20 = _101_target;
	bool _21 = _19 == _20;
	if (!_21) goto else_102;
	int64_t _22;
// AST_CALL
// test/leetcode.orng:56
	struct struct_1 _23 = string_4;
	int64_t _24 = stdlib_system_println(_23);
	_22 = _24;
	_8 = _22;
	goto end_102;
else_102:;
	int64_t _25;
// AST_CALL
// test/leetcode.orng:58
	struct struct_1 _26 = string_5;
	int64_t _27 = 0;
	struct struct_3 _28 = _101_ans;
	int64_t _29 = _28.data[_27];
	int64_t _30 = 1;
	struct struct_3 _31 = _101_ans;
	int64_t _32 = _31.data[_30];
	int64_t _33 = stdlib_system_println(_26, _29, _32);
	_25 = _33;
	_8 = _25;
end_102:;
	_0 = _8;
return_block_101:;
}

int64_t test_leetcode_convertToInt(struct struct_4* _l)
{
	int64_t retval;
	int64_t _0;
	struct struct_4* _1 = _l;
	struct struct_4* _2 = _1->next;
	void* _3 = 0;
	bool _4 = _2 == _3;
	if (!_4) goto else_104;
	int64_t _5;
// AST_DOT
// test/leetcode.orng:74
	struct struct_4* _6 = _l;
	int64_t _7 = _6->val;
	_5 = _7;
	_0 = _5;
	goto end_104;
else_104:;
	int64_t _8;
// AST_ADD
// test/leetcode.orng:76
	struct struct_4* _9 = _l;
	int64_t _10 = _9->val;
	struct struct_4* _11 = _l;
	struct struct_4* _12 = _11->next;
	int64_t _13 = test_leetcode_convertToInt(_12);
	int64_t _14 = 10;
	int64_t _15 = _13 * _14;
	int64_t _16 = _10 + _15;
	_8 = _16;
	_0 = _8;
end_104:;
	retval = _0;
return_block_105:;
	return retval;
}

struct struct_4* test_leetcode_convertToList(int64_t _i)
{
	struct struct_4* retval;
	struct struct_4* _0;
// AST_DEFINE
// test/leetcode.orng:80
	struct struct_4* _1 = calloc(sizeof(struct struct_4), 1);
	*_1 = ((struct struct_4){0, 0});
	struct struct_4* _106_retval = _1;
// AST_IFELSE
// test/leetcode.orng:81
	struct struct_4 _2;
	int64_t _3 = _i;
	int64_t _4 = 10;
	bool _5 = _3 < _4;
	if (!_5) goto else_107;
	struct struct_4 _6;
// AST_ASSIGN
// test/leetcode.orng:82
	int64_t _7 = _i;
	void* _8 = 0;
	struct struct_4 _9 = {_7, _8};
	*_106_retval = _9;
	_6 = _9;
	_2 = _6;
	goto end_107;
else_107:;
	struct struct_4 _10;
// AST_ASSIGN
// test/leetcode.orng:84
	int64_t _11 = _i;
	int64_t _12 = 10;
	int64_t _13 = _11 % _12;
	int64_t _14 = _i;
	int64_t _15 = 10;
	int64_t _16 = _14 / _15;
	struct struct_4* _17 = test_leetcode_convertToList(_16);
	struct struct_4 _18 = {_13, _17};
	*_106_retval = _18;
	_10 = _18;
	_2 = _10;
end_107:;
// AST_RETURN
// test/leetcode.orng:86
	struct struct_4* _19 = _106_retval;
	retval = _19;
	goto return_block_106;
	_0 = _19;
	retval = _0;
return_block_106:;
	return retval;
}

struct struct_4* test_leetcode_addTwoNumbers(struct struct_4* _l1, struct struct_4* _l2)
{
	struct struct_4* retval;
	int64_t _0 = test_leetcode_convertToInt(_l1);
	int64_t _1 = test_leetcode_convertToInt(_l2);
	int64_t _2 = _0 + _1;
	struct struct_4* _3 = test_leetcode_convertToList(_2);
	retval = _3;
return_block_:;
	return retval;
}

void test_leetcode_test_addTwoNumbers()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:93
	struct struct_4* _1 = calloc(sizeof(struct struct_4), 1);
	*_1 = ((struct struct_4){0, 0});
	struct struct_4* _109_l1_c = _1;
// AST_ASSIGN
// test/leetcode.orng:94
	int64_t _2 = 3;
	void* _3 = 0;
	struct struct_4 _4 = {_2, _3};
	*_109_l1_c = _4;
// AST_DEFINE
// test/leetcode.orng:95
	struct struct_4* _5 = calloc(sizeof(struct struct_4), 1);
	*_5 = ((struct struct_4){0, 0});
	struct struct_4* _109_l1_b = _5;
// AST_ASSIGN
// test/leetcode.orng:96
	int64_t _6 = 4;
	struct struct_4* _7 = _109_l1_c;
	struct struct_4 _8 = {_6, _7};
	*_109_l1_b = _8;
// AST_DEFINE
// test/leetcode.orng:97
	struct struct_4* _9 = calloc(sizeof(struct struct_4), 1);
	*_9 = ((struct struct_4){0, 0});
	struct struct_4* _109_l1 = _9;
// AST_ASSIGN
// test/leetcode.orng:98
	int64_t _10 = 2;
	struct struct_4* _11 = _109_l1_b;
	struct struct_4 _12 = {_10, _11};
	*_109_l1 = _12;
// AST_DEFINE
// test/leetcode.orng:99
	struct struct_4* _13 = calloc(sizeof(struct struct_4), 1);
	*_13 = ((struct struct_4){0, 0});
	struct struct_4* _109_l2_c = _13;
// AST_ASSIGN
// test/leetcode.orng:100
	int64_t _14 = 4;
	void* _15 = 0;
	struct struct_4 _16 = {_14, _15};
	*_109_l2_c = _16;
// AST_DEFINE
// test/leetcode.orng:101
	struct struct_4* _17 = calloc(sizeof(struct struct_4), 1);
	*_17 = ((struct struct_4){0, 0});
	struct struct_4* _109_l2_b = _17;
// AST_ASSIGN
// test/leetcode.orng:102
	int64_t _18 = 6;
	struct struct_4* _19 = _109_l2_c;
	struct struct_4 _20 = {_18, _19};
	*_109_l2_b = _20;
// AST_DEFINE
// test/leetcode.orng:103
	struct struct_4* _21 = calloc(sizeof(struct struct_4), 1);
	*_21 = ((struct struct_4){0, 0});
	struct struct_4* _109_l2 = _21;
// AST_ASSIGN
// test/leetcode.orng:104
	int64_t _22 = 5;
	struct struct_4* _23 = _109_l2_b;
	struct struct_4 _24 = {_22, _23};
	*_109_l2 = _24;
// AST_DEFINE
// test/leetcode.orng:106
	struct struct_4* _25 = test_leetcode_addTwoNumbers(_109_l1, _109_l2);
	struct struct_4* _109_ans = _25;
// AST_IFELSE
// test/leetcode.orng:108
	int64_t _26;
	bool _27 = 0;
	bool _28 = 0;
	struct struct_4* _29 = _109_ans;
	int64_t _30 = _29->val;
	int64_t _31 = 7;
	bool _32 = _30 == _31;
	if (!_32) goto over_1;
	struct struct_4* _33 = _109_ans;
	struct struct_4* _34 = _33->next;
	int64_t _35 = _34->val;
	int64_t _36 = 0;
	bool _37 = _35 == _36;
	_28 = _37;
over_1:;
	if (!_28) goto over_0;
	struct struct_4* _38 = _109_ans;
	struct struct_4* _39 = _38->next;
	struct struct_4* _40 = _39->next;
	int64_t _41 = _40->val;
	int64_t _42 = 8;
	bool _43 = _41 == _42;
	_27 = _43;
over_0:;
	if (!_27) goto else_110;
	int64_t _44;
// AST_CALL
// test/leetcode.orng:109
	struct struct_1 _45 = string_6;
	int64_t _46 = stdlib_system_println(_45);
	_44 = _46;
	_26 = _44;
	goto end_110;
else_110:;
	int64_t _47;
// AST_CALL
// test/leetcode.orng:111
	struct struct_1 _48 = string_7;
	int64_t _49 = stdlib_system_println(_48);
	_47 = _49;
	_26 = _47;
end_110:;
	_0 = _26;
return_block_109:;
}

int64_t test_leetcode_lengthOfLongestSubstring(struct struct_1 _str)
{
	int64_t retval;
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:121
// AST_DEFINE
// test/leetcode.orng:133
	struct struct_1 _1 = _str;
	int64_t _2 = _1.length;
	int64_t _112_n = _2;
// AST_DEFINE
// test/leetcode.orng:134
	int64_t _3 = 0;
	int64_t _112_res = _3;
// AST_FOR
// test/leetcode.orng:138
	int64_t _4 = 0;
	int64_t _116_i = _4;
begin_116:;
	int64_t _5 = _116_i;
	int64_t _6 = _112_n;
	bool _7 = _5 < _6;
	if (!_7) goto end_116;
// AST_FOR
// test/leetcode.orng:139
	int64_t _8 = _116_i;
	int64_t _117_j = _8;
begin_117:;
	int64_t _9 = _117_j;
	int64_t _10 = _112_n;
	bool _11 = _9 < _10;
	if (!_11) goto end_117;
// AST_IF
// test/leetcode.orng:140
	bool _12 = test_leetcode_areDistinct(_str, _116_i, _117_j);
	if (!_12) goto end_118;
	int64_t _13;
// AST_ASSIGN
// test/leetcode.orng:141
	int64_t _14 = _117_j;
	int64_t _15 = _116_i;
	int64_t _16 = _14 - _15;
	int64_t _17 = 1;
	int64_t _18 = _16 + _17;
	double _19 = stdlib_math_max(_112_res, _18);
	int64_t _20 = (int64_t)_19;
	_112_res = _20;
	_13 = _20;
end_118:;
	int64_t _21 = 1;
	_117_j += _21;
	goto begin_117;
end_117:;
	int64_t _22 = 1;
	_116_i += _22;
	goto begin_116;
end_116:;
// AST_RETURN
// test/leetcode.orng:146
	int64_t _23 = _112_res;
	retval = _23;
	goto return_block_112;
	_0 = _23;
	retval = _0;
return_block_112:;
	return retval;
}

bool test_leetcode_areDistinct(struct struct_1 _str, int64_t _i, int64_t _j)
{
	bool retval;
	bool _0;
// AST_DEFINE
// test/leetcode.orng:123
	struct struct_7 _113_visited = ((struct struct_7){256, (bool*[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}});
// AST_FOR
// test/leetcode.orng:124
	bool _1;
	int64_t _2 = _i;
	int64_t _114_k = _2;
begin_114:;
	int64_t _3 = _114_k;
	int64_t _4 = _j;
	bool _5 = _3 <= _4;
	if (!_5) goto end_114;
	bool _6;
// AST_DEFINE
// test/leetcode.orng:125
	int64_t _7 = _114_k;
	struct struct_1 _8 = _str;
	int8_t _9 = _8.data[_7];
	int64_t _10 = (int64_t)_9;
	int64_t _114_charCode = _10;
// AST_IF
// test/leetcode.orng:126
	int64_t _11 = _114_charCode;
	struct struct_7 _12 = _113_visited;
	bool _13 = _12.data[_11];
	if (!_13) goto end_115;
	bool _14;
// AST_RETURN
// test/leetcode.orng:127
	bool _15 = 0;
	retval = _15;
	goto return_block_113;
	_14 = _15;
end_115:;
// AST_ASSIGN
// test/leetcode.orng:129
	bool _16 = 1;
	int64_t _17 = _114_charCode;
	_113_visited.data[_17] = _16;
	_6 = _16;
	_1 = _6;
	int64_t _18 = 1;
	_114_k += _18;
	goto begin_114;
end_114:;
	_1 = _6;
// AST_RETURN
// test/leetcode.orng:131
	bool _19 = 1;
	retval = _19;
	goto return_block_113;
	_0 = _19;
	retval = _0;
return_block_113:;
	return retval;
}

void test_leetcode_test_lengthOfLongestSubstring()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:150
	struct struct_1 _1 = string_8;
	struct struct_1 _119_s = _1;
// AST_DEFINE
// test/leetcode.orng:152
	int64_t _2 = test_leetcode_lengthOfLongestSubstring(_119_s);
	int64_t _119_ans = _2;
// AST_IFELSE
// test/leetcode.orng:154
	int64_t _3;
	int64_t _4 = _119_ans;
	int64_t _5 = 3;
	bool _6 = _4 == _5;
	if (!_6) goto else_120;
	int64_t _7;
// AST_CALL
// test/leetcode.orng:155
	struct struct_1 _8 = string_9;
	int64_t _9 = stdlib_system_println(_8);
	_7 = _9;
	_3 = _7;
	goto end_120;
else_120:;
	int64_t _10;
// AST_CALL
// test/leetcode.orng:157
	struct struct_1 _11 = string_10;
	int64_t _12 = stdlib_system_println(_11, _119_ans);
	_10 = _12;
	_3 = _10;
end_120:;
	_0 = _3;
return_block_119:;
}

float test_leetcode_findMedianSortedArrays(struct struct_3 _nums1, struct struct_3 _nums2)
{
	float retval;
	int defer_0 = 0;
	float _0;
// AST_DEFINE
// test/leetcode.orng:166
	struct struct_3 _1 = _nums1;
	int64_t _2 = _1.length;
	struct struct_3 _3 = _nums2;
	int64_t _4 = _3.length;
	int64_t _5 = _2 + _4;
	struct struct_3 _6 = {_5, malloc(sizeof(int64_t) * _5)};
	_6.length = _5;
	for(int i = 0; i < _5; i++) {_6.data[i] = 0;}
	struct struct_3 _122_merged = _6;
// AST_DEFER
// test/leetcode.orng:167
	defer_0 = 1;
// AST_DEFINE
// test/leetcode.orng:169
	int64_t _7 = 0;
	int64_t _122_i = _7;
// AST_DEFINE
// test/leetcode.orng:170
	int64_t _8 = 0;
	int64_t _122_j = _8;
// AST_FOR
// test/leetcode.orng:171
begin_123:;
	int64_t _9 = _122_i;
	int64_t _10 = _122_j;
	int64_t _11 = _9 + _10;
	struct struct_3 _12 = _122_merged;
	int64_t _13 = _12.length;
	bool _14 = _11 < _13;
	if (!_14) goto end_123;
// AST_IFELSE
// test/leetcode.orng:172
	bool _15 = 0;
	int64_t _16 = _122_i;
	struct struct_3 _17 = _nums1;
	int64_t _18 = _17.length;
	bool _19 = _16 < _18;
	if (!_19) goto over_0;
	int64_t _20 = _122_j;
	struct struct_3 _21 = _nums2;
	int64_t _22 = _21.length;
	bool _23 = _20 < _22;
	_15 = _23;
over_0:;
	if (!_15) goto else_124;
	int64_t _24;
// AST_IFELSE
// test/leetcode.orng:173
	int64_t _25;
	int64_t _26 = _122_i;
	struct struct_3 _27 = _nums1;
	int64_t _28 = _27.data[_26];
	int64_t _29 = _122_j;
	struct struct_3 _30 = _nums2;
	int64_t _31 = _30.data[_29];
	bool _32 = _28 < _31;
	if (!_32) goto else_125;
	int64_t _33;
// AST_ASSIGN
// test/leetcode.orng:174
	int64_t _34 = _122_i;
	struct struct_3 _35 = _nums1;
	int64_t _36 = _35.data[_34];
	int64_t _37 = _122_i;
	int64_t _38 = _122_j;
	int64_t _39 = _37 + _38;
	_122_merged.data[_39] = _36;
// AST_ADD_ASSIGN
// test/leetcode.orng:175
	int64_t _40 = 1;
	_122_i += _40;
	_33 = _40;
	_25 = _33;
	goto end_125;
else_125:;
	int64_t _41;
// AST_ASSIGN
// test/leetcode.orng:177
	int64_t _42 = _122_j;
	struct struct_3 _43 = _nums2;
	int64_t _44 = _43.data[_42];
	int64_t _45 = _122_i;
	int64_t _46 = _122_j;
	int64_t _47 = _45 + _46;
	_122_merged.data[_47] = _44;
// AST_ADD_ASSIGN
// test/leetcode.orng:178
	int64_t _48 = 1;
	_122_j += _48;
	_41 = _48;
	_25 = _41;
end_125:;
	_24 = _25;
	goto end_124;
else_124:;
	int64_t _49 = _122_i;
	struct struct_3 _50 = _nums1;
	int64_t _51 = _50.length;
	bool _52 = _49 < _51;
	if (!_52) goto else_127;
	int64_t _53;
// AST_ASSIGN
// test/leetcode.orng:181
	int64_t _54 = _122_i;
	struct struct_3 _55 = _nums1;
	int64_t _56 = _55.data[_54];
	int64_t _57 = _122_i;
	int64_t _58 = _122_j;
	int64_t _59 = _57 + _58;
	_122_merged.data[_59] = _56;
// AST_ADD_ASSIGN
// test/leetcode.orng:182
	int64_t _60 = 1;
	_122_i += _60;
	_53 = _60;
	goto end_127;
else_127:;
	int64_t _61 = _122_j;
	struct struct_3 _62 = _nums2;
	int64_t _63 = _62.length;
	bool _64 = _61 < _63;
	if (!_64) goto end_128;
	int64_t _65;
// AST_ASSIGN
// test/leetcode.orng:184
	int64_t _66 = _122_j;
	struct struct_3 _67 = _nums2;
	int64_t _68 = _67.data[_66];
	int64_t _69 = _122_i;
	int64_t _70 = _122_j;
	int64_t _71 = _69 + _70;
	_122_merged.data[_71] = _68;
// AST_ADD_ASSIGN
// test/leetcode.orng:185
	int64_t _72 = 1;
	_122_j += _72;
	_65 = _72;
end_128:;
end_127:;
end_124:;
	goto begin_123;
end_123:;
// AST_IFELSE
// test/leetcode.orng:189
	float _73;
	struct struct_3 _74 = _122_merged;
	int64_t _75 = _74.length;
	int64_t _76 = 2;
	int64_t _77 = _75 % _76;
	int64_t _78 = 0;
	bool _79 = _77 == _78;
	if (!_79) goto else_129;
	float _80;
// AST_DIVIDE
// test/leetcode.orng:190
	struct struct_3 _81 = _122_merged;
	int64_t _82 = _81.length;
	int64_t _83 = 2;
	int64_t _84 = _82 / _83;
	struct struct_3 _85 = _122_merged;
	int64_t _86 = _85.data[_84];
	struct struct_3 _87 = _122_merged;
	int64_t _88 = _87.length;
	int64_t _89 = 2;
	int64_t _90 = _88 / _89;
	int64_t _91 = 1;
	int64_t _92 = _90 + _91;
	struct struct_3 _93 = _122_merged;
	int64_t _94 = _93.data[_92];
	int64_t _95 = _86 + _94;
	int64_t _96 = _95;
	float _97 = 2.000000;
	float _98 = _96 / _97;
	_80 = _98;
	_73 = _80;
	goto end_129;
else_129:;
	float _99;
// AST_CAST
// test/leetcode.orng:192
	struct struct_3 _100 = _122_merged;
	int64_t _101 = _100.length;
	int64_t _102 = 2;
	int64_t _103 = _101 / _102;
	struct struct_3 _104 = _122_merged;
	int64_t _105 = _104.data[_103];
	float _106 = (float)_105;
	_99 = _106;
	_73 = _99;
end_129:;
	_0 = _73;
	retval = _0;
return_block_122:;
	if (defer_0) {
	struct struct_3 _107 = _122_merged;
	free(_107.data);
	}
	return retval;
}

void test_leetcode_test_findMedianSortedArrays()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:197
	int64_t* _1 = 1;
	int64_t* _2 = 3;
	struct struct_3 _3 = {2, (int64_t*[]){_1, _2}};
	struct struct_3 _131_nums1 = _3;
// AST_DEFINE
// test/leetcode.orng:198
	int64_t* _4 = 2;
	struct struct_3 _5 = {1, (int64_t*[]){_4}};
	struct struct_3 _131_nums2 = _5;
// AST_DEFINE
// test/leetcode.orng:200
	float _6 = test_leetcode_findMedianSortedArrays(_131_nums1, _131_nums2);
	float _131_ans = _6;
// AST_IFELSE
// test/leetcode.orng:202
	int64_t _7;
	float _8 = _131_ans;
	float _9 = 2.000000;
	bool _10 = _8 == _9;
	if (!_10) goto else_132;
	int64_t _11;
// AST_CALL
// test/leetcode.orng:203
	struct struct_1 _12 = string_11;
	int64_t _13 = stdlib_system_println(_12);
	_11 = _13;
	_7 = _11;
	goto end_132;
else_132:;
	int64_t _14;
// AST_CALL
// test/leetcode.orng:205
	struct struct_1 _15 = string_12;
	int64_t _16 = stdlib_system_println(_15, _131_ans);
	_14 = _16;
	_7 = _14;
end_132:;
	_0 = _7;
return_block_131:;
}

struct struct_1 test_leetcode_longestPalindrome(struct struct_1 _s)
{
	struct struct_1 retval;
	struct struct_1 _0;
// AST_DEFINE
// test/leetcode.orng:213
// AST_DEFINE
// test/leetcode.orng:223
	int64_t _1 = 0;
	int64_t _134_start = _1;
// AST_DEFINE
// test/leetcode.orng:224
	int64_t _2 = 0;
	int64_t _134_end = _2;
// AST_FOR
// test/leetcode.orng:225
	int64_t _3 = 0;
	int64_t _137_i = _3;
begin_137:;
	int64_t _4 = _137_i;
	struct struct_1 _5 = _s;
	int64_t _6 = _5.length;
	bool _7 = _4 < _6;
	if (!_7) goto end_137;
// AST_DEFINE
// test/leetcode.orng:226
	int64_t _8 = test_leetcode_expandAroundCenter(_s, _137_i, _137_i);
	int64_t _137_len1 = _8;
// AST_DEFINE
// test/leetcode.orng:227
	int64_t _9 = _137_i;
	int64_t _10 = 1;
	int64_t _11 = _9 + _10;
	int64_t _12 = test_leetcode_expandAroundCenter(_s, _137_i, _11);
	int64_t _137_len2 = _12;
// AST_DEFINE
// test/leetcode.orng:228
	double _13 = stdlib_math_max(_137_len1, _137_len2);
	int64_t _14 = (int64_t)_13;
	int64_t _137_len = _14;
// AST_IF
// test/leetcode.orng:229
	int64_t _15 = _137_len;
	int64_t _16 = _134_end;
	int64_t _17 = _134_start;
	int64_t _18 = _16 - _17;
	bool _19 = _15 > _18;
	if (!_19) goto end_138;
	int64_t _20;
// AST_ASSIGN
// test/leetcode.orng:230
	int64_t _21 = _137_i;
	int64_t _22 = _137_len;
	int64_t _23 = 1;
	int64_t _24 = _22 - _23;
	int64_t _25 = _24;
	int64_t _26 = 2;
	int64_t _27 = _25 / _26;
	int64_t _28 = _21 - _27;
	_134_start = _28;
// AST_ASSIGN
// test/leetcode.orng:231
	int64_t _29 = _137_i;
	int64_t _30 = _137_len;
	int64_t _31 = 2;
	int64_t _32 = _30 / _31;
	int64_t _33 = _29 + _32;
	_134_end = _33;
	_20 = _33;
end_138:;
	int64_t _34 = 1;
	_137_i += _34;
	goto begin_137;
end_137:;
// AST_CALL
// test/leetcode.orng:234
	int64_t _35 = _134_end;
	int64_t _36 = 1;
	int64_t _37 = _35 + _36;
	struct struct_1 _38 = stdlib_string_substring(_s, _134_start, _37);
	_0 = _38;
	retval = _0;
return_block_134:;
	return retval;
}

int64_t test_leetcode_expandAroundCenter(struct struct_1 _s, int64_t _left, int64_t _right)
{
	int64_t retval;
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:214
	int64_t _1 = _left;
	int64_t _135_L = _1;
// AST_DEFINE
// test/leetcode.orng:215
	int64_t _2 = _right;
	int64_t _135_R = _2;
// AST_FOR
// test/leetcode.orng:216
	int64_t _3;
begin_136:;
	bool _4 = 0;
	bool _5 = 0;
	int64_t _6 = _135_L;
	int64_t _7 = 0;
	bool _8 = _6 >= _7;
	if (!_8) goto over_1;
	int64_t _9 = _135_R;
	struct struct_1 _10 = _s;
	int64_t _11 = _10.length;
	bool _12 = _9 < _11;
	_5 = _12;
over_1:;
	if (!_5) goto over_0;
	int64_t _13 = _135_L;
	struct struct_1 _14 = _s;
	int8_t _15 = _14.data[_13];
	int64_t _16 = _135_R;
	struct struct_1 _17 = _s;
	int8_t _18 = _17.data[_16];
	bool _19 = _15 == _18;
	_4 = _19;
over_0:;
	if (!_4) goto end_136;
	int64_t _20;
// AST_SUB_ASSIGN
// test/leetcode.orng:217
	int64_t _21 = 1;
	_135_L -= _21;
// AST_ADD_ASSIGN
// test/leetcode.orng:218
	int64_t _22 = 1;
	_135_R += _22;
	_20 = _22;
	_3 = _20;
	goto begin_136;
end_136:;
	_3 = _20;
// AST_SUBTRACT
// test/leetcode.orng:220
	int64_t _23 = _135_R;
	int64_t _24 = _135_L;
	int64_t _25 = _23 - _24;
	int64_t _26 = 1;
	int64_t _27 = _25 - _26;
	_0 = _27;
	retval = _0;
return_block_135:;
	return retval;
}

void test_leetcode_test_longestPalindrome()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:238
	struct struct_1 _1 = string_13;
	struct struct_1 _139_s = _1;
// AST_DEFINE
// test/leetcode.orng:240
	struct struct_1 _2 = test_leetcode_longestPalindrome(_139_s);
	struct struct_1 _139_ans = _2;
// AST_IFELSE
// test/leetcode.orng:242
	int64_t _3;
	bool _4 = 1;
	struct struct_1 _5 = string_14;
	bool _6 = stdlib_string_equals(_139_ans, _5);
	if (_6) goto over_0;
	struct struct_1 _7 = string_15;
	bool _8 = stdlib_string_equals(_139_ans, _7);
	_4 = _8;
over_0:;
	if (!_4) goto else_140;
	int64_t _9;
// AST_CALL
// test/leetcode.orng:243
	struct struct_1 _10 = string_16;
	int64_t _11 = stdlib_system_println(_10);
	_9 = _11;
	_3 = _9;
	goto end_140;
else_140:;
	int64_t _12;
// AST_CALL
// test/leetcode.orng:245
	struct struct_1 _13 = string_17;
	int64_t _14 = stdlib_system_println(_13);
	_12 = _14;
	_3 = _12;
end_140:;
	_0 = _3;
return_block_139:;
}

struct struct_1 test_leetcode_convert(struct struct_1 _s, int64_t _numRows)
{
	struct struct_1 retval;
	int defer_0 = 0;
	struct struct_1 _0;
// AST_DEFINE
// test/leetcode.orng:254
	struct struct_1 _1 = _s;
	int64_t _2 = _1.length;
	struct struct_9 _3 = {_2, malloc(sizeof(struct struct_1) * _2)};
	_3.length = _2;
	for(int i = 0; i < _2; i++) {_3.data[i] = ((struct struct_1){0, 0});}
	struct struct_9 _142_board = _3;
// AST_FOR
// test/leetcode.orng:255
	struct struct_1 _4;
	int64_t _5 = 0;
	int64_t _143_i = _5;
begin_143:;
	int64_t _6 = _143_i;
	struct struct_1 _7 = _s;
	int64_t _8 = _7.length;
	bool _9 = _6 < _8;
	if (!_9) goto end_143;
	struct struct_1 _10;
// AST_ASSIGN
// test/leetcode.orng:256
	int64_t _11 = _numRows;
	struct struct_1 _12 = {_11, malloc(sizeof(int8_t) * _11)};
	_12.length = _11;
	for(int i = 0; i < _11; i++) {_12.data[i] = 0;}
	int64_t _13 = _143_i;
	_142_board.data[_13] = _12;
	_10 = _12;
	_4 = _10;
	int64_t _14 = 1;
	_143_i += _14;
	goto begin_143;
end_143:;
	_4 = _10;
// AST_DEFER
// test/leetcode.orng:258
	defer_0 = 1;
// AST_DEFINE
// test/leetcode.orng:265
	int64_t _15 = 0;
	int64_t _142_x = _15;
// AST_DEFINE
// test/leetcode.orng:266
	int64_t _16 = 0;
	int64_t _142_y = _16;
// AST_DEFINE
// test/leetcode.orng:267
	bool _17 = 0;
	bool _142_diagnolizing = _17;
// AST_FOR
// test/leetcode.orng:268
	int64_t _18 = 0;
	int64_t _146_i = _18;
begin_146:;
	int64_t _19 = _146_i;
	struct struct_1 _20 = _s;
	int64_t _21 = _20.length;
	bool _22 = _19 < _21;
	if (!_22) goto end_146;
// AST_ASSIGN
// test/leetcode.orng:269
	int64_t _23 = _146_i;
	struct struct_1 _24 = _s;
	int8_t _25 = _24.data[_23];
	int64_t _26 = _142_y;
	int64_t _27 = _142_x;
	_142_board.data[_27].data[_26] = _25;
// AST_IFELSE
// test/leetcode.orng:270
	bool _28 = _142_diagnolizing;
	if (!_28) goto else_147;
// AST_SUB_ASSIGN
// test/leetcode.orng:271
	int64_t _29 = 1;
	_142_y -= _29;
// AST_ADD_ASSIGN
// test/leetcode.orng:272
	int64_t _30 = 1;
	_142_x += _30;
// AST_IF
// test/leetcode.orng:273
	int64_t _31 = _142_y;
	int64_t _32 = 0;
	bool _33 = _31 == _32;
	if (!_33) goto end_148;
	bool _34;
// AST_ASSIGN
// test/leetcode.orng:274
	bool _35 = 0;
	_142_diagnolizing = _35;
	_34 = _35;
end_148:;
	goto end_147;
else_147:;
// AST_ADD_ASSIGN
// test/leetcode.orng:277
	int64_t _36 = 1;
	_142_y += _36;
// AST_IF
// test/leetcode.orng:278
	int64_t _37 = _142_y;
	int64_t _38 = _numRows;
	bool _39 = _37 == _38;
	if (!_39) goto end_150;
	int64_t _40;
// AST_ASSIGN
// test/leetcode.orng:279
	bool _41 = 1;
	_142_diagnolizing = _41;
// AST_SUB_ASSIGN
// test/leetcode.orng:280
	int64_t _42 = 2;
	_142_y -= _42;
// AST_ADD_ASSIGN
// test/leetcode.orng:281
	int64_t _43 = 1;
	_142_x += _43;
	_40 = _43;
end_150:;
end_147:;
	int64_t _44 = 1;
	_146_i += _44;
	goto begin_146;
end_146:;
// AST_DEFINE
// test/leetcode.orng:286
	struct struct_1 _45 = _s;
	int64_t _46 = _45.length;
	struct struct_1 _47 = {_46, malloc(sizeof(int8_t) * _46)};
	_47.length = _46;
	for(int i = 0; i < _46; i++) {_47.data[i] = 0;}
	struct struct_1 _142_retval = _47;
// AST_DEFINE
// test/leetcode.orng:287
	int64_t _48 = 0;
	int64_t _142_k = _48;
// AST_FOR
// test/leetcode.orng:288
	int64_t _49 = 0;
	int64_t _151_j = _49;
begin_151:;
	int64_t _50 = _151_j;
	int64_t _51 = _numRows;
	bool _52 = _50 < _51;
	if (!_52) goto end_151;
// AST_FOR
// test/leetcode.orng:289
	int64_t _53 = 0;
	int64_t _152_i = _53;
begin_152:;
	int64_t _54 = _152_i;
	struct struct_1 _55 = _s;
	int64_t _56 = _55.length;
	bool _57 = _54 < _56;
	if (!_57) goto end_152;
// AST_IF
// test/leetcode.orng:290
	int64_t _58 = _151_j;
	int64_t _59 = _152_i;
	struct struct_9 _60 = _142_board;
	struct struct_1 _61 = _60.data[_59];
	int8_t _62 = _61.data[_58];
	int8_t _63 = '\0';
	bool _64 = _62 != _63;
	if (!_64) goto end_153;
	int64_t _65;
// AST_ASSIGN
// test/leetcode.orng:291
	int64_t _66 = _151_j;
	int64_t _67 = _152_i;
	struct struct_9 _68 = _142_board;
	struct struct_1 _69 = _68.data[_67];
	int8_t _70 = _69.data[_66];
	int64_t _71 = _142_k;
	_142_retval.data[_71] = _70;
// AST_ADD_ASSIGN
// test/leetcode.orng:292
	int64_t _72 = 1;
	_142_k += _72;
	_65 = _72;
end_153:;
	int64_t _73 = 1;
	_152_i += _73;
	goto begin_152;
end_152:;
	int64_t _74 = 1;
	_151_j += _74;
	goto begin_151;
end_151:;
// AST_IDENT
// test/leetcode.orng:297
	struct struct_1 _75 = _142_retval;
	_0 = _75;
	retval = _0;
return_block_142:;
	if (defer_0) {
// AST_FOR
// test/leetcode.orng:259
	int64_t _76 = 0;
	int64_t _181_i = _76;
begin_181:;
	int64_t _77 = _181_i;
	struct struct_1 _78 = _s;
	int64_t _79 = _78.length;
	bool _80 = _77 < _79;
	if (!_80) goto end_181;
// AST_FREE
// test/leetcode.orng:260
	int64_t _81 = _181_i;
	struct struct_9 _82 = _142_board;
	struct struct_1 _83 = _82.data[_81];
	free(_83.data);
	int64_t _84 = 1;
	_181_i += _84;
	goto begin_181;
end_181:;
// AST_FREE
// test/leetcode.orng:262
	struct struct_9 _85 = _142_board;
	free(_85.data);
	}
	return retval;
}

void test_leetcode_test_convert()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:301
	struct struct_1 _1 = string_18;
	int64_t _2 = 3;
	struct struct_1 _3 = test_leetcode_convert(_1, _2);
	struct struct_1 _154_ans = _3;
// AST_IFELSE
// test/leetcode.orng:303
	int64_t _4;
	struct struct_1 _5 = string_19;
	bool _6 = stdlib_string_equals(_154_ans, _5);
	if (!_6) goto else_155;
	int64_t _7;
// AST_CALL
// test/leetcode.orng:304
	struct struct_1 _8 = string_20;
	int64_t _9 = stdlib_system_println(_8);
	_7 = _9;
	_4 = _7;
	goto end_155;
else_155:;
	int64_t _10;
// AST_CALL
// test/leetcode.orng:306
	struct struct_1 _11 = string_21;
	int64_t _12 = stdlib_system_println(_11);
	_10 = _12;
	_4 = _10;
end_155:;
	_0 = _4;
return_block_154:;
}

struct struct_4* test_leetcode_reverseList(struct struct_4* _list)
{
	struct struct_4* retval;
	struct struct_4* _0;
// AST_DEFINE
// test/leetcode.orng:316
	struct struct_4* _1 = 0;
	struct struct_4* _157_prev = _1;
// AST_DEFINE
// test/leetcode.orng:317
	struct struct_4* _2 = _list;
	struct struct_4* _157_curr = _2;
// AST_DEFINE
// test/leetcode.orng:318
	struct struct_4* _3 = 0;
	struct struct_4* _157_next = _3;
// AST_FOR
// test/leetcode.orng:319
	struct struct_4* _4;
begin_158:;
	struct struct_4* _5 = _157_curr;
	void* _6 = 0;
	bool _7 = _5 != _6;
	if (!_7) goto end_158;
	struct struct_4* _8;
// AST_ASSIGN
// test/leetcode.orng:320
	struct struct_4* _9 = _157_curr;
	struct struct_4* _10 = _9->next;
	_157_next = _10;
// AST_ASSIGN
// test/leetcode.orng:321
	struct struct_4* _11 = _157_prev;
	_157_curr->next = _11;
// AST_ASSIGN
// test/leetcode.orng:322
	struct struct_4* _12 = _157_curr;
	_157_prev = _12;
// AST_ASSIGN
// test/leetcode.orng:323
	struct struct_4* _13 = _157_next;
	_157_curr = _13;
	_8 = _13;
	_4 = _8;
	goto begin_158;
end_158:;
	_4 = _8;
// AST_ASSIGN
// test/leetcode.orng:325
	struct struct_4* _14 = _157_prev;
	_list = _14;
// AST_RETURN
// test/leetcode.orng:326
	struct struct_4* _15 = _list;
	retval = _15;
	goto return_block_157;
	_0 = _15;
	retval = _0;
return_block_157:;
	return retval;
}

int64_t test_leetcode_reverse(int64_t _x)
{
	int64_t retval;
	struct struct_4* _0 = test_leetcode_convertToList(_x);
	struct struct_4* _1 = test_leetcode_reverseList(_0);
	int64_t _2 = test_leetcode_convertToInt(_1);
	retval = _2;
return_block_:;
	return retval;
}

void test_leetcode_test_reverse()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:331
	int64_t _1 = 123;
	int64_t _2 = test_leetcode_reverse(_1);
	int64_t _159_ans = _2;
// AST_IFELSE
// test/leetcode.orng:333
	int64_t _3;
	int64_t _4 = _159_ans;
	int64_t _5 = 321;
	bool _6 = _4 == _5;
	if (!_6) goto else_160;
	int64_t _7;
// AST_CALL
// test/leetcode.orng:334
	struct struct_1 _8 = string_22;
	int64_t _9 = stdlib_system_println(_8);
	_7 = _9;
	_3 = _7;
	goto end_160;
else_160:;
	int64_t _10;
// AST_CALL
// test/leetcode.orng:336
	struct struct_1 _11 = string_23;
	int64_t _12 = stdlib_system_println(_11);
	_10 = _12;
	_3 = _10;
end_160:;
	_0 = _3;
return_block_159:;
}

int64_t test_leetcode_myAtoi(struct struct_1 _s)
{
	int64_t retval;
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:345
	int64_t _1 = 0;
	int64_t _162_x = _1;
// AST_DEFINE
// test/leetcode.orng:346
	int64_t _2 = 0;
	int64_t _162_i = _2;
// AST_DEFINE
// test/leetcode.orng:347
	bool _3 = 1;
	bool _162_sign = _3;
// AST_FOR
// test/leetcode.orng:350
	int64_t _4;
begin_163:;
	bool _5 = 0;
	int64_t _6 = _162_i;
	struct struct_1 _7 = _s;
	int64_t _8 = _7.length;
	bool _9 = _6 < _8;
	if (!_9) goto over_0;
	int64_t _10 = _162_i;
	struct struct_1 _11 = _s;
	int8_t _12 = _11.data[_10];
	int8_t _13 = ' ';
	bool _14 = _12 == _13;
	_5 = _14;
over_0:;
	if (!_5) goto end_163;
	int64_t _15;
// AST_ADD_ASSIGN
// test/leetcode.orng:350
	int64_t _16 = 1;
	_162_i += _16;
	_15 = _16;
	_4 = _15;
	goto begin_163;
end_163:;
	_4 = _15;
// AST_IFELSE
// test/leetcode.orng:353
	int64_t _17 = _162_i;
	struct struct_1 _18 = _s;
	int64_t _19 = _18.length;
	bool _20 = _17 == _19;
	if (!_20) goto else_164;
	int64_t _21;
// AST_RETURN
// test/leetcode.orng:354
	int64_t _22 = 0;
	retval = _22;
	goto return_block_162;
	_21 = _22;
	goto end_164;
else_164:;
	int64_t _23 = _162_i;
	struct struct_1 _24 = _s;
	int8_t _25 = _24.data[_23];
	int8_t _26 = '+';
	bool _27 = _25 == _26;
	if (!_27) goto else_165;
	int64_t _28;
// AST_ASSIGN
// test/leetcode.orng:356
	bool _29 = 1;
	_162_sign = _29;
// AST_ADD_ASSIGN
// test/leetcode.orng:357
	int64_t _30 = 1;
	_162_i += _30;
	_28 = _30;
	goto end_165;
else_165:;
	int64_t _31 = _162_i;
	struct struct_1 _32 = _s;
	int8_t _33 = _32.data[_31];
	int8_t _34 = '-';
	bool _35 = _33 == _34;
	if (!_35) goto end_166;
	int64_t _36;
// AST_ASSIGN
// test/leetcode.orng:359
	bool _37 = 0;
	_162_sign = _37;
// AST_ADD_ASSIGN
// test/leetcode.orng:360
	int64_t _38 = 1;
	_162_i += _38;
	_36 = _38;
end_166:;
end_165:;
end_164:;
// AST_FOR
// test/leetcode.orng:364
	int64_t _39;
begin_167:;
	bool _40 = 0;
	int64_t _41 = _162_i;
	struct struct_1 _42 = _s;
	int64_t _43 = _42.length;
	bool _44 = _41 < _43;
	if (!_44) goto over_1;
	int64_t _45 = _162_i;
	struct struct_1 _46 = _s;
	int8_t _47 = _46.data[_45];
	bool _48 = isdigit(_47);
	_40 = _48;
over_1:;
	if (!_40) goto end_167;
	int64_t _49;
// AST_ASSIGN
// test/leetcode.orng:365
	int64_t _50 = _162_x;
	int64_t _51 = 10;
	int64_t _52 = _50 * _51;
	int64_t _53 = _162_i;
	struct struct_1 _54 = _s;
	int8_t _55 = _54.data[_53];
	int64_t _56 = (int64_t)_55;
	int64_t _57 = _52 + _56;
	int8_t _58 = '0';
	int64_t _59 = (int64_t)_58;
	int64_t _60 = _57 - _59;
	_162_x = _60;
	_49 = _60;
	_39 = _49;
	int64_t _61 = 1;
	_162_i += _61;
	goto begin_167;
end_167:;
	_39 = _49;
// AST_IFELSE
// test/leetcode.orng:368
	int64_t _62;
	bool _63 = _162_sign;
	if (!_63) goto else_168;
	int64_t _64;
// AST_IDENT
// test/leetcode.orng:368
	int64_t _65 = _162_x;
	_64 = _65;
	_62 = _64;
	goto end_168;
else_168:;
	int64_t _66;
// AST_NEG
// test/leetcode.orng:368
	int64_t _67 = _162_x;
	int64_t _68 = -_67;
	_66 = _68;
	_62 = _66;
end_168:;
	_0 = _62;
	retval = _0;
return_block_162:;
	return retval;
}

void test_leetcode_test_myAtoi()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:372
	struct struct_1 _1 = string_24;
	struct struct_1 _170_s = _1;
// AST_DEFINE
// test/leetcode.orng:374
	int64_t _2 = test_leetcode_myAtoi(_170_s);
	int64_t _170_ans = _2;
// AST_IFELSE
// test/leetcode.orng:376
	int64_t _3;
	int64_t _4 = _170_ans;
	int64_t _5 = 42;
	bool _6 = _4 == _5;
	if (!_6) goto else_171;
	int64_t _7;
// AST_CALL
// test/leetcode.orng:377
	struct struct_1 _8 = string_25;
	int64_t _9 = stdlib_system_println(_8);
	_7 = _9;
	_3 = _7;
	goto end_171;
else_171:;
	int64_t _10;
// AST_CALL
// test/leetcode.orng:379
	struct struct_1 _11 = string_26;
	int64_t _12 = stdlib_system_println(_11);
	_10 = _12;
	_3 = _10;
end_171:;
	_0 = _3;
return_block_170:;
}

bool test_leetcode_isPalindrome(int64_t _x)
{
	bool retval;
	bool _0;
// AST_DEFINE
// test/leetcode.orng:385
	struct struct_4* _1 = test_leetcode_convertToList(_x);
	struct struct_4* _173_list = _1;
// AST_DEFINE
// test/leetcode.orng:386
	struct struct_4* _2 = test_leetcode_convertToList(_x);
	struct struct_4* _3 = test_leetcode_reverseList(_2);
	struct struct_4* _173_reversedList = _3;
// AST_FOR
// test/leetcode.orng:387
	struct struct_4* _4;
begin_174:;
	struct struct_4* _5 = _173_list;
	void* _6 = 0;
	bool _7 = _5 != _6;
	if (!_7) goto end_174;
	struct struct_4* _8;
// AST_IF
// test/leetcode.orng:388
	struct struct_4* _9 = _173_list;
	int64_t _10 = _9->val;
	struct struct_4* _11 = _173_reversedList;
	int64_t _12 = _11->val;
	bool _13 = _10 != _12;
	if (!_13) goto end_175;
	bool _14;
// AST_RETURN
// test/leetcode.orng:389
	bool _15 = 0;
	retval = _15;
	goto return_block_173;
	_14 = _15;
end_175:;
// AST_ASSIGN
// test/leetcode.orng:391
	struct struct_4* _16 = _173_list;
	struct struct_4* _17 = _16->next;
	_173_list = _17;
// AST_ASSIGN
// test/leetcode.orng:392
	struct struct_4* _18 = _173_reversedList;
	struct struct_4* _19 = _18->next;
	_173_reversedList = _19;
	_8 = _19;
	_4 = _8;
	goto begin_174;
end_174:;
	_4 = _8;
// AST_RETURN
// test/leetcode.orng:394
	bool _20 = 1;
	retval = _20;
	goto return_block_173;
	_0 = _20;
	retval = _0;
return_block_173:;
	return retval;
}

void test_leetcode_test_isPalindrome()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:398
	int64_t _1 = 121;
	int64_t _176_x = _1;
// AST_DEFINE
// test/leetcode.orng:400
	bool _2 = test_leetcode_isPalindrome(_176_x);
	bool _176_ans = _2;
// AST_IFELSE
// test/leetcode.orng:402
	int64_t _3;
	bool _4 = _176_ans;
	if (!_4) goto else_177;
	int64_t _5;
// AST_CALL
// test/leetcode.orng:403
	struct struct_1 _6 = string_27;
	int64_t _7 = stdlib_system_println(_6);
	_5 = _7;
	_3 = _5;
	goto end_177;
else_177:;
	int64_t _8;
// AST_CALL
// test/leetcode.orng:405
	struct struct_1 _9 = string_28;
	int64_t _10 = stdlib_system_println(_9);
	_8 = _10;
	_3 = _8;
end_177:;
	_0 = _3;
return_block_176:;
}

int64_t test_testModule_main(struct struct_2 _args)
{
	int64_t retval;
	int64_t _0;
// AST_CALL
// test/testModule.orng:3
	test_leetcode_test_all();
// AST_INT
// test/testModule.orng:4
	int64_t _1 = 0;
	_0 = _1;
	retval = _0;
return_block_179:;
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

bool stdlib_string_equals(struct struct_1 _a, struct struct_1 _b)
{
	bool retval;
	bool _0;
// AST_IFELSE
// stdlib/string.orng:30
	bool _1;
	struct struct_1 _2 = _a;
	int64_t _3 = _2.length;
	struct struct_1 _4 = _b;
	int64_t _5 = _4.length;
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
	int64_t _10 = 0;
	int64_t _15_i = _10;
begin_15:;
	int64_t _11 = _15_i;
	struct struct_1 _12 = _a;
	int64_t _13 = _12.length;
	bool _14 = _11 < _13;
	if (!_14) goto end_15;
// AST_IF
// stdlib/string.orng:34
	int64_t _15 = _15_i;
	struct struct_1 _16 = _a;
	int8_t _17 = _16.data[_15];
	int64_t _18 = _15_i;
	struct struct_1 _19 = _b;
	int8_t _20 = _19.data[_18];
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
	int64_t _24 = 1;
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

struct struct_1 stdlib_string_substring(struct struct_1 _s, int64_t _start, int64_t _end)
{
	struct struct_1 retval;
	struct struct_1 _0;
// AST_DEFINE
// stdlib/string.orng:43
	int64_t _1 = _end;
	int64_t _2 = _start;
	int64_t _3 = _1 - _2;
	struct struct_1 _4 = {_3, malloc(sizeof(int8_t) * _3)};
	_4.length = _3;
	for(int i = 0; i < _3; i++) {_4.data[i] = 0;}
	struct struct_1 _17_retval = _4;
// AST_FOR
// stdlib/string.orng:44
	int8_t _5;
	int64_t _6 = 0;
	int64_t _18_i = _6;
begin_18:;
	int64_t _7 = _18_i;
	struct struct_1 _8 = _17_retval;
	int64_t _9 = _8.length;
	bool _10 = _7 < _9;
	if (!_10) goto end_18;
	int8_t _11;
// AST_ASSIGN
// stdlib/string.orng:45
	int64_t _12 = _start;
	int64_t _13 = _18_i;
	int64_t _14 = _12 + _13;
	struct struct_1 _15 = _s;
	int8_t _16 = _15.data[_14];
	int64_t _17 = _18_i;
	_17_retval.data[_17] = _16;
	_11 = _16;
	_5 = _11;
	int64_t _18 = 1;
	_18_i += _18;
	goto begin_18;
end_18:;
	_5 = _11;
// AST_RETURN
// stdlib/string.orng:47
	struct struct_1 _19 = _17_retval;
	retval = _19;
	goto return_block_17;
	_0 = _19;
	retval = _0;
return_block_17:;
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
