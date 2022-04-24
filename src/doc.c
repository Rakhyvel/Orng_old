#include "doc.h"
#include "ast.h"
#include "main.h"
#include <stdio.h>
#include <string.h>

char* randomText = "Creates a new IconButton with a path to the icon, a position, and a color schemeCreates a new IconButton with a path to the icon, a position, and a color schemeCreates a new IconBu";

static void generateType(FILE* out, SymbolNode* global)
{
    if (!global || !global->isPublic || global->symbolType != SYMBOL_TYPE) {
        return;
    }
    fprintf(out, "<div class=\"member\">");
    char typeStr[255];
    AST_TypeRepr(typeStr, global->type);
    if (global->isCompTime) {
        fprintf(out, "<h3><code class=\"ident\">%s</code><code>::</code><code class=\"type\">%s</code></h3>", global->name, typeStr);
    } else {
        fprintf(out, "<h3><code class=\"ident\">%s</code><code>:</code><code class=\"type\">%s</code></h3>", global->name, typeStr);
    }
    fprintf(out, "</div>");
}

static void generateGlobal(FILE* out, SymbolNode* global)
{
    if (!global || !global->isPublic || global->symbolType != SYMBOL_VARIABLE) {
        return;
    }
    fprintf(out, "<div class=\"member\">");
    char typeStr[255];
    AST_TypeRepr(typeStr, global->type);
    if (global->isCompTime) {
        fprintf(out, "<h3><code class=\"ident\">%s</code><code>::</code><code class=\"type\">%s</code></h3>", global->name, typeStr);
    } else {
        fprintf(out, "<h3><code class=\"ident\">%s</code><code>:</code><code class=\"type\">%s</code></h3>", global->name, typeStr);
    }

    fprintf(out, "<p>%s</p></div>", global->desc);
}

static void generateFunction(FILE* out, SymbolNode* global)
{
    if (!global || !global->isPublic || global->symbolType != SYMBOL_FUNCTION) {
        return;
    }

    fprintf(out, "<div class=\"member\">");
    char typeStr[255];
    AST_TypeRepr(typeStr, global->type);
    if (global->isCompTime) {
        fprintf(out, "<h3><code class=\"ident\">%s</code><code>::</code><code class=\"type\">%s</code></h3>", global->name, typeStr);
    } else {
        fprintf(out, "<h3><code class=\"ident\">%s</code><code>:</code><code class=\"type\">%s</code></h3>", global->name, typeStr);
    }
    fprintf(out, "<p>%s</p><h3><em>Parameters</em></h3><p>blah blah blah blah</p><h3><em>Returns</em></h3><p>blah blah blah blah</p>\n", global->desc);
    fprintf(out, "</div>");
}

static void generateModule(FILE* out, SymbolNode* module)
{
    if (!module || !module->isPublic || module->symbolType != SYMBOL_MODULE) {
        return;
    }
    fprintf(out, "<div class=\"module\" id=\"%s\">", module->name);
    char typeStr[255];
    AST_TypeRepr(typeStr, module->type);
    if (module->isCompTime) {
        fprintf(out, "<h2><code class=\"ident\">%s</code><code>::</code><code class=\"type\">%s</code></h2>", module->name, typeStr);
    } else {
        fprintf(out, "<h2><code class=\"ident\">%s</code><code>::</code><code class=\"type\">%s</code></h2>", module->name, typeStr);
    }
    fprintf(out, "<p>%s</p>", module->desc);

    List* children = module->children->keyList;

    fprintf(out, "<h3><em>Types</em></h3>");
    ListElem* elem = List_Begin(children);
    for (; elem != List_End(children); elem = elem->next) {
        SymbolNode* child = Map_Get(module->children, elem->data);
        generateType(out, child);
    }
    fprintf(out, "<h3><em>Fields</em></h3>");
    elem = List_Begin(children);
    for (; elem != List_End(children); elem = elem->next) {
        SymbolNode* child = Map_Get(module->children, elem->data);
        generateGlobal(out, child);
    }
    fprintf(out, "<h3><em>Functions</em></h3>");
    elem = List_Begin(children);
    for (; elem != List_End(children); elem = elem->next) {
        SymbolNode* child = Map_Get(module->children, elem->data);
        generateFunction(out, child);
    }
    fprintf(out, "</div>");
}

static void generatePackage(FILE* out, SymbolNode* symbol)
{
    if (!symbol || !symbol->isPublic || symbol->symbolType != SYMBOL_PACKAGE) {
        return;
    }
    char typeStr[255];
    AST_TypeRepr(typeStr, symbol->type);
    fprintf(out, "<div class=\"module\"><h1><code class=\"ident\">%s</code><code>::</code><code class=\"type\">%s</code></h1><p>%s</p>", symbol->name, typeStr, randomText);

    List* children = symbol->children->keyList;

    fprintf(out, "<h3><em>Modules</em></h3><table><tbody>");
    ListElem* elem = List_Begin(children);
    for (; elem != List_End(children); elem = elem->next) {
        SymbolNode* child = Map_Get(symbol->children, elem->data);
        if (child->symbolType != SYMBOL_MODULE) {
            continue;
        }
        fprintf(out, "<tr><td><h3><code><a href=\"#%s\">%s</a></code></h3></td></tr>", child->name, child->name);
    }
    fprintf(out, "</tbody></table></div>");
    elem = List_Begin(children);
    for (; elem != List_End(children); elem = elem->next) {
        SymbolNode* child = Map_Get(symbol->children, elem->data);
        generateModule(out, child);
    }
}

void Doc_Generate(SymbolNode* program, char* packagePath)
{
    char* outFilename[255];
    strncpy_s(outFilename, 255, packagePath, 255);
    strcat_s(outFilename, 255, "/");
    strcat_s(outFilename, 255, pathToFilename(packagePath));
    strcat_s(outFilename, 255, ".html");

    FILE* out;
    fopen_s(&out, outFilename, "w");
    if (out == NULL) {
        perror(outFilename);
        exit(1);
        return;
    }

    // Generate HTML
    fprintf(out, "<!-- documentation generated by Orange Translator http://josephs-projects.com -->\n");
    fprintf(out, "<html><head><title>%s.html</title><style>body{font-family:arial; font-size:14px; color:#333} .content{max-width:150ch; margin:auto;} .ident{color: #001080;} .type{color: #267FB3;} div {margin: 1.5rem 0rem; padding:0.5rem 1rem} div.module {background-color:#F3F3F3; border: 1px solid black;} div.member{background-color:#fff; border:1px solid black;} h1 {font-size: 1.25rem;} h2 {font-size: 1rem;} h3 {font-size: 1rem; margin: 0;} ul{padding:0 0 0 1rem; margin:0;}</style></head><body><div class=\"content\">", program->name);
    generatePackage(out, program);
    fprintf(out, "</div></body></html>");

    if (fclose(out)) {
        perror(outFilename);
        exit(1);
        return;
    }
}