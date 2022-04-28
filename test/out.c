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
struct struct_4 test_leetcode_twoSum(struct struct_3* test_leetcode_twoSum_nums, signed int test_leetcode_twoSum_target);
void test_leetcode_test_twoSum();
signed int test_leetcode_convertToInt(struct struct_6* test_leetcode_convertToInt_l);
struct struct_6* test_leetcode_convertToList(signed int test_leetcode_convertToList_i);
struct struct_6* test_leetcode_addTwoNumbers(struct struct_6* test_leetcode_addTwoNumbers_l1, struct struct_6* test_leetcode_addTwoNumbers_l2);
void test_leetcode_test_addTwoNumbers();
bool test_leetcode_areDistinct(struct struct_1* test_leetcode_areDistinct_str, signed int test_leetcode_areDistinct_i, signed int test_leetcode_areDistinct_j);
signed int test_leetcode_lengthOfLongestSubstring(struct struct_1* test_leetcode_lengthOfLongestSubstring_str);
void test_leetcode_test_lengthOfLongestSubstring();
float test_leetcode_findMedianSortedArrays(struct struct_3* test_leetcode_findMedianSortedArrays_nums1, struct struct_3* test_leetcode_findMedianSortedArrays_nums2);
void test_leetcode_test_findMedianSortedArrays();
struct struct_1* test_leetcode_longestPalindrome(struct struct_1* test_leetcode_longestPalindrome_s);
signed int test_leetcode_expandAroundCenter(struct struct_1* test_leetcode_expandAroundCenter_s, signed int test_leetcode_expandAroundCenter_left, signed int test_leetcode_expandAroundCenter_right);
void test_leetcode_test_longestPalindrome();
struct struct_1* test_leetcode_convert(struct struct_1* test_leetcode_convert_s, signed int test_leetcode_convert_numRows);
void test_leetcode_test_convert();
struct struct_6* test_leetcode_reverseList(struct struct_6* test_leetcode_reverseList_list);
signed int test_leetcode_reverse(signed int test_leetcode_reverse_x);
void test_leetcode_test_reverse();
signed int test_leetcode_myAtoi(struct struct_1* test_leetcode_myAtoi_s);
void test_leetcode_test_myAtoi();
signed int test_testModule_main(struct struct_2* test_testModule_main_args);
double stdlib_math_max(double stdlib_math_max_x, double stdlib_math_max_y);
bool stdlib_string_equals(struct struct_1* stdlib_string_equals_a, struct struct_1* stdlib_string_equals_b);
struct struct_1* stdlib_string_substring(struct struct_1* stdlib_string_substring_s, signed int stdlib_string_substring_start, signed int stdlib_string_substring_end);

#ifndef ORANGE_PROGRAM_28858
#define ORANGE_PROGRAM_28858

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
continue_91:;
}
struct struct_4 test_leetcode_twoSum(struct struct_3* test_leetcode_twoSum_nums, signed int test_leetcode_twoSum_target)
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
	signed int _93_i = _5;
begin_93:;
	signed int _6 = _93_i;
	struct struct_3* _7 = test_leetcode_twoSum_nums;
	signed int _8 = _7->length;
	signed int _9 = 1;
	signed int _10 = _8 - _9;
	bool _11 = _6 < _10;
	if (!_11) goto end_93;
// AST_FOR
// test/leetcode.orng:21
	signed int _12 = _93_i;
	signed int _13 = 1;
	signed int _14 = _12 + _13;
	signed int _94_j = _14;
begin_94:;
	signed int _15 = _94_j;
	struct struct_3* _16 = test_leetcode_twoSum_nums;
	signed int _17 = _16->length;
	bool _18 = _15 < _17;
	if (!_18) goto end_94;
// AST_IF
// test/leetcode.orng:22
	signed int _19 = _93_i;
	struct struct_3* _20 = test_leetcode_twoSum_nums;
	signed int _21 = _20->data[_19];
	signed int _22 = _94_j;
	struct struct_3* _23 = test_leetcode_twoSum_nums;
	signed int _24 = _23->data[_22];
	signed int _25 = _21 + _24;
	signed int _26 = test_leetcode_twoSum_target;
	bool _27 = _25 == _26;
	if (!_27) goto end_95;
// AST_ASSIGN
// test/leetcode.orng:23
	signed int _28 = _93_i;
	signed int _29 = _94_j;
	struct struct_4 _30 = {2, {_28, _29}};
	_92_ans = _30;
continue_95:;
end_95:;
continue_94:;
	signed int _31 = 1;
	_94_j += _31;
	goto begin_94;
end_94:;
continue_93:;
	signed int _32 = 1;
	_93_i += _32;
	goto begin_93;
end_93:;
// AST_RETURN
// test/leetcode.orng:27
	struct struct_4 _33 = _92_ans;
	retval = _33;
	goto return_block_92;
continue_92:;
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
// AST_IFELSE
// test/leetcode.orng:36
	signed int _9 = 0;
	signed int _10 = _96_ans.data[_9];
	signed int _11 = _96_nums.data[_10];
	signed int _12 = 1;
	signed int _13 = _96_ans.data[_12];
	signed int _14 = _96_nums.data[_13];
	signed int _15 = _11 + _14;
	signed int _16 = _96_target;
	bool _17 = _15 == _16;
	if (!_17) goto else_97;
// AST_CALL
// test/leetcode.orng:37
	struct struct_1* _18 = &string_0;
	signed int _19 = stdlib_system_println(_18);
continue_97:;
	goto end_97;
else_97:;
// AST_CALL
// test/leetcode.orng:39
	struct struct_1* _20 = &string_1;
	signed int _21 = stdlib_system_println(_20);
continue_98:;
end_97:;
continue_96:;
}
signed int test_leetcode_convertToInt(struct struct_6* test_leetcode_convertToInt_l)
{
	signed int retval;
// AST_IFELSE
// test/leetcode.orng:54
	struct struct_6* _0 = test_leetcode_convertToInt_l;
	struct struct_6* _1 = _0->next;
	void* _2 = 0;
	bool _3 = _1 == _2;
	if (!_3) goto else_100;
// AST_RETURN
// test/leetcode.orng:55
	struct struct_6* _4 = test_leetcode_convertToInt_l;
	signed int _5 = _4->val;
	retval = _5;
	goto return_block_99;
continue_100:;
	goto end_100;
else_100:;
// AST_DEFINE
// test/leetcode.orng:57
	struct struct_6* _6 = test_leetcode_convertToInt_l;
	struct struct_6* _7 = _6->next;
	signed int _8 = test_leetcode_convertToInt(_7);
	signed int _101_bottom = _8;
// AST_RETURN
// test/leetcode.orng:58
	struct struct_6* _9 = test_leetcode_convertToInt_l;
	signed int _10 = _9->val;
	signed int _11 = _101_bottom;
	signed int _12 = 10;
	signed int _13 = _11 * _12;
	signed int _14 = _10 + _13;
	retval = _14;
	goto return_block_99;
continue_101:;
end_100:;
continue_99:;
return_block_99:;
    return retval;
}
struct struct_6* test_leetcode_convertToList(signed int test_leetcode_convertToList_i)
{
	struct struct_6* retval;
// AST_DEFINE
// test/leetcode.orng:62
	struct struct_6* _0 = calloc(sizeof(struct struct_6), 1);
	*_0 = ((struct struct_6){0, 0});
	struct struct_6* _102_retval = _0;
// AST_IFELSE
// test/leetcode.orng:63
	signed int _1 = test_leetcode_convertToList_i;
	signed int _2 = 10;
	bool _3 = _1 < _2;
	if (!_3) goto else_103;
// AST_ASSIGN
// test/leetcode.orng:64
	signed int _4 = test_leetcode_convertToList_i;
	void* _5 = 0;
	struct struct_6 _6 = {_4, _5};
	*_102_retval = _6;
continue_103:;
	goto end_103;
else_103:;
// AST_ASSIGN
// test/leetcode.orng:66
	signed int _7 = test_leetcode_convertToList_i;
	signed int _8 = 10;
	signed int _9 = _7 % _8;
	signed int _10 = test_leetcode_convertToList_i;
	signed int _11 = 10;
	signed int _12 = _10 / _11;
	struct struct_6* _13 = test_leetcode_convertToList(_12);
	struct struct_6 _14 = {_9, _13};
	*_102_retval = _14;
continue_104:;
end_103:;
// AST_RETURN
// test/leetcode.orng:68
	struct struct_6* _15 = _102_retval;
	retval = _15;
	goto return_block_102;
continue_102:;
return_block_102:;
    return retval;
}
struct struct_6* test_leetcode_addTwoNumbers(struct struct_6* test_leetcode_addTwoNumbers_l1, struct struct_6* test_leetcode_addTwoNumbers_l2)
{
	struct struct_6* retval;
// AST_RETURN
// test/leetcode.orng:71
	signed int _0 = test_leetcode_convertToInt(test_leetcode_addTwoNumbers_l1);
	signed int _1 = test_leetcode_convertToInt(test_leetcode_addTwoNumbers_l2);
	signed int _2 = _0 + _1;
	struct struct_6* _3 = test_leetcode_convertToList(_2);
	retval = _3;
	goto return_block_105;
continue_105:;
return_block_105:;
    return retval;
}
void test_leetcode_test_addTwoNumbers()
{// AST_DEFINE
// test/leetcode.orng:75
	struct struct_6* _0 = calloc(sizeof(struct struct_6), 1);
	*_0 = ((struct struct_6){0, 0});
	struct struct_6* _106_l1_c = _0;
// AST_ASSIGN
// test/leetcode.orng:76
	signed int _1 = 3;
	void* _2 = 0;
	struct struct_6 _3 = {_1, _2};
	*_106_l1_c = _3;
// AST_DEFINE
// test/leetcode.orng:77
	struct struct_6* _4 = calloc(sizeof(struct struct_6), 1);
	*_4 = ((struct struct_6){0, 0});
	struct struct_6* _106_l1_b = _4;
// AST_ASSIGN
// test/leetcode.orng:78
	signed int _5 = 4;
	struct struct_6* _6 = _106_l1_c;
	struct struct_6 _7 = {_5, _6};
	*_106_l1_b = _7;
// AST_DEFINE
// test/leetcode.orng:79
	struct struct_6* _8 = calloc(sizeof(struct struct_6), 1);
	*_8 = ((struct struct_6){0, 0});
	struct struct_6* _106_l1 = _8;
// AST_ASSIGN
// test/leetcode.orng:80
	signed int _9 = 2;
	struct struct_6* _10 = _106_l1_b;
	struct struct_6 _11 = {_9, _10};
	*_106_l1 = _11;
// AST_DEFINE
// test/leetcode.orng:81
	struct struct_6* _12 = calloc(sizeof(struct struct_6), 1);
	*_12 = ((struct struct_6){0, 0});
	struct struct_6* _106_l2_c = _12;
// AST_ASSIGN
// test/leetcode.orng:82
	signed int _13 = 4;
	void* _14 = 0;
	struct struct_6 _15 = {_13, _14};
	*_106_l2_c = _15;
// AST_DEFINE
// test/leetcode.orng:83
	struct struct_6* _16 = calloc(sizeof(struct struct_6), 1);
	*_16 = ((struct struct_6){0, 0});
	struct struct_6* _106_l2_b = _16;
// AST_ASSIGN
// test/leetcode.orng:84
	signed int _17 = 6;
	struct struct_6* _18 = _106_l2_c;
	struct struct_6 _19 = {_17, _18};
	*_106_l2_b = _19;
// AST_DEFINE
// test/leetcode.orng:85
	struct struct_6* _20 = calloc(sizeof(struct struct_6), 1);
	*_20 = ((struct struct_6){0, 0});
	struct struct_6* _106_l2 = _20;
// AST_ASSIGN
// test/leetcode.orng:86
	signed int _21 = 5;
	struct struct_6* _22 = _106_l2_b;
	struct struct_6 _23 = {_21, _22};
	*_106_l2 = _23;
// AST_DEFINE
// test/leetcode.orng:88
	struct struct_6* _24 = test_leetcode_addTwoNumbers(_106_l1, _106_l2);
	struct struct_6* _106_ans = _24;
// AST_IFELSE
// test/leetcode.orng:90
	struct struct_6* _25 = _106_ans;
	signed int _26 = _25->val;
	signed int _27 = 7;
	bool _28 = _26 == _27;
	struct struct_6* _29 = _106_ans;
	struct struct_6* _30 = _29->next;
	signed int _31 = _30->val;
	signed int _32 = 0;
	bool _33 = _31 == _32;
	bool _34 = _28 && _33;
	struct struct_6* _35 = _106_ans;
	struct struct_6* _36 = _35->next;
	struct struct_6* _37 = _36->next;
	signed int _38 = _37->val;
	signed int _39 = 8;
	bool _40 = _38 == _39;
	bool _41 = _34 && _40;
	if (!_41) goto else_107;
// AST_CALL
// test/leetcode.orng:91
	struct struct_1* _42 = &string_2;
	signed int _43 = stdlib_system_println(_42);
continue_107:;
	goto end_107;
else_107:;
// AST_CALL
// test/leetcode.orng:93
	struct struct_1* _44 = &string_3;
	signed int _45 = stdlib_system_println(_44);
continue_108:;
end_107:;
continue_106:;
}
bool test_leetcode_areDistinct(struct struct_1* test_leetcode_areDistinct_str, signed int test_leetcode_areDistinct_i, signed int test_leetcode_areDistinct_j)
{
	bool retval;
// AST_DEFINE
// test/leetcode.orng:101
	struct struct_7 _109_visited = ((struct struct_7){256, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
// AST_FOR
// test/leetcode.orng:102
	signed int _0 = test_leetcode_areDistinct_i;
	signed int _110_k = _0;
begin_110:;
	signed int _1 = _110_k;
	signed int _2 = test_leetcode_areDistinct_j;
	bool _3 = _1 <= _2;
	if (!_3) goto end_110;
// AST_DEFINE
// test/leetcode.orng:103
	signed int _4 = _110_k;
	struct struct_1* _5 = test_leetcode_areDistinct_str;
	signed char _6 = _5->data[_4];
	signed int _7 = (signed int)_6;
	signed int _110_charCode = _7;
// AST_IF
// test/leetcode.orng:104
	signed int _8 = _110_charCode;
	bool _9 = _109_visited.data[_8];
	if (!_9) goto end_111;
// AST_RETURN
// test/leetcode.orng:105
	bool _10 = 0;
	retval = _10;
	goto return_block_109;
continue_111:;
end_111:;
// AST_ASSIGN
// test/leetcode.orng:107
	bool _11 = 1;
	signed int _12 = _110_charCode;
	_109_visited.data[_12] = _11;
continue_110:;
	signed int _13 = 1;
	_110_k += _13;
	goto begin_110;
end_110:;
// AST_RETURN
// test/leetcode.orng:109
	bool _14 = 1;
	retval = _14;
	goto return_block_109;
continue_109:;
return_block_109:;
    return retval;
}
signed int test_leetcode_lengthOfLongestSubstring(struct struct_1* test_leetcode_lengthOfLongestSubstring_str)
{
	signed int retval;
// AST_DEFINE
// test/leetcode.orng:115
	struct struct_1* _0 = test_leetcode_lengthOfLongestSubstring_str;
	signed int _1 = _0->length;
	signed int _112_n = _1;
// AST_DEFINE
// test/leetcode.orng:116
	signed int _2 = 0;
	signed int _112_res = _2;
// AST_FOR
// test/leetcode.orng:120
	signed int _3 = 0;
	signed int _113_i = _3;
begin_113:;
	signed int _4 = _113_i;
	signed int _5 = _112_n;
	bool _6 = _4 < _5;
	if (!_6) goto end_113;
// AST_FOR
// test/leetcode.orng:121
	signed int _7 = _113_i;
	signed int _114_j = _7;
begin_114:;
	signed int _8 = _114_j;
	signed int _9 = _112_n;
	bool _10 = _8 < _9;
	if (!_10) goto end_114;
// AST_IF
// test/leetcode.orng:122
	bool _11 = test_leetcode_areDistinct(test_leetcode_lengthOfLongestSubstring_str, _113_i, _114_j);
	if (!_11) goto end_115;
// AST_ASSIGN
// test/leetcode.orng:123
	signed int _12 = _114_j;
	signed int _13 = _113_i;
	signed int _14 = _12 - _13;
	signed int _15 = 1;
	signed int _16 = _14 + _15;
	double _17 = stdlib_math_max(_112_res, _16);
	signed int _18 = (signed int)_17;
	_112_res = _18;
continue_115:;
end_115:;
continue_114:;
	signed int _19 = 1;
	_114_j += _19;
	goto begin_114;
end_114:;
continue_113:;
	signed int _20 = 1;
	_113_i += _20;
	goto begin_113;
end_113:;
// AST_RETURN
// test/leetcode.orng:128
	signed int _21 = _112_res;
	retval = _21;
	goto return_block_112;
continue_112:;
return_block_112:;
    return retval;
}
void test_leetcode_test_lengthOfLongestSubstring()
{// AST_DEFINE
// test/leetcode.orng:132
	struct struct_1* _0 = &string_4;
	struct struct_1* _116_s = _0;
// AST_DEFINE
// test/leetcode.orng:134
	signed int _1 = test_leetcode_lengthOfLongestSubstring(_116_s);
	signed int _116_ans = _1;
// AST_IFELSE
// test/leetcode.orng:136
	signed int _2 = _116_ans;
	signed int _3 = 3;
	bool _4 = _2 == _3;
	if (!_4) goto else_117;
// AST_CALL
// test/leetcode.orng:137
	struct struct_1* _5 = &string_5;
	signed int _6 = stdlib_system_println(_5);
continue_117:;
	goto end_117;
else_117:;
// AST_CALL
// test/leetcode.orng:139
	struct struct_1* _7 = &string_6;
	signed int _8 = stdlib_system_println(_7, _116_ans);
continue_118:;
end_117:;
continue_116:;
}
float test_leetcode_findMedianSortedArrays(struct struct_3* test_leetcode_findMedianSortedArrays_nums1, struct struct_3* test_leetcode_findMedianSortedArrays_nums2)
{
	float retval;
	int defer_0 = 0;
// AST_DEFINE
// test/leetcode.orng:148
	struct struct_3* _0 = test_leetcode_findMedianSortedArrays_nums1;
	signed int _1 = _0->length;
	struct struct_3* _2 = test_leetcode_findMedianSortedArrays_nums2;
	signed int _3 = _2->length;
	signed int _4 = _1 + _3;
	struct struct_3* _5 = malloc(sizeof(signed int) + sizeof(signed int) * _4);
	_5->length = _4;
	for(int i = 0; i < _4; i++) {_5->data[i] = 0;}
	struct struct_3* _119_merged = _5;
// AST_DEFER
// test/leetcode.orng:149
	defer_0 = 1;
// AST_DEFINE
// test/leetcode.orng:151
	signed int _6 = 0;
	signed int _119_i = _6;
// AST_DEFINE
// test/leetcode.orng:152
	signed int _7 = 0;
	signed int _119_j = _7;
// AST_FOR
// test/leetcode.orng:153
begin_120:;
	signed int _8 = _119_i;
	signed int _9 = _119_j;
	signed int _10 = _8 + _9;
	struct struct_3* _11 = _119_merged;
	signed int _12 = _11->length;
	bool _13 = _10 < _12;
	if (!_13) goto end_120;
// AST_IFELSE
// test/leetcode.orng:154
	signed int _14 = _119_i;
	struct struct_3* _15 = test_leetcode_findMedianSortedArrays_nums1;
	signed int _16 = _15->length;
	bool _17 = _14 < _16;
	signed int _18 = _119_j;
	struct struct_3* _19 = test_leetcode_findMedianSortedArrays_nums2;
	signed int _20 = _19->length;
	bool _21 = _18 < _20;
	bool _22 = _17 && _21;
	if (!_22) goto else_121;
// AST_IFELSE
// test/leetcode.orng:155
	signed int _23 = _119_i;
	struct struct_3* _24 = test_leetcode_findMedianSortedArrays_nums1;
	signed int _25 = _24->data[_23];
	signed int _26 = _119_j;
	struct struct_3* _27 = test_leetcode_findMedianSortedArrays_nums2;
	signed int _28 = _27->data[_26];
	bool _29 = _25 < _28;
	if (!_29) goto else_122;
// AST_ASSIGN
// test/leetcode.orng:156
	signed int _30 = _119_i;
	struct struct_3* _31 = test_leetcode_findMedianSortedArrays_nums1;
	signed int _32 = _31->data[_30];
	signed int _33 = _119_i;
	signed int _34 = _119_j;
	signed int _35 = _33 + _34;
	struct struct_3* _36 = _119_merged;
	_36->data[_35] = _32;
// AST_ADD_ASSIGN
// test/leetcode.orng:157
	signed int _37 = 1;
	_119_i += _37;
continue_122:;
	goto end_122;
else_122:;
// AST_ASSIGN
// test/leetcode.orng:159
	signed int _38 = _119_j;
	struct struct_3* _39 = test_leetcode_findMedianSortedArrays_nums2;
	signed int _40 = _39->data[_38];
	signed int _41 = _119_i;
	signed int _42 = _119_j;
	signed int _43 = _41 + _42;
	struct struct_3* _44 = _119_merged;
	_44->data[_43] = _40;
// AST_ADD_ASSIGN
// test/leetcode.orng:160
	signed int _45 = 1;
	_119_j += _45;
continue_123:;
end_122:;
continue_121:;
	goto end_121;
else_121:;
	signed int _46 = _119_i;
	struct struct_3* _47 = test_leetcode_findMedianSortedArrays_nums1;
	signed int _48 = _47->length;
	bool _49 = _46 < _48;
	if (!_49) goto else_124;
// AST_ASSIGN
// test/leetcode.orng:163
	signed int _50 = _119_i;
	struct struct_3* _51 = test_leetcode_findMedianSortedArrays_nums1;
	signed int _52 = _51->data[_50];
	signed int _53 = _119_i;
	signed int _54 = _119_j;
	signed int _55 = _53 + _54;
	struct struct_3* _56 = _119_merged;
	_56->data[_55] = _52;
// AST_ADD_ASSIGN
// test/leetcode.orng:164
	signed int _57 = 1;
	_119_i += _57;
continue_124:;
	goto end_124;
else_124:;
	signed int _58 = _119_j;
	struct struct_3* _59 = test_leetcode_findMedianSortedArrays_nums2;
	signed int _60 = _59->length;
	bool _61 = _58 < _60;
	if (!_61) goto end_125;
// AST_ASSIGN
// test/leetcode.orng:166
	signed int _62 = _119_j;
	struct struct_3* _63 = test_leetcode_findMedianSortedArrays_nums2;
	signed int _64 = _63->data[_62];
	signed int _65 = _119_i;
	signed int _66 = _119_j;
	signed int _67 = _65 + _66;
	struct struct_3* _68 = _119_merged;
	_68->data[_67] = _64;
// AST_ADD_ASSIGN
// test/leetcode.orng:167
	signed int _69 = 1;
	_119_j += _69;
continue_125:;
end_125:;
end_124:;
end_121:;
continue_120:;
	goto begin_120;
end_120:;
// AST_IFELSE
// test/leetcode.orng:171
	struct struct_3* _70 = _119_merged;
	signed int _71 = _70->length;
	signed int _72 = 2;
	signed int _73 = _71 % _72;
	signed int _74 = 0;
	bool _75 = _73 == _74;
	if (!_75) goto else_126;
// AST_RETURN
// test/leetcode.orng:172
	struct struct_3* _76 = _119_merged;
	signed int _77 = _76->length;
	signed int _78 = 2;
	signed int _79 = _77 / _78;
	struct struct_3* _80 = _119_merged;
	signed int _81 = _80->data[_79];
	struct struct_3* _82 = _119_merged;
	signed int _83 = _82->length;
	signed int _84 = 2;
	signed int _85 = _83 / _84;
	signed int _86 = 1;
	signed int _87 = _85 + _86;
	struct struct_3* _88 = _119_merged;
	signed int _89 = _88->data[_87];
	signed int _90 = _81 + _89;
	signed int _91 = _90;
	float _92 = 2.000000;
	signed int _93 = _91 / _92;
	retval = _93;
	goto return_block_119;
continue_126:;
	goto end_126;
else_126:;
// AST_RETURN
// test/leetcode.orng:174
	struct struct_3* _94 = _119_merged;
	signed int _95 = _94->length;
	signed int _96 = 2;
	signed int _97 = _95 / _96;
	struct struct_3* _98 = _119_merged;
	signed int _99 = _98->data[_97];
	float _100 = (float)_99;
	retval = _100;
	goto return_block_119;
continue_127:;
end_126:;
continue_119:;
	if (defer_0) {
	struct struct_3* _101 = _119_merged;
	free(_101);
	}
return_block_119:;
	if (defer_0) {
	struct struct_3* _102 = _119_merged;
	free(_102);
	}
    return retval;
}
void test_leetcode_test_findMedianSortedArrays()
{// AST_DEFINE
// test/leetcode.orng:179
	signed int _0 = 1;
	signed int _1 = 3;
	struct struct_4 _2 = {2, {_0, _1}};
	struct struct_4 _128_nums1 = _2;
// AST_DEFINE
// test/leetcode.orng:180
	signed int _3 = 2;
	struct struct_8 _4 = {1, {_3}};
	struct struct_8 _128_nums2 = _4;
// AST_DEFINE
// test/leetcode.orng:182
	struct struct_4 _5 = _128_nums1;
	struct struct_4* _6 = &_5;
	struct struct_8 _7 = _128_nums2;
	struct struct_8* _8 = &_7;
	float _9 = test_leetcode_findMedianSortedArrays(_6, _8);
	float _128_ans = _9;
// AST_IFELSE
// test/leetcode.orng:184
	float _10 = _128_ans;
	signed int _11 = 2;
	bool _12 = _10 == _11;
	if (!_12) goto else_129;
// AST_CALL
// test/leetcode.orng:185
	struct struct_1* _13 = &string_7;
	signed int _14 = stdlib_system_println(_13);
continue_129:;
	goto end_129;
else_129:;
// AST_CALL
// test/leetcode.orng:187
	struct struct_1* _15 = &string_8;
	signed int _16 = stdlib_system_println(_15);
continue_130:;
end_129:;
continue_128:;
}
struct struct_1* test_leetcode_longestPalindrome(struct struct_1* test_leetcode_longestPalindrome_s)
{
	struct struct_1* retval;
// AST_DEFINE
// test/leetcode.orng:195
// AST_DEFINE
// test/leetcode.orng:205
	signed int _0 = 0;
	signed int _131_start = _0;
// AST_DEFINE
// test/leetcode.orng:206
	signed int _1 = 0;
	signed int _131_end = _1;
// AST_FOR
// test/leetcode.orng:207
	signed int _2 = 0;
	signed int _134_i = _2;
begin_134:;
	signed int _3 = _134_i;
	struct struct_1* _4 = test_leetcode_longestPalindrome_s;
	signed int _5 = _4->length;
	bool _6 = _3 < _5;
	if (!_6) goto end_134;
// AST_DEFINE
// test/leetcode.orng:208
	signed int _7 = test_leetcode_expandAroundCenter(test_leetcode_longestPalindrome_s, _134_i, _134_i);
	signed int _134_len1 = _7;
// AST_DEFINE
// test/leetcode.orng:209
	signed int _8 = _134_i;
	signed int _9 = 1;
	signed int _10 = _8 + _9;
	signed int _11 = test_leetcode_expandAroundCenter(test_leetcode_longestPalindrome_s, _134_i, _10);
	signed int _134_len2 = _11;
// AST_DEFINE
// test/leetcode.orng:210
	double _12 = stdlib_math_max(_134_len1, _134_len2);
	double _134_len = _12;
// AST_IF
// test/leetcode.orng:211
	double _13 = _134_len;
	signed int _14 = _131_end;
	signed int _15 = _131_start;
	signed int _16 = _14 - _15;
	bool _17 = _13 > _16;
	if (!_17) goto end_135;
// AST_ASSIGN
// test/leetcode.orng:212
	signed int _18 = _134_i;
	double _19 = _134_len;
	signed int _20 = 1;
	double _21 = _19 - _20;
	double _22 = _21;
	signed int _23 = 2;
	double _24 = _22 / _23;
	signed int _25 = _18 - _24;
	_131_start = _25;
// AST_ASSIGN
// test/leetcode.orng:213
	signed int _26 = _134_i;
	double _27 = _134_len;
	signed int _28 = 2;
	double _29 = _27 / _28;
	signed int _30 = _26 + _29;
	_131_end = _30;
continue_135:;
end_135:;
continue_134:;
	signed int _31 = 1;
	_134_i += _31;
	goto begin_134;
end_134:;
// AST_RETURN
// test/leetcode.orng:216
	signed int _32 = _131_end;
	signed int _33 = 1;
	signed int _34 = _32 + _33;
	struct struct_1* _35 = stdlib_string_substring(test_leetcode_longestPalindrome_s, _131_start, _34);
	retval = _35;
	goto return_block_131;
continue_131:;
return_block_131:;
    return retval;
}
signed int test_leetcode_expandAroundCenter(struct struct_1* test_leetcode_expandAroundCenter_s, signed int test_leetcode_expandAroundCenter_left, signed int test_leetcode_expandAroundCenter_right)
{
	signed int retval;
// AST_DEFINE
// test/leetcode.orng:196
	signed int _0 = test_leetcode_expandAroundCenter_left;
	signed int _132_L = _0;
// AST_DEFINE
// test/leetcode.orng:197
	signed int _1 = test_leetcode_expandAroundCenter_right;
	signed int _132_R = _1;
// AST_FOR
// test/leetcode.orng:198
begin_133:;
	signed int _2 = _132_L;
	signed int _3 = 0;
	bool _4 = _2 >= _3;
	signed int _5 = _132_R;
	struct struct_1* _6 = test_leetcode_expandAroundCenter_s;
	signed int _7 = _6->length;
	bool _8 = _5 < _7;
	bool _9 = _4 && _8;
	signed int _10 = _132_L;
	struct struct_1* _11 = test_leetcode_expandAroundCenter_s;
	signed char _12 = _11->data[_10];
	signed int _13 = _132_R;
	struct struct_1* _14 = test_leetcode_expandAroundCenter_s;
	signed char _15 = _14->data[_13];
	bool _16 = _12 == _15;
	bool _17 = _9 && _16;
	if (!_17) goto end_133;
// AST_SUB_ASSIGN
// test/leetcode.orng:199
	signed int _18 = 1;
	_132_L -= _18;
// AST_ADD_ASSIGN
// test/leetcode.orng:200
	signed int _19 = 1;
	_132_R += _19;
continue_133:;
	goto begin_133;
end_133:;
// AST_RETURN
// test/leetcode.orng:202
	signed int _20 = _132_R;
	signed int _21 = _132_L;
	signed int _22 = _20 - _21;
	signed int _23 = 1;
	signed int _24 = _22 - _23;
	retval = _24;
	goto return_block_132;
continue_132:;
return_block_132:;
    return retval;
}
void test_leetcode_test_longestPalindrome()
{// AST_DEFINE
// test/leetcode.orng:220
	struct struct_1* _0 = &string_9;
	struct struct_1* _136_s = _0;
// AST_DEFINE
// test/leetcode.orng:222
	struct struct_1* _1 = test_leetcode_longestPalindrome(_136_s);
	struct struct_1* _136_ans = _1;
// AST_IFELSE
// test/leetcode.orng:224
	struct struct_1* _2 = &string_10;
	bool _3 = stdlib_string_equals(_136_ans, _2);
	struct struct_1* _4 = &string_11;
	bool _5 = stdlib_string_equals(_136_ans, _4);
	bool _6 = _3 || _5;
	if (!_6) goto else_137;
// AST_CALL
// test/leetcode.orng:225
	struct struct_1* _7 = &string_12;
	signed int _8 = stdlib_system_println(_7);
continue_137:;
	goto end_137;
else_137:;
// AST_CALL
// test/leetcode.orng:227
	struct struct_1* _9 = &string_13;
	signed int _10 = stdlib_system_println(_9);
continue_138:;
end_137:;
continue_136:;
}
struct struct_1* test_leetcode_convert(struct struct_1* test_leetcode_convert_s, signed int test_leetcode_convert_numRows)
{
	struct struct_1* retval;
	int defer_0 = 0;
// AST_DEFINE
// test/leetcode.orng:236
	struct struct_1* _0 = test_leetcode_convert_s;
	signed int _1 = _0->length;
	struct struct_2* _2 = malloc(sizeof(signed int) + sizeof(struct struct_1*) * _1);
	_2->length = _1;
	for(int i = 0; i < _1; i++) {_2->data[i] = 0;}
	struct struct_2* _139_board = _2;
// AST_FOR
// test/leetcode.orng:237
	signed int _3 = 0;
	signed int _140_i = _3;
begin_140:;
	signed int _4 = _140_i;
	struct struct_1* _5 = test_leetcode_convert_s;
	signed int _6 = _5->length;
	bool _7 = _4 < _6;
	if (!_7) goto end_140;
// AST_ASSIGN
// test/leetcode.orng:238
	signed int _8 = test_leetcode_convert_numRows;
	struct struct_1* _9 = malloc(sizeof(signed int) + sizeof(signed char) * _8);
	_9->length = _8;
	for(int i = 0; i < _8; i++) {_9->data[i] = 0;}
	signed int _10 = _140_i;
	struct struct_2* _11 = _139_board;
	_11->data[_10] = _9;
continue_140:;
	signed int _12 = 1;
	_140_i += _12;
	goto begin_140;
end_140:;
// AST_DEFER
// test/leetcode.orng:240
	defer_0 = 1;
// AST_DEFINE
// test/leetcode.orng:247
	signed int _13 = 0;
	signed int _139_x = _13;
// AST_DEFINE
// test/leetcode.orng:248
	signed int _14 = 0;
	signed int _139_y = _14;
// AST_DEFINE
// test/leetcode.orng:249
	bool _15 = 0;
	bool _139_diagnolizing = _15;
// AST_FOR
// test/leetcode.orng:250
	signed int _16 = 0;
	signed int _143_i = _16;
begin_143:;
	signed int _17 = _143_i;
	struct struct_1* _18 = test_leetcode_convert_s;
	signed int _19 = _18->length;
	bool _20 = _17 < _19;
	if (!_20) goto end_143;
// AST_ASSIGN
// test/leetcode.orng:251
	signed int _21 = _143_i;
	struct struct_1* _22 = test_leetcode_convert_s;
	signed char _23 = _22->data[_21];
	signed int _24 = _139_y;
	signed int _25 = _139_x;
	struct struct_2* _26 = _139_board;
	struct struct_1* _27 = _26->data[_25];
	_27->data[_24] = _23;
// AST_IFELSE
// test/leetcode.orng:252
	bool _28 = _139_diagnolizing;
	if (!_28) goto else_144;
// AST_SUB_ASSIGN
// test/leetcode.orng:253
	signed int _29 = 1;
	_139_y -= _29;
// AST_ADD_ASSIGN
// test/leetcode.orng:254
	signed int _30 = 1;
	_139_x += _30;
// AST_IF
// test/leetcode.orng:255
	signed int _31 = _139_y;
	signed int _32 = 0;
	bool _33 = _31 == _32;
	if (!_33) goto end_145;
// AST_ASSIGN
// test/leetcode.orng:256
	bool _34 = 0;
	_139_diagnolizing = _34;
continue_145:;
end_145:;
continue_144:;
	goto end_144;
else_144:;
// AST_ADD_ASSIGN
// test/leetcode.orng:259
	signed int _35 = 1;
	_139_y += _35;
// AST_IF
// test/leetcode.orng:260
	signed int _36 = _139_y;
	signed int _37 = test_leetcode_convert_numRows;
	bool _38 = _36 == _37;
	if (!_38) goto end_147;
// AST_ASSIGN
// test/leetcode.orng:261
	bool _39 = 1;
	_139_diagnolizing = _39;
// AST_SUB_ASSIGN
// test/leetcode.orng:262
	signed int _40 = 2;
	_139_y -= _40;
// AST_ADD_ASSIGN
// test/leetcode.orng:263
	signed int _41 = 1;
	_139_x += _41;
continue_147:;
end_147:;
continue_146:;
end_144:;
continue_143:;
	signed int _42 = 1;
	_143_i += _42;
	goto begin_143;
end_143:;
// AST_DEFINE
// test/leetcode.orng:268
	struct struct_1* _43 = test_leetcode_convert_s;
	signed int _44 = _43->length;
	struct struct_1* _45 = malloc(sizeof(signed int) + sizeof(signed char) * _44);
	_45->length = _44;
	for(int i = 0; i < _44; i++) {_45->data[i] = 0;}
	struct struct_1* _139_retval = _45;
// AST_DEFINE
// test/leetcode.orng:269
	signed int _46 = 0;
	signed int _139_k = _46;
// AST_FOR
// test/leetcode.orng:270
	signed int _47 = 0;
	signed int _148_j = _47;
begin_148:;
	signed int _48 = _148_j;
	signed int _49 = test_leetcode_convert_numRows;
	bool _50 = _48 < _49;
	if (!_50) goto end_148;
// AST_FOR
// test/leetcode.orng:271
	signed int _51 = 0;
	signed int _149_i = _51;
begin_149:;
	signed int _52 = _149_i;
	struct struct_1* _53 = test_leetcode_convert_s;
	signed int _54 = _53->length;
	bool _55 = _52 < _54;
	if (!_55) goto end_149;
// AST_IF
// test/leetcode.orng:272
	signed int _56 = _148_j;
	signed int _57 = _149_i;
	struct struct_2* _58 = _139_board;
	struct struct_1* _59 = _58->data[_57];
	signed char _60 = _59->data[_56];
	signed char _61 = '\0';
	bool _62 = _60 != _61;
	if (!_62) goto end_150;
// AST_ASSIGN
// test/leetcode.orng:273
	signed int _63 = _148_j;
	signed int _64 = _149_i;
	struct struct_2* _65 = _139_board;
	struct struct_1* _66 = _65->data[_64];
	signed char _67 = _66->data[_63];
	signed int _68 = _139_k;
	struct struct_1* _69 = _139_retval;
	_69->data[_68] = _67;
// AST_ADD_ASSIGN
// test/leetcode.orng:274
	signed int _70 = 1;
	_139_k += _70;
continue_150:;
end_150:;
continue_149:;
	signed int _71 = 1;
	_149_i += _71;
	goto begin_149;
end_149:;
continue_148:;
	signed int _72 = 1;
	_148_j += _72;
	goto begin_148;
end_148:;
// AST_RETURN
// test/leetcode.orng:279
	struct struct_1* _73 = _139_retval;
	retval = _73;
	goto return_block_139;
continue_139:;
	if (defer_0) {
// AST_FOR
// test/leetcode.orng:241
	signed int _74 = 0;
	signed int _180_i = _74;
begin_180:;
	signed int _75 = _180_i;
	struct struct_1* _76 = test_leetcode_convert_s;
	signed int _77 = _76->length;
	bool _78 = _75 < _77;
	if (!_78) goto end_180;
// AST_FREE
// test/leetcode.orng:242
	signed int _79 = _180_i;
	struct struct_2* _80 = _139_board;
	struct struct_1* _81 = _80->data[_79];
	free(_81);
continue_180:;
	signed int _82 = 1;
	_180_i += _82;
	goto begin_180;
end_180:;
// AST_FREE
// test/leetcode.orng:244
	struct struct_2* _83 = _139_board;
	free(_83);
continue_179:;
	}
return_block_139:;
	if (defer_0) {
// AST_FOR
// test/leetcode.orng:241
	signed int _84 = 0;
	signed int _182_i = _84;
begin_182:;
	signed int _85 = _182_i;
	struct struct_1* _86 = test_leetcode_convert_s;
	signed int _87 = _86->length;
	bool _88 = _85 < _87;
	if (!_88) goto end_182;
// AST_FREE
// test/leetcode.orng:242
	signed int _89 = _182_i;
	struct struct_2* _90 = _139_board;
	struct struct_1* _91 = _90->data[_89];
	free(_91);
continue_182:;
	signed int _92 = 1;
	_182_i += _92;
	goto begin_182;
end_182:;
// AST_FREE
// test/leetcode.orng:244
	struct struct_2* _93 = _139_board;
	free(_93);
continue_181:;
	}
    return retval;
}
void test_leetcode_test_convert()
{// AST_DEFINE
// test/leetcode.orng:283
	struct struct_1* _0 = &string_14;
	signed int _1 = 3;
	struct struct_1* _2 = test_leetcode_convert(_0, _1);
	struct struct_1* _151_ans = _2;
// AST_IFELSE
// test/leetcode.orng:285
	struct struct_1* _3 = &string_15;
	bool _4 = stdlib_string_equals(_151_ans, _3);
	if (!_4) goto else_152;
// AST_CALL
// test/leetcode.orng:286
	struct struct_1* _5 = &string_16;
	signed int _6 = stdlib_system_println(_5);
continue_152:;
	goto end_152;
else_152:;
// AST_CALL
// test/leetcode.orng:288
	struct struct_1* _7 = &string_17;
	signed int _8 = stdlib_system_println(_7);
continue_153:;
end_152:;
continue_151:;
}
struct struct_6* test_leetcode_reverseList(struct struct_6* test_leetcode_reverseList_list)
{
	struct struct_6* retval;
// AST_DEFINE
// test/leetcode.orng:298
	struct struct_6* _0 = 0;
	struct struct_6* _154_prev = _0;
// AST_DEFINE
// test/leetcode.orng:299
	struct struct_6* _1 = test_leetcode_reverseList_list;
	struct struct_6* _154_curr = _1;
// AST_DEFINE
// test/leetcode.orng:300
	struct struct_6* _2 = 0;
	struct struct_6* _154_next = _2;
// AST_FOR
// test/leetcode.orng:301
begin_155:;
	struct struct_6* _3 = _154_curr;
	void* _4 = 0;
	bool _5 = _3 != _4;
	if (!_5) goto end_155;
// AST_ASSIGN
// test/leetcode.orng:302
	struct struct_6* _6 = _154_curr;
	struct struct_6* _7 = _6->next;
	_154_next = _7;
// AST_ASSIGN
// test/leetcode.orng:303
	struct struct_6* _8 = _154_prev;
	_154_curr->next = _8;
// AST_ASSIGN
// test/leetcode.orng:304
	struct struct_6* _9 = _154_curr;
	_154_prev = _9;
// AST_ASSIGN
// test/leetcode.orng:305
	struct struct_6* _10 = _154_next;
	_154_curr = _10;
continue_155:;
	goto begin_155;
end_155:;
// AST_ASSIGN
// test/leetcode.orng:307
	struct struct_6* _11 = _154_prev;
	test_leetcode_reverseList_list = _11;
// AST_RETURN
// test/leetcode.orng:308
	struct struct_6* _12 = test_leetcode_reverseList_list;
	retval = _12;
	goto return_block_154;
continue_154:;
return_block_154:;
    return retval;
}
signed int test_leetcode_reverse(signed int test_leetcode_reverse_x)
{
	signed int retval;
// AST_RETURN
// test/leetcode.orng:310
	struct struct_6* _0 = test_leetcode_convertToList(test_leetcode_reverse_x);
	struct struct_6* _1 = test_leetcode_reverseList(_0);
	signed int _2 = test_leetcode_convertToInt(_1);
	retval = _2;
	goto return_block_156;
continue_156:;
return_block_156:;
    return retval;
}
void test_leetcode_test_reverse()
{// AST_DEFINE
// test/leetcode.orng:313
	signed int _0 = 123;
	signed int _1 = test_leetcode_reverse(_0);
	signed int _157_ans = _1;
// AST_IFELSE
// test/leetcode.orng:315
	signed int _2 = _157_ans;
	signed int _3 = 321;
	bool _4 = _2 == _3;
	if (!_4) goto else_158;
// AST_CALL
// test/leetcode.orng:316
	struct struct_1* _5 = &string_18;
	signed int _6 = stdlib_system_println(_5);
continue_158:;
	goto end_158;
else_158:;
// AST_CALL
// test/leetcode.orng:318
	struct struct_1* _7 = &string_19;
	signed int _8 = stdlib_system_println(_7);
continue_159:;
end_158:;
continue_157:;
}
signed int test_leetcode_myAtoi(struct struct_1* test_leetcode_myAtoi_s)
{
	signed int retval;
// AST_DEFINE
// test/leetcode.orng:327
	signed int _0 = 0;
	signed int _160_x = _0;
// AST_DEFINE
// test/leetcode.orng:328
	signed int _1 = 0;
	signed int _160_i = _1;
// AST_DEFINE
// test/leetcode.orng:329
	bool _2 = 1;
	bool _160_sign = _2;
// AST_FOR
// test/leetcode.orng:332
begin_161:;
	signed int _3 = _160_i;
	struct struct_1* _4 = test_leetcode_myAtoi_s;
	signed int _5 = _4->length;
	bool _6 = _3 < _5;
	signed int _7 = _160_i;
	struct struct_1* _8 = test_leetcode_myAtoi_s;
	signed char _9 = _8->data[_7];
	signed char _10 = ' ';
	bool _11 = _9 == _10;
	bool _12 = _6 && _11;
	if (!_12) goto end_161;
// AST_ADD_ASSIGN
// test/leetcode.orng:332
	signed int _13 = 1;
	_160_i += _13;
continue_161:;
	goto begin_161;
end_161:;
// AST_IFELSE
// test/leetcode.orng:335
	signed int _14 = _160_i;
	struct struct_1* _15 = test_leetcode_myAtoi_s;
	signed int _16 = _15->length;
	bool _17 = _14 == _16;
	if (!_17) goto else_162;
// AST_RETURN
// test/leetcode.orng:336
	signed int _18 = 0;
	retval = _18;
	goto return_block_160;
continue_162:;
	goto end_162;
else_162:;
	signed int _19 = _160_i;
	struct struct_1* _20 = test_leetcode_myAtoi_s;
	signed char _21 = _20->data[_19];
	signed char _22 = '+';
	bool _23 = _21 == _22;
	if (!_23) goto else_163;
// AST_ASSIGN
// test/leetcode.orng:338
	bool _24 = 1;
	_160_sign = _24;
// AST_ADD_ASSIGN
// test/leetcode.orng:339
	signed int _25 = 1;
	_160_i += _25;
continue_163:;
	goto end_163;
else_163:;
	signed int _26 = _160_i;
	struct struct_1* _27 = test_leetcode_myAtoi_s;
	signed char _28 = _27->data[_26];
	signed char _29 = '-';
	bool _30 = _28 == _29;
	if (!_30) goto end_164;
// AST_ASSIGN
// test/leetcode.orng:341
	bool _31 = 0;
	_160_sign = _31;
// AST_ADD_ASSIGN
// test/leetcode.orng:342
	signed int _32 = 1;
	_160_i += _32;
continue_164:;
end_164:;
end_163:;
end_162:;
// AST_FOR
// test/leetcode.orng:346
begin_165:;
	signed int _33 = _160_i;
	struct struct_1* _34 = test_leetcode_myAtoi_s;
	signed int _35 = _34->length;
	bool _36 = _33 < _35;
	signed int _37 = _160_i;
	struct struct_1* _38 = test_leetcode_myAtoi_s;
	signed char _39 = _38->data[_37];
	bool _40 = isdigit(_39);
	bool _41 = _36 && _40;
	if (!_41) goto end_165;
// AST_ASSIGN
// test/leetcode.orng:347
	signed int _42 = _160_x;
	signed int _43 = 10;
	signed int _44 = _42 * _43;
	signed int _45 = _160_i;
	struct struct_1* _46 = test_leetcode_myAtoi_s;
	signed char _47 = _46->data[_45];
	signed int _48 = (signed int)_47;
	signed int _49 = _44 + _48;
	signed char _50 = '0';
	signed int _51 = (signed int)_50;
	signed int _52 = _49 - _51;
	_160_x = _52;
continue_165:;
	signed int _53 = 1;
	_160_i += _53;
	goto begin_165;
end_165:;
// AST_RETURN
// test/leetcode.orng:350
	bool _54 = _160_sign;
	signed int _55 = _160_x;
	signed int _56 = _160_x;
	signed int _57 = -_56;
	signed int _58 = _54 ? _55 : _57;
	retval = _58;
	goto return_block_160;
continue_160:;
return_block_160:;
    return retval;
}
void test_leetcode_test_myAtoi()
{// AST_DEFINE
// test/leetcode.orng:354
	struct struct_1* _0 = &string_20;
	struct struct_1* _166_s = _0;
// AST_DEFINE
// test/leetcode.orng:356
	signed int _1 = test_leetcode_myAtoi(_166_s);
	signed int _166_ans = _1;
// AST_IFELSE
// test/leetcode.orng:358
	signed int _2 = _166_ans;
	signed int _3 = 42;
	bool _4 = _2 == _3;
	if (!_4) goto else_167;
// AST_CALL
// test/leetcode.orng:359
	struct struct_1* _5 = &string_21;
	signed int _6 = stdlib_system_println(_5);
continue_167:;
	goto end_167;
else_167:;
// AST_CALL
// test/leetcode.orng:361
	struct struct_1* _7 = &string_22;
	signed int _8 = stdlib_system_println(_7);
continue_168:;
end_167:;
continue_166:;
}
signed int test_testModule_main(struct struct_2* test_testModule_main_args)
{
	signed int retval;
// AST_CALL
// test/testModule.orng:3
	test_leetcode_test_all();
// AST_RETURN
// test/testModule.orng:4
	signed int _0 = 0;
	retval = _0;
	goto return_block_178;
continue_178:;
return_block_178:;
    return retval;
}
double stdlib_math_max(double stdlib_math_max_x, double stdlib_math_max_y)
{
	double retval;
// AST_IFELSE
// stdlib/math.orng:9
	double _0 = stdlib_math_max_x;
	double _1 = stdlib_math_max_y;
	bool _2 = _0 > _1;
	if (!_2) goto else_4;
// AST_RETURN
// stdlib/math.orng:10
	double _3 = stdlib_math_max_x;
	retval = _3;
	goto return_block_3;
continue_4:;
	goto end_4;
else_4:;
// AST_RETURN
// stdlib/math.orng:12
	double _4 = stdlib_math_max_y;
	retval = _4;
	goto return_block_3;
continue_5:;
end_4:;
continue_3:;
return_block_3:;
    return retval;
}
bool stdlib_string_equals(struct struct_1* stdlib_string_equals_a, struct struct_1* stdlib_string_equals_b)
{
	bool retval;
// AST_IFELSE
// stdlib/string.orng:30
	struct struct_1* _0 = stdlib_string_equals_a;
	signed int _1 = _0->length;
	struct struct_1* _2 = stdlib_string_equals_b;
	signed int _3 = _2->length;
	bool _4 = _1 != _3;
	if (!_4) goto else_13;
// AST_RETURN
// stdlib/string.orng:31
	bool _5 = 0;
	retval = _5;
	goto return_block_12;
continue_13:;
	goto end_13;
else_13:;
// AST_FOR
// stdlib/string.orng:33
	signed int _6 = 0;
	signed int _15_i = _6;
begin_15:;
	signed int _7 = _15_i;
	struct struct_1* _8 = stdlib_string_equals_a;
	signed int _9 = _8->length;
	bool _10 = _7 < _9;
	if (!_10) goto end_15;
// AST_IF
// stdlib/string.orng:34
	signed int _11 = _15_i;
	struct struct_1* _12 = stdlib_string_equals_a;
	signed char _13 = _12->data[_11];
	signed int _14 = _15_i;
	struct struct_1* _15 = stdlib_string_equals_b;
	signed char _16 = _15->data[_14];
	bool _17 = _13 != _16;
	if (!_17) goto end_16;
// AST_RETURN
// stdlib/string.orng:35
	bool _18 = 0;
	retval = _18;
	goto return_block_12;
continue_16:;
end_16:;
continue_15:;
	signed int _19 = 1;
	_15_i += _19;
	goto begin_15;
end_15:;
// AST_RETURN
// stdlib/string.orng:38
	bool _20 = 1;
	retval = _20;
	goto return_block_12;
continue_14:;
end_13:;
continue_12:;
return_block_12:;
    return retval;
}
struct struct_1* stdlib_string_substring(struct struct_1* stdlib_string_substring_s, signed int stdlib_string_substring_start, signed int stdlib_string_substring_end)
{
	struct struct_1* retval;
// AST_DEFINE
// stdlib/string.orng:43
	signed int _0 = stdlib_string_substring_end;
	signed int _1 = stdlib_string_substring_start;
	signed int _2 = _0 - _1;
	struct struct_1* _3 = malloc(sizeof(signed int) + sizeof(signed char) * _2);
	_3->length = _2;
	for(int i = 0; i < _2; i++) {_3->data[i] = 0;}
	struct struct_1* _17_retval = _3;
// AST_FOR
// stdlib/string.orng:44
	signed int _4 = 0;
	signed int _18_i = _4;
begin_18:;
	signed int _5 = _18_i;
	struct struct_1* _6 = _17_retval;
	signed int _7 = _6->length;
	bool _8 = _5 < _7;
	if (!_8) goto end_18;
// AST_ASSIGN
// stdlib/string.orng:45
	signed int _9 = stdlib_string_substring_start;
	signed int _10 = _18_i;
	signed int _11 = _9 + _10;
	struct struct_1* _12 = stdlib_string_substring_s;
	signed char _13 = _12->data[_11];
	signed int _14 = _18_i;
	struct struct_1* _15 = _17_retval;
	_15->data[_14] = _13;
continue_18:;
	signed int _16 = 1;
	_18_i += _16;
	goto begin_18;
end_18:;
// AST_RETURN
// stdlib/string.orng:47
	struct struct_1* _17 = _17_retval;
	retval = _17;
	goto return_block_17;
continue_17:;
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
