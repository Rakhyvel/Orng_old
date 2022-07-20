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
	int64_t length;
	bool* data;
};

struct struct_7 {
	int64_t length;
	int64_t* data;
};

struct struct_8 {
	int64_t tag;
	union {
		struct struct_9* something;
	};
};

struct struct_9 {
	int64_t val;
	struct struct_8 next;
};

/* Verbatim code */
int std_system_println(struct struct_1 _format, ...) {va_list _25_args;va_start(_25_args, _format.data);int retval = vprintf(_format.data, _25_args);va_end(_25_args);char newLine[2] = {'\n', '\0'};printf(newLine);return retval;}

int64_t test_testModule_main(struct struct_2 _args);
void test_leetcode_test_all();
void test_leetcode_test_twoSum();
struct struct_3 test_leetcode_twoSum(struct struct_3 _nums, int64_t _target);
void test_leetcode_test_lengthOfLongestSubstring();
int64_t test_leetcode_lengthOfLongestSubstring(struct struct_1 _str);
bool test_leetcode_areDistinct(struct struct_1 _str, int64_t _i, int64_t _j);
double std_math_max(double _x, double _y);
void test_leetcode_test_findMedianSortedArrays();
float test_leetcode_findMedianSortedArrays(struct struct_3 _nums1, struct struct_3 _nums2);
void test_leetcode_test_longestPalindrome();
struct struct_1 test_leetcode_longestPalindrome(struct struct_1 _s);
int64_t test_leetcode_expandAroundCenter(struct struct_1 _s, int64_t _left, int64_t _right);
bool std_string_equals(struct struct_1 _a, struct struct_1 _b);
void test_leetcode_test_convert();
struct struct_1 test_leetcode_convert(struct struct_1 _s, int64_t _numRows);

#ifndef ORANGE_PROGRAM_31415
#define ORANGE_PROGRAM_31415

int64_t test_testModule_main(struct struct_2 _args)
{
	int64_t retval;
	void (*_0) ();
	struct struct_2 _args_0;
	_args_0 = _args;
L195:; // incoming:1
	_0 = test_leetcode_test_all;
	_0();
	retval = 0;
	goto end;
end:;
	return retval;
}

void test_leetcode_test_all()
{
	void (*_0) ();
	void (*_2) ();
	void (*_4) ();
	void (*_6) ();
	void (*_8) ();
L193:; // incoming:1
	_0 = test_leetcode_test_twoSum;
	_0();
	_2 = test_leetcode_test_lengthOfLongestSubstring;
	_2();
	_4 = test_leetcode_test_findMedianSortedArrays;
	_4();
	_6 = test_leetcode_test_longestPalindrome;
	_6();
	_8 = test_leetcode_test_convert;
	_8();
	goto end;
end:;
	return;
}

void test_leetcode_test_twoSum()
{
	int64_t _1;
	int64_t _2;
	int64_t _3;
	int64_t _4;
	struct struct_3 _43_nums_0;
	int64_t _43_target_0;
	struct struct_3 (*_6) (struct struct_3 _nums, int64_t _target);
	struct struct_3 _7;
	struct struct_3 _43_ans_0;
	int64_t _8;
	int64_t _9;
	int64_t _10;
	int64_t _11;
	int64_t _12;
	int64_t _13;
	int64_t _14;
	int64_t _15;
	bool _16;
	int64_t (*_17) (struct struct_1 _format, ...);
	struct struct_1 _19;
	int64_t _18;
	int64_t (*_21) (struct struct_1 _format, ...);
	struct struct_1 _23;
	int64_t _24;
	int64_t _25;
	int32_t _26;
	int64_t _27;
	int64_t _28;
	int32_t _29;
	int64_t _22;
	struct struct_3 _43_ans_1;
L14:; // incoming:1
	_1 = 2;
	_2 = 7;
	_3 = 11;
	_4 = 15;
	_43_nums_0 = (struct struct_3) {4, (int64_t[]){_1, _2, _3, _4}};
	_43_target_0 = 9;
	_6 = test_leetcode_twoSum;
	_7 = _6(_43_nums_0, _43_target_0);
	_43_ans_0 = _7;
	_9 = 0;
	_10 = _43_ans_0.data[_9];
	_11 = _43_nums_0.data[_10];
	_12 = 1;
	_13 = _43_ans_0.data[_12];
	_14 = _43_nums_0.data[_13];
	_15 = _11 + _14;
	_16 = _15 == _43_target_0;
	if (!_16) {
		_43_ans_1 = _43_ans_0;
		goto L19;
	} else {
		goto L15;
	}
L15:; // incoming:1
	_17 = std_system_println;
	_19 = (struct struct_1) {15, "twoSum: Passed!"};
	_18 = _17(_19);
	_8 = _18;
	goto L18;
L18:; // incoming:2
	goto end;
L19:; // incoming:1
	_21 = std_system_println;
	_23 = (struct struct_1) {20, "twoSum: Failed %d %d"};
	_24 = 0;
	_25 = _43_ans_1.data[_24];
	_26 = (int32_t) _25;
	_27 = 1;
	_28 = _43_ans_1.data[_27];
	_29 = (int32_t) _28;
	_22 = _21(_23, _26, _29);
	_8 = _22;
	goto L18;
end:;
	return;
}

struct struct_3 test_leetcode_twoSum(struct struct_3 _nums, int64_t _target)
{
	struct struct_3 retval;
	int64_t _38_i_0;
	struct struct_3 _nums_0;
	int64_t _target_0;
	int64_t _1;
	int64_t _2;
	int64_t _3;
	bool _4;
	struct struct_3 _nums_1;
	int64_t _38_i_2;
	int64_t _target_1;
	int64_t _5;
	int64_t _6;
	int64_t _40_j_0;
	int64_t _38_i_3;
	struct struct_3 _nums_2;
	int64_t _target_2;
	int64_t _7;
	bool _8;
	struct struct_3 _nums_3;
	int64_t _40_j_2;
	int64_t _38_i_4;
	int64_t _target_3;
	int64_t _9;
	int64_t _10;
	int64_t _11;
	bool _12;
	struct struct_3 _nums_4;
	int64_t _38_i_5;
	int64_t _40_j_3;
	int64_t _target_4;
	int64_t _14;
	struct struct_3 _15;
	struct struct_3 _13;
	int64_t _38_i_6;
	int64_t _40_j_4;
	int64_t _16;
	int64_t _17;
	int64_t _40_j_1;
	int64_t _40_j_5;
	struct struct_3 _nums_5;
	int64_t _38_i_7;
	int64_t _target_5;
	int64_t _18;
	int64_t _19;
	int64_t _38_i_1;
	int64_t _38_i_8;
	struct struct_3 _nums_6;
	int64_t _target_6;
	int64_t _21;
	int64_t _23;
	int64_t _24;
	struct struct_3 _22;
	struct struct_3 _20;
	_nums_0 = _nums;
	_target_0 = _target;
L0:; // incoming:1
	_38_i_0 = 0;
	_nums_1 = _nums_0;
	_38_i_2 = _38_i_0;
	_target_1 = _target_0;
	goto L1;
L1:; // incoming:2
	_1 = _nums_1.length;
	_2 = 1;
	_3 = _1 - _2;
	_4 = _38_i_2 < _3;
	if (!_4) {
		goto L13;
	} else {
		_38_i_3 = _38_i_2;
		_nums_2 = _nums_1;
		_target_2 = _target_1;
		goto L2;
	}
L2:; // incoming:1
	_5 = 1;
	_6 = _38_i_3 + _5;
	_40_j_0 = _6;
	_nums_3 = _nums_2;
	_40_j_2 = _40_j_0;
	_38_i_4 = _38_i_3;
	_target_3 = _target_2;
	goto L3;
L3:; // incoming:2
	_7 = _nums_3.length;
	_8 = _40_j_2 < _7;
	if (!_8) {
		_38_i_8 = _38_i_4;
		_nums_6 = _nums_3;
		_target_6 = _target_3;
		goto L12;
	} else {
		_nums_4 = _nums_3;
		_38_i_5 = _38_i_4;
		_40_j_3 = _40_j_2;
		_target_4 = _target_3;
		goto L4;
	}
L4:; // incoming:1
	_9 = _nums_4.data[_38_i_5];
	_10 = _nums_4.data[_40_j_3];
	_11 = _9 + _10;
	_12 = _11 == _target_4;
	if (!_12) {
		_40_j_5 = _40_j_3;
		_nums_5 = _nums_4;
		_38_i_7 = _38_i_5;
		_target_5 = _target_4;
		goto L9;
	} else {
		_38_i_6 = _38_i_5;
		_40_j_4 = _40_j_3;
		goto L5;
	}
L5:; // incoming:1
	_14 = 2;
	_15 = (struct struct_3) {2, (int64_t[]){_38_i_6, _40_j_4}};
	_13 = (struct struct_3) {_14, malloc(sizeof(int64_t) * _14)}; for (int i_14 = 0; i_14 < _14; i_14++) {_13.data[i_14] = _15.data[i_14];}
	retval = _13;
	goto end;
L9:; // incoming:1
	_16 = 1;
	_17 = _40_j_5 + _16;
	_40_j_1 = _17;
	_nums_3 = _nums_5;
	_40_j_2 = _40_j_1;
	_38_i_4 = _38_i_7;
	_target_3 = _target_5;
	goto L3;
L12:; // incoming:1
	_18 = 1;
	_19 = _38_i_8 + _18;
	_38_i_1 = _19;
	_nums_1 = _nums_6;
	_38_i_2 = _38_i_1;
	_target_1 = _target_6;
	goto L1;
L13:; // incoming:1
	_21 = 2;
	_23 = -1;
	_24 = -2;
	_22 = (struct struct_3) {2, (int64_t[]){_23, _24}};
	_20 = (struct struct_3) {_21, malloc(sizeof(int64_t) * _21)}; for (int i_21 = 0; i_21 < _21; i_21++) {_20.data[i_21] = _22.data[i_21];}
	retval = _20;
	goto end;
end:;
	return retval;
}

void test_leetcode_test_lengthOfLongestSubstring()
{
	struct struct_1 _0;
	struct struct_1 _63_s_0;
	int64_t (*_1) (struct struct_1 _str);
	int64_t _2;
	int64_t _63_ans_0;
	int64_t _3;
	int64_t _4;
	bool _5;
	int64_t (*_6) (struct struct_1 _format, ...);
	struct struct_1 _8;
	int64_t _7;
	int64_t (*_10) (struct struct_1 _format, ...);
	struct struct_1 _12;
	int64_t _11;
	int64_t _63_ans_1;
L51:; // incoming:1
	_0 = (struct struct_1) {8, "abcabcbb"};
	_63_s_0 = _0;
	_1 = test_leetcode_lengthOfLongestSubstring;
	_2 = _1(_63_s_0);
	_63_ans_0 = _2;
	_4 = 3;
	_5 = _63_ans_0 == _4;
	if (!_5) {
		_63_ans_1 = _63_ans_0;
		goto L56;
	} else {
		goto L52;
	}
L52:; // incoming:1
	_6 = std_system_println;
	_8 = (struct struct_1) {33, "lengthOfLongestSubstring: Passed!"};
	_7 = _6(_8);
	_3 = _7;
	goto L55;
L55:; // incoming:2
	goto end;
L56:; // incoming:1
	_10 = std_system_println;
	_12 = (struct struct_1) {35, "lengthOfLongestSubstring: Failed %d"};
	_11 = _10(_12, _63_ans_1);
	_3 = _11;
	goto L55;
end:;
	return;
}

int64_t test_leetcode_lengthOfLongestSubstring(struct struct_1 _str)
{
	int64_t retval;
	int64_t _0;
	int64_t _53_n_0;
	int64_t _53_res_0;
	int64_t _58_i_0;
	struct struct_1 _str_0;
	bool _3;
	int64_t _58_i_2;
	int64_t _53_n_1;
	struct struct_1 _str_1;
	int64_t _53_res_3;
	int64_t _60_j_0;
	int64_t _58_i_3;
	int64_t _53_n_2;
	struct struct_1 _str_2;
	int64_t _53_res_4;
	bool _4;
	int64_t _60_j_2;
	int64_t _53_n_3;
	struct struct_1 _str_3;
	int64_t _58_i_4;
	int64_t _53_res_5;
	bool (*_5) (struct struct_1 _str, int64_t _i, int64_t _j);
	bool _6;
	struct struct_1 _str_4;
	int64_t _58_i_5;
	int64_t _60_j_3;
	int64_t _53_res_6;
	int64_t _53_n_4;
	double (*_7) (double _x, double _y);
	int64_t _9;
	int64_t _10;
	int64_t _11;
	double _8;
	int64_t _12;
	int64_t _53_res_2;
	int64_t _60_j_4;
	int64_t _58_i_6;
	int64_t _53_res_7;
	int64_t _53_n_5;
	struct struct_1 _str_5;
	int64_t _13;
	int64_t _14;
	int64_t _60_j_1;
	int64_t _60_j_5;
	int64_t _53_n_6;
	struct struct_1 _str_6;
	int64_t _58_i_7;
	int64_t _53_res_8;
	int64_t _15;
	int64_t _16;
	int64_t _58_i_1;
	int64_t _58_i_8;
	int64_t _53_n_7;
	struct struct_1 _str_7;
	int64_t _53_res_9;
	int64_t _53_res_10;
	_str_0 = _str;
L36:; // incoming:1
	_0 = _str_0.length;
	_53_n_0 = _0;
	_53_res_0 = 0;
	_58_i_0 = 0;
	_58_i_2 = _58_i_0;
	_53_n_1 = _53_n_0;
	_str_1 = _str_0;
	_53_res_3 = _53_res_0;
	goto L37;
L37:; // incoming:2
	_3 = _58_i_2 < _53_n_1;
	if (!_3) {
		_53_res_10 = _53_res_3;
		goto L50;
	} else {
		_58_i_3 = _58_i_2;
		_53_n_2 = _53_n_1;
		_str_2 = _str_1;
		_53_res_4 = _53_res_3;
		goto L38;
	}
L38:; // incoming:1
	_60_j_0 = _58_i_3;
	_60_j_2 = _60_j_0;
	_53_n_3 = _53_n_2;
	_str_3 = _str_2;
	_58_i_4 = _58_i_3;
	_53_res_5 = _53_res_4;
	goto L39;
L39:; // incoming:2
	_4 = _60_j_2 < _53_n_3;
	if (!_4) {
		_58_i_8 = _58_i_4;
		_53_n_7 = _53_n_3;
		_str_7 = _str_3;
		_53_res_9 = _53_res_5;
		goto L49;
	} else {
		_str_4 = _str_3;
		_58_i_5 = _58_i_4;
		_60_j_3 = _60_j_2;
		_53_res_6 = _53_res_5;
		_53_n_4 = _53_n_3;
		goto L40;
	}
L40:; // incoming:1
	_5 = test_leetcode_areDistinct;
	_6 = _5(_str_4, _58_i_5, _60_j_3);
	if (!_6) {
		_60_j_5 = _60_j_3;
		_53_n_6 = _53_n_4;
		_str_6 = _str_4;
		_58_i_7 = _58_i_5;
		_53_res_8 = _53_res_6;
		goto L45;
	} else {
		_60_j_4 = _60_j_3;
		_58_i_6 = _58_i_5;
		_53_res_7 = _53_res_6;
		_53_n_5 = _53_n_4;
		_str_5 = _str_4;
		goto L41;
	}
L41:; // incoming:1
	_7 = std_math_max;
	_9 = _60_j_4 - _58_i_6;
	_10 = 1;
	_11 = _9 + _10;
	_8 = _7(_53_res_7, _11);
	_12 = (int64_t) _8;
	_53_res_2 = _12;
	_60_j_5 = _60_j_4;
	_53_n_6 = _53_n_5;
	_str_6 = _str_5;
	_58_i_7 = _58_i_6;
	_53_res_8 = _53_res_2;
	goto L45;
L45:; // incoming:2
	_13 = 1;
	_14 = _60_j_5 + _13;
	_60_j_1 = _14;
	_60_j_2 = _60_j_1;
	_53_n_3 = _53_n_6;
	_str_3 = _str_6;
	_58_i_4 = _58_i_7;
	_53_res_5 = _53_res_8;
	goto L39;
L49:; // incoming:1
	_15 = 1;
	_16 = _58_i_8 + _15;
	_58_i_1 = _16;
	_58_i_2 = _58_i_1;
	_53_n_1 = _53_n_7;
	_str_1 = _str_7;
	_53_res_3 = _53_res_9;
	goto L37;
L50:; // incoming:1
	retval = _53_res_10;
	goto end;
end:;
	return retval;
}

bool test_leetcode_areDistinct(struct struct_1 _str, int64_t _i, int64_t _j)
{
	bool retval;
	bool _1;
	struct struct_6 _54_visited_0;
	int64_t _55_k_0;
	int64_t _i_0;
	struct struct_1 _str_0;
	int64_t _j_0;
	bool _2;
	int64_t _55_k_2;
	int64_t _j_1;
	struct struct_1 _str_1;
	struct struct_6 _54_visited_1;
	int8_t _3;
	int64_t _4;
	int64_t _56_charCode_0;
	bool _5;
	struct struct_1 _str_2;
	int64_t _55_k_3;
	struct struct_6 _54_visited_2;
	int64_t _j_2;
	bool _7;
	int64_t _8;
	int64_t _9;
	int64_t _55_k_1;
	struct struct_6 _54_visited_3;
	int64_t _56_charCode_1;
	int64_t _55_k_4;
	int64_t _j_3;
	struct struct_1 _str_3;
	_str_0 = _str;
	_i_0 = _i;
	_j_0 = _j;
L21:; // incoming:1
	_1 = 0;
	_54_visited_0 = (struct struct_6) {256, (bool[]){_1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1}};
	_55_k_0 = _i_0;
	_55_k_2 = _55_k_0;
	_j_1 = _j_0;
	_str_1 = _str_0;
	_54_visited_1 = _54_visited_0;
	goto L22;
L22:; // incoming:2
	_2 = _55_k_2 <= _j_1;
	if (!_2) {
		goto L29;
	} else {
		_str_2 = _str_1;
		_55_k_3 = _55_k_2;
		_54_visited_2 = _54_visited_1;
		_j_2 = _j_1;
		goto L23;
	}
L23:; // incoming:1
	_3 = _str_2.data[_55_k_3];
	_4 = (int64_t) _3;
	_56_charCode_0 = _4;
	_5 = _54_visited_2.data[_56_charCode_0];
	if (!_5) {
		_54_visited_3 = _54_visited_2;
		_56_charCode_1 = _56_charCode_0;
		_55_k_4 = _55_k_3;
		_j_3 = _j_2;
		_str_3 = _str_2;
		goto L26;
	} else {
		goto L24;
	}
L24:; // incoming:1
	retval = 0;
	goto end;
L26:; // incoming:1
	_7 = 1;
	_54_visited_3.data[_56_charCode_1] = _7;
	_8 = 1;
	_9 = _55_k_4 + _8;
	_55_k_1 = _9;
	_55_k_2 = _55_k_1;
	_j_1 = _j_3;
	_str_1 = _str_3;
	_54_visited_1 = _54_visited_3;
	goto L22;
L29:; // incoming:1
	retval = 1;
	goto end;
end:;
	return retval;
}

double std_math_max(double _x, double _y)
{
	double retval;
	double _0;
	bool _1;
	double _x_0;
	double _y_0;
	double _x_1;
	double _y_1;
	_x_0 = _x;
	_y_0 = _y;
L30:; // incoming:1
	_1 = _x_0 > _y_0;
	if (!_1) {
		_y_1 = _y_0;
		goto L35;
	} else {
		_x_1 = _x_0;
		goto L32;
	}
L32:; // incoming:1
	_0 = _x_1;
	goto L33;
L33:; // incoming:2
	retval = _0;
	goto end;
L35:; // incoming:1
	_0 = _y_1;
	goto L33;
end:;
	return retval;
}

void test_leetcode_test_findMedianSortedArrays()
{
	int64_t _1;
	int64_t _2;
	struct struct_3 _77_nums1_0;
	int64_t _4;
	struct struct_3 _77_nums2_0;
	float (*_5) (struct struct_3 _nums1, struct struct_3 _nums2);
	float _6;
	float _77_ans_0;
	int64_t _7;
	float _8;
	bool _9;
	int64_t (*_10) (struct struct_1 _format, ...);
	struct struct_1 _12;
	int64_t _11;
	int64_t (*_14) (struct struct_1 _format, ...);
	struct struct_1 _16;
	int64_t _15;
	float _77_ans_1;
L92:; // incoming:1
	_1 = 1;
	_2 = 3;
	_77_nums1_0 = (struct struct_3) {2, (int64_t[]){_1, _2}};
	_4 = 2;
	_77_nums2_0 = (struct struct_3) {1, (int64_t[]){_4}};
	_5 = test_leetcode_findMedianSortedArrays;
	_6 = _5(_77_nums1_0, _77_nums2_0);
	_77_ans_0 = _6;
	_8 = 2.000000;
	_9 = _77_ans_0 == _8;
	if (!_9) {
		_77_ans_1 = _77_ans_0;
		goto L97;
	} else {
		goto L93;
	}
L93:; // incoming:1
	_10 = std_system_println;
	_12 = (struct struct_1) {31, "findMedianSortedArrays: Passed!"};
	_11 = _10(_12);
	_7 = _11;
	goto L96;
L96:; // incoming:2
	goto end;
L97:; // incoming:1
	_14 = std_system_println;
	_16 = (struct struct_1) {33, "findMedianSortedArrays: Failed %f"};
	_15 = _14(_16, _77_ans_1);
	_7 = _15;
	goto L96;
end:;
	return;
}

float test_leetcode_findMedianSortedArrays(struct struct_3 _nums1, struct struct_3 _nums2)
{
	float retval;
	int64_t _1;
	int64_t _2;
	int64_t _3;
	int64_t _4;
	struct struct_3 _0;
	struct struct_3 _66_merged_0;
	int64_t _66_i_0;
	int64_t _66_j_0;
	struct struct_3 _nums1_0;
	struct struct_3 _nums2_0;
	int64_t _7;
	int64_t _8;
	bool _9;
	int64_t _66_i_8;
	int64_t _66_j_7;
	struct struct_3 _66_merged_1;
	struct struct_3 _nums1_1;
	struct struct_3 _nums2_1;
	int8_t _10;
	int64_t _11;
	bool _12;
	struct struct_3 _nums1_2;
	int64_t _66_i_9;
	struct struct_3 _nums2_2;
	int64_t _66_j_8;
	struct struct_3 _66_merged_2;
	int64_t _13;
	bool _14;
	struct struct_3 _nums2_3;
	int64_t _66_j_9;
	struct struct_3 _nums1_3;
	int64_t _66_i_10;
	struct struct_3 _66_merged_3;
	struct struct_3 _nums1_4;
	int64_t _66_i_11;
	struct struct_3 _nums2_4;
	int64_t _66_j_10;
	struct struct_3 _66_merged_4;
	int64_t _15;
	int64_t _16;
	bool _17;
	struct struct_3 _nums1_5;
	int64_t _66_i_12;
	struct struct_3 _nums2_5;
	int64_t _66_j_11;
	struct struct_3 _66_merged_5;
	int64_t _18;
	int64_t _19;
	int64_t _20;
	int64_t _21;
	int64_t _66_i_5;
	int64_t _66_i_13;
	int64_t _66_j_12;
	struct struct_3 _nums1_6;
	struct struct_3 _66_merged_6;
	struct struct_3 _nums2_6;
	int64_t _22;
	int64_t _23;
	int64_t _24;
	int64_t _25;
	int64_t _66_j_5;
	int64_t _66_i_14;
	int64_t _66_j_13;
	struct struct_3 _nums2_7;
	struct struct_3 _66_merged_7;
	struct struct_3 _nums1_7;
	int64_t _26;
	bool _27;
	struct struct_3 _nums1_8;
	int64_t _66_i_15;
	int64_t _66_j_14;
	struct struct_3 _66_merged_8;
	struct struct_3 _nums2_8;
	int64_t _28;
	int64_t _29;
	int64_t _30;
	int64_t _31;
	int64_t _66_i_7;
	int64_t _66_i_16;
	int64_t _66_j_15;
	struct struct_3 _nums1_9;
	struct struct_3 _66_merged_9;
	struct struct_3 _nums2_9;
	int64_t _32;
	bool _33;
	struct struct_3 _nums2_10;
	int64_t _66_j_16;
	int64_t _66_i_17;
	struct struct_3 _66_merged_10;
	struct struct_3 _nums1_10;
	int64_t _34;
	int64_t _35;
	int64_t _36;
	int64_t _37;
	int64_t _66_j_6;
	int64_t _66_i_18;
	int64_t _66_j_17;
	struct struct_3 _nums2_11;
	struct struct_3 _66_merged_11;
	struct struct_3 _nums1_11;
	struct struct_3 _nums1_12;
	int64_t _66_i_19;
	struct struct_3 _nums2_12;
	int64_t _66_j_18;
	struct struct_3 _66_merged_12;
	float _38;
	int64_t _39;
	int64_t _40;
	int64_t _41;
	int64_t _42;
	bool _43;
	struct struct_3 _66_merged_13;
	int64_t _44;
	int64_t _45;
	int64_t _46;
	int64_t _47;
	int64_t _48;
	int64_t _49;
	int64_t _50;
	int64_t _51;
	int64_t _52;
	int64_t _53;
	int64_t _54;
	int64_t _55;
	float _56;
	float _57;
	struct struct_3 _66_merged_14;
	int64_t* _66;
	struct struct_3 _66_merged_15;
	int64_t _59;
	int64_t _60;
	int64_t _61;
	int64_t _62;
	float _63;
	struct struct_3 _66_merged_16;
	_nums1_0 = _nums1;
	_nums2_0 = _nums2;
L58:; // incoming:1
	_1 = _nums1_0.length;
	_2 = _nums2_0.length;
	_3 = _1 + _2;
	_4 = 0;
	_0 = (struct struct_3) {_3, malloc(sizeof(int64_t) * _3)}; for (int i_3 = 0; i_3 < _3; i_3++) {_0.data[i_3] = _4;}
	_66_merged_0 = _0;
	_66_i_0 = 0;
	_66_j_0 = 0;
	_66_i_8 = _66_i_0;
	_66_j_7 = _66_j_0;
	_66_merged_1 = _66_merged_0;
	_nums1_1 = _nums1_0;
	_nums2_1 = _nums2_0;
	goto L59;
L59:; // incoming:6
	_7 = _66_i_8 + _66_j_7;
	_8 = _66_merged_1.length;
	_9 = _7 < _8;
	if (!_9) {
		_66_merged_13 = _66_merged_1;
		goto L83;
	} else {
		_nums1_2 = _nums1_1;
		_66_i_9 = _66_i_8;
		_nums2_2 = _nums2_1;
		_66_j_8 = _66_j_7;
		_66_merged_2 = _66_merged_1;
		goto L60;
	}
L60:; // incoming:1
	_11 = _nums1_2.length;
	_12 = _66_i_9 < _11;
	if (!_12) {
		_nums1_12 = _nums1_2;
		_66_i_19 = _66_i_9;
		_nums2_12 = _nums2_2;
		_66_j_18 = _66_j_8;
		_66_merged_12 = _66_merged_2;
		goto L82;
	} else {
		_nums2_3 = _nums2_2;
		_66_j_9 = _66_j_8;
		_nums1_3 = _nums1_2;
		_66_i_10 = _66_i_9;
		_66_merged_3 = _66_merged_2;
		goto L61;
	}
L61:; // incoming:1
	_13 = _nums2_3.length;
	_14 = _66_j_9 < _13;
	_10 = _14;
	_nums1_4 = _nums1_3;
	_66_i_11 = _66_i_10;
	_nums2_4 = _nums2_3;
	_66_j_10 = _66_j_9;
	_66_merged_4 = _66_merged_3;
	goto L62;
L62:; // incoming:2
	if (!_10) {
		_nums1_8 = _nums1_4;
		_66_i_15 = _66_i_11;
		_66_j_14 = _66_j_10;
		_66_merged_8 = _66_merged_4;
		_nums2_8 = _nums2_4;
		goto L73;
	} else {
		_nums1_5 = _nums1_4;
		_66_i_12 = _66_i_11;
		_nums2_5 = _nums2_4;
		_66_j_11 = _66_j_10;
		_66_merged_5 = _66_merged_4;
		goto L63;
	}
L63:; // incoming:1
	_15 = _nums1_5.data[_66_i_12];
	_16 = _nums2_5.data[_66_j_11];
	_17 = _15 < _16;
	if (!_17) {
		_66_i_14 = _66_i_12;
		_66_j_13 = _66_j_11;
		_nums2_7 = _nums2_5;
		_66_merged_7 = _66_merged_5;
		_nums1_7 = _nums1_5;
		goto L71;
	} else {
		_66_i_13 = _66_i_12;
		_66_j_12 = _66_j_11;
		_nums1_6 = _nums1_5;
		_66_merged_6 = _66_merged_5;
		_nums2_6 = _nums2_5;
		goto L64;
	}
L64:; // incoming:1
	_18 = _66_i_13 + _66_j_12;
	_19 = _nums1_6.data[_66_i_13];
	_66_merged_6.data[_18] = _19;
	_20 = 1;
	_21 = _66_i_13 + _20;
	_66_i_5 = _21;
	_66_i_8 = _66_i_5;
	_66_j_7 = _66_j_12;
	_66_merged_1 = _66_merged_6;
	_nums1_1 = _nums1_6;
	_nums2_1 = _nums2_6;
	goto L59;
L71:; // incoming:1
	_22 = _66_i_14 + _66_j_13;
	_23 = _nums2_7.data[_66_j_13];
	_66_merged_7.data[_22] = _23;
	_24 = 1;
	_25 = _66_j_13 + _24;
	_66_j_5 = _25;
	_66_i_8 = _66_i_14;
	_66_j_7 = _66_j_5;
	_66_merged_1 = _66_merged_7;
	_nums1_1 = _nums1_7;
	_nums2_1 = _nums2_7;
	goto L59;
L73:; // incoming:1
	_26 = _nums1_8.length;
	_27 = _66_i_15 < _26;
	if (!_27) {
		_nums2_10 = _nums2_8;
		_66_j_16 = _66_j_14;
		_66_i_17 = _66_i_15;
		_66_merged_10 = _66_merged_8;
		_nums1_10 = _nums1_8;
		goto L77;
	} else {
		_66_i_16 = _66_i_15;
		_66_j_15 = _66_j_14;
		_nums1_9 = _nums1_8;
		_66_merged_9 = _66_merged_8;
		_nums2_9 = _nums2_8;
		goto L74;
	}
L74:; // incoming:1
	_28 = _66_i_16 + _66_j_15;
	_29 = _nums1_9.data[_66_i_16];
	_66_merged_9.data[_28] = _29;
	_30 = 1;
	_31 = _66_i_16 + _30;
	_66_i_7 = _31;
	_66_i_8 = _66_i_7;
	_66_j_7 = _66_j_15;
	_66_merged_1 = _66_merged_9;
	_nums1_1 = _nums1_9;
	_nums2_1 = _nums2_9;
	goto L59;
L77:; // incoming:1
	_32 = _nums2_10.length;
	_33 = _66_j_16 < _32;
	if (!_33) {
		_66_i_8 = _66_i_17;
		_66_j_7 = _66_j_16;
		_66_merged_1 = _66_merged_10;
		_nums1_1 = _nums1_10;
		_nums2_1 = _nums2_10;
		goto L59;
	} else {
		_66_i_18 = _66_i_17;
		_66_j_17 = _66_j_16;
		_nums2_11 = _nums2_10;
		_66_merged_11 = _66_merged_10;
		_nums1_11 = _nums1_10;
		goto L78;
	}
L78:; // incoming:1
	_34 = _66_i_18 + _66_j_17;
	_35 = _nums2_11.data[_66_j_17];
	_66_merged_11.data[_34] = _35;
	_36 = 1;
	_37 = _66_j_17 + _36;
	_66_j_6 = _37;
	_66_i_8 = _66_i_18;
	_66_j_7 = _66_j_6;
	_66_merged_1 = _66_merged_11;
	_nums1_1 = _nums1_11;
	_nums2_1 = _nums2_11;
	goto L59;
L82:; // incoming:1
	_10 = 0;
	_nums1_4 = _nums1_12;
	_66_i_11 = _66_i_19;
	_nums2_4 = _nums2_12;
	_66_j_10 = _66_j_18;
	_66_merged_4 = _66_merged_12;
	goto L62;
L83:; // incoming:1
	_39 = _66_merged_13.length;
	_40 = 2;
	_41 = _39 % _40;
	_42 = 0;
	_43 = _41 == _42;
	if (!_43) {
		_66_merged_16 = _66_merged_13;
		goto L90;
	} else {
		_66_merged_14 = _66_merged_13;
		goto L84;
	}
L84:; // incoming:1
	_44 = _66_merged_14.length;
	_45 = 2;
	_46 = _44 / _45;
	_47 = _66_merged_14.data[_46];
	_48 = _66_merged_14.length;
	_49 = 2;
	_50 = _48 / _49;
	_51 = 1;
	_52 = _50 + _51;
	_53 = _66_merged_14.data[_52];
	_54 = _47 + _53;
	_55 = _54;
	_56 = 2.000000;
	_57 = _55 / _56;
	_38 = _57;
	_66_merged_15 = _66_merged_14;
	goto L88;
L88:; // incoming:2
	_66 = _66_merged_15.data;
	free(_66);
	retval = _38;
	goto end;
L90:; // incoming:1
	_59 = _66_merged_16.length;
	_60 = 2;
	_61 = _59 / _60;
	_62 = _66_merged_16.data[_61];
	_63 = (float) _62;
	_38 = _63;
	_66_merged_15 = _66_merged_16;
	goto L88;
end:;
	return retval;
}

void test_leetcode_test_longestPalindrome()
{
	struct struct_1 _0;
	struct struct_1 _88_s_0;
	struct struct_1 (*_1) (struct struct_1 _s);
	struct struct_1 _2;
	struct struct_1 _88_ans_0;
	int64_t _3;
	int8_t _4;
	bool (*_5) (struct struct_1 _a, struct struct_1 _b);
	struct struct_1 _7;
	bool _6;
	struct struct_1 _88_ans_1;
	struct struct_1 _88_ans_2;
	int64_t (*_11) (struct struct_1 _format, ...);
	struct struct_1 _13;
	int64_t _12;
	int64_t (*_15) (struct struct_1 _format, ...);
	struct struct_1 _17;
	int64_t _18;
	int64_t _16;
	struct struct_1 _88_ans_3;
	bool (*_8) (struct struct_1 _a, struct struct_1 _b);
	struct struct_1 _10;
	bool _9;
	struct struct_1 _88_ans_4;
L135:; // incoming:1
	_0 = (struct struct_1) {5, "babad"};
	_88_s_0 = _0;
	_1 = test_leetcode_longestPalindrome;
	_2 = _1(_88_s_0);
	_88_ans_0 = _2;
	_5 = std_string_equals;
	_7 = (struct struct_1) {3, "bab"};
	_6 = _5(_88_ans_0, _7);
	if (!_6) {
		_88_ans_4 = _88_ans_0;
		goto L144;
	} else {
		_88_ans_1 = _88_ans_0;
		goto L136;
	}
L136:; // incoming:1
	_4 = 1;
	_88_ans_2 = _88_ans_1;
	goto L137;
L137:; // incoming:2
	if (!_4) {
		_88_ans_3 = _88_ans_2;
		goto L142;
	} else {
		goto L138;
	}
L138:; // incoming:1
	_11 = std_system_println;
	_13 = (struct struct_1) {26, "longestPalindrome: Passed!"};
	_12 = _11(_13);
	_3 = _12;
	goto L141;
L141:; // incoming:2
	goto end;
L142:; // incoming:1
	_15 = std_system_println;
	_17 = (struct struct_1) {28, "longestPalindrome: Failed %d"};
	_18 = _88_ans_3.length;
	_16 = _15(_17, _18);
	_3 = _16;
	goto L141;
L144:; // incoming:1
	_8 = std_string_equals;
	_10 = (struct struct_1) {3, "aba"};
	_9 = _8(_88_ans_4, _10);
	_4 = _9;
	_88_ans_2 = _88_ans_4;
	goto L137;
end:;
	return;
}

struct struct_1 test_leetcode_longestPalindrome(struct struct_1 _s)
{
	struct struct_1 retval;
	int64_t _80_start_0;
	int64_t _80_end_0;
	int64_t _84_i_0;
	struct struct_1 _s_0;
	int64_t _3;
	bool _4;
	struct struct_1 _s_1;
	int64_t _84_i_2;
	int64_t _80_end_5;
	int64_t _80_start_5;
	int64_t (*_5) (struct struct_1 _s, int64_t _left, int64_t _right);
	int64_t _6;
	int64_t _85_len1_0;
	int64_t (*_7) (struct struct_1 _s, int64_t _left, int64_t _right);
	int64_t _9;
	int64_t _10;
	int64_t _8;
	int64_t _85_len2_0;
	double (*_11) (double _x, double _y);
	double _12;
	int64_t _13;
	int64_t _85_len_0;
	int64_t _14;
	bool _15;
	struct struct_1 _s_2;
	int64_t _84_i_3;
	int64_t _80_end_6;
	int64_t _80_start_6;
	int64_t _16;
	int64_t _17;
	int64_t _18;
	int64_t _19;
	int64_t _20;
	int64_t _21;
	int64_t _22;
	int64_t _23;
	int64_t _24;
	int64_t _80_end_4;
	int64_t _80_start_4;
	int64_t _85_len_1;
	int64_t _84_i_4;
	struct struct_1 _s_3;
	int64_t _25;
	int64_t _26;
	int64_t _84_i_1;
	int64_t _84_i_5;
	struct struct_1 _s_4;
	int64_t _80_end_7;
	int64_t _80_start_7;
	int64_t _27;
	int64_t _28;
	int64_t _29;
	int8_t* _30;
	int8_t* _31;
	struct struct_1 _32;
	int64_t _80_end_8;
	int64_t _80_start_8;
	struct struct_1 _s_5;
	_s_0 = _s;
L112:; // incoming:1
	_80_start_0 = 0;
	_80_end_0 = 0;
	_84_i_0 = 0;
	_s_1 = _s_0;
	_84_i_2 = _84_i_0;
	_80_end_5 = _80_end_0;
	_80_start_5 = _80_start_0;
	goto L113;
L113:; // incoming:2
	_3 = _s_1.length;
	_4 = _84_i_2 < _3;
	if (!_4) {
		_80_end_8 = _80_end_5;
		_80_start_8 = _80_start_5;
		_s_5 = _s_1;
		goto L122;
	} else {
		_s_2 = _s_1;
		_84_i_3 = _84_i_2;
		_80_end_6 = _80_end_5;
		_80_start_6 = _80_start_5;
		goto L114;
	}
L114:; // incoming:1
	_5 = test_leetcode_expandAroundCenter;
	_6 = _5(_s_2, _84_i_3, _84_i_3);
	_85_len1_0 = _6;
	_7 = test_leetcode_expandAroundCenter;
	_9 = 1;
	_10 = _84_i_3 + _9;
	_8 = _7(_s_2, _84_i_3, _10);
	_85_len2_0 = _8;
	_11 = std_math_max;
	_12 = _11(_85_len1_0, _85_len2_0);
	_13 = (int64_t) _12;
	_85_len_0 = _13;
	_14 = _80_end_6 - _80_start_6;
	_15 = _85_len_0 > _14;
	if (!_15) {
		_84_i_5 = _84_i_3;
		_s_4 = _s_2;
		_80_end_7 = _80_end_6;
		_80_start_7 = _80_start_6;
		goto L120;
	} else {
		_85_len_1 = _85_len_0;
		_84_i_4 = _84_i_3;
		_s_3 = _s_2;
		goto L115;
	}
L115:; // incoming:1
	_16 = 1;
	_17 = _85_len_1 - _16;
	_18 = _17;
	_19 = 2;
	_20 = _18 / _19;
	_21 = _84_i_4 - _20;
	_22 = 2;
	_23 = _85_len_1 / _22;
	_24 = _84_i_4 + _23;
	_80_end_4 = _24;
	_80_start_4 = _21;
	_84_i_5 = _84_i_4;
	_s_4 = _s_3;
	_80_end_7 = _80_end_4;
	_80_start_7 = _80_start_4;
	goto L120;
L120:; // incoming:2
	_25 = 1;
	_26 = _84_i_5 + _25;
	_84_i_1 = _26;
	_s_1 = _s_4;
	_84_i_2 = _84_i_1;
	_80_end_5 = _80_end_7;
	_80_start_5 = _80_start_7;
	goto L113;
L122:; // incoming:1
	_27 = 1;
	_28 = _80_end_8 + _27;
	_29 = _28 - _80_start_8;
	_30 = _s_5.data;
	_31 = _30 + _80_start_8;
	_32 = (struct struct_1) {_29, _31};
	retval = _32;
	goto end;
end:;
	return retval;
}

int64_t test_leetcode_expandAroundCenter(struct struct_1 _s, int64_t _left, int64_t _right)
{
	int64_t retval;
	int8_t _0;
	int8_t _1;
	int64_t _2;
	bool _3;
	int64_t _left_3;
	struct struct_1 _s_0;
	int64_t _right_3;
	int64_t _4;
	bool _5;
	struct struct_1 _s_1;
	int64_t _right_4;
	int64_t _left_4;
	struct struct_1 _s_2;
	int64_t _left_5;
	int64_t _right_5;
	int8_t _6;
	int8_t _7;
	bool _8;
	struct struct_1 _s_3;
	int64_t _left_6;
	int64_t _right_6;
	int64_t _left_7;
	int64_t _right_7;
	struct struct_1 _s_4;
	int64_t _9;
	int64_t _10;
	int64_t _11;
	int64_t _12;
	int64_t _left_2;
	int64_t _right_2;
	int64_t _left_8;
	int64_t _right_8;
	struct struct_1 _s_5;
	int64_t _13;
	int64_t _14;
	int64_t _15;
	int64_t _right_9;
	int64_t _left_9;
	int64_t _left_10;
	int64_t _right_10;
	struct struct_1 _s_6;
	struct struct_1 _s_7;
	int64_t _left_11;
	int64_t _right_11;
	_s_0 = _s;
	_left_3 = _left;
	_right_3 = _right;
L100:; // incoming:2
	_2 = 0;
	_3 = _left_3 >= _2;
	if (!_3) {
		_s_7 = _s_0;
		_left_11 = _left_3;
		_right_11 = _right_3;
		goto L111;
	} else {
		_s_1 = _s_0;
		_right_4 = _right_3;
		_left_4 = _left_3;
		goto L101;
	}
L101:; // incoming:1
	_4 = _s_1.length;
	_5 = _right_4 < _4;
	_1 = _5;
	_s_2 = _s_1;
	_left_5 = _left_4;
	_right_5 = _right_4;
	goto L102;
L102:; // incoming:2
	if (!_1) {
		_left_10 = _left_5;
		_right_10 = _right_5;
		_s_6 = _s_2;
		goto L110;
	} else {
		_s_3 = _s_2;
		_left_6 = _left_5;
		_right_6 = _right_5;
		goto L103;
	}
L103:; // incoming:1
	_6 = _s_3.data[_left_6];
	_7 = _s_3.data[_right_6];
	_8 = _6 == _7;
	_0 = _8;
	_left_7 = _left_6;
	_right_7 = _right_6;
	_s_4 = _s_3;
	goto L104;
L104:; // incoming:2
	if (!_0) {
		_right_9 = _right_7;
		_left_9 = _left_7;
		goto L108;
	} else {
		_left_8 = _left_7;
		_right_8 = _right_7;
		_s_5 = _s_4;
		goto L105;
	}
L105:; // incoming:1
	_9 = 1;
	_10 = _left_8 - _9;
	_11 = 1;
	_12 = _right_8 + _11;
	_left_2 = _10;
	_right_2 = _12;
	_left_3 = _left_2;
	_s_0 = _s_5;
	_right_3 = _right_2;
	goto L100;
L108:; // incoming:1
	_13 = _right_9 - _left_9;
	_14 = 1;
	_15 = _13 - _14;
	retval = _15;
	goto end;
L110:; // incoming:1
	_0 = 0;
	_left_7 = _left_10;
	_right_7 = _right_10;
	_s_4 = _s_6;
	goto L104;
L111:; // incoming:1
	_1 = 0;
	_s_2 = _s_7;
	_left_5 = _left_11;
	_right_5 = _right_11;
	goto L102;
end:;
	return retval;
}

bool std_string_equals(struct struct_1 _a, struct struct_1 _b)
{
	bool retval;
	bool _0;
	int64_t _1;
	int64_t _2;
	bool _3;
	struct struct_1 _a_0;
	struct struct_1 _b_0;
	int64_t _19_i_0;
	struct struct_1 _a_1;
	struct struct_1 _b_1;
	int64_t _6;
	bool _7;
	struct struct_1 _a_2;
	int64_t _19_i_2;
	struct struct_1 _b_2;
	int8_t _8;
	int8_t _9;
	bool _10;
	struct struct_1 _a_3;
	int64_t _19_i_3;
	struct struct_1 _b_3;
	int64_t _12;
	int64_t _13;
	int64_t _19_i_1;
	int64_t _19_i_4;
	struct struct_1 _a_4;
	struct struct_1 _b_4;
	_a_0 = _a;
	_b_0 = _b;
L124:; // incoming:1
	_1 = _a_0.length;
	_2 = _b_0.length;
	_3 = _1 != _2;
	if (!_3) {
		_a_1 = _a_0;
		_b_1 = _b_0;
		goto L126;
	} else {
		goto L125;
	}
L125:; // incoming:1
	retval = 0;
	goto end;
L126:; // incoming:1
	_19_i_0 = 0;
	_a_2 = _a_1;
	_19_i_2 = _19_i_0;
	_b_2 = _b_1;
	goto L127;
L127:; // incoming:2
	_6 = _a_2.length;
	_7 = _19_i_2 < _6;
	if (!_7) {
		goto L134;
	} else {
		_a_3 = _a_2;
		_19_i_3 = _19_i_2;
		_b_3 = _b_2;
		goto L128;
	}
L128:; // incoming:1
	_8 = _a_3.data[_19_i_3];
	_9 = _b_3.data[_19_i_3];
	_10 = _8 != _9;
	if (!_10) {
		_19_i_4 = _19_i_3;
		_a_4 = _a_3;
		_b_4 = _b_3;
		goto L133;
	} else {
		goto L129;
	}
L129:; // incoming:1
	retval = 0;
	goto end;
L133:; // incoming:1
	_12 = 1;
	_13 = _19_i_4 + _12;
	_19_i_1 = _13;
	_a_2 = _a_4;
	_19_i_2 = _19_i_1;
	_b_2 = _b_4;
	goto L127;
L134:; // incoming:1
	retval = 1;
	goto end;
end:;
	return retval;
}

void test_leetcode_test_convert()
{
	struct struct_1 (*_0) (struct struct_1 _s, int64_t _numRows);
	struct struct_1 _2;
	int64_t _3;
	struct struct_1 _1;
	struct struct_1 _106_ans_0;
	int64_t _4;
	bool (*_5) (struct struct_1 _a, struct struct_1 _b);
	struct struct_1 _7;
	bool _6;
	int64_t (*_8) (struct struct_1 _format, ...);
	struct struct_1 _10;
	int64_t _9;
	int64_t (*_12) (struct struct_1 _format, ...);
	struct struct_1 _14;
	int64_t _13;
L186:; // incoming:1
	_0 = test_leetcode_convert;
	_2 = (struct struct_1) {14, "PAYPALISHIRING"};
	_3 = 3;
	_1 = _0(_2, _3);
	_106_ans_0 = _1;
	_5 = std_string_equals;
	_7 = (struct struct_1) {14, "PAHNAPLSIIGYIR"};
	_6 = _5(_106_ans_0, _7);
	if (!_6) {
		goto L191;
	} else {
		goto L187;
	}
L187:; // incoming:1
	_8 = std_system_println;
	_10 = (struct struct_1) {16, "convert: Passed!"};
	_9 = _8(_10);
	_4 = _9;
	goto L190;
L190:; // incoming:2
	goto end;
L191:; // incoming:1
	_12 = std_system_println;
	_14 = (struct struct_1) {15, "convert: Failed"};
	_13 = _12(_14);
	_4 = _13;
	goto L190;
end:;
	return;
}

struct struct_1 test_leetcode_convert(struct struct_1 _s, int64_t _numRows)
{
	struct struct_1 retval;
	int64_t _1;
	int8_t _2;
	struct struct_2 _0;
	struct struct_2 _91_board_0;
	int64_t _91_x_0;
	int64_t _91_y_0;
	bool _91_diagnolizing_0;
	int64_t _95_i_0;
	struct struct_1 _s_0;
	int64_t _numRows_0;
	int64_t _7;
	bool _8;
	struct struct_1 _s_1;
	int64_t _95_i_2;
	struct struct_2 _91_board_1;
	int64_t _91_x_4;
	int64_t _91_y_5;
	bool _91_diagnolizing_5;
	int64_t _numRows_1;
	struct struct_1 _9;
	int8_t _10;
	struct struct_2 _91_board_2;
	int64_t _91_x_5;
	struct struct_1 _s_2;
	int64_t _95_i_3;
	int64_t _91_y_6;
	bool _91_diagnolizing_6;
	int64_t _numRows_2;
	int64_t _11;
	int64_t _12;
	int64_t _91_y_1;
	int64_t _13;
	int64_t _14;
	int64_t _91_x_1;
	int64_t _15;
	bool _16;
	int64_t _91_y_7;
	int64_t _91_x_6;
	int64_t _95_i_4;
	struct struct_1 _s_3;
	struct struct_2 _91_board_3;
	int64_t _numRows_3;
	bool _91_diagnolizing_7;
	bool _91_diagnolizing_3;
	int64_t _95_i_5;
	struct struct_1 _s_4;
	struct struct_2 _91_board_4;
	int64_t _91_x_7;
	int64_t _91_y_8;
	int64_t _numRows_4;
	int64_t _26;
	int64_t _27;
	int64_t _95_i_1;
	int64_t _95_i_6;
	struct struct_1 _s_5;
	struct struct_2 _91_board_5;
	int64_t _91_x_8;
	int64_t _91_y_9;
	bool _91_diagnolizing_8;
	int64_t _numRows_5;
	int64_t _18;
	int64_t _19;
	int64_t _91_y_2;
	bool _20;
	int64_t _91_y_10;
	int64_t _numRows_6;
	int64_t _91_x_9;
	int64_t _95_i_7;
	struct struct_1 _s_6;
	struct struct_2 _91_board_6;
	bool _91_diagnolizing_9;
	int64_t _22;
	int64_t _23;
	int64_t _24;
	int64_t _25;
	int64_t _91_x_3;
	int64_t _91_y_4;
	bool _91_diagnolizing_4;
	int64_t _91_y_11;
	int64_t _91_x_10;
	int64_t _95_i_8;
	struct struct_1 _s_7;
	struct struct_2 _91_board_7;
	int64_t _numRows_7;
	int64_t _29;
	int8_t _30;
	struct struct_1 _28;
	struct struct_1 _91_retval_0;
	int64_t _91_k_0;
	int64_t _101_j_0;
	struct struct_1 _s_8;
	int64_t _numRows_8;
	struct struct_2 _91_board_8;
	bool _33;
	int64_t _101_j_2;
	int64_t _numRows_9;
	struct struct_1 _s_9;
	struct struct_2 _91_board_9;
	struct struct_1 _91_retval_1;
	int64_t _91_k_3;
	int64_t _103_i_0;
	struct struct_1 _s_10;
	struct struct_2 _91_board_10;
	int64_t _101_j_3;
	struct struct_1 _91_retval_2;
	int64_t _91_k_4;
	int64_t _numRows_10;
	int64_t _35;
	bool _36;
	struct struct_1 _s_11;
	int64_t _103_i_2;
	struct struct_2 _91_board_11;
	int64_t _101_j_4;
	struct struct_1 _91_retval_3;
	int64_t _91_k_5;
	int64_t _numRows_11;
	struct struct_1 _37;
	int8_t _38;
	int8_t _39;
	bool _40;
	struct struct_2 _91_board_12;
	int64_t _103_i_3;
	int64_t _101_j_5;
	struct struct_1 _91_retval_4;
	int64_t _91_k_6;
	struct struct_1 _s_12;
	int64_t _numRows_12;
	struct struct_1 _41;
	int8_t _42;
	int64_t _43;
	int64_t _44;
	int64_t _91_k_2;
	struct struct_2 _91_board_13;
	int64_t _103_i_4;
	int64_t _101_j_6;
	struct struct_1 _91_retval_5;
	int64_t _91_k_7;
	struct struct_1 _s_13;
	int64_t _numRows_13;
	int64_t _45;
	int64_t _46;
	int64_t _103_i_1;
	int64_t _103_i_5;
	struct struct_1 _s_14;
	struct struct_2 _91_board_14;
	int64_t _101_j_7;
	struct struct_1 _91_retval_6;
	int64_t _91_k_8;
	int64_t _numRows_14;
	int64_t _47;
	int64_t _48;
	int64_t _101_j_1;
	int64_t _101_j_8;
	int64_t _numRows_15;
	struct struct_1 _s_15;
	struct struct_2 _91_board_15;
	struct struct_1 _91_retval_7;
	int64_t _91_k_9;
	int64_t _93_i_0;
	struct struct_1 _s_16;
	struct struct_1 _91_retval_8;
	int64_t _51;
	bool _52;
	struct struct_1 _s_17;
	int64_t _93_i_2;
	struct struct_1 _91_retval_9;
	int64_t _53;
	int64_t _54;
	int64_t _93_i_1;
	int64_t _93_i_3;
	struct struct_1 _s_18;
	struct struct_1 _91_retval_10;
	struct struct_1 _91_retval_11;
	_s_0 = _s;
	_numRows_0 = _numRows;
L145:; // incoming:1
	_1 = _s_0.length;
	_2 = 0;
	_0 = (struct struct_2) {_1, malloc(sizeof(struct struct_1) * _1)}; for (int i_1 = 0; i_1 < _1; i_1++) {_0.data[i_1] = (struct struct_1) {_numRows_0, malloc(sizeof(int8_t) * _numRows_0)}; for (int i_numRows_0 = 0; i_numRows_0 < _numRows_0; i_numRows_0++) {_0.data[i_1].data[i_numRows_0] = _2;}}
	_91_board_0 = _0;
	_91_x_0 = 0;
	_91_y_0 = 0;
	_91_diagnolizing_0 = 0;
	_95_i_0 = 0;
	_s_1 = _s_0;
	_95_i_2 = _95_i_0;
	_91_board_1 = _91_board_0;
	_91_x_4 = _91_x_0;
	_91_y_5 = _91_y_0;
	_91_diagnolizing_5 = _91_diagnolizing_0;
	_numRows_1 = _numRows_0;
	goto L146;
L146:; // incoming:2
	_7 = _s_1.length;
	_8 = _95_i_2 < _7;
	if (!_8) {
		_s_8 = _s_1;
		_numRows_8 = _numRows_1;
		_91_board_8 = _91_board_1;
		goto L163;
	} else {
		_91_board_2 = _91_board_1;
		_91_x_5 = _91_x_4;
		_s_2 = _s_1;
		_95_i_3 = _95_i_2;
		_91_y_6 = _91_y_5;
		_91_diagnolizing_6 = _91_diagnolizing_5;
		_numRows_2 = _numRows_1;
		goto L147;
	}
L147:; // incoming:1
	_10 = _s_2.data[_95_i_3];
	(_91_board_2.data[_91_x_5]).data[_91_y_6] = _10;
	if (!_91_diagnolizing_6) {
		_91_y_10 = _91_y_6;
		_numRows_6 = _numRows_2;
		_91_x_9 = _91_x_5;
		_95_i_7 = _95_i_3;
		_s_6 = _s_2;
		_91_board_6 = _91_board_2;
		_91_diagnolizing_9 = _91_diagnolizing_6;
		goto L157;
	} else {
		_91_y_7 = _91_y_6;
		_91_x_6 = _91_x_5;
		_95_i_4 = _95_i_3;
		_s_3 = _s_2;
		_91_board_3 = _91_board_2;
		_numRows_3 = _numRows_2;
		_91_diagnolizing_7 = _91_diagnolizing_6;
		goto L148;
	}
L148:; // incoming:1
	_11 = 1;
	_12 = _91_y_7 - _11;
	_91_y_1 = _12;
	_13 = 1;
	_14 = _91_x_6 + _13;
	_91_x_1 = _14;
	_15 = 0;
	_16 = _91_y_1 == _15;
	if (!_16) {
		_95_i_6 = _95_i_4;
		_s_5 = _s_3;
		_91_board_5 = _91_board_3;
		_91_x_8 = _91_x_1;
		_91_y_9 = _91_y_1;
		_91_diagnolizing_8 = _91_diagnolizing_7;
		_numRows_5 = _numRows_3;
		goto L155;
	} else {
		_95_i_5 = _95_i_4;
		_s_4 = _s_3;
		_91_board_4 = _91_board_3;
		_91_x_7 = _91_x_1;
		_91_y_8 = _91_y_1;
		_numRows_4 = _numRows_3;
		goto L149;
	}
L149:; // incoming:1
	_91_diagnolizing_3 = 0;
	_95_i_6 = _95_i_5;
	_s_5 = _s_4;
	_91_board_5 = _91_board_4;
	_91_x_8 = _91_x_7;
	_91_y_9 = _91_y_8;
	_91_diagnolizing_8 = _91_diagnolizing_3;
	_numRows_5 = _numRows_4;
	goto L155;
L155:; // incoming:4
	_26 = 1;
	_27 = _95_i_6 + _26;
	_95_i_1 = _27;
	_s_1 = _s_5;
	_95_i_2 = _95_i_1;
	_91_board_1 = _91_board_5;
	_91_x_4 = _91_x_8;
	_91_y_5 = _91_y_9;
	_91_diagnolizing_5 = _91_diagnolizing_8;
	_numRows_1 = _numRows_5;
	goto L146;
L157:; // incoming:1
	_18 = 1;
	_19 = _91_y_10 + _18;
	_91_y_2 = _19;
	_20 = _91_y_2 == _numRows_6;
	if (!_20) {
		_95_i_6 = _95_i_7;
		_s_5 = _s_6;
		_91_board_5 = _91_board_6;
		_91_x_8 = _91_x_9;
		_91_y_9 = _91_y_2;
		_91_diagnolizing_8 = _91_diagnolizing_9;
		_numRows_5 = _numRows_6;
		goto L155;
	} else {
		_91_y_11 = _91_y_2;
		_91_x_10 = _91_x_9;
		_95_i_8 = _95_i_7;
		_s_7 = _s_6;
		_91_board_7 = _91_board_6;
		_numRows_7 = _numRows_6;
		goto L158;
	}
L158:; // incoming:1
	_22 = 2;
	_23 = _91_y_11 - _22;
	_24 = 1;
	_25 = _91_x_10 + _24;
	_91_x_3 = _25;
	_91_y_4 = _23;
	_91_diagnolizing_4 = 1;
	_95_i_6 = _95_i_8;
	_s_5 = _s_7;
	_91_board_5 = _91_board_7;
	_91_x_8 = _91_x_3;
	_91_y_9 = _91_y_4;
	_91_diagnolizing_8 = _91_diagnolizing_4;
	_numRows_5 = _numRows_7;
	goto L155;
L163:; // incoming:1
	_29 = _s_8.length;
	_30 = 0;
	_28 = (struct struct_1) {_29, malloc(sizeof(int8_t) * _29)}; for (int i_29 = 0; i_29 < _29; i_29++) {_28.data[i_29] = _30;}
	_91_retval_0 = _28;
	_91_k_0 = 0;
	_101_j_0 = 0;
	_101_j_2 = _101_j_0;
	_numRows_9 = _numRows_8;
	_s_9 = _s_8;
	_91_board_9 = _91_board_8;
	_91_retval_1 = _91_retval_0;
	_91_k_3 = _91_k_0;
	goto L164;
L164:; // incoming:2
	_33 = _101_j_2 < _numRows_9;
	if (!_33) {
		_s_16 = _s_9;
		_91_retval_8 = _91_retval_1;
		goto L178;
	} else {
		_s_10 = _s_9;
		_91_board_10 = _91_board_9;
		_101_j_3 = _101_j_2;
		_91_retval_2 = _91_retval_1;
		_91_k_4 = _91_k_3;
		_numRows_10 = _numRows_9;
		goto L165;
	}
L165:; // incoming:1
	_103_i_0 = 0;
	_s_11 = _s_10;
	_103_i_2 = _103_i_0;
	_91_board_11 = _91_board_10;
	_101_j_4 = _101_j_3;
	_91_retval_3 = _91_retval_2;
	_91_k_5 = _91_k_4;
	_numRows_11 = _numRows_10;
	goto L166;
L166:; // incoming:2
	_35 = _s_11.length;
	_36 = _103_i_2 < _35;
	if (!_36) {
		_101_j_8 = _101_j_4;
		_numRows_15 = _numRows_11;
		_s_15 = _s_11;
		_91_board_15 = _91_board_11;
		_91_retval_7 = _91_retval_3;
		_91_k_9 = _91_k_5;
		goto L176;
	} else {
		_91_board_12 = _91_board_11;
		_103_i_3 = _103_i_2;
		_101_j_5 = _101_j_4;
		_91_retval_4 = _91_retval_3;
		_91_k_6 = _91_k_5;
		_s_12 = _s_11;
		_numRows_12 = _numRows_11;
		goto L167;
	}
L167:; // incoming:1
	_37 = _91_board_12.data[_103_i_3];
	_38 = _37.data[_101_j_5];
	_39 = 0;
	_40 = _38 != _39;
	if (!_40) {
		_103_i_5 = _103_i_3;
		_s_14 = _s_12;
		_91_board_14 = _91_board_12;
		_101_j_7 = _101_j_5;
		_91_retval_6 = _91_retval_4;
		_91_k_8 = _91_k_6;
		_numRows_14 = _numRows_12;
		goto L172;
	} else {
		_91_board_13 = _91_board_12;
		_103_i_4 = _103_i_3;
		_101_j_6 = _101_j_5;
		_91_retval_5 = _91_retval_4;
		_91_k_7 = _91_k_6;
		_s_13 = _s_12;
		_numRows_13 = _numRows_12;
		goto L168;
	}
L168:; // incoming:1
	_41 = _91_board_13.data[_103_i_4];
	_42 = _41.data[_101_j_6];
	_91_retval_5.data[_91_k_7] = _42;
	_43 = 1;
	_44 = _91_k_7 + _43;
	_91_k_2 = _44;
	_103_i_5 = _103_i_4;
	_s_14 = _s_13;
	_91_board_14 = _91_board_13;
	_101_j_7 = _101_j_6;
	_91_retval_6 = _91_retval_5;
	_91_k_8 = _91_k_2;
	_numRows_14 = _numRows_13;
	goto L172;
L172:; // incoming:2
	_45 = 1;
	_46 = _103_i_5 + _45;
	_103_i_1 = _46;
	_s_11 = _s_14;
	_103_i_2 = _103_i_1;
	_91_board_11 = _91_board_14;
	_101_j_4 = _101_j_7;
	_91_retval_3 = _91_retval_6;
	_91_k_5 = _91_k_8;
	_numRows_11 = _numRows_14;
	goto L166;
L176:; // incoming:1
	_47 = 1;
	_48 = _101_j_8 + _47;
	_101_j_1 = _48;
	_101_j_2 = _101_j_1;
	_numRows_9 = _numRows_15;
	_s_9 = _s_15;
	_91_board_9 = _91_board_15;
	_91_retval_1 = _91_retval_7;
	_91_k_3 = _91_k_9;
	goto L164;
L178:; // incoming:1
	_93_i_0 = 0;
	_s_17 = _s_16;
	_93_i_2 = _93_i_0;
	_91_retval_9 = _91_retval_8;
	goto L179;
L179:; // incoming:2
	_51 = _s_17.length;
	_52 = _93_i_2 < _51;
	if (!_52) {
		_91_retval_11 = _91_retval_9;
		goto L185;
	} else {
		_93_i_3 = _93_i_2;
		_s_18 = _s_17;
		_91_retval_10 = _91_retval_9;
		goto L182;
	}
L182:; // incoming:1
	_53 = 1;
	_54 = _93_i_3 + _53;
	_93_i_1 = _54;
	_s_17 = _s_18;
	_93_i_2 = _93_i_1;
	_91_retval_9 = _91_retval_10;
	goto L179;
L185:; // incoming:1
	retval = _91_retval_11;
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
