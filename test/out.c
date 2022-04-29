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

struct struct_2 {
	signed int length;
	struct struct_1* data[];
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

/* Enums */

/* Forward global declarations */

/* Forward function and procedure declarations */
signed int test_testModule_main(struct struct_2* _args);

#ifndef ORANGE_PROGRAM_28834
#define ORANGE_PROGRAM_28834

/* String definitions */
struct struct_1 string_23 = {2, {'%', 'd', '\0'}};
struct struct_1 string_24 = {2, {'%', 'd', '\0'}};
struct struct_1 string_25 = {2, {'%', 'd', '\0'}};
struct struct_1 string_26 = {2, {'%', 'd', '\0'}};
struct struct_1 string_27 = {2, {'%', 'd', '\0'}};
struct struct_1 string_28 = {2, {'%', 'd', '\0'}};
struct struct_1 string_29 = {2, {'%', 'd', '\0'}};
struct struct_1 string_30 = {2, {'%', 'd', '\0'}};
struct struct_1 string_31 = {2, {'%', 'd', '\0'}};
struct struct_1 string_32 = {2, {'%', 'd', '\0'}};
struct struct_1 string_33 = {2, {'%', 'd', '\0'}};
struct struct_1 string_34 = {2, {'%', 'd', '\0'}};
struct struct_1 string_35 = {2, {'%', 'd', '\0'}};
struct struct_1 string_36 = {2, {'%', 'd', '\0'}};
struct struct_1 string_37 = {2, {'%', 'd', '\0'}};
struct struct_1 string_38 = {2, {'%', 'd', '\0'}};

/* Enum definitions */

/* Function and procedure definitions */
signed int test_testModule_main(struct struct_2* _args)
{
	signed int retval;
	struct struct_1* _0 = &string_23;
	bool _1 = 1;
	bool _2 = 1;
	bool _3 = 1;
	if (_3) goto over_1;
	bool _4 = 1;
	_2 = _4;
over_1:;
	if (_2) goto over_0;
	bool _5 = 1;
	_1 = _5;
over_0:;
	signed int _6 = stdlib_system_println(_0, _1);
	struct struct_1* _7 = &string_24;
	bool _8 = 1;
	bool _9 = 1;
	bool _10 = 1;
	if (_10) goto over_3;
	bool _11 = 1;
	_9 = _11;
over_3:;
	if (_9) goto over_2;
	bool _12 = 0;
	_8 = _12;
over_2:;
	signed int _13 = stdlib_system_println(_7, _8);
	struct struct_1* _14 = &string_25;
	bool _15 = 1;
	bool _16 = 1;
	bool _17 = 1;
	if (_17) goto over_5;
	bool _18 = 0;
	_16 = _18;
over_5:;
	if (_16) goto over_4;
	bool _19 = 1;
	_15 = _19;
over_4:;
	signed int _20 = stdlib_system_println(_14, _15);
	struct struct_1* _21 = &string_26;
	bool _22 = 1;
	bool _23 = 1;
	bool _24 = 1;
	if (_24) goto over_7;
	bool _25 = 0;
	_23 = _25;
over_7:;
	if (_23) goto over_6;
	bool _26 = 0;
	_22 = _26;
over_6:;
	signed int _27 = stdlib_system_println(_21, _22);
	struct struct_1* _28 = &string_27;
	bool _29 = 1;
	bool _30 = 1;
	bool _31 = 0;
	if (_31) goto over_9;
	bool _32 = 1;
	_30 = _32;
over_9:;
	if (_30) goto over_8;
	bool _33 = 1;
	_29 = _33;
over_8:;
	signed int _34 = stdlib_system_println(_28, _29);
	struct struct_1* _35 = &string_28;
	bool _36 = 1;
	bool _37 = 1;
	bool _38 = 0;
	if (_38) goto over_11;
	bool _39 = 1;
	_37 = _39;
over_11:;
	if (_37) goto over_10;
	bool _40 = 0;
	_36 = _40;
over_10:;
	signed int _41 = stdlib_system_println(_35, _36);
	struct struct_1* _42 = &string_29;
	bool _43 = 1;
	bool _44 = 1;
	bool _45 = 0;
	if (_45) goto over_13;
	bool _46 = 0;
	_44 = _46;
over_13:;
	if (_44) goto over_12;
	bool _47 = 1;
	_43 = _47;
over_12:;
	signed int _48 = stdlib_system_println(_42, _43);
	struct struct_1* _49 = &string_30;
	bool _50 = 1;
	bool _51 = 1;
	bool _52 = 0;
	if (_52) goto over_15;
	bool _53 = 0;
	_51 = _53;
over_15:;
	if (_51) goto over_14;
	bool _54 = 0;
	_50 = _54;
over_14:;
	signed int _55 = stdlib_system_println(_49, _50);
	struct struct_1* _56 = &string_31;
	bool _57 = 0;
	bool _58 = 0;
	bool _59 = 1;
	if (!_59) goto over_17;
	bool _60 = 1;
	_58 = _60;
over_17:;
	if (!_58) goto over_16;
	bool _61 = 1;
	_57 = _61;
over_16:;
	signed int _62 = stdlib_system_println(_56, _57);
	struct struct_1* _63 = &string_32;
	bool _64 = 0;
	bool _65 = 0;
	bool _66 = 1;
	if (!_66) goto over_19;
	bool _67 = 1;
	_65 = _67;
over_19:;
	if (!_65) goto over_18;
	bool _68 = 0;
	_64 = _68;
over_18:;
	signed int _69 = stdlib_system_println(_63, _64);
	struct struct_1* _70 = &string_33;
	bool _71 = 0;
	bool _72 = 0;
	bool _73 = 1;
	if (!_73) goto over_21;
	bool _74 = 0;
	_72 = _74;
over_21:;
	if (!_72) goto over_20;
	bool _75 = 1;
	_71 = _75;
over_20:;
	signed int _76 = stdlib_system_println(_70, _71);
	struct struct_1* _77 = &string_34;
	bool _78 = 0;
	bool _79 = 0;
	bool _80 = 1;
	if (!_80) goto over_23;
	bool _81 = 0;
	_79 = _81;
over_23:;
	if (!_79) goto over_22;
	bool _82 = 0;
	_78 = _82;
over_22:;
	signed int _83 = stdlib_system_println(_77, _78);
	struct struct_1* _84 = &string_35;
	bool _85 = 0;
	bool _86 = 0;
	bool _87 = 0;
	if (!_87) goto over_25;
	bool _88 = 1;
	_86 = _88;
over_25:;
	if (!_86) goto over_24;
	bool _89 = 1;
	_85 = _89;
over_24:;
	signed int _90 = stdlib_system_println(_84, _85);
	struct struct_1* _91 = &string_36;
	bool _92 = 0;
	bool _93 = 0;
	bool _94 = 0;
	if (!_94) goto over_27;
	bool _95 = 1;
	_93 = _95;
over_27:;
	if (!_93) goto over_26;
	bool _96 = 0;
	_92 = _96;
over_26:;
	signed int _97 = stdlib_system_println(_91, _92);
	struct struct_1* _98 = &string_37;
	bool _99 = 0;
	bool _100 = 0;
	bool _101 = 0;
	if (!_101) goto over_29;
	bool _102 = 0;
	_100 = _102;
over_29:;
	if (!_100) goto over_28;
	bool _103 = 1;
	_99 = _103;
over_28:;
	signed int _104 = stdlib_system_println(_98, _99);
	struct struct_1* _105 = &string_38;
	bool _106 = 0;
	bool _107 = 0;
	bool _108 = 0;
	if (!_108) goto over_31;
	bool _109 = 0;
	_107 = _109;
over_31:;
	if (!_107) goto over_30;
	bool _110 = 0;
	_106 = _110;
over_30:;
	signed int _111 = stdlib_system_println(_105, _106);
	signed int _112 = 0;
	retval = _112;
	goto return_block_178;
continue_178:;
return_block_178:;
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
