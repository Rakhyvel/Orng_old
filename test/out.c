/* Code generated using the Orng compiler http://josephs-projects.com */

#ifndef ORNG_25489
#define ORNG_25489

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
#include <errno.h>

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
	case 134:
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
		return "blockDevicedRequired";
	case 17:
		return "deviceOrResourceBusy";
	case 18:
		return "fileExists";
	case 19:
		return "invalidCrossDeviceLink";
	case 20:
		return "noSuchDevice";
	case 21:
		return "notADirectory";
	case 22:
		return "isADirectory";
	case 23:
		return "invalidArgument";
	case 24:
		return "tooManyOpenFilesInSystem";
	case 25:
		return "tooManyOpenFiles";
	case 26:
		return "inappropriateIOCTLForDevice";
	case 27:
		return "textFileBusy";
	case 28:
		return "fileTooLarge";
	case 29:
		return "noSpaceLeftOnDevice";
	case 30:
		return "illegalSeek";
	case 31:
		return "readOnlyFileSystem";
	case 32:
		return "tooManyLinks";
	case 33:
		return "brokenPipe";
	case 34:
		return "numericalArgumentOutOfDomain";
	case 35:
		return "numericalArgumentOutOfRange";
	case 36:
		return "resourceDeadlockAvoided";
	case 37:
		return "fileNameTooLong";
	case 38:
		return "noLocksAvailable";
	case 39:
		return "functionNotImplemented";
	case 40:
		return "directoryNotEmpty";
	case 41:
		return "tooManyLevelsOfSymbolicLinks";
	case 42:
		return "noMessageOfDesiredType";
	case 43:
		return "identifierRemoved";
	case 44:
		return "channelNumberOutOfRange";
	case 45:
		return "level2NotSynchronized";
	case 46:
		return "level3Halted";
	case 47:
		return "level3Reset";
	case 48:
		return "linkNumberOutOfRange";
	case 49:
		return "protocolDriverNotAttatched";
	case 50:
		return "noCSIStructureAvailable";
	case 51:
		return "level2Halted";
	case 52:
		return "invalidExchange";
	case 53:
		return "invalidRequestDescriptor";
	case 54:
		return "exchangeFull";
	case 55:
		return "noAnode";
	case 56:
		return "invalidRequestCode";
	case 57:
		return "invalidSlot";
	case 58:
		return "badFontFileFormat";
	case 59:
		return "deviceNotAStream";
	case 60:
		return "noDataAvailable";
	case 61:
		return "timerExpired";
	case 62:
		return "outOfStreamsResources";
	case 63:
		return "machineIsNotOnTheNetwork";
	case 64:
		return "packageNotInstalled";
	case 65:
		return "objectIsRemote";
	case 66:
		return "linkHasBeenSevered";
	case 67:
		return "advertiseError";
	case 68:
		return "srmountError";
	case 69:
		return "communicationErrorOnSend";
	case 70:
		return "protocolError";
	case 71:
		return "multihopAttempted";
	case 72:
		return "rfsSpecificError";
	case 73:
		return "badMessage";
	case 74:
		return "valueTooLargeForDefinedDataType";
	case 75:
		return "nameNotUniqueOnNetwork";
	case 76:
		return "fileDescriptorInBadState";
	case 77:
		return "remoteAddressChanged";
	case 78:
		return "canNotAccessANeededSharedLibrary";
	case 79:
		return "accessingACorruptedSharedLibrary";
	case 80:
		return "libSectionCorrupted";
	case 81:
		return "attemptingToLinkInTooManySharedLibraries";
	case 82:
		return "cannotExecASharedLibraryDirectly";
	case 83:
		return "invalidOrIncompleteMultibyteOrWideCharacter";
	case 84:
		return "interruptedSystemCallShouldBeRestarted";
	case 85:
		return "streamsPipeError";
	case 86:
		return "tooManyUsers";
	case 87:
		return "socketOperationOnNonSocket";
	case 88:
		return "destinationAddressRequired";
	case 89:
		return "messageTooLong";
	case 90:
		return "protocolWrongTypeForSocket";
	case 91:
		return "protocolNotAvailable";
	case 92:
		return "protocolNotSupported";
	case 93:
		return "socketTypeNotSupported";
	case 94:
		return "operationNotSupported";
	case 95:
		return "protocolFamilyNotSupported";
	case 96:
		return "addressFamilyNotSupportedByProtocol";
	case 97:
		return "addressAlreadyInUse";
	case 98:
		return "cannotAssignRequestedAddress";
	case 99:
		return "networkIsDown";
	case 100:
		return "networkIsUnreachable";
	case 101:
		return "networkDroppedConnectionOnReset";
	case 102:
		return "softwareCausedConnectionAbort";
	case 103:
		return "connectionResetByPeer";
	case 104:
		return "noBufferSpaceAvailable";
	case 105:
		return "transportEndpointIsAlreadyConnected";
	case 106:
		return "transportEndpointIsNotConnected";
	case 107:
		return "cannotSendAfterTransportEndpointShutdown";
	case 108:
		return "tooManyReferencesCannotSplice";
	case 109:
		return "connectionTimedOut";
	case 110:
		return "connectionRefused";
	case 111:
		return "hostIsDown";
	case 112:
		return "noRouteToHost";
	case 113:
		return "operationAlreadyInProgress";
	case 114:
		return "operationNowInProgress";
	case 115:
		return "staleFileHandle";
	case 116:
		return "structureNeedsCleaning";
	case 117:
		return "notAXENIXNamedTypeFile";
	case 118:
		return "noXENIXSEmaphoresAvailable";
	case 119:
		return "isANamedTypeFile";
	case 120:
		return "remoteIOError";
	case 121:
		return "diskQuotaExceeded";
	case 122:
		return "noMediumFound";
	case 123:
		return "wrongMediumType";
	case 124:
		return "operationCancelled";
	case 125:
		return "requiredKeyNotAvailable";
	case 126:
		return "keyHasExpired";
	case 127:
		return "keyHasBeenRevoked";
	case 128:
		return "keyWasRejectedByService";
	case 129:
		return "ownerDied";
	case 130:
		return "stateNotRecoverable";
	case 131:
		return "operationNotPossibleDueToRFKill";
	case 132:
		return "memoryPageHasHardwareError";
	case 133:
	case 135:
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
struct struct_3 std_system_getError();

struct struct_3 test_testModule_main(struct struct_2 _args)
{
	struct struct_3 retval;
	struct struct_3 (*_0) ();
	struct struct_3 _1;
	int64_t _2;
	int64_t _4;
	int64_t _5;
	bool _3;
	struct struct_2 _args_0;
	int64_t (*_6) (struct struct_1 _format, ...);
	struct struct_1 _8;
	int64_t _7;
	int64_t _2;
	int64_t _15;
	struct struct_3 _16;
	int64_t (*_10) (struct struct_1 _format, ...);
	struct struct_1 _12;
	int64_t _11;
	int64_t _2;
	_args_0 = _args;
L264:; // incoming:1
	_0 = std_system_getError;
	if ((&stackTrace)->length >= 1000) {
		fprintf(stderr, "error: stack overflow\n");
		stackTracePrintReverse((&stackTrace));
		exit(1);
	}
	(&stackTrace)->data[(&stackTrace)->length++] = "test/testModule.orng: \n5     | std.system.getError()\n      |                    ^\n";
	_1 = _0();
	stackTrace.length--;
	_4 = someExtern;
	_5 = 4;
	_3 = _4 == _5;
	if (!_3) {
		goto L269;
	} else {
		goto L265;
	}
L265:; // incoming:1
	_6 = std_system_println;
	_8 = (struct struct_1) {4, "haha"};
	if ((&stackTrace)->length >= 1000) {
		fprintf(stderr, "error: stack overflow\n");
		stackTracePrintReverse((&stackTrace));
		exit(1);
	}
	(&stackTrace)->data[(&stackTrace)->length++] = "test/testModule.orng: \n7     | std.system.println(\"haha\")\n      |                   ^\n";
	_7 = _6(_8);
	stackTrace.length--;
	_2 = _7;
	goto L268;
L268:; // incoming:2
	_15 = 135;
	_16 = (struct struct_3) {_15};
	retval = _16;
	goto end;
L269:; // incoming:1
	_10 = std_system_println;
	_12 = (struct struct_1) {4, "hahe"};
	if ((&stackTrace)->length >= 1000) {
		fprintf(stderr, "error: stack overflow\n");
		stackTracePrintReverse((&stackTrace));
		exit(1);
	}
	(&stackTrace)->data[(&stackTrace)->length++] = "test/testModule.orng: \n9     | std.system.println(\"hahe\")\n      |                   ^\n";
	_11 = _10(_12);
	stackTrace.length--;
	_2 = _11;
	goto L268;
end:;
	return retval;
}

struct struct_3 std_system_getError()
{
	struct struct_3 retval;
	struct struct_3 _0;
	int64_t _1;
	int64_t _3;
	bool _2;
	int64_t _4;
	int64_t _6;
	bool _5;
	int64_t _7;
	int64_t _9;
	bool _8;
	int64_t _10;
	int64_t _12;
	bool _11;
	int64_t _13;
	int64_t _15;
	bool _14;
	int64_t _16;
	int64_t _18;
	bool _17;
	int64_t _19;
	int64_t _21;
	bool _20;
	int64_t _22;
	int64_t _24;
	bool _23;
	int64_t _25;
	int64_t _27;
	bool _26;
	int64_t _28;
	int64_t _30;
	bool _29;
	int64_t _31;
	int64_t _33;
	bool _32;
	int64_t _34;
	int64_t _36;
	bool _35;
	int64_t _37;
	int64_t _39;
	bool _38;
	int64_t _40;
	int64_t _42;
	bool _41;
	int64_t _43;
	int64_t _45;
	bool _44;
	int64_t _46;
	int64_t _48;
	bool _47;
	int64_t _49;
	int64_t _51;
	bool _50;
	int64_t _52;
	int64_t _54;
	bool _53;
	int64_t _55;
	int64_t _57;
	bool _56;
	int64_t _58;
	int64_t _60;
	bool _59;
	int64_t _61;
	int64_t _63;
	bool _62;
	int64_t _64;
	int64_t _66;
	bool _65;
	int64_t _67;
	int64_t _69;
	bool _68;
	int64_t _70;
	int64_t _72;
	bool _71;
	int64_t _73;
	int64_t _75;
	bool _74;
	int64_t _76;
	int64_t _78;
	bool _77;
	int64_t _79;
	int64_t _81;
	bool _80;
	int64_t _82;
	int64_t _84;
	bool _83;
	int64_t _85;
	int64_t _87;
	bool _86;
	int64_t _88;
	int64_t _90;
	bool _89;
	int64_t _91;
	int64_t _93;
	bool _92;
	int64_t _94;
	int64_t _96;
	bool _95;
	int64_t _97;
	int64_t _99;
	bool _98;
	int64_t _100;
	int64_t _102;
	bool _101;
	int64_t _103;
	int64_t _105;
	bool _104;
	int64_t _106;
	int64_t _108;
	bool _107;
	int64_t _109;
	int64_t _111;
	bool _110;
	int64_t _112;
	int64_t _114;
	bool _113;
	int64_t _115;
	int64_t _117;
	bool _116;
	int64_t _118;
	int64_t _120;
	bool _119;
	int64_t _121;
	int64_t _123;
	bool _122;
	int64_t _124;
	int64_t _126;
	bool _125;
	int64_t _127;
	int64_t _129;
	bool _128;
	int64_t _130;
	int64_t _132;
	bool _131;
	int64_t _133;
	int64_t _135;
	bool _134;
	int64_t _136;
	int64_t _138;
	bool _137;
	int64_t _139;
	int64_t _141;
	bool _140;
	int64_t _142;
	int64_t _144;
	bool _143;
	int64_t _145;
	int64_t _147;
	bool _146;
	int64_t _148;
	int64_t _150;
	bool _149;
	int64_t _151;
	int64_t _153;
	bool _152;
	int64_t _154;
	int64_t _156;
	bool _155;
	int64_t _157;
	int64_t _159;
	bool _158;
	int64_t _160;
	int64_t _162;
	bool _161;
	int64_t _163;
	int64_t _165;
	bool _164;
	int64_t _166;
	int64_t _168;
	bool _167;
	int64_t _169;
	int64_t _171;
	bool _170;
	int64_t _172;
	int64_t _174;
	bool _173;
	int64_t _175;
	int64_t _177;
	bool _176;
	int64_t _178;
	int64_t _180;
	bool _179;
	int64_t _181;
	int64_t _183;
	bool _182;
	int64_t _184;
	int64_t _186;
	bool _185;
	int64_t _187;
	int64_t _189;
	bool _188;
	int64_t _190;
	int64_t _192;
	bool _191;
	int64_t _193;
	int64_t _195;
	bool _194;
	int64_t _196;
	int64_t _198;
	bool _197;
	int64_t _199;
	int64_t _201;
	bool _200;
	int64_t _202;
	int64_t _204;
	bool _203;
	int64_t _205;
	int64_t _207;
	bool _206;
	int64_t _208;
	int64_t _210;
	bool _209;
	int64_t _211;
	int64_t _213;
	bool _212;
	int64_t _214;
	int64_t _216;
	bool _215;
	int64_t _217;
	int64_t _219;
	bool _218;
	int64_t _220;
	int64_t _222;
	bool _221;
	int64_t _223;
	int64_t _225;
	bool _224;
	int64_t _226;
	int64_t _228;
	bool _227;
	int64_t _229;
	int64_t _231;
	bool _230;
	int64_t _232;
	int64_t _234;
	bool _233;
	int64_t _235;
	int64_t _237;
	bool _236;
	int64_t _238;
	int64_t _240;
	bool _239;
	int64_t _241;
	int64_t _243;
	bool _242;
	int64_t _244;
	int64_t _246;
	bool _245;
	int64_t _247;
	int64_t _249;
	bool _248;
	int64_t _250;
	int64_t _252;
	bool _251;
	int64_t _253;
	int64_t _255;
	bool _254;
	int64_t _256;
	int64_t _258;
	bool _257;
	int64_t _259;
	int64_t _261;
	bool _260;
	int64_t _262;
	int64_t _264;
	bool _263;
	int64_t _265;
	int64_t _267;
	bool _266;
	int64_t _268;
	int64_t _270;
	bool _269;
	int64_t _271;
	int64_t _273;
	bool _272;
	int64_t _274;
	int64_t _276;
	bool _275;
	int64_t _277;
	int64_t _279;
	bool _278;
	int64_t _280;
	int64_t _282;
	bool _281;
	int64_t _283;
	int64_t _285;
	bool _284;
	int64_t _286;
	int64_t _288;
	bool _287;
	int64_t _289;
	int64_t _291;
	bool _290;
	int64_t _292;
	int64_t _294;
	bool _293;
	int64_t _295;
	int64_t _297;
	bool _296;
	int64_t _298;
	int64_t _300;
	bool _299;
	int64_t _301;
	int64_t _303;
	bool _302;
	int64_t _304;
	int64_t _306;
	bool _305;
	int64_t _307;
	int64_t _309;
	bool _308;
	int64_t _310;
	int64_t _312;
	bool _311;
	int64_t _313;
	int64_t _315;
	bool _314;
	int64_t _316;
	int64_t _318;
	bool _317;
	int64_t _319;
	int64_t _321;
	bool _320;
	int64_t _322;
	int64_t _324;
	bool _323;
	int64_t _325;
	int64_t _327;
	bool _326;
	int64_t _328;
	int64_t _330;
	bool _329;
	int64_t _331;
	int64_t _333;
	bool _332;
	int64_t _334;
	int64_t _336;
	bool _335;
	int64_t _337;
	int64_t _339;
	bool _338;
	int64_t _340;
	int64_t _342;
	bool _341;
	int64_t _343;
	int64_t _345;
	bool _344;
	int64_t _346;
	int64_t _348;
	bool _347;
	int64_t _349;
	int64_t _351;
	bool _350;
	int64_t _352;
	int64_t _354;
	bool _353;
	int64_t _355;
	int64_t _357;
	bool _356;
	int64_t _358;
	int64_t _360;
	bool _359;
	int64_t _361;
	int64_t _363;
	bool _362;
	int64_t _364;
	int64_t _366;
	bool _365;
	int64_t _367;
	int64_t _369;
	bool _368;
	int64_t _370;
	int64_t _372;
	bool _371;
	int64_t _373;
	int64_t _375;
	bool _374;
	int64_t _376;
	int64_t _378;
	bool _377;
	int64_t _379;
	int64_t _381;
	bool _380;
	int64_t _382;
	int64_t _384;
	bool _383;
	int64_t _385;
	int64_t _387;
	bool _386;
	int64_t _388;
	int64_t _390;
	bool _389;
	int64_t _391;
	int64_t _393;
	bool _392;
	int64_t _394;
	struct struct_3 _395;
	struct struct_3 _0;
	int64_t _654;
	struct struct_3 _655;
	struct struct_3 _0;
	int64_t _652;
	struct struct_3 _653;
	struct struct_3 _0;
	int64_t _650;
	struct struct_3 _651;
	struct struct_3 _0;
	int64_t _648;
	struct struct_3 _649;
	struct struct_3 _0;
	int64_t _646;
	struct struct_3 _647;
	struct struct_3 _0;
	int64_t _644;
	struct struct_3 _645;
	struct struct_3 _0;
	int64_t _642;
	struct struct_3 _643;
	struct struct_3 _0;
	int64_t _640;
	struct struct_3 _641;
	struct struct_3 _0;
	int64_t _638;
	struct struct_3 _639;
	struct struct_3 _0;
	int64_t _636;
	struct struct_3 _637;
	struct struct_3 _0;
	int64_t _634;
	struct struct_3 _635;
	struct struct_3 _0;
	int64_t _632;
	struct struct_3 _633;
	struct struct_3 _0;
	int64_t _630;
	struct struct_3 _631;
	struct struct_3 _0;
	int64_t _628;
	struct struct_3 _629;
	struct struct_3 _0;
	int64_t _626;
	struct struct_3 _627;
	struct struct_3 _0;
	int64_t _624;
	struct struct_3 _625;
	struct struct_3 _0;
	int64_t _622;
	struct struct_3 _623;
	struct struct_3 _0;
	int64_t _620;
	struct struct_3 _621;
	struct struct_3 _0;
	int64_t _618;
	struct struct_3 _619;
	struct struct_3 _0;
	int64_t _616;
	struct struct_3 _617;
	struct struct_3 _0;
	int64_t _614;
	struct struct_3 _615;
	struct struct_3 _0;
	int64_t _612;
	struct struct_3 _613;
	struct struct_3 _0;
	int64_t _610;
	struct struct_3 _611;
	struct struct_3 _0;
	int64_t _608;
	struct struct_3 _609;
	struct struct_3 _0;
	int64_t _606;
	struct struct_3 _607;
	struct struct_3 _0;
	int64_t _604;
	struct struct_3 _605;
	struct struct_3 _0;
	int64_t _602;
	struct struct_3 _603;
	struct struct_3 _0;
	int64_t _600;
	struct struct_3 _601;
	struct struct_3 _0;
	int64_t _598;
	struct struct_3 _599;
	struct struct_3 _0;
	int64_t _596;
	struct struct_3 _597;
	struct struct_3 _0;
	int64_t _594;
	struct struct_3 _595;
	struct struct_3 _0;
	int64_t _592;
	struct struct_3 _593;
	struct struct_3 _0;
	int64_t _590;
	struct struct_3 _591;
	struct struct_3 _0;
	int64_t _588;
	struct struct_3 _589;
	struct struct_3 _0;
	int64_t _586;
	struct struct_3 _587;
	struct struct_3 _0;
	int64_t _584;
	struct struct_3 _585;
	struct struct_3 _0;
	int64_t _582;
	struct struct_3 _583;
	struct struct_3 _0;
	int64_t _580;
	struct struct_3 _581;
	struct struct_3 _0;
	int64_t _578;
	struct struct_3 _579;
	struct struct_3 _0;
	int64_t _576;
	struct struct_3 _577;
	struct struct_3 _0;
	int64_t _574;
	struct struct_3 _575;
	struct struct_3 _0;
	int64_t _572;
	struct struct_3 _573;
	struct struct_3 _0;
	int64_t _570;
	struct struct_3 _571;
	struct struct_3 _0;
	int64_t _568;
	struct struct_3 _569;
	struct struct_3 _0;
	int64_t _566;
	struct struct_3 _567;
	struct struct_3 _0;
	int64_t _564;
	struct struct_3 _565;
	struct struct_3 _0;
	int64_t _562;
	struct struct_3 _563;
	struct struct_3 _0;
	int64_t _560;
	struct struct_3 _561;
	struct struct_3 _0;
	int64_t _558;
	struct struct_3 _559;
	struct struct_3 _0;
	int64_t _556;
	struct struct_3 _557;
	struct struct_3 _0;
	int64_t _554;
	struct struct_3 _555;
	struct struct_3 _0;
	int64_t _552;
	struct struct_3 _553;
	struct struct_3 _0;
	int64_t _550;
	struct struct_3 _551;
	struct struct_3 _0;
	int64_t _548;
	struct struct_3 _549;
	struct struct_3 _0;
	int64_t _546;
	struct struct_3 _547;
	struct struct_3 _0;
	int64_t _544;
	struct struct_3 _545;
	struct struct_3 _0;
	int64_t _542;
	struct struct_3 _543;
	struct struct_3 _0;
	int64_t _540;
	struct struct_3 _541;
	struct struct_3 _0;
	int64_t _538;
	struct struct_3 _539;
	struct struct_3 _0;
	int64_t _536;
	struct struct_3 _537;
	struct struct_3 _0;
	int64_t _534;
	struct struct_3 _535;
	struct struct_3 _0;
	int64_t _532;
	struct struct_3 _533;
	struct struct_3 _0;
	int64_t _530;
	struct struct_3 _531;
	struct struct_3 _0;
	int64_t _528;
	struct struct_3 _529;
	struct struct_3 _0;
	int64_t _526;
	struct struct_3 _527;
	struct struct_3 _0;
	int64_t _524;
	struct struct_3 _525;
	struct struct_3 _0;
	int64_t _522;
	struct struct_3 _523;
	struct struct_3 _0;
	int64_t _520;
	struct struct_3 _521;
	struct struct_3 _0;
	int64_t _518;
	struct struct_3 _519;
	struct struct_3 _0;
	int64_t _516;
	struct struct_3 _517;
	struct struct_3 _0;
	int64_t _514;
	struct struct_3 _515;
	struct struct_3 _0;
	int64_t _512;
	struct struct_3 _513;
	struct struct_3 _0;
	int64_t _510;
	struct struct_3 _511;
	struct struct_3 _0;
	int64_t _508;
	struct struct_3 _509;
	struct struct_3 _0;
	int64_t _506;
	struct struct_3 _507;
	struct struct_3 _0;
	int64_t _504;
	struct struct_3 _505;
	struct struct_3 _0;
	int64_t _502;
	struct struct_3 _503;
	struct struct_3 _0;
	int64_t _500;
	struct struct_3 _501;
	struct struct_3 _0;
	int64_t _498;
	struct struct_3 _499;
	struct struct_3 _0;
	int64_t _496;
	struct struct_3 _497;
	struct struct_3 _0;
	int64_t _494;
	struct struct_3 _495;
	struct struct_3 _0;
	int64_t _492;
	struct struct_3 _493;
	struct struct_3 _0;
	int64_t _490;
	struct struct_3 _491;
	struct struct_3 _0;
	int64_t _488;
	struct struct_3 _489;
	struct struct_3 _0;
	int64_t _486;
	struct struct_3 _487;
	struct struct_3 _0;
	int64_t _484;
	struct struct_3 _485;
	struct struct_3 _0;
	int64_t _482;
	struct struct_3 _483;
	struct struct_3 _0;
	int64_t _480;
	struct struct_3 _481;
	struct struct_3 _0;
	int64_t _478;
	struct struct_3 _479;
	struct struct_3 _0;
	int64_t _476;
	struct struct_3 _477;
	struct struct_3 _0;
	int64_t _474;
	struct struct_3 _475;
	struct struct_3 _0;
	int64_t _472;
	struct struct_3 _473;
	struct struct_3 _0;
	int64_t _470;
	struct struct_3 _471;
	struct struct_3 _0;
	int64_t _468;
	struct struct_3 _469;
	struct struct_3 _0;
	int64_t _466;
	struct struct_3 _467;
	struct struct_3 _0;
	int64_t _464;
	struct struct_3 _465;
	struct struct_3 _0;
	int64_t _462;
	struct struct_3 _463;
	struct struct_3 _0;
	int64_t _460;
	struct struct_3 _461;
	struct struct_3 _0;
	int64_t _458;
	struct struct_3 _459;
	struct struct_3 _0;
	int64_t _456;
	struct struct_3 _457;
	struct struct_3 _0;
	int64_t _454;
	struct struct_3 _455;
	struct struct_3 _0;
	int64_t _452;
	struct struct_3 _453;
	struct struct_3 _0;
	int64_t _450;
	struct struct_3 _451;
	struct struct_3 _0;
	int64_t _448;
	struct struct_3 _449;
	struct struct_3 _0;
	int64_t _446;
	struct struct_3 _447;
	struct struct_3 _0;
	int64_t _444;
	struct struct_3 _445;
	struct struct_3 _0;
	int64_t _442;
	struct struct_3 _443;
	struct struct_3 _0;
	int64_t _440;
	struct struct_3 _441;
	struct struct_3 _0;
	int64_t _438;
	struct struct_3 _439;
	struct struct_3 _0;
	int64_t _436;
	struct struct_3 _437;
	struct struct_3 _0;
	int64_t _434;
	struct struct_3 _435;
	struct struct_3 _0;
	int64_t _432;
	struct struct_3 _433;
	struct struct_3 _0;
	int64_t _430;
	struct struct_3 _431;
	struct struct_3 _0;
	int64_t _428;
	struct struct_3 _429;
	struct struct_3 _0;
	int64_t _426;
	struct struct_3 _427;
	struct struct_3 _0;
	int64_t _424;
	struct struct_3 _425;
	struct struct_3 _0;
	int64_t _422;
	struct struct_3 _423;
	struct struct_3 _0;
	int64_t _420;
	struct struct_3 _421;
	struct struct_3 _0;
	int64_t _418;
	struct struct_3 _419;
	struct struct_3 _0;
	int64_t _416;
	struct struct_3 _417;
	struct struct_3 _0;
	int64_t _414;
	struct struct_3 _415;
	struct struct_3 _0;
	int64_t _412;
	struct struct_3 _413;
	struct struct_3 _0;
	int64_t _410;
	struct struct_3 _411;
	struct struct_3 _0;
	int64_t _408;
	struct struct_3 _409;
	struct struct_3 _0;
	int64_t _406;
	struct struct_3 _407;
	struct struct_3 _0;
	int64_t _404;
	struct struct_3 _405;
	struct struct_3 _0;
	int64_t _402;
	struct struct_3 _403;
	struct struct_3 _0;
	int64_t _400;
	struct struct_3 _401;
	struct struct_3 _0;
	int64_t _398;
	struct struct_3 _399;
	struct struct_3 _0;
	int64_t _396;
	struct struct_3 _397;
	struct struct_3 _0;
L0:; // incoming:1
	_1 = EPERM;
	_3 = errno;
	_2 = _3 != _1;
	if (!_2) {
		goto L132;
	} else {
		goto L1;
	}
L1:; // incoming:1
	_4 = ENOENT;
	_6 = errno;
	_5 = _6 != _4;
	if (!_5) {
		goto L263;
	} else {
		goto L2;
	}
L2:; // incoming:1
	_7 = ESRCH;
	_9 = errno;
	_8 = _9 != _7;
	if (!_8) {
		goto L262;
	} else {
		goto L3;
	}
L3:; // incoming:1
	_10 = EINTR;
	_12 = errno;
	_11 = _12 != _10;
	if (!_11) {
		goto L261;
	} else {
		goto L4;
	}
L4:; // incoming:1
	_13 = EIO;
	_15 = errno;
	_14 = _15 != _13;
	if (!_14) {
		goto L260;
	} else {
		goto L5;
	}
L5:; // incoming:1
	_16 = ENXIO;
	_18 = errno;
	_17 = _18 != _16;
	if (!_17) {
		goto L259;
	} else {
		goto L6;
	}
L6:; // incoming:1
	_19 = E2BIG;
	_21 = errno;
	_20 = _21 != _19;
	if (!_20) {
		goto L258;
	} else {
		goto L7;
	}
L7:; // incoming:1
	_22 = ENOEXEC;
	_24 = errno;
	_23 = _24 != _22;
	if (!_23) {
		goto L257;
	} else {
		goto L8;
	}
L8:; // incoming:1
	_25 = EBADF;
	_27 = errno;
	_26 = _27 != _25;
	if (!_26) {
		goto L256;
	} else {
		goto L9;
	}
L9:; // incoming:1
	_28 = ECHILD;
	_30 = errno;
	_29 = _30 != _28;
	if (!_29) {
		goto L255;
	} else {
		goto L10;
	}
L10:; // incoming:1
	_31 = EAGAIN;
	_33 = errno;
	_32 = _33 != _31;
	if (!_32) {
		goto L254;
	} else {
		goto L11;
	}
L11:; // incoming:1
	_34 = ENOMEM;
	_36 = errno;
	_35 = _36 != _34;
	if (!_35) {
		goto L253;
	} else {
		goto L12;
	}
L12:; // incoming:1
	_37 = EACCES;
	_39 = errno;
	_38 = _39 != _37;
	if (!_38) {
		goto L252;
	} else {
		goto L13;
	}
L13:; // incoming:1
	_40 = EFAULT;
	_42 = errno;
	_41 = _42 != _40;
	if (!_41) {
		goto L251;
	} else {
		goto L14;
	}
L14:; // incoming:1
	_43 = ENOTBLK;
	_45 = errno;
	_44 = _45 != _43;
	if (!_44) {
		goto L250;
	} else {
		goto L15;
	}
L15:; // incoming:1
	_46 = EBUSY;
	_48 = errno;
	_47 = _48 != _46;
	if (!_47) {
		goto L249;
	} else {
		goto L16;
	}
L16:; // incoming:1
	_49 = EEXIST;
	_51 = errno;
	_50 = _51 != _49;
	if (!_50) {
		goto L248;
	} else {
		goto L17;
	}
L17:; // incoming:1
	_52 = EXDEV;
	_54 = errno;
	_53 = _54 != _52;
	if (!_53) {
		goto L247;
	} else {
		goto L18;
	}
L18:; // incoming:1
	_55 = ENODEV;
	_57 = errno;
	_56 = _57 != _55;
	if (!_56) {
		goto L246;
	} else {
		goto L19;
	}
L19:; // incoming:1
	_58 = ENOTDIR;
	_60 = errno;
	_59 = _60 != _58;
	if (!_59) {
		goto L245;
	} else {
		goto L20;
	}
L20:; // incoming:1
	_61 = EISDIR;
	_63 = errno;
	_62 = _63 != _61;
	if (!_62) {
		goto L244;
	} else {
		goto L21;
	}
L21:; // incoming:1
	_64 = EINVAL;
	_66 = errno;
	_65 = _66 != _64;
	if (!_65) {
		goto L243;
	} else {
		goto L22;
	}
L22:; // incoming:1
	_67 = ENFILE;
	_69 = errno;
	_68 = _69 != _67;
	if (!_68) {
		goto L242;
	} else {
		goto L23;
	}
L23:; // incoming:1
	_70 = EMFILE;
	_72 = errno;
	_71 = _72 != _70;
	if (!_71) {
		goto L241;
	} else {
		goto L24;
	}
L24:; // incoming:1
	_73 = ENOTTY;
	_75 = errno;
	_74 = _75 != _73;
	if (!_74) {
		goto L240;
	} else {
		goto L25;
	}
L25:; // incoming:1
	_76 = ETXTBSY;
	_78 = errno;
	_77 = _78 != _76;
	if (!_77) {
		goto L239;
	} else {
		goto L26;
	}
L26:; // incoming:1
	_79 = EFBIG;
	_81 = errno;
	_80 = _81 != _79;
	if (!_80) {
		goto L238;
	} else {
		goto L27;
	}
L27:; // incoming:1
	_82 = ENOSPC;
	_84 = errno;
	_83 = _84 != _82;
	if (!_83) {
		goto L237;
	} else {
		goto L28;
	}
L28:; // incoming:1
	_85 = ESPIPE;
	_87 = errno;
	_86 = _87 != _85;
	if (!_86) {
		goto L236;
	} else {
		goto L29;
	}
L29:; // incoming:1
	_88 = EROFS;
	_90 = errno;
	_89 = _90 != _88;
	if (!_89) {
		goto L235;
	} else {
		goto L30;
	}
L30:; // incoming:1
	_91 = EMLINK;
	_93 = errno;
	_92 = _93 != _91;
	if (!_92) {
		goto L234;
	} else {
		goto L31;
	}
L31:; // incoming:1
	_94 = EPIPE;
	_96 = errno;
	_95 = _96 != _94;
	if (!_95) {
		goto L233;
	} else {
		goto L32;
	}
L32:; // incoming:1
	_97 = EDOM;
	_99 = errno;
	_98 = _99 != _97;
	if (!_98) {
		goto L232;
	} else {
		goto L33;
	}
L33:; // incoming:1
	_100 = ERANGE;
	_102 = errno;
	_101 = _102 != _100;
	if (!_101) {
		goto L231;
	} else {
		goto L34;
	}
L34:; // incoming:1
	_103 = EDEADLK;
	_105 = errno;
	_104 = _105 != _103;
	if (!_104) {
		goto L230;
	} else {
		goto L35;
	}
L35:; // incoming:1
	_106 = ENAMETOOLONG;
	_108 = errno;
	_107 = _108 != _106;
	if (!_107) {
		goto L229;
	} else {
		goto L36;
	}
L36:; // incoming:1
	_109 = ENOLCK;
	_111 = errno;
	_110 = _111 != _109;
	if (!_110) {
		goto L228;
	} else {
		goto L37;
	}
L37:; // incoming:1
	_112 = ENOSYS;
	_114 = errno;
	_113 = _114 != _112;
	if (!_113) {
		goto L227;
	} else {
		goto L38;
	}
L38:; // incoming:1
	_115 = ENOTEMPTY;
	_117 = errno;
	_116 = _117 != _115;
	if (!_116) {
		goto L226;
	} else {
		goto L39;
	}
L39:; // incoming:1
	_118 = ELOOP;
	_120 = errno;
	_119 = _120 != _118;
	if (!_119) {
		goto L225;
	} else {
		goto L40;
	}
L40:; // incoming:1
	_121 = ENOMSG;
	_123 = errno;
	_122 = _123 != _121;
	if (!_122) {
		goto L224;
	} else {
		goto L41;
	}
L41:; // incoming:1
	_124 = EIDRM;
	_126 = errno;
	_125 = _126 != _124;
	if (!_125) {
		goto L223;
	} else {
		goto L42;
	}
L42:; // incoming:1
	_127 = ECHRNG;
	_129 = errno;
	_128 = _129 != _127;
	if (!_128) {
		goto L222;
	} else {
		goto L43;
	}
L43:; // incoming:1
	_130 = EL2NSYNC;
	_132 = errno;
	_131 = _132 != _130;
	if (!_131) {
		goto L221;
	} else {
		goto L44;
	}
L44:; // incoming:1
	_133 = EL3HLT;
	_135 = errno;
	_134 = _135 != _133;
	if (!_134) {
		goto L220;
	} else {
		goto L45;
	}
L45:; // incoming:1
	_136 = EL3RST;
	_138 = errno;
	_137 = _138 != _136;
	if (!_137) {
		goto L219;
	} else {
		goto L46;
	}
L46:; // incoming:1
	_139 = ELNRNG;
	_141 = errno;
	_140 = _141 != _139;
	if (!_140) {
		goto L218;
	} else {
		goto L47;
	}
L47:; // incoming:1
	_142 = EUNATCH;
	_144 = errno;
	_143 = _144 != _142;
	if (!_143) {
		goto L217;
	} else {
		goto L48;
	}
L48:; // incoming:1
	_145 = ENOCSI;
	_147 = errno;
	_146 = _147 != _145;
	if (!_146) {
		goto L216;
	} else {
		goto L49;
	}
L49:; // incoming:1
	_148 = EL2HLT;
	_150 = errno;
	_149 = _150 != _148;
	if (!_149) {
		goto L215;
	} else {
		goto L50;
	}
L50:; // incoming:1
	_151 = EBADE;
	_153 = errno;
	_152 = _153 != _151;
	if (!_152) {
		goto L214;
	} else {
		goto L51;
	}
L51:; // incoming:1
	_154 = EBADR;
	_156 = errno;
	_155 = _156 != _154;
	if (!_155) {
		goto L213;
	} else {
		goto L52;
	}
L52:; // incoming:1
	_157 = EXFULL;
	_159 = errno;
	_158 = _159 != _157;
	if (!_158) {
		goto L212;
	} else {
		goto L53;
	}
L53:; // incoming:1
	_160 = ENOANO;
	_162 = errno;
	_161 = _162 != _160;
	if (!_161) {
		goto L211;
	} else {
		goto L54;
	}
L54:; // incoming:1
	_163 = EBADRQC;
	_165 = errno;
	_164 = _165 != _163;
	if (!_164) {
		goto L210;
	} else {
		goto L55;
	}
L55:; // incoming:1
	_166 = EBADSLT;
	_168 = errno;
	_167 = _168 != _166;
	if (!_167) {
		goto L209;
	} else {
		goto L56;
	}
L56:; // incoming:1
	_169 = EBFONT;
	_171 = errno;
	_170 = _171 != _169;
	if (!_170) {
		goto L208;
	} else {
		goto L57;
	}
L57:; // incoming:1
	_172 = ENOSTR;
	_174 = errno;
	_173 = _174 != _172;
	if (!_173) {
		goto L207;
	} else {
		goto L58;
	}
L58:; // incoming:1
	_175 = ENODATA;
	_177 = errno;
	_176 = _177 != _175;
	if (!_176) {
		goto L206;
	} else {
		goto L59;
	}
L59:; // incoming:1
	_178 = ETIME;
	_180 = errno;
	_179 = _180 != _178;
	if (!_179) {
		goto L205;
	} else {
		goto L60;
	}
L60:; // incoming:1
	_181 = ENOSR;
	_183 = errno;
	_182 = _183 != _181;
	if (!_182) {
		goto L204;
	} else {
		goto L61;
	}
L61:; // incoming:1
	_184 = ENONET;
	_186 = errno;
	_185 = _186 != _184;
	if (!_185) {
		goto L203;
	} else {
		goto L62;
	}
L62:; // incoming:1
	_187 = ENOPKG;
	_189 = errno;
	_188 = _189 != _187;
	if (!_188) {
		goto L202;
	} else {
		goto L63;
	}
L63:; // incoming:1
	_190 = EREMOTE;
	_192 = errno;
	_191 = _192 != _190;
	if (!_191) {
		goto L201;
	} else {
		goto L64;
	}
L64:; // incoming:1
	_193 = ENOLINK;
	_195 = errno;
	_194 = _195 != _193;
	if (!_194) {
		goto L200;
	} else {
		goto L65;
	}
L65:; // incoming:1
	_196 = EADV;
	_198 = errno;
	_197 = _198 != _196;
	if (!_197) {
		goto L199;
	} else {
		goto L66;
	}
L66:; // incoming:1
	_199 = ESRMNT;
	_201 = errno;
	_200 = _201 != _199;
	if (!_200) {
		goto L198;
	} else {
		goto L67;
	}
L67:; // incoming:1
	_202 = ECOMM;
	_204 = errno;
	_203 = _204 != _202;
	if (!_203) {
		goto L197;
	} else {
		goto L68;
	}
L68:; // incoming:1
	_205 = EPROTO;
	_207 = errno;
	_206 = _207 != _205;
	if (!_206) {
		goto L196;
	} else {
		goto L69;
	}
L69:; // incoming:1
	_208 = EMULTIHOP;
	_210 = errno;
	_209 = _210 != _208;
	if (!_209) {
		goto L195;
	} else {
		goto L70;
	}
L70:; // incoming:1
	_211 = EDOTDOT;
	_213 = errno;
	_212 = _213 != _211;
	if (!_212) {
		goto L194;
	} else {
		goto L71;
	}
L71:; // incoming:1
	_214 = EBADMSG;
	_216 = errno;
	_215 = _216 != _214;
	if (!_215) {
		goto L193;
	} else {
		goto L72;
	}
L72:; // incoming:1
	_217 = EOVERFLOW;
	_219 = errno;
	_218 = _219 != _217;
	if (!_218) {
		goto L192;
	} else {
		goto L73;
	}
L73:; // incoming:1
	_220 = ENOTUNIQ;
	_222 = errno;
	_221 = _222 != _220;
	if (!_221) {
		goto L191;
	} else {
		goto L74;
	}
L74:; // incoming:1
	_223 = EBADFD;
	_225 = errno;
	_224 = _225 != _223;
	if (!_224) {
		goto L190;
	} else {
		goto L75;
	}
L75:; // incoming:1
	_226 = EREMCHG;
	_228 = errno;
	_227 = _228 != _226;
	if (!_227) {
		goto L189;
	} else {
		goto L76;
	}
L76:; // incoming:1
	_229 = ELIBACC;
	_231 = errno;
	_230 = _231 != _229;
	if (!_230) {
		goto L188;
	} else {
		goto L77;
	}
L77:; // incoming:1
	_232 = ELIBBAD;
	_234 = errno;
	_233 = _234 != _232;
	if (!_233) {
		goto L187;
	} else {
		goto L78;
	}
L78:; // incoming:1
	_235 = ELIBSCN;
	_237 = errno;
	_236 = _237 != _235;
	if (!_236) {
		goto L186;
	} else {
		goto L79;
	}
L79:; // incoming:1
	_238 = ELIBMAX;
	_240 = errno;
	_239 = _240 != _238;
	if (!_239) {
		goto L185;
	} else {
		goto L80;
	}
L80:; // incoming:1
	_241 = ELIBEXEC;
	_243 = errno;
	_242 = _243 != _241;
	if (!_242) {
		goto L184;
	} else {
		goto L81;
	}
L81:; // incoming:1
	_244 = EILSEQ;
	_246 = errno;
	_245 = _246 != _244;
	if (!_245) {
		goto L183;
	} else {
		goto L82;
	}
L82:; // incoming:1
	_247 = ERESTART;
	_249 = errno;
	_248 = _249 != _247;
	if (!_248) {
		goto L182;
	} else {
		goto L83;
	}
L83:; // incoming:1
	_250 = ESTRPIPE;
	_252 = errno;
	_251 = _252 != _250;
	if (!_251) {
		goto L181;
	} else {
		goto L84;
	}
L84:; // incoming:1
	_253 = EUSERS;
	_255 = errno;
	_254 = _255 != _253;
	if (!_254) {
		goto L180;
	} else {
		goto L85;
	}
L85:; // incoming:1
	_256 = ENOTSOCK;
	_258 = errno;
	_257 = _258 != _256;
	if (!_257) {
		goto L179;
	} else {
		goto L86;
	}
L86:; // incoming:1
	_259 = EDESTADDRREQ;
	_261 = errno;
	_260 = _261 != _259;
	if (!_260) {
		goto L178;
	} else {
		goto L87;
	}
L87:; // incoming:1
	_262 = EMSGSIZE;
	_264 = errno;
	_263 = _264 != _262;
	if (!_263) {
		goto L177;
	} else {
		goto L88;
	}
L88:; // incoming:1
	_265 = EPROTOTYPE;
	_267 = errno;
	_266 = _267 != _265;
	if (!_266) {
		goto L176;
	} else {
		goto L89;
	}
L89:; // incoming:1
	_268 = ENOPROTOOPT;
	_270 = errno;
	_269 = _270 != _268;
	if (!_269) {
		goto L175;
	} else {
		goto L90;
	}
L90:; // incoming:1
	_271 = EPROTONOSUPPORT;
	_273 = errno;
	_272 = _273 != _271;
	if (!_272) {
		goto L174;
	} else {
		goto L91;
	}
L91:; // incoming:1
	_274 = ESOCKTNOSUPPORT;
	_276 = errno;
	_275 = _276 != _274;
	if (!_275) {
		goto L173;
	} else {
		goto L92;
	}
L92:; // incoming:1
	_277 = EOPNOTSUPP;
	_279 = errno;
	_278 = _279 != _277;
	if (!_278) {
		goto L172;
	} else {
		goto L93;
	}
L93:; // incoming:1
	_280 = EPFNOSUPPORT;
	_282 = errno;
	_281 = _282 != _280;
	if (!_281) {
		goto L171;
	} else {
		goto L94;
	}
L94:; // incoming:1
	_283 = EAFNOSUPPORT;
	_285 = errno;
	_284 = _285 != _283;
	if (!_284) {
		goto L170;
	} else {
		goto L95;
	}
L95:; // incoming:1
	_286 = EADDRINUSE;
	_288 = errno;
	_287 = _288 != _286;
	if (!_287) {
		goto L169;
	} else {
		goto L96;
	}
L96:; // incoming:1
	_289 = EADDRNOTAVAIL;
	_291 = errno;
	_290 = _291 != _289;
	if (!_290) {
		goto L168;
	} else {
		goto L97;
	}
L97:; // incoming:1
	_292 = ENETDOWN;
	_294 = errno;
	_293 = _294 != _292;
	if (!_293) {
		goto L167;
	} else {
		goto L98;
	}
L98:; // incoming:1
	_295 = ENETUNREACH;
	_297 = errno;
	_296 = _297 != _295;
	if (!_296) {
		goto L166;
	} else {
		goto L99;
	}
L99:; // incoming:1
	_298 = ENETRESET;
	_300 = errno;
	_299 = _300 != _298;
	if (!_299) {
		goto L165;
	} else {
		goto L100;
	}
L100:; // incoming:1
	_301 = ECONNABORTED;
	_303 = errno;
	_302 = _303 != _301;
	if (!_302) {
		goto L164;
	} else {
		goto L101;
	}
L101:; // incoming:1
	_304 = ECONNRESET;
	_306 = errno;
	_305 = _306 != _304;
	if (!_305) {
		goto L163;
	} else {
		goto L102;
	}
L102:; // incoming:1
	_307 = ENOBUFS;
	_309 = errno;
	_308 = _309 != _307;
	if (!_308) {
		goto L162;
	} else {
		goto L103;
	}
L103:; // incoming:1
	_310 = EISCONN;
	_312 = errno;
	_311 = _312 != _310;
	if (!_311) {
		goto L161;
	} else {
		goto L104;
	}
L104:; // incoming:1
	_313 = ENOTCONN;
	_315 = errno;
	_314 = _315 != _313;
	if (!_314) {
		goto L160;
	} else {
		goto L105;
	}
L105:; // incoming:1
	_316 = ESHUTDOWN;
	_318 = errno;
	_317 = _318 != _316;
	if (!_317) {
		goto L159;
	} else {
		goto L106;
	}
L106:; // incoming:1
	_319 = ETOOMANYREFS;
	_321 = errno;
	_320 = _321 != _319;
	if (!_320) {
		goto L158;
	} else {
		goto L107;
	}
L107:; // incoming:1
	_322 = ETIMEDOUT;
	_324 = errno;
	_323 = _324 != _322;
	if (!_323) {
		goto L157;
	} else {
		goto L108;
	}
L108:; // incoming:1
	_325 = ECONNREFUSED;
	_327 = errno;
	_326 = _327 != _325;
	if (!_326) {
		goto L156;
	} else {
		goto L109;
	}
L109:; // incoming:1
	_328 = EHOSTDOWN;
	_330 = errno;
	_329 = _330 != _328;
	if (!_329) {
		goto L155;
	} else {
		goto L110;
	}
L110:; // incoming:1
	_331 = EHOSTUNREACH;
	_333 = errno;
	_332 = _333 != _331;
	if (!_332) {
		goto L154;
	} else {
		goto L111;
	}
L111:; // incoming:1
	_334 = EALREADY;
	_336 = errno;
	_335 = _336 != _334;
	if (!_335) {
		goto L153;
	} else {
		goto L112;
	}
L112:; // incoming:1
	_337 = EINPROGRESS;
	_339 = errno;
	_338 = _339 != _337;
	if (!_338) {
		goto L152;
	} else {
		goto L113;
	}
L113:; // incoming:1
	_340 = ESTALE;
	_342 = errno;
	_341 = _342 != _340;
	if (!_341) {
		goto L151;
	} else {
		goto L114;
	}
L114:; // incoming:1
	_343 = EUCLEAN;
	_345 = errno;
	_344 = _345 != _343;
	if (!_344) {
		goto L150;
	} else {
		goto L115;
	}
L115:; // incoming:1
	_346 = ENOTNAM;
	_348 = errno;
	_347 = _348 != _346;
	if (!_347) {
		goto L149;
	} else {
		goto L116;
	}
L116:; // incoming:1
	_349 = ENAVAIL;
	_351 = errno;
	_350 = _351 != _349;
	if (!_350) {
		goto L148;
	} else {
		goto L117;
	}
L117:; // incoming:1
	_352 = EISNAM;
	_354 = errno;
	_353 = _354 != _352;
	if (!_353) {
		goto L147;
	} else {
		goto L118;
	}
L118:; // incoming:1
	_355 = EREMOTEIO;
	_357 = errno;
	_356 = _357 != _355;
	if (!_356) {
		goto L146;
	} else {
		goto L119;
	}
L119:; // incoming:1
	_358 = EDQUOT;
	_360 = errno;
	_359 = _360 != _358;
	if (!_359) {
		goto L145;
	} else {
		goto L120;
	}
L120:; // incoming:1
	_361 = ENOMEDIUM;
	_363 = errno;
	_362 = _363 != _361;
	if (!_362) {
		goto L144;
	} else {
		goto L121;
	}
L121:; // incoming:1
	_364 = EMEDIUMTYPE;
	_366 = errno;
	_365 = _366 != _364;
	if (!_365) {
		goto L143;
	} else {
		goto L122;
	}
L122:; // incoming:1
	_367 = ECANCELED;
	_369 = errno;
	_368 = _369 != _367;
	if (!_368) {
		goto L142;
	} else {
		goto L123;
	}
L123:; // incoming:1
	_370 = ENOKEY;
	_372 = errno;
	_371 = _372 != _370;
	if (!_371) {
		goto L141;
	} else {
		goto L124;
	}
L124:; // incoming:1
	_373 = EKEYEXPIRED;
	_375 = errno;
	_374 = _375 != _373;
	if (!_374) {
		goto L140;
	} else {
		goto L125;
	}
L125:; // incoming:1
	_376 = EKEYREVOKED;
	_378 = errno;
	_377 = _378 != _376;
	if (!_377) {
		goto L139;
	} else {
		goto L126;
	}
L126:; // incoming:1
	_379 = EKEYREJECTED;
	_381 = errno;
	_380 = _381 != _379;
	if (!_380) {
		goto L138;
	} else {
		goto L127;
	}
L127:; // incoming:1
	_382 = EOWNERDEAD;
	_384 = errno;
	_383 = _384 != _382;
	if (!_383) {
		goto L137;
	} else {
		goto L128;
	}
L128:; // incoming:1
	_385 = ENOTRECOVERABLE;
	_387 = errno;
	_386 = _387 != _385;
	if (!_386) {
		goto L136;
	} else {
		goto L129;
	}
L129:; // incoming:1
	_388 = ERFKILL;
	_390 = errno;
	_389 = _390 != _388;
	if (!_389) {
		goto L135;
	} else {
		goto L130;
	}
L130:; // incoming:1
	_391 = EHWPOISON;
	_393 = errno;
	_392 = _393 != _391;
	if (!_392) {
		goto L134;
	} else {
		goto L132;
	}
L132:; // incoming:2
	_394 = 2;
	_395 = (struct struct_3) {_394};
	_0 = _395;
	goto L133;
L133:; // incoming:131
	retval = _0;
	goto end;
L134:; // incoming:1
	_654 = 132;
	_655 = (struct struct_3) {_654};
	_0 = _655;
	goto L133;
L135:; // incoming:1
	_652 = 131;
	_653 = (struct struct_3) {_652};
	_0 = _653;
	goto L133;
L136:; // incoming:1
	_650 = 130;
	_651 = (struct struct_3) {_650};
	_0 = _651;
	goto L133;
L137:; // incoming:1
	_648 = 129;
	_649 = (struct struct_3) {_648};
	_0 = _649;
	goto L133;
L138:; // incoming:1
	_646 = 128;
	_647 = (struct struct_3) {_646};
	_0 = _647;
	goto L133;
L139:; // incoming:1
	_644 = 127;
	_645 = (struct struct_3) {_644};
	_0 = _645;
	goto L133;
L140:; // incoming:1
	_642 = 126;
	_643 = (struct struct_3) {_642};
	_0 = _643;
	goto L133;
L141:; // incoming:1
	_640 = 125;
	_641 = (struct struct_3) {_640};
	_0 = _641;
	goto L133;
L142:; // incoming:1
	_638 = 124;
	_639 = (struct struct_3) {_638};
	_0 = _639;
	goto L133;
L143:; // incoming:1
	_636 = 123;
	_637 = (struct struct_3) {_636};
	_0 = _637;
	goto L133;
L144:; // incoming:1
	_634 = 122;
	_635 = (struct struct_3) {_634};
	_0 = _635;
	goto L133;
L145:; // incoming:1
	_632 = 121;
	_633 = (struct struct_3) {_632};
	_0 = _633;
	goto L133;
L146:; // incoming:1
	_630 = 120;
	_631 = (struct struct_3) {_630};
	_0 = _631;
	goto L133;
L147:; // incoming:1
	_628 = 119;
	_629 = (struct struct_3) {_628};
	_0 = _629;
	goto L133;
L148:; // incoming:1
	_626 = 118;
	_627 = (struct struct_3) {_626};
	_0 = _627;
	goto L133;
L149:; // incoming:1
	_624 = 117;
	_625 = (struct struct_3) {_624};
	_0 = _625;
	goto L133;
L150:; // incoming:1
	_622 = 116;
	_623 = (struct struct_3) {_622};
	_0 = _623;
	goto L133;
L151:; // incoming:1
	_620 = 115;
	_621 = (struct struct_3) {_620};
	_0 = _621;
	goto L133;
L152:; // incoming:1
	_618 = 114;
	_619 = (struct struct_3) {_618};
	_0 = _619;
	goto L133;
L153:; // incoming:1
	_616 = 113;
	_617 = (struct struct_3) {_616};
	_0 = _617;
	goto L133;
L154:; // incoming:1
	_614 = 112;
	_615 = (struct struct_3) {_614};
	_0 = _615;
	goto L133;
L155:; // incoming:1
	_612 = 111;
	_613 = (struct struct_3) {_612};
	_0 = _613;
	goto L133;
L156:; // incoming:1
	_610 = 110;
	_611 = (struct struct_3) {_610};
	_0 = _611;
	goto L133;
L157:; // incoming:1
	_608 = 109;
	_609 = (struct struct_3) {_608};
	_0 = _609;
	goto L133;
L158:; // incoming:1
	_606 = 108;
	_607 = (struct struct_3) {_606};
	_0 = _607;
	goto L133;
L159:; // incoming:1
	_604 = 107;
	_605 = (struct struct_3) {_604};
	_0 = _605;
	goto L133;
L160:; // incoming:1
	_602 = 106;
	_603 = (struct struct_3) {_602};
	_0 = _603;
	goto L133;
L161:; // incoming:1
	_600 = 105;
	_601 = (struct struct_3) {_600};
	_0 = _601;
	goto L133;
L162:; // incoming:1
	_598 = 104;
	_599 = (struct struct_3) {_598};
	_0 = _599;
	goto L133;
L163:; // incoming:1
	_596 = 103;
	_597 = (struct struct_3) {_596};
	_0 = _597;
	goto L133;
L164:; // incoming:1
	_594 = 102;
	_595 = (struct struct_3) {_594};
	_0 = _595;
	goto L133;
L165:; // incoming:1
	_592 = 101;
	_593 = (struct struct_3) {_592};
	_0 = _593;
	goto L133;
L166:; // incoming:1
	_590 = 100;
	_591 = (struct struct_3) {_590};
	_0 = _591;
	goto L133;
L167:; // incoming:1
	_588 = 99;
	_589 = (struct struct_3) {_588};
	_0 = _589;
	goto L133;
L168:; // incoming:1
	_586 = 98;
	_587 = (struct struct_3) {_586};
	_0 = _587;
	goto L133;
L169:; // incoming:1
	_584 = 97;
	_585 = (struct struct_3) {_584};
	_0 = _585;
	goto L133;
L170:; // incoming:1
	_582 = 96;
	_583 = (struct struct_3) {_582};
	_0 = _583;
	goto L133;
L171:; // incoming:1
	_580 = 95;
	_581 = (struct struct_3) {_580};
	_0 = _581;
	goto L133;
L172:; // incoming:1
	_578 = 94;
	_579 = (struct struct_3) {_578};
	_0 = _579;
	goto L133;
L173:; // incoming:1
	_576 = 93;
	_577 = (struct struct_3) {_576};
	_0 = _577;
	goto L133;
L174:; // incoming:1
	_574 = 92;
	_575 = (struct struct_3) {_574};
	_0 = _575;
	goto L133;
L175:; // incoming:1
	_572 = 91;
	_573 = (struct struct_3) {_572};
	_0 = _573;
	goto L133;
L176:; // incoming:1
	_570 = 90;
	_571 = (struct struct_3) {_570};
	_0 = _571;
	goto L133;
L177:; // incoming:1
	_568 = 89;
	_569 = (struct struct_3) {_568};
	_0 = _569;
	goto L133;
L178:; // incoming:1
	_566 = 88;
	_567 = (struct struct_3) {_566};
	_0 = _567;
	goto L133;
L179:; // incoming:1
	_564 = 87;
	_565 = (struct struct_3) {_564};
	_0 = _565;
	goto L133;
L180:; // incoming:1
	_562 = 86;
	_563 = (struct struct_3) {_562};
	_0 = _563;
	goto L133;
L181:; // incoming:1
	_560 = 85;
	_561 = (struct struct_3) {_560};
	_0 = _561;
	goto L133;
L182:; // incoming:1
	_558 = 84;
	_559 = (struct struct_3) {_558};
	_0 = _559;
	goto L133;
L183:; // incoming:1
	_556 = 83;
	_557 = (struct struct_3) {_556};
	_0 = _557;
	goto L133;
L184:; // incoming:1
	_554 = 82;
	_555 = (struct struct_3) {_554};
	_0 = _555;
	goto L133;
L185:; // incoming:1
	_552 = 81;
	_553 = (struct struct_3) {_552};
	_0 = _553;
	goto L133;
L186:; // incoming:1
	_550 = 80;
	_551 = (struct struct_3) {_550};
	_0 = _551;
	goto L133;
L187:; // incoming:1
	_548 = 79;
	_549 = (struct struct_3) {_548};
	_0 = _549;
	goto L133;
L188:; // incoming:1
	_546 = 78;
	_547 = (struct struct_3) {_546};
	_0 = _547;
	goto L133;
L189:; // incoming:1
	_544 = 77;
	_545 = (struct struct_3) {_544};
	_0 = _545;
	goto L133;
L190:; // incoming:1
	_542 = 76;
	_543 = (struct struct_3) {_542};
	_0 = _543;
	goto L133;
L191:; // incoming:1
	_540 = 75;
	_541 = (struct struct_3) {_540};
	_0 = _541;
	goto L133;
L192:; // incoming:1
	_538 = 74;
	_539 = (struct struct_3) {_538};
	_0 = _539;
	goto L133;
L193:; // incoming:1
	_536 = 73;
	_537 = (struct struct_3) {_536};
	_0 = _537;
	goto L133;
L194:; // incoming:1
	_534 = 72;
	_535 = (struct struct_3) {_534};
	_0 = _535;
	goto L133;
L195:; // incoming:1
	_532 = 71;
	_533 = (struct struct_3) {_532};
	_0 = _533;
	goto L133;
L196:; // incoming:1
	_530 = 70;
	_531 = (struct struct_3) {_530};
	_0 = _531;
	goto L133;
L197:; // incoming:1
	_528 = 69;
	_529 = (struct struct_3) {_528};
	_0 = _529;
	goto L133;
L198:; // incoming:1
	_526 = 68;
	_527 = (struct struct_3) {_526};
	_0 = _527;
	goto L133;
L199:; // incoming:1
	_524 = 67;
	_525 = (struct struct_3) {_524};
	_0 = _525;
	goto L133;
L200:; // incoming:1
	_522 = 66;
	_523 = (struct struct_3) {_522};
	_0 = _523;
	goto L133;
L201:; // incoming:1
	_520 = 65;
	_521 = (struct struct_3) {_520};
	_0 = _521;
	goto L133;
L202:; // incoming:1
	_518 = 64;
	_519 = (struct struct_3) {_518};
	_0 = _519;
	goto L133;
L203:; // incoming:1
	_516 = 63;
	_517 = (struct struct_3) {_516};
	_0 = _517;
	goto L133;
L204:; // incoming:1
	_514 = 62;
	_515 = (struct struct_3) {_514};
	_0 = _515;
	goto L133;
L205:; // incoming:1
	_512 = 61;
	_513 = (struct struct_3) {_512};
	_0 = _513;
	goto L133;
L206:; // incoming:1
	_510 = 60;
	_511 = (struct struct_3) {_510};
	_0 = _511;
	goto L133;
L207:; // incoming:1
	_508 = 59;
	_509 = (struct struct_3) {_508};
	_0 = _509;
	goto L133;
L208:; // incoming:1
	_506 = 58;
	_507 = (struct struct_3) {_506};
	_0 = _507;
	goto L133;
L209:; // incoming:1
	_504 = 57;
	_505 = (struct struct_3) {_504};
	_0 = _505;
	goto L133;
L210:; // incoming:1
	_502 = 56;
	_503 = (struct struct_3) {_502};
	_0 = _503;
	goto L133;
L211:; // incoming:1
	_500 = 55;
	_501 = (struct struct_3) {_500};
	_0 = _501;
	goto L133;
L212:; // incoming:1
	_498 = 54;
	_499 = (struct struct_3) {_498};
	_0 = _499;
	goto L133;
L213:; // incoming:1
	_496 = 53;
	_497 = (struct struct_3) {_496};
	_0 = _497;
	goto L133;
L214:; // incoming:1
	_494 = 52;
	_495 = (struct struct_3) {_494};
	_0 = _495;
	goto L133;
L215:; // incoming:1
	_492 = 51;
	_493 = (struct struct_3) {_492};
	_0 = _493;
	goto L133;
L216:; // incoming:1
	_490 = 50;
	_491 = (struct struct_3) {_490};
	_0 = _491;
	goto L133;
L217:; // incoming:1
	_488 = 49;
	_489 = (struct struct_3) {_488};
	_0 = _489;
	goto L133;
L218:; // incoming:1
	_486 = 48;
	_487 = (struct struct_3) {_486};
	_0 = _487;
	goto L133;
L219:; // incoming:1
	_484 = 47;
	_485 = (struct struct_3) {_484};
	_0 = _485;
	goto L133;
L220:; // incoming:1
	_482 = 46;
	_483 = (struct struct_3) {_482};
	_0 = _483;
	goto L133;
L221:; // incoming:1
	_480 = 45;
	_481 = (struct struct_3) {_480};
	_0 = _481;
	goto L133;
L222:; // incoming:1
	_478 = 44;
	_479 = (struct struct_3) {_478};
	_0 = _479;
	goto L133;
L223:; // incoming:1
	_476 = 43;
	_477 = (struct struct_3) {_476};
	_0 = _477;
	goto L133;
L224:; // incoming:1
	_474 = 42;
	_475 = (struct struct_3) {_474};
	_0 = _475;
	goto L133;
L225:; // incoming:1
	_472 = 41;
	_473 = (struct struct_3) {_472};
	_0 = _473;
	goto L133;
L226:; // incoming:1
	_470 = 40;
	_471 = (struct struct_3) {_470};
	_0 = _471;
	goto L133;
L227:; // incoming:1
	_468 = 39;
	_469 = (struct struct_3) {_468};
	_0 = _469;
	goto L133;
L228:; // incoming:1
	_466 = 38;
	_467 = (struct struct_3) {_466};
	_0 = _467;
	goto L133;
L229:; // incoming:1
	_464 = 37;
	_465 = (struct struct_3) {_464};
	_0 = _465;
	goto L133;
L230:; // incoming:1
	_462 = 36;
	_463 = (struct struct_3) {_462};
	_0 = _463;
	goto L133;
L231:; // incoming:1
	_460 = 35;
	_461 = (struct struct_3) {_460};
	_0 = _461;
	goto L133;
L232:; // incoming:1
	_458 = 34;
	_459 = (struct struct_3) {_458};
	_0 = _459;
	goto L133;
L233:; // incoming:1
	_456 = 33;
	_457 = (struct struct_3) {_456};
	_0 = _457;
	goto L133;
L234:; // incoming:1
	_454 = 32;
	_455 = (struct struct_3) {_454};
	_0 = _455;
	goto L133;
L235:; // incoming:1
	_452 = 31;
	_453 = (struct struct_3) {_452};
	_0 = _453;
	goto L133;
L236:; // incoming:1
	_450 = 30;
	_451 = (struct struct_3) {_450};
	_0 = _451;
	goto L133;
L237:; // incoming:1
	_448 = 29;
	_449 = (struct struct_3) {_448};
	_0 = _449;
	goto L133;
L238:; // incoming:1
	_446 = 28;
	_447 = (struct struct_3) {_446};
	_0 = _447;
	goto L133;
L239:; // incoming:1
	_444 = 27;
	_445 = (struct struct_3) {_444};
	_0 = _445;
	goto L133;
L240:; // incoming:1
	_442 = 26;
	_443 = (struct struct_3) {_442};
	_0 = _443;
	goto L133;
L241:; // incoming:1
	_440 = 25;
	_441 = (struct struct_3) {_440};
	_0 = _441;
	goto L133;
L242:; // incoming:1
	_438 = 24;
	_439 = (struct struct_3) {_438};
	_0 = _439;
	goto L133;
L243:; // incoming:1
	_436 = 23;
	_437 = (struct struct_3) {_436};
	_0 = _437;
	goto L133;
L244:; // incoming:1
	_434 = 22;
	_435 = (struct struct_3) {_434};
	_0 = _435;
	goto L133;
L245:; // incoming:1
	_432 = 21;
	_433 = (struct struct_3) {_432};
	_0 = _433;
	goto L133;
L246:; // incoming:1
	_430 = 20;
	_431 = (struct struct_3) {_430};
	_0 = _431;
	goto L133;
L247:; // incoming:1
	_428 = 19;
	_429 = (struct struct_3) {_428};
	_0 = _429;
	goto L133;
L248:; // incoming:1
	_426 = 18;
	_427 = (struct struct_3) {_426};
	_0 = _427;
	goto L133;
L249:; // incoming:1
	_424 = 17;
	_425 = (struct struct_3) {_424};
	_0 = _425;
	goto L133;
L250:; // incoming:1
	_422 = 16;
	_423 = (struct struct_3) {_422};
	_0 = _423;
	goto L133;
L251:; // incoming:1
	_420 = 15;
	_421 = (struct struct_3) {_420};
	_0 = _421;
	goto L133;
L252:; // incoming:1
	_418 = 14;
	_419 = (struct struct_3) {_418};
	_0 = _419;
	goto L133;
L253:; // incoming:1
	_416 = 13;
	_417 = (struct struct_3) {_416};
	_0 = _417;
	goto L133;
L254:; // incoming:1
	_414 = 12;
	_415 = (struct struct_3) {_414};
	_0 = _415;
	goto L133;
L255:; // incoming:1
	_412 = 11;
	_413 = (struct struct_3) {_412};
	_0 = _413;
	goto L133;
L256:; // incoming:1
	_410 = 10;
	_411 = (struct struct_3) {_410};
	_0 = _411;
	goto L133;
L257:; // incoming:1
	_408 = 9;
	_409 = (struct struct_3) {_408};
	_0 = _409;
	goto L133;
L258:; // incoming:1
	_406 = 8;
	_407 = (struct struct_3) {_406};
	_0 = _407;
	goto L133;
L259:; // incoming:1
	_404 = 7;
	_405 = (struct struct_3) {_404};
	_0 = _405;
	goto L133;
L260:; // incoming:1
	_402 = 6;
	_403 = (struct struct_3) {_402};
	_0 = _403;
	goto L133;
L261:; // incoming:1
	_400 = 5;
	_401 = (struct struct_3) {_400};
	_0 = _401;
	goto L133;
L262:; // incoming:1
	_398 = 4;
	_399 = (struct struct_3) {_398};
	_0 = _399;
	goto L133;
L263:; // incoming:1
	_396 = 3;
	_397 = (struct struct_3) {_396};
	_0 = _397;
	goto L133;
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
	return retval.tag != 135;
}
#endif
