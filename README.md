# Orng
Orng is a simple, modular general-purpose programming language for hobby programmers. Hobbyist programmers continuously modify their projects as living-breathing documents. Orng has many constructs that are more aligned with this type of programming.

[![Alt Text](https://github.com/Rakhyvel/Orng/blob/main/splash.png)](https://github.com/Rakhyvel/Orng/blob/rakhyvel_cleanup/splash.png?raw=true)

[Read the documentation here!](https://github.com/Rakhyvel/Orng/blob/main/documentation.md)

## Module and Package System
Orng features a package and module system which makes it easy to re-use and organize code. Modules and packages are first class in Orng, meaning they can be assigned to variables and passed around as parameters to functions.

Packages in Orng are simply folders/directories with a `.pkg.orng` manifest file, and `.orng` source code files. Package description is done using Orng itself, so there's no need to learn another complicated package management utility.

## Elegant Arithmetic Type System
Unlike most languages, Orng has structural type equivalence, which means two types are equivalent if they have the same structure. Types are also first class in Orng, meaning you can assign and pass them as values.

## Perfect Interoperability With C/C++ ABI
Orng compiles to C, and allows for C functions to be called from Orng code, offering perfect bidirectional interoperability with C. You can use pre-exisiting C libraries, or drop in Orng into your pre-exisiting C project.

## Planned Features
- [x] Inner functions, methods for product and sum data types
- [x] Default parameters, named arguments
- [x] Sum data types
- [x] 'Maybe' sum data types
- [x] Error sum data types
- [ ] Parametric types
- [ ] Interfaces/typeclasses/traits
- [ ] String interpolation
- [ ] Runtime constancy (immutability)
- [ ] Attributes
- [ ] Test suite
- [ ] Visual Studio language server
- [ ] LLVM code generation

### Maybe?
- [ ] Pattern matching
- [ ] Exponentiation
- [ ] Relational operator chaining
- [ ] Refinement types
- [ ] Quantifiers `some`, `all`, `none` for iterators