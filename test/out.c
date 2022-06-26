/* Code generated using Orange Translator http://josephs-projects.com */

/* Includes used by the program */
#define _CRT_SECURE_NO_WARNINGS
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

struct struct_7 {
	int64_t tag;
	union {
		struct struct_6* something;
	};
};

struct struct_6 {
	int64_t val;
	struct struct_7 next;
};

struct struct_8 {
	int64_t length;
	int64_t* data;
};

struct struct_9 {
	int64_t length;
	bool* data;
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
struct struct_1 string_20;
struct struct_1 string_21;
struct struct_1 string_22;
struct struct_1 string_23;
struct struct_1 string_24;
struct struct_1 string_25;
struct struct_1 string_26;
struct struct_1 string_27;
struct struct_1 string_28;
struct struct_1 string_29;
struct struct_1 string_30;
struct struct_1 string_31;
struct struct_1 string_32;
struct struct_1 string_33;
struct struct_1 string_34;
struct struct_1 string_35;
struct struct_1 string_36;
struct struct_1 string_37;
struct struct_1 string_38;
struct struct_1 string_39;
struct struct_1 string_40;
struct struct_1 string_41;
struct struct_1 string_42;
struct struct_1 string_43;
struct struct_1 string_44;
struct struct_1 string_45;
struct struct_1 string_46;
struct struct_1 string_47;
struct struct_1 string_48;
struct struct_1 string_49;
struct struct_1 string_50;
struct struct_1 string_51;
struct struct_1 string_52;
struct struct_1 string_53;
struct struct_1 string_54;
struct struct_1 string_55;
struct struct_1 string_56;

/* Forward global declarations */

/* Forward function and procedure declarations */
void test_leetcode_test_all();
void test_leetcode_test_twoSum();
struct struct_3 test_leetcode_twoSum(struct struct_3 _nums, int64_t _target);
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
void test_leetcode_test_addTwoNumbers();
bool test_leetcode_hasValue(struct struct_7 _node, struct struct_3 _x);
struct struct_6* test_leetcode_addTwoNumbers(struct struct_6* _l1, struct struct_6* _l2);
struct struct_6* test_leetcode_convertToList(int64_t _i);
int64_t test_leetcode_convertToInt(struct struct_7 _l);
void test_leetcode_test_findMedianSortedArrays();
float test_leetcode_findMedianSortedArrays(struct struct_3 _nums1, struct struct_3 _nums2);
void test_leetcode_test_longestPalindrome();
struct struct_1 test_leetcode_longestPalindrome(struct struct_1 _s);
int64_t test_leetcode_expandAroundCenter(struct struct_1 _s, int64_t _left, int64_t _right);
void test_leetcode_test_convert();
struct struct_1 test_leetcode_convert(struct struct_1 _s, int64_t _numRows);
void test_leetcode_test_reverse();
int64_t test_leetcode_reverse(int64_t _x);
struct struct_6* test_leetcode_reverseList(struct struct_6* _list);
void test_leetcode_test_myAtoi();
int64_t test_leetcode_myAtoi(struct struct_1 _s);
void test_leetcode_test_isPalindrome();
bool test_leetcode_isPalindrome(int64_t _x);
void test_leetcode_test_isMatch();
bool test_leetcode_isMatch(struct struct_1 _s, struct struct_1 _p);
void test_leetcode_test_maxArea();
int64_t test_leetcode_maxArea(struct struct_3 _height, int64_t _max);
void test_leetcode_fizzbuzz(int64_t _n);
struct struct_1 test_leetcode_fizzbuzz2(int64_t _n);
int64_t test_leetcode_lengthOfLongestSubstring(struct struct_1 _str);
bool test_leetcode_areDistinct(struct struct_1 _str, int64_t _i, int64_t _j);
void test_leetcode_test_lengthOfLongestSubstring();
int64_t test_testModule_main(struct struct_2 _args);

#ifndef ORANGE_PROGRAM_22933
#define ORANGE_PROGRAM_22933

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
struct struct_1 string_14 = {15, (char[]){'t', 'w', 'o', 'S', 'u', 'm', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_15 = {20, (char[]){'t', 'w', 'o', 'S', 'u', 'm', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', ' ', '%', 'd', ' ', '%', 'd', '\0'}};
struct struct_1 string_16 = {22, (char[]){'a', 'd', 'd', 'T', 'w', 'o', 'N', 'u', 'm', 'b', 'e', 'r', 's', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_17 = {21, (char[]){'a', 'd', 'd', 'T', 'w', 'o', 'N', 'u', 'm', 'b', 'e', 'r', 's', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
struct struct_1 string_18 = {31, (char[]){'f', 'i', 'n', 'd', 'M', 'e', 'd', 'i', 'a', 'n', 'S', 'o', 'r', 't', 'e', 'd', 'A', 'r', 'r', 'a', 'y', 's', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_19 = {33, (char[]){'f', 'i', 'n', 'd', 'M', 'e', 'd', 'i', 'a', 'n', 'S', 'o', 'r', 't', 'e', 'd', 'A', 'r', 'r', 'a', 'y', 's', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', ' ', '%', 'f', '\0'}};
struct struct_1 string_20 = {5, (char[]){'b', 'a', 'b', 'a', 'd', '\0'}};
struct struct_1 string_21 = {3, (char[]){'b', 'a', 'b', '\0'}};
struct struct_1 string_22 = {3, (char[]){'a', 'b', 'a', '\0'}};
struct struct_1 string_23 = {26, (char[]){'l', 'o', 'n', 'g', 'e', 's', 't', 'P', 'a', 'l', 'i', 'n', 'd', 'r', 'o', 'm', 'e', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_24 = {28, (char[]){'l', 'o', 'n', 'g', 'e', 's', 't', 'P', 'a', 'l', 'i', 'n', 'd', 'r', 'o', 'm', 'e', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', ' ', '%', 'd', '\0'}};
struct struct_1 string_25 = {14, (char[]){'P', 'A', 'Y', 'P', 'A', 'L', 'I', 'S', 'H', 'I', 'R', 'I', 'N', 'G', '\0'}};
struct struct_1 string_26 = {14, (char[]){'P', 'A', 'H', 'N', 'A', 'P', 'L', 'S', 'I', 'I', 'G', 'Y', 'I', 'R', '\0'}};
struct struct_1 string_27 = {16, (char[]){'c', 'o', 'n', 'v', 'e', 'r', 't', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_28 = {15, (char[]){'c', 'o', 'n', 'v', 'e', 'r', 't', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
struct struct_1 string_29 = {16, (char[]){'r', 'e', 'v', 'e', 'r', 's', 'e', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_30 = {15, (char[]){'r', 'e', 'v', 'e', 'r', 's', 'e', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
struct struct_1 string_31 = {2, (char[]){'4', '2', '\0'}};
struct struct_1 string_32 = {15, (char[]){'m', 'y', 'A', 't', 'o', 'i', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_33 = {14, (char[]){'m', 'y', 'A', 't', 'o', 'i', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
struct struct_1 string_34 = {21, (char[]){'i', 's', 'P', 'a', 'l', 'i', 'n', 'd', 'r', 'o', 'm', 'e', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_35 = {20, (char[]){'i', 's', 'P', 'a', 'l', 'i', 'n', 'd', 'r', 'o', 'm', 'e', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
struct struct_1 string_36 = {2, (char[]){'a', 'a', '\0'}};
struct struct_1 string_37 = {2, (char[]){'a', '*', '\0'}};
struct struct_1 string_38 = {16, (char[]){'i', 's', 'M', 'a', 't', 'c', 'h', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_39 = {15, (char[]){'i', 's', 'M', 'a', 't', 'c', 'h', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
struct struct_1 string_40 = {16, (char[]){'m', 'a', 'x', 'A', 'r', 'e', 'a', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_41 = {18, (char[]){'m', 'a', 'x', 'A', 'r', 'e', 'a', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', ' ', '%', 'd', '\0'}};
struct struct_1 string_42 = {8, (char[]){'f', 'i', 'z', 'z', 'b', 'u', 'z', 'z', '\0'}};
struct struct_1 string_43 = {4, (char[]){'f', 'i', 'z', 'z', '\0'}};
struct struct_1 string_44 = {4, (char[]){'b', 'u', 'z', 'z', '\0'}};
struct struct_1 string_45 = {2, (char[]){'%', 'd', '\0'}};
struct struct_1 string_46 = {8, (char[]){'f', 'i', 'z', 'z', 'b', 'u', 'z', 'z', '\0'}};
struct struct_1 string_47 = {4, (char[]){'f', 'i', 'z', 'z', '\0'}};
struct struct_1 string_48 = {4, (char[]){'b', 'u', 'z', 'z', '\0'}};
struct struct_1 string_49 = {2, (char[]){'%', 'd', '\0'}};
struct struct_1 string_50 = {8, (char[]){'a', 'b', 'c', 'a', 'b', 'c', 'b', 'b', '\0'}};
struct struct_1 string_51 = {33, (char[]){'l', 'e', 'n', 'g', 't', 'h', 'O', 'f', 'L', 'o', 'n', 'g', 'e', 's', 't', 'S', 'u', 'b', 's', 't', 'r', 'i', 'n', 'g', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_52 = {35, (char[]){'l', 'e', 'n', 'g', 't', 'h', 'O', 'f', 'L', 'o', 'n', 'g', 'e', 's', 't', 'S', 'u', 'b', 's', 't', 'r', 'i', 'n', 'g', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', ' ', '%', 'd', '\0'}};
struct struct_1 string_53 = {10, (char[]){'<', 's', 't', 'd', 'l', 'i', 'b', '.', 'h', '>', '\0'}};
struct struct_1 string_54 = {9, (char[]){'<', 's', 't', 'd', 'i', 'o', '.', 'h', '>', '\0'}};
struct struct_1 string_55 = {10, (char[]){'<', 's', 't', 'd', 'i', 'n', 't', '.', 'h', '>', '\0'}};
struct struct_1 string_56 = {11, (char[]){'<', 's', 't', 'd', 'b', 'o', 'o', 'l', '.', 'h', '>', '\0'}};

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
// AST_CALL
// test/leetcode.orng:14
	test_leetcode_test_isMatch();
// AST_CALL
// test/leetcode.orng:15
	test_leetcode_test_maxArea();
return_block_32:;
}

void test_leetcode_test_twoSum()
{
	int64_t _0 = 0;
// AST_DEFINE
// test/leetcode.orng:58
	int64_t _1 = 2;
	int64_t _2 = 7;
	int64_t _3 = 11;
	int64_t _4 = 15;
	struct struct_3 _5 = {4, (int64_t[]){_1, _2, _3, _4}};
	struct struct_3 _43_nums = _5;
// AST_DEFINE
// test/leetcode.orng:59
	int64_t _6 = 9;
	int64_t _43_target = _6;
// AST_DEFINE
// test/leetcode.orng:61
	struct struct_3 _7 = test_leetcode_twoSum(_43_nums, _43_target);
	struct struct_3 _43_ans = _7;
// AST_IF
// test/leetcode.orng:67
	int64_t _8 = 0;
	int64_t _9 = 0;
	struct struct_3 _10 = _43_ans;
	int64_t _11 = _10.data[_9];
	struct struct_3 _12 = _43_nums;
	int64_t _13 = _12.data[_11];
	int64_t _14 = 1;
	struct struct_3 _15 = _43_ans;
	int64_t _16 = _15.data[_14];
	struct struct_3 _17 = _43_nums;
	int64_t _18 = _17.data[_16];
	int64_t _19 = _13 + _18;
	int64_t _20 = _43_target;
	bool _21 = _19 == _20;
	if (!_21) goto else_44;
	int64_t _22 = 0;
// AST_CALL
// test/leetcode.orng:64
	struct struct_1 _23 = string_14;
	int64_t _24 = std_system_println(_23);
	_22 = _24;
	_8 = _22;
	goto end_44;
else_44:;
	int64_t _25 = 0;
// AST_CALL
// test/leetcode.orng:66
	struct struct_1 _26 = string_15;
	int64_t _27 = 0;
	struct struct_3 _28 = _43_ans;
	int64_t _29 = _28.data[_27];
	struct struct_3 _30 = _43_nums;
	int64_t _31 = _30.data[_29];
	int64_t _32 = 1;
	struct struct_3 _33 = _43_ans;
	int64_t _34 = _33.data[_32];
	struct struct_3 _35 = _43_nums;
	int64_t _36 = _35.data[_34];
	int64_t _37 = std_system_println(_26, _31, _36);
	_25 = _37;
	_8 = _25;
end_44:;
	_0 = _8;
return_block_43:;
}

struct struct_3 test_leetcode_twoSum(struct struct_3 _nums, int64_t _target)
{
	struct struct_3 retval;
	struct struct_3 _0 = ((struct struct_3){2, (int64_t*[]){0, 0}});
// AST_FOR
// test/leetcode.orng:53
	int64_t _1 = 0;
	int64_t _38_i = _1;
begin_39:;
	int64_t _2 = _38_i;
	struct struct_3 _3 = _nums;
	int64_t _4 = _3.length;
	int64_t _5 = 1;
	int64_t _6 = _4 - _5;
	bool _7 = _2 < _6;
	if (!_7) goto end_39;
// AST_FOR
// test/leetcode.orng:52
	int64_t _8 = _38_i;
	int64_t _9 = 1;
	int64_t _10 = _8 + _9;
	int64_t _40_j = _10;
begin_41:;
	int64_t _11 = _40_j;
	struct struct_3 _12 = _nums;
	int64_t _13 = _12.length;
	bool _14 = _11 < _13;
	if (!_14) goto end_41;
// AST_IF
// test/leetcode.orng:51
	int64_t _15 = _38_i;
	struct struct_3 _16 = _nums;
	int64_t _17 = _16.data[_15];
	int64_t _18 = _40_j;
	struct struct_3 _19 = _nums;
	int64_t _20 = _19.data[_18];
	int64_t _21 = _17 + _20;
	int64_t _22 = _target;
	bool _23 = _21 == _22;
	if (!_23) goto else_42;
	struct struct_3 _24 = ((struct struct_3){2, (int64_t*[]){0, 0}});
// AST_RETURN
// test/leetcode.orng:50
	int64_t _25 = _38_i;
	int64_t _26 = _40_j;
	struct struct_3 _27 = {2, (int64_t[]){_25, _26}};
	int64_t _28 = 2;
	struct struct_3 _29 = {_28, malloc(sizeof(int64_t) * _28)};
	_29.length = _28;
	for(int i = 0; i < _28; i++) {_29.data[i] = _27.data[i];}
	retval = _29;
	goto return_block_37;
	_24 = _29;
	goto end_42;
else_42:;
end_42:;
	// for post
	int64_t _30 = 1;
	_40_j += _30;
	goto begin_41;
end_41:;
	// for post
	int64_t _31 = 1;
	_38_i += _31;
	goto begin_39;
end_39:;
// AST_RETURN
// test/leetcode.orng:54
	int64_t _32 = -1;
	int64_t _33 = -2;
	struct struct_3 _34 = {2, (int64_t[]){_32, _33}};
	int64_t _35 = 2;
	struct struct_3 _36 = {_35, malloc(sizeof(int64_t) * _35)};
	_36.length = _35;
	for(int i = 0; i < _35; i++) {_36.data[i] = _34.data[i];}
	retval = _36;
	goto return_block_37;
	_0 = _36;
	retval = _0;
return_block_37:;
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
	exit(_5);
	goto end_2;
else_2:;
end_2:;
return_block_1:;
}

FILE* std_system_open(struct struct_1 _filename, struct struct_1 _mode)
{
	FILE* retval;
	FILE* _0 = 0;
// AST_RETURN
// std/system.orng:13
	struct struct_1 _1 = _filename;
	int8_t* _2 = _1.data;
	struct struct_1 _3 = _mode;
	int8_t* _4 = _3.data;
	FILE* _5 = fopen(_2, _4);
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
	int64_t _0 = 0;
// AST_RETURN
// std/system.orng:17
	int64_t _1 = fgetc(_file);
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
	int64_t _0 = 0;
// AST_RETURN
// std/system.orng:21
	int64_t _1 = ungetc(_c, _file);
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
	int64_t _0 = 0;
	retval = _0;
return_block_:;
	return retval;
}

int64_t std_system_err(struct struct_1 _format, ...)
{
	int64_t retval;
	int64_t _0 = 0;
	retval = _0;
return_block_:;
	return retval;
}

int64_t std_system_errln(struct struct_1 _format, ...)
{
	int64_t retval;
	int64_t _0 = 0;
	retval = _0;
return_block_:;
	return retval;
}

int64_t std_math_abs(int64_t _x)
{
	int64_t retval;
	int64_t _0 = 0;
	int64_t _1 = _x;
	int64_t _2 = 0;
	bool _3 = _1 > _2;
	if (!_3) goto else_3;
	int64_t _4 = 0;
// AST_IDENT
// std/math.orng:3
	int64_t _5 = _x;
	_4 = _5;
	_0 = _4;
	goto end_3;
else_3:;
	int64_t _6 = 0;
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
	double _0 = 0;
	double _1 = _x;
	double _2 = _y;
	bool _3 = _1 > _2;
	if (!_3) goto else_5;
	double _4 = 0;
// AST_IDENT
// std/math.orng:7
	double _5 = _x;
	_4 = _5;
	_0 = _4;
	goto end_5;
else_5:;
	double _6 = 0;
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
	double _0 = 0;
	double _1 = _x;
	double _2 = _y;
	bool _3 = _1 < _2;
	if (!_3) goto else_7;
	double _4 = 0;
// AST_IDENT
// std/math.orng:8
	double _5 = _x;
	_4 = _5;
	_0 = _4;
	goto end_7;
else_7:;
	double _6 = 0;
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
	bool _0 = 0;
// AST_RETURN
// std/string.orng:4
	struct struct_1 _1 = _str1;
	int8_t* _2 = _1.data;
	struct struct_1 _3 = _str2;
	int8_t* _4 = _3.data;
	int64_t _5 = strcmp(_2, _4);
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
	struct struct_1 _0 = ((struct struct_1){0, 0});
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
	void* _11 = memset(_7, _8, _10);
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
	int64_t _24 = strncpy_s(_13, _17, _19, _23);
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
	int64_t _0 = 0;
// AST_RETURN
// std/string.orng:16
	struct struct_1 _1 = _dst;
	int8_t* _2 = _1.data;
	struct struct_1 _3 = _src;
	int8_t* _4 = _3.data;
	int64_t _5 = strncpy_s(_2, _dstSize, _4, _srcSize);
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
	bool _0 = 0;
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
	bool _12 = 0;
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
	bool _0 = 0;
// AST_IF
// std/string.orng:38
	bool _1 = 0;
	struct struct_1 _2 = _a;
	int64_t _3 = _2.length;
	struct struct_1 _4 = _b;
	int64_t _5 = _4.length;
	bool _6 = _3 != _5;
	if (!_6) goto else_17;
	bool _7 = 0;
// AST_RETURN
// std/string.orng:30
	bool _8 = 0;
	retval = _8;
	goto return_block_16;
	_7 = _8;
	_1 = _7;
	goto end_17;
else_17:;
	bool _9 = 0;
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
	bool _22 = 0;
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
	struct struct_1 _0 = ((struct struct_1){0, 0});
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
	int8_t _5 = 0;
	int64_t _6 = 0;
	int64_t _23_i = _6;
begin_24:;
	int64_t _7 = _23_i;
	struct struct_1 _8 = _22_retval;
	int64_t _9 = _8.length;
	bool _10 = _7 < _9;
	if (!_10) goto end_24;
	int8_t _11 = 0;
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
	_5 = _11;
end_24:;
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
	int8_t* _0 = 0;
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
	int8_t _3 = 0;
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
	int8_t _11 = 0;
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
	_3 = _11;
end_27:;
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
	struct struct_1 _0 = ((struct struct_1){0, 0});
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

void test_leetcode_test_addTwoNumbers()
{
	int64_t _0 = 0;
// AST_DEFINE
// test/leetcode.orng:98
	int64_t _1 = 3;
	int64_t _2 = 0;
	struct struct_7 _3 = ((struct struct_7){0});
	_3.tag = 0;
	struct struct_6 _4 = {_1, _3};
	struct struct_6* _5 = calloc(sizeof(struct struct_6), 1);
	*_5 = _4;
	struct struct_6* _48_l1_c = _5;
// AST_DEFINE
// test/leetcode.orng:99
	int64_t _6 = 4;
	struct struct_6* _7 = _48_l1_c;
	struct struct_7 _8 = ((struct struct_7){0});
	_8.tag = 1;
	_8.something = _7;
	struct struct_6 _9 = {_6, _8};
	struct struct_6* _10 = calloc(sizeof(struct struct_6), 1);
	*_10 = _9;
	struct struct_6* _48_l1_b = _10;
// AST_DEFINE
// test/leetcode.orng:100
	int64_t _11 = 2;
	struct struct_6* _12 = _48_l1_b;
	struct struct_7 _13 = ((struct struct_7){0});
	_13.tag = 1;
	_13.something = _12;
	struct struct_6 _14 = {_11, _13};
	struct struct_6* _15 = calloc(sizeof(struct struct_6), 1);
	*_15 = _14;
	struct struct_6* _48_l1 = _15;
// AST_DEFINE
// test/leetcode.orng:101
	int64_t _16 = 4;
	int64_t _17 = 0;
	struct struct_7 _18 = ((struct struct_7){0});
	_18.tag = 0;
	struct struct_6 _19 = {_16, _18};
	struct struct_6* _20 = calloc(sizeof(struct struct_6), 1);
	*_20 = _19;
	struct struct_6* _48_l2_c = _20;
// AST_DEFINE
// test/leetcode.orng:102
	int64_t _21 = 6;
	struct struct_6* _22 = _48_l2_c;
	struct struct_7 _23 = ((struct struct_7){0});
	_23.tag = 1;
	_23.something = _22;
	struct struct_6 _24 = {_21, _23};
	struct struct_6* _25 = calloc(sizeof(struct struct_6), 1);
	*_25 = _24;
	struct struct_6* _48_l2_b = _25;
// AST_DEFINE
// test/leetcode.orng:103
	int64_t _26 = 5;
	struct struct_6* _27 = _48_l2_b;
	struct struct_7 _28 = ((struct struct_7){0});
	_28.tag = 1;
	_28.something = _27;
	struct struct_6 _29 = {_26, _28};
	struct struct_6* _30 = calloc(sizeof(struct struct_6), 1);
	*_30 = _29;
	struct struct_6* _48_l2 = _30;
// AST_DEFINE
// test/leetcode.orng:105
	struct struct_6* _31 = test_leetcode_addTwoNumbers(_48_l1, _48_l2);
	struct struct_6* _48_ans = _31;
// AST_DEFINE
// test/leetcode.orng:107
// AST_IF
// test/leetcode.orng:118
	int64_t _32 = 0;
	struct struct_6* _33 = _48_ans;
	struct struct_7 _34 = ((struct struct_7){0});
	_34.tag = 1;
	_34.something = _33;
	int64_t _35 = 7;
	int64_t _36 = 0;
	int64_t _37 = 8;
	struct struct_3 _38 = {3, (int64_t[]){_35, _36, _37}};
	bool _39 = test_leetcode_hasValue(_34, _38);
	if (!_39) goto else_51;
	int64_t _40 = 0;
// AST_CALL
// test/leetcode.orng:115
	struct struct_1 _41 = string_16;
	int64_t _42 = std_system_println(_41);
	_40 = _42;
	_32 = _40;
	goto end_51;
else_51:;
	int64_t _43 = 0;
// AST_CALL
// test/leetcode.orng:117
	struct struct_1 _44 = string_17;
	int64_t _45 = std_system_println(_44);
	_43 = _45;
	_32 = _43;
end_51:;
	_0 = _32;
return_block_48:;
}

bool test_leetcode_hasValue(struct struct_7 _node, struct struct_3 _x)
{
	bool retval;
	bool _0 = 0;
	struct struct_7 _1 = _node;
	bool _2 = _1.tag != 0;
	if (!_2) goto else_49;
	bool _3 = 0;
// AST_AND
// test/leetcode.orng:109
	bool _4 = 0;
	struct struct_7 _5 = _node;
	struct struct_6* _6 = _5.something;
	int64_t _7 = _6->val;
	int64_t _8 = 0;
	struct struct_3 _9 = _x;
	int64_t _10 = _9.data[_8];
	bool _11 = _7 == _10;
	if (!_11) goto over_0;
	struct struct_7 _12 = _node;
	struct struct_6* _13 = _12.something;
	struct struct_7 _14 = _13->next;
	struct struct_3 _15 = _x;
	int64_t _16 = 1;
	int64_t _17 = _15.length;
	struct struct_3 _18 = {_17 - _16, _15.data + _16};
	bool _19 = test_leetcode_hasValue(_14, _18);
	_4 = _19;
over_0:;
	_3 = _4;
	_0 = _3;
	goto end_49;
else_49:;
	bool _20 = 0;
// AST_TRUE
// test/leetcode.orng:111
	bool _21 = 1;
	_20 = _21;
	_0 = _20;
end_49:;
	retval = _0;
return_block_50:;
	return retval;
}

struct struct_6* test_leetcode_addTwoNumbers(struct struct_6* _l1, struct struct_6* _l2)
{
	struct struct_6* retval;
	struct struct_6* _0 = _l1;
	struct struct_7 _1 = ((struct struct_7){0});
	_1.tag = 1;
	_1.something = _0;
	int64_t _2 = test_leetcode_convertToInt(_1);
	struct struct_6* _3 = _l2;
	struct struct_7 _4 = ((struct struct_7){0});
	_4.tag = 1;
	_4.something = _3;
	int64_t _5 = test_leetcode_convertToInt(_4);
	int64_t _6 = _2 + _5;
	struct struct_6* _7 = test_leetcode_convertToList(_6);
	retval = _7;
return_block_:;
	return retval;
}

struct struct_6* test_leetcode_convertToList(int64_t _i)
{
	struct struct_6* retval;
	struct struct_6* _0 = 0;
	int64_t _1 = _i;
	int64_t _2 = 10;
	bool _3 = _1 < _2;
	if (!_3) goto else_46;
	struct struct_6* _4 = 0;
// AST_NEW
// test/leetcode.orng:89
	int64_t _5 = _i;
	int64_t _6 = 0;
	struct struct_7 _7 = ((struct struct_7){0});
	_7.tag = 0;
	struct struct_6 _8 = {_5, _7};
	struct struct_6* _9 = calloc(sizeof(struct struct_6), 1);
	*_9 = _8;
	_4 = _9;
	_0 = _4;
	goto end_46;
else_46:;
	struct struct_6* _10 = 0;
// AST_NEW
// test/leetcode.orng:91
	int64_t _11 = _i;
	int64_t _12 = 10;
	int64_t _13 = _11 % _12;
	int64_t _14 = _i;
	int64_t _15 = 10;
	int64_t _16 = _14 / _15;
	struct struct_6* _17 = test_leetcode_convertToList(_16);
	struct struct_7 _18 = ((struct struct_7){0});
	_18.tag = 1;
	_18.something = _17;
	struct struct_6 _19 = {_13, _18};
	struct struct_6* _20 = calloc(sizeof(struct struct_6), 1);
	*_20 = _19;
	_10 = _20;
	_0 = _10;
end_46:;
	retval = _0;
return_block_47:;
	return retval;
}

int64_t test_leetcode_convertToInt(struct struct_7 _l)
{
	int64_t retval;
	int64_t _0 = 0;
	struct struct_7 _1 = _l;
	switch (_1.tag) {
	case 0:
	{
	int64_t _2 = 0;
	_0 = _2;
	break;
	} // end case
	case 1:
	{
	struct struct_7 _3 = _l;
	struct struct_6* _4 = _3.something;
	int64_t _5 = _4->val;
	struct struct_7 _6 = _l;
	struct struct_6* _7 = _6.something;
	struct struct_7 _8 = _7->next;
	int64_t _9 = test_leetcode_convertToInt(_8);
	int64_t _10 = 10;
	int64_t _11 = _9 * _10;
	int64_t _12 = _5 + _11;
	_0 = _12;
	break;
	} // end case
	} // end switch
	retval = _0;
return_block_:;
	return retval;
}

void test_leetcode_test_findMedianSortedArrays()
{
	int64_t _0 = 0;
// AST_DEFINE
// test/leetcode.orng:203
	int64_t _1 = 1;
	int64_t _2 = 3;
	struct struct_3 _3 = {2, (int64_t[]){_1, _2}};
	struct struct_3 _77_nums1 = _3;
// AST_DEFINE
// test/leetcode.orng:204
	int64_t _4 = 2;
	struct struct_3 _5 = {1, (int64_t[]){_4}};
	struct struct_3 _77_nums2 = _5;
// AST_DEFINE
// test/leetcode.orng:206
	float _6 = test_leetcode_findMedianSortedArrays(_77_nums1, _77_nums2);
	float _77_ans = _6;
// AST_IF
// test/leetcode.orng:212
	int64_t _7 = 0;
	float _8 = _77_ans;
	float _9 = 2.000000;
	bool _10 = _8 == _9;
	if (!_10) goto else_78;
	int64_t _11 = 0;
// AST_CALL
// test/leetcode.orng:209
	struct struct_1 _12 = string_18;
	int64_t _13 = std_system_println(_12);
	_11 = _13;
	_7 = _11;
	goto end_78;
else_78:;
	int64_t _14 = 0;
// AST_CALL
// test/leetcode.orng:211
	struct struct_1 _15 = string_19;
	int64_t _16 = std_system_println(_15, _77_ans);
	_14 = _16;
	_7 = _14;
end_78:;
	_0 = _7;
return_block_77:;
}

float test_leetcode_findMedianSortedArrays(struct struct_3 _nums1, struct struct_3 _nums2)
{
	float retval;
	int defer_0 = 0;
	float _0 = 0;
// AST_DEFINE
// test/leetcode.orng:172
	struct struct_3 _1 = _nums1;
	int64_t _2 = _1.length;
	struct struct_3 _3 = _nums2;
	int64_t _4 = _3.length;
	int64_t _5 = _2 + _4;
	struct struct_3 _6 = {_5, malloc(sizeof(int64_t) * _5)};
	_6.length = _5;
	for(int i = 0; i < _5; i++) {_6.data[i] = 0;}
	struct struct_3 _66_merged = _6;
// AST_DEFER
// test/leetcode.orng:173
	defer_0 = 1;
// AST_DEFINE
// test/leetcode.orng:175
	int64_t _7 = 0;
	int64_t _66_i = _7;
// AST_DEFINE
// test/leetcode.orng:176
	int64_t _8 = 0;
	int64_t _66_j = _8;
// AST_FOR
// test/leetcode.orng:193
begin_68:;
	int64_t _9 = _66_i;
	int64_t _10 = _66_j;
	int64_t _11 = _9 + _10;
	struct struct_3 _12 = _66_merged;
	int64_t _13 = _12.length;
	bool _14 = _11 < _13;
	if (!_14) goto end_68;
// AST_IF
// test/leetcode.orng:192
	bool _15 = 0;
	int64_t _16 = _66_i;
	struct struct_3 _17 = _nums1;
	int64_t _18 = _17.length;
	bool _19 = _16 < _18;
	if (!_19) goto over_0;
	int64_t _20 = _66_j;
	struct struct_3 _21 = _nums2;
	int64_t _22 = _21.length;
	bool _23 = _20 < _22;
	_15 = _23;
over_0:;
	if (!_15) goto else_69;
	int64_t _24 = 0;
// AST_IF
// test/leetcode.orng:185
	int64_t _25 = 0;
	int64_t _26 = _66_i;
	struct struct_3 _27 = _nums1;
	int64_t _28 = _27.data[_26];
	int64_t _29 = _66_j;
	struct struct_3 _30 = _nums2;
	int64_t _31 = _30.data[_29];
	bool _32 = _28 < _31;
	if (!_32) goto else_70;
	int64_t _33 = 0;
// AST_ASSIGN
// test/leetcode.orng:180
	int64_t _34 = _66_i;
	struct struct_3 _35 = _nums1;
	int64_t _36 = _35.data[_34];
	int64_t _37 = _66_i;
	int64_t _38 = _66_j;
	int64_t _39 = _37 + _38;
	_66_merged.data[_39] = _36;
// AST_ADD_ASSIGN
// test/leetcode.orng:181
	int64_t _40 = 1;
	_66_i += _40;
	_33 = _40;
	_25 = _33;
	goto end_70;
else_70:;
	int64_t _41 = 0;
// AST_ASSIGN
// test/leetcode.orng:183
	int64_t _42 = _66_j;
	struct struct_3 _43 = _nums2;
	int64_t _44 = _43.data[_42];
	int64_t _45 = _66_i;
	int64_t _46 = _66_j;
	int64_t _47 = _45 + _46;
	_66_merged.data[_47] = _44;
// AST_ADD_ASSIGN
// test/leetcode.orng:184
	int64_t _48 = 1;
	_66_j += _48;
	_41 = _48;
	_25 = _41;
end_70:;
	_24 = _25;
	goto end_69;
else_69:;
	int64_t _49 = _66_i;
	struct struct_3 _50 = _nums1;
	int64_t _51 = _50.length;
	bool _52 = _49 < _51;
	if (!_52) goto else_72;
	int64_t _53 = 0;
// AST_ASSIGN
// test/leetcode.orng:187
	int64_t _54 = _66_i;
	struct struct_3 _55 = _nums1;
	int64_t _56 = _55.data[_54];
	int64_t _57 = _66_i;
	int64_t _58 = _66_j;
	int64_t _59 = _57 + _58;
	_66_merged.data[_59] = _56;
// AST_ADD_ASSIGN
// test/leetcode.orng:188
	int64_t _60 = 1;
	_66_i += _60;
	_53 = _60;
	goto end_72;
else_72:;
	int64_t _61 = _66_j;
	struct struct_3 _62 = _nums2;
	int64_t _63 = _62.length;
	bool _64 = _61 < _63;
	if (!_64) goto else_73;
	int64_t _65 = 0;
// AST_ASSIGN
// test/leetcode.orng:190
	int64_t _66 = _66_j;
	struct struct_3 _67 = _nums2;
	int64_t _68 = _67.data[_66];
	int64_t _69 = _66_i;
	int64_t _70 = _66_j;
	int64_t _71 = _69 + _70;
	_66_merged.data[_71] = _68;
// AST_ADD_ASSIGN
// test/leetcode.orng:191
	int64_t _72 = 1;
	_66_j += _72;
	_65 = _72;
	goto end_73;
else_73:;
end_73:;
end_72:;
end_69:;
	// for post
	goto begin_68;
end_68:;
// AST_IF
// test/leetcode.orng:199
	float _73 = 0;
	struct struct_3 _74 = _66_merged;
	int64_t _75 = _74.length;
	int64_t _76 = 2;
	int64_t _77 = _75 % _76;
	int64_t _78 = 0;
	bool _79 = _77 == _78;
	if (!_79) goto else_74;
	float _80 = 0;
// AST_DIVIDE
// test/leetcode.orng:196
	int64_t _81 = 0;
// AST_ADD
// test/leetcode.orng:196
	struct struct_3 _82 = _66_merged;
	int64_t _83 = _82.length;
	int64_t _84 = 2;
	int64_t _85 = _83 / _84;
	struct struct_3 _86 = _66_merged;
	int64_t _87 = _86.data[_85];
	struct struct_3 _88 = _66_merged;
	int64_t _89 = _88.length;
	int64_t _90 = 2;
	int64_t _91 = _89 / _90;
	int64_t _92 = 1;
	int64_t _93 = _91 + _92;
	struct struct_3 _94 = _66_merged;
	int64_t _95 = _94.data[_93];
	int64_t _96 = _87 + _95;
	_81 = _96;
	float _97 = 2.000000;
	float _98 = _81 / _97;
	_80 = _98;
	_73 = _80;
	goto end_74;
else_74:;
	float _99 = 0;
// AST_CAST
// test/leetcode.orng:198
	struct struct_3 _100 = _66_merged;
	int64_t _101 = _100.length;
	int64_t _102 = 2;
	int64_t _103 = _101 / _102;
	struct struct_3 _104 = _66_merged;
	int64_t _105 = _104.data[_103];
	float _106 = (float)_105;
	_99 = _106;
	_73 = _99;
end_74:;
	_0 = _73;
	retval = _0;
return_block_66:;
	if (defer_0) {
	struct struct_3 _107 = _66_merged;
	free(_107.data);
	}
	return retval;
}

void test_leetcode_test_longestPalindrome()
{
	int64_t _0 = 0;
// AST_DEFINE
// test/leetcode.orng:242
	struct struct_1 _1 = string_20;
	struct struct_1 _88_s = _1;
// AST_DEFINE
// test/leetcode.orng:244
	struct struct_1 _2 = test_leetcode_longestPalindrome(_88_s);
	struct struct_1 _88_ans = _2;
// AST_IF
// test/leetcode.orng:250
	int64_t _3 = 0;
	bool _4 = 1;
	struct struct_1 _5 = string_21;
	bool _6 = std_string_equals(_88_ans, _5);
	if (_6) goto over_0;
	struct struct_1 _7 = string_22;
	bool _8 = std_string_equals(_88_ans, _7);
	_4 = _8;
over_0:;
	if (!_4) goto else_89;
	int64_t _9 = 0;
// AST_CALL
// test/leetcode.orng:247
	struct struct_1 _10 = string_23;
	int64_t _11 = std_system_println(_10);
	_9 = _11;
	_3 = _9;
	goto end_89;
else_89:;
	int64_t _12 = 0;
// AST_CALL
// test/leetcode.orng:249
	struct struct_1 _13 = string_24;
	struct struct_1 _14 = _88_ans;
	int64_t _15 = _14.length;
	int64_t _16 = std_system_println(_13, _15);
	_12 = _16;
	_3 = _12;
end_89:;
	_0 = _3;
return_block_88:;
}

struct struct_1 test_leetcode_longestPalindrome(struct struct_1 _s)
{
	struct struct_1 retval;
	struct struct_1 _0 = ((struct struct_1){0, 0});
// AST_DEFINE
// test/leetcode.orng:219
// AST_DEFINE
// test/leetcode.orng:227
	int64_t _1 = 0;
	int64_t _80_start = _1;
// AST_DEFINE
// test/leetcode.orng:228
	int64_t _2 = 0;
	int64_t _80_end = _2;
// AST_FOR
// test/leetcode.orng:237
	int64_t _3 = 0;
	int64_t _84_i = _3;
begin_85:;
	int64_t _4 = _84_i;
	struct struct_1 _5 = _s;
	int64_t _6 = _5.length;
	bool _7 = _4 < _6;
	if (!_7) goto end_85;
// AST_DEFINE
// test/leetcode.orng:230
	int64_t _8 = test_leetcode_expandAroundCenter(_s, _84_i, _84_i);
	int64_t _85_len1 = _8;
// AST_DEFINE
// test/leetcode.orng:231
	int64_t _9 = _84_i;
	int64_t _10 = 1;
	int64_t _11 = _9 + _10;
	int64_t _12 = test_leetcode_expandAroundCenter(_s, _84_i, _11);
	int64_t _85_len2 = _12;
// AST_DEFINE
// test/leetcode.orng:232
	double _13 = std_math_max(_85_len1, _85_len2);
	int64_t _14 = (int64_t)_13;
	int64_t _85_len = _14;
// AST_IF
// test/leetcode.orng:236
	int64_t _15 = _85_len;
	int64_t _16 = _80_end;
	int64_t _17 = _80_start;
	int64_t _18 = _16 - _17;
	bool _19 = _15 > _18;
	if (!_19) goto else_86;
	int64_t _20 = 0;
// AST_ASSIGN
// test/leetcode.orng:234
	int64_t _21 = _84_i;
	int64_t _22 = 0;
// AST_SUBTRACT
// test/leetcode.orng:234
	int64_t _23 = _85_len;
	int64_t _24 = 1;
	int64_t _25 = _23 - _24;
	_22 = _25;
	int64_t _26 = 2;
	int64_t _27 = _22 / _26;
	int64_t _28 = _21 - _27;
	_80_start = _28;
// AST_ASSIGN
// test/leetcode.orng:235
	int64_t _29 = _84_i;
	int64_t _30 = _85_len;
	int64_t _31 = 2;
	int64_t _32 = _30 / _31;
	int64_t _33 = _29 + _32;
	_80_end = _33;
	_20 = _33;
	goto end_86;
else_86:;
end_86:;
	// for post
	int64_t _34 = 1;
	_84_i += _34;
	goto begin_85;
end_85:;
// AST_SLICE
// test/leetcode.orng:238
	struct struct_1 _35 = _s;
	int64_t _36 = _80_start;
	int64_t _37 = _80_end;
	int64_t _38 = 1;
	int64_t _39 = _37 + _38;
	struct struct_1 _40 = {_39 - _36, _35.data + _36};
	_0 = _40;
	retval = _0;
return_block_80:;
	return retval;
}

int64_t test_leetcode_expandAroundCenter(struct struct_1 _s, int64_t _left, int64_t _right)
{
	int64_t retval;
	int64_t _0 = 0;
// AST_FOR
// test/leetcode.orng:223
	int64_t _1 = 0;
begin_83:;
	bool _2 = 0;
	bool _3 = 0;
	int64_t _4 = _left;
	int64_t _5 = 0;
	bool _6 = _4 >= _5;
	if (!_6) goto over_1;
	int64_t _7 = _right;
	struct struct_1 _8 = _s;
	int64_t _9 = _8.length;
	bool _10 = _7 < _9;
	_3 = _10;
over_1:;
	if (!_3) goto over_0;
	int64_t _11 = _left;
	struct struct_1 _12 = _s;
	int8_t _13 = _12.data[_11];
	int64_t _14 = _right;
	struct struct_1 _15 = _s;
	int8_t _16 = _15.data[_14];
	bool _17 = _13 == _16;
	_2 = _17;
over_0:;
	if (!_2) goto end_83;
	int64_t _18 = 0;
// AST_SUB_ASSIGN
// test/leetcode.orng:221
	int64_t _19 = 1;
	_left -= _19;
// AST_ADD_ASSIGN
// test/leetcode.orng:222
	int64_t _20 = 1;
	_right += _20;
	_18 = _20;
	_1 = _18;
	// for post
	goto begin_83;
	_1 = _18;
end_83:;
// AST_SUBTRACT
// test/leetcode.orng:224
	int64_t _21 = _right;
	int64_t _22 = _left;
	int64_t _23 = _21 - _22;
	int64_t _24 = 1;
	int64_t _25 = _23 - _24;
	_0 = _25;
	retval = _0;
return_block_81:;
	return retval;
}

void test_leetcode_test_convert()
{
	int64_t _0 = 0;
// AST_DEFINE
// test/leetcode.orng:310
	struct struct_1 _1 = string_25;
	int64_t _2 = 3;
	struct struct_1 _3 = test_leetcode_convert(_1, _2);
	struct struct_1 _108_ans = _3;
// AST_IF
// test/leetcode.orng:316
	int64_t _4 = 0;
	struct struct_1 _5 = string_26;
	bool _6 = std_string_equals(_108_ans, _5);
	if (!_6) goto else_109;
	int64_t _7 = 0;
// AST_CALL
// test/leetcode.orng:313
	struct struct_1 _8 = string_27;
	int64_t _9 = std_system_println(_8);
	_7 = _9;
	_4 = _7;
	goto end_109;
else_109:;
	int64_t _10 = 0;
// AST_CALL
// test/leetcode.orng:315
	struct struct_1 _11 = string_28;
	int64_t _12 = std_system_println(_11);
	_10 = _12;
	_4 = _10;
end_109:;
	_0 = _4;
return_block_108:;
}

struct struct_1 test_leetcode_convert(struct struct_1 _s, int64_t _numRows)
{
	struct struct_1 retval;
	int defer_0 = 0;
	struct struct_1 _0 = ((struct struct_1){0, 0});
// AST_DEFINE
// test/leetcode.orng:263
	struct struct_1 _1 = _s;
	int64_t _2 = _1.length;
	struct struct_2 _3 = {_2, malloc(sizeof(struct struct_1) * _2)};
	_3.length = _2;
	for(int i = 0; i < _2; i++) {_3.data[i] = ((struct struct_1){0, 0});}
	struct struct_2 _91_board = _3;
// AST_FOR
// test/leetcode.orng:266
	struct struct_1 _4 = ((struct struct_1){0, 0});
	int64_t _5 = 0;
	int64_t _92_i = _5;
begin_93:;
	int64_t _6 = _92_i;
	struct struct_1 _7 = _s;
	int64_t _8 = _7.length;
	bool _9 = _6 < _8;
	if (!_9) goto end_93;
	struct struct_1 _10 = ((struct struct_1){0, 0});
// AST_ASSIGN
// test/leetcode.orng:265
	int64_t _11 = _numRows;
	struct struct_1 _12 = {_11, malloc(sizeof(int8_t) * _11)};
	_12.length = _11;
	for(int i = 0; i < _11; i++) {_12.data[i] = 0;}
	int64_t _13 = _92_i;
	_91_board.data[_13] = _12;
	_10 = _12;
	_4 = _10;
	// for post
	int64_t _14 = 1;
	_92_i += _14;
	goto begin_93;
	_4 = _10;
end_93:;
// AST_DEFER
// test/leetcode.orng:272
	defer_0 = 1;
// AST_DEFINE
// test/leetcode.orng:274
	int64_t _15 = 0;
	int64_t _91_x = _15;
// AST_DEFINE
// test/leetcode.orng:275
	int64_t _16 = 0;
	int64_t _91_y = _16;
// AST_DEFINE
// test/leetcode.orng:276
	bool _17 = 0;
	bool _91_diagnolizing = _17;
// AST_FOR
// test/leetcode.orng:293
	int64_t _18 = 0;
	int64_t _97_i = _18;
begin_98:;
	int64_t _19 = _97_i;
	struct struct_1 _20 = _s;
	int64_t _21 = _20.length;
	bool _22 = _19 < _21;
	if (!_22) goto end_98;
// AST_ASSIGN
// test/leetcode.orng:278
	int64_t _23 = _97_i;
	struct struct_1 _24 = _s;
	int8_t _25 = _24.data[_23];
	int64_t _26 = _91_y;
	int64_t _27 = _91_x;
	_91_board.data[_27].data[_26] = _25;
// AST_IF
// test/leetcode.orng:292
	bool _28 = _91_diagnolizing;
	if (!_28) goto else_99;
// AST_SUB_ASSIGN
// test/leetcode.orng:280
	int64_t _29 = 1;
	_91_y -= _29;
// AST_ADD_ASSIGN
// test/leetcode.orng:281
	int64_t _30 = 1;
	_91_x += _30;
// AST_IF
// test/leetcode.orng:284
	int64_t _31 = _91_y;
	int64_t _32 = 0;
	bool _33 = _31 == _32;
	if (!_33) goto else_100;
	bool _34 = 0;
// AST_ASSIGN
// test/leetcode.orng:283
	bool _35 = 0;
	_91_diagnolizing = _35;
	_34 = _35;
	goto end_100;
else_100:;
end_100:;
	goto end_99;
else_99:;
// AST_ADD_ASSIGN
// test/leetcode.orng:286
	int64_t _36 = 1;
	_91_y += _36;
// AST_IF
// test/leetcode.orng:291
	int64_t _37 = _91_y;
	int64_t _38 = _numRows;
	bool _39 = _37 == _38;
	if (!_39) goto else_102;
	int64_t _40 = 0;
// AST_ASSIGN
// test/leetcode.orng:288
	bool _41 = 1;
	_91_diagnolizing = _41;
// AST_SUB_ASSIGN
// test/leetcode.orng:289
	int64_t _42 = 2;
	_91_y -= _42;
// AST_ADD_ASSIGN
// test/leetcode.orng:290
	int64_t _43 = 1;
	_91_x += _43;
	_40 = _43;
	goto end_102;
else_102:;
end_102:;
end_99:;
	// for post
	int64_t _44 = 1;
	_97_i += _44;
	goto begin_98;
end_98:;
// AST_DEFINE
// test/leetcode.orng:295
	struct struct_1 _45 = _s;
	int64_t _46 = _45.length;
	struct struct_1 _47 = {_46, malloc(sizeof(int8_t) * _46)};
	_47.length = _46;
	for(int i = 0; i < _46; i++) {_47.data[i] = 0;}
	struct struct_1 _91_retval = _47;
// AST_DEFINE
// test/leetcode.orng:296
	int64_t _48 = 0;
	int64_t _91_k = _48;
// AST_FOR
// test/leetcode.orng:304
	int64_t _49 = 0;
	int64_t _103_j = _49;
begin_104:;
	int64_t _50 = _103_j;
	int64_t _51 = _numRows;
	bool _52 = _50 < _51;
	if (!_52) goto end_104;
// AST_FOR
// test/leetcode.orng:303
	int64_t _53 = 0;
	int64_t _105_i = _53;
begin_106:;
	int64_t _54 = _105_i;
	struct struct_1 _55 = _s;
	int64_t _56 = _55.length;
	bool _57 = _54 < _56;
	if (!_57) goto end_106;
// AST_IF
// test/leetcode.orng:302
	int64_t _58 = _103_j;
	int64_t _59 = _105_i;
	struct struct_2 _60 = _91_board;
	struct struct_1 _61 = _60.data[_59];
	int8_t _62 = _61.data[_58];
	int8_t _63 = '\0';
	bool _64 = _62 != _63;
	if (!_64) goto else_107;
	int64_t _65 = 0;
// AST_ASSIGN
// test/leetcode.orng:300
	int64_t _66 = _103_j;
	int64_t _67 = _105_i;
	struct struct_2 _68 = _91_board;
	struct struct_1 _69 = _68.data[_67];
	int8_t _70 = _69.data[_66];
	int64_t _71 = _91_k;
	_91_retval.data[_71] = _70;
// AST_ADD_ASSIGN
// test/leetcode.orng:301
	int64_t _72 = 1;
	_91_k += _72;
	_65 = _72;
	goto end_107;
else_107:;
end_107:;
	// for post
	int64_t _73 = 1;
	_105_i += _73;
	goto begin_106;
end_106:;
	// for post
	int64_t _74 = 1;
	_103_j += _74;
	goto begin_104;
end_104:;
// AST_IDENT
// test/leetcode.orng:306
	struct struct_1 _75 = _91_retval;
	_0 = _75;
	retval = _0;
return_block_91:;
	if (defer_0) {
// AST_FOR
// test/leetcode.orng:270
	int64_t _76 = 0;
	int64_t _95_i = _76;
begin_96:;
	int64_t _77 = _95_i;
	struct struct_1 _78 = _s;
	int64_t _79 = _78.length;
	bool _80 = _77 < _79;
	if (!_80) goto end_96;
// AST_FREE
// test/leetcode.orng:269
	int64_t _81 = _95_i;
	struct struct_2 _82 = _91_board;
	struct struct_1 _83 = _82.data[_81];
	free(_83.data);
	// for post
	int64_t _84 = 1;
	_95_i += _84;
	goto begin_96;
end_96:;
// AST_FREE
// test/leetcode.orng:271
	struct struct_2 _85 = _91_board;
	free(_85.data);
	}
	return retval;
}

void test_leetcode_test_reverse()
{
	int64_t _0 = 0;
// AST_DEFINE
// test/leetcode.orng:340
	int64_t _1 = 123;
	int64_t _2 = test_leetcode_reverse(_1);
	int64_t _114_ans = _2;
// AST_IF
// test/leetcode.orng:346
	int64_t _3 = 0;
	int64_t _4 = _114_ans;
	int64_t _5 = 321;
	bool _6 = _4 == _5;
	if (!_6) goto else_115;
	int64_t _7 = 0;
// AST_CALL
// test/leetcode.orng:343
	struct struct_1 _8 = string_29;
	int64_t _9 = std_system_println(_8);
	_7 = _9;
	_3 = _7;
	goto end_115;
else_115:;
	int64_t _10 = 0;
// AST_CALL
// test/leetcode.orng:345
	struct struct_1 _11 = string_30;
	int64_t _12 = std_system_println(_11);
	_10 = _12;
	_3 = _10;
end_115:;
	_0 = _3;
return_block_114:;
}

int64_t test_leetcode_reverse(int64_t _x)
{
	int64_t retval;
	struct struct_6* _0 = test_leetcode_convertToList(_x);
	struct struct_6* _1 = test_leetcode_reverseList(_0);
	struct struct_7 _2 = ((struct struct_7){0});
	_2.tag = 1;
	_2.something = _1;
	int64_t _3 = test_leetcode_convertToInt(_2);
	retval = _3;
return_block_:;
	return retval;
}

struct struct_6* test_leetcode_reverseList(struct struct_6* _list)
{
	struct struct_6* retval;
	struct struct_6* _0 = 0;
// AST_DEFINE
// test/leetcode.orng:325
	struct struct_6* _111_newList = 0;
// AST_DEFINE
// test/leetcode.orng:326
	struct struct_6* _1 = _list;
	struct struct_7 _2 = _1->next;
	struct struct_7 _111_next = _2;
// AST_IF
// test/leetcode.orng:332
	struct struct_7 _3 = _111_next;
	bool _4 = _3.tag == 0;
	if (!_4) goto else_112;
	struct struct_6* _5 = 0;
// AST_RETURN
// test/leetcode.orng:328
	struct struct_6* _6 = _list;
	retval = _6;
	goto return_block_111;
	_5 = _6;
	goto end_112;
else_112:;
	struct struct_7 _7 = ((struct struct_7){0});
// AST_ASSIGN
// test/leetcode.orng:330
	struct struct_7 _8 = _111_next;
	struct struct_6* _9 = _8.something;
	struct struct_6* _10 = test_leetcode_reverseList(_9);
	_111_newList = _10;
// AST_ASSIGN
// test/leetcode.orng:331
	struct struct_6* _11 = _list;
	struct struct_7 _12 = ((struct struct_7){0});
	_12.tag = 1;
	_12.something = _11;
	_111_next.something->next = _12;
	_7 = _12;
end_112:;
// AST_ASSIGN
// test/leetcode.orng:333
	int64_t _13 = 0;
	struct struct_7 _14 = ((struct struct_7){0});
	_14.tag = 0;
	_list->next = _14;
// AST_RETURN
// test/leetcode.orng:334
	struct struct_6* _15 = _111_newList;
	retval = _15;
	goto return_block_111;
	_0 = _15;
	retval = _0;
return_block_111:;
	return retval;
}

void test_leetcode_test_myAtoi()
{
	int64_t _0 = 0;
// AST_DEFINE
// test/leetcode.orng:381
	struct struct_1 _1 = string_31;
	struct struct_1 _127_s = _1;
// AST_DEFINE
// test/leetcode.orng:383
	int64_t _2 = test_leetcode_myAtoi(_127_s);
	int64_t _127_ans = _2;
// AST_IF
// test/leetcode.orng:389
	int64_t _3 = 0;
	int64_t _4 = _127_ans;
	int64_t _5 = 42;
	bool _6 = _4 == _5;
	if (!_6) goto else_128;
	int64_t _7 = 0;
// AST_CALL
// test/leetcode.orng:386
	struct struct_1 _8 = string_32;
	int64_t _9 = std_system_println(_8);
	_7 = _9;
	_3 = _7;
	goto end_128;
else_128:;
	int64_t _10 = 0;
// AST_CALL
// test/leetcode.orng:388
	struct struct_1 _11 = string_33;
	int64_t _12 = std_system_println(_11);
	_10 = _12;
	_3 = _10;
end_128:;
	_0 = _3;
return_block_127:;
}

int64_t test_leetcode_myAtoi(struct struct_1 _s)
{
	int64_t retval;
	int64_t _0 = 0;
// AST_DEFINE
// test/leetcode.orng:354
	int64_t _1 = 0;
	int64_t _117_x = _1;
// AST_DEFINE
// test/leetcode.orng:355
	int64_t _2 = 0;
	int64_t _117_i = _2;
// AST_DEFINE
// test/leetcode.orng:356
	bool _3 = 1;
	bool _117_sign = _3;
// AST_FOR
// test/leetcode.orng:359
	int64_t _4 = 0;
begin_119:;
	bool _5 = 0;
	int64_t _6 = _117_i;
	struct struct_1 _7 = _s;
	int64_t _8 = _7.length;
	bool _9 = _6 < _8;
	if (!_9) goto over_0;
	int64_t _10 = _117_i;
	struct struct_1 _11 = _s;
	int8_t _12 = _11.data[_10];
	int8_t _13 = ' ';
	bool _14 = _12 == _13;
	_5 = _14;
over_0:;
	if (!_5) goto end_119;
	int64_t _15 = 0;
// AST_ADD_ASSIGN
// test/leetcode.orng:359
	int64_t _16 = 1;
	_117_i += _16;
	_15 = _16;
	_4 = _15;
	// for post
	goto begin_119;
	_4 = _15;
end_119:;
// AST_IF
// test/leetcode.orng:370
	int64_t _17 = _117_i;
	struct struct_1 _18 = _s;
	int64_t _19 = _18.length;
	bool _20 = _17 == _19;
	if (!_20) goto else_120;
	int64_t _21 = 0;
// AST_RETURN
// test/leetcode.orng:363
	int64_t _22 = 0;
	retval = _22;
	goto return_block_117;
	_21 = _22;
	goto end_120;
else_120:;
	int64_t _23 = _117_i;
	struct struct_1 _24 = _s;
	int8_t _25 = _24.data[_23];
	int8_t _26 = '+';
	bool _27 = _25 == _26;
	if (!_27) goto else_121;
	int64_t _28 = 0;
// AST_ASSIGN
// test/leetcode.orng:365
	bool _29 = 1;
	_117_sign = _29;
// AST_ADD_ASSIGN
// test/leetcode.orng:366
	int64_t _30 = 1;
	_117_i += _30;
	_28 = _30;
	goto end_121;
else_121:;
	int64_t _31 = _117_i;
	struct struct_1 _32 = _s;
	int8_t _33 = _32.data[_31];
	int8_t _34 = '-';
	bool _35 = _33 == _34;
	if (!_35) goto else_122;
	int64_t _36 = 0;
// AST_ASSIGN
// test/leetcode.orng:368
	bool _37 = 0;
	_117_sign = _37;
// AST_ADD_ASSIGN
// test/leetcode.orng:369
	int64_t _38 = 1;
	_117_i += _38;
	_36 = _38;
	goto end_122;
else_122:;
end_122:;
end_121:;
end_120:;
// AST_FOR
// test/leetcode.orng:375
	int64_t _39 = 0;
begin_124:;
	bool _40 = 0;
	int64_t _41 = _117_i;
	struct struct_1 _42 = _s;
	int64_t _43 = _42.length;
	bool _44 = _41 < _43;
	if (!_44) goto over_1;
	int64_t _45 = _117_i;
	struct struct_1 _46 = _s;
	int8_t _47 = _46.data[_45];
	bool _48 = isdigit(_47);
	_40 = _48;
over_1:;
	if (!_40) goto end_124;
	int64_t _49 = 0;
// AST_ASSIGN
// test/leetcode.orng:374
	int64_t _50 = _117_x;
	int64_t _51 = 10;
	int64_t _52 = _50 * _51;
	int64_t _53 = _117_i;
	struct struct_1 _54 = _s;
	int8_t _55 = _54.data[_53];
	int64_t _56 = (int64_t)_55;
	int64_t _57 = _52 + _56;
	int8_t _58 = '0';
	int64_t _59 = (int64_t)_58;
	int64_t _60 = _57 - _59;
	_117_x = _60;
	_49 = _60;
	_39 = _49;
	// for post
	int64_t _61 = 1;
	_117_i += _61;
	goto begin_124;
	_39 = _49;
end_124:;
// AST_IF
// test/leetcode.orng:377
	int64_t _62 = 0;
	bool _63 = _117_sign;
	if (!_63) goto else_125;
	int64_t _64 = 0;
// AST_IDENT
// test/leetcode.orng:377
	int64_t _65 = _117_x;
	_64 = _65;
	_62 = _64;
	goto end_125;
else_125:;
	int64_t _66 = 0;
// AST_NEG
// test/leetcode.orng:377
	int64_t _67 = _117_x;
	int64_t _68 = -_67;
	_66 = _68;
	_62 = _66;
end_125:;
	_0 = _62;
	retval = _0;
return_block_117:;
	return retval;
}

void test_leetcode_test_isPalindrome()
{
	int64_t _0 = 0;
// AST_DEFINE
// test/leetcode.orng:412
	int64_t _1 = 121;
	int64_t _135_x = _1;
// AST_DEFINE
// test/leetcode.orng:414
	bool _2 = test_leetcode_isPalindrome(_135_x);
	bool _135_ans = _2;
// AST_IF
// test/leetcode.orng:420
	int64_t _3 = 0;
	bool _4 = _135_ans;
	if (!_4) goto else_136;
	int64_t _5 = 0;
// AST_CALL
// test/leetcode.orng:417
	struct struct_1 _6 = string_34;
	int64_t _7 = std_system_println(_6);
	_5 = _7;
	_3 = _5;
	goto end_136;
else_136:;
	int64_t _8 = 0;
// AST_CALL
// test/leetcode.orng:419
	struct struct_1 _9 = string_35;
	int64_t _10 = std_system_println(_9);
	_8 = _10;
	_3 = _8;
end_136:;
	_0 = _3;
return_block_135:;
}

bool test_leetcode_isPalindrome(int64_t _x)
{
	bool retval;
	bool _0 = 0;
// AST_DEFINE
// test/leetcode.orng:396
	struct struct_6* _1 = test_leetcode_convertToList(_x);
	struct struct_6* _130_list = _1;
// AST_DEFINE
// test/leetcode.orng:397
	struct struct_6* _2 = test_leetcode_convertToList(_x);
	struct struct_6* _3 = test_leetcode_reverseList(_2);
	struct struct_6* _130_reversedList = _3;
// AST_FOR
// test/leetcode.orng:407
begin_132:;
	bool _4 = 1;
	if (!_4) goto end_132;
// AST_IF
// test/leetcode.orng:406
	struct struct_6* _5 = _130_list;
	int64_t _6 = _5->val;
	struct struct_6* _7 = _130_reversedList;
	int64_t _8 = _7->val;
	bool _9 = _6 != _8;
	if (!_9) goto else_133;
	bool _10 = 0;
// AST_RETURN
// test/leetcode.orng:402
	bool _11 = 0;
	retval = _11;
	goto return_block_130;
	_10 = _11;
	goto end_133;
else_133:;
	struct struct_6* _12 = 0;
// AST_ASSIGN
// test/leetcode.orng:404
	struct struct_6* _13 = 0;
	struct struct_6* _14 = _130_list;
	struct struct_7 _15 = _14->next;
	if (_15.tag == 0) goto else_0;
	_13 = _15.something;
	goto end_1;
else_0:;
	goto end_132;
end_1:;
	_130_list = _13;
// AST_ASSIGN
// test/leetcode.orng:405
	struct struct_6* _16 = 0;
	struct struct_6* _17 = _130_reversedList;
	struct struct_7 _18 = _17->next;
	if (_18.tag == 0) goto else_2;
	_16 = _18.something;
	goto end_3;
else_2:;
	goto end_132;
end_3:;
	_130_reversedList = _16;
	_12 = _16;
end_133:;
	// for post
	goto begin_132;
end_132:;
// AST_RETURN
// test/leetcode.orng:408
	bool _19 = 1;
	retval = _19;
	goto return_block_130;
	_0 = _19;
	retval = _0;
return_block_130:;
	return retval;
}

void test_leetcode_test_isMatch()
{
	int64_t _0 = 0;
// AST_DEFINE
// test/leetcode.orng:453
	struct struct_1 _1 = string_36;
	struct struct_1 _148_s = _1;
// AST_DEFINE
// test/leetcode.orng:454
	struct struct_1 _2 = string_37;
	struct struct_1 _148_p = _2;
// AST_DEFINE
// test/leetcode.orng:456
	bool _3 = test_leetcode_isMatch(_148_s, _148_p);
	bool _148_ans = _3;
// AST_IF
// test/leetcode.orng:462
	int64_t _4 = 0;
	bool _5 = _148_ans;
	if (!_5) goto else_149;
	int64_t _6 = 0;
// AST_CALL
// test/leetcode.orng:459
	struct struct_1 _7 = string_38;
	int64_t _8 = std_system_println(_7);
	_6 = _8;
	_4 = _6;
	goto end_149;
else_149:;
	int64_t _9 = 0;
// AST_CALL
// test/leetcode.orng:461
	struct struct_1 _10 = string_39;
	int64_t _11 = std_system_println(_10);
	_9 = _11;
	_4 = _9;
end_149:;
	_0 = _4;
return_block_148:;
}

bool test_leetcode_isMatch(struct struct_1 _s, struct struct_1 _p)
{
	bool retval;
	bool _0 = 0;
// AST_DEFINE
// test/leetcode.orng:430
	int64_t _1 = 0;
	int64_t _138_i = _1;
// AST_DEFINE
// test/leetcode.orng:431
	int64_t _2 = 0;
	int64_t _138_j = _2;
// AST_FOR
// test/leetcode.orng:448
begin_140:;
	int64_t _3 = _138_i;
	struct struct_1 _4 = _s;
	int64_t _5 = _4.length;
	bool _6 = _3 < _5;
	if (!_6) goto end_140;
// AST_DEFINE
// test/leetcode.orng:434
	bool _7 = 0;
	int64_t _8 = _138_j;
	int64_t _9 = 1;
	int64_t _10 = _8 + _9;
	struct struct_1 _11 = _p;
	int64_t _12 = _11.length;
	bool _13 = _10 == _12;
	if (!_13) goto else_141;
	bool _14 = 0;
// AST_FALSE
// test/leetcode.orng:434
	bool _15 = 0;
	_14 = _15;
	_7 = _14;
	goto end_141;
else_141:;
	bool _16 = 0;
// AST_EQ
// test/leetcode.orng:434
	int64_t _17 = _138_j;
	int64_t _18 = 1;
	int64_t _19 = _17 + _18;
	struct struct_1 _20 = _p;
	int8_t _21 = _20.data[_19];
	int8_t _22 = '*';
	bool _23 = _21 == _22;
	_16 = _23;
	_7 = _16;
end_141:;
	bool _140_repeat = _7;
// AST_IF
// test/leetcode.orng:447
	bool _24 = 0;
	int64_t _25 = _138_j;
	struct struct_1 _26 = _p;
	int8_t _27 = _26.data[_25];
	int8_t _28 = '.';
	bool _29 = _27 != _28;
	if (!_29) goto over_0;
	int64_t _30 = _138_i;
	struct struct_1 _31 = _s;
	int8_t _32 = _31.data[_30];
	int64_t _33 = _138_j;
	struct struct_1 _34 = _p;
	int8_t _35 = _34.data[_33];
	bool _36 = _32 != _35;
	_24 = _36;
over_0:;
	if (!_24) goto else_143;
// AST_IF
// test/leetcode.orng:441
	bool _37 = _140_repeat;
	if (!_37) goto else_144;
	int64_t _38 = 0;
// AST_ADD_ASSIGN
// test/leetcode.orng:438
	int64_t _39 = 1;
	_138_j += _39;
	_38 = _39;
	goto end_144;
else_144:;
	bool _40 = 0;
// AST_RETURN
// test/leetcode.orng:440
	bool _41 = 0;
	retval = _41;
	goto return_block_138;
	_40 = _41;
end_144:;
	goto end_143;
else_143:;
// AST_ADD_ASSIGN
// test/leetcode.orng:443
	int64_t _42 = 1;
	_138_i += _42;
// AST_IF
// test/leetcode.orng:446
	bool _43 = _140_repeat;
	bool _44 = !_43;
	if (!_44) goto else_147;
	int64_t _45 = 0;
// AST_ADD_ASSIGN
// test/leetcode.orng:445
	int64_t _46 = 1;
	_138_j += _46;
	_45 = _46;
	goto end_147;
else_147:;
end_147:;
end_143:;
	// for post
	goto begin_140;
end_140:;
// AST_TRUE
// test/leetcode.orng:449
	bool _47 = 1;
	_0 = _47;
	retval = _0;
return_block_138:;
	return retval;
}

void test_leetcode_test_maxArea()
{
	int64_t _0 = 0;
// AST_DEFINE
// test/leetcode.orng:480
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
	struct struct_3 _155_height = _10;
// AST_DEFINE
// test/leetcode.orng:482
	int64_t _11 = 0;
	int64_t _12 = test_leetcode_maxArea(_155_height, _11);
	int64_t _155_ans = _12;
// AST_IF
// test/leetcode.orng:488
	int64_t _13 = 0;
	int64_t _14 = _155_ans;
	int64_t _15 = 49;
	bool _16 = _14 == _15;
	if (!_16) goto else_156;
	int64_t _17 = 0;
// AST_CALL
// test/leetcode.orng:485
	struct struct_1 _18 = string_40;
	int64_t _19 = std_system_println(_18);
	_17 = _19;
	_13 = _17;
	goto end_156;
else_156:;
	int64_t _20 = 0;
// AST_CALL
// test/leetcode.orng:487
	struct struct_1 _21 = string_41;
	int64_t _22 = std_system_println(_21, _155_ans);
	_20 = _22;
	_13 = _20;
end_156:;
	_0 = _13;
return_block_155:;
}

int64_t test_leetcode_maxArea(struct struct_3 _height, int64_t _max)
{
	int64_t retval;
	int64_t _0 = 0;
	int64_t _1 = 0;
	int64_t _151_i = _1;
begin_152:;
	int64_t _2 = _151_i;
	struct struct_3 _3 = _height;
	int64_t _4 = _3.length;
	int64_t _5 = 1;
	int64_t _6 = _4 - _5;
	bool _7 = _2 < _6;
	if (!_7) goto end_152;
	int64_t _8 = 0;
// AST_FOR
// test/leetcode.orng:476
	int64_t _9 = 0;
	int64_t _10 = _151_i;
	int64_t _11 = 1;
	int64_t _12 = _10 + _11;
	int64_t _153_j = _12;
begin_154:;
	int64_t _13 = _153_j;
	struct struct_3 _14 = _height;
	int64_t _15 = _14.length;
	bool _16 = _13 < _15;
	if (!_16) goto end_154;
	int64_t _17 = 0;
// AST_ASSIGN
// test/leetcode.orng:475
	int64_t _18 = _151_i;
	int64_t _19 = _153_j;
	int64_t _20 = _18 - _19;
	int64_t _21 = std_math_abs(_20);
	int64_t _22 = _151_i;
	struct struct_3 _23 = _height;
	int64_t _24 = _23.data[_22];
	int64_t _25 = _153_j;
	struct struct_3 _26 = _height;
	int64_t _27 = _26.data[_25];
	double _28 = std_math_min(_24, _27);
	double _29 = _21 * _28;
	double _30 = std_math_max(_max, _29);
	int64_t _31 = (int64_t)_30;
	_max = _31;
	_17 = _31;
	_9 = _17;
	// for post
	int64_t _32 = 1;
	_153_j += _32;
	goto begin_154;
	_9 = _17;
end_154:;
	_8 = _9;
	_0 = _8;
	// for post
	int64_t _33 = 1;
	_151_i += _33;
	goto begin_152;
	_0 = _8;
end_152:;
	retval = _0;
return_block_151:;
	return retval;
}

void test_leetcode_fizzbuzz(int64_t _n)
{
	struct struct_1 _0 = ((struct struct_1){0, 0});
	int64_t _1 = _n;
	int64_t _2 = 16;
	int64_t _3 = _1 % _2;
	int64_t _4 = 0;
	bool _5 = _3 == _4;
	if (!_5) goto else_33;
	struct struct_1 _6 = ((struct struct_1){0, 0});
// AST_STRING
// test/leetcode.orng:22
	struct struct_1 _7 = string_42;
	_6 = _7;
	_0 = _6;
	goto end_33;
else_33:;
	struct struct_1 _8 = ((struct struct_1){0, 0});
	int64_t _9 = _n;
	int64_t _10 = 3;
	int64_t _11 = _9 % _10;
	int64_t _12 = 0;
	bool _13 = _11 == _12;
	if (!_13) goto else_34;
	struct struct_1 _14 = ((struct struct_1){0, 0});
// AST_STRING
// test/leetcode.orng:24
	struct struct_1 _15 = string_43;
	_14 = _15;
	_8 = _14;
	goto end_34;
else_34:;
	struct struct_1 _16 = ((struct struct_1){0, 0});
	int64_t _17 = _n;
	int64_t _18 = 5;
	int64_t _19 = _17 % _18;
	int64_t _20 = 0;
	bool _21 = _19 == _20;
	if (!_21) goto else_35;
	struct struct_1 _22 = ((struct struct_1){0, 0});
// AST_STRING
// test/leetcode.orng:26
	struct struct_1 _23 = string_44;
	_22 = _23;
	_16 = _22;
	goto end_35;
else_35:;
	struct struct_1 _24 = ((struct struct_1){0, 0});
// AST_CALL
// test/leetcode.orng:28
	int64_t _25 = 255;
	struct struct_1 _26 = string_45;
	struct struct_1 _27 = std_string_format(_25, _26, _n);
	_24 = _27;
	_16 = _24;
end_35:;
	_8 = _16;
end_34:;
	_0 = _8;
end_33:;
return_block_36:;
}

struct struct_1 test_leetcode_fizzbuzz2(int64_t _n)
{
	struct struct_1 retval;
	struct struct_1 _0 = ((struct struct_1){0, 0});
	int64_t _1 = _n;
	int64_t _2 = 15;
	int64_t _3 = _1 % _2;
	switch (_3) {
	case 0:
	{
	struct struct_1 _4 = string_46;
	_0 = _4;
	break;
	} // end case
	case 3:
	case 6:
	case 9:
	case 12:
	{
	struct struct_1 _5 = string_47;
	_0 = _5;
	break;
	} // end case
	case 5:
	case 10:
	{
	struct struct_1 _6 = string_48;
	_0 = _6;
	break;
	} // end case
	default:
	{
	int64_t _7 = 255;
	struct struct_1 _8 = string_49;
	struct struct_1 _9 = std_string_format(_7, _8, _n);
	_0 = _9;
	break;
	} // end default
	} // end switch
	retval = _0;
return_block_:;
	return retval;
}

int64_t test_leetcode_lengthOfLongestSubstring(struct struct_1 _str)
{
	int64_t retval;
	int64_t _0 = 0;
// AST_DEFINE
// test/leetcode.orng:127
// AST_DEFINE
// test/leetcode.orng:139
	struct struct_1 _1 = _str;
	int64_t _2 = _1.length;
	int64_t _53_n = _2;
// AST_DEFINE
// test/leetcode.orng:140
	int64_t _3 = 0;
	int64_t _53_res = _3;
// AST_FOR
// test/leetcode.orng:150
	int64_t _4 = 0;
	int64_t _58_i = _4;
begin_59:;
	int64_t _5 = _58_i;
	int64_t _6 = _53_n;
	bool _7 = _5 < _6;
	if (!_7) goto end_59;
// AST_FOR
// test/leetcode.orng:149
	int64_t _8 = _58_i;
	int64_t _60_j = _8;
begin_61:;
	int64_t _9 = _60_j;
	int64_t _10 = _53_n;
	bool _11 = _9 < _10;
	if (!_11) goto end_61;
// AST_IF
// test/leetcode.orng:148
	bool _12 = test_leetcode_areDistinct(_str, _58_i, _60_j);
	if (!_12) goto else_62;
	int64_t _13 = 0;
// AST_ASSIGN
// test/leetcode.orng:147
	int64_t _14 = _60_j;
	int64_t _15 = _58_i;
	int64_t _16 = _14 - _15;
	int64_t _17 = 1;
	int64_t _18 = _16 + _17;
	double _19 = std_math_max(_53_res, _18);
	int64_t _20 = (int64_t)_19;
	_53_res = _20;
	_13 = _20;
	goto end_62;
else_62:;
end_62:;
	// for post
	int64_t _21 = 1;
	_60_j += _21;
	goto begin_61;
end_61:;
	// for post
	int64_t _22 = 1;
	_58_i += _22;
	goto begin_59;
end_59:;
// AST_RETURN
// test/leetcode.orng:152
	int64_t _23 = _53_res;
	retval = _23;
	goto return_block_53;
	_0 = _23;
	retval = _0;
return_block_53:;
	return retval;
}

bool test_leetcode_areDistinct(struct struct_1 _str, int64_t _i, int64_t _j)
{
	bool retval;
	bool _0 = 0;
// AST_DEFINE
// test/leetcode.orng:129
	struct struct_9 _54_visited = ((struct struct_9){256, (bool*[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}});
// AST_FOR
// test/leetcode.orng:136
	bool _1 = 0;
	int64_t _2 = _i;
	int64_t _55_k = _2;
begin_56:;
	int64_t _3 = _55_k;
	int64_t _4 = _j;
	bool _5 = _3 <= _4;
	if (!_5) goto end_56;
	bool _6 = 0;
// AST_DEFINE
// test/leetcode.orng:131
	int64_t _7 = _55_k;
	struct struct_1 _8 = _str;
	int8_t _9 = _8.data[_7];
	int64_t _10 = (int64_t)_9;
	int64_t _56_charCode = _10;
// AST_IF
// test/leetcode.orng:134
	int64_t _11 = _56_charCode;
	struct struct_9 _12 = _54_visited;
	bool _13 = _12.data[_11];
	if (!_13) goto else_57;
	bool _14 = 0;
// AST_RETURN
// test/leetcode.orng:133
	bool _15 = 0;
	retval = _15;
	goto return_block_54;
	_14 = _15;
	goto end_57;
else_57:;
end_57:;
// AST_ASSIGN
// test/leetcode.orng:135
	bool _16 = 1;
	int64_t _17 = _56_charCode;
	_54_visited.data[_17] = _16;
	_6 = _16;
	_1 = _6;
	// for post
	int64_t _18 = 1;
	_55_k += _18;
	goto begin_56;
	_1 = _6;
end_56:;
// AST_RETURN
// test/leetcode.orng:137
	bool _19 = 1;
	retval = _19;
	goto return_block_54;
	_0 = _19;
	retval = _0;
return_block_54:;
	return retval;
}

void test_leetcode_test_lengthOfLongestSubstring()
{
	int64_t _0 = 0;
// AST_DEFINE
// test/leetcode.orng:156
	struct struct_1 _1 = string_50;
	struct struct_1 _63_s = _1;
// AST_DEFINE
// test/leetcode.orng:158
	int64_t _2 = test_leetcode_lengthOfLongestSubstring(_63_s);
	int64_t _63_ans = _2;
// AST_IF
// test/leetcode.orng:164
	int64_t _3 = 0;
	int64_t _4 = _63_ans;
	int64_t _5 = 3;
	bool _6 = _4 == _5;
	if (!_6) goto else_64;
	int64_t _7 = 0;
// AST_CALL
// test/leetcode.orng:161
	struct struct_1 _8 = string_51;
	int64_t _9 = std_system_println(_8);
	_7 = _9;
	_3 = _7;
	goto end_64;
else_64:;
	int64_t _10 = 0;
// AST_CALL
// test/leetcode.orng:163
	struct struct_1 _11 = string_52;
	int64_t _12 = std_system_println(_11, _63_ans);
	_10 = _12;
	_3 = _10;
end_64:;
	_0 = _3;
return_block_63:;
}

int64_t test_testModule_main(struct struct_2 _args)
{
	int64_t retval;
	int64_t _0 = 0;
// AST_CALL
// test/testModule.orng:3
	test_leetcode_test_all();
// AST_INT
// test/testModule.orng:4
	int64_t _1 = 0;
	_0 = _1;
	retval = _0;
return_block_158:;
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
	system("pause");
	return retval;
}
#endif
