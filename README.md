# Orng
Orng is a simple, modular general-purpose programming language for hobby programmers. Hobbyist programmers continuously modify their projects as living-breathing documents. Orng has many constructs that are more aligned with this type of programming. Those include:

## Module and Package System
Orng features a package and module system which makes it easy to re-use and organize code.

Modules and packages are first class in Orng, meaning they can be assigned to variables and passed around to functions. This is how imports are done.
```
myModule::Module = ( 
    -- import `system` module from `std` package as `sys`
    sys::Module = std.system

    main::(args:[]String)->!() = sys.println("Hello, World!")
)
```

Packages in Orng are simply folders/directories with a `.pkg.orng` manifest file, and `.orng` source code files. Package description is done using Orng itself, so there's no need to learn another complicated package management utility.

## Elegant Arithmetic Type System
Unlike most languages, Orng has structural type equivalence, which means two types are equivalent if they have the same structure. This is contrary to languages like C, where types are equivalent if they have the same name. Types are also first class in Orng, meaning you can assign and pass them as values.
```
testFn::()->() = {
    -- A 'typedef' in Orng:
    Vector::Type = (x:Real, y:Real)

    myPosition:Vector = (3, 4)
    yourPosition:(x:Real, y:Real) = myPosition -- This is allowed! Same types because same structure
}
```
Orng has sum types in the form of tagged unions. These act like both classic enums and unions in one type.
```
-- Fields in sum types without a specified type default to a void type. Acts as a regular enum
CardSuit::Type = <hearts, diamonds, clubs, spades>

-- Fields in sum types can have heterogenous types and data associated with them
PlayingCard::Type = <
    ace
    pipCard:(number:Int, suit:CardSuit)
    courtCard:(letter:Char, suit:CardSuit)
>
```
### Maybe Types
Tony Hoare called the null reference his 'billion dollar mistake'. There is no concept of a null reference in Orng. Instead, Orng uses a monadic Maybe Type, like in Zig, Haskell, or Rust. This allows for existence semantics to be statically checked, which increases security and readibility.
```
-- Either an Int, or nothing
x:?Int = 3
-- x is equivalent to:
x:<something:Int, nothing> = 3
```
### Error unions
Errors capture the idea that a function can either return a successful value, or an error. Errors are sum data types, with extra semantics.
```
-- Some possible errors a function may return
MyError::Type = <arithmeticError, typeError, computerOnFireError>

-- This function returns either a MyError sum type as an error, or an Int
myFunc::()->FileError!Int = 4

-- myFunc is equivalent to this function:
myFunc::()-><success:Int, arithmeticError, typeError, computerOnFireError> = 4
```

## Perfect Interoperability With C/C++ ABI
Orng compiles to C, and allows for C functions to be called from Orng code, offering perfect bidirectional interoperability with C. You can use pre-exisiting C libraries, or drop in Orng into your pre-exisiting C project.

## Planned Features
- [x] Default parameters, named arguments
- [x] Sum data types
- [x] Inner functions, methods for product and sum data type
- [x] Support for `maybe` monadic sum data types
- [x] Support for `error` monadic sum data types
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