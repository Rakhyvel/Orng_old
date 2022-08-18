# Orng
Orng is a simple, modular general-purpose programming language for hobby programmers. Hobbyist programmers continuously modify their projects as living-breathing documents. Orng has many constructs that are more aligned with this type of programming. Those include:

## Module and Package System
Orng features a package and module system which makes it easy to re-use and organize code.

Modules and packages are first class in Orng, meaning they can be assigned to variables and passed around to functions. This is how imports are done.
```
myModule::Module = (
    sys::Module = std.system -- import `system` module from `std` package as `sys`

    main::(args:[]String)->!() = sys.println("Hello, World!")
)
```

Packages in Orng are simply folders/directories with a `.pkg.orng` manifest file, and `.orng` source code files. This removes the need for a complex package manager. Package management can be done with pre-existing utilities like Git. This also allows for source-code libraries, which are more inline with a hobbyist style of programming.

## Elegant Arithmetic Type System

## Strong Compile-time Evaluation
Orng features a strong 

## Perfect Interoperability With C/C++ ABI

## What's Not In Orng

## Planned Features