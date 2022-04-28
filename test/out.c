/* Code generated using Orange Translator http://josephs-projects.com */

/* Includes used by the program */
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Struct definitions */
struct struct_1 {
	signed int length;
	signed char data[];
};

struct struct_1* new_struct_1(int count)
{
	struct struct_1* retval = malloc(sizeof(signed int) + sizeof(signed char) * count);
	for(int i = 0; i < count; i++) {
		retval->data[i] = 0;
	}
	retval->length = count;
	return retval;
}

struct struct_2 {
	signed int length;
	struct struct_1* data[];
};

struct struct_2* new_struct_2(int count)
{
	struct struct_2* retval = malloc(sizeof(signed int) + sizeof(struct struct_1*) * count);
	for(int i = 0; i < count; i++) {
		retval->data[i] = 0;
	}
	retval->length = count;
	return retval;
}

struct struct_3 {
	signed int length;
	signed int data[];
};

struct struct_3* new_struct_3(int count)
{
	struct struct_3* retval = malloc(sizeof(signed int) + sizeof(signed int) * count);
	for(int i = 0; i < count; i++) {
		retval->data[i] = 0;
	}
	retval->length = count;
	return retval;
}

struct struct_4 {
	signed int length;
	signed int data[2];
};

struct struct_4* new_struct_4(int count)
{
	struct struct_4* retval = malloc(sizeof(signed int) + sizeof(signed int) * count);
	for(int i = 0; i < count; i++) {
		retval->data[i] = 0;
	}
	retval->length = count;
	return retval;
}

struct struct_5 {
	signed int length;
	signed int data[4];
};

struct struct_5* new_struct_5(int count)
{
	struct struct_5* retval = malloc(sizeof(signed int) + sizeof(signed int) * count);
	for(int i = 0; i < count; i++) {
		retval->data[i] = 0;
	}
	retval->length = count;
	return retval;
}

struct struct_6 {
	signed int val;
	struct struct_6* next;
};

struct struct_6* new_struct_6()
{
	struct struct_6* retval = malloc(sizeof(struct struct_6));
	*retval = ((struct struct_6){0, 0});
	return retval;
}

struct struct_7 {
	signed int length;
	bool data[256];
};

struct struct_7* new_struct_7(int count)
{
	struct struct_7* retval = malloc(sizeof(signed int) + sizeof(bool) * count);
	for(int i = 0; i < count; i++) {
		retval->data[i] = 0;
	}
	retval->length = count;
	return retval;
}

struct struct_8 {
	signed int length;
	signed int data[1];
};

struct struct_8* new_struct_8(int count)
{
	struct struct_8* retval = malloc(sizeof(signed int) + sizeof(signed int) * count);
	for(int i = 0; i < count; i++) {
		retval->data[i] = 0;
	}
	retval->length = count;
	return retval;
}

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
struct struct_4 test_leetcode_twoSum(struct struct_3* _nums, signed int _target);
void test_leetcode_test_twoSum();
signed int test_leetcode_convertToInt(struct struct_6* _l);
struct struct_6* test_leetcode_convertToList(signed int _i);
struct struct_6* test_leetcode_addTwoNumbers(struct struct_6* _l1, struct struct_6* _l2);
void test_leetcode_test_addTwoNumbers();
signed int test_leetcode_lengthOfLongestSubstring(struct struct_1* _s);
void test_leetcode_test_lengthOfLongestSubstring();
float test_leetcode_findMedianSortedArrays(struct struct_3* _nums1, struct struct_3* _nums2);
void test_leetcode_test_findMedianSortedArrays();
struct struct_1* test_leetcode_longestPalindrome(struct struct_1* _s);
signed int test_leetcode_expandAroundCenter(struct struct_1* _s, signed int _left, signed int _right);
void test_leetcode_test_longestPalindrome();
struct struct_1* test_leetcode_convert(struct struct_1* _s, signed int _numRows);
void test_leetcode_test_convert();
struct struct_6* test_leetcode_reverseList(struct struct_6* _list);
signed int test_leetcode_reverse(signed int _x);
void test_leetcode_test_reverse();
signed int test_leetcode_myAtoi(struct struct_1* _s);
void test_leetcode_test_myAtoi();
signed int test_testModule_main(struct struct_2* _args);
double stdlib_math_max(double _x, double _y);
bool stdlib_string_equals(struct struct_1* _a, struct struct_1* _b);
struct struct_1* stdlib_string_substring(struct struct_1* _s, signed int _start, signed int _end);

#ifndef ORANGE_PROGRAM_9776
#define ORANGE_PROGRAM_9776

/* String definitions */
struct struct_1 string_0 = {15, {'t', 'w', 'o', 'S', 'u', 'm', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_1 = {14, {'t', 'w', 'o', 'S', 'u', 'm', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
struct struct_1 string_2 = {22, {'a', 'd', 'd', 'T', 'w', 'o', 'N', 'u', 'm', 'b', 'e', 'r', 's', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_3 = {21, {'a', 'd', 'd', 'T', 'w', 'o', 'N', 'u', 'm', 'b', 'e', 'r', 's', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
struct struct_1 string_4 = {8, {'a', 'b', 'c', 'a', 'b', 'c', 'b', 'b', '\0'}};
struct struct_1 string_5 = {33, {'l', 'e', 'n', 'g', 't', 'h', 'O', 'f', 'L', 'o', 'n', 'g', 'e', 's', 't', 'S', 'u', 'b', 's', 't', 'r', 'i', 'n', 'g', ':', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'}};
struct struct_1 string_6 = {32, {'l', 'e', 'n', 'g', 't', 'h', 'O', 'f', 'L', 'o', 'n', 'g', 'e', 's', 't', 'S', 'u', 'b', 's', 't', 'r', 'i', 'n', 'g', ':', ' ', 'F', 'a', 'i', 'l', 'e', 'd', '\0'}};
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
{// AST_CALL
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
}
struct struct_4 test_leetcode_twoSum(struct struct_3* _nums, signed int _target)
{
	struct struct_4 retval;
// AST_DEFINE
// test/leetcode.orng:19
	signed int _0 = 1;
	signed int _1 = -_0;
	signed int _2 = 1;
	signed int _3 = -_2;
	struct struct_4 _4 = {2, {_1, _3}};
	struct struct_4 _92_ans = _4;
// AST_FOR
// test/leetcode.orng:20
	signed int _5 = 0;
	signed int _i = _5;
begin_93:;
	signed int _6 = _i;
	struct struct_3* _7 = _nums;
	signed int _8 = _7->length;
	signed int _9 = 1;
	signed int _10 = _8 - _9;
	bool _11 = _6 < _10;
	if (!_11) goto end_93;
// AST_FOR
// test/leetcode.orng:21
	signed int _12 = _i;
	signed int _13 = 1;
	signed int _14 = _12 + _13;
	signed int _j = _14;
begin_94:;
	signed int _15 = _j;
	struct struct_3* _16 = _nums;
	signed int _17 = _16->length;
	bool _18 = _15 < _17;
	if (!_18) goto end_94;
// AST_IF
// test/leetcode.orng:22
	signed int _19 = _i;
	struct struct_3* _20 = _nums;
	signed int _21 = _20->data[_19];
	signed int _22 = _j;
	struct struct_3* _23 = _nums;
	signed int _24 = _23->data[_22];
	signed int _25 = _21 + _24;
	signed int _26 = _target;
	bool _27 = _25 == _26;
	if (!_27) goto end_95;
// AST_ASSIGN
// test/leetcode.orng:23
	signed int _28 = _i;
	signed int _29 = _j;
	struct struct_4 _30 = {2, {_28, _29}};
	_92_ans= _30;
end_95:;
	signed int _31 = 1;
	_j+= _31;
	goto begin_94;
end_94:;
	signed int _32 = 1;
	_i+= _32;
	goto begin_93;
end_93:;
// AST_RETURN
// test/leetcode.orng:27
	struct struct_4 _33 = _92_ans;
	retval = _33;
	goto return_block_92;
return_block_92:;
    return retval;
}
void test_leetcode_test_twoSum()
{// AST_DEFINE
// test/leetcode.orng:31
	signed int _0 = 2;
	signed int _1 = 7;
	signed int _2 = 11;
	signed int _3 = 15;
	struct struct_5 _4 = {4, {_0, _1, _2, _3}};
	struct struct_5 _96_nums = _4;
// AST_DEFINE
// test/leetcode.orng:32
	signed int _5 = 9;
	signed int _96_target = _5;
// AST_DEFINE
// test/leetcode.orng:34
	struct struct_5 _6 = _96_nums;
	struct struct_5* _7 = &_6;
	struct struct_4 _8 = test_leetcode_twoSum(_7, _96_target);
	struct struct_4 _96_ans = _8;
// Unknown ASTNode type
// test/leetcode.orng:36
	signed int _9 = 0;
	struct struct_4 _10 = _96_ans;
	signed int _11 = _10.data[_9];
	struct struct_5 _12 = _96_nums;
	signed int _13 = _12.data[_11];
	signed int _14 = 1;
	struct struct_4 _15 = _96_ans;
	signed int _16 = _15.data[_14];
	struct struct_5 _17 = _96_nums;
	signed int _18 = _17.data[_16];
	signed int _19 = _13 + _18;
	signed int _20 = _96_target;
	bool _21 = _19 == _20;
	if (!21) goto begin_97;
// AST_CALL
// test/leetcode.orng:37
	struct struct_1* _22 = &string_0;
	signed int _23 = stdlib_system_println(_22);
	goto end_97;
begin_97:;
// AST_CALL
// test/leetcode.orng:39
	struct struct_1* _24 = &string_1;
	signed int _25 = stdlib_system_println(_24);
end_97:;
}
signed int test_leetcode_convertToInt(struct struct_6* _l)
{
	signed int retval;
// Unknown ASTNode type
// test/leetcode.orng:54
	struct struct_6* _0 = _l;
	struct struct_6* _1 = _0->next;
	void* _2 = 0;
	bool _3 = _1 == _2;
	if (!3) goto begin_100;
// AST_RETURN
// test/leetcode.orng:55
	struct struct_6* _4 = _l;
	signed int _5 = _4->val;
	retval = _5;
	goto return_block_99;
	goto end_100;
begin_100:;
// AST_DEFINE
// test/leetcode.orng:57
	struct struct_6* _6 = _l;
	struct struct_6* _7 = _6->next;
	signed int _8 = test_leetcode_convertToInt(_7);
	signed int _bottom = _8;
// AST_RETURN
// test/leetcode.orng:58
	struct struct_6* _9 = _l;
	signed int _10 = _9->val;
	signed int _11 = _bottom;
	signed int _12 = 10;
	signed int _13 = _11 * _12;
	signed int _14 = _10 + _13;
	retval = _14;
	goto return_block_99;
end_100:;
return_block_99:;
    return retval;
}
struct struct_6* test_leetcode_convertToList(signed int _i)
{
	struct struct_6* retval;
// AST_DEFINE
// test/leetcode.orng:62
calloc(sizeof(struct struct_6), 1)	struct struct_6* _102_retval = _5;
// Unknown ASTNode type
// test/leetcode.orng:63
	signed int _0 = _i;
	signed int _1 = 10;
	bool _2 = _0 < _1;
	if (!2) goto begin_103;
// AST_ASSIGN
// test/leetcode.orng:64
{	signed int _3 = _i;
, 	void* _4 = 0;
}	struct struct_6 _5 = (struct struct_6)_1;
	*_102_retval= _5;
	goto end_103;
begin_103:;
// AST_ASSIGN
// test/leetcode.orng:66
{	signed int _6 = _i;
	signed int _7 = 10;
	signed int _8 = _6 % _7;
, 	signed int _9 = _i;
	signed int _10 = 10;
	signed int _11 = _9 / _10;
	struct struct_6* _12 = test_leetcode_convertToList(_11);
}	struct struct_6 _13 = (struct struct_6)_1;
	*_102_retval= _13;
end_103:;
// AST_RETURN
// test/leetcode.orng:68
	struct struct_6* _14 = _102_retval;
	retval = _14;
	goto return_block_102;
return_block_102:;
    return retval;
}
struct struct_6* test_leetcode_addTwoNumbers(struct struct_6* _l1, struct struct_6* _l2)
{
	struct struct_6* retval;
// AST_RETURN
// test/leetcode.orng:71
	signed int _0 = test_leetcode_convertToInt(_l1);
	signed int _1 = test_leetcode_convertToInt(_l2);
	signed int _2 = _0 + _1;
	struct struct_6* _3 = test_leetcode_convertToList(_2);
	retval = _3;
	goto return_block_105;
return_block_105:;
    return retval;
}
void test_leetcode_test_addTwoNumbers()
{// AST_DEFINE
// test/leetcode.orng:75
calloc(sizeof(struct struct_6), 1)	struct struct_6* _106_l1_c = _5;
// AST_ASSIGN
// test/leetcode.orng:76
{	signed int _0 = 3;
, 	void* _1 = 0;
}	struct struct_6 _2 = (struct struct_6)_1;
	*_106_l1_c= _2;
// AST_DEFINE
// test/leetcode.orng:77
calloc(sizeof(struct struct_6), 1)	struct struct_6* _106_l1_b = _5;
// AST_ASSIGN
// test/leetcode.orng:78
{	signed int _3 = 4;
, 	struct struct_6* _4 = _106_l1_c;
}	struct struct_6 _5 = (struct struct_6)_1;
	*_106_l1_b= _5;
// AST_DEFINE
// test/leetcode.orng:79
calloc(sizeof(struct struct_6), 1)	struct struct_6* _106_l1 = _5;
// AST_ASSIGN
// test/leetcode.orng:80
{	signed int _6 = 2;
, 	struct struct_6* _7 = _106_l1_b;
}	struct struct_6 _8 = (struct struct_6)_1;
	*_106_l1= _8;
// AST_DEFINE
// test/leetcode.orng:81
calloc(sizeof(struct struct_6), 1)	struct struct_6* _106_l2_c = _5;
// AST_ASSIGN
// test/leetcode.orng:82
{	signed int _9 = 4;
, 	void* _10 = 0;
}	struct struct_6 _11 = (struct struct_6)_1;
	*_106_l2_c= _11;
// AST_DEFINE
// test/leetcode.orng:83
calloc(sizeof(struct struct_6), 1)	struct struct_6* _106_l2_b = _5;
// AST_ASSIGN
// test/leetcode.orng:84
{	signed int _12 = 6;
, 	struct struct_6* _13 = _106_l2_c;
}	struct struct_6 _14 = (struct struct_6)_1;
	*_106_l2_b= _14;
// AST_DEFINE
// test/leetcode.orng:85
calloc(sizeof(struct struct_6), 1)	struct struct_6* _106_l2 = _5;
// AST_ASSIGN
// test/leetcode.orng:86
{	signed int _15 = 5;
, 	struct struct_6* _16 = _106_l2_b;
}	struct struct_6 _17 = (struct struct_6)_1;
	*_106_l2= _17;
// AST_DEFINE
// test/leetcode.orng:88
	struct struct_6* _18 = test_leetcode_addTwoNumbers(_106_l1, _106_l2);
	struct struct_6* _106_ans = _18;
// Unknown ASTNode type
// test/leetcode.orng:90
	struct struct_6* _19 = _106_ans;
	signed int _20 = _19->val;
	signed int _21 = 7;
	bool _22 = _20 == _21;
	struct struct_6* _23 = _106_ans;
	struct struct_6* _24 = _23->next;
	signed int _25 = _24->val;
	signed int _26 = 0;
	bool _27 = _25 == _26;
	bool _28 = _22 && _27;
	struct struct_6* _29 = _106_ans;
	struct struct_6* _30 = _29->next;
	struct struct_6* _31 = _30->next;
	signed int _32 = _31->val;
	signed int _33 = 8;
	bool _34 = _32 == _33;
	bool _35 = _28 && _34;
	if (!35) goto begin_107;
// AST_CALL
// test/leetcode.orng:91
	struct struct_1* _36 = &string_2;
	signed int _37 = stdlib_system_println(_36);
	goto end_107;
begin_107:;
// AST_CALL
// test/leetcode.orng:93
	struct struct_1* _38 = &string_3;
	signed int _39 = stdlib_system_println(_38);
end_107:;
}
signed int test_leetcode_lengthOfLongestSubstring(struct struct_1* _s)
{
	signed int retval;
// AST_DEFINE
// test/leetcode.orng:102
	signed int _0 = 0;
	signed int _109_longest = _0;
// AST_FOR
// test/leetcode.orng:103
	signed int _1 = 0;
	signed int _i = _1;
begin_110:;
	signed int _2 = _i;
	struct struct_1* _3 = _s;
	signed int _4 = _3->length;
	bool _5 = _2 < _4;
	if (!_5) goto end_110;
// AST_DEFINE
// test/leetcode.orng:104
	struct struct_7 _visited = ((struct struct_7){256, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
// AST_FOR
// test/leetcode.orng:105
	signed int _6 = _i;
	signed int _j = _6;
begin_111:;
	signed int _7 = _j;
	struct struct_1* _8 = _s;
	signed int _9 = _8->length;
	bool _10 = _7 < _9;
	if (!_10) goto end_111;
// Unknown ASTNode type
// test/leetcode.orng:106
	signed int _11 = _j;
	struct struct_1* _12 = _s;
	signed char _13 = _12->data[_11];
	struct struct_7 _14 = _visited;
	bool _15 = _14.data[_13];
	if (!15) goto begin_112;
// Unknown ASTNode type
// test/leetcode.orng:107
break	goto end_112;
begin_112:;
// AST_ASSIGN
// test/leetcode.orng:109
	signed int _16 = _j;
	signed int _17 = _i;
	signed int _18 = _16 - _17;
	signed int _19 = 1;
	signed int _20 = _18 + _19;
	double _21 = stdlib_math_max(_109_longest, _20);
	signed int _22 = (signed int)_21;
	_109_longest= _22;
// AST_ASSIGN
// test/leetcode.orng:110
	bool _23 = 1;
	signed int _24 = _j;
	struct struct_1* _25 = _s;
	signed char _26 = _25->data[_24];
	_visited.data[_26]= _23;
end_112:;
	signed int _27 = 1;
	_j+= _27;
	goto begin_111;
end_111:;
// AST_ASSIGN
// test/leetcode.orng:113
	bool _28 = 0;
	signed int _29 = _i;
	struct struct_1* _30 = _s;
	signed char _31 = _30->data[_29];
	_visited.data[_31]= _28;
	signed int _32 = 1;
	_i+= _32;
	goto begin_110;
end_110:;
// AST_RETURN
// test/leetcode.orng:115
	signed int _33 = _109_longest;
	retval = _33;
	goto return_block_109;
return_block_109:;
    return retval;
}
void test_leetcode_test_lengthOfLongestSubstring()
{// AST_DEFINE
// test/leetcode.orng:119
	struct struct_1* _0 = &string_4;
	struct struct_1* _114_s = _0;
// AST_DEFINE
// test/leetcode.orng:121
	signed int _1 = test_leetcode_lengthOfLongestSubstring(_114_s);
	signed int _114_ans = _1;
// Unknown ASTNode type
// test/leetcode.orng:123
	signed int _2 = _114_ans;
	signed int _3 = 3;
	bool _4 = _2 == _3;
	if (!4) goto begin_115;
// AST_CALL
// test/leetcode.orng:124
	struct struct_1* _5 = &string_5;
	signed int _6 = stdlib_system_println(_5);
	goto end_115;
begin_115:;
// AST_CALL
// test/leetcode.orng:126
	struct struct_1* _7 = &string_6;
	signed int _8 = stdlib_system_println(_7);
end_115:;
}
float test_leetcode_findMedianSortedArrays(struct struct_3* _nums1, struct struct_3* _nums2)
{
	float retval;
int defer_0 = 0;
// AST_DEFINE
// test/leetcode.orng:135
new_struct_3(	struct struct_3* _0 = _nums1;
	signed int _1 = _0->length;
	struct struct_3* _2 = _nums2;
	signed int _3 = _2->length;
	signed int _4 = _1 + _3;
)	struct struct_3* _117_merged = _1;
// Unknown ASTNode type
// test/leetcode.orng:136
defer_0 = 1;// AST_DEFINE
// test/leetcode.orng:138
	signed int _5 = 0;
	signed int _117_i = _5;
// AST_DEFINE
// test/leetcode.orng:139
	signed int _6 = 0;
	signed int _117_j = _6;
// AST_FOR
// test/leetcode.orng:140
begin_118:;
	signed int _7 = _117_i;
	signed int _8 = _117_j;
	signed int _9 = _7 + _8;
	struct struct_3* _