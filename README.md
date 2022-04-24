# Orange
Orange is a simple, modular general-purpose programming language for hobby programmers.

## Emphasis on code re-use
Waste less time configuring libraries and more time working on the projects you love.
- No messing with complicated build configurations each time you start a new project
- Package manifests use the same syntax as the rest of the language
- Low-friction code refactorability

## Simple language
Things look like what they do, and do what they look like.
- No ambiguity!
- No hidden control flow
- No hidden allocation/deallocations

## Planned features
- Union types
- Compile time evaluation
- First-class-type based generics

## Documentation
This is subject to change as the language evolves.

### Hello World
Below is a sample Hello World program written in Orange using the `stdlib` package:
```
-[stdlib]
myModule::Module = (
    theSystemModule::Module = stdlib.system

    + main::(args:[]String)->Int = {
        stdlib.system.println("Hello, ")
        theSystemModule.println(" World!")
        return 0
    }
)
```
There are a couple idiomatic Orange things to notice about this Hello World example.

The first line `-[stdlib]` is a restriction tag that indicates that the `myModule` module only sees the `stdlib` package symbol from it's parent scope. In other words, it "imports" the `stdlib` package. This is more intuitive than the import systems of other languages, and generalizes to other symbols in a way that improves refactorability.

Next, notice that the `myModule` module definition is surrounded with parenthesis, while the `main` function definition is surrounded with braces. 

This is because the module definition is syntactically and semantically equivalent to a function's parameter list. Modules are a list of definitions, and so are function parameter lists. They mean the same thing, so they look the same.

Also notice the definition `theSystemModule::Module = stdlib.system`. In Orange, **everything is first class**. Types, modules, packages, functions, everything. `theSystemModule::Module = stdlib.system` is simply declaring another symbol for the `stdlib.system` module. When the code is compiled, any call to `stdlib.system.println` and `theSystemModule.println` will call the same function.

### Comments
```
commentExample::Module = (
    // Comments in Orange start with a '//' token and end at a new line
    // Code within a comment is not used by the compiler
    + aFunction::()->() = {
        // stdlib.system.println("This won't be seen!")
    }
)
```

### Variables
```
variableExample::Module = (
    // Variables can be declared in modules
    globalVariable: Int = 5

    someFunction::()->() = {
        // Pattern is name : type = expression
        var: Char = 'd'

        // If expression is ommited, a zero-value expression is filled in
        willBeZero: Int // = 0

        // If the type is ommited, the type will be infered from the value
        someInt := 5

        // Use double colons to declare something constant
        pi::Real = 3.1415926
    }
)
```
### Types
```
// Module is a type, values are singleton namespaces
typesExample::Module = (
    // Some primitive type examples
    anInteger: Int = 4
    aReal: Real = 4.0
    aLetter: Char = '4'
    allFour: Bool = true
)
```
Address types can be made from other types by adding a `&` in front.
```
addressesExample::Module = (
    addrOfAnInt: &Int = null // A 64-bit address of an integer
    addrOfAddrOfInt: &&Int
)
```
Static arrays can be made by adding `[x]` where x is a constant time integer expression. Arrays are contiguous chunks of memory, not pointers like in C. Arrays know their length.
```
staticArrayExample::Module = (
    fourChars: [4]Char
    chessBoard: [8][8]Char // An array of arrays
)
```
Dynamic arrays are pointers to arrays. They can either point to arrays of a known length, or arrays of any length.
```
dynamicArrayExample::Module = (
    integerArrayAddr: &[10]Int  // A memory address of 10 integers
    anySizeArray: []Real        // A pointer to an array of reals of any size
)
```
Function types domain of parameters and a co-domain separated by the `->` token. Their values are equivalent to function pointers.
```
functionTypeExample::Module = (
    sqrt: (x:Real)->Real // This function takes a real input and produces a real output
)
```
### Blocks
### If
### For
### Switch
### Defer
### Functions
### External Symbols
### Scoping Control
### Modules
### Packages