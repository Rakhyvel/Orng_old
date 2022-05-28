/*
PHILOSOPHY:
- Stateless functional style between modules/packages for predictability
- Stateful imperative style inside functions for speed
- Everything, including packages, modules, functions, constants, AND types, is an expression
- Every .orng file defines one symbol with the same name as the file


1. read files in package
2. tokenize
3. parse into AST & symbol tree
	- each file contains one definition of a constant type
	- the entire program is represented by a symbol tree
	- the symbol tree defined in each file is appended to the program symbol tree
4. for each symbol definition, flatten AST into IR list
	- types are NOT flattened and maintain tree structure for ease of comparing
	- this includes paramlists for types, modules, packages, function domains
	- types ASTs ARE expanded and validated to form their true structural type
	- each symbol keeps a copy of their old type for error printing(?)
5. perform semantic analysis on each IR instruction in list to turn it into a typed IR list
6. take symbol tree with typed IR list definitions and generate to C code or doc
	- flatten symbol tree to have a list of all globals, functions, structs, etc
*/

#include "../util/debug.h"
#include "./doc.h"
#include "./generator.h"
#include "./ir.h"
#include "./lexer.h"
#include "./parse.h"
#include "./symbol.h"
#include "./tinydir.h"
#include "./validator.h"
#include <process.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include <io.h> // For access().
#include <sys/stat.h> // For stat().
#include <sys/types.h> // For stat().

char* packagesPath;
char* filename;
// The filename of the output file
char outFilename[255];

static bool errsExist = false;

// files[fileNo] -> lines[lineNo]
Map* files;
Map* files_whitespace; // Map(String, List(Int))

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
        } else {
            if (lineLength >= lineCapacity - 1) {
                lineCapacity *= 2;
                char* newLine = realloc(line, lineCapacity * sizeof(char));
                if (newLine) {
                    line = newLine;
                } else {
                    fprintf(stderr, "fatal: memory error\n");
                    exit(1);
                }
            }
            line[lineLength++] = nextChar;
            line[lineLength + 1] = '\0';
        }
    }
    List_Append(lines, line);

    Map_Put(files, filename, lines);
}

//
char* getRelPath(char* absPath)
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

char* pathToFilename(char* path)
{
    char* recentSlash = path - 1;
    for (int i = 0; path[i]; i++) {
        if (path[i] == '/' || path[i] == '\\') {
            recentSlash = path + i;
        }
    }
    return recentSlash + 1;
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

static ASTNode* readFile(char* _filename, SymbolNode* program)
{
    FILE* in;
    filename = _filename;
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
    ASTNode* retval = Parser_Parse(in, program);

    if (fclose(in)) {
        perror(_filename);
        exit(1);
    }
    return retval;
}

char* getUserDirectory()
{
#ifdef _WIN32
    char* userDir = NULL;
    size_t sz = 0;
    if (_dupenv_s(&userDir, &sz, "USERPROFILE") || userDir == NULL) {
        gen_error("user profile environment variable not defined\n");
    }
    return userDir;
#else
    return getenv("HOME");
#endif
}

/*
Takes in a parent absolute directory, and a sub directory path.
Creates the subdirectory if it does not exist
Returns the concatonated path length
*/
char* createIfNotExist(char* parentAbsDir, char* subDirPath)
{
    int userDirLen = strlen(parentAbsDir);
    int subDirLen = userDirLen + strlen(subDirPath) + 1;
    char* subDir = calloc(subDirLen, sizeof(char));
    if (!subDir) {
        gen_error("mem error");
        return;
    }
    strcpy_s(subDir, subDirLen, parentAbsDir);
    strcat_s(subDir, subDirLen, subDirPath);

    bool exists = false;
    if (_access(subDir, 0) == 0) {
        struct stat status;
        stat(subDir, &status);
        exists = (status.st_mode & S_IFDIR) != 0;
    } else {
        exists = false;
    }

    if (!exists) {
#ifdef _WIN32
        _mkdir(subDir);
#else
        mkdir(subDir, 0700);
#endif
    }

    return subDir;
}

wchar_t* charToWChar(char* orig)
{
    size_t newsize = strlen(orig) + 1;

    wchar_t* wcstring = calloc(newsize, sizeof(wchar_t));

    size_t convertedChars = 0;
    mbstowcs_s(&convertedChars, wcstring, newsize, orig, _TRUNCATE);

    return wcstring;
}

char* wCharToChar(wchar_t* orig)
{
    size_t origsize = wcslen(orig) + 1;
    size_t convertedChars = 0;

    const size_t newsize = origsize * 2;

    char* nstring = calloc(newsize, sizeof(char));

    wcstombs_s(&convertedChars, nstring, newsize, orig, _TRUNCATE);

    return nstring;
}

/*
to read package
    read in & parse package manifest file
    validate package AST
    for each dependency:
        check program to see if it already exists
        if it exists already
            if not visited
                err, cycles!
        else
            read in package, add package ptr to the node's list of depens
    read in all module files from package dir
	set package symbol to be visited
*/
SymbolNode* readPackage(char* packagePath, SymbolNode* program)
{
    // Create manifest filename
    int manifestFilenameLen = strlen(packagePath) + 50;
    char* manifestFilename = calloc(manifestFilenameLen, sizeof(char));
    if (!manifestFilename) {
        gen_error("mem err");
        return -1;
    }
    char* packageName = pathToFilename(packagePath);
    strcpy_s(manifestFilename, manifestFilenameLen, packagePath);
    strcat_s(manifestFilename, manifestFilenameLen, "\\");
    strcat_s(manifestFilename, manifestFilenameLen, packageName);
    strcat_s(manifestFilename, manifestFilenameLen, ".pkg.orng");

    // Read in & parse package manifest file
    ASTNode* packageAST = readFile(manifestFilename, program);
    SymbolNode* packageSymbol = packageAST->define.symbol;

    char* relPath = getRelPath(manifestFilename);
    char end = isSubStr(relPath, packageSymbol->name);
    if (end != '\\' && end != '/') {
        error(packageAST->pos, "package symbol differs from package directory");
    }

    List* dependencies = packageSymbol->restrictionExpr;
    for (ListElem* e = List_Begin(dependencies); e != List_End(dependencies); e = e->next) {
        ASTNode* packageAST = e->data;
        if (packageAST->astType != AST_IDENT) {
            error(packageAST->pos, "package restrict list must be identifiers only");
        }
        char* packageName = packageAST->ident.data;
        SymbolNode* depenPackage;
        if ((depenPackage = Map_Get(program->children, packageName)) != NULL) {
            if (!depenPackage->visited) {
                gen_error("cycle between packages '%s' and '%s'", packageSymbol->name, packageName);
            }
        } else {
            char absolutePackageName[255];
            memset(absolutePackageName, 0, 255);
            strcat_s(absolutePackageName, 255, packagesPath);
            strcat_s(absolutePackageName, 255, "\\");
            strcat_s(absolutePackageName, 255, packageName);
            readPackage(absolutePackageName, program);
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
            if (isSubStr(pathToFilename(filename), var->name) != '.') {
                error(def->pos, "module symbol differs from module file name");
            }
            List_Append(packageSymbol->def->paramlist.defines, def);
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

void unVisitSymbolTree(SymbolNode* node)
{
    if (node == NULL) {
        return;
    }
    node->visited = false;

    List* children = node->children->keyList;
    ListElem* elem = List_Begin(children);
    for (; elem != List_End(children); elem = elem->next) {
        SymbolNode* child = Map_Get(node->children, elem->data);
        unVisitSymbolTree(child);
    }
}

/*
Translates an input file to a C output file
*/
int main(int argc, char** argv)
{
    clock_t t;
    t = clock();

    printf("started...\n");
    if (argc != 2) {
        gen_error("expected project directory as command line argument");
    }

    // Create orange directories if they don't exist
    char* userDir = getUserDirectory();
    createIfNotExist(userDir, "\\orange");
    packagesPath = createIfNotExist(userDir, "\\orange\\packages");

    // Read in manifest
    AST_Init();
    files = Map_Create();
    SymbolNode* program = Symbol_Create("program", SYMBOL_PROGRAM, NULL, (Position) { NULL, 0, 0, 0 });
    SymbolNode* outPackage = readPackage(argv[1], program);
    unVisitSymbolTree(program);

    // Either generate doc or generate program
    if (false) {
        doDefTypes = true;
        char* packageName = pathToFilename(argv[1]);
        SymbolNode* package = Symbol_Find(packageName, program);
        Doc_Generate(package, argv[1]);
    } else {
        Program programStruct = Validator_Validate(program);

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

        Generator_Generate(programStruct, out);

        if (fclose(out)) {
            perror(outFilename);
            exit(1);
        }
    }

    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("%d ms\n", (int)(time_taken * 1000.0));

    system("pause");
}

/*
prints out a general error message about the program with no position given
*/
void gen_error(const char* message, ...)
{
    va_list args;
    fprintf(stderr, "error: ");
    va_start(args, message);
    vfprintf(stderr, message, args);
    va_end(args);
    fprintf(stderr, "\n");

    system("pause");
    exit(1);
}

static char* firstNonSpace(char* str)
{
    int i = 0;
    for (; str[i] != '\0' && isspace(str[i]); i++)
        ;
    return str + i;
}

static int countLeadingWhitespace(char* str)
{
    int count = 0;
    for (int i = 0; str[i] != '\0' && isspace(str[i]); i++) {
        if (str[i] == ' ') {
            count++;
        } else if (str[i] == '\t') {
            count += 4;
        }
    }
    return count;
}

static void printPos(struct position pos)
{
    if (pos.filename) {
        fprintf(stderr, "%s: \n", getRelPath(pos.filename));
        fprintf(stderr, "      |\n");
        int minWhiteSpace = 100000;
        int maxLineLength = 0;
        for (int i = pos.start_line; i <= pos.end_line; i++) {
            List* lines = Map_Get(files, pos.filename);
            char* lineStr = List_Get(lines, i - 1);
            minWhiteSpace = min(minWhiteSpace, countLeadingWhitespace(lineStr));
        }
        for (int i = pos.start_line; i <= pos.end_line; i++) {
            fprintf(stderr, "%d", i);
            for (int j = 0; j < 5 - (int)(log(i) / log(10)); j++) {
                fprintf(stderr, " ");
            }
            List* lines = Map_Get(files, pos.filename);
            char* lineStr = List_Get(lines, i - 1);
            int spaces = countLeadingWhitespace(lineStr) - minWhiteSpace;
            fprintf(stderr, "| ");
            for (int j = 0; j < spaces; j++) {
                fprintf(stderr, " ");
            }
            if (pos.start_line == pos.end_line || (i != pos.start_line && i != pos.end_line)) {
                char* stripped = firstNonSpace(lineStr);
                fprintf(stderr, "%s", stripped);
                maxLineLength = max(maxLineLength, strlen(stripped) + spaces);
            } else {
                bool seenNonWhiteSpace = false;
                int start = i == pos.start_line ? pos.start_span : 1;
                int end = i == pos.start_line ? strlen(lineStr) + 1 : pos.end_span + 1;
                int charsPrinted = spaces;
                for (int j = start; j <= end; j++) {
                    char c = lineStr[j - 1];
                    if (isspace(c) && !seenNonWhiteSpace) {
                        continue;
                    } else {
                        seenNonWhiteSpace = true;
                        fprintf(stderr, "%c", c);
                        charsPrinted++;
                    }
                }
                maxLineLength = max(maxLineLength, charsPrinted - 1);
            }
            fprintf(stderr, "\n");
        }

        fprintf(stderr, "      | ");
        if (pos.start_line == pos.end_line) {
            for (int i = 0; i < pos.start_span - 1; i++) {
                fprintf(stderr, " ");
            }
            for (int i = pos.start_span; i < pos.end_span; i++) {
                fprintf(stderr, "^");
            }
        } else {
            for (int i = 0; i < maxLineLength; i++) {
                fprintf(stderr, "^");
            }
        }
        fprintf(stderr, "\n");
    }
}

/*
Prints out an error message, with a filename and line number
*/
void error(struct position pos, const char* message, ...)
{
    va_list args;
    fprintf(stderr, "error: ");

    va_start(args, message);
    vfprintf(stderr, message, args);
    va_end(args);
    fprintf(stderr, "\n");

    printPos(pos);

    system("pause");
    exit(1);
}

void error2(Position pos1, Position pos2, const char* message, ...)
{
    va_list args;
    fprintf(stderr, "error: ");

    va_start(args, message);
    vfprintf(stderr, message, args);
    va_end(args);
    fprintf(stderr, "\n");

    printPos(pos1);
    printPos(pos2);

    system("pause");
    exit(1);
}