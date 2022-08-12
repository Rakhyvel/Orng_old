/* Code generated using the Orng compiler http://josephs-projects.com */

#ifndef ORNG_3676
#define ORNG_3676

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

/* Debug */
struct list {
	int length;
	int capacity;
	char** data;
};

struct list stackTrace;
struct list errorTrace;

void stackTraceInit(struct list* list) {
	list->length = 0;
	list->capacity = 10;
	list->data = malloc(sizeof(char*) * list->capacity);
}

void stackTracePush(struct list* list, char* data) {
	if (list->length >= list->capacity) {
		list->capacity *= 2;
		list->data = realloc(list->data, list->capacity);
	}
	list->data[list->length] = data;
	list->length++;
}

void stackTracePop(struct list* list) {
	list->length--;
}

void stackTraceClear(struct list* list) {
	list->length = 0;
}

void stackTracePrint(struct list* list) {
	for (int i = 0; i < list->length; i++) {
		fprintf(stderr, "%s", list->data[i]);
	}
}

void stackTracePrintReverse(struct list* list) {
	for (int i = list->length - 1; i >= 0; i--) {
		fprintf(stderr, "%s", list->data[i]);
	}
}

char* tagGetFieldName(int tag) {
	switch(tag) {
	case 0:
		return "nothing";
	case 1:
	case 2:
		return "something";
	case 3:
		return "a";
	case 4:
		return "b";
	case 5:
		return "c";
	case 6:
		return "d";
	case 7:
		return "e";
	case 8:
		return "fileNotFound";
	case 9:
		return "resourceBusy";
	case 10:
		return "outOfMemory";
	case 11:
	case 12:
		return "success";
	}
}

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
};

struct struct_4 {
	int64_t length;
	int64_t* data;
};

struct struct_5 {
	int64_t tag;
	union {
		struct struct_6* something;
	};
};

struct struct_6 {
	int64_t val;
	struct struct_5 next;
};

struct struct_7 {
	int64_t length;
	bool* data;
};

struct struct_8 {
	int64_t tag;
	union {
		int64_t c;
	};
};

struct struct_9 {
	int64_t tag;
	union {
		int64_t c;
		int8_t d;
	};
};

struct struct_10 {
	float re;
	float im;
};

struct struct_11 {
	int64_t tag;
	union {
		int64_t fileNotFound;
	};
};

struct struct_12 {
	int64_t tag;
	union {
		int64_t success;
		int64_t fileNotFound;
	};
};

struct struct_13 {
	int64_t tag;
};

/* Verbatim code */
int std_system_println(struct struct_1 _format, ...) {va_list _25_args;va_start(_25_args, _format.data);int retval = vprintf(_format.data, _25_args);va_end(_25_args);char newLine[2] = {'\n', '\0'};printf(newLine);return retval;}

/* Function definitions */
struct struct_3 test_testModule_main(struct struct_2 _args);
void test_leetcode_test_all();
void test_leetcode_test_twoSum();
struct struct_4 test_leetcode_twoSum(struct struct_4 _nums, int64_t _target);
void std_debug_assert(bool _predicate, struct struct_1 _msg);
int64_t std_system_err(struct struct_1 _format, ...);
int64_t std_system_errln(struct struct_1 _format, ...);
void test_leetcode_test_addTwoNumbers();
struct struct_6* test_leetcode_addTwoNumbers(struct struct_6* _l1, struct struct_6* _l2);
struct struct_6* test_leetcode_convertToList(int64_t _i);
int64_t test_leetcode_convertToInt(struct struct_5 _l);
bool test_leetcode_hasValue(struct struct_5 _node, struct struct_4 _x);
void test_leetcode_test_lengthOfLongestSubstring();
int64_t test_leetcode_lengthOfLongestSubstring(struct struct_1 _str);
bool test_leetcode_areDistinct(struct struct_1 _str, int64_t _i, int64_t _j);
double std_math_max(double _x, double _y);
void test_leetcode_test_findMedianSortedArrays();
float test_leetcode_findMedianSortedArrays(struct struct_4 _nums1, struct struct_4 _nums2);
void test_leetcode_test_longestPalindrome();
struct struct_1 test_leetcode_longestPalindrome(struct struct_1 _s);
int64_t test_leetcode_expandAroundCenter(struct struct_1 _s, int64_t _left, int64_t _right);
bool std_string_equals(struct struct_1 _a, struct struct_1 _b);
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
int64_t test_leetcode_maxArea(struct struct_4 _height, int64_t _max);
int64_t std_math_abs(int64_t _x);
double std_math_min(double _x, double _y);

struct struct_3 test_testModule_main(struct struct_2 _args)
{
	struct struct_3 retval;
	void (*_0) ();
	int64_t _2;
	struct struct_3 _3;
	struct struct_2 _args_0;
	_args_0 = _args;
L302:; // incoming:1
	_0 = test_leetcode_test_all;
	stackTracePush(&stackTrace, "test/testModule.orng: \n36    | main::(args:[]String)->!() = leetcode.test_all()\n      |                                               ^\n");
	_0();
	_2 = 12;
	_3 = (struct struct_3) {_2};
	retval = _3;
	goto end;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

void test_leetcode_test_all()
{
	void (*_0) ();
	void (*_2) ();
	void (*_4) ();
	void (*_6) ();
	void (*_8) ();
	void (*_10) ();
	void (*_12) ();
	void (*_14) ();
	void (*_16) ();
	void (*_18) ();
	void (*_20) ();
	int64_t (*_22) (struct struct_1 _format, ...);
	struct struct_1 _24;
	int64_t _23;
L301:; // incoming:1
	_0 = test_leetcode_test_twoSum;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n5     | test_twoSum()\n      |            ^\n");
	_0();
	_2 = test_leetcode_test_addTwoNumbers;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n6     | test_addTwoNumbers()\n      |                   ^\n");
	_2();
	_4 = test_leetcode_test_lengthOfLongestSubstring;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n7     | test_lengthOfLongestSubstring()\n      |                              ^\n");
	_4();
	_6 = test_leetcode_test_findMedianSortedArrays;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n8     | test_findMedianSortedArrays()\n      |                            ^\n");
	_6();
	_8 = test_leetcode_test_longestPalindrome;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n9     | test_longestPalindrome()\n      |                       ^\n");
	_8();
	_10 = test_leetcode_test_convert;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n10    | test_convert()\n      |             ^\n");
	_10();
	_12 = test_leetcode_test_reverse;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n11    | test_reverse()\n      |             ^\n");
	_12();
	_14 = test_leetcode_test_myAtoi;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n12    | test_myAtoi()\n      |            ^\n");
	_14();
	_16 = test_leetcode_test_isPalindrome;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n13    | test_isPalindrome()\n      |                  ^\n");
	_16();
	_18 = test_leetcode_test_isMatch;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n14    | test_isMatch()\n      |             ^\n");
	_18();
	_20 = test_leetcode_test_maxArea;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n15    | test_maxArea()\n      |             ^\n");
	_20();
	_22 = std_system_println;
	_24 = (struct struct_1) {7, "Passed!"};
	stackTracePush(&stackTrace, "test/leetcode.orng: \n16    | std.system.println(\"Passed!\")\n      |                   ^\n");
	_23 = _22(_24);
	goto end;
end:;
	stackTracePop(&stackTrace);
	return;
}

void test_leetcode_test_twoSum()
{
	int64_t _1;
	int64_t _2;
	int64_t _3;
	int64_t _4;
	struct struct_4 _43_nums_0;
	int64_t _43_target_0;
	struct struct_4 (*_6) (struct struct_4 _nums, int64_t _target);
	struct struct_4 _7;
	struct struct_4 _43_ans_0;
	void (*_8) (bool _predicate, struct struct_1 _msg);
	int64_t _11;
	int64_t _12;
	int64_t _13;
	int64_t _14;
	int64_t _15;
	int64_t _16;
	int64_t _17;
	bool _10;
	struct struct_1 _18;
L21:; // incoming:1
	_1 = 2;
	_2 = 7;
	_3 = 11;
	_4 = 15;
	_43_nums_0 = (struct struct_4) {4, (int64_t[]){_1, _2, _3, _4}};
	_43_target_0 = 9;
	_6 = test_leetcode_twoSum;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n62    | ans := twoSum(nums, target)\n      |              ^\n");
	_7 = _6(_43_nums_0, _43_target_0);
	_43_ans_0 = _7;
	_8 = std_debug_assert;
	_11 = 0;
	_12 = _43_ans_0.data[_11];
	_13 = _43_nums_0.data[_12];
	_14 = 1;
	_15 = _43_ans_0.data[_14];
	_16 = _43_nums_0.data[_15];
	_17 = _13 + _16;
	_10 = _17 == _43_target_0;
	_18 = (struct struct_1) {20, "no message specified"};
	stackTracePush(&stackTrace, "test/leetcode.orng: \n64    | std.debug.assert(nums[ans[0]] + nums[ans[1]] == target)\n      |                 ^\n");
	_8(_10, _18);
	goto end;
end:;
	stackTracePop(&stackTrace);
	return;
}

struct struct_4 test_leetcode_twoSum(struct struct_4 _nums, int64_t _target)
{
	struct struct_4 retval;
	int64_t _38_i_0;
	struct struct_4 _nums_0;
	int64_t _target_0;
	int64_t _1;
	int64_t _2;
	int64_t _3;
	bool _4;
	struct struct_4 _nums_1;
	int64_t _38_i_2;
	int64_t _target_1;
	int64_t _5;
	int64_t _6;
	int64_t _40_j_0;
	int64_t _38_i_3;
	struct struct_4 _nums_2;
	int64_t _target_2;
	int64_t _7;
	bool _8;
	struct struct_4 _nums_3;
	int64_t _40_j_2;
	int64_t _38_i_4;
	int64_t _target_3;
	int64_t _10;
	int64_t _11;
	int64_t _12;
	bool _9;
	struct struct_4 _nums_4;
	int64_t _38_i_5;
	int64_t _40_j_3;
	int64_t _target_4;
	int64_t _14;
	struct struct_4 _15;
	struct struct_4 _13;
	int64_t _38_i_6;
	int64_t _40_j_4;
	int64_t _16;
	int64_t _17;
	int64_t _40_j_1;
	int64_t _40_j_5;
	struct struct_4 _nums_5;
	int64_t _38_i_7;
	int64_t _target_5;
	int64_t _18;
	int64_t _19;
	int64_t _38_i_1;
	int64_t _38_i_8;
	struct struct_4 _nums_6;
	int64_t _target_6;
	int64_t _21;
	int64_t _23;
	int64_t _24;
	struct struct_4 _22;
	struct struct_4 _20;
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
	_10 = _nums_4.data[_38_i_5];
	_11 = _nums_4.data[_40_j_3];
	_12 = _10 + _11;
	_9 = _12 == _target_4;
	if (!_9) {
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
	_15 = (struct struct_4) {2, (int64_t[]){_38_i_6, _40_j_4}};
	_13 = (struct struct_4) {_14, malloc(sizeof(int64_t) * _14)}; for (int i_14 = 0; i_14 < _14; i_14++) {_13.data[i_14] = _15.data[i_14];}
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
	_22 = (struct struct_4) {2, (int64_t[]){_23, _24}};
	_20 = (struct struct_4) {_21, malloc(sizeof(int64_t) * _21)}; for (int i_21 = 0; i_21 < _21; i_21++) {_20.data[i_21] = _22.data[i_21];}
	retval = _20;
	goto end;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

void std_debug_assert(bool _predicate, struct struct_1 _msg)
{
	bool _0;
	bool _predicate_0;
	struct struct_1 _msg_0;
	int64_t (*_1) (struct struct_1 _format, ...);
	struct struct_1 _3;
	int64_t _2;
	int64_t (*_4) (struct struct_1 _format, ...);
	int64_t _5;
	struct struct_1 _msg_1;
	_predicate_0 = _predicate;
	_msg_0 = _msg;
L16:; // incoming:1
	_0 = !_predicate_0;
	if (!_0) {
		goto end;
	} else {
		_msg_1 = _msg_0;
		goto L17;
	}
L17:; // incoming:1
	_1 = std_system_err;
	_3 = (struct struct_1) {18, "assertion failed: "};
	stackTracePush(&stackTrace, "std/debug.orng: \n8     | system.err(\"assertion failed: \")\n      |           ^\n");
	_2 = _1(_3);
	_4 = std_system_errln;
	stackTracePush(&stackTrace, "std/debug.orng: \n9     | system.errln(msg)\n      |             ^\n");
	_5 = _4(_msg_1);
	fprintf(stderr, "error: unreachable\n");
	stackTracePush(&stackTrace, "std/debug.orng: \n10    | unreachable\n      | ^^^^^^^^^^^\n");
	stackTracePrintReverse(&stackTrace);
	exit(1);
	goto end;
end:;
	stackTracePop(&stackTrace);
	return;
}

int64_t std_system_err(struct struct_1 _format, ...)
{
	int64_t retval;
	struct struct_1 _format_0;
	_format_0 = _format;
L14:; // incoming:1
	retval = 0;
	goto end;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

int64_t std_system_errln(struct struct_1 _format, ...)
{
	int64_t retval;
	struct struct_1 _format_0;
	_format_0 = _format;
L15:; // incoming:1
	retval = 0;
	goto end;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

void test_leetcode_test_addTwoNumbers()
{
	int64_t _2;
	int64_t _3;
	struct struct_5 _4;
	struct struct_6 _1;
	struct struct_6* _0;
	struct struct_6* _46_l1_c_0;
	int64_t _7;
	int64_t _8;
	struct struct_5 _9;
	struct struct_6 _6;
	struct struct_6* _5;
	struct struct_6* _46_l1_b_0;
	int64_t _12;
	int64_t _13;
	struct struct_5 _14;
	struct struct_6 _11;
	struct struct_6* _10;
	struct struct_6* _46_l1_0;
	int64_t _17;
	int64_t _18;
	struct struct_5 _19;
	struct struct_6 _16;
	struct struct_6* _15;
	struct struct_6* _46_l2_c_0;
	int64_t _22;
	int64_t _23;
	struct struct_5 _24;
	struct struct_6 _21;
	struct struct_6* _20;
	struct struct_6* _46_l2_b_0;
	int64_t _27;
	int64_t _28;
	struct struct_5 _29;
	struct struct_6 _26;
	struct struct_6* _25;
	struct struct_6* _46_l2_0;
	struct struct_6* (*_30) (struct struct_6* _l1, struct struct_6* _l2);
	struct struct_6* _31;
	struct struct_6* _46_ans_0;
	void (*_32) (bool _predicate, struct struct_1 _msg);
	bool (*_34) (struct struct_5 _node, struct struct_4 _x);
	int64_t _36;
	struct struct_5 _37;
	int64_t _39;
	int64_t _40;
	int64_t _41;
	struct struct_4 _38;
	bool _35;
	struct struct_1 _42;
L44:; // incoming:1
	_2 = 3;
	_3 = 0;
	_4 = (struct struct_5) {_3};
	_1 = (struct struct_6) {_2, _4};
	_0 = calloc(sizeof(struct struct_6), 1);
	*_0 = _1;
	_46_l1_c_0 = _0;
	_7 = 4;
	_8 = 2;
	_9 = (struct struct_5) {_8, _46_l1_c_0};
	_6 = (struct struct_6) {_7, _9};
	_5 = calloc(sizeof(struct struct_6), 1);
	*_5 = _6;
	_46_l1_b_0 = _5;
	_12 = 2;
	_13 = 2;
	_14 = (struct struct_5) {_13, _46_l1_b_0};
	_11 = (struct struct_6) {_12, _14};
	_10 = calloc(sizeof(struct struct_6), 1);
	*_10 = _11;
	_46_l1_0 = _10;
	_17 = 4;
	_18 = 0;
	_19 = (struct struct_5) {_18};
	_16 = (struct struct_6) {_17, _19};
	_15 = calloc(sizeof(struct struct_6), 1);
	*_15 = _16;
	_46_l2_c_0 = _15;
	_22 = 6;
	_23 = 2;
	_24 = (struct struct_5) {_23, _46_l2_c_0};
	_21 = (struct struct_6) {_22, _24};
	_20 = calloc(sizeof(struct struct_6), 1);
	*_20 = _21;
	_46_l2_b_0 = _20;
	_27 = 5;
	_28 = 2;
	_29 = (struct struct_5) {_28, _46_l2_b_0};
	_26 = (struct struct_6) {_27, _29};
	_25 = calloc(sizeof(struct struct_6), 1);
	*_25 = _26;
	_46_l2_0 = _25;
	_30 = test_leetcode_addTwoNumbers;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n102   | ans := addTwoNumbers(l1, l2)\n      |                     ^\n");
	_31 = _30(_46_l1_0, _46_l2_0);
	_46_ans_0 = _31;
	_32 = std_debug_assert;
	_34 = test_leetcode_hasValue;
	_36 = 2;
	_37 = (struct struct_5) {_36, _46_ans_0};
	_39 = 7;
	_40 = 0;
	_41 = 8;
	_38 = (struct struct_4) {3, (int64_t[]){_39, _40, _41}};
	stackTracePush(&stackTrace, "test/leetcode.orng: \n111   | std.debug.assert(hasValue(ans, [7, 0, 8]))\n      |                          ^\n");
	_35 = _34(_37, _38);
	_42 = (struct struct_1) {20, "no message specified"};
	stackTracePush(&stackTrace, "test/leetcode.orng: \n111   | std.debug.assert(hasValue(ans, [7, 0, 8]))\n      |                 ^\n");
	_32(_35, _42);
	goto end;
end:;
	stackTracePop(&stackTrace);
	return;
}

struct struct_6* test_leetcode_addTwoNumbers(struct struct_6* _l1, struct struct_6* _l2)
{
	struct struct_6* retval;
	struct struct_6* (*_0) (int64_t _i);
	int64_t (*_2) (struct struct_5 _l);
	int64_t _4;
	struct struct_5 _5;
	int64_t _3;
	int64_t (*_6) (struct struct_5 _l);
	int64_t _8;
	struct struct_5 _9;
	int64_t _7;
	int64_t _10;
	struct struct_6* _1;
	struct struct_6* _l1_0;
	struct struct_6* _l2_0;
	_l1_0 = _l1;
	_l2_0 = _l2;
L34:; // incoming:1
	_0 = test_leetcode_convertToList;
	_2 = test_leetcode_convertToInt;
	_4 = 2;
	_5 = (struct struct_5) {_4, _l1_0};
	stackTracePush(&stackTrace, "test/leetcode.orng: \n92    | convertToList(convertToInt(l1) + convertToInt(l2))\n      |                           ^\n");
	_3 = _2(_5);
	_6 = test_leetcode_convertToInt;
	_8 = 2;
	_9 = (struct struct_5) {_8, _l2_0};
	stackTracePush(&stackTrace, "test/leetcode.orng: \n92    | convertToList(convertToInt(l1) + convertToInt(l2))\n      |                                              ^\n");
	_7 = _6(_9);
	_10 = _3 + _7;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n92    | convertToList(convertToInt(l1) + convertToInt(l2))\n      |              ^\n");
	_1 = _0(_10);
	retval = _1;
	goto end;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

struct struct_6* test_leetcode_convertToList(int64_t _i)
{
	struct struct_6* retval;
	struct struct_6* _0;
	int64_t _1;
	bool _2;
	int64_t _i_0;
	int64_t _5;
	struct struct_5 _6;
	struct struct_6 _4;
	struct struct_6* _3;
	int64_t _i_1;
	int64_t _10;
	int64_t _11;
	int64_t _12;
	struct struct_6* (*_13) (int64_t _i);
	int64_t _15;
	int64_t _16;
	struct struct_6* _14;
	struct struct_5 _17;
	struct struct_6 _9;
	struct struct_6* _8;
	int64_t _i_2;
	_i_0 = _i;
L22:; // incoming:1
	_1 = 10;
	_2 = _i_0 < _1;
	if (!_2) {
		_i_2 = _i_0;
		goto L26;
	} else {
		_i_1 = _i_0;
		goto L23;
	}
L23:; // incoming:1
	_5 = 0;
	_6 = (struct struct_5) {_5};
	_4 = (struct struct_6) {_i_1, _6};
	_3 = calloc(sizeof(struct struct_6), 1);
	*_3 = _4;
	_0 = _3;
	goto L25;
L25:; // incoming:2
	retval = _0;
	goto end;
L26:; // incoming:1
	_10 = 10;
	_11 = _i_2 % _10;
	_12 = 2;
	_13 = test_leetcode_convertToList;
	_15 = 10;
	_16 = _i_2 / _15;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n88    | new ListNode(i % 10, convertToList(i / 10))\n      |                                   ^\n");
	_14 = _13(_16);
	_17 = (struct struct_5) {_12, _14};
	_9 = (struct struct_6) {_11, _17};
	_8 = calloc(sizeof(struct struct_6), 1);
	*_8 = _9;
	_0 = _8;
	goto L25;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

int64_t test_leetcode_convertToInt(struct struct_5 _l)
{
	int64_t retval;
	int64_t _0;
	int64_t _1;
	int64_t _2;
	bool _3;
	struct struct_5 _l_0;
	int64_t _4;
	bool _5;
	struct struct_5 _l_1;
	struct struct_6* _7;
	struct struct_6 _8;
	int64_t _9;
	int64_t (*_10) (struct struct_5 _l);
	struct struct_6* _12;
	struct struct_6 _13;
	struct struct_5 _14;
	int64_t _11;
	int64_t _15;
	int64_t _16;
	int64_t _17;
	struct struct_5 _l_2;
	_l_0 = _l;
L28:; // incoming:1
	_1 = _l_0.tag;
	_2 = 0;
	_3 = _1 != _2;
	if (!_3) {
		goto L31;
	} else {
		_l_1 = _l_0;
		goto L29;
	}
L29:; // incoming:1
	_4 = 2;
	_5 = _1 != _4;
	if (!_5) {
		_l_2 = _l_1;
		goto L33;
	} else {
		goto L31;
	}
L31:; // incoming:2
	_0 = 0;
	goto L32;
L32:; // incoming:2
	retval = _0;
	goto end;
L33:; // incoming:1
	_7 = _l_2.something;
	_8 = *_7;
	_9 = _8.val;
	_10 = test_leetcode_convertToInt;
	_12 = _l_2.something;
	_13 = *_12;
	_14 = _13.next;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n81    | .something -> l?.val + convertToInt(l?.next) * 10\n      |                                    ^\n");
	_11 = _10(_14);
	_15 = 10;
	_16 = _11 * _15;
	_17 = _9 + _16;
	_0 = _17;
	goto L32;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

bool test_leetcode_hasValue(struct struct_5 _node, struct struct_4 _x)
{
	bool retval;
	bool _0;
	int64_t _2;
	int64_t _3;
	struct struct_3 _4;
	int64_t _5;
	bool _1;
	struct struct_5 _node_0;
	struct struct_4 _x_0;
	int8_t _6;
	struct struct_6* _8;
	struct struct_6 _9;
	int64_t _10;
	int64_t _11;
	int64_t _12;
	bool _7;
	struct struct_5 _node_1;
	struct struct_4 _x_1;
	bool (*_13) (struct struct_5 _node, struct struct_4 _x);
	struct struct_6* _15;
	struct struct_6 _16;
	struct struct_5 _17;
	int64_t _18;
	int64_t _19;
	int64_t _20;
	int64_t* _21;
	int64_t* _22;
	struct struct_4 _23;
	bool _14;
	struct struct_5 _node_2;
	struct struct_4 _x_2;
	_node_0 = _node;
	_x_0 = _x;
L35:; // incoming:1
	_2 = _node_0.tag;
	_3 = 0;
	_4 = (struct struct_3) {_3};
	_5 = _4.tag;
	_1 = _2 != _5;
	if (!_1) {
		goto L43;
	} else {
		_node_1 = _node_0;
		_x_1 = _x_0;
		goto L36;
	}
L36:; // incoming:1
	_8 = _node_1.something;
	_9 = *_8;
	_10 = _9.val;
	_11 = 0;
	_12 = _x_1.data[_11];
	_7 = _10 == _12;
	if (!_7) {
		goto L41;
	} else {
		_node_2 = _node_1;
		_x_2 = _x_1;
		goto L37;
	}
L37:; // incoming:1
	_13 = test_leetcode_hasValue;
	_15 = _node_2.something;
	_16 = *_15;
	_17 = _16.next;
	_18 = 1;
	_19 = _x_2.length;
	_20 = _19 - _18;
	_21 = _x_2.data;
	_22 = _21 + _18;
	_23 = (struct struct_4) {_20, _22};
	stackTracePush(&stackTrace, "test/leetcode.orng: \n106   | node?.val == x[0] && hasValue(node?.next, x[1;])\n      |                              ^\n");
	_14 = _13(_17, _23);
	_6 = _14;
	goto L39;
L39:; // incoming:2
	_0 = _6;
	goto L40;
L40:; // incoming:2
	retval = _0;
	goto end;
L41:; // incoming:1
	_6 = 0;
	goto L39;
L43:; // incoming:1
	_0 = 1;
	goto L40;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

void test_leetcode_test_lengthOfLongestSubstring()
{
	struct struct_1 _0;
	struct struct_1 _59_s_0;
	int64_t (*_1) (struct struct_1 _str);
	int64_t _2;
	int64_t _59_ans_0;
	void (*_3) (bool _predicate, struct struct_1 _msg);
	int64_t _6;
	bool _5;
	struct struct_1 _7;
L75:; // incoming:1
	_0 = (struct struct_1) {8, "abcabcbb"};
	_59_s_0 = _0;
	_1 = test_leetcode_lengthOfLongestSubstring;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n151   | ans := lengthOfLongestSubstring(s)\n      |                                ^\n");
	_2 = _1(_59_s_0);
	_59_ans_0 = _2;
	_3 = std_debug_assert;
	_6 = 3;
	_5 = _59_ans_0 == _6;
	_7 = (struct struct_1) {20, "no message specified"};
	stackTracePush(&stackTrace, "test/leetcode.orng: \n153   | std.debug.assert(ans == 3)\n      |                 ^\n");
	_3(_5, _7);
	goto end;
end:;
	stackTracePop(&stackTrace);
	return;
}

int64_t test_leetcode_lengthOfLongestSubstring(struct struct_1 _str)
{
	int64_t retval;
	int64_t _0;
	int64_t _49_n_0;
	int64_t _49_res_0;
	int64_t _54_i_0;
	struct struct_1 _str_0;
	bool _3;
	int64_t _54_i_2;
	int64_t _49_n_1;
	struct struct_1 _str_1;
	int64_t _49_res_3;
	int64_t _56_j_0;
	int64_t _54_i_3;
	int64_t _49_n_2;
	struct struct_1 _str_2;
	int64_t _49_res_4;
	bool _4;
	int64_t _56_j_2;
	int64_t _49_n_3;
	struct struct_1 _str_3;
	int64_t _54_i_4;
	int64_t _49_res_5;
	bool (*_5) (struct struct_1 _str, int64_t _i, int64_t _j);
	bool _6;
	struct struct_1 _str_4;
	int64_t _54_i_5;
	int64_t _56_j_3;
	int64_t _49_res_6;
	int64_t _49_n_4;
	double (*_7) (double _x, double _y);
	int64_t _9;
	int64_t _10;
	int64_t _11;
	double _8;
	int64_t _12;
	int64_t _49_res_2;
	int64_t _56_j_4;
	int64_t _54_i_6;
	int64_t _49_res_7;
	int64_t _49_n_5;
	struct struct_1 _str_5;
	int64_t _13;
	int64_t _14;
	int64_t _56_j_1;
	int64_t _56_j_5;
	int64_t _49_n_6;
	struct struct_1 _str_6;
	int64_t _54_i_7;
	int64_t _49_res_8;
	int64_t _15;
	int64_t _16;
	int64_t _54_i_1;
	int64_t _54_i_8;
	int64_t _49_n_7;
	struct struct_1 _str_7;
	int64_t _49_res_9;
	int64_t _49_res_10;
	_str_0 = _str;
L60:; // incoming:1
	_0 = _str_0.length;
	_49_n_0 = _0;
	_49_res_0 = 0;
	_54_i_0 = 0;
	_54_i_2 = _54_i_0;
	_49_n_1 = _49_n_0;
	_str_1 = _str_0;
	_49_res_3 = _49_res_0;
	goto L61;
L61:; // incoming:2
	_3 = _54_i_2 < _49_n_1;
	if (!_3) {
		_49_res_10 = _49_res_3;
		goto L74;
	} else {
		_54_i_3 = _54_i_2;
		_49_n_2 = _49_n_1;
		_str_2 = _str_1;
		_49_res_4 = _49_res_3;
		goto L62;
	}
L62:; // incoming:1
	_56_j_0 = _54_i_3;
	_56_j_2 = _56_j_0;
	_49_n_3 = _49_n_2;
	_str_3 = _str_2;
	_54_i_4 = _54_i_3;
	_49_res_5 = _49_res_4;
	goto L63;
L63:; // incoming:2
	_4 = _56_j_2 < _49_n_3;
	if (!_4) {
		_54_i_8 = _54_i_4;
		_49_n_7 = _49_n_3;
		_str_7 = _str_3;
		_49_res_9 = _49_res_5;
		goto L73;
	} else {
		_str_4 = _str_3;
		_54_i_5 = _54_i_4;
		_56_j_3 = _56_j_2;
		_49_res_6 = _49_res_5;
		_49_n_4 = _49_n_3;
		goto L64;
	}
L64:; // incoming:1
	_5 = test_leetcode_areDistinct;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n139   | if areDistinct(str, i, j) {\n      |               ^\n");
	_6 = _5(_str_4, _54_i_5, _56_j_3);
	if (!_6) {
		_56_j_5 = _56_j_3;
		_49_n_6 = _49_n_4;
		_str_6 = _str_4;
		_54_i_7 = _54_i_5;
		_49_res_8 = _49_res_6;
		goto L69;
	} else {
		_56_j_4 = _56_j_3;
		_54_i_6 = _54_i_5;
		_49_res_7 = _49_res_6;
		_49_n_5 = _49_n_4;
		_str_5 = _str_4;
		goto L65;
	}
L65:; // incoming:1
	_7 = std_math_max;
	_9 = _56_j_4 - _54_i_6;
	_10 = 1;
	_11 = _9 + _10;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n140   | res = std.math.max(res, j - i + 1):Int\n      |                   ^\n");
	_8 = _7(_49_res_7, _11);
	_12 = (int64_t) _8;
	_49_res_2 = _12;
	_56_j_5 = _56_j_4;
	_49_n_6 = _49_n_5;
	_str_6 = _str_5;
	_54_i_7 = _54_i_6;
	_49_res_8 = _49_res_2;
	goto L69;
L69:; // incoming:2
	_13 = 1;
	_14 = _56_j_5 + _13;
	_56_j_1 = _14;
	_56_j_2 = _56_j_1;
	_49_n_3 = _49_n_6;
	_str_3 = _str_6;
	_54_i_4 = _54_i_7;
	_49_res_5 = _49_res_8;
	goto L63;
L73:; // incoming:1
	_15 = 1;
	_16 = _54_i_8 + _15;
	_54_i_1 = _16;
	_54_i_2 = _54_i_1;
	_49_n_1 = _49_n_7;
	_str_1 = _str_7;
	_49_res_3 = _49_res_9;
	goto L61;
L74:; // incoming:1
	retval = _49_res_10;
	goto end;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

bool test_leetcode_areDistinct(struct struct_1 _str, int64_t _i, int64_t _j)
{
	bool retval;
	bool _1;
	struct struct_7 _50_visited_0;
	int64_t _51_k_0;
	int64_t _i_0;
	struct struct_1 _str_0;
	int64_t _j_0;
	bool _2;
	int64_t _51_k_2;
	int64_t _j_1;
	struct struct_1 _str_1;
	struct struct_7 _50_visited_1;
	int8_t _3;
	int64_t _4;
	int64_t _52_charCode_0;
	bool _5;
	struct struct_1 _str_2;
	int64_t _51_k_3;
	struct struct_7 _50_visited_2;
	int64_t _j_2;
	bool _7;
	int64_t _8;
	int64_t _9;
	int64_t _51_k_1;
	struct struct_7 _50_visited_3;
	int64_t _52_charCode_1;
	int64_t _51_k_4;
	int64_t _j_3;
	struct struct_1 _str_3;
	_str_0 = _str;
	_i_0 = _i;
	_j_0 = _j;
L45:; // incoming:1
	_1 = 0;
	_50_visited_0 = (struct struct_7) {256, (bool[]){_1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1}};
	_51_k_0 = _i_0;
	_51_k_2 = _51_k_0;
	_j_1 = _j_0;
	_str_1 = _str_0;
	_50_visited_1 = _50_visited_0;
	goto L46;
L46:; // incoming:2
	_2 = _51_k_2 <= _j_1;
	if (!_2) {
		goto L53;
	} else {
		_str_2 = _str_1;
		_51_k_3 = _51_k_2;
		_50_visited_2 = _50_visited_1;
		_j_2 = _j_1;
		goto L47;
	}
L47:; // incoming:1
	_3 = _str_2.data[_51_k_3];
	_4 = (int64_t) _3;
	_52_charCode_0 = _4;
	_5 = _50_visited_2.data[_52_charCode_0];
	if (!_5) {
		_50_visited_3 = _50_visited_2;
		_52_charCode_1 = _52_charCode_0;
		_51_k_4 = _51_k_3;
		_j_3 = _j_2;
		_str_3 = _str_2;
		goto L50;
	} else {
		goto L48;
	}
L48:; // incoming:1
	retval = 0;
	goto end;
L50:; // incoming:1
	_7 = 1;
	_50_visited_3.data[_52_charCode_1] = _7;
	_8 = 1;
	_9 = _51_k_4 + _8;
	_51_k_1 = _9;
	_51_k_2 = _51_k_1;
	_j_1 = _j_3;
	_str_1 = _str_3;
	_50_visited_1 = _50_visited_3;
	goto L46;
L53:; // incoming:1
	retval = 1;
	goto end;
end:;
	stackTracePop(&stackTrace);
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
L54:; // incoming:1
	_1 = _x_0 > _y_0;
	if (!_1) {
		_y_1 = _y_0;
		goto L59;
	} else {
		_x_1 = _x_0;
		goto L56;
	}
L56:; // incoming:1
	_0 = _x_1;
	goto L57;
L57:; // incoming:2
	retval = _0;
	goto end;
L59:; // incoming:1
	_0 = _y_1;
	goto L57;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

void test_leetcode_test_findMedianSortedArrays()
{
	int64_t _1;
	int64_t _2;
	struct struct_4 _71_nums1_0;
	int64_t _4;
	struct struct_4 _71_nums2_0;
	float (*_5) (struct struct_4 _nums1, struct struct_4 _nums2);
	float _6;
	float _71_ans_0;
	void (*_7) (bool _predicate, struct struct_1 _msg);
	float _10;
	bool _9;
	struct struct_1 _11;
L110:; // incoming:1
	_1 = 1;
	_2 = 3;
	_71_nums1_0 = (struct struct_4) {2, (int64_t[]){_1, _2}};
	_4 = 2;
	_71_nums2_0 = (struct struct_4) {1, (int64_t[]){_4}};
	_5 = test_leetcode_findMedianSortedArrays;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n195   | ans := findMedianSortedArrays(nums1, nums2)\n      |                              ^\n");
	_6 = _5(_71_nums1_0, _71_nums2_0);
	_71_ans_0 = _6;
	_7 = std_debug_assert;
	_10 = 2.000000;
	_9 = _71_ans_0 == _10;
	_11 = (struct struct_1) {20, "no message specified"};
	stackTracePush(&stackTrace, "test/leetcode.orng: \n197   | std.debug.assert(ans == 2.0)\n      |                 ^\n");
	_7(_9, _11);
	goto end;
end:;
	stackTracePop(&stackTrace);
	return;
}

float test_leetcode_findMedianSortedArrays(struct struct_4 _nums1, struct struct_4 _nums2)
{
	float retval;
	int64_t _1;
	int64_t _2;
	int64_t _3;
	int64_t _4;
	struct struct_4 _0;
	struct struct_4 _60_merged_0;
	int64_t _60_i_0;
	int64_t _60_j_0;
	struct struct_4 _nums1_0;
	struct struct_4 _nums2_0;
	int64_t _7;
	int64_t _8;
	bool _9;
	int64_t _60_i_8;
	int64_t _60_j_7;
	struct struct_4 _60_merged_1;
	struct struct_4 _nums1_1;
	struct struct_4 _nums2_1;
	int8_t _10;
	int64_t _11;
	bool _12;
	struct struct_4 _nums1_2;
	int64_t _60_i_9;
	struct struct_4 _nums2_2;
	int64_t _60_j_8;
	struct struct_4 _60_merged_2;
	int64_t _13;
	bool _14;
	struct struct_4 _nums2_3;
	int64_t _60_j_9;
	struct struct_4 _nums1_3;
	int64_t _60_i_10;
	struct struct_4 _60_merged_3;
	struct struct_4 _nums1_4;
	int64_t _60_i_11;
	struct struct_4 _nums2_4;
	int64_t _60_j_10;
	struct struct_4 _60_merged_4;
	int64_t _15;
	int64_t _16;
	bool _17;
	struct struct_4 _nums1_5;
	int64_t _60_i_12;
	struct struct_4 _nums2_5;
	int64_t _60_j_11;
	struct struct_4 _60_merged_5;
	int64_t _18;
	int64_t _19;
	int64_t _20;
	int64_t _21;
	int64_t _60_i_5;
	int64_t _60_i_13;
	int64_t _60_j_12;
	struct struct_4 _nums1_6;
	struct struct_4 _60_merged_6;
	struct struct_4 _nums2_6;
	int64_t _22;
	int64_t _23;
	int64_t _24;
	int64_t _25;
	int64_t _60_j_5;
	int64_t _60_i_14;
	int64_t _60_j_13;
	struct struct_4 _nums2_7;
	struct struct_4 _60_merged_7;
	struct struct_4 _nums1_7;
	int64_t _26;
	bool _27;
	struct struct_4 _nums1_8;
	int64_t _60_i_15;
	int64_t _60_j_14;
	struct struct_4 _60_merged_8;
	struct struct_4 _nums2_8;
	int64_t _28;
	int64_t _29;
	int64_t _30;
	int64_t _31;
	int64_t _60_i_7;
	int64_t _60_i_16;
	int64_t _60_j_15;
	struct struct_4 _nums1_9;
	struct struct_4 _60_merged_9;
	struct struct_4 _nums2_9;
	int64_t _32;
	bool _33;
	struct struct_4 _nums2_10;
	int64_t _60_j_16;
	int64_t _60_i_17;
	struct struct_4 _60_merged_10;
	struct struct_4 _nums1_10;
	int64_t _34;
	int64_t _35;
	int64_t _36;
	int64_t _37;
	int64_t _60_j_6;
	int64_t _60_i_18;
	int64_t _60_j_17;
	struct struct_4 _nums2_11;
	struct struct_4 _60_merged_11;
	struct struct_4 _nums1_11;
	struct struct_4 _nums1_12;
	int64_t _60_i_19;
	struct struct_4 _nums2_12;
	int64_t _60_j_18;
	struct struct_4 _60_merged_12;
	float _38;
	int64_t _40;
	int64_t _41;
	int64_t _42;
	int64_t _43;
	bool _39;
	struct struct_4 _60_merged_13;
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
	struct struct_4 _60_merged_14;
	int64_t* _66;
	struct struct_4 _60_merged_15;
	int64_t _59;
	int64_t _60;
	int64_t _61;
	int64_t _62;
	float _63;
	struct struct_4 _60_merged_16;
	_nums1_0 = _nums1;
	_nums2_0 = _nums2;
L76:; // incoming:1
	_1 = _nums1_0.length;
	_2 = _nums2_0.length;
	_3 = _1 + _2;
	_4 = 0;
	_0 = (struct struct_4) {_3, malloc(sizeof(int64_t) * _3)}; for (int i_3 = 0; i_3 < _3; i_3++) {_0.data[i_3] = _4;}
	_60_merged_0 = _0;
	_60_i_0 = 0;
	_60_j_0 = 0;
	_60_i_8 = _60_i_0;
	_60_j_7 = _60_j_0;
	_60_merged_1 = _60_merged_0;
	_nums1_1 = _nums1_0;
	_nums2_1 = _nums2_0;
	goto L77;
L77:; // incoming:6
	_7 = _60_i_8 + _60_j_7;
	_8 = _60_merged_1.length;
	_9 = _7 < _8;
	if (!_9) {
		_60_merged_13 = _60_merged_1;
		goto L101;
	} else {
		_nums1_2 = _nums1_1;
		_60_i_9 = _60_i_8;
		_nums2_2 = _nums2_1;
		_60_j_8 = _60_j_7;
		_60_merged_2 = _60_merged_1;
		goto L78;
	}
L78:; // incoming:1
	_11 = _nums1_2.length;
	_12 = _60_i_9 < _11;
	if (!_12) {
		_nums1_12 = _nums1_2;
		_60_i_19 = _60_i_9;
		_nums2_12 = _nums2_2;
		_60_j_18 = _60_j_8;
		_60_merged_12 = _60_merged_2;
		goto L100;
	} else {
		_nums2_3 = _nums2_2;
		_60_j_9 = _60_j_8;
		_nums1_3 = _nums1_2;
		_60_i_10 = _60_i_9;
		_60_merged_3 = _60_merged_2;
		goto L79;
	}
L79:; // incoming:1
	_13 = _nums2_3.length;
	_14 = _60_j_9 < _13;
	_10 = _14;
	_nums1_4 = _nums1_3;
	_60_i_11 = _60_i_10;
	_nums2_4 = _nums2_3;
	_60_j_10 = _60_j_9;
	_60_merged_4 = _60_merged_3;
	goto L80;
L80:; // incoming:2
	if (!_10) {
		_nums1_8 = _nums1_4;
		_60_i_15 = _60_i_11;
		_60_j_14 = _60_j_10;
		_60_merged_8 = _60_merged_4;
		_nums2_8 = _nums2_4;
		goto L91;
	} else {
		_nums1_5 = _nums1_4;
		_60_i_12 = _60_i_11;
		_nums2_5 = _nums2_4;
		_60_j_11 = _60_j_10;
		_60_merged_5 = _60_merged_4;
		goto L81;
	}
L81:; // incoming:1
	_15 = _nums1_5.data[_60_i_12];
	_16 = _nums2_5.data[_60_j_11];
	_17 = _15 < _16;
	if (!_17) {
		_60_i_14 = _60_i_12;
		_60_j_13 = _60_j_11;
		_nums2_7 = _nums2_5;
		_60_merged_7 = _60_merged_5;
		_nums1_7 = _nums1_5;
		goto L89;
	} else {
		_60_i_13 = _60_i_12;
		_60_j_12 = _60_j_11;
		_nums1_6 = _nums1_5;
		_60_merged_6 = _60_merged_5;
		_nums2_6 = _nums2_5;
		goto L82;
	}
L82:; // incoming:1
	_18 = _60_i_13 + _60_j_12;
	_19 = _nums1_6.data[_60_i_13];
	_60_merged_6.data[_18] = _19;
	_20 = 1;
	_21 = _60_i_13 + _20;
	_60_i_5 = _21;
	_60_i_8 = _60_i_5;
	_60_j_7 = _60_j_12;
	_60_merged_1 = _60_merged_6;
	_nums1_1 = _nums1_6;
	_nums2_1 = _nums2_6;
	goto L77;
L89:; // incoming:1
	_22 = _60_i_14 + _60_j_13;
	_23 = _nums2_7.data[_60_j_13];
	_60_merged_7.data[_22] = _23;
	_24 = 1;
	_25 = _60_j_13 + _24;
	_60_j_5 = _25;
	_60_i_8 = _60_i_14;
	_60_j_7 = _60_j_5;
	_60_merged_1 = _60_merged_7;
	_nums1_1 = _nums1_7;
	_nums2_1 = _nums2_7;
	goto L77;
L91:; // incoming:1
	_26 = _nums1_8.length;
	_27 = _60_i_15 < _26;
	if (!_27) {
		_nums2_10 = _nums2_8;
		_60_j_16 = _60_j_14;
		_60_i_17 = _60_i_15;
		_60_merged_10 = _60_merged_8;
		_nums1_10 = _nums1_8;
		goto L95;
	} else {
		_60_i_16 = _60_i_15;
		_60_j_15 = _60_j_14;
		_nums1_9 = _nums1_8;
		_60_merged_9 = _60_merged_8;
		_nums2_9 = _nums2_8;
		goto L92;
	}
L92:; // incoming:1
	_28 = _60_i_16 + _60_j_15;
	_29 = _nums1_9.data[_60_i_16];
	_60_merged_9.data[_28] = _29;
	_30 = 1;
	_31 = _60_i_16 + _30;
	_60_i_7 = _31;
	_60_i_8 = _60_i_7;
	_60_j_7 = _60_j_15;
	_60_merged_1 = _60_merged_9;
	_nums1_1 = _nums1_9;
	_nums2_1 = _nums2_9;
	goto L77;
L95:; // incoming:1
	_32 = _nums2_10.length;
	_33 = _60_j_16 < _32;
	if (!_33) {
		_60_i_8 = _60_i_17;
		_60_j_7 = _60_j_16;
		_60_merged_1 = _60_merged_10;
		_nums1_1 = _nums1_10;
		_nums2_1 = _nums2_10;
		goto L77;
	} else {
		_60_i_18 = _60_i_17;
		_60_j_17 = _60_j_16;
		_nums2_11 = _nums2_10;
		_60_merged_11 = _60_merged_10;
		_nums1_11 = _nums1_10;
		goto L96;
	}
L96:; // incoming:1
	_34 = _60_i_18 + _60_j_17;
	_35 = _nums2_11.data[_60_j_17];
	_60_merged_11.data[_34] = _35;
	_36 = 1;
	_37 = _60_j_17 + _36;
	_60_j_6 = _37;
	_60_i_8 = _60_i_18;
	_60_j_7 = _60_j_6;
	_60_merged_1 = _60_merged_11;
	_nums1_1 = _nums1_11;
	_nums2_1 = _nums2_11;
	goto L77;
L100:; // incoming:1
	_10 = 0;
	_nums1_4 = _nums1_12;
	_60_i_11 = _60_i_19;
	_nums2_4 = _nums2_12;
	_60_j_10 = _60_j_18;
	_60_merged_4 = _60_merged_12;
	goto L80;
L101:; // incoming:1
	_40 = _60_merged_13.length;
	_41 = 2;
	_42 = _40 % _41;
	_43 = 0;
	_39 = _42 == _43;
	if (!_39) {
		_60_merged_16 = _60_merged_13;
		goto L108;
	} else {
		_60_merged_14 = _60_merged_13;
		goto L102;
	}
L102:; // incoming:1
	_44 = _60_merged_14.length;
	_45 = 2;
	_46 = _44 / _45;
	_47 = _60_merged_14.data[_46];
	_48 = _60_merged_14.length;
	_49 = 2;
	_50 = _48 / _49;
	_51 = 1;
	_52 = _50 + _51;
	_53 = _60_merged_14.data[_52];
	_54 = _47 + _53;
	_55 = _54;
	_56 = 2.000000;
	_57 = _55 / _56;
	_38 = _57;
	_60_merged_15 = _60_merged_14;
	goto L106;
L106:; // incoming:2
	_66 = _60_merged_15.data;
	free(_66);
	retval = _38;
	goto end;
L108:; // incoming:1
	_59 = _60_merged_16.length;
	_60 = 2;
	_61 = _59 / _60;
	_62 = _60_merged_16.data[_61];
	_63 = (float) _62;
	_38 = _63;
	_60_merged_15 = _60_merged_16;
	goto L106;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

void test_leetcode_test_longestPalindrome()
{
	struct struct_1 _0;
	struct struct_1 _80_s_0;
	struct struct_1 (*_1) (struct struct_1 _s);
	struct struct_1 _2;
	struct struct_1 _80_ans_0;
	void (*_3) (bool _predicate, struct struct_1 _msg);
	int8_t _5;
	bool (*_6) (struct struct_1 _a, struct struct_1 _b);
	struct struct_1 _8;
	bool _7;
	struct struct_1 _12;
	bool (*_9) (struct struct_1 _a, struct struct_1 _b);
	struct struct_1 _11;
	bool _10;
	struct struct_1 _80_ans_1;
L147:; // incoming:1
	_0 = (struct struct_1) {5, "babad"};
	_80_s_0 = _0;
	_1 = test_leetcode_longestPalindrome;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n229   | ans := longestPalindrome(s)\n      |                         ^\n");
	_2 = _1(_80_s_0);
	_80_ans_0 = _2;
	_3 = std_debug_assert;
	_6 = std_string_equals;
	_8 = (struct struct_1) {3, "bab"};
	stackTracePush(&stackTrace, "test/leetcode.orng: \n231   | std.debug.assert(std.string.equals(ans, \"bab\") || std.string.equals(ans, \"aba\"))\n      |                                   ^\n");
	_7 = _6(_80_ans_0, _8);
	if (!_7) {
		_80_ans_1 = _80_ans_0;
		goto L150;
	} else {
		goto L148;
	}
L148:; // incoming:1
	_5 = 1;
	goto L149;
L149:; // incoming:2
	_12 = (struct struct_1) {20, "no message specified"};
	stackTracePush(&stackTrace, "test/leetcode.orng: \n231   | std.debug.assert(std.string.equals(ans, \"bab\") || std.string.equals(ans, \"aba\"))\n      |                 ^\n");
	_3(_5, _12);
	goto end;
L150:; // incoming:1
	_9 = std_string_equals;
	_11 = (struct struct_1) {3, "aba"};
	stackTracePush(&stackTrace, "test/leetcode.orng: \n231   | std.debug.assert(std.string.equals(ans, \"bab\") || std.string.equals(ans, \"aba\"))\n      |                                                                    ^\n");
	_10 = _9(_80_ans_1, _11);
	_5 = _10;
	goto L149;
end:;
	stackTracePop(&stackTrace);
	return;
}

struct struct_1 test_leetcode_longestPalindrome(struct struct_1 _s)
{
	struct struct_1 retval;
	int64_t _72_start_0;
	int64_t _72_end_0;
	int64_t _76_i_0;
	struct struct_1 _s_0;
	int64_t _3;
	bool _4;
	struct struct_1 _s_1;
	int64_t _76_i_2;
	int64_t _72_end_5;
	int64_t _72_start_5;
	int64_t (*_5) (struct struct_1 _s, int64_t _left, int64_t _right);
	int64_t _6;
	int64_t _77_len1_0;
	int64_t (*_7) (struct struct_1 _s, int64_t _left, int64_t _right);
	int64_t _9;
	int64_t _10;
	int64_t _8;
	int64_t _77_len2_0;
	double (*_11) (double _x, double _y);
	double _12;
	int64_t _13;
	int64_t _77_len_0;
	int64_t _14;
	bool _15;
	struct struct_1 _s_2;
	int64_t _76_i_3;
	int64_t _72_end_6;
	int64_t _72_start_6;
	int64_t _16;
	int64_t _17;
	int64_t _18;
	int64_t _19;
	int64_t _20;
	int64_t _21;
	int64_t _22;
	int64_t _23;
	int64_t _24;
	int64_t _72_end_4;
	int64_t _72_start_4;
	int64_t _77_len_1;
	int64_t _76_i_4;
	struct struct_1 _s_3;
	int64_t _25;
	int64_t _26;
	int64_t _76_i_1;
	int64_t _76_i_5;
	struct struct_1 _s_4;
	int64_t _72_end_7;
	int64_t _72_start_7;
	int64_t _27;
	int64_t _28;
	int64_t _29;
	int8_t* _30;
	int8_t* _31;
	struct struct_1 _32;
	int64_t _72_end_8;
	int64_t _72_start_8;
	struct struct_1 _s_5;
	_s_0 = _s;
L124:; // incoming:1
	_72_start_0 = 0;
	_72_end_0 = 0;
	_76_i_0 = 0;
	_s_1 = _s_0;
	_76_i_2 = _76_i_0;
	_72_end_5 = _72_end_0;
	_72_start_5 = _72_start_0;
	goto L125;
L125:; // incoming:2
	_3 = _s_1.length;
	_4 = _76_i_2 < _3;
	if (!_4) {
		_72_end_8 = _72_end_5;
		_72_start_8 = _72_start_5;
		_s_5 = _s_1;
		goto L134;
	} else {
		_s_2 = _s_1;
		_76_i_3 = _76_i_2;
		_72_end_6 = _72_end_5;
		_72_start_6 = _72_start_5;
		goto L126;
	}
L126:; // incoming:1
	_5 = test_leetcode_expandAroundCenter;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n215   | len1 := expandAroundCenter(s, i, i)\n      |                           ^\n");
	_6 = _5(_s_2, _76_i_3, _76_i_3);
	_77_len1_0 = _6;
	_7 = test_leetcode_expandAroundCenter;
	_9 = 1;
	_10 = _76_i_3 + _9;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n216   | len2 := expandAroundCenter(s, i, i + 1)\n      |                           ^\n");
	_8 = _7(_s_2, _76_i_3, _10);
	_77_len2_0 = _8;
	_11 = std_math_max;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n217   | len := std.math.max(len1, len2):Int\n      |                    ^\n");
	_12 = _11(_77_len1_0, _77_len2_0);
	_13 = (int64_t) _12;
	_77_len_0 = _13;
	_14 = _72_end_6 - _72_start_6;
	_15 = _77_len_0 > _14;
	if (!_15) {
		_76_i_5 = _76_i_3;
		_s_4 = _s_2;
		_72_end_7 = _72_end_6;
		_72_start_7 = _72_start_6;
		goto L132;
	} else {
		_77_len_1 = _77_len_0;
		_76_i_4 = _76_i_3;
		_s_3 = _s_2;
		goto L127;
	}
L127:; // incoming:1
	_16 = 1;
	_17 = _77_len_1 - _16;
	_18 = _17;
	_19 = 2;
	_20 = _18 / _19;
	_21 = _76_i_4 - _20;
	_22 = 2;
	_23 = _77_len_1 / _22;
	_24 = _76_i_4 + _23;
	_72_end_4 = _24;
	_72_start_4 = _21;
	_76_i_5 = _76_i_4;
	_s_4 = _s_3;
	_72_end_7 = _72_end_4;
	_72_start_7 = _72_start_4;
	goto L132;
L132:; // incoming:2
	_25 = 1;
	_26 = _76_i_5 + _25;
	_76_i_1 = _26;
	_s_1 = _s_4;
	_76_i_2 = _76_i_1;
	_72_end_5 = _72_end_7;
	_72_start_5 = _72_start_7;
	goto L125;
L134:; // incoming:1
	_27 = 1;
	_28 = _72_end_8 + _27;
	_29 = _28 - _72_start_8;
	_30 = _s_5.data;
	_31 = _30 + _72_start_8;
	_32 = (struct struct_1) {_29, _31};
	retval = _32;
	goto end;
end:;
	stackTracePop(&stackTrace);
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
	int8_t _7;
	int8_t _8;
	bool _6;
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
L112:; // incoming:2
	_2 = 0;
	_3 = _left_3 >= _2;
	if (!_3) {
		_s_7 = _s_0;
		_left_11 = _left_3;
		_right_11 = _right_3;
		goto L123;
	} else {
		_s_1 = _s_0;
		_right_4 = _right_3;
		_left_4 = _left_3;
		goto L113;
	}
L113:; // incoming:1
	_4 = _s_1.length;
	_5 = _right_4 < _4;
	_1 = _5;
	_s_2 = _s_1;
	_left_5 = _left_4;
	_right_5 = _right_4;
	goto L114;
L114:; // incoming:2
	if (!_1) {
		_left_10 = _left_5;
		_right_10 = _right_5;
		_s_6 = _s_2;
		goto L122;
	} else {
		_s_3 = _s_2;
		_left_6 = _left_5;
		_right_6 = _right_5;
		goto L115;
	}
L115:; // incoming:1
	_7 = _s_3.data[_left_6];
	_8 = _s_3.data[_right_6];
	_6 = _7 == _8;
	_0 = _6;
	_left_7 = _left_6;
	_right_7 = _right_6;
	_s_4 = _s_3;
	goto L116;
L116:; // incoming:2
	if (!_0) {
		_right_9 = _right_7;
		_left_9 = _left_7;
		goto L120;
	} else {
		_left_8 = _left_7;
		_right_8 = _right_7;
		_s_5 = _s_4;
		goto L117;
	}
L117:; // incoming:1
	_9 = 1;
	_10 = _left_8 - _9;
	_11 = 1;
	_12 = _right_8 + _11;
	_left_2 = _10;
	_right_2 = _12;
	_left_3 = _left_2;
	_s_0 = _s_5;
	_right_3 = _right_2;
	goto L112;
L120:; // incoming:1
	_13 = _right_9 - _left_9;
	_14 = 1;
	_15 = _13 - _14;
	retval = _15;
	goto end;
L122:; // incoming:1
	_0 = 0;
	_left_7 = _left_10;
	_right_7 = _right_10;
	_s_4 = _s_6;
	goto L116;
L123:; // incoming:1
	_1 = 0;
	_s_2 = _s_7;
	_left_5 = _left_11;
	_right_5 = _right_11;
	goto L114;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

bool std_string_equals(struct struct_1 _a, struct struct_1 _b)
{
	bool retval;
	int64_t _2;
	int64_t _3;
	bool _1;
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
	int8_t _9;
	int8_t _10;
	bool _8;
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
L136:; // incoming:1
	_2 = _a_0.length;
	_3 = _b_0.length;
	_1 = _2 != _3;
	if (!_1) {
		_a_1 = _a_0;
		_b_1 = _b_0;
		goto L138;
	} else {
		goto L137;
	}
L137:; // incoming:1
	retval = 0;
	goto end;
L138:; // incoming:1
	_19_i_0 = 0;
	_a_2 = _a_1;
	_19_i_2 = _19_i_0;
	_b_2 = _b_1;
	goto L139;
L139:; // incoming:2
	_6 = _a_2.length;
	_7 = _19_i_2 < _6;
	if (!_7) {
		goto L146;
	} else {
		_a_3 = _a_2;
		_19_i_3 = _19_i_2;
		_b_3 = _b_2;
		goto L140;
	}
L140:; // incoming:1
	_9 = _a_3.data[_19_i_3];
	_10 = _b_3.data[_19_i_3];
	_8 = _9 != _10;
	if (!_8) {
		_19_i_4 = _19_i_3;
		_a_4 = _a_3;
		_b_4 = _b_3;
		goto L145;
	} else {
		goto L141;
	}
L141:; // incoming:1
	retval = 0;
	goto end;
L145:; // incoming:1
	_12 = 1;
	_13 = _19_i_4 + _12;
	_19_i_1 = _13;
	_a_2 = _a_4;
	_19_i_2 = _19_i_1;
	_b_2 = _b_4;
	goto L139;
L146:; // incoming:1
	retval = 1;
	goto end;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

void test_leetcode_test_convert()
{
	struct struct_1 (*_0) (struct struct_1 _s, int64_t _numRows);
	struct struct_1 _2;
	int64_t _3;
	struct struct_1 _1;
	struct struct_1 _96_ans_0;
	void (*_4) (bool _predicate, struct struct_1 _msg);
	bool (*_6) (struct struct_1 _a, struct struct_1 _b);
	struct struct_1 _8;
	bool _7;
	struct struct_1 _9;
L192:; // incoming:1
	_0 = test_leetcode_convert;
	_2 = (struct struct_1) {14, "PAYPALISHIRING"};
	_3 = 3;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n283   | ans := convert(\"PAYPALISHIRING\", 3)\n      |               ^\n");
	_1 = _0(_2, _3);
	_96_ans_0 = _1;
	_4 = std_debug_assert;
	_6 = std_string_equals;
	_8 = (struct struct_1) {14, "PAHNAPLSIIGYIR"};
	stackTracePush(&stackTrace, "test/leetcode.orng: \n285   | std.debug.assert(std.string.equals(ans, \"PAHNAPLSIIGYIR\"))\n      |                                   ^\n");
	_7 = _6(_96_ans_0, _8);
	_9 = (struct struct_1) {20, "no message specified"};
	stackTracePush(&stackTrace, "test/leetcode.orng: \n285   | std.debug.assert(std.string.equals(ans, \"PAHNAPLSIIGYIR\"))\n      |                 ^\n");
	_4(_7, _9);
	goto end;
end:;
	stackTracePop(&stackTrace);
	return;
}

struct struct_1 test_leetcode_convert(struct struct_1 _s, int64_t _numRows)
{
	struct struct_1 retval;
	int64_t _1;
	int8_t _2;
	struct struct_2 _0;
	struct struct_2 _81_board_0;
	int64_t _81_x_0;
	int64_t _81_y_0;
	bool _81_diagnolizing_0;
	int64_t _85_i_0;
	struct struct_1 _s_0;
	int64_t _numRows_0;
	int64_t _7;
	bool _8;
	struct struct_1 _s_1;
	int64_t _85_i_2;
	struct struct_2 _81_board_1;
	int64_t _81_x_4;
	int64_t _81_y_5;
	bool _81_diagnolizing_5;
	int64_t _numRows_1;
	struct struct_1 _9;
	int8_t _10;
	struct struct_2 _81_board_2;
	int64_t _81_x_5;
	struct struct_1 _s_2;
	int64_t _85_i_3;
	int64_t _81_y_6;
	bool _81_diagnolizing_6;
	int64_t _numRows_2;
	int64_t _11;
	int64_t _12;
	int64_t _81_y_1;
	int64_t _13;
	int64_t _14;
	int64_t _81_x_1;
	int64_t _16;
	bool _15;
	int64_t _81_y_7;
	int64_t _81_x_6;
	int64_t _85_i_4;
	struct struct_1 _s_3;
	struct struct_2 _81_board_3;
	int64_t _numRows_3;
	bool _81_diagnolizing_7;
	bool _81_diagnolizing_3;
	int64_t _85_i_5;
	struct struct_1 _s_4;
	struct struct_2 _81_board_4;
	int64_t _81_x_7;
	int64_t _81_y_8;
	int64_t _numRows_4;
	int64_t _26;
	int64_t _27;
	int64_t _85_i_1;
	int64_t _85_i_6;
	struct struct_1 _s_5;
	struct struct_2 _81_board_5;
	int64_t _81_x_8;
	int64_t _81_y_9;
	bool _81_diagnolizing_8;
	int64_t _numRows_5;
	int64_t _18;
	int64_t _19;
	int64_t _81_y_2;
	bool _20;
	int64_t _81_y_10;
	int64_t _numRows_6;
	int64_t _81_x_9;
	int64_t _85_i_7;
	struct struct_1 _s_6;
	struct struct_2 _81_board_6;
	bool _81_diagnolizing_9;
	int64_t _22;
	int64_t _23;
	int64_t _24;
	int64_t _25;
	int64_t _81_x_3;
	int64_t _81_y_4;
	bool _81_diagnolizing_4;
	int64_t _81_y_11;
	int64_t _81_x_10;
	int64_t _85_i_8;
	struct struct_1 _s_7;
	struct struct_2 _81_board_7;
	int64_t _numRows_7;
	int64_t _29;
	int8_t _30;
	struct struct_1 _28;
	struct struct_1 _81_retval_0;
	int64_t _81_k_0;
	int64_t _91_j_0;
	struct struct_1 _s_8;
	int64_t _numRows_8;
	struct struct_2 _81_board_8;
	bool _33;
	int64_t _91_j_2;
	int64_t _numRows_9;
	struct struct_1 _s_9;
	struct struct_2 _81_board_9;
	struct struct_1 _81_retval_1;
	int64_t _81_k_3;
	int64_t _93_i_0;
	struct struct_1 _s_10;
	struct struct_2 _81_board_10;
	int64_t _91_j_3;
	struct struct_1 _81_retval_2;
	int64_t _81_k_4;
	int64_t _numRows_10;
	int64_t _35;
	bool _36;
	struct struct_1 _s_11;
	int64_t _93_i_2;
	struct struct_2 _81_board_11;
	int64_t _91_j_4;
	struct struct_1 _81_retval_3;
	int64_t _81_k_5;
	int64_t _numRows_11;
	struct struct_1 _38;
	int8_t _39;
	int8_t _40;
	bool _37;
	struct struct_2 _81_board_12;
	int64_t _93_i_3;
	int64_t _91_j_5;
	struct struct_1 _81_retval_4;
	int64_t _81_k_6;
	struct struct_1 _s_12;
	int64_t _numRows_12;
	struct struct_1 _41;
	int8_t _42;
	int64_t _43;
	int64_t _44;
	int64_t _81_k_2;
	struct struct_2 _81_board_13;
	int64_t _93_i_4;
	int64_t _91_j_6;
	struct struct_1 _81_retval_5;
	int64_t _81_k_7;
	struct struct_1 _s_13;
	int64_t _numRows_13;
	int64_t _45;
	int64_t _46;
	int64_t _93_i_1;
	int64_t _93_i_5;
	struct struct_1 _s_14;
	struct struct_2 _81_board_14;
	int64_t _91_j_7;
	struct struct_1 _81_retval_6;
	int64_t _81_k_8;
	int64_t _numRows_14;
	int64_t _47;
	int64_t _48;
	int64_t _91_j_1;
	int64_t _91_j_8;
	int64_t _numRows_15;
	struct struct_1 _s_15;
	struct struct_2 _81_board_15;
	struct struct_1 _81_retval_7;
	int64_t _81_k_9;
	int64_t _83_i_0;
	struct struct_1 _s_16;
	struct struct_1 _81_retval_8;
	int64_t _51;
	bool _52;
	struct struct_1 _s_17;
	int64_t _83_i_2;
	struct struct_1 _81_retval_9;
	int64_t _53;
	int64_t _54;
	int64_t _83_i_1;
	int64_t _83_i_3;
	struct struct_1 _s_18;
	struct struct_1 _81_retval_10;
	struct struct_1 _81_retval_11;
	_s_0 = _s;
	_numRows_0 = _numRows;
L151:; // incoming:1
	_1 = _s_0.length;
	_2 = 0;
	_0 = (struct struct_2) {_1, malloc(sizeof(struct struct_1) * _1)}; for (int i_1 = 0; i_1 < _1; i_1++) {_0.data[i_1] = (struct struct_1) {_numRows_0, malloc(sizeof(int8_t) * _numRows_0)}; for (int i_numRows_0 = 0; i_numRows_0 < _numRows_0; i_numRows_0++) {_0.data[i_1].data[i_numRows_0] = _2;}}
	_81_board_0 = _0;
	_81_x_0 = 0;
	_81_y_0 = 0;
	_81_diagnolizing_0 = 0;
	_85_i_0 = 0;
	_s_1 = _s_0;
	_85_i_2 = _85_i_0;
	_81_board_1 = _81_board_0;
	_81_x_4 = _81_x_0;
	_81_y_5 = _81_y_0;
	_81_diagnolizing_5 = _81_diagnolizing_0;
	_numRows_1 = _numRows_0;
	goto L152;
L152:; // incoming:2
	_7 = _s_1.length;
	_8 = _85_i_2 < _7;
	if (!_8) {
		_s_8 = _s_1;
		_numRows_8 = _numRows_1;
		_81_board_8 = _81_board_1;
		goto L169;
	} else {
		_81_board_2 = _81_board_1;
		_81_x_5 = _81_x_4;
		_s_2 = _s_1;
		_85_i_3 = _85_i_2;
		_81_y_6 = _81_y_5;
		_81_diagnolizing_6 = _81_diagnolizing_5;
		_numRows_2 = _numRows_1;
		goto L153;
	}
L153:; // incoming:1
	_10 = _s_2.data[_85_i_3];
	(_81_board_2.data[_81_x_5]).data[_81_y_6] = _10;
	if (!_81_diagnolizing_6) {
		_81_y_10 = _81_y_6;
		_numRows_6 = _numRows_2;
		_81_x_9 = _81_x_5;
		_85_i_7 = _85_i_3;
		_s_6 = _s_2;
		_81_board_6 = _81_board_2;
		_81_diagnolizing_9 = _81_diagnolizing_6;
		goto L163;
	} else {
		_81_y_7 = _81_y_6;
		_81_x_6 = _81_x_5;
		_85_i_4 = _85_i_3;
		_s_3 = _s_2;
		_81_board_3 = _81_board_2;
		_numRows_3 = _numRows_2;
		_81_diagnolizing_7 = _81_diagnolizing_6;
		goto L154;
	}
L154:; // incoming:1
	_11 = 1;
	_12 = _81_y_7 - _11;
	_81_y_1 = _12;
	_13 = 1;
	_14 = _81_x_6 + _13;
	_81_x_1 = _14;
	_16 = 0;
	_15 = _81_y_1 == _16;
	if (!_15) {
		_85_i_6 = _85_i_4;
		_s_5 = _s_3;
		_81_board_5 = _81_board_3;
		_81_x_8 = _81_x_1;
		_81_y_9 = _81_y_1;
		_81_diagnolizing_8 = _81_diagnolizing_7;
		_numRows_5 = _numRows_3;
		goto L161;
	} else {
		_85_i_5 = _85_i_4;
		_s_4 = _s_3;
		_81_board_4 = _81_board_3;
		_81_x_7 = _81_x_1;
		_81_y_8 = _81_y_1;
		_numRows_4 = _numRows_3;
		goto L155;
	}
L155:; // incoming:1
	_81_diagnolizing_3 = 0;
	_85_i_6 = _85_i_5;
	_s_5 = _s_4;
	_81_board_5 = _81_board_4;
	_81_x_8 = _81_x_7;
	_81_y_9 = _81_y_8;
	_81_diagnolizing_8 = _81_diagnolizing_3;
	_numRows_5 = _numRows_4;
	goto L161;
L161:; // incoming:4
	_26 = 1;
	_27 = _85_i_6 + _26;
	_85_i_1 = _27;
	_s_1 = _s_5;
	_85_i_2 = _85_i_1;
	_81_board_1 = _81_board_5;
	_81_x_4 = _81_x_8;
	_81_y_5 = _81_y_9;
	_81_diagnolizing_5 = _81_diagnolizing_8;
	_numRows_1 = _numRows_5;
	goto L152;
L163:; // incoming:1
	_18 = 1;
	_19 = _81_y_10 + _18;
	_81_y_2 = _19;
	_20 = _81_y_2 == _numRows_6;
	if (!_20) {
		_85_i_6 = _85_i_7;
		_s_5 = _s_6;
		_81_board_5 = _81_board_6;
		_81_x_8 = _81_x_9;
		_81_y_9 = _81_y_2;
		_81_diagnolizing_8 = _81_diagnolizing_9;
		_numRows_5 = _numRows_6;
		goto L161;
	} else {
		_81_y_11 = _81_y_2;
		_81_x_10 = _81_x_9;
		_85_i_8 = _85_i_7;
		_s_7 = _s_6;
		_81_board_7 = _81_board_6;
		_numRows_7 = _numRows_6;
		goto L164;
	}
L164:; // incoming:1
	_22 = 2;
	_23 = _81_y_11 - _22;
	_24 = 1;
	_25 = _81_x_10 + _24;
	_81_x_3 = _25;
	_81_y_4 = _23;
	_81_diagnolizing_4 = 1;
	_85_i_6 = _85_i_8;
	_s_5 = _s_7;
	_81_board_5 = _81_board_7;
	_81_x_8 = _81_x_3;
	_81_y_9 = _81_y_4;
	_81_diagnolizing_8 = _81_diagnolizing_4;
	_numRows_5 = _numRows_7;
	goto L161;
L169:; // incoming:1
	_29 = _s_8.length;
	_30 = 0;
	_28 = (struct struct_1) {_29, malloc(sizeof(int8_t) * _29)}; for (int i_29 = 0; i_29 < _29; i_29++) {_28.data[i_29] = _30;}
	_81_retval_0 = _28;
	_81_k_0 = 0;
	_91_j_0 = 0;
	_91_j_2 = _91_j_0;
	_numRows_9 = _numRows_8;
	_s_9 = _s_8;
	_81_board_9 = _81_board_8;
	_81_retval_1 = _81_retval_0;
	_81_k_3 = _81_k_0;
	goto L170;
L170:; // incoming:2
	_33 = _91_j_2 < _numRows_9;
	if (!_33) {
		_s_16 = _s_9;
		_81_retval_8 = _81_retval_1;
		goto L184;
	} else {
		_s_10 = _s_9;
		_81_board_10 = _81_board_9;
		_91_j_3 = _91_j_2;
		_81_retval_2 = _81_retval_1;
		_81_k_4 = _81_k_3;
		_numRows_10 = _numRows_9;
		goto L171;
	}
L171:; // incoming:1
	_93_i_0 = 0;
	_s_11 = _s_10;
	_93_i_2 = _93_i_0;
	_81_board_11 = _81_board_10;
	_91_j_4 = _91_j_3;
	_81_retval_3 = _81_retval_2;
	_81_k_5 = _81_k_4;
	_numRows_11 = _numRows_10;
	goto L172;
L172:; // incoming:2
	_35 = _s_11.length;
	_36 = _93_i_2 < _35;
	if (!_36) {
		_91_j_8 = _91_j_4;
		_numRows_15 = _numRows_11;
		_s_15 = _s_11;
		_81_board_15 = _81_board_11;
		_81_retval_7 = _81_retval_3;
		_81_k_9 = _81_k_5;
		goto L182;
	} else {
		_81_board_12 = _81_board_11;
		_93_i_3 = _93_i_2;
		_91_j_5 = _91_j_4;
		_81_retval_4 = _81_retval_3;
		_81_k_6 = _81_k_5;
		_s_12 = _s_11;
		_numRows_12 = _numRows_11;
		goto L173;
	}
L173:; // incoming:1
	_38 = _81_board_12.data[_93_i_3];
	_39 = _38.data[_91_j_5];
	_40 = 0;
	_37 = _39 != _40;
	if (!_37) {
		_93_i_5 = _93_i_3;
		_s_14 = _s_12;
		_81_board_14 = _81_board_12;
		_91_j_7 = _91_j_5;
		_81_retval_6 = _81_retval_4;
		_81_k_8 = _81_k_6;
		_numRows_14 = _numRows_12;
		goto L178;
	} else {
		_81_board_13 = _81_board_12;
		_93_i_4 = _93_i_3;
		_91_j_6 = _91_j_5;
		_81_retval_5 = _81_retval_4;
		_81_k_7 = _81_k_6;
		_s_13 = _s_12;
		_numRows_13 = _numRows_12;
		goto L174;
	}
L174:; // incoming:1
	_41 = _81_board_13.data[_93_i_4];
	_42 = _41.data[_91_j_6];
	_81_retval_5.data[_81_k_7] = _42;
	_43 = 1;
	_44 = _81_k_7 + _43;
	_81_k_2 = _44;
	_93_i_5 = _93_i_4;
	_s_14 = _s_13;
	_81_board_14 = _81_board_13;
	_91_j_7 = _91_j_6;
	_81_retval_6 = _81_retval_5;
	_81_k_8 = _81_k_2;
	_numRows_14 = _numRows_13;
	goto L178;
L178:; // incoming:2
	_45 = 1;
	_46 = _93_i_5 + _45;
	_93_i_1 = _46;
	_s_11 = _s_14;
	_93_i_2 = _93_i_1;
	_81_board_11 = _81_board_14;
	_91_j_4 = _91_j_7;
	_81_retval_3 = _81_retval_6;
	_81_k_5 = _81_k_8;
	_numRows_11 = _numRows_14;
	goto L172;
L182:; // incoming:1
	_47 = 1;
	_48 = _91_j_8 + _47;
	_91_j_1 = _48;
	_91_j_2 = _91_j_1;
	_numRows_9 = _numRows_15;
	_s_9 = _s_15;
	_81_board_9 = _81_board_15;
	_81_retval_1 = _81_retval_7;
	_81_k_3 = _81_k_9;
	goto L170;
L184:; // incoming:1
	_83_i_0 = 0;
	_s_17 = _s_16;
	_83_i_2 = _83_i_0;
	_81_retval_9 = _81_retval_8;
	goto L185;
L185:; // incoming:2
	_51 = _s_17.length;
	_52 = _83_i_2 < _51;
	if (!_52) {
		_81_retval_11 = _81_retval_9;
		goto L191;
	} else {
		_83_i_3 = _83_i_2;
		_s_18 = _s_17;
		_81_retval_10 = _81_retval_9;
		goto L188;
	}
L188:; // incoming:1
	_53 = 1;
	_54 = _83_i_3 + _53;
	_83_i_1 = _54;
	_s_17 = _s_18;
	_83_i_2 = _83_i_1;
	_81_retval_9 = _81_retval_10;
	goto L185;
L191:; // incoming:1
	retval = _81_retval_11;
	goto end;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

void test_leetcode_test_reverse()
{
	int64_t (*_0) (int64_t _x);
	int64_t _2;
	int64_t _1;
	int64_t _100_ans_0;
	void (*_3) (bool _predicate, struct struct_1 _msg);
	int64_t _6;
	bool _5;
	struct struct_1 _7;
L199:; // incoming:1
	_0 = test_leetcode_reverse;
	_2 = 123;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n309   | ans := reverse(123)\n      |               ^\n");
	_1 = _0(_2);
	_100_ans_0 = _1;
	_3 = std_debug_assert;
	_6 = 321;
	_5 = _100_ans_0 == _6;
	_7 = (struct struct_1) {20, "no message specified"};
	stackTracePush(&stackTrace, "test/leetcode.orng: \n311   | std.debug.assert(ans == 321)\n      |                 ^\n");
	_3(_5, _7);
	goto end;
end:;
	stackTracePop(&stackTrace);
	return;
}

int64_t test_leetcode_reverse(int64_t _x)
{
	int64_t retval;
	int64_t (*_0) (struct struct_5 _l);
	int64_t _2;
	struct struct_6* (*_3) (struct struct_6* _list);
	struct struct_6* (*_5) (int64_t _i);
	struct struct_6* _6;
	struct struct_6* _4;
	struct struct_5 _7;
	int64_t _1;
	int64_t _x_0;
	_x_0 = _x;
L198:; // incoming:1
	_0 = test_leetcode_convertToInt;
	_2 = 2;
	_3 = test_leetcode_reverseList;
	_5 = test_leetcode_convertToList;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n306   | reverse::(x:Int)->Int = convertToInt(reverseList(convertToList(x)))\n      |                                                               ^\n");
	_6 = _5(_x_0);
	stackTracePush(&stackTrace, "test/leetcode.orng: \n306   | reverse::(x:Int)->Int = convertToInt(reverseList(convertToList(x)))\n      |                                                 ^\n");
	_4 = _3(_6);
	_7 = (struct struct_5) {_2, _4};
	stackTracePush(&stackTrace, "test/leetcode.orng: \n306   | reverse::(x:Int)->Int = convertToInt(reverseList(convertToList(x)))\n      |                                     ^\n");
	_1 = _0(_7);
	retval = _1;
	goto end;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

struct struct_6* test_leetcode_reverseList(struct struct_6* _list)
{
	struct struct_6* retval;
	struct struct_6 _1;
	struct struct_5 _2;
	struct struct_5 _97_next_0;
	int64_t _4;
	int64_t _5;
	struct struct_3 _6;
	int64_t _7;
	bool _3;
	struct struct_6* _list_0;
	struct struct_6* _list_1;
	struct struct_6* (*_8) (struct struct_6* _list);
	struct struct_6* _10;
	struct struct_6* _9;
	struct struct_6* _11;
	struct struct_6 _12;
	int64_t _13;
	struct struct_5 _14;
	struct struct_6 _16;
	int64_t _17;
	struct struct_5 _18;
	struct struct_5 _97_next_1;
	struct struct_6* _list_2;
	_list_0 = _list;
L193:; // incoming:1
	_1 = *_list_0;
	_2 = _1.next;
	_97_next_0 = _2;
	_4 = _97_next_0.tag;
	_5 = 0;
	_6 = (struct struct_3) {_5};
	_7 = _6.tag;
	_3 = _4 == _7;
	if (!_3) {
		_97_next_1 = _97_next_0;
		_list_2 = _list_0;
		goto L195;
	} else {
		_list_1 = _list_0;
		goto L194;
	}
L194:; // incoming:1
	retval = _list_1;
	goto end;
L195:; // incoming:1
	_8 = test_leetcode_reverseList;
	_10 = _97_next_1.something;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n299   | newList = reverseList(next?)\n      |                      ^\n");
	_9 = _8(_10);
	_11 = _97_next_1.something;
	_13 = 2;
	_14 = (struct struct_5) {_13, _list_2};
	(*_11).next = _14;
	_17 = 0;
	_18 = (struct struct_5) {_17};
	(*_list_2).next = _18;
	retval = _9;
	goto end;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

void test_leetcode_test_myAtoi()
{
	struct struct_1 _0;
	struct struct_1 _111_s_0;
	int64_t (*_1) (struct struct_1 _s);
	int64_t _2;
	int64_t _111_ans_0;
	void (*_3) (bool _predicate, struct struct_1 _msg);
	int64_t _6;
	bool _5;
	struct struct_1 _7;
L234:; // incoming:1
	_0 = (struct struct_1) {2, "42"};
	_111_s_0 = _0;
	_1 = test_leetcode_myAtoi;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n348   | ans := myAtoi(s)\n      |              ^\n");
	_2 = _1(_111_s_0);
	_111_ans_0 = _2;
	_3 = std_debug_assert;
	_6 = 42;
	_5 = _111_ans_0 == _6;
	_7 = (struct struct_1) {20, "no message specified"};
	stackTracePush(&stackTrace, "test/leetcode.orng: \n350   | std.debug.assert(ans == 42)\n      |                 ^\n");
	_3(_5, _7);
	goto end;
end:;
	stackTracePop(&stackTrace);
	return;
}

int64_t test_leetcode_myAtoi(struct struct_1 _s)
{
	int64_t retval;
	int64_t _101_x_0;
	int64_t _101_i_0;
	bool _101_sign_0;
	struct struct_1 _s_0;
	int8_t _3;
	int64_t _4;
	bool _5;
	struct struct_1 _s_1;
	int64_t _101_i_10;
	int64_t _101_x_4;
	bool _101_sign_6;
	int8_t _7;
	int8_t _8;
	bool _6;
	struct struct_1 _s_2;
	int64_t _101_i_11;
	int64_t _101_x_5;
	bool _101_sign_7;
	int64_t _101_i_12;
	struct struct_1 _s_3;
	int64_t _101_x_6;
	bool _101_sign_8;
	int64_t _9;
	int64_t _10;
	int64_t _101_i_6;
	int64_t _101_i_13;
	struct struct_1 _s_4;
	int64_t _101_x_7;
	bool _101_sign_9;
	int64_t _12;
	bool _11;
	struct struct_1 _s_5;
	int64_t _101_i_14;
	int64_t _101_x_8;
	bool _101_sign_10;
	int8_t _15;
	int8_t _16;
	bool _14;
	struct struct_1 _s_6;
	int64_t _101_i_15;
	int64_t _101_x_9;
	bool _101_sign_11;
	int64_t _18;
	int64_t _19;
	int64_t _101_i_8;
	bool _101_sign_4;
	int64_t _101_i_16;
	struct struct_1 _s_7;
	int64_t _101_x_10;
	int8_t _26;
	int64_t _27;
	bool _28;
	struct struct_1 _s_8;
	int64_t _101_i_17;
	int64_t _101_x_11;
	bool _101_sign_12;
	bool (*_29) (int8_t _c);
	int8_t _31;
	bool _30;
	struct struct_1 _s_9;
	int64_t _101_i_18;
	int64_t _101_x_12;
	bool _101_sign_13;
	int64_t _101_x_13;
	struct struct_1 _s_10;
	int64_t _101_i_19;
	bool _101_sign_14;
	int64_t _32;
	int64_t _33;
	int8_t _34;
	int64_t _35;
	int64_t _36;
	int8_t _37;
	int64_t _38;
	int64_t _39;
	int64_t _101_x_3;
	int64_t _40;
	int64_t _41;
	int64_t _101_i_3;
	int64_t _101_x_14;
	struct struct_1 _s_11;
	int64_t _101_i_20;
	bool _101_sign_15;
	int64_t _42;
	bool _101_sign_16;
	int64_t _101_x_15;
	int64_t _101_x_16;
	int64_t _44;
	int64_t _101_x_17;
	int64_t _101_x_18;
	struct struct_1 _s_12;
	int64_t _101_i_21;
	bool _101_sign_17;
	int8_t _21;
	int8_t _22;
	bool _20;
	struct struct_1 _s_13;
	int64_t _101_i_22;
	int64_t _101_x_19;
	bool _101_sign_18;
	int64_t _24;
	int64_t _25;
	int64_t _101_i_9;
	bool _101_sign_5;
	int64_t _101_i_23;
	struct struct_1 _s_14;
	int64_t _101_x_20;
	int64_t _101_i_24;
	struct struct_1 _s_15;
	int64_t _101_x_21;
	bool _101_sign_19;
	_s_0 = _s;
L200:; // incoming:1
	_101_x_0 = 0;
	_101_i_0 = 0;
	_101_sign_0 = 1;
	_s_1 = _s_0;
	_101_i_10 = _101_i_0;
	_101_x_4 = _101_x_0;
	_101_sign_6 = _101_sign_0;
	goto L201;
L201:; // incoming:2
	_4 = _s_1.length;
	_5 = _101_i_10 < _4;
	if (!_5) {
		_101_i_24 = _101_i_10;
		_s_15 = _s_1;
		_101_x_21 = _101_x_4;
		_101_sign_19 = _101_sign_6;
		goto L233;
	} else {
		_s_2 = _s_1;
		_101_i_11 = _101_i_10;
		_101_x_5 = _101_x_4;
		_101_sign_7 = _101_sign_6;
		goto L202;
	}
L202:; // incoming:1
	_7 = _s_2.data[_101_i_11];
	_8 = 32;
	_6 = _7 == _8;
	_3 = _6;
	_101_i_12 = _101_i_11;
	_s_3 = _s_2;
	_101_x_6 = _101_x_5;
	_101_sign_8 = _101_sign_7;
	goto L203;
L203:; // incoming:2
	if (!_3) {
		_s_5 = _s_3;
		_101_i_14 = _101_i_12;
		_101_x_8 = _101_x_6;
		_101_sign_10 = _101_sign_8;
		goto L207;
	} else {
		_101_i_13 = _101_i_12;
		_s_4 = _s_3;
		_101_x_7 = _101_x_6;
		_101_sign_9 = _101_sign_8;
		goto L204;
	}
L204:; // incoming:1
	_9 = 1;
	_10 = _101_i_13 + _9;
	_101_i_6 = _10;
	_s_1 = _s_4;
	_101_i_10 = _101_i_6;
	_101_x_4 = _101_x_7;
	_101_sign_6 = _101_sign_9;
	goto L201;
L207:; // incoming:1
	_12 = _s_5.length;
	_11 = _101_i_14 == _12;
	if (!_11) {
		_s_6 = _s_5;
		_101_i_15 = _101_i_14;
		_101_x_9 = _101_x_8;
		_101_sign_11 = _101_sign_10;
		goto L209;
	} else {
		goto L208;
	}
L208:; // incoming:1
	retval = 0;
	goto end;
L209:; // incoming:1
	_15 = _s_6.data[_101_i_15];
	_16 = 43;
	_14 = _15 == _16;
	if (!_14) {
		_s_13 = _s_6;
		_101_i_22 = _101_i_15;
		_101_x_19 = _101_x_9;
		_101_sign_18 = _101_sign_11;
		goto L228;
	} else {
		_101_i_16 = _101_i_15;
		_s_7 = _s_6;
		_101_x_10 = _101_x_9;
		goto L210;
	}
L210:; // incoming:1
	_18 = 1;
	_19 = _101_i_16 + _18;
	_101_i_8 = _19;
	_101_sign_4 = 1;
	_s_8 = _s_7;
	_101_i_17 = _101_i_8;
	_101_x_11 = _101_x_10;
	_101_sign_12 = _101_sign_4;
	goto L214;
L214:; // incoming:4
	_27 = _s_8.length;
	_28 = _101_i_17 < _27;
	if (!_28) {
		_101_x_18 = _101_x_11;
		_s_12 = _s_8;
		_101_i_21 = _101_i_17;
		_101_sign_17 = _101_sign_12;
		goto L227;
	} else {
		_s_9 = _s_8;
		_101_i_18 = _101_i_17;
		_101_x_12 = _101_x_11;
		_101_sign_13 = _101_sign_12;
		goto L215;
	}
L215:; // incoming:1
	_29 = isdigit;
	_31 = _s_9.data[_101_i_18];
	stackTracePush(&stackTrace, "test/leetcode.orng: \n338   | for ; i < s.length && std.string.isdigit(s[i]); i += 1 {\n      |                                                 ^\n");
	_30 = _29(_31);
	_26 = _30;
	_101_x_13 = _101_x_12;
	_s_10 = _s_9;
	_101_i_19 = _101_i_18;
	_101_sign_14 = _101_sign_13;
	goto L216;
L216:; // incoming:2
	if (!_26) {
		_101_sign_16 = _101_sign_14;
		_101_x_15 = _101_x_13;
		goto L220;
	} else {
		_101_x_14 = _101_x_13;
		_s_11 = _s_10;
		_101_i_20 = _101_i_19;
		_101_sign_15 = _101_sign_14;
		goto L217;
	}
L217:; // incoming:1
	_32 = 10;
	_33 = _101_x_14 * _32;
	_34 = _s_11.data[_101_i_20];
	_35 = (int64_t) _34;
	_36 = _33 + _35;
	_37 = 48;
	_38 = (int64_t) _37;
	_39 = _36 - _38;
	_101_x_3 = _39;
	_40 = 1;
	_41 = _101_i_20 + _40;
	_101_i_3 = _41;
	_s_8 = _s_11;
	_101_i_17 = _101_i_3;
	_101_x_11 = _101_x_3;
	_101_sign_12 = _101_sign_15;
	goto L214;
L220:; // incoming:1
	if (!_101_sign_16) {
		_101_x_17 = _101_x_15;
		goto L225;
	} else {
		_101_x_16 = _101_x_15;
		goto L222;
	}
L222:; // incoming:1
	_42 = _101_x_16;
	goto L224;
L224:; // incoming:2
	retval = _42;
	goto end;
L225:; // incoming:1
	_44 = -_101_x_17;
	_42 = _44;
	goto L224;
L227:; // incoming:1
	_26 = 0;
	_101_x_13 = _101_x_18;
	_s_10 = _s_12;
	_101_i_19 = _101_i_21;
	_101_sign_14 = _101_sign_17;
	goto L216;
L228:; // incoming:1
	_21 = _s_13.data[_101_i_22];
	_22 = 45;
	_20 = _21 == _22;
	if (!_20) {
		_s_8 = _s_13;
		_101_i_17 = _101_i_22;
		_101_x_11 = _101_x_19;
		_101_sign_12 = _101_sign_18;
		goto L214;
	} else {
		_101_i_23 = _101_i_22;
		_s_14 = _s_13;
		_101_x_20 = _101_x_19;
		goto L229;
	}
L229:; // incoming:1
	_24 = 1;
	_25 = _101_i_23 + _24;
	_101_i_9 = _25;
	_101_sign_5 = 0;
	_s_8 = _s_14;
	_101_i_17 = _101_i_9;
	_101_x_11 = _101_x_20;
	_101_sign_12 = _101_sign_5;
	goto L214;
L233:; // incoming:1
	_3 = 0;
	_101_i_12 = _101_i_24;
	_s_3 = _s_15;
	_101_x_6 = _101_x_21;
	_101_sign_8 = _101_sign_19;
	goto L203;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

void test_leetcode_test_isPalindrome()
{
	int64_t _116_x_0;
	bool (*_1) (int64_t _x);
	bool _2;
	bool _116_ans_0;
	void (*_3) (bool _predicate, struct struct_1 _msg);
	struct struct_1 _5;
L247:; // incoming:1
	_116_x_0 = 121;
	_1 = test_leetcode_isPalindrome;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n374   | ans := isPalindrome(x)\n      |                    ^\n");
	_2 = _1(_116_x_0);
	_116_ans_0 = _2;
	_3 = std_debug_assert;
	_5 = (struct struct_1) {20, "no message specified"};
	stackTracePush(&stackTrace, "test/leetcode.orng: \n376   | std.debug.assert(ans)\n      |                 ^\n");
	_3(_116_ans_0, _5);
	goto end;
end:;
	stackTracePop(&stackTrace);
	return;
}

bool test_leetcode_isPalindrome(int64_t _x)
{
	bool retval;
	int64_t _0;
	struct struct_6* (*_1) (int64_t _i);
	struct struct_6* _2;
	struct struct_5 _3;
	struct struct_5 _112_list_0;
	int64_t _4;
	struct struct_6* (*_5) (struct struct_6* _list);
	struct struct_6* (*_7) (int64_t _i);
	struct struct_6* _8;
	struct struct_6* _6;
	struct struct_5 _9;
	struct struct_5 _112_reversedList_0;
	int64_t _x_0;
	int8_t _10;
	int64_t _12;
	int64_t _13;
	struct struct_3 _14;
	int64_t _15;
	bool _11;
	struct struct_5 _112_list_4;
	struct struct_5 _112_reversedList_4;
	int64_t _17;
	int64_t _18;
	struct struct_3 _19;
	int64_t _20;
	bool _16;
	struct struct_5 _112_reversedList_5;
	struct struct_5 _112_list_5;
	struct struct_5 _112_list_6;
	struct struct_5 _112_reversedList_6;
	struct struct_6* _22;
	struct struct_6 _23;
	int64_t _24;
	struct struct_6* _25;
	struct struct_6 _26;
	int64_t _27;
	bool _21;
	struct struct_5 _112_list_7;
	struct struct_5 _112_reversedList_7;
	struct struct_6* _29;
	struct struct_6 _30;
	struct struct_5 _31;
	struct struct_6* _32;
	struct struct_6 _33;
	struct struct_5 _34;
	struct struct_5 _112_list_3;
	struct struct_5 _112_reversedList_3;
	struct struct_5 _112_list_8;
	struct struct_5 _112_reversedList_8;
	struct struct_5 _112_list_9;
	struct struct_5 _112_reversedList_9;
	_x_0 = _x;
L235:; // incoming:1
	_0 = 2;
	_1 = test_leetcode_convertToList;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n357   | list: ?&ListNode = convertToList(x)\n      |                                 ^\n");
	_2 = _1(_x_0);
	_3 = (struct struct_5) {_0, _2};
	_112_list_0 = _3;
	_4 = 2;
	_5 = test_leetcode_reverseList;
	_7 = test_leetcode_convertToList;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n358   | reversedList: ?&ListNode = reverseList(convertToList(x))\n      |                                                     ^\n");
	_8 = _7(_x_0);
	stackTracePush(&stackTrace, "test/leetcode.orng: \n358   | reversedList: ?&ListNode = reverseList(convertToList(x))\n      |                                       ^\n");
	_6 = _5(_8);
	_9 = (struct struct_5) {_4, _6};
	_112_reversedList_0 = _9;
	_112_list_4 = _112_list_0;
	_112_reversedList_4 = _112_reversedList_0;
	goto L236;
L236:; // incoming:2
	_12 = _112_list_4.tag;
	_13 = 0;
	_14 = (struct struct_3) {_13};
	_15 = _14.tag;
	_11 = _12 != _15;
	if (!_11) {
		_112_list_9 = _112_list_4;
		_112_reversedList_9 = _112_reversedList_4;
		goto L246;
	} else {
		_112_reversedList_5 = _112_reversedList_4;
		_112_list_5 = _112_list_4;
		goto L237;
	}
L237:; // incoming:1
	_17 = _112_reversedList_5.tag;
	_18 = 0;
	_19 = (struct struct_3) {_18};
	_20 = _19.tag;
	_16 = _17 != _20;
	_10 = _16;
	_112_list_6 = _112_list_5;
	_112_reversedList_6 = _112_reversedList_5;
	goto L238;
L238:; // incoming:2
	if (!_10) {
		goto L245;
	} else {
		_112_list_7 = _112_list_6;
		_112_reversedList_7 = _112_reversedList_6;
		goto L239;
	}
L239:; // incoming:1
	_22 = _112_list_7.something;
	_23 = *_22;
	_24 = _23.val;
	_25 = _112_reversedList_7.something;
	_26 = *_25;
	_27 = _26.val;
	_21 = _24 != _27;
	if (!_21) {
		_112_list_8 = _112_list_7;
		_112_reversedList_8 = _112_reversedList_7;
		goto L242;
	} else {
		goto L240;
	}
L240:; // incoming:1
	retval = 0;
	goto end;
L242:; // incoming:1
	_29 = _112_list_8.something;
	_30 = *_29;
	_31 = _30.next;
	_32 = _112_reversedList_8.something;
	_33 = *_32;
	_34 = _33.next;
	_112_list_3 = _31;
	_112_reversedList_3 = _34;
	_112_list_4 = _112_list_3;
	_112_reversedList_4 = _112_reversedList_3;
	goto L236;
L245:; // incoming:1
	retval = 1;
	goto end;
L246:; // incoming:1
	_10 = 0;
	_112_list_6 = _112_list_9;
	_112_reversedList_6 = _112_reversedList_9;
	goto L238;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

void test_leetcode_test_isMatch()
{
	struct struct_1 _0;
	struct struct_1 _127_s_0;
	struct struct_1 _1;
	struct struct_1 _127_p_0;
	bool (*_2) (struct struct_1 _s, struct struct_1 _p);
	bool _3;
	bool _127_ans_0;
	void (*_4) (bool _predicate, struct struct_1 _msg);
	struct struct_1 _6;
L276:; // incoming:1
	_0 = (struct struct_1) {2, "aa"};
	_127_s_0 = _0;
	_1 = (struct struct_1) {2, "a*"};
	_127_p_0 = _1;
	_2 = test_leetcode_isMatch;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n412   | ans := isMatch(s, p)\n      |               ^\n");
	_3 = _2(_127_s_0, _127_p_0);
	_127_ans_0 = _3;
	_4 = std_debug_assert;
	_6 = (struct struct_1) {20, "no message specified"};
	stackTracePush(&stackTrace, "test/leetcode.orng: \n414   | std.debug.assert(ans)\n      |                 ^\n");
	_4(_127_ans_0, _6);
	goto end;
end:;
	stackTracePop(&stackTrace);
	return;
}

bool test_leetcode_isMatch(struct struct_1 _s, struct struct_1 _p)
{
	bool retval;
	int64_t _117_i_0;
	int64_t _117_j_0;
	struct struct_1 _s_0;
	struct struct_1 _p_0;
	int64_t _2;
	bool _3;
	struct struct_1 _s_1;
	int64_t _117_i_2;
	int64_t _117_j_8;
	struct struct_1 _p_1;
	bool _4;
	int64_t _6;
	int64_t _7;
	int64_t _8;
	bool _5;
	int64_t _117_j_9;
	struct struct_1 _p_2;
	struct struct_1 _s_2;
	int64_t _117_i_3;
	struct struct_1 _p_3;
	int64_t _117_j_10;
	struct struct_1 _s_3;
	int64_t _117_i_4;
	bool _119_repeat_0;
	int8_t _17;
	int8_t _19;
	int8_t _20;
	bool _18;
	struct struct_1 _p_4;
	int64_t _117_j_11;
	struct struct_1 _s_4;
	int64_t _117_i_5;
	int8_t _22;
	int8_t _23;
	bool _21;
	struct struct_1 _s_5;
	int64_t _117_i_6;
	struct struct_1 _p_5;
	int64_t _117_j_12;
	bool _119_repeat_1;
	bool _119_repeat_2;
	int64_t _117_j_13;
	struct struct_1 _s_6;
	int64_t _117_i_7;
	struct struct_1 _p_6;
	bool _119_repeat_3;
	int64_t _117_j_14;
	struct struct_1 _s_7;
	int64_t _117_i_8;
	struct struct_1 _p_7;
	int64_t _24;
	int64_t _25;
	int64_t _117_j_7;
	int64_t _117_j_15;
	struct struct_1 _s_8;
	int64_t _117_i_9;
	struct struct_1 _p_8;
	int64_t _27;
	int64_t _28;
	int64_t _117_i_1;
	bool _29;
	int64_t _117_i_10;
	bool _119_repeat_4;
	int64_t _117_j_16;
	struct struct_1 _s_9;
	struct struct_1 _p_9;
	int64_t _30;
	int64_t _31;
	int64_t _117_j_6;
	int64_t _117_j_17;
	struct struct_1 _s_10;
	int64_t _117_i_11;
	struct struct_1 _p_10;
	bool _119_repeat_5;
	int64_t _117_j_18;
	struct struct_1 _s_11;
	int64_t _117_i_12;
	struct struct_1 _p_11;
	int64_t _12;
	int64_t _13;
	int8_t _14;
	int8_t _15;
	bool _11;
	int64_t _117_j_19;
	struct struct_1 _p_12;
	struct struct_1 _s_12;
	int64_t _117_i_13;
	_s_0 = _s;
	_p_0 = _p;
L248:; // incoming:1
	_117_i_0 = 0;
	_117_j_0 = 0;
	_s_1 = _s_0;
	_117_i_2 = _117_i_0;
	_117_j_8 = _117_j_0;
	_p_1 = _p_0;
	goto L249;
L249:; // incoming:4
	_2 = _s_1.length;
	_3 = _117_i_2 < _2;
	if (!_3) {
		goto L275;
	} else {
		_117_j_9 = _117_j_8;
		_p_2 = _p_1;
		_s_2 = _s_1;
		_117_i_3 = _117_i_2;
		goto L250;
	}
L250:; // incoming:1
	_6 = 1;
	_7 = _117_j_9 + _6;
	_8 = _p_2.length;
	_5 = _7 == _8;
	if (!_5) {
		_117_j_19 = _117_j_9;
		_p_12 = _p_2;
		_s_12 = _s_2;
		_117_i_13 = _117_i_3;
		goto L272;
	} else {
		_p_3 = _p_2;
		_117_j_10 = _117_j_9;
		_s_3 = _s_2;
		_117_i_4 = _117_i_3;
		goto L252;
	}
L252:; // incoming:1
	_4 = 0;
	_p_4 = _p_3;
	_117_j_11 = _117_j_10;
	_s_4 = _s_3;
	_117_i_5 = _117_i_4;
	goto L253;
L253:; // incoming:2
	_119_repeat_0 = _4;
	_19 = _p_4.data[_117_j_11];
	_20 = 46;
	_18 = _19 != _20;
	if (!_18) {
		_119_repeat_5 = _119_repeat_0;
		_117_j_18 = _117_j_11;
		_s_11 = _s_4;
		_117_i_12 = _117_i_5;
		_p_11 = _p_4;
		goto L271;
	} else {
		_s_5 = _s_4;
		_117_i_6 = _117_i_5;
		_p_5 = _p_4;
		_117_j_12 = _117_j_11;
		_119_repeat_1 = _119_repeat_0;
		goto L254;
	}
L254:; // incoming:1
	_22 = _s_5.data[_117_i_6];
	_23 = _p_5.data[_117_j_12];
	_21 = _22 != _23;
	_17 = _21;
	_119_repeat_2 = _119_repeat_1;
	_117_j_13 = _117_j_12;
	_s_6 = _s_5;
	_117_i_7 = _117_i_6;
	_p_6 = _p_5;
	goto L255;
L255:; // incoming:2
	if (!_17) {
		_117_i_10 = _117_i_7;
		_119_repeat_4 = _119_repeat_2;
		_117_j_16 = _117_j_13;
		_s_9 = _s_6;
		_p_9 = _p_6;
		goto L265;
	} else {
		_119_repeat_3 = _119_repeat_2;
		_117_j_14 = _117_j_13;
		_s_7 = _s_6;
		_117_i_8 = _117_i_7;
		_p_7 = _p_6;
		goto L256;
	}
L256:; // incoming:1
	if (!_119_repeat_3) {
		goto L264;
	} else {
		_117_j_15 = _117_j_14;
		_s_8 = _s_7;
		_117_i_9 = _117_i_8;
		_p_8 = _p_7;
		goto L257;
	}
L257:; // incoming:1
	_24 = 1;
	_25 = _117_j_15 + _24;
	_117_j_7 = _25;
	_s_1 = _s_8;
	_117_i_2 = _117_i_9;
	_117_j_8 = _117_j_7;
	_p_1 = _p_8;
	goto L249;
L264:; // incoming:1
	retval = 0;
	goto end;
L265:; // incoming:1
	_27 = 1;
	_28 = _117_i_10 + _27;
	_117_i_1 = _28;
	_29 = !_119_repeat_4;
	if (!_29) {
		_s_1 = _s_9;
		_117_i_2 = _117_i_1;
		_117_j_8 = _117_j_16;
		_p_1 = _p_9;
		goto L249;
	} else {
		_117_j_17 = _117_j_16;
		_s_10 = _s_9;
		_117_i_11 = _117_i_1;
		_p_10 = _p_9;
		goto L266;
	}
L266:; // incoming:1
	_30 = 1;
	_31 = _117_j_17 + _30;
	_117_j_6 = _31;
	_s_1 = _s_10;
	_117_i_2 = _117_i_11;
	_117_j_8 = _117_j_6;
	_p_1 = _p_10;
	goto L249;
L271:; // incoming:1
	_17 = 0;
	_119_repeat_2 = _119_repeat_5;
	_117_j_13 = _117_j_18;
	_s_6 = _s_11;
	_117_i_7 = _117_i_12;
	_p_6 = _p_11;
	goto L255;
L272:; // incoming:1
	_12 = 1;
	_13 = _117_j_19 + _12;
	_14 = _p_12.data[_13];
	_15 = 42;
	_11 = _14 == _15;
	_4 = _11;
	_p_4 = _p_12;
	_117_j_11 = _117_j_19;
	_s_4 = _s_12;
	_117_i_5 = _117_i_13;
	goto L253;
L275:; // incoming:1
	retval = 1;
	goto end;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

void test_leetcode_test_maxArea()
{
	int64_t _1;
	int64_t _2;
	int64_t _3;
	int64_t _4;
	int64_t _5;
	int64_t _6;
	int64_t _7;
	int64_t _8;
	int64_t _9;
	struct struct_4 _133_height_0;
	int64_t (*_10) (struct struct_4 _height, int64_t _max);
	int64_t _12;
	int64_t _11;
	int64_t _133_ans_0;
	void (*_13) (bool _predicate, struct struct_1 _msg);
	int64_t _16;
	bool _15;
	struct struct_1 _17;
L300:; // incoming:1
	_1 = 1;
	_2 = 8;
	_3 = 6;
	_4 = 2;
	_5 = 5;
	_6 = 4;
	_7 = 8;
	_8 = 3;
	_9 = 7;
	_133_height_0 = (struct struct_4) {9, (int64_t[]){_1, _2, _3, _4, _5, _6, _7, _8, _9}};
	_10 = test_leetcode_maxArea;
	_12 = 0;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n436   | ans := maxArea(height)\n      |               ^\n");
	_11 = _10(_133_height_0, _12);
	_133_ans_0 = _11;
	_13 = std_debug_assert;
	_16 = 49;
	_15 = _133_ans_0 == _16;
	_17 = (struct struct_1) {20, "no message specified"};
	stackTracePush(&stackTrace, "test/leetcode.orng: \n438   | std.debug.assert(ans == 49)\n      |                 ^\n");
	_13(_15, _17);
	goto end;
end:;
	stackTracePop(&stackTrace);
	return;
}

int64_t test_leetcode_maxArea(struct struct_4 _height, int64_t _max)
{
	int64_t retval;
	int64_t _129_i_0;
	struct struct_4 _height_0;
	int64_t _max_3;
	int64_t _1;
	int64_t _2;
	int64_t _3;
	bool _4;
	struct struct_4 _height_1;
	int64_t _129_i_2;
	int64_t _max_4;
	int64_t _5;
	int64_t _6;
	int64_t _131_j_0;
	int64_t _129_i_3;
	struct struct_4 _height_2;
	int64_t _max_5;
	int64_t _7;
	bool _8;
	struct struct_4 _height_3;
	int64_t _131_j_2;
	int64_t _129_i_4;
	int64_t _max_6;
	double (*_9) (double _x, double _y);
	int64_t (*_11) (int64_t _x);
	int64_t _13;
	int64_t _12;
	double (*_14) (double _x, double _y);
	int64_t _16;
	int64_t _17;
	double _15;
	double _18;
	double _10;
	int64_t _19;
	int64_t _max_2;
	int64_t _20;
	int64_t _21;
	int64_t _131_j_1;
	int64_t _129_i_5;
	int64_t _131_j_3;
	struct struct_4 _height_4;
	int64_t _max_7;
	int64_t _22;
	int64_t _23;
	int64_t _129_i_1;
	int64_t _129_i_6;
	struct struct_4 _height_5;
	int64_t _max_8;
	int64_t _max_9;
	_height_0 = _height;
	_max_3 = _max;
L289:; // incoming:1
	_129_i_0 = 0;
	_height_1 = _height_0;
	_129_i_2 = _129_i_0;
	_max_4 = _max_3;
	goto L290;
L290:; // incoming:2
	_1 = _height_1.length;
	_2 = 1;
	_3 = _1 - _2;
	_4 = _129_i_2 < _3;
	if (!_4) {
		_max_9 = _max_4;
		goto L299;
	} else {
		_129_i_3 = _129_i_2;
		_height_2 = _height_1;
		_max_5 = _max_4;
		goto L291;
	}
L291:; // incoming:1
	_5 = 1;
	_6 = _129_i_3 + _5;
	_131_j_0 = _6;
	_height_3 = _height_2;
	_131_j_2 = _131_j_0;
	_129_i_4 = _129_i_3;
	_max_6 = _max_5;
	goto L292;
L292:; // incoming:2
	_7 = _height_3.length;
	_8 = _131_j_2 < _7;
	if (!_8) {
		_129_i_6 = _129_i_4;
		_height_5 = _height_3;
		_max_8 = _max_6;
		goto L298;
	} else {
		_129_i_5 = _129_i_4;
		_131_j_3 = _131_j_2;
		_height_4 = _height_3;
		_max_7 = _max_6;
		goto L293;
	}
L293:; // incoming:1
	_9 = std_math_max;
	_11 = std_math_abs;
	_13 = _129_i_5 - _131_j_3;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n427   | max = std.math.max(max, std.math.abs(i - j) * std.math.min(height[i], height[j])):Int\n      |                                     ^\n");
	_12 = _11(_13);
	_14 = std_math_min;
	_16 = _height_4.data[_129_i_5];
	_17 = _height_4.data[_131_j_3];
	stackTracePush(&stackTrace, "test/leetcode.orng: \n427   | max = std.math.max(max, std.math.abs(i - j) * std.math.min(height[i], height[j])):Int\n      |                                                           ^\n");
	_15 = _14(_16, _17);
	_18 = _12 * _15;
	stackTracePush(&stackTrace, "test/leetcode.orng: \n427   | max = std.math.max(max, std.math.abs(i - j) * std.math.min(height[i], height[j])):Int\n      |                   ^\n");
	_10 = _9(_max_7, _18);
	_19 = (int64_t) _10;
	_max_2 = _19;
	_20 = 1;
	_21 = _131_j_3 + _20;
	_131_j_1 = _21;
	_height_3 = _height_4;
	_131_j_2 = _131_j_1;
	_129_i_4 = _129_i_5;
	_max_6 = _max_2;
	goto L292;
L298:; // incoming:1
	_22 = 1;
	_23 = _129_i_6 + _22;
	_129_i_1 = _23;
	_height_1 = _height_5;
	_129_i_2 = _129_i_1;
	_max_4 = _max_8;
	goto L290;
L299:; // incoming:1
	retval = _max_9;
	goto end;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

int64_t std_math_abs(int64_t _x)
{
	int64_t retval;
	int64_t _0;
	int64_t _1;
	bool _2;
	int64_t _x_0;
	int64_t _x_1;
	int64_t _4;
	int64_t _x_2;
	_x_0 = _x;
L277:; // incoming:1
	_1 = 0;
	_2 = _x_0 > _1;
	if (!_2) {
		_x_2 = _x_0;
		goto L281;
	} else {
		_x_1 = _x_0;
		goto L279;
	}
L279:; // incoming:1
	_0 = _x_1;
	goto L280;
L280:; // incoming:2
	retval = _0;
	goto end;
L281:; // incoming:1
	_4 = -_x_2;
	_0 = _4;
	goto L280;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

double std_math_min(double _x, double _y)
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
L283:; // incoming:1
	_1 = _x_0 < _y_0;
	if (!_1) {
		_y_1 = _y_0;
		goto L288;
	} else {
		_x_1 = _x_0;
		goto L285;
	}
L285:; // incoming:1
	_0 = _x_1;
	goto L286;
L286:; // incoming:2
	retval = _0;
	goto end;
L288:; // incoming:1
	_0 = _y_1;
	goto L286;
end:;
	stackTracePop(&stackTrace);
	return retval;
}

void pause() {system("pause");}

int main(int argc, char** argv)
{
	atexit(pause);
	stackTraceInit(&stackTrace);
	stackTraceInit(&errorTrace);
	struct struct_2 args = {argc, calloc(sizeof(struct struct_1) * argc, 1)};
	for (int  i = 0; i < argc; i++) {
		int length = strlen(argv[i]);
		args.data[i] = (struct struct_1){length, calloc(sizeof(char) * length, 1)};
		memcpy(args.data[i].data, argv[i], length);
	}
	struct struct_3 retval = test_testModule_main(args);
	for (int  i = 0; i < argc; i++) {
		free(args.data[i].data);
	}
	free(args.data);
	if (errorTrace.length > 0) {
		fprintf(stderr, "error: %s\n", tagGetFieldName(retval.tag));
	}
	stackTracePrint(&errorTrace);
	return retval.tag != 12;
}
#endif
