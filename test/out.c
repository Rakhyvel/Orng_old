/* Code generated using the Orng compiler http://josephs-projects.com */

#ifndef ORNG_26138
#define ORNG_26138
#define _CRT_SECURE_NO_WARNINGS

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
	char* data[1000];
};

struct list stackTrace;
struct list errorTrace;

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
	case 79:
		return "something";
	case 2:
		return "operationNotPermitted";
	case 3:
		return "noSuchFileOrDirectory";
	case 4:
		return "noSuchProcess";
	case 5:
		return "interruptedSystemCall";
	case 6:
		return "inputOutputError";
	case 7:
		return "noSuchDeviceOrAddress";
	case 8:
		return "argumentListTooLong";
	case 9:
		return "execFormatError";
	case 10:
		return "badFileDescriptor";
	case 11:
		return "noChildProcesses";
	case 12:
		return "resourceTemporarilyUnavailable";
	case 13:
		return "cannotAllocateMemory";
	case 14:
		return "permissionDenied";
	case 15:
		return "badAddress";
	case 16:
		return "deviceOrResourceBusy";
	case 17:
		return "fileExists";
	case 18:
		return "invalidCrossDeviceLink";
	case 19:
		return "noSuchDevice";
	case 20:
		return "notADirectory";
	case 21:
		return "isADirectory";
	case 22:
		return "invalidArgument";
	case 23:
		return "tooManyOpenFilesInSystem";
	case 24:
		return "tooManyOpenFiles";
	case 25:
		return "inappropriateIOCTLForDevice";
	case 26:
		return "textFileBusy";
	case 27:
		return "fileTooLarge";
	case 28:
		return "noSpaceLeftOnDevice";
	case 29:
		return "illegalSeek";
	case 30:
		return "readOnlyFileSystem";
	case 31:
		return "tooManyLinks";
	case 32:
		return "brokenPipe";
	case 33:
		return "numericalArgumentOutOfDomain";
	case 34:
		return "numericalArgumentOutOfRange";
	case 35:
		return "resourceDeadlockAvoided";
	case 36:
		return "fileNameTooLong";
	case 37:
		return "noLocksAvailable";
	case 38:
		return "functionNotImplemented";
	case 39:
		return "directoryNotEmpty";
	case 40:
		return "tooManyLevelsOfSymbolicLinks";
	case 41:
		return "noMessageOfDesiredType";
	case 42:
		return "identifierRemoved";
	case 43:
		return "deviceNotAStream";
	case 44:
		return "noDataAvailable";
	case 45:
		return "timerExpired";
	case 46:
		return "outOfStreamsResources";
	case 47:
		return "linkHasBeenSevered";
	case 48:
		return "protocolError";
	case 49:
		return "badMessage";
	case 50:
		return "valueTooLargeForDefinedDataType";
	case 51:
		return "invalidOrIncompleteMultibyteOrWideCharacter";
	case 52:
		return "socketOperationOnNonSocket";
	case 53:
		return "destinationAddressRequired";
	case 54:
		return "messageTooLong";
	case 55:
		return "protocolWrongTypeForSocket";
	case 56:
		return "protocolNotAvailable";
	case 57:
		return "protocolNotSupported";
	case 58:
		return "operationNotSupported";
	case 59:
		return "addressFamilyNotSupportedByProtocol";
	case 60:
		return "addressAlreadyInUse";
	case 61:
		return "cannotAssignRequestedAddress";
	case 62:
		return "networkIsDown";
	case 63:
		return "networkIsUnreachable";
	case 64:
		return "networkDroppedConnectionOnReset";
	case 65:
		return "softwareCausedConnectionAbort";
	case 66:
		return "connectionResetByPeer";
	case 67:
		return "noBufferSpaceAvailable";
	case 68:
		return "transportEndpointIsAlreadyConnected";
	case 69:
		return "transportEndpointIsNotConnected";
	case 70:
		return "connectionTimedOut";
	case 71:
		return "connectionRefused";
	case 72:
		return "noRouteToHost";
	case 73:
		return "operationAlreadyInProgress";
	case 74:
		return "operationNowInProgress";
	case 75:
		return "operationCancelled";
	case 76:
		return "ownerDied";
	case 77:
		return "stateNotRecoverable";
	case 78:
	case 80:
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
		FILE* success;
	};
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
	int64_t tag;
};

/* Verbatim code */
int std_system_println(struct struct_1 _format, ...) {va_list _25_args;va_start(_25_args, _format.data);int retval = vprintf(_format.data, _25_args);va_end(_25_args);char newLine[2] = {'\n', '\0'};printf(newLine);return retval;}
int std_system_err(struct struct_1 _format, ...) {va_list _25_args;va_start(_25_args, _format.data);int retval = vfprintf(stderr, _format.data, _25_args);va_end(_25_args);char newLine[2] = {'\n', '\0'};return retval;}
int std_system_errln(struct struct_1 _format, ...) {va_list _25_args;va_start(_25_args, _format.data);int retval = vfprintf(stderr, _format.data, _25_args);va_end(_25_args);char newLine[2] = {'\n', '\0'};fprintf(stderr, newLine);return retval;}

/* Function definitions */
struct struct_3 test_testModule_main(struct struct_2 _args);
struct struct_5 std_system_open(struct struct_1 _filename, struct struct_1 _mode);
struct struct_3 std_system_getError();

struct struct_3 test_testModule_main(struct struct_2 _args)
{
	struct struct_3 retval;
	struct struct_5 (*_0) (struct struct_1 _filename, struct struct_1 _mode);
	int64_t _2;
	int64_t _5;
	bool _6;
	struct struct_2 _args_0;
	struct struct_1 _3;
	struct struct_1 _8;
	struct struct_5 _1;
	int64_t _9;
	int64_t _10;
	bool _11;
	struct struct_2 _args_1;
	struct struct_2 _args_2;
	int64_t (*_15) (struct struct_1 _format, ...);
	struct struct_1 _17;
	int64_t _18;
	int64_t _21;
	bool _22;
	struct struct_2 _args_3;
	struct struct_1 _19;
	int64_t _16;
	int64_t _24;
	struct struct_3 _25;
	struct struct_2 _args_4;
	struct struct_2 _args_5;
	struct struct_2 _args_6;
	struct struct_2 _args_7;
	_args_0 = _args;
L157:; // incoming:1
	_0 = std_system_open;
	_2 = 0;
	_5 = _args_0.length;
	_6 = _2 < _5;
	if (!_6) {
		_args_7 = _args_0;
		goto L175;
	} else {
		_args_1 = _args_0;
		goto L160;
	}
L160:; // incoming:2
	_3 = _args_1.data[_2];
	_8 = (struct struct_1) {1, "r"};
	if ((&stackTrace)->length >= 1000) {
		fprintf(stderr, "error: stack overflow\n");
		stackTracePrintReverse((&stackTrace));
		exit(1);
	}
	(&stackTrace)->data[(&stackTrace)->length++] = "test/testModule.orng: \n3     | myFile := std.system.open(args[0], \"r\")\n      |                          ^\n";
	_1 = _0(_3, _8);
	stackTrace.length--;
	_9 = _1.tag;
	_10 = 78;
	_11 = _9 != _10;
	if (!_11) {
		_args_6 = _args_1;
		goto L173;
	} else {
		_args_2 = _args_1;
		goto L161;
	}
L161:; // incoming:1
	if ((&errorTrace)->length >= 1000) {
		fprintf(stderr, "error: stack overflow\n");
		stackTracePrintReverse((&errorTrace));
		exit(1);
	}
	(&errorTrace)->data[(&errorTrace)->length++] = "test/testModule.orng: \n3     | myFile := std.system.open(args[0], \"r\")\n      |                          ^\n";
	_args_3 = _args_2;
	goto L162;
L162:; // incoming:2
	_15 = std_system_println;
	_17 = (struct struct_1) {16, "Cannot open '%s'"};
	_18 = 0;
	_21 = _args_3.length;
	_22 = _18 < _21;
	if (!_22) {
		_args_5 = _args_3;
		goto L172;
	} else {
		_args_4 = _args_3;
		goto L167;
	}
L167:; // incoming:2
	_19 = _args_4.data[_18];
	if ((&stackTrace)->length >= 1000) {
		fprintf(stderr, "error: stack overflow\n");
		stackTracePrintReverse((&stackTrace));
		exit(1);
	}
	(&stackTrace)->data[(&stackTrace)->length++] = "test/testModule.orng: \n5     | std.system.Error.noSuchFileOrDirectory -> std.system.println(\"Cannot open '%s'\", args[0])\n      |                                                             ^\n";
	_16 = _15(_17, _19);
	stackTrace.length--;
	_24 = 80;
	_25 = (struct struct_3) {_24};
	retval = _25;
	goto end;
L172:; // incoming:1
	fprintf(stderr, "error: array index greater than array length\n");
	if ((&stackTrace)->length >= 1000) {
		fprintf(stderr, "error: stack overflow\n");
		stackTracePrintReverse((&stackTrace));
		exit(1);
	}
	(&stackTrace)->data[(&stackTrace)->length++] = "test/testModule.orng: \n5     | std.system.Error.noSuchFileOrDirectory -> std.system.println(\"Cannot open '%s'\", args[0])\n      |                                                                                      ^\n";
	stackTracePrintReverse(&stackTrace);
	exit(1);
	_args_4 = _args_5;
	goto L167;
L173:; // incoming:1
errorTrace.length = 0;
	_args_3 = _args_6;
	goto L162;
L175:; // incoming:1
	fprintf(stderr, "error: array index greater than array length\n");
	if ((&stackTrace)->length >= 1000) {
		fprintf(stderr, "error: stack overflow\n");
		stackTracePrintReverse((&stackTrace));
		exit(1);
	}
	(&stackTrace)->data[(&stackTrace)->length++] = "test/testModule.orng: \n3     | myFile := std.system.open(args[0], \"r\")\n      |                               ^\n";
	stackTracePrintReverse(&stackTrace);
	exit(1);
	_args_1 = _args_7;
	goto L160;
end:;
	return retval;
}

struct struct_5 std_system_open(struct struct_1 _filename, struct struct_1 _mode)
{
	struct struct_5 retval;
	FILE* (*_0) (int8_t* _filename, int8_t* _mode);
	int8_t* _2;
	int8_t* _3;
	FILE* _1;
	FILE* _29_retval_0;
	int64_t _6;
	int64_t _7;
	bool _5;
	struct struct_1 _filename_0;
	struct struct_1 _mode_0;
	struct struct_3 (*_8) ();
	struct struct_3 _9;
	struct struct_5 _10;
	int64_t _11;
	struct struct_5 _12;
	FILE* _29_retval_1;
	_filename_0 = _filename;
	_mode_0 = _mode;
L154:; // incoming:1
	_0 = fopen;
	_2 = _filename_0.data;
	_3 = _mode_0.data;
	if ((&stackTrace)->length >= 1000) {
		fprintf(stderr, "error: stack overflow\n");
		stackTracePrintReverse((&stackTrace));
		exit(1);
	}
	(&stackTrace)->data[(&stackTrace)->length++] = "std/system.orng: \n249   | retval := fopen(filename.data, mode.data)\n      |                ^\n";
	_1 = _0(_2, _3);
	stackTrace.length--;
	_29_retval_0 = _1;
	_6 = (int64_t) _29_retval_0;
	_7 = 0;
	_5 = _6 == _7;
	if (!_5) {
		_29_retval_1 = _29_retval_0;
		goto L156;
	} else {
		goto L155;
	}
L155:; // incoming:1
	_8 = std_system_getError;
	if ((&stackTrace)->length >= 1000) {
		fprintf(stderr, "error: stack overflow\n");
		stackTracePrintReverse((&stackTrace));
		exit(1);
	}
	(&stackTrace)->data[(&stackTrace)->length++] = "std/system.orng: \n251   | return getError()\n      |                ^\n";
	_9 = _8();
	stackTrace.length--;
	_10 = *((struct struct_5*) &_9);
	retval = _10;
	goto end;
L156:; // incoming:1
	_11 = 78;
	_12 = (struct struct_5) {_11, _29_retval_1};
	retval = _12;
	goto end;
end:;
	return retval;
}

struct struct_3 std_system_getError()
{
	struct struct_3 retval;
	struct struct_3 _0;
	int64_t _1;
	int64_t _2;
	int64_t _4;
	bool _3;
	int64_t _5;
	int64_t _7;
	bool _6;
	int64_t _8;
	int64_t _10;
	bool _9;
	int64_t _11;
	int64_t _13;
	bool _12;
	int64_t _14;
	int64_t _16;
	bool _15;
	int64_t _17;
	int64_t _19;
	bool _18;
	int64_t _20;
	int64_t _22;
	bool _21;
	int64_t _23;
	int64_t _25;
	bool _24;
	int64_t _26;
	int64_t _28;
	bool _27;
	int64_t _29;
	int64_t _31;
	bool _30;
	int64_t _32;
	int64_t _34;
	bool _33;
	int64_t _35;
	int64_t _37;
	bool _36;
	int64_t _38;
	int64_t _40;
	bool _39;
	int64_t _41;
	int64_t _43;
	bool _42;
	int64_t _44;
	int64_t _46;
	bool _45;
	int64_t _47;
	int64_t _49;
	bool _48;
	int64_t _50;
	int64_t _52;
	bool _51;
	int64_t _53;
	int64_t _55;
	bool _54;
	int64_t _56;
	int64_t _58;
	bool _57;
	int64_t _59;
	int64_t _61;
	bool _60;
	int64_t _62;
	int64_t _64;
	bool _63;
	int64_t _65;
	int64_t _67;
	bool _66;
	int64_t _68;
	int64_t _70;
	bool _69;
	int64_t _71;
	int64_t _73;
	bool _72;
	int64_t _74;
	int64_t _76;
	bool _75;
	int64_t _77;
	int64_t _79;
	bool _78;
	int64_t _80;
	int64_t _82;
	bool _81;
	int64_t _83;
	int64_t _85;
	bool _84;
	int64_t _86;
	int64_t _88;
	bool _87;
	int64_t _89;
	int64_t _91;
	bool _90;
	int64_t _92;
	int64_t _94;
	bool _93;
	int64_t _95;
	int64_t _97;
	bool _96;
	int64_t _98;
	int64_t _100;
	bool _99;
	int64_t _101;
	int64_t _103;
	bool _102;
	int64_t _104;
	int64_t _106;
	bool _105;
	int64_t _107;
	int64_t _109;
	bool _108;
	int64_t _110;
	int64_t _112;
	bool _111;
	int64_t _113;
	int64_t _115;
	bool _114;
	int64_t _116;
	int64_t _118;
	bool _117;
	int64_t _119;
	int64_t _121;
	bool _120;
	int64_t _122;
	int64_t _124;
	bool _123;
	int64_t _125;
	int64_t _127;
	bool _126;
	int64_t _128;
	int64_t _130;
	bool _129;
	int64_t _131;
	int64_t _133;
	bool _132;
	int64_t _134;
	int64_t _136;
	bool _135;
	int64_t _137;
	int64_t _139;
	bool _138;
	int64_t _140;
	int64_t _142;
	bool _141;
	int64_t _143;
	int64_t _145;
	bool _144;
	int64_t _146;
	int64_t _148;
	bool _147;
	int64_t _149;
	int64_t _151;
	bool _150;
	int64_t _152;
	int64_t _154;
	bool _153;
	int64_t _155;
	int64_t _157;
	bool _156;
	int64_t _158;
	int64_t _160;
	bool _159;
	int64_t _161;
	int64_t _163;
	bool _162;
	int64_t _164;
	int64_t _166;
	bool _165;
	int64_t _167;
	int64_t _169;
	bool _168;
	int64_t _170;
	int64_t _172;
	bool _171;
	int64_t _173;
	int64_t _175;
	bool _174;
	int64_t _176;
	int64_t _178;
	bool _177;
	int64_t _179;
	int64_t _181;
	bool _180;
	int64_t _182;
	int64_t _184;
	bool _183;
	int64_t _185;
	int64_t _187;
	bool _186;
	int64_t _188;
	int64_t _190;
	bool _189;
	int64_t _191;
	int64_t _193;
	bool _192;
	int64_t _194;
	int64_t _196;
	bool _195;
	int64_t _197;
	int64_t _199;
	bool _198;
	int64_t _200;
	int64_t _202;
	bool _201;
	int64_t _203;
	int64_t _205;
	bool _204;
	int64_t _206;
	int64_t _208;
	bool _207;
	int64_t _209;
	int64_t _211;
	bool _210;
	int64_t _212;
	int64_t _214;
	bool _213;
	int64_t _215;
	int64_t _217;
	bool _216;
	int64_t _218;
	int64_t _220;
	bool _219;
	int64_t _221;
	int64_t _223;
	bool _222;
	int64_t _224;
	int64_t _226;
	bool _225;
	int64_t _227;
	int64_t _229;
	bool _228;
	int64_t _230;
	struct struct_3 _231;
	int64_t _380;
	struct struct_3 _381;
	int64_t _378;
	struct struct_3 _379;
	int64_t _376;
	struct struct_3 _377;
	int64_t _374;
	struct struct_3 _375;
	int64_t _372;
	struct struct_3 _373;
	int64_t _370;
	struct struct_3 _371;
	int64_t _368;
	struct struct_3 _369;
	int64_t _366;
	struct struct_3 _367;
	int64_t _364;
	struct struct_3 _365;
	int64_t _362;
	struct struct_3 _363;
	int64_t _360;
	struct struct_3 _361;
	int64_t _358;
	struct struct_3 _359;
	int64_t _356;
	struct struct_3 _357;
	int64_t _354;
	struct struct_3 _355;
	int64_t _352;
	struct struct_3 _353;
	int64_t _350;
	struct struct_3 _351;
	int64_t _348;
	struct struct_3 _349;
	int64_t _346;
	struct struct_3 _347;
	int64_t _344;
	struct struct_3 _345;
	int64_t _342;
	struct struct_3 _343;
	int64_t _340;
	struct struct_3 _341;
	int64_t _338;
	struct struct_3 _339;
	int64_t _336;
	struct struct_3 _337;
	int64_t _334;
	struct struct_3 _335;
	int64_t _332;
	struct struct_3 _333;
	int64_t _330;
	struct struct_3 _331;
	int64_t _328;
	struct struct_3 _329;
	int64_t _326;
	struct struct_3 _327;
	int64_t _324;
	struct struct_3 _325;
	int64_t _322;
	struct struct_3 _323;
	int64_t _320;
	struct struct_3 _321;
	int64_t _318;
	struct struct_3 _319;
	int64_t _316;
	struct struct_3 _317;
	int64_t _314;
	struct struct_3 _315;
	int64_t _312;
	struct struct_3 _313;
	int64_t _310;
	struct struct_3 _311;
	int64_t _308;
	struct struct_3 _309;
	int64_t _306;
	struct struct_3 _307;
	int64_t _304;
	struct struct_3 _305;
	int64_t _302;
	struct struct_3 _303;
	int64_t _300;
	struct struct_3 _301;
	int64_t _298;
	struct struct_3 _299;
	int64_t _296;
	struct struct_3 _297;
	int64_t _294;
	struct struct_3 _295;
	int64_t _292;
	struct struct_3 _293;
	int64_t _290;
	struct struct_3 _291;
	int64_t _288;
	struct struct_3 _289;
	int64_t _286;
	struct struct_3 _287;
	int64_t _284;
	struct struct_3 _285;
	int64_t _282;
	struct struct_3 _283;
	int64_t _280;
	struct struct_3 _281;
	int64_t _278;
	struct struct_3 _279;
	int64_t _276;
	struct struct_3 _277;
	int64_t _274;
	struct struct_3 _275;
	int64_t _272;
	struct struct_3 _273;
	int64_t _270;
	struct struct_3 _271;
	int64_t _268;
	struct struct_3 _269;
	int64_t _266;
	struct struct_3 _267;
	int64_t _264;
	struct struct_3 _265;
	int64_t _262;
	struct struct_3 _263;
	int64_t _260;
	struct struct_3 _261;
	int64_t _258;
	struct struct_3 _259;
	int64_t _256;
	struct struct_3 _257;
	int64_t _254;
	struct struct_3 _255;
	int64_t _252;
	struct struct_3 _253;
	int64_t _250;
	struct struct_3 _251;
	int64_t _248;
	struct struct_3 _249;
	int64_t _246;
	struct struct_3 _247;
	int64_t _244;
	struct struct_3 _245;
	int64_t _242;
	struct struct_3 _243;
	int64_t _240;
	struct struct_3 _241;
	int64_t _238;
	struct struct_3 _239;
	int64_t _236;
	struct struct_3 _237;
	int64_t _234;
	struct struct_3 _235;
	int64_t _232;
	struct struct_3 _233;
L0:; // incoming:1
	_1 = errno;
	_2 = EPERM;
	_4 = _1;
	_3 = _4 != _2;
	if (!_3) {
		goto L77;
	} else {
		goto L1;
	}
L1:; // incoming:1
	_5 = ENOENT;
	_7 = _1;
	_6 = _7 != _5;
	if (!_6) {
		goto L153;
	} else {
		goto L2;
	}
L2:; // incoming:1
	_8 = ESRCH;
	_10 = _1;
	_9 = _10 != _8;
	if (!_9) {
		goto L152;
	} else {
		goto L3;
	}
L3:; // incoming:1
	_11 = EINTR;
	_13 = _1;
	_12 = _13 != _11;
	if (!_12) {
		goto L151;
	} else {
		goto L4;
	}
L4:; // incoming:1
	_14 = EIO;
	_16 = _1;
	_15 = _16 != _14;
	if (!_15) {
		goto L150;
	} else {
		goto L5;
	}
L5:; // incoming:1
	_17 = ENXIO;
	_19 = _1;
	_18 = _19 != _17;
	if (!_18) {
		goto L149;
	} else {
		goto L6;
	}
L6:; // incoming:1
	_20 = E2BIG;
	_22 = _1;
	_21 = _22 != _20;
	if (!_21) {
		goto L148;
	} else {
		goto L7;
	}
L7:; // incoming:1
	_23 = ENOEXEC;
	_25 = _1;
	_24 = _25 != _23;
	if (!_24) {
		goto L147;
	} else {
		goto L8;
	}
L8:; // incoming:1
	_26 = EBADF;
	_28 = _1;
	_27 = _28 != _26;
	if (!_27) {
		goto L146;
	} else {
		goto L9;
	}
L9:; // incoming:1
	_29 = ECHILD;
	_31 = _1;
	_30 = _31 != _29;
	if (!_30) {
		goto L145;
	} else {
		goto L10;
	}
L10:; // incoming:1
	_32 = EAGAIN;
	_34 = _1;
	_33 = _34 != _32;
	if (!_33) {
		goto L144;
	} else {
		goto L11;
	}
L11:; // incoming:1
	_35 = ENOMEM;
	_37 = _1;
	_36 = _37 != _35;
	if (!_36) {
		goto L143;
	} else {
		goto L12;
	}
L12:; // incoming:1
	_38 = EACCES;
	_40 = _1;
	_39 = _40 != _38;
	if (!_39) {
		goto L142;
	} else {
		goto L13;
	}
L13:; // incoming:1
	_41 = EFAULT;
	_43 = _1;
	_42 = _43 != _41;
	if (!_42) {
		goto L141;
	} else {
		goto L14;
	}
L14:; // incoming:1
	_44 = EBUSY;
	_46 = _1;
	_45 = _46 != _44;
	if (!_45) {
		goto L140;
	} else {
		goto L15;
	}
L15:; // incoming:1
	_47 = EEXIST;
	_49 = _1;
	_48 = _49 != _47;
	if (!_48) {
		goto L139;
	} else {
		goto L16;
	}
L16:; // incoming:1
	_50 = EXDEV;
	_52 = _1;
	_51 = _52 != _50;
	if (!_51) {
		goto L138;
	} else {
		goto L17;
	}
L17:; // incoming:1
	_53 = ENODEV;
	_55 = _1;
	_54 = _55 != _53;
	if (!_54) {
		goto L137;
	} else {
		goto L18;
	}
L18:; // incoming:1
	_56 = ENOTDIR;
	_58 = _1;
	_57 = _58 != _56;
	if (!_57) {
		goto L136;
	} else {
		goto L19;
	}
L19:; // incoming:1
	_59 = EISDIR;
	_61 = _1;
	_60 = _61 != _59;
	if (!_60) {
		goto L135;
	} else {
		goto L20;
	}
L20:; // incoming:1
	_62 = EINVAL;
	_64 = _1;
	_63 = _64 != _62;
	if (!_63) {
		goto L134;
	} else {
		goto L21;
	}
L21:; // incoming:1
	_65 = ENFILE;
	_67 = _1;
	_66 = _67 != _65;
	if (!_66) {
		goto L133;
	} else {
		goto L22;
	}
L22:; // incoming:1
	_68 = EMFILE;
	_70 = _1;
	_69 = _70 != _68;
	if (!_69) {
		goto L132;
	} else {
		goto L23;
	}
L23:; // incoming:1
	_71 = ENOTTY;
	_73 = _1;
	_72 = _73 != _71;
	if (!_72) {
		goto L131;
	} else {
		goto L24;
	}
L24:; // incoming:1
	_74 = ETXTBSY;
	_76 = _1;
	_75 = _76 != _74;
	if (!_75) {
		goto L130;
	} else {
		goto L25;
	}
L25:; // incoming:1
	_77 = EFBIG;
	_79 = _1;
	_78 = _79 != _77;
	if (!_78) {
		goto L129;
	} else {
		goto L26;
	}
L26:; // incoming:1
	_80 = ENOSPC;
	_82 = _1;
	_81 = _82 != _80;
	if (!_81) {
		goto L128;
	} else {
		goto L27;
	}
L27:; // incoming:1
	_83 = ESPIPE;
	_85 = _1;
	_84 = _85 != _83;
	if (!_84) {
		goto L127;
	} else {
		goto L28;
	}
L28:; // incoming:1
	_86 = EROFS;
	_88 = _1;
	_87 = _88 != _86;
	if (!_87) {
		goto L126;
	} else {
		goto L29;
	}
L29:; // incoming:1
	_89 = EMLINK;
	_91 = _1;
	_90 = _91 != _89;
	if (!_90) {
		goto L125;
	} else {
		goto L30;
	}
L30:; // incoming:1
	_92 = EPIPE;
	_94 = _1;
	_93 = _94 != _92;
	if (!_93) {
		goto L124;
	} else {
		goto L31;
	}
L31:; // incoming:1
	_95 = EDOM;
	_97 = _1;
	_96 = _97 != _95;
	if (!_96) {
		goto L123;
	} else {
		goto L32;
	}
L32:; // incoming:1
	_98 = ERANGE;
	_100 = _1;
	_99 = _100 != _98;
	if (!_99) {
		goto L122;
	} else {
		goto L33;
	}
L33:; // incoming:1
	_101 = EDEADLK;
	_103 = _1;
	_102 = _103 != _101;
	if (!_102) {
		goto L121;
	} else {
		goto L34;
	}
L34:; // incoming:1
	_104 = ENAMETOOLONG;
	_106 = _1;
	_105 = _106 != _104;
	if (!_105) {
		goto L120;
	} else {
		goto L35;
	}
L35:; // incoming:1
	_107 = ENOLCK;
	_109 = _1;
	_108 = _109 != _107;
	if (!_108) {
		goto L119;
	} else {
		goto L36;
	}
L36:; // incoming:1
	_110 = ENOSYS;
	_112 = _1;
	_111 = _112 != _110;
	if (!_111) {
		goto L118;
	} else {
		goto L37;
	}
L37:; // incoming:1
	_113 = ENOTEMPTY;
	_115 = _1;
	_114 = _115 != _113;
	if (!_114) {
		goto L117;
	} else {
		goto L38;
	}
L38:; // incoming:1
	_116 = ELOOP;
	_118 = _1;
	_117 = _118 != _116;
	if (!_117) {
		goto L116;
	} else {
		goto L39;
	}
L39:; // incoming:1
	_119 = ENOMSG;
	_121 = _1;
	_120 = _121 != _119;
	if (!_120) {
		goto L115;
	} else {
		goto L40;
	}
L40:; // incoming:1
	_122 = EIDRM;
	_124 = _1;
	_123 = _124 != _122;
	if (!_123) {
		goto L114;
	} else {
		goto L41;
	}
L41:; // incoming:1
	_125 = ENOSTR;
	_127 = _1;
	_126 = _127 != _125;
	if (!_126) {
		goto L113;
	} else {
		goto L42;
	}
L42:; // incoming:1
	_128 = ENODATA;
	_130 = _1;
	_129 = _130 != _128;
	if (!_129) {
		goto L112;
	} else {
		goto L43;
	}
L43:; // incoming:1
	_131 = ETIME;
	_133 = _1;
	_132 = _133 != _131;
	if (!_132) {
		goto L111;
	} else {
		goto L44;
	}
L44:; // incoming:1
	_134 = ENOSR;
	_136 = _1;
	_135 = _136 != _134;
	if (!_135) {
		goto L110;
	} else {
		goto L45;
	}
L45:; // incoming:1
	_137 = ENOLINK;
	_139 = _1;
	_138 = _139 != _137;
	if (!_138) {
		goto L109;
	} else {
		goto L46;
	}
L46:; // incoming:1
	_140 = EPROTO;
	_142 = _1;
	_141 = _142 != _140;
	if (!_141) {
		goto L108;
	} else {
		goto L47;
	}
L47:; // incoming:1
	_143 = EBADMSG;
	_145 = _1;
	_144 = _145 != _143;
	if (!_144) {
		goto L107;
	} else {
		goto L48;
	}
L48:; // incoming:1
	_146 = EOVERFLOW;
	_148 = _1;
	_147 = _148 != _146;
	if (!_147) {
		goto L106;
	} else {
		goto L49;
	}
L49:; // incoming:1
	_149 = EILSEQ;
	_151 = _1;
	_150 = _151 != _149;
	if (!_150) {
		goto L105;
	} else {
		goto L50;
	}
L50:; // incoming:1
	_152 = ENOTSOCK;
	_154 = _1;
	_153 = _154 != _152;
	if (!_153) {
		goto L104;
	} else {
		goto L51;
	}
L51:; // incoming:1
	_155 = EDESTADDRREQ;
	_157 = _1;
	_156 = _157 != _155;
	if (!_156) {
		goto L103;
	} else {
		goto L52;
	}
L52:; // incoming:1
	_158 = EMSGSIZE;
	_160 = _1;
	_159 = _160 != _158;
	if (!_159) {
		goto L102;
	} else {
		goto L53;
	}
L53:; // incoming:1
	_161 = EPROTOTYPE;
	_163 = _1;
	_162 = _163 != _161;
	if (!_162) {
		goto L101;
	} else {
		goto L54;
	}
L54:; // incoming:1
	_164 = ENOPROTOOPT;
	_166 = _1;
	_165 = _166 != _164;
	if (!_165) {
		goto L100;
	} else {
		goto L55;
	}
L55:; // incoming:1
	_167 = EPROTONOSUPPORT;
	_169 = _1;
	_168 = _169 != _167;
	if (!_168) {
		goto L99;
	} else {
		goto L56;
	}
L56:; // incoming:1
	_170 = EOPNOTSUPP;
	_172 = _1;
	_171 = _172 != _170;
	if (!_171) {
		goto L98;
	} else {
		goto L57;
	}
L57:; // incoming:1
	_173 = EAFNOSUPPORT;
	_175 = _1;
	_174 = _175 != _173;
	if (!_174) {
		goto L97;
	} else {
		goto L58;
	}
L58:; // incoming:1
	_176 = EADDRINUSE;
	_178 = _1;
	_177 = _178 != _176;
	if (!_177) {
		goto L96;
	} else {
		goto L59;
	}
L59:; // incoming:1
	_179 = EADDRNOTAVAIL;
	_181 = _1;
	_180 = _181 != _179;
	if (!_180) {
		goto L95;
	} else {
		goto L60;
	}
L60:; // incoming:1
	_182 = ENETDOWN;
	_184 = _1;
	_183 = _184 != _182;
	if (!_183) {
		goto L94;
	} else {
		goto L61;
	}
L61:; // incoming:1
	_185 = ENETUNREACH;
	_187 = _1;
	_186 = _187 != _185;
	if (!_186) {
		goto L93;
	} else {
		goto L62;
	}
L62:; // incoming:1
	_188 = ENETRESET;
	_190 = _1;
	_189 = _190 != _188;
	if (!_189) {
		goto L92;
	} else {
		goto L63;
	}
L63:; // incoming:1
	_191 = ECONNABORTED;
	_193 = _1;
	_192 = _193 != _191;
	if (!_192) {
		goto L91;
	} else {
		goto L64;
	}
L64:; // incoming:1
	_194 = ECONNRESET;
	_196 = _1;
	_195 = _196 != _194;
	if (!_195) {
		goto L90;
	} else {
		goto L65;
	}
L65:; // incoming:1
	_197 = ENOBUFS;
	_199 = _1;
	_198 = _199 != _197;
	if (!_198) {
		goto L89;
	} else {
		goto L66;
	}
L66:; // incoming:1
	_200 = EISCONN;
	_202 = _1;
	_201 = _202 != _200;
	if (!_201) {
		goto L88;
	} else {
		goto L67;
	}
L67:; // incoming:1
	_203 = ENOTCONN;
	_205 = _1;
	_204 = _205 != _203;
	if (!_204) {
		goto L87;
	} else {
		goto L68;
	}
L68:; // incoming:1
	_206 = ETIMEDOUT;
	_208 = _1;
	_207 = _208 != _206;
	if (!_207) {
		goto L86;
	} else {
		goto L69;
	}
L69:; // incoming:1
	_209 = ECONNREFUSED;
	_211 = _1;
	_210 = _211 != _209;
	if (!_210) {
		goto L85;
	} else {
		goto L70;
	}
L70:; // incoming:1
	_212 = EHOSTUNREACH;
	_214 = _1;
	_213 = _214 != _212;
	if (!_213) {
		goto L84;
	} else {
		goto L71;
	}
L71:; // incoming:1
	_215 = EALREADY;
	_217 = _1;
	_216 = _217 != _215;
	if (!_216) {
		goto L83;
	} else {
		goto L72;
	}
L72:; // incoming:1
	_218 = EINPROGRESS;
	_220 = _1;
	_219 = _220 != _218;
	if (!_219) {
		goto L82;
	} else {
		goto L73;
	}
L73:; // incoming:1
	_221 = ECANCELED;
	_223 = _1;
	_222 = _223 != _221;
	if (!_222) {
		goto L81;
	} else {
		goto L74;
	}
L74:; // incoming:1
	_224 = EOWNERDEAD;
	_226 = _1;
	_225 = _226 != _224;
	if (!_225) {
		goto L80;
	} else {
		goto L75;
	}
L75:; // incoming:1
	_227 = ENOTRECOVERABLE;
	_229 = _1;
	_228 = _229 != _227;
	if (!_228) {
		goto L79;
	} else {
		goto L77;
	}
L77:; // incoming:2
	_230 = 2;
	_231 = (struct struct_3) {_230};
	_0 = _231;
	goto L78;
L78:; // incoming:76
	retval = _0;
	goto end;
L79:; // incoming:1
	_380 = 77;
	_381 = (struct struct_3) {_380};
	_0 = _381;
	goto L78;
L80:; // incoming:1
	_378 = 76;
	_379 = (struct struct_3) {_378};
	_0 = _379;
	goto L78;
L81:; // incoming:1
	_376 = 75;
	_377 = (struct struct_3) {_376};
	_0 = _377;
	goto L78;
L82:; // incoming:1
	_374 = 74;
	_375 = (struct struct_3) {_374};
	_0 = _375;
	goto L78;
L83:; // incoming:1
	_372 = 73;
	_373 = (struct struct_3) {_372};
	_0 = _373;
	goto L78;
L84:; // incoming:1
	_370 = 72;
	_371 = (struct struct_3) {_370};
	_0 = _371;
	goto L78;
L85:; // incoming:1
	_368 = 71;
	_369 = (struct struct_3) {_368};
	_0 = _369;
	goto L78;
L86:; // incoming:1
	_366 = 70;
	_367 = (struct struct_3) {_366};
	_0 = _367;
	goto L78;
L87:; // incoming:1
	_364 = 69;
	_365 = (struct struct_3) {_364};
	_0 = _365;
	goto L78;
L88:; // incoming:1
	_362 = 68;
	_363 = (struct struct_3) {_362};
	_0 = _363;
	goto L78;
L89:; // incoming:1
	_360 = 67;
	_361 = (struct struct_3) {_360};
	_0 = _361;
	goto L78;
L90:; // incoming:1
	_358 = 66;
	_359 = (struct struct_3) {_358};
	_0 = _359;
	goto L78;
L91:; // incoming:1
	_356 = 65;
	_357 = (struct struct_3) {_356};
	_0 = _357;
	goto L78;
L92:; // incoming:1
	_354 = 64;
	_355 = (struct struct_3) {_354};
	_0 = _355;
	goto L78;
L93:; // incoming:1
	_352 = 63;
	_353 = (struct struct_3) {_352};
	_0 = _353;
	goto L78;
L94:; // incoming:1
	_350 = 62;
	_351 = (struct struct_3) {_350};
	_0 = _351;
	goto L78;
L95:; // incoming:1
	_348 = 61;
	_349 = (struct struct_3) {_348};
	_0 = _349;
	goto L78;
L96:; // incoming:1
	_346 = 60;
	_347 = (struct struct_3) {_346};
	_0 = _347;
	goto L78;
L97:; // incoming:1
	_344 = 59;
	_345 = (struct struct_3) {_344};
	_0 = _345;
	goto L78;
L98:; // incoming:1
	_342 = 58;
	_343 = (struct struct_3) {_342};
	_0 = _343;
	goto L78;
L99:; // incoming:1
	_340 = 57;
	_341 = (struct struct_3) {_340};
	_0 = _341;
	goto L78;
L100:; // incoming:1
	_338 = 56;
	_339 = (struct struct_3) {_338};
	_0 = _339;
	goto L78;
L101:; // incoming:1
	_336 = 55;
	_337 = (struct struct_3) {_336};
	_0 = _337;
	goto L78;
L102:; // incoming:1
	_334 = 54;
	_335 = (struct struct_3) {_334};
	_0 = _335;
	goto L78;
L103:; // incoming:1
	_332 = 53;
	_333 = (struct struct_3) {_332};
	_0 = _333;
	goto L78;
L104:; // incoming:1
	_330 = 52;
	_331 = (struct struct_3) {_330};
	_0 = _331;
	goto L78;
L105:; // incoming:1
	_328 = 51;
	_329 = (struct struct_3) {_328};
	_0 = _329;
	goto L78;
L106:; // incoming:1
	_326 = 50;
	_327 = (struct struct_3) {_326};
	_0 = _327;
	goto L78;
L107:; // incoming:1
	_324 = 49;
	_325 = (struct struct_3) {_324};
	_0 = _325;
	goto L78;
L108:; // incoming:1
	_322 = 48;
	_323 = (struct struct_3) {_322};
	_0 = _323;
	goto L78;
L109:; // incoming:1
	_320 = 47;
	_321 = (struct struct_3) {_320};
	_0 = _321;
	goto L78;
L110:; // incoming:1
	_318 = 46;
	_319 = (struct struct_3) {_318};
	_0 = _319;
	goto L78;
L111:; // incoming:1
	_316 = 45;
	_317 = (struct struct_3) {_316};
	_0 = _317;
	goto L78;
L112:; // incoming:1
	_314 = 44;
	_315 = (struct struct_3) {_314};
	_0 = _315;
	goto L78;
L113:; // incoming:1
	_312 = 43;
	_313 = (struct struct_3) {_312};
	_0 = _313;
	goto L78;
L114:; // incoming:1
	_310 = 42;
	_311 = (struct struct_3) {_310};
	_0 = _311;
	goto L78;
L115:; // incoming:1
	_308 = 41;
	_309 = (struct struct_3) {_308};
	_0 = _309;
	goto L78;
L116:; // incoming:1
	_306 = 40;
	_307 = (struct struct_3) {_306};
	_0 = _307;
	goto L78;
L117:; // incoming:1
	_304 = 39;
	_305 = (struct struct_3) {_304};
	_0 = _305;
	goto L78;
L118:; // incoming:1
	_302 = 38;
	_303 = (struct struct_3) {_302};
	_0 = _303;
	goto L78;
L119:; // incoming:1
	_300 = 37;
	_301 = (struct struct_3) {_300};
	_0 = _301;
	goto L78;
L120:; // incoming:1
	_298 = 36;
	_299 = (struct struct_3) {_298};
	_0 = _299;
	goto L78;
L121:; // incoming:1
	_296 = 35;
	_297 = (struct struct_3) {_296};
	_0 = _297;
	goto L78;
L122:; // incoming:1
	_294 = 34;
	_295 = (struct struct_3) {_294};
	_0 = _295;
	goto L78;
L123:; // incoming:1
	_292 = 33;
	_293 = (struct struct_3) {_292};
	_0 = _293;
	goto L78;
L124:; // incoming:1
	_290 = 32;
	_291 = (struct struct_3) {_290};
	_0 = _291;
	goto L78;
L125:; // incoming:1
	_288 = 31;
	_289 = (struct struct_3) {_288};
	_0 = _289;
	goto L78;
L126:; // incoming:1
	_286 = 30;
	_287 = (struct struct_3) {_286};
	_0 = _287;
	goto L78;
L127:; // incoming:1
	_284 = 29;
	_285 = (struct struct_3) {_284};
	_0 = _285;
	goto L78;
L128:; // incoming:1
	_282 = 28;
	_283 = (struct struct_3) {_282};
	_0 = _283;
	goto L78;
L129:; // incoming:1
	_280 = 27;
	_281 = (struct struct_3) {_280};
	_0 = _281;
	goto L78;
L130:; // incoming:1
	_278 = 26;
	_279 = (struct struct_3) {_278};
	_0 = _279;
	goto L78;
L131:; // incoming:1
	_276 = 25;
	_277 = (struct struct_3) {_276};
	_0 = _277;
	goto L78;
L132:; // incoming:1
	_274 = 24;
	_275 = (struct struct_3) {_274};
	_0 = _275;
	goto L78;
L133:; // incoming:1
	_272 = 23;
	_273 = (struct struct_3) {_272};
	_0 = _273;
	goto L78;
L134:; // incoming:1
	_270 = 22;
	_271 = (struct struct_3) {_270};
	_0 = _271;
	goto L78;
L135:; // incoming:1
	_268 = 21;
	_269 = (struct struct_3) {_268};
	_0 = _269;
	goto L78;
L136:; // incoming:1
	_266 = 20;
	_267 = (struct struct_3) {_266};
	_0 = _267;
	goto L78;
L137:; // incoming:1
	_264 = 19;
	_265 = (struct struct_3) {_264};
	_0 = _265;
	goto L78;
L138:; // incoming:1
	_262 = 18;
	_263 = (struct struct_3) {_262};
	_0 = _263;
	goto L78;
L139:; // incoming:1
	_260 = 17;
	_261 = (struct struct_3) {_260};
	_0 = _261;
	goto L78;
L140:; // incoming:1
	_258 = 16;
	_259 = (struct struct_3) {_258};
	_0 = _259;
	goto L78;
L141:; // incoming:1
	_256 = 15;
	_257 = (struct struct_3) {_256};
	_0 = _257;
	goto L78;
L142:; // incoming:1
	_254 = 14;
	_255 = (struct struct_3) {_254};
	_0 = _255;
	goto L78;
L143:; // incoming:1
	_252 = 13;
	_253 = (struct struct_3) {_252};
	_0 = _253;
	goto L78;
L144:; // incoming:1
	_250 = 12;
	_251 = (struct struct_3) {_250};
	_0 = _251;
	goto L78;
L145:; // incoming:1
	_248 = 11;
	_249 = (struct struct_3) {_248};
	_0 = _249;
	goto L78;
L146:; // incoming:1
	_246 = 10;
	_247 = (struct struct_3) {_246};
	_0 = _247;
	goto L78;
L147:; // incoming:1
	_244 = 9;
	_245 = (struct struct_3) {_244};
	_0 = _245;
	goto L78;
L148:; // incoming:1
	_242 = 8;
	_243 = (struct struct_3) {_242};
	_0 = _243;
	goto L78;
L149:; // incoming:1
	_240 = 7;
	_241 = (struct struct_3) {_240};
	_0 = _241;
	goto L78;
L150:; // incoming:1
	_238 = 6;
	_239 = (struct struct_3) {_238};
	_0 = _239;
	goto L78;
L151:; // incoming:1
	_236 = 5;
	_237 = (struct struct_3) {_236};
	_0 = _237;
	goto L78;
L152:; // incoming:1
	_234 = 4;
	_235 = (struct struct_3) {_234};
	_0 = _235;
	goto L78;
L153:; // incoming:1
	_232 = 3;
	_233 = (struct struct_3) {_232};
	_0 = _233;
	goto L78;
end:;
	return retval;
}

void pause() {system("pause");}

int main(int argc, char** argv)
{
	atexit(pause);
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
	return retval.tag != 80;
}
#endif
