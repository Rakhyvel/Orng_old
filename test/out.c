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
	int64_t* data;
};

struct struct_9 {
	int64_t length;
	bool* data;
};

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

int64_t test_testModule_main(struct struct_2 _args);

#ifndef ORANGE_PROGRAM_28306
#define ORANGE_PROGRAM_28306

/* String definitions */
struct struct_1 string_0 = {20, (char[]){'n', 'o', ' ', 'm', 'e', 's', 's', 'a', 'g', 'e', ' ', 's', 'p', 'e', 'c', 'i', 'f', 'i', 'e', 'd', '\0'}};
struct struct_1 string_1 = {18, (char[]){'a', 's', 's', 'e', 'r', 't', 'i', 'o', 'n', ' ', 'f', 'a', 'i', 'l', 'e', 'd', ':', ' ', '\0'}};
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

int64_t test_testModule_main(struct struct_2 _args)
{
	int64_t retval;
	bool _158_z;
	bool* _158_c_0;
	bool* _6;
	bool _7;
	int64_t _9;
L6:; // incoming:1
	_158_z = 0;
	_6 = &_158_z;
	_158_c_0 = _6;
	_7 = 0;
	*_158_c_0 = _7;
	if (!_158_z) {
		goto L11;
	} else {
		goto L8;
	}
L8:; // incoming:1
	_9 = 4;
	goto L9;
L9:; // incoming:2
	retval = _9;
	goto L0;
L11:; // incoming:1
	_9 = 5;
	goto L9;
L0:;
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
