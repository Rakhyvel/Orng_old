// © 2021-2022 Joseph Shimel. All rights reserved.
/*
COMPILER PIPELINE:
- Root package filename is given as command-line argument.
- .pkg.orng manifest file is read in and parsed. Package dependency non-cyclic graph is constructed.
- Every .orng file in every package is read in and parsed to create symbol tree
- The symbol tree is walked-through, type expanding and semantic analysis is done
- The symbol for the main function is found
- The main function symbol is converted to a control-flow graph (CFG) node, along with any functions the main functions calls, and so on.
- The CFG is optimized
- The CFG is generated out to output code
*/

#include "../util/debug.h"
#include "./errors.h"
#include "./generator.h"
#include "./ir.h"
#include "./lexer.h"
#include "./parse.h"
#include "./program.h"
#include "./symbol.h"
#include "./tinydir.h"
#include "./validator.h"
#include <process.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Given an absolute path, returns pointer of substring in the form packageName/fileName
char* Main_GetRelPath(char* absPath)
{
    char* recentSlash = absPath - 1;
    char* secondRecentSlash = absPath - 1;
    for (int i = 0; absPath[i]; i++) {
        if (absPath[i] == '/' || absPath[i] == '\\') {
            secondRecentSlash = recentSlash;
            recentSlash = absPath + i;
        }
    }
    return secondRecentSlash + 1;
}

// Takes in a path, returns a pointer to the substring of just the filename
char* Main_PathToFilename(char* path)
{
    char* recentSlash = path - 1;
    for (int i = 0; path[i]; i++) {
        if (path[i] == '/' || path[i] == '\\') {
            recentSlash = path + i;
        }
    }
    return recentSlash + 1;
}

// Reads in a file and puts the filename/list of lines relation in the files map
static void readLines(FILE* in)
{
    int nextChar, lineLength = 0, lineCapacity = 80;
    List* lines = List_Create();
    char* line = calloc(lineCapacity, sizeof(char));
    while ((nextChar = fgetc(in)) != EOF) {
        if (nextChar == '\n') {
            lineLength = 0;
            lineCapacity = 80;
            List_Append(lines, line);
            line = calloc(lineCapacity, sizeof(char));
            ASSERT(line != NULL);
        } else {
            if (lineLength >= lineCapacity - 1) {
                lineCapacity *= 2;
                line = realloc(line, lineCapacity * sizeof(char));
                ASSERT(line != NULL);
            }
            ASSERT(line != NULL);
            line[lineLength++] = nextChar;
            line[lineLength + 1] = '\0';
        }
    }
    List_Append(lines, line);

    Map_Put(program->files, program->filename, lines);
}

// Reads a file, updates file map, parses file and returns the define AST node
static ASTNode* readFile(char* _filename, SymbolNode* rootSymbol)
{
    FILE* in;
    program->filename = _filename;
    line = 1;
    span = 1;

    fopen_s(&in, _filename, "r");
    if (in == NULL) {
        perror(_filename);
        system("pause");
        exit(1);
    }
    readLines(in);
    if (fclose(in)) {
        perror(_filename);
        exit(1);
    }

    fopen_s(&in, _filename, "r");
    if (in == NULL) {
        perror(_filename);
        exit(1);
    }
    ASTNode* retval = Parser_Parse(in, rootSymbol);

    if (fclose(in)) {
        perror(_filename);
        exit(1);
    }
    return retval;
}

// Returns whether or not a relative path begins with a string
static char isSubStr(char* relPath, char* symbolName)
{
    int i;
    for (i = 0; symbolName[i]; i++) {
        if (symbolName[i] != relPath[i]) {
            return false;
        }
    }
    return relPath[i];
}

// Converts a char to a wide character
static wchar_t* charToWChar(char* orig)
{
    size_t newsize = strlen(orig) + 1;

    wchar_t* wcstring = calloc(newsize, sizeof(wchar_t));

    size_t convertedChars = 0;
    mbstowcs_s(&convertedChars, wcstring, newsize, orig, _TRUNCATE);

    return wcstring;
}

// Converts a wide character to a character
static char* wCharToChar(wchar_t* orig)
{
    size_t origsize = wcslen(orig) + 1;
    size_t convertedChars = 0;

    const size_t newsize = origsize * 2;

    char* nstring = calloc(newsize, sizeof(char));

    wcstombs_s(&convertedChars, nstring, newsize, orig, _TRUNCATE);

    return nstring;
}

// Reads in package, constructs package dependency graph, reads in file of package
static SymbolNode* readPackage(char* packagePath, SymbolNode* rootSymbol)
{
    // Create manifest filename
    int manifestFilenameLen = strlen(packagePath) + 50;
    char* manifestFilename = calloc(manifestFilenameLen, sizeof(char));
    ASSERT(manifestFilename != NULL);
    char* packageName = Main_PathToFilename(packagePath);
    strcpy_s(manifestFilename, manifestFilenameLen, packagePath);
    strcat_s(manifestFilename, manifestFilenameLen, "\\");
    strcat_s(manifestFilename, manifestFilenameLen, packageName);
    strcat_s(manifestFilename, manifestFilenameLen, ".pkg.orng");

    // Read in & parse package manifest file
    ASTNode* packageAST = readFile(manifestFilename, rootSymbol);
    SymbolNode* packageSymbol = packageAST->define.symbol;

    char* relPath = Main_GetRelPath(manifestFilename);
    char end = isSubStr(relPath, packageSymbol->name);
    if (end != '\\' && end != '/') {
        error(packageAST->pos, "package symbol differs from package directory");
    }

    forall(elem, packageSymbol->restrictionExpr)
    {
        ASTNode* packageAST = elem->data;
        if (packageAST->astType != AST_IDENT) {
            error(packageAST->pos, "package restrict list must be identifiers only");
        }
        char* packageName = packageAST->ident.data;
        SymbolNode* depenPackage;
        if ((depenPackage = Map_Get(rootSymbol->children, packageName)) != NULL) {
            if (!depenPackage->visited) {
                error2(packageSymbol->pos, depenPackage->pos, "cycle between packages '%s' and '%s'", packageSymbol->name, packageName);
            }
        } else {
            char absolutePackageName[255];
            memset(absolutePackageName, 0, 255);
            strcat_s(absolutePackageName, 255, program->packagesPath);
            strcat_s(absolutePackageName, 255, "\\");
            strcat_s(absolutePackageName, 255, packageName);
            readPackage(absolutePackageName, rootSymbol);
        }
    }
    packageSymbol->visited = true;

    tinydir_dir dir;
    if (tinydir_open(&dir, charToWChar(packagePath)) == -1) {
        perror("Error opening file");
        goto bail;
    }

    while (dir.has_next) {
        tinydir_file file;
        if (tinydir_readfile(&dir, &file) == -1) {
            perror("Error getting file");
            goto bail;
        }

        char* filename = wCharToChar(file.path);
        if (strstr(filename, ".orng") && !strstr(filename, ".pkg.orng")) {
            ASTNode* def = readFile(filename, packageSymbol);
            SymbolNode* var = def->define.symbol;
            if (isSubStr(Main_PathToFilename(filename), var->name) != '.') {
                error(def->pos, "symbol name differs from containing file name");
            }
            List_Append(packageSymbol->def->product.defines, def);
        }

        if (tinydir_next(&dir) == -1) {
            perror("Error getting next file");
            goto bail;
        }
    }
bail:
    tinydir_close(&dir);
    return packageSymbol;
}

// Compiles an Orng program given a root package directory path
int main(int argc, char** argv)
{
    clock_t t;
    t = clock();

    printf("started...\n");
    if (argc != 2) {
        compilerError("expected project directory as command line argument");
    }

    AST_Init();
    Program_Init();

    SymbolNode* rootSymbol = Symbol_Create("program", SYMBOL_PROGRAM, NULL, (Position) { NULL, 0, 0, 0 });
    SymbolNode* outPackage = readPackage(argv[1], rootSymbol);
    Symbol_UnvisitTree(rootSymbol);

    Validator_ValidateSymbol(rootSymbol);

    char outFilename[255];
    memset(outFilename, 0, 255);
    strcat_s(outFilename, 255, argv[1]);
    strcat_s(outFilename, 255, "\\");
    if (Map_Get(outPackage->children, "_outname")) {
        SymbolNode* outnameSymbol = Map_Get(outPackage->children, "_outname");
        ASTNode* outnameDef = outnameSymbol->def;
        strcat_s(outFilename, 255, outnameDef->string.data);
    } else {
        strcat_s(outFilename, 255, "out.c");
    }

    FILE* out;
    fopen_s(&out, outFilename, "w");
    if (out == NULL) {
        perror(outFilename);
        exit(1);
    }

    Generator_Generate(out);

    if (fclose(out)) {
        perror(outFilename);
        exit(1);
    }

    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("%d ms\n", (int)(time_taken * 1000.0));

    system("pause");
}