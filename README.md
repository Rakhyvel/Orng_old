# Orange
Orange is a simple, modular general-purpose programming language for hobby programmers.

## Emphasis on code re-use
Waste less time configuring libraries and more time working on the projects you love.
- No messing with complicated build configurations each time you start a new project
- Package manifests use the same syntax as the rest of the language

## Low friction
As hobbyist programmers, our projects are living, breathing documents that change over time. Orange's syntax allows you to go from a:
```
myFunction::()->() = {
    someVar := 4
    someVar2 := '5'
    someVar3 := false
<span style="color:blue">
    {
        // A block of code
    }
</span>
}
```
```
myFunction::()->() = {
    someVar := 4
    someVar2 := '5'
    someVar3 := false

    -[someVar, someVar2]
    {
        // To a restricted block of code
    }
}
```
```
myFunction::()->() = {
    someVar := 4
    someVar2 := '5'
    someVar3 := false

    myOtherFunction := (someVar, someVar2)->{
        // To a lambda
    }
}
```
```
myFunction::()->() = {
    someVar := 4
    someVar2 := '5'
    someVar3 := false

    myOtherFunction::(someVar:Int, someVar2:Char)->() = {
        // To an inner function
    }
}
```
```
myFunction::()->() = {
    someVar := 4
    someVar2 := '5'
    someVar3 := false
}

myOtherFunction::(someVar:Int, someVar2:Char)->() = {
    // To an outer function
}
```
All with minimal code changes.

## Simple language
Things look like what they do, and do what they look like.
- No ambiguity!
- No hidden control flow
- No hidden allocation/deallocations

## Planned features
- Union types
- Compile time evaluation
- First-class-type based generics