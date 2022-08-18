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

Packages in Orng are simply folders/directories with a `.pkg.orng` manifest file, and `.orng` source code files. Package management can be done with pre-existing utilities like Git. This also allows for source-code libraries, which are more in line with a hobbyist style of programming.

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

## Strong Compile-time Evaluation
Orng features a strong 

## Perfect Interoperability With C/C++ ABI

## What's Not In Orng

## Planned Features