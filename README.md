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
Below is a sample Hello World program written in Orange using the `stdlib` package.
```
-[stdlib]
myModule::Module = (
    + main::(args:[]String)->Int = {
        stdlib.system.println("Hello, World!")
        return 0
    }
)
```
### Comments
### Variables
### Types
### Blocks
### If
### For
### Switch
### Defer
### Functions
### Modules & Scoping
### Packages