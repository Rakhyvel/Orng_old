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
	int64_t length;
	int64_t* data;
};

struct struct_5 {
	int64_t length;
	int8_t* data;
};

struct struct_6 {
	int64_t val;
	struct struct_6* next;
};

struct struct_7 {
	int64_t length;
	int64_t* data;
};

struct struct_8 {
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
int8_t* std_string_itoa(int64_t _int);
struct struct_1 std_string_format(int64_t _n, struct struct_1 _f, ...);
void test_leetcode_test_addTwoNumbers();
struct struct_6* test_leetcode_addTwoNumbers(struct struct_6* _l1, struct struct_6* _l2);
struct struct_6* test_leetcode_convertToList(int64_t _i);
int64_t test_leetcode_convertToInt(struct struct_6* _l);
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

#ifndef ORANGE_PROGRAM_1461
#define ORANGE_PROGRAM_1461

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
struct struct_1 string_15 = {14, (char[]){'t', 'w', 'o', 'S', 'u', 'm', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
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
struct struct_1 string_40 = {2, (char[]){'%', 'd', '\0'}};
struct struct_1 string_41 = {16, (char[]){'m', 'a', 'x', 'A', 'r', 'e', 'a', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_42 = {18, (char[]){'m', 'a', 'x', 'A', 'r', 'e', 'a', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', ' ', '%', 'd', '\0'}};
struct struct_1 string_43 = {8, (char[]){'f', 'i', 'z', 'z', 'b', 'u', 'z', 'z', '\0'}};
struct struct_1 string_44 = {4, (char[]){'f', 'i', 'z', 'z', '\0'}};
struct struct_1 string_45 = {4, (char[]){'b', 'u', 'z', 'z', '\0'}};
struct struct_1 string_46 = {2, (char[]){'%', 'd', '\0'}};
struct struct_1 string_47 = {8, (char[]){'f', 'i', 'z', 'z', 'b', 'u', 'z', 'z', '\0'}};
struct struct_1 string_48 = {4, (char[]){'f', 'i', 'z', 'z', '\0'}};
struct struct_1 string_49 = {4, (char[]){'b', 'u', 'z', 'z', '\0'}};
struct struct_1 string_50 = {2, (char[]){'%', 'd', '\0'}};
struct struct_1 string_51 = {8, (char[]){'a', 'b', 'c', 'a', 'b', 'c', 'b', 'b', '\0'}};
struct struct_1 string_52 = {33, (char[]){'l', 'e', 'n', 'g', 't', 'h', 'O', 'f', 'L', 'o', 'n', 'g', 'e', 's', 't', 'S', 'u', 'b', 's', 't', 'r', 'i', 'n', 'g', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_53 = {35, (char[]){'l', 'e', 'n', 'g', 't', 'h', 'O', 'f', 'L', 'o', 'n', 'g', 'e', 's', 't', 'S', 'u', 'b', 's', 't', 'r', 'i', 'n', 'g', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', ' ', '%', 'd', '\0'}};

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
return_block_35:;
}

void test_leetcode_test_twoSum()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:58
	int64_t* _1 = 2;
	int64_t* _2 = 7;
	int64_t* _3 = 11;
	int64_t* _4 = 15;
	struct struct_3 _5 = {4, (int64_t*[]){_1, _2, _3, _4}};
	struct struct_3 _46_nums = _5;
// AST_DEFINE
// test/leetcode.orng:59
	int64_t _6 = 9;
	int64_t _46_target = _6;
// AST_DEFINE
// test/leetcode.orng:61
	struct struct_3 _7 = test_leetcode_twoSum(_46_nums, _46_target);
	struct struct_3 _46_ans = _7;
// AST_IF
// test/leetcode.orng:67
	int64_t _8;
	int64_t _9 = 0;
	struct struct_3 _10 = _46_ans;
	int64_t _11 = _10.data[_9];
	struct struct_3 _12 = _46_nums;
	int64_t _13 = _12.data[_11];
	int64_t _14 = 1;
	struct struct_3 _15 = _46_ans;
	int64_t _16 = _15.data[_14];
	struct struct_3 _17 = _46_nums;
	int64_t _18 = _17.data[_16];
	int64_t _19 = _13 + _18;
	int64_t _20 = _46_target;
	bool _21 = _19 == _20;
	if (!_21) goto else_47;
	int64_t _22;
// AST_CALL
// test/leetcode.orng:64
	struct struct_1 _23 = string_14;
	int64_t _24 = std_system_println(_23);
	_22 = _24;
	_8 = _22;
	goto end_47;
else_47:;
	int64_t _25;
// AST_CALL
// test/leetcode.orng:66
	struct struct_1 _26 = string_15;
	int64_t _27 = std_system_println(_26);
	_25 = _27;
	_8 = _25;
end_47:;
	_0 = _8;
return_block_46:;
}

struct struct_3 test_leetcode_twoSum(struct struct_3 _nums, int64_t _target)
{
	struct struct_3 retval;
	struct struct_3 _0;
// AST_FOR
// test/leetcode.orng:53
	int64_t _1 = 0;
	int64_t _41_i = _1;
begin_42:;
	int64_t _2 = _41_i;
	struct struct_3 _3 = _nums;
	int64_t _4 = _3.length;
	int64_t _5 = 1;
	int64_t _6 = _4 - _5;
	bool _7 = _2 < _6;
	if (!_7) goto end_42;
// AST_FOR
// test/leetcode.orng:52
	int64_t _8 = _41_i;
	int64_t _9 = 1;
	int64_t _10 = _8 + _9;
	int64_t _43_j = _10;
begin_44:;
	int64_t _11 = _43_j;
	struct struct_3 _12 = _nums;
	int64_t _13 = _12.length;
	bool _14 = _11 < _13;
	if (!_14) goto end_44;
// AST_IF
// test/leetcode.orng:51
	int64_t _15 = _41_i;
	struct struct_3 _16 = _nums;
	int64_t _17 = _16.data[_15];
	int64_t _18 = _43_j;
	struct struct_3 _19 = _nums;
	int64_t _20 = _19.data[_18];
	int64_t _21 = _17 + _20;
	int64_t _22 = _target;
	bool _23 = _21 == _22;
	if (!_23) goto else_45;
	struct struct_3 _24;
// AST_RETURN
// test/leetcode.orng:50
	int64_t _25 = _41_i;
	int64_t _26 = _43_j;
	struct struct_3 _27 = {2, (int64_t[]){_25, _26}};
	int64_t _28 = 2;
	struct struct_3 _29 = {_28, malloc(sizeof(int64_t) * _28)};
	_29.length = _28;
	for(int i = 0; i < _28; i++) {_29.data[i] = _27.data[i];}
	retval = _29;
	goto return_block_40;
	_24 = _29;
	goto end_45;
else_45:;
end_45:;
	// for post
	int64_t _30 = 1;
	_43_j += _30;
	goto begin_44;
end_44:;
	// for post
	int64_t _31 = 1;
	_41_i += _31;
	goto begin_42;
end_42:;
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
	goto return_block_40;
	_0 = _36;
	retval = _0;
return_block_40:;
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

int8_t* std_string_itoa(int64_t _int)
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
	_int *= _2;
// AST_FOR
// std/string.orng:60
	int8_t _3;
begin_27:;
	bool _4 = 0;
	int64_t _5 = _int;
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
	_int /= _12;
// AST_ASSIGN
// std/string.orng:59
	int64_t _13 = _int;
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

void test_leetcode_test_addTwoNumbers()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:99
	int64_t _1 = 3;
	int64_t _2 = 0;
	struct struct_6 _3 = {_1, _2};
	struct struct_6* _4 = calloc(sizeof(struct struct_6), 1);
	*_4 = _3;
	struct struct_6* _53_l1_c = _4;
// AST_DEFINE
// test/leetcode.orng:100
	int64_t _5 = 4;
	struct struct_6* _6 = _53_l1_c;
	struct struct_6 _7 = {_5, _6};
	struct struct_6* _8 = calloc(sizeof(struct struct_6), 1);
	*_8 = _7;
	struct struct_6* _53_l1_b = _8;
// AST_DEFINE
// test/leetcode.orng:101
	int64_t _9 = 2;
	struct struct_6* _10 = _53_l1_b;
	struct struct_6 _11 = {_9, _10};
	struct struct_6* _12 = calloc(sizeof(struct struct_6), 1);
	*_12 = _11;
	struct struct_6* _53_l1 = _12;
// AST_DEFINE
// test/leetcode.orng:102
	int64_t _13 = 4;
	int64_t _14 = 0;
	struct struct_6 _15 = {_13, _14};
	struct struct_6* _16 = calloc(sizeof(struct struct_6), 1);
	*_16 = _15;
	struct struct_6* _53_l2_c = _16;
// AST_DEFINE
// test/leetcode.orng:103
	int64_t _17 = 6;
	struct struct_6* _18 = _53_l2_c;
	struct struct_6 _19 = {_17, _18};
	struct struct_6* _20 = calloc(sizeof(struct struct_6), 1);
	*_20 = _19;
	struct struct_6* _53_l2_b = _20;
// AST_DEFINE
// test/leetcode.orng:104
	int64_t _21 = 5;
	struct struct_6* _22 = _53_l2_b;
	struct struct_6 _23 = {_21, _22};
	struct struct_6* _24 = calloc(sizeof(struct struct_6), 1);
	*_24 = _23;
	struct struct_6* _53_l2 = _24;
// AST_DEFINE
// test/leetcode.orng:106
	struct struct_6* _25 = test_leetcode_addTwoNumbers(_53_l1, _53_l2);
	struct struct_6* _53_ans = _25;
// AST_IF
// test/leetcode.orng:112
	int64_t _26;
	bool _27 = 0;
	bool _28 = 0;
	struct struct_6* _29 = _53_ans;
	int64_t _30 = _29->val;
	int64_t _31 = 7;
	bool _32 = _30 == _31;
	if (!_32) goto over_1;
	struct struct_6* _33 = _53_ans;
	struct struct_6* _34 = _33->next;
	int64_t _35 = _34->val;
	int64_t _36 = 0;
	bool _37 = _35 == _36;
	_28 = _37;
over_1:;
	if (!_28) goto over_0;
	struct struct_6* _38 = _53_ans;
	struct struct_6* _39 = _38->next;
	struct struct_6* _40 = _39->next;
	int64_t _41 = _40->val;
	int64_t _42 = 8;
	bool _43 = _41 == _42;
	_27 = _43;
over_0:;
	if (!_27) goto else_54;
	int64_t _44;
// AST_CALL
// test/leetcode.orng:109
	struct struct_1 _45 = string_16;
	int64_t _46 = std_system_println(_45);
	_44 = _46;
	_26 = _44;
	goto end_54;
else_54:;
	int64_t _47;
// AST_CALL
// test/leetcode.orng:111
	struct struct_1 _48 = string_17;
	int64_t _49 = std_system_println(_48);
	_47 = _49;
	_26 = _47;
end_54:;
	_0 = _26;
return_block_53:;
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

struct struct_6* test_leetcode_convertToList(int64_t _i)
{
	struct struct_6* retval;
	struct struct_6* _0;
	int64_t _1 = _i;
	int64_t _2 = 10;
	bool _3 = _1 < _2;
	if (!_3) goto else_51;
	struct struct_6* _4;
// AST_NEW
// test/leetcode.orng:90
	int64_t _5 = _i;
	int64_t _6 = 0;
	struct struct_6 _7 = {_5, _6};
	struct struct_6* _8 = calloc(sizeof(struct struct_6), 1);
	*_8 = _7;
	_4 = _8;
	_0 = _4;
	goto end_51;
else_51:;
	struct struct_6* _9;
// AST_NEW
// test/leetcode.orng:92
	int64_t _10 = _i;
	int64_t _11 = 10;
	int64_t _12 = _10 % _11;
	int64_t _13 = _i;
	int64_t _14 = 10;
	int64_t _15 = _13 / _14;
	struct struct_6* _16 = test_leetcode_convertToList(_15);
	struct struct_6 _17 = {_12, _16};
	struct struct_6* _18 = calloc(sizeof(struct struct_6), 1);
	*_18 = _17;
	_9 = _18;
	_0 = _9;
end_51:;
	retval = _0;
return_block_52:;
	return retval;
}

int64_t test_leetcode_convertToInt(struct struct_6* _l)
{
	int64_t retval;
	int64_t _0;
	struct struct_6* _1 = _l;
	struct struct_6* _2 = _1->next;
	int64_t _3 = 0;
	struct struct_6* _4 = (struct struct_6*)_3;
	bool _5 = _2 == _4;
	if (!_5) goto else_49;
	int64_t _6;
// AST_DOT
// test/leetcode.orng:83
	struct struct_6* _7 = _l;
	int64_t _8 = _7->val;
	_6 = _8;
	_0 = _6;
	goto end_49;
else_49:;
	int64_t _9;
// AST_ADD
// test/leetcode.orng:85
	struct struct_6* _10 = _l;
	int64_t _11 = _10->val;
	struct struct_6* _12 = _l;
	struct struct_6* _13 = _12->next;
	int64_t _14 = test_leetcode_convertToInt(_13);
	int64_t _15 = 10;
	int64_t _16 = _14 * _15;
	int64_t _17 = _11 + _16;
	_9 = _17;
	_0 = _9;
end_49:;
	retval = _0;
return_block_50:;
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
	struct struct_3 _80_nums1 = _3;
// AST_DEFINE
// test/leetcode.orng:198
	int64_t* _4 = 2;
	struct struct_3 _5 = {1, (int64_t*[]){_4}};
	struct struct_3 _80_nums2 = _5;
// AST_DEFINE
// test/leetcode.orng:200
	float _6 = test_leetcode_findMedianSortedArrays(_80_nums1, _80_nums2);
	float _80_ans = _6;
// AST_IF
// test/leetcode.orng:206
	int64_t _7;
	float _8 = _80_ans;
	float _9 = 2.000000;
	bool _10 = _8 == _9;
	if (!_10) goto else_81;
	int64_t _11;
// AST_CALL
// test/leetcode.orng:203
	struct struct_1 _12 = string_18;
	int64_t _13 = std_system_println(_12);
	_11 = _13;
	_7 = _11;
	goto end_81;
else_81:;
	int64_t _14;
// AST_CALL
// test/leetcode.orng:205
	struct struct_1 _15 = string_19;
	int64_t _16 = std_system_println(_15, _80_ans);
	_14 = _16;
	_7 = _14;
end_81:;
	_0 = _7;
return_block_80:;
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
	struct struct_3 _69_merged = _6;
// AST_DEFER
// test/leetcode.orng:167
	defer_0 = 1;
// AST_DEFINE
// test/leetcode.orng:169
	int64_t _7 = 0;
	int64_t _69_i = _7;
// AST_DEFINE
// test/leetcode.orng:170
	int64_t _8 = 0;
	int64_t _69_j = _8;
// AST_FOR
// test/leetcode.orng:187
begin_71:;
	int64_t _9 = _69_i;
	int64_t _10 = _69_j;
	int64_t _11 = _9 + _10;
	struct struct_3 _12 = _69_merged;
	int64_t _13 = _12.length;
	bool _14 = _11 < _13;
	if (!_14) goto end_71;
// AST_IF
// test/leetcode.orng:186
	bool _15 = 0;
	int64_t _16 = _69_i;
	struct struct_3 _17 = _nums1;
	int64_t _18 = _17.length;
	bool _19 = _16 < _18;
	if (!_19) goto over_0;
	int64_t _20 = _69_j;
	struct struct_3 _21 = _nums2;
	int64_t _22 = _21.length;
	bool _23 = _20 < _22;
	_15 = _23;
over_0:;
	if (!_15) goto else_72;
	int64_t _24;
// AST_IF
// test/leetcode.orng:179
	int64_t _25;
	int64_t _26 = _69_i;
	struct struct_3 _27 = _nums1;
	int64_t _28 = _27.data[_26];
	int64_t _29 = _69_j;
	struct struct_3 _30 = _nums2;
	int64_t _31 = _30.data[_29];
	bool _32 = _28 < _31;
	if (!_32) goto else_73;
	int64_t _33;
// AST_ASSIGN
// test/leetcode.orng:174
	int64_t _34 = _69_i;
	struct struct_3 _35 = _nums1;
	int64_t _36 = _35.data[_34];
	int64_t _37 = _69_i;
	int64_t _38 = _69_j;
	int64_t _39 = _37 + _38;
	_69_merged.data[_39] = _36;
// AST_ADD_ASSIGN
// test/leetcode.orng:175
	int64_t _40 = 1;
	_69_i += _40;
	_33 = _40;
	_25 = _33;
	goto end_73;
else_73:;
	int64_t _41;
// AST_ASSIGN
// test/leetcode.orng:177
	int64_t _42 = _69_j;
	struct struct_3 _43 = _nums2;
	int64_t _44 = _43.data[_42];
	int64_t _45 = _69_i;
	int64_t _46 = _69_j;
	int64_t _47 = _45 + _46;
	_69_merged.data[_47] = _44;
// AST_ADD_ASSIGN
// test/leetcode.orng:178
	int64_t _48 = 1;
	_69_j += _48;
	_41 = _48;
	_25 = _41;
end_73:;
	_24 = _25;
	goto end_72;
else_72:;
	int64_t _49 = _69_i;
	struct struct_3 _50 = _nums1;
	int64_t _51 = _50.length;
	bool _52 = _49 < _51;
	if (!_52) goto else_75;
	int64_t _53;
// AST_ASSIGN
// test/leetcode.orng:181
	int64_t _54 = _69_i;
	struct struct_3 _55 = _nums1;
	int64_t _56 = _55.data[_54];
	int64_t _57 = _69_i;
	int64_t _58 = _69_j;
	int64_t _59 = _57 + _58;
	_69_merged.data[_59] = _56;
// AST_ADD_ASSIGN
// test/leetcode.orng:182
	int64_t _60 = 1;
	_69_i += _60;
	_53 = _60;
	goto end_75;
else_75:;
	int64_t _61 = _69_j;
	struct struct_3 _62 = _nums2;
	int64_t _63 = _62.length;
	bool _64 = _61 < _63;
	if (!_64) goto else_76;
	int64_t _65;
// AST_ASSIGN
// test/leetcode.orng:184
	int64_t _66 = _69_j;
	struct struct_3 _67 = _nums2;
	int64_t _68 = _67.data[_66];
	int64_t _69 = _69_i;
	int64_t _70 = _69_j;
	int64_t _71 = _69 + _70;
	_69_merged.data[_71] = _68;
// AST_ADD_ASSIGN
// test/leetcode.orng:185
	int64_t _72 = 1;
	_69_j += _72;
	_65 = _72;
	goto end_76;
else_76:;
end_76:;
end_75:;
end_72:;
	// for post
	goto begin_71;
end_71:;
// AST_IF
// test/leetcode.orng:193
	float _73;
	struct struct_3 _74 = _69_merged;
	int64_t _75 = _74.length;
	int64_t _76 = 2;
	int64_t _77 = _75 % _76;
	int64_t _78 = 0;
	bool _79 = _77 == _78;
	if (!_79) goto else_77;
	float _80;
// AST_DIVIDE
// test/leetcode.orng:190
	int64_t _81;
// AST_ADD
// test/leetcode.orng:190
	struct struct_3 _82 = _69_merged;
	int64_t _83 = _82.length;
	int64_t _84 = 2;
	int64_t _85 = _83 / _84;
	struct struct_3 _86 = _69_merged;
	int64_t _87 = _86.data[_85];
	struct struct_3 _88 = _69_merged;
	int64_t _89 = _88.length;
	int64_t _90 = 2;
	int64_t _91 = _89 / _90;
	int64_t _92 = 1;
	int64_t _93 = _91 + _92;
	struct struct_3 _94 = _69_merged;
	int64_t _95 = _94.data[_93];
	int64_t _96 = _87 + _95;
	_81 = _96;
	float _97 = 2.000000;
	float _98 = _81 / _97;
	_80 = _98;
	_73 = _80;
	goto end_77;
else_77:;
	float _99;
// AST_CAST
// test/leetcode.orng:192
	struct struct_3 _100 = _69_merged;
	int64_t _101 = _100.length;
	int64_t _102 = 2;
	int64_t _103 = _101 / _102;
	struct struct_3 _104 = _69_merged;
	int64_t _105 = _104.data[_103];
	float _106 = (float)_105;
	_99 = _106;
	_73 = _99;
end_77:;
	_0 = _73;
	retval = _0;
return_block_69:;
	if (defer_0) {
	struct struct_3 _107 = _69_merged;
	free(_107.data);
	}
	return retval;
}

void test_leetcode_test_longestPalindrome()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:236
	struct struct_1 _1 = string_20;
	struct struct_1 _91_s = _1;
// AST_DEFINE
// test/leetcode.orng:238
	struct struct_1 _2 = test_leetcode_longestPalindrome(_91_s);
	struct struct_1 _91_ans = _2;
// AST_IF
// test/leetcode.orng:244
	int64_t _3;
	bool _4 = 1;
	struct struct_1 _5 = string_21;
	bool _6 = std_string_equals(_91_ans, _5);
	if (_6) goto over_0;
	struct struct_1 _7 = string_22;
	bool _8 = std_string_equals(_91_ans, _7);
	_4 = _8;
over_0:;
	if (!_4) goto else_92;
	int64_t _9;
// AST_CALL
// test/leetcode.orng:241
	struct struct_1 _10 = string_23;
	int64_t _11 = std_system_println(_10);
	_9 = _11;
	_3 = _9;
	goto end_92;
else_92:;
	int64_t _12;
// AST_CALL
// test/leetcode.orng:243
	struct struct_1 _13 = string_24;
	struct struct_1 _14 = _91_ans;
	int64_t _15 = _14.length;
	int64_t _16 = std_system_println(_13, _15);
	_12 = _16;
	_3 = _12;
end_92:;
	_0 = _3;
return_block_91:;
}

struct struct_1 test_leetcode_longestPalindrome(struct struct_1 _s)
{
	struct struct_1 retval;
	struct struct_1 _0;
// AST_DEFINE
// test/leetcode.orng:213
// AST_DEFINE
// test/leetcode.orng:221
	int64_t _1 = 0;
	int64_t _83_start = _1;
// AST_DEFINE
// test/leetcode.orng:222
	int64_t _2 = 0;
	int64_t _83_end = _2;
// AST_FOR
// test/leetcode.orng:231
	int64_t _3 = 0;
	int64_t _87_i = _3;
begin_88:;
	int64_t _4 = _87_i;
	struct struct_1 _5 = _s;
	int64_t _6 = _5.length;
	bool _7 = _4 < _6;
	if (!_7) goto end_88;
// AST_DEFINE
// test/leetcode.orng:224
	int64_t _8 = test_leetcode_expandAroundCenter(_s, _87_i, _87_i);
	int64_t _88_len1 = _8;
// AST_DEFINE
// test/leetcode.orng:225
	int64_t _9 = _87_i;
	int64_t _10 = 1;
	int64_t _11 = _9 + _10;
	int64_t _12 = test_leetcode_expandAroundCenter(_s, _87_i, _11);
	int64_t _88_len2 = _12;
// AST_DEFINE
// test/leetcode.orng:226
	double _13 = std_math_max(_88_len1, _88_len2);
	int64_t _14 = (int64_t)_13;
	int64_t _88_len = _14;
// AST_IF
// test/leetcode.orng:230
	int64_t _15 = _88_len;
	int64_t _16 = _83_end;
	int64_t _17 = _83_start;
	int64_t _18 = _16 - _17;
	bool _19 = _15 > _18;
	if (!_19) goto else_89;
	int64_t _20;
// AST_ASSIGN
// test/leetcode.orng:228
	int64_t _21 = _87_i;
	int64_t _22;
// AST_SUBTRACT
// test/leetcode.orng:228
	int64_t _23 = _88_len;
	int64_t _24 = 1;
	int64_t _25 = _23 - _24;
	_22 = _25;
	int64_t _26 = 2;
	int64_t _27 = _22 / _26;
	int64_t _28 = _21 - _27;
	_83_start = _28;
// AST_ASSIGN
// test/leetcode.orng:229
	int64_t _29 = _87_i;
	int64_t _30 = _88_len;
	int64_t _31 = 2;
	int64_t _32 = _30 / _31;
	int64_t _33 = _29 + _32;
	_83_end = _33;
	_20 = _33;
	goto end_89;
else_89:;
end_89:;
	// for post
	int64_t _34 = 1;
	_87_i += _34;
	goto begin_88;
end_88:;
// AST_SLICE
// test/leetcode.orng:232
	struct struct_1 _35 = _s;
	int64_t _36 = _83_start;
	int64_t _37 = _83_end;
	int64_t _38 = 1;
	int64_t _39 = _37 + _38;
	struct struct_1 _40 = {_39 - _36, _35.data + _36};
	_0 = _40;
	retval = _0;
return_block_83:;
	return retval;
}

int64_t test_leetcode_expandAroundCenter(struct struct_1 _s, int64_t _left, int64_t _right)
{
	int64_t retval;
	int64_t _0;
// AST_FOR
// test/leetcode.orng:217
	int64_t _1;
begin_86:;
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
	if (!_2) goto end_86;
	int64_t _18;
// AST_SUB_ASSIGN
// test/leetcode.orng:215
	int64_t _19 = 1;
	_left -= _19;
// AST_ADD_ASSIGN
// test/leetcode.orng:216
	int64_t _20 = 1;
	_right += _20;
	_18 = _20;
	_1 = _18;
	// for post
	goto begin_86;
end_86:;
	_1 = _18;
// AST_SUBTRACT
// test/leetcode.orng:218
	int64_t _21 = _right;
	int64_t _22 = _left;
	int64_t _23 = _21 - _22;
	int64_t _24 = 1;
	int64_t _25 = _23 - _24;
	_0 = _25;
	retval = _0;
return_block_84:;
	return retval;
}

void test_leetcode_test_convert()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:304
	struct struct_1 _1 = string_25;
	int64_t _2 = 3;
	struct struct_1 _3 = test_leetcode_convert(_1, _2);
	struct struct_1 _111_ans = _3;
// AST_IF
// test/leetcode.orng:310
	int64_t _4;
	struct struct_1 _5 = string_26;
	bool _6 = std_string_equals(_111_ans, _5);
	if (!_6) goto else_112;
	int64_t _7;
// AST_CALL
// test/leetcode.orng:307
	struct struct_1 _8 = string_27;
	int64_t _9 = std_system_println(_8);
	_7 = _9;
	_4 = _7;
	goto end_112;
else_112:;
	int64_t _10;
// AST_CALL
// test/leetcode.orng:309
	struct struct_1 _11 = string_28;
	int64_t _12 = std_system_println(_11);
	_10 = _12;
	_4 = _10;
end_112:;
	_0 = _4;
return_block_111:;
}

struct struct_1 test_leetcode_convert(struct struct_1 _s, int64_t _numRows)
{
	struct struct_1 retval;
	int defer_0 = 0;
	struct struct_1 _0;
// AST_DEFINE
// test/leetcode.orng:257
	struct struct_1 _1 = _s;
	int64_t _2 = _1.length;
	struct struct_2 _3 = {_2, malloc(sizeof(struct struct_1) * _2)};
	_3.length = _2;
	for(int i = 0; i < _2; i++) {_3.data[i] = ((struct struct_1){0, 0});}
	struct struct_2 _94_board = _3;
// AST_FOR
// test/leetcode.orng:260
	struct struct_1 _4;
	int64_t _5 = 0;
	int64_t _95_i = _5;
begin_96:;
	int64_t _6 = _95_i;
	struct struct_1 _7 = _s;
	int64_t _8 = _7.length;
	bool _9 = _6 < _8;
	if (!_9) goto end_96;
	struct struct_1 _10;
// AST_ASSIGN
// test/leetcode.orng:259
	int64_t _11 = _numRows;
	struct struct_1 _12 = {_11, malloc(sizeof(int8_t) * _11)};
	_12.length = _11;
	for(int i = 0; i < _11; i++) {_12.data[i] = 0;}
	int64_t _13 = _95_i;
	_94_board.data[_13] = _12;
	_10 = _12;
	_4 = _10;
	// for post
	int64_t _14 = 1;
	_95_i += _14;
	goto begin_96;
end_96:;
	_4 = _10;
// AST_DEFER
// test/leetcode.orng:266
	defer_0 = 1;
// AST_DEFINE
// test/leetcode.orng:268
	int64_t _15 = 0;
	int64_t _94_x = _15;
// AST_DEFINE
// test/leetcode.orng:269
	int64_t _16 = 0;
	int64_t _94_y = _16;
// AST_DEFINE
// test/leetcode.orng:270
	bool _17 = 0;
	bool _94_diagnolizing = _17;
// AST_FOR
// test/leetcode.orng:287
	int64_t _18 = 0;
	int64_t _100_i = _18;
begin_101:;
	int64_t _19 = _100_i;
	struct struct_1 _20 = _s;
	int64_t _21 = _20.length;
	bool _22 = _19 < _21;
	if (!_22) goto end_101;
// AST_ASSIGN
// test/leetcode.orng:272
	int64_t _23 = _100_i;
	struct struct_1 _24 = _s;
	int8_t _25 = _24.data[_23];
	int64_t _26 = _94_y;
	int64_t _27 = _94_x;
	_94_board.data[_27].data[_26] = _25;
// AST_IF
// test/leetcode.orng:286
	bool _28 = _94_diagnolizing;
	if (!_28) goto else_102;
// AST_SUB_ASSIGN
// test/leetcode.orng:274
	int64_t _29 = 1;
	_94_y -= _29;
// AST_ADD_ASSIGN
// test/leetcode.orng:275
	int64_t _30 = 1;
	_94_x += _30;
// AST_IF
// test/leetcode.orng:278
	int64_t _31 = _94_y;
	int64_t _32 = 0;
	bool _33 = _31 == _32;
	if (!_33) goto else_103;
	bool _34;
// AST_ASSIGN
// test/leetcode.orng:277
	bool _35 = 0;
	_94_diagnolizing = _35;
	_34 = _35;
	goto end_103;
else_103:;
end_103:;
	goto end_102;
else_102:;
// AST_ADD_ASSIGN
// test/leetcode.orng:280
	int64_t _36 = 1;
	_94_y += _36;
// AST_IF
// test/leetcode.orng:285
	int64_t _37 = _94_y;
	int64_t _38 = _numRows;
	bool _39 = _37 == _38;
	if (!_39) goto else_105;
	int64_t _40;
// AST_ASSIGN
// test/leetcode.orng:282
	bool _41 = 1;
	_94_diagnolizing = _41;
// AST_SUB_ASSIGN
// test/leetcode.orng:283
	int64_t _42 = 2;
	_94_y -= _42;
// AST_ADD_ASSIGN
// test/leetcode.orng:284
	int64_t _43 = 1;
	_94_x += _43;
	_40 = _43;
	goto end_105;
else_105:;
end_105:;
end_102:;
	// for post
	int64_t _44 = 1;
	_100_i += _44;
	goto begin_101;
end_101:;
// AST_DEFINE
// test/leetcode.orng:289
	struct struct_1 _45 = _s;
	int64_t _46 = _45.length;
	struct struct_1 _47 = {_46, malloc(sizeof(int8_t) * _46)};
	_47.length = _46;
	for(int i = 0; i < _46; i++) {_47.data[i] = 0;}
	struct struct_1 _94_retval = _47;
// AST_DEFINE
// test/leetcode.orng:290
	int64_t _48 = 0;
	int64_t _94_k = _48;
// AST_FOR
// test/leetcode.orng:298
	int64_t _49 = 0;
	int64_t _106_j = _49;
begin_107:;
	int64_t _50 = _106_j;
	int64_t _51 = _numRows;
	bool _52 = _50 < _51;
	if (!_52) goto end_107;
// AST_FOR
// test/leetcode.orng:297
	int64_t _53 = 0;
	int64_t _108_i = _53;
begin_109:;
	int64_t _54 = _108_i;
	struct struct_1 _55 = _s;
	int64_t _56 = _55.length;
	bool _57 = _54 < _56;
	if (!_57) goto end_109;
// AST_IF
// test/leetcode.orng:296
	int64_t _58 = _106_j;
	int64_t _59 = _108_i;
	struct struct_2 _60 = _94_board;
	struct struct_1 _61 = _60.data[_59];
	int8_t _62 = _61.data[_58];
	int8_t _63 = '\0';
	bool _64 = _62 != _63;
	if (!_64) goto else_110;
	int64_t _65;
// AST_ASSIGN
// test/leetcode.orng:294
	int64_t _66 = _106_j;
	int64_t _67 = _108_i;
	struct struct_2 _68 = _94_board;
	struct struct_1 _69 = _68.data[_67];
	int8_t _70 = _69.data[_66];
	int64_t _71 = _94_k;
	_94_retval.data[_71] = _70;
// AST_ADD_ASSIGN
// test/leetcode.orng:295
	int64_t _72 = 1;
	_94_k += _72;
	_65 = _72;
	goto end_110;
else_110:;
end_110:;
	// for post
	int64_t _73 = 1;
	_108_i += _73;
	goto begin_109;
end_109:;
	// for post
	int64_t _74 = 1;
	_106_j += _74;
	goto begin_107;
end_107:;
// AST_IDENT
// test/leetcode.orng:300
	struct struct_1 _75 = _94_retval;
	_0 = _75;
	retval = _0;
return_block_94:;
	if (defer_0) {
// AST_FOR
// test/leetcode.orng:264
	int64_t _76 = 0;
	int64_t _98_i = _76;
begin_99:;
	int64_t _77 = _98_i;
	struct struct_1 _78 = _s;
	int64_t _79 = _78.length;
	bool _80 = _77 < _79;
	if (!_80) goto end_99;
// AST_FREE
// test/leetcode.orng:263
	int64_t _81 = _98_i;
	struct struct_2 _82 = _94_board;
	struct struct_1 _83 = _82.data[_81];
	free(_83.data);
	// for post
	int64_t _84 = 1;
	_98_i += _84;
	goto begin_99;
end_99:;
// AST_FREE
// test/leetcode.orng:265
	struct struct_2 _85 = _94_board;
	free(_85.data);
	}
	return retval;
}

void test_leetcode_test_reverse()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:335
	int64_t _1 = 123;
	int64_t _2 = test_leetcode_reverse(_1);
	int64_t _117_ans = _2;
// AST_IF
// test/leetcode.orng:341
	int64_t _3;
	int64_t _4 = _117_ans;
	int64_t _5 = 321;
	bool _6 = _4 == _5;
	if (!_6) goto else_118;
	int64_t _7;
// AST_CALL
// test/leetcode.orng:338
	struct struct_1 _8 = string_29;
	int64_t _9 = std_system_println(_8);
	_7 = _9;
	_3 = _7;
	goto end_118;
else_118:;
	int64_t _10;
// AST_CALL
// test/leetcode.orng:340
	struct struct_1 _11 = string_30;
	int64_t _12 = std_system_println(_11);
	_10 = _12;
	_3 = _10;
end_118:;
	_0 = _3;
return_block_117:;
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

struct struct_6* test_leetcode_reverseList(struct struct_6* _list)
{
	struct struct_6* retval;
	struct struct_6* _0;
// AST_DEFINE
// test/leetcode.orng:319
	int64_t _1 = 0;
	struct struct_6* _2 = (struct struct_6*)_1;
	struct struct_6* _114_prev = _2;
// AST_DEFINE
// test/leetcode.orng:320
	struct struct_6* _3 = _list;
	struct struct_6* _114_curr = _3;
// AST_DEFINE
// test/leetcode.orng:321
	int64_t _4 = 0;
	struct struct_6* _5 = (struct struct_6*)_4;
	struct struct_6* _114_next = _5;
// AST_FOR
// test/leetcode.orng:327
	struct struct_6* _6;
begin_116:;
	struct struct_6* _7 = _114_curr;
	int64_t _8 = 0;
	struct struct_6* _9 = (struct struct_6*)_8;
	bool _10 = _7 != _9;
	if (!_10) goto end_116;
	struct struct_6* _11;
// AST_ASSIGN
// test/leetcode.orng:323
	struct struct_6* _12 = _114_curr;
	struct struct_6* _13 = _12->next;
	_114_next = _13;
// AST_ASSIGN
// test/leetcode.orng:324
	struct struct_6* _14 = _114_prev;
	_114_curr->next = _14;
// AST_ASSIGN
// test/leetcode.orng:325
	struct struct_6* _15 = _114_curr;
	_114_prev = _15;
// AST_ASSIGN
// test/leetcode.orng:326
	struct struct_6* _16 = _114_next;
	_114_curr = _16;
	_11 = _16;
	_6 = _11;
	// for post
	goto begin_116;
end_116:;
	_6 = _11;
// AST_ASSIGN
// test/leetcode.orng:328
	struct struct_6* _17 = _114_prev;
	_list = _17;
// AST_RETURN
// test/leetcode.orng:329
	struct struct_6* _18 = _list;
	retval = _18;
	goto return_block_114;
	_0 = _18;
	retval = _0;
return_block_114:;
	return retval;
}

void test_leetcode_test_myAtoi()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:376
	struct struct_1 _1 = string_31;
	struct struct_1 _130_s = _1;
// AST_DEFINE
// test/leetcode.orng:378
	int64_t _2 = test_leetcode_myAtoi(_130_s);
	int64_t _130_ans = _2;
// AST_IF
// test/leetcode.orng:384
	int64_t _3;
	int64_t _4 = _130_ans;
	int64_t _5 = 42;
	bool _6 = _4 == _5;
	if (!_6) goto else_131;
	int64_t _7;
// AST_CALL
// test/leetcode.orng:381
	struct struct_1 _8 = string_32;
	int64_t _9 = std_system_println(_8);
	_7 = _9;
	_3 = _7;
	goto end_131;
else_131:;
	int64_t _10;
// AST_CALL
// test/leetcode.orng:383
	struct struct_1 _11 = string_33;
	int64_t _12 = std_system_println(_11);
	_10 = _12;
	_3 = _10;
end_131:;
	_0 = _3;
return_block_130:;
}

int64_t test_leetcode_myAtoi(struct struct_1 _s)
{
	int64_t retval;
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:349
	int64_t _1 = 0;
	int64_t _120_x = _1;
// AST_DEFINE
// test/leetcode.orng:350
	int64_t _2 = 0;
	int64_t _120_i = _2;
// AST_DEFINE
// test/leetcode.orng:351
	bool _3 = 1;
	bool _120_sign = _3;
// AST_FOR
// test/leetcode.orng:354
	int64_t _4;
begin_122:;
	bool _5 = 0;
	int64_t _6 = _120_i;
	struct struct_1 _7 = _s;
	int64_t _8 = _7.length;
	bool _9 = _6 < _8;
	if (!_9) goto over_0;
	int64_t _10 = _120_i;
	struct struct_1 _11 = _s;
	int8_t _12 = _11.data[_10];
	int8_t _13 = ' ';
	bool _14 = _12 == _13;
	_5 = _14;
over_0:;
	if (!_5) goto end_122;
	int64_t _15;
// AST_ADD_ASSIGN
// test/leetcode.orng:354
	int64_t _16 = 1;
	_120_i += _16;
	_15 = _16;
	_4 = _15;
	// for post
	goto begin_122;
end_122:;
	_4 = _15;
// AST_IF
// test/leetcode.orng:365
	int64_t _17 = _120_i;
	struct struct_1 _18 = _s;
	int64_t _19 = _18.length;
	bool _20 = _17 == _19;
	if (!_20) goto else_123;
	int64_t _21;
// AST_RETURN
// test/leetcode.orng:358
	int64_t _22 = 0;
	retval = _22;
	goto return_block_120;
	_21 = _22;
	goto end_123;
else_123:;
	int64_t _23 = _120_i;
	struct struct_1 _24 = _s;
	int8_t _25 = _24.data[_23];
	int8_t _26 = '+';
	bool _27 = _25 == _26;
	if (!_27) goto else_124;
	int64_t _28;
// AST_ASSIGN
// test/leetcode.orng:360
	bool _29 = 1;
	_120_sign = _29;
// AST_ADD_ASSIGN
// test/leetcode.orng:361
	int64_t _30 = 1;
	_120_i += _30;
	_28 = _30;
	goto end_124;
else_124:;
	int64_t _31 = _120_i;
	struct struct_1 _32 = _s;
	int8_t _33 = _32.data[_31];
	int8_t _34 = '-';
	bool _35 = _33 == _34;
	if (!_35) goto else_125;
	int64_t _36;
// AST_ASSIGN
// test/leetcode.orng:363
	bool _37 = 0;
	_120_sign = _37;
// AST_ADD_ASSIGN
// test/leetcode.orng:364
	int64_t _38 = 1;
	_120_i += _38;
	_36 = _38;
	goto end_125;
else_125:;
end_125:;
end_124:;
end_123:;
// AST_FOR
// test/leetcode.orng:370
	int64_t _39;
begin_127:;
	bool _40 = 0;
	int64_t _41 = _120_i;
	struct struct_1 _42 = _s;
	int64_t _43 = _42.length;
	bool _44 = _41 < _43;
	if (!_44) goto over_1;
	int64_t _45 = _120_i;
	struct struct_1 _46 = _s;
	int8_t _47 = _46.data[_45];
	bool _48 = (_47);
	_40 = _48;
over_1:;
	if (!_40) goto end_127;
	int64_t _49;
// AST_ASSIGN
// test/leetcode.orng:369
	int64_t _50 = _120_x;
	int64_t _51 = 10;
	int64_t _52 = _50 * _51;
	int64_t _53 = _120_i;
	struct struct_1 _54 = _s;
	int8_t _55 = _54.data[_53];
	int64_t _56 = (int64_t)_55;
	int64_t _57 = _52 + _56;
	int8_t _58 = '0';
	int64_t _59 = (int64_t)_58;
	int64_t _60 = _57 - _59;
	_120_x = _60;
	_49 = _60;
	_39 = _49;
	// for post
	int64_t _61 = 1;
	_120_i += _61;
	goto begin_127;
end_127:;
	_39 = _49;
// AST_IF
// test/leetcode.orng:372
	int64_t _62;
	bool _63 = _120_sign;
	if (!_63) goto else_128;
	int64_t _64;
// AST_IDENT
// test/leetcode.orng:372
	int64_t _65 = _120_x;
	_64 = _65;
	_62 = _64;
	goto end_128;
else_128:;
	int64_t _66;
// AST_NEG
// test/leetcode.orng:372
	int64_t _67 = _120_x;
	int64_t _68 = -_67;
	_66 = _68;
	_62 = _66;
end_128:;
	_0 = _62;
	retval = _0;
return_block_120:;
	return retval;
}

void test_leetcode_test_isPalindrome()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:404
	int64_t _1 = 121;
	int64_t _137_x = _1;
// AST_DEFINE
// test/leetcode.orng:406
	bool _2 = test_leetcode_isPalindrome(_137_x);
	bool _137_ans = _2;
// AST_IF
// test/leetcode.orng:412
	int64_t _3;
	bool _4 = _137_ans;
	if (!_4) goto else_138;
	int64_t _5;
// AST_CALL
// test/leetcode.orng:409
	struct struct_1 _6 = string_34;
	int64_t _7 = std_system_println(_6);
	_5 = _7;
	_3 = _5;
	goto end_138;
else_138:;
	int64_t _8;
// AST_CALL
// test/leetcode.orng:411
	struct struct_1 _9 = string_35;
	int64_t _10 = std_system_println(_9);
	_8 = _10;
	_3 = _8;
end_138:;
	_0 = _3;
return_block_137:;
}

bool test_leetcode_isPalindrome(int64_t _x)
{
	bool retval;
	bool _0;
// AST_DEFINE
// test/leetcode.orng:391
	struct struct_6* _1 = test_leetcode_convertToList(_x);
	struct struct_6* _133_list = _1;
// AST_DEFINE
// test/leetcode.orng:392
	struct struct_6* _2 = test_leetcode_convertToList(_x);
	struct struct_6* _3 = test_leetcode_reverseList(_2);
	struct struct_6* _133_reversedList = _3;
// AST_FOR
// test/leetcode.orng:399
	struct struct_6* _4;
begin_135:;
	struct struct_6* _5 = _133_list;
	int64_t _6 = 0;
	struct struct_6* _7 = (struct struct_6*)_6;
	bool _8 = _5 != _7;
	if (!_8) goto end_135;
	struct struct_6* _9;
// AST_IF
// test/leetcode.orng:396
	struct struct_6* _10 = _133_list;
	int64_t _11 = _10->val;
	struct struct_6* _12 = _133_reversedList;
	int64_t _13 = _12->val;
	bool _14 = _11 != _13;
	if (!_14) goto else_136;
	bool _15;
// AST_RETURN
// test/leetcode.orng:395
	bool _16 = 0;
	retval = _16;
	goto return_block_133;
	_15 = _16;
	goto end_136;
else_136:;
end_136:;
// AST_ASSIGN
// test/leetcode.orng:397
	struct struct_6* _17 = _133_list;
	struct struct_6* _18 = _17->next;
	_133_list = _18;
// AST_ASSIGN
// test/leetcode.orng:398
	struct struct_6* _19 = _133_reversedList;
	struct struct_6* _20 = _19->next;
	_133_reversedList = _20;
	_9 = _20;
	_4 = _9;
	// for post
	goto begin_135;
end_135:;
	_4 = _9;
// AST_RETURN
// test/leetcode.orng:400
	bool _21 = 1;
	retval = _21;
	goto return_block_133;
	_0 = _21;
	retval = _0;
return_block_133:;
	return retval;
}

void test_leetcode_test_isMatch()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:445
	struct struct_1 _1 = string_36;
	struct struct_1 _150_s = _1;
// AST_DEFINE
// test/leetcode.orng:446
	struct struct_1 _2 = string_37;
	struct struct_1 _150_p = _2;
// AST_DEFINE
// test/leetcode.orng:448
	bool _3 = test_leetcode_isMatch(_150_s, _150_p);
	bool _150_ans = _3;
// AST_IF
// test/leetcode.orng:454
	int64_t _4;
	bool _5 = _150_ans;
	if (!_5) goto else_151;
	int64_t _6;
// AST_CALL
// test/leetcode.orng:451
	struct struct_1 _7 = string_38;
	int64_t _8 = std_system_println(_7);
	_6 = _8;
	_4 = _6;
	goto end_151;
else_151:;
	int64_t _9;
// AST_CALL
// test/leetcode.orng:453
	struct struct_1 _10 = string_39;
	int64_t _11 = std_system_println(_10);
	_9 = _11;
	_4 = _9;
end_151:;
	_0 = _4;
return_block_150:;
}

bool test_leetcode_isMatch(struct struct_1 _s, struct struct_1 _p)
{
	bool retval;
	bool _0;
// AST_DEFINE
// test/leetcode.orng:422
	int64_t _1 = 0;
	int64_t _140_i = _1;
// AST_DEFINE
// test/leetcode.orng:423
	int64_t _2 = 0;
	int64_t _140_j = _2;
// AST_FOR
// test/leetcode.orng:440
begin_142:;
	int64_t _3 = _140_i;
	struct struct_1 _4 = _s;
	int64_t _5 = _4.length;
	bool _6 = _3 < _5;
	if (!_6) goto end_142;
// AST_DEFINE
// test/leetcode.orng:426
	bool _7;
	int64_t _8 = _140_j;
	int64_t _9 = 1;
	int64_t _10 = _8 + _9;
	struct struct_1 _11 = _p;
	int64_t _12 = _11.length;
	bool _13 = _10 == _12;
	if (!_13) goto else_143;
	bool _14;
// AST_FALSE
// test/leetcode.orng:426
	bool _15 = 0;
	_14 = _15;
	_7 = _14;
	goto end_143;
else_143:;
	bool _16;
// AST_EQ
// test/leetcode.orng:426
	int64_t _17 = _140_j;
	int64_t _18 = 1;
	int64_t _19 = _17 + _18;
	struct struct_1 _20 = _p;
	int8_t _21 = _20.data[_19];
	int8_t _22 = '*';
	bool _23 = _21 == _22;
	_16 = _23;
	_7 = _16;
end_143:;
	bool _142_repeat = _7;
// AST_IF
// test/leetcode.orng:439
	bool _24 = 0;
	int64_t _25 = _140_j;
	struct struct_1 _26 = _p;
	int8_t _27 = _26.data[_25];
	int8_t _28 = '.';
	bool _29 = _27 != _28;
	if (!_29) goto over_0;
	int64_t _30 = _140_i;
	struct struct_1 _31 = _s;
	int8_t _32 = _31.data[_30];
	int64_t _33 = _140_j;
	struct struct_1 _34 = _p;
	int8_t _35 = _34.data[_33];
	bool _36 = _32 != _35;
	_24 = _36;
over_0:;
	if (!_24) goto else_145;
// AST_IF
// test/leetcode.orng:433
	bool _37 = _142_repeat;
	if (!_37) goto else_146;
	int64_t _38;
// AST_ADD_ASSIGN
// test/leetcode.orng:430
	int64_t _39 = 1;
	_140_j += _39;
	_38 = _39;
	goto end_146;
else_146:;
	bool _40;
// AST_RETURN
// test/leetcode.orng:432
	bool _41 = 0;
	retval = _41;
	goto return_block_140;
	_40 = _41;
end_146:;
	goto end_145;
else_145:;
// AST_ADD_ASSIGN
// test/leetcode.orng:435
	int64_t _42 = 1;
	_140_i += _42;
// AST_IF
// test/leetcode.orng:438
	bool _43 = _142_repeat;
	bool _44 = !_43;
	if (!_44) goto else_149;
	int64_t _45;
// AST_ADD_ASSIGN
// test/leetcode.orng:437
	int64_t _46 = 1;
	_140_j += _46;
	_45 = _46;
	goto end_149;
else_149:;
end_149:;
end_145:;
	// for post
	goto begin_142;
end_142:;
// AST_TRUE
// test/leetcode.orng:441
	bool _47 = 1;
	_0 = _47;
	retval = _0;
return_block_140:;
	return retval;
}

void test_leetcode_test_maxArea()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:473
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
	struct struct_3 _157_height = _10;
// AST_DEFINE
// test/leetcode.orng:475
	int64_t _11 = 0;
	int64_t _12 = test_leetcode_maxArea(_157_height, _11);
	int64_t _157_ans = _12;
// AST_IF
// test/leetcode.orng:481
	int64_t _13;
	int64_t _14 = _157_ans;
	int64_t _15 = 49;
	bool _16 = _14 == _15;
	if (!_16) goto else_158;
	int64_t _17;
// AST_CALL
// test/leetcode.orng:478
	struct struct_1 _18 = string_41;
	int64_t _19 = std_system_println(_18);
	_17 = _19;
	_13 = _17;
	goto end_158;
else_158:;
	int64_t _20;
// AST_CALL
// test/leetcode.orng:480
	struct struct_1 _21 = string_42;
	int64_t _22 = std_system_println(_21, _157_ans);
	_20 = _22;
	_13 = _20;
end_158:;
	_0 = _13;
return_block_157:;
}

int64_t test_leetcode_maxArea(struct struct_3 _height, int64_t _max)
{
	int64_t retval;
	int64_t _0;
	int64_t _1 = 0;
	int64_t _153_i = _1;
begin_154:;
	int64_t _2 = _153_i;
	struct struct_3 _3 = _height;
	int64_t _4 = _3.length;
	int64_t _5 = 1;
	int64_t _6 = _4 - _5;
	bool _7 = _2 < _6;
	if (!_7) goto end_154;
	int64_t _8;
// AST_FOR
// test/leetcode.orng:469
	int64_t _9;
	int64_t _10 = _153_i;
	int64_t _11 = 1;
	int64_t _12 = _10 + _11;
	int64_t _155_j = _12;
begin_156:;
	int64_t _13 = _155_j;
	struct struct_3 _14 = _height;
	int64_t _15 = _14.length;
	bool _16 = _13 < _15;
	if (!_16) goto end_156;
	int64_t _17;
// AST_CALL
// test/leetcode.orng:467
	struct struct_1 _18 = string_40;
	int64_t _19 = _153_i;
	int64_t _20 = _155_j;
	int64_t _21 = _19 - _20;
	int64_t _22 = std_math_abs(_21);
	int64_t _23 = std_system_println(_18, _22);
// AST_ASSIGN
// test/leetcode.orng:468
	int64_t _24 = _153_i;
	int64_t _25 = _155_j;
	int64_t _26 = _24 - _25;
	int64_t _27 = std_math_abs(_26);
	int64_t _28 = _153_i;
	struct struct_3 _29 = _height;
	int64_t _30 = _29.data[_28];
	int64_t _31 = _155_j;
	struct struct_3 _32 = _height;
	int64_t _33 = _32.data[_31];
	double _34 = std_math_min(_30, _33);
	double _35 = _27 * _34;
	double _36 = std_math_max(_max, _35);
	int64_t _37 = (int64_t)_36;
	_max = _37;
	_17 = _37;
	_9 = _17;
	// for post
	int64_t _38 = 1;
	_155_j += _38;
	goto begin_156;
end_156:;
	_9 = _17;
	_8 = _9;
	_0 = _8;
	// for post
	int64_t _39 = 1;
	_153_i += _39;
	goto begin_154;
end_154:;
	_0 = _8;
	retval = _0;
return_block_153:;
	return retval;
}

void test_leetcode_fizzbuzz(int64_t _n)
{
	struct struct_1 _0;
	int64_t _1 = _n;
	int64_t _2 = 16;
	int64_t _3 = _1 % _2;
	int64_t _4 = 0;
	bool _5 = _3 == _4;
	if (!_5) goto else_36;
	struct struct_1 _6;
// AST_STRING
// test/leetcode.orng:22
	struct struct_1 _7 = string_43;
	_6 = _7;
	_0 = _6;
	goto end_36;
else_36:;
	struct struct_1 _8;
	int64_t _9 = _n;
	int64_t _10 = 3;
	int64_t _11 = _9 % _10;
	int64_t _12 = 0;
	bool _13 = _11 == _12;
	if (!_13) goto else_37;
	struct struct_1 _14;
// AST_STRING
// test/leetcode.orng:24
	struct struct_1 _15 = string_44;
	_14 = _15;
	_8 = _14;
	goto end_37;
else_37:;
	struct struct_1 _16;
	int64_t _17 = _n;
	int64_t _18 = 5;
	int64_t _19 = _17 % _18;
	int64_t _20 = 0;
	bool _21 = _19 == _20;
	if (!_21) goto else_38;
	struct struct_1 _22;
// AST_STRING
// test/leetcode.orng:26
	struct struct_1 _23 = string_45;
	_22 = _23;
	_16 = _22;
	goto end_38;
else_38:;
	struct struct_1 _24;
// AST_CALL
// test/leetcode.orng:28
	int64_t _25 = 255;
	struct struct_1 _26 = string_46;
	struct struct_1 _27 = std_string_format(_25, _26, _n);
	_24 = _27;
	_16 = _24;
end_38:;
	_8 = _16;
end_37:;
	_0 = _8;
end_36:;
return_block_39:;
}

struct struct_1 test_leetcode_fizzbuzz2(int64_t _n)
{
	struct struct_1 retval;
	struct struct_1 _0;
	int64_t _1 = _n;
	int64_t _2 = 15;
	int64_t _3 = _1 % _2;
	switch (_3) {
	case 0:
	{
	struct struct_1 _4 = string_47;
	_0 = _4;
	break;
	} // end case
	case 3:
	case 6:
	case 9:
	case 12:
	{
	struct struct_1 _5 = string_48;
	_0 = _5;
	break;
	} // end case
	case 5:
	case 10:
	{
	struct struct_1 _6 = string_49;
	_0 = _6;
	break;
	} // end case
	default:
	{
	int64_t _7 = 255;
	struct struct_1 _8 = string_50;
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
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:121
// AST_DEFINE
// test/leetcode.orng:133
	struct struct_1 _1 = _str;
	int64_t _2 = _1.length;
	int64_t _56_n = _2;
// AST_DEFINE
// test/leetcode.orng:134
	int64_t _3 = 0;
	int64_t _56_res = _3;
// AST_FOR
// test/leetcode.orng:144
	int64_t _4 = 0;
	int64_t _61_i = _4;
begin_62:;
	int64_t _5 = _61_i;
	int64_t _6 = _56_n;
	bool _7 = _5 < _6;
	if (!_7) goto end_62;
// AST_FOR
// test/leetcode.orng:143
	int64_t _8 = _61_i;
	int64_t _63_j = _8;
begin_64:;
	int64_t _9 = _63_j;
	int64_t _10 = _56_n;
	bool _11 = _9 < _10;
	if (!_11) goto end_64;
// AST_IF
// test/leetcode.orng:142
	bool _12 = test_leetcode_areDistinct(_str, _61_i, _63_j);
	if (!_12) goto else_65;
	int64_t _13;
// AST_ASSIGN
// test/leetcode.orng:141
	int64_t _14 = _63_j;
	int64_t _15 = _61_i;
	int64_t _16 = _14 - _15;
	int64_t _17 = 1;
	int64_t _18 = _16 + _17;
	double _19 = std_math_max(_56_res, _18);
	int64_t _20 = (int64_t)_19;
	_56_res = _20;
	_13 = _20;
	goto end_65;
else_65:;
end_65:;
	// for post
	int64_t _21 = 1;
	_63_j += _21;
	goto begin_64;
end_64:;
	// for post
	int64_t _22 = 1;
	_61_i += _22;
	goto begin_62;
end_62:;
// AST_RETURN
// test/leetcode.orng:146
	int64_t _23 = _56_res;
	retval = _23;
	goto return_block_56;
	_0 = _23;
	retval = _0;
return_block_56:;
	return retval;
}

bool test_leetcode_areDistinct(struct struct_1 _str, int64_t _i, int64_t _j)
{
	bool retval;
	bool _0;
// AST_DEFINE
// test/leetcode.orng:123
	struct struct_8 _57_visited = ((struct struct_8){256, (bool*[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}});
// AST_FOR
// test/leetcode.orng:130
	bool _1;
	int64_t _2 = _i;
	int64_t _58_k = _2;
begin_59:;
	int64_t _3 = _58_k;
	int64_t _4 = _j;
	bool _5 = _3 <= _4;
	if (!_5) goto end_59;
	bool _6;
// AST_DEFINE
// test/leetcode.orng:125
	int64_t _7 = _58_k;
	struct struct_1 _8 = _str;
	int8_t _9 = _8.data[_7];
	int64_t _10 = (int64_t)_9;
	int64_t _59_charCode = _10;
// AST_IF
// test/leetcode.orng:128
	int64_t _11 = _59_charCode;
	struct struct_8 _12 = _57_visited;
	bool _13 = _12.data[_11];
	if (!_13) goto else_60;
	bool _14;
// AST_RETURN
// test/leetcode.orng:127
	bool _15 = 0;
	retval = _15;
	goto return_block_57;
	_14 = _15;
	goto end_60;
else_60:;
end_60:;
// AST_ASSIGN
// test/leetcode.orng:129
	bool _16 = 1;
	int64_t _17 = _59_charCode;
	_57_visited.data[_17] = _16;
	_6 = _16;
	_1 = _6;
	// for post
	int64_t _18 = 1;
	_58_k += _18;
	goto begin_59;
end_59:;
	_1 = _6;
// AST_RETURN
// test/leetcode.orng:131
	bool _19 = 1;
	retval = _19;
	goto return_block_57;
	_0 = _19;
	retval = _0;
return_block_57:;
	return retval;
}

void test_leetcode_test_lengthOfLongestSubstring()
{
	int64_t _0;
// AST_DEFINE
// test/leetcode.orng:150
	struct struct_1 _1 = string_51;
	struct struct_1 _66_s = _1;
// AST_DEFINE
// test/leetcode.orng:152
	int64_t _2 = test_leetcode_lengthOfLongestSubstring(_66_s);
	int64_t _66_ans = _2;
// AST_IF
// test/leetcode.orng:158
	int64_t _3;
	int64_t _4 = _66_ans;
	int64_t _5 = 3;
	bool _6 = _4 == _5;
	if (!_6) goto else_67;
	int64_t _7;
// AST_CALL
// test/leetcode.orng:155
	struct struct_1 _8 = string_52;
	int64_t _9 = std_system_println(_8);
	_7 = _9;
	_3 = _7;
	goto end_67;
else_67:;
	int64_t _10;
// AST_CALL
// test/leetcode.orng:157
	struct struct_1 _11 = string_53;
	int64_t _12 = std_system_println(_11, _66_ans);
	_10 = _12;
	_3 = _10;
end_67:;
	_0 = _3;
return_block_66:;
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
return_block_160:;
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
