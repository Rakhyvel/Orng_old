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
	int64_t tag;
	union {
		struct struct_7* something;
	};
};

struct struct_7 {
	int64_t val;
	struct struct_6 next;
};

struct struct_8 {
	int64_t length;
	bool* data;
};

struct struct_9 {
	int64_t length;
	int64_t* data;
};

/* Verbatim code */
int std_system_println(struct struct_1 _format, ...) {va_list _25_args;va_start(_25_args, _format.data);int retval = vprintf(_format.data, _25_args);va_end(_25_args);char newLine[2] = {'\n', '\0'};printf(newLine);return retval;}

int64_t test_testModule_main(struct struct_2 _args);
void test_leetcode_test_lengthOfLongestSubstring();
int64_t test_leetcode_lengthOfLongestSubstring(struct struct_1 _str);
bool test_leetcode_areDistinct(struct struct_1 _str, int64_t _i, int64_t _j);
double std_math_max(double _x, double _y);

#ifndef ORANGE_PROGRAM_1679
#define ORANGE_PROGRAM_1679

int64_t test_testModule_main(struct struct_2 _args)
{
	int64_t retval;
	register void (*_0) ();
	register struct struct_2 _args_0;
	_args_0 = _args;
L37:; // incoming:1
	_0 = test_leetcode_test_lengthOfLongestSubstring;
	_0();
	retval = 0;
	goto end;
end:;
	return retval;
}

void test_leetcode_test_lengthOfLongestSubstring()
{
	register struct struct_1 _0;
	register struct struct_1 _63_s_0;
	register int64_t (*_1) (struct struct_1 _str);
	register int64_t _2;
	register int64_t _63_ans_0;
	register int64_t _4;
	register bool _5;
	register int64_t (*_6) (struct struct_1 _format, ...);
	register struct struct_1 _8;
	register int64_t _7;
	register int64_t (*_10) (struct struct_1 _format, ...);
	register struct struct_1 _12;
	register int64_t _11;
	register int64_t _63_ans_1;
L30:; // incoming:1
	_0 = (struct struct_1) {8, "abcabcbb"};
	_63_s_0 = _0;
	_1 = test_leetcode_lengthOfLongestSubstring;
	_2 = _1(_63_s_0);
	_63_ans_0 = _2;
	_4 = 3;
	_5 = _63_ans_0 == _4;
	if (!_5) {
		_63_ans_1 = _63_ans_0;
		goto L35;
	} else {
		goto L31;
	}
L31:; // incoming:1
	_6 = std_system_println;
	_8 = (struct struct_1) {33, "lengthOfLongestSubstring: Passed!"};
	_7 = _6(_8);
	goto L34;
L34:; // incoming:2
	goto end;
L35:; // incoming:1
	_10 = std_system_println;
	_12 = (struct struct_1) {35, "lengthOfLongestSubstring: Failed %d"};
	_11 = _10(_12, _63_ans_1);
	goto L34;
end:;
	return;
}

int64_t test_leetcode_lengthOfLongestSubstring(struct struct_1 _str)
{
	int64_t retval;
	register int64_t _0;
	register int64_t _53_n_0;
	register int64_t _53_res_0;
	register int64_t _58_i_0;
	register struct struct_1 _str_0;
	register bool _3;
	register int64_t _58_i_2;
	register int64_t _53_n_1;
	register struct struct_1 _str_1;
	register int64_t _53_res_3;
	register int64_t _60_j_0;
	register int64_t _58_i_3;
	register int64_t _53_n_2;
	register struct struct_1 _str_2;
	register int64_t _53_res_4;
	register bool _4;
	register int64_t _60_j_2;
	register int64_t _53_n_3;
	register struct struct_1 _str_3;
	register int64_t _58_i_4;
	register int64_t _53_res_5;
	register bool (*_5) (struct struct_1 _str, int64_t _i, int64_t _j);
	register bool _6;
	register struct struct_1 _str_4;
	register int64_t _58_i_5;
	register int64_t _60_j_3;
	register int64_t _53_res_6;
	register int64_t _53_n_4;
	register double (*_7) (double _x, double _y);
	register int64_t _9;
	register int64_t _10;
	register int64_t _11;
	register double _8;
	register int64_t _12;
	register int64_t _53_res_2;
	register int64_t _60_j_4;
	register int64_t _58_i_6;
	register int64_t _53_res_7;
	register int64_t _53_n_5;
	register struct struct_1 _str_5;
	register int64_t _13;
	register int64_t _14;
	register int64_t _60_j_1;
	register int64_t _60_j_5;
	register int64_t _53_n_6;
	register struct struct_1 _str_6;
	register int64_t _58_i_7;
	register int64_t _53_res_8;
	register int64_t _15;
	register int64_t _16;
	register int64_t _58_i_1;
	register int64_t _58_i_8;
	register int64_t _53_n_7;
	register struct struct_1 _str_7;
	register int64_t _53_res_9;
	register int64_t _53_res_10;
	_str_0 = _str;
L15:; // incoming:1
	_0 = _str_0.length;
	_53_n_0 = _0;
	_53_res_0 = 0;
	_58_i_0 = 0;
	_58_i_2 = _58_i_0;
	_53_n_1 = _53_n_0;
	_str_1 = _str_0;
	_53_res_3 = _53_res_0;
	goto L16;
L16:; // incoming:2
	_3 = _58_i_2 < _53_n_1;
	if (!_3) {
		_53_res_10 = _53_res_3;
		goto L29;
	} else {
		_58_i_3 = _58_i_2;
		_53_n_2 = _53_n_1;
		_str_2 = _str_1;
		_53_res_4 = _53_res_3;
		goto L17;
	}
L17:; // incoming:1
	_60_j_0 = _58_i_3;
	_60_j_2 = _60_j_0;
	_53_n_3 = _53_n_2;
	_str_3 = _str_2;
	_58_i_4 = _58_i_3;
	_53_res_5 = _53_res_4;
	goto L18;
L18:; // incoming:2
	_4 = _60_j_2 < _53_n_3;
	if (!_4) {
		_58_i_8 = _58_i_4;
		_53_n_7 = _53_n_3;
		_str_7 = _str_3;
		_53_res_9 = _53_res_5;
		goto L28;
	} else {
		_str_4 = _str_3;
		_58_i_5 = _58_i_4;
		_60_j_3 = _60_j_2;
		_53_res_6 = _53_res_5;
		_53_n_4 = _53_n_3;
		goto L19;
	}
L19:; // incoming:1
	_5 = test_leetcode_areDistinct;
	_6 = _5(_str_4, _58_i_5, _60_j_3);
	if (!_6) {
		_60_j_5 = _60_j_3;
		_53_n_6 = _53_n_4;
		_str_6 = _str_4;
		_58_i_7 = _58_i_5;
		_53_res_8 = _53_res_6;
		goto L24;
	} else {
		_60_j_4 = _60_j_3;
		_58_i_6 = _58_i_5;
		_53_res_7 = _53_res_6;
		_53_n_5 = _53_n_4;
		_str_5 = _str_4;
		goto L20;
	}
L20:; // incoming:1
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
	goto L24;
L24:; // incoming:2
	_13 = 1;
	_14 = _60_j_5 + _13;
	_60_j_1 = _14;
	_60_j_2 = _60_j_1;
	_53_n_3 = _53_n_6;
	_str_3 = _str_6;
	_58_i_4 = _58_i_7;
	_53_res_5 = _53_res_8;
	goto L18;
L28:; // incoming:1
	_15 = 1;
	_16 = _58_i_8 + _15;
	_58_i_1 = _16;
	_58_i_2 = _58_i_1;
	_53_n_1 = _53_n_7;
	_str_1 = _str_7;
	_53_res_3 = _53_res_9;
	goto L16;
L29:; // incoming:1
	retval = _53_res_10;
	goto end;
end:;
	return retval;
}

bool test_leetcode_areDistinct(struct struct_1 _str, int64_t _i, int64_t _j)
{
	bool retval;
	register bool _1;
	register struct struct_8 _54_visited_0;
	register int64_t _55_k_0;
	register int64_t _i_0;
	register struct struct_1 _str_0;
	register int64_t _j_0;
	register bool _2;
	register int64_t _55_k_2;
	register int64_t _j_1;
	register struct struct_1 _str_1;
	register struct struct_8 _54_visited_1;
	register int8_t _3;
	register int64_t _4;
	register int64_t _56_charCode_0;
	register bool _5;
	register struct struct_1 _str_2;
	register int64_t _55_k_3;
	register struct struct_8 _54_visited_2;
	register int64_t _j_2;
	register bool _7;
	register int64_t _8;
	register int64_t _9;
	register int64_t _55_k_1;
	register struct struct_8 _54_visited_3;
	register int64_t _56_charCode_1;
	register int64_t _55_k_4;
	register int64_t _j_3;
	register struct struct_1 _str_3;
	_str_0 = _str;
	_i_0 = _i;
	_j_0 = _j;
L0:; // incoming:1
	_1 = 0;
	_54_visited_0 = (struct struct_8) {256, (bool[]){_1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1, _1}};
	_55_k_0 = _i_0;
	_55_k_2 = _55_k_0;
	_j_1 = _j_0;
	_str_1 = _str_0;
	_54_visited_1 = _54_visited_0;
	goto L1;
L1:; // incoming:2
	_2 = _55_k_2 <= _j_1;
	if (!_2) {
		goto L8;
	} else {
		_str_2 = _str_1;
		_55_k_3 = _55_k_2;
		_54_visited_2 = _54_visited_1;
		_j_2 = _j_1;
		goto L2;
	}
L2:; // incoming:1
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
		goto L5;
	} else {
		goto L3;
	}
L3:; // incoming:1
	retval = 0;
	goto end;
L5:; // incoming:1
	_7 = 1;
	_54_visited_3.data[_56_charCode_1] = _7;
	_8 = 1;
	_9 = _55_k_4 + _8;
	_55_k_1 = _9;
	_55_k_2 = _55_k_1;
	_j_1 = _j_3;
	_str_1 = _str_3;
	_54_visited_1 = _54_visited_3;
	goto L1;
L8:; // incoming:1
	retval = 1;
	goto end;
end:;
	return retval;
}

double std_math_max(double _x, double _y)
{
	double retval;
	register bool _1;
	register double _x_0;
	register double _y_0;
	_x_0 = _x;
	_y_0 = _y;
L9:; // incoming:1
	_1 = _x_0 > _y_0;
	if (!_1) {
		goto L13;
	} else {
		goto L12;
	}
L12:; // incoming:2
	retval = _x_0;
	goto end;
L13:; // incoming:2
	retval = _y_0;
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
