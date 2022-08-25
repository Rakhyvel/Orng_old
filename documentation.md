# Documentation
## Getting Started with Hello World
The following is an example of a Hello World program written in Orng.
```
-- Inline comments use double dashes
myModule::Module = (
    -- Import the system module from the std package as sys
    sys::Module = std.system
    
    main::(args:[]String)->!() = sys.println("Hello, World!")
)
```

## Variable Declarations, Definitions, and Scope
Variables are defined using their name, type, and an initializing definition.
```
x:Int = 4
```
Declarations can omit the type, and it will be infered from the right-hand-side of the assignment if possible.
```
-- Variable x is assumed to be of type Int
x := 4
```
Declarations can omit the initializing value, and the default value will be given.
```
-- Variable x is of type Int, given default value of 0
x:Int
```
Variables cannot be shadowed.
### External Declaration Modifiers
External variables are variables that do not yet exist, but will during link-time. Variable declarations can be marked as external with the `?` modifier. If no square brackets follow the `?`, the name of the variable will be used when interfacing with external code.

External variables may be compile-time constant and not have a definition
```
-- There will be a function called sin that takes a real number and returns a real number at link-time
sin?::(x:Real)->Real
```
Sometimes external names are awkward to use with Orng's module system. You can use square brackets after the `?` to give the external name, while the original name of the variable will be used without Orng.
```
sdl::Module = (
    -- These two symbols refer to the same external function
    SDL_Init?::()->()
    init?[SDL_Init]::()->()
)

-- Compare:
sdl.SDL_Init()
-- with:
sdl.init()
```
#### External Types
You can provide a definition of a type for Orng to reason with.
```
Rect1?[SDL_Rect]::Type
Rect2?[SDL_Rect]::Type = (x:Int32, y:Int32, w:Int32, h:Int32)

rectA:Rect1                     -- Orng cannot reason about this type, cannot access fields, cannot instantiate
rectB:Rect2 = (0, 0, 100, 100)  -- Orng can reason about this type!
```

### Restriction Declaration Modifiers
You can restrict which symbols from higher up in the symbol tree the declared variable can use in it's type and definition. This is useful for modules, packages, and functions.
```
myModule -[std, sdl, apricot]::Module = (
    -- Can only use std, sdl, and apricot from parent scope in this module
)
```

## Types
### Primitive Types
There are a few primitive, external types in Orng defined at program-level scope for each Orng program.

| Type Name | C Equivalent | Description                             | Literals                                                                               |
|-----------|--------------|-----------------------------------------|----------------------------------------------------------------------------------------|
| Bool      | int8_t       | Boolean true/false value                | `true`, `false`                                                                        |
| Char      | char         | Character on the system, usually 8 bits | '[_a-zA-Z0-9]'                                                                         |
| Int8      | int8_t       | 8 bit signed integer                    | [0-9]\*, 0x[a-fA-F0-9]\*, 0b[0-1]\*                                                    |
| Int16     | int16_t      | 16 bit signed integer                   | [0-9]\*, 0x[a-fA-F0-9]\*, 0b[0-1]\*                                                    |
| Int32     | int32_t      | 32 bit signed integer                   | [0-9]\*, 0x[a-fA-F0-9]\*, 0b[0-1]\*                                                    |
| Int64     | int64_t      | 64 bit signed integer                   | [0-9]\*, 0x[a-fA-F0-9]\*, 0b[0-1]\*                                                    |
| Int       | int64_t      | Word size on machine, usually 64 bits   | [0-9]\*, 0x[a-fA-F0-9]\*, 0b[0-1]\*                                                    |
| Real32    | float        | 32 bit floating point real number       | [0-9]*(.[0-9])?                                                                        |
| Real64    | double       | 64 bit floating point real number       | [0-9]*(.[0-9])?                                                                        |
| Real      | double       | Word size on machine, usually 64 bits   | [0-9]*(.[0-9])?                                                                        |

There are a few types in Orng that have no C equivalent, and whose values must be compile-time constant.

| Type Name | Description                                                                                       |
|-----------|---------------------------------------------------------------------------------------------------|
| Type      | An data type in Orng                                                                              |
| Module    | A collection of comptime constant singleton definitions                                           |
| Package   | A collection of comptime constant singleton definitions defined in files in the package directory |

### Compile-Time Constants
Types can be marked as compile-time constant with the `:` prefix token. This means that their values must be known at compile-time, rather than run-time.
```
x::Int = 4
y::Real = 4.5 + 4 -- This will be collapsed to be the compile-time constant value
```
Functions that return a compile-time constant must have all compile-time constant parameters. Whenever they are called, their result is evaluated at compile-time. fdf
```
```
### Addresses
Address types represent the address of data in the computer's main memory. They are constructed using the prefix `&` token.
```
IntAddress::Type = &Int
```
Addresses cannot be implicitly cast to numerical types, but they can be cast explicitly.

The default value for an address is 0.

Let `A` and `B` be types. Then `&A <: &B` if and only if `A <: B`.
### Product Types
Product types are similar to structs, classes, or records. They are constructed with declarations surrounded by parenthesis, delimited by either a comma or a newline.
```
Vector::Type = (x:Real, y:Real)

Complex::Type = (
    re:Real
    im:Real
)
```

Compile-time constant fields do not necessarily need definitions so long as the product type is not coerced to a module. Compile-time constant fields are not generated, but are inherit to the type itself and are taken into account when checking for type equivelance.

Product types can be compared for equality and inequality. Two product type values are equal when all their corresponding fields are equal, and are inequal when one or more corresponding fields are inequal.
```
Complex::Type = (
    re:Real
    im:Real
)
x:Complex = (3, 4)
y:Complex = (3, 4)
z:Complex = (1, 3)

x == y  -- true
x == z  -- false
```

The default value of a product type is the default value of all fields.

For two product types `A` and `B`, then `A <: B` when they have the same number of fields, and for each field:
* The names of the fields are equal
* The types of the field from `A` is a subtype of the type of the field from `B`
* If any of the two fields is compile-time constant, the other must be as well, and the definitions must be equal in value.

#### Positional Field Product Type Literals
Values for product types can be constructed positionally, where values are given for fields in the same order as the fields are defined. There may be fewer values than field definitions, so long as all non-default fields must have a value. There may not be more values than field definitions.
```
Vector::Type = (x:Real, y:Real)

myVector:Vector = (3, 4)
```
Positional product literals have an undefined type by default, and must be coerced to a type either with an assignment, definition, function argument, literal argument, or cast.
```
myVector:Vector = (3, 4)        -- Ok, type resolved from declaration
myVector = (3, 4)               -- Ok, type resolved from assignment
someFn::(v:Vector)->() = {}
someFn((3, 4))                  -- Ok, type resolved from function call argument
VectorType::Type = (v:Vector)
newVector:VectorType = ((3, 4)) -- Ok, type resolved from product type literal
otherVector := (3, 4):Vector    -- Ok, type resolved from cast


badVector := (3, 4)             -- Not ok, cannot resolve type
```
#### Named Field Product Type Literals
Values for product types can also be given by name. The order of the names does not matter. There may be no duplicate fields given. All fields without an explicit default value must be given a value. Field names must exist in the product type.
```
Vector::Type = (x:Real, y:Real)

myVector:Vector = (.y=4, x.=3)
```
Like positional product literals, named product literal must be coerced to a type somehow.
#### Default Parameters
Non-compile-time constant typed fields can be given a default definition. This overrides the fields implicit default value.
```
Vector1::Type = (x:Real, y:Real)        -- Only implicit defaults values
Vector2::Type = (x:Real=3, y:Real=4)    -- Both given explicit default values

vec1a:Vector1                           -- Given implicit default value (0, 0):Vector1
vec1b:Vector1 = (3, 4)                  -- Literal must give value for all fields without default value

vec2a:Vector2                           -- Given implicit default value (3, 4):Vector2
vec2b:Vector2 = (2)                     -- Given value (2, 4):Vector2
```
#### Compile-Time Constant Product Type Fields
Fields that are compile-time constant are intrinsic to the type itself. They are not generated out, and instead are inlined whenever they are accessed.
```
MyStruct::Type = (
    arraySize::Int = 4
    myArray:[arraySize]Real -- Will generate as an array of 4 reals
)

x:MyStruct
std.debug.assert(x.arraySize == 4)
```
Compile-time constant fields can also be accessed using the type expression.
```MyStruct::Type = (
    arraySize::Int = 4
    myArray:[arraySize]Real -- Will generate as an array of 4 reals
)

std.debug.assert(MyStruct.arraySize == 4)
```
#### Compile-Time Constant Methods
Compile-time constant functions that take in an address to it's own type as the first parameter can be used to create a method.
```
Car::Type = (
    numWheels:Int
    color:String

    print::(self:&Car)->() = {
        std.system.println("cas has %d wheels, is the color %s", self.numWheels, self.color)
    }
)

-- Notice the type is an address to the car
myCar:&Car = new Car(4, "red")
-- First argument is implicitly given as `myCar`, since first parameter's type matches the address to it's type
myCar.print()
-- This also works, and is equivalent
Car.print(myCar)
```
### Arrays
Arrays are product types of a length of the array, and the address to the first element. They can be constructed by surrounding a compile-time constant length with square brackets before the element data type.
```
fourInts:[4]Int

x::Int = 4
y::Int = 23
comptimeEvalSizeStr:[x + y - 3]Char
```
Arrays can optionally be given no size, and the size may change throughout runtime.
```
unknownSize:[]Int = giveRandIntArray()
```
Arrays have two fields. They are `length`, and `data`. Length is an integer representing the length of the array. Data is the memory address of the first element in the array.
```
myArr:[10]Real

myArrLength:Int = myArr.length
myArrData:&Real = myArr.data
```

The default value of an array is the an array with no length, and a data address of 0.

For two arrays `A` and `B`, then `A <: B` when:
* The element data types of `A` are a subtype of the element data types of `B`.
* If `B` has a defined length, the length of `B` is equal as an integer to the length of `B` as an integer.

#### Slices
Slices are limited view of an array from an inclusive lower-bound, to an exclusive upper-bound. They are zero-indexed as if they were a separate array themselves.
```
myArr:[10]Int
mySlice := myArr[2..5]  -- Slice of the array from index 2 of myArr, up to and not including index 5
```
Slices can leave off the lower-bound, upper-bound, or both. If the lower-bound is left off, it defaults to 0. If the upper-bound is left off, it defaults to the runtime length of the array.
```
myArr:[10]Int
firstFive := myArr[..5]
lastFive := myArr[5..]
copyArr := myArr[..]
```
It is not illegal to use bounds that exceed the length of the original array, or bounds that are below 0. However, the upper-bound must be greater than or equal to the lower-bound.
#### Strings
Strings in Orng are arrays of characters. They can be constructed using double quotes. Strings literals are not null terminated by default. You can use the '\0' character at the end to add a null terminator when working with external C code.
```
myStr:[]Char = "Hello, World!"
myCharArr:String = myStr

myStrZ:[]Char = "Hello, World!\0"
myCharArrZ:String = myStrZ
```
### Sum Types
Orng has support for tagged unions/heterogenous enums, called sum types in Orng. They can be constructed with a list of definitions delimited by either a comma or a newline, and surrounded by angle brackets. For sum-type field definitions only, if the type is omitted, the void type is infered. Sum types enclose a new type scope. Multiple fields may have the same type.
```
-- With explicit void types
CardSuit1::Type = <
    hearts:()
    diamonds:()
    clubs:()
    spades:()
>

-- With implicit void types
CardSuit2::Type = <
    hearts
    diamonds
    clubs
    spades
>
```
Sum types can have heterogenous field types.
```
IntOrBool::Type = <
    int:Int
    bool:Bool
>
```

Two sum types are equal when they have the same field name and type.
```
IntOrBool::Type = <
    int:Int
    bool:Bool
>

x:IntOrBool = IntOrBool.int
x.int = 5

y:IntOrBool = IntOrBool.int
y.int = 6

z:IntOrBool = IntOrBool.bool

x == y      -- true, even through x.int == y.int is false
x == z      -- false
```

The default value for a sum type is the default value for the type of the first field in the sum type.

Given two sum types `A` and `B`, `A <: B` when all definitions in `A` have a corresponding definition in `B` with the same field name and type that is equivalent. Order does not matter.
#### Sum Type Literals
Sum type values can be constructed using sum type literals with the field and type surrounded in angle brackets. The default value for the type is given.
```
IntOrBool::Type = <
    int:Int
    bool:Bool
>

x:IntOrBool = <int:Int>
x:IntOrBool = <bool:Bool>
```

Sum literals for fields with void type can omit the type.
```
CardSuit::Type = <
    hearts
    clubs
    diamonds
    spades
>

myCardSuit:CardSuit = <hearts>
```

Sum literals can also be created using the dot operator on a sum literal type.
```
IntOrBool::Type = <
    int:Int
    bool:Bool
>

x:IntOrBool = IntOrBool.int
y:IntOrBool = IntOrBool.bool
```
#### Sum Type Coercion
Non-sum type values may be coerced up to a sum-type in cases of declaration and assignment when there is a field with that type. If there are multiple fields with the type, the first one that matches will be used.
```
IntOrBool::Type = <
    int:Int
    bool:Bool
>

x:IntOrBool = false -- Will be coerced to <bool:Bool>
```
Sub-sum type values will be coerced up to a super-sum type.
```
-- Super type
IntOrBoolOrChar::Type = <
    int:Int
    bool:Bool
    char:Char
>
-- Sub type
IntOrBool::Type = <
    int:Int
    bool:Bool
>
x:IntOrBoolOrChar = IntOrBool.int -- Subtype, will be coerced up
```
The data of a sum-type can be accessed using the dot operator and the field name. Will panic in debug mode if the field is not active.
```
IntOrBool::Type = <
    int:Int
    bool:Bool
>
x:IntOrBool = 5
y:Int = x.int + 8
-- x.bool causes panic in debug mode, field is not active at this point
```
#### Union Operator
Sum types can be unioned together using the `||` operator. Field names may conflict so long as the types are *equal* (that is, equivalent both ways). The fields of the left sum type will be the first fields in the resulting type, followed by the fields of the right side that are not already included in the left type.
```
IntOrBool::Type = <
    int:Int
    bool:Bool
>
IntOrChar::Type = <
    int:Int
    char:Char
>

-- The following two types are equivalent
IntOrBoolOrChar1::Type = <
    int:Int
    bool:Bool
    char:Char
>
IntOrBoolOrChar2::Type = IntOrBool || IntOrChar
```
#### Maybe Sum Types
Maybe types represent the idea that data may exist, or may not. They are constructed using the prefix `?` type operator. The resulting sum type has two fields, a field called `nothing` with a void type, and a field called `something` with the base type.
```
-- The following two types are equivalent
MaybeInt1::Type = <nothing, something:Int>
MaybeInt2::Type = ?Int

x:MaybeInt1 = 5
y:MaybeInt2 = <nothing>
z:?Int      = 5
```
The postfix `?` value operator is equivalent to doing `.something`, and is used to extract the value from a maybe type.
```
x:?Int = 5
y:Int  = x?
```
#### Error Sum Types
Error sum types capture the idea that a process can either fail in some way, or be successful. Error types can be constructed with the `!` binary operator, where the left is a sum type of possible errors, and the right type is the successful type. The binary `!` type operator is equivalent to a sum type union.
```
SomeErrors::Type = <error1, error2, error3>

-- The following two types are completely equivalent
ErrorProneInt1::Type = SomeErrors!Int
ErrorProneInt2::Type = <success:Int> || SomeErrors
```
The left side of the `!` operator can be left out in the case of a function codomain type. The error set will be infered from any sum literals not found in the base type returned from the function definition.
```
SomeErrors::Type = <error1, error2, error3>

-- Function codomain infered to be <success:Int, error1, error3>
myFunc::(x:Int)->!Int =
    if x == 0 {
        return SomeErrors.error1
    } else if x == 1 {
        return SomeErrors.error3
    } else {
        return x
    }
```
### Functions
Functions allow parameterization of values. Function types can be constructed using the `->` binary type operator. The left side is the domain, and must be a product type of parameters. The right type is the codomain, and is the type returned when the function is called.
```
add::(x:Int, y:Int)->Int = x + y
sub::(x:Int, y:Int)->Int = x - y
left::(x:Int, y:Int)->Int = x
```
Compile-time constant function typed values are generated out as proper functions. Non-compile-time constant function typed values act as function pointers.

Two function typed values are equal when the address of the function they point to is the same.
```
func1::(x:Int)->Int = x + 5
func2::(x:Int)->Int = x + 5

x := func1
y := func1
z := func2

x == y  -- true, same function
x == z  -- false, even though functions are similar, not equal
```
#### Positional Arguments
Functions can be given arguments positionally in the same order as their parameters. There may be fewer arguments than function parameters, so long as all non-default parameters must have a corresponding argument. There may not be more arguments than parameters.
```
myFunc:(x:Int, y:Int, z:Int)->Int = x + y + z

myFunc(3, 4, 5)
```
#### Named Field Product Type Literals
Function arguments can also be passed by name. The order of the names does not matter. There may be no duplicate names given. All parameters without an explicit default value must be given an argument. Parameters names must exist in the domain of the function.
```
myFunc:(x:Int, y:Int, z:Int)->Int = x + y + z

myFunc(.z=3, .y=4, .x=5)
```
Like positional product literals, named product literal must be coerced to a type somehow.
#### Default Parameters
Non-compile-time constant typed parameters can be given a default definition. This overrides the parameter's implicit default value.
```
add::(x:Int=3, y:Int=4) = x + y

add()   -- given default parameters (3, 4), returns 7
```
#### Inner Functions
Functions can be defined inside other functions. The are scoped to just outside the outermost function's scope. Like all compile-time constants, they can be used before they are techinally defined.
```
z::Int = 5
func1::()->() = {
    x:Int = func2(3)

    func2::(y:Int)->Int = {
        -- x is not visible here
        -- z is visible here
        return y + z
    }
}
```

## Value Operators
Below is a list of operators in order of lowest precedence to highest.

| Syntax       | Operand Types                                               | Operation Type                                             | Description                                                                       |
|--------------|-------------------------------------------------------------|----------------|-------------------------------------------------------------------------------------------------------------------------------|
| a = b        | `typeof` b <: `typeof` a                                    | if `typeof` a <: `typeof` b {`typeof` b} else {`typeof` a} | Assignment                                                                        |
| a \|\| b     | `typeof` a <: Bool; `typeof` b <: Bool                      | Bool                                                       | Short circuiting boolean or                                                       |
| a && b       | `typeof` a <: Bool; `typeof` b <: Bool                      | Bool                                                       | Short circuiting boolean and                                                      |
| a \| b       | `typeof` a <: Int64; `typeof` b <: Int64                    | if `typeof` a <: `typeof` b {`typeof` b} else {`typeof` a} | Bitwise or                                                                        |
| a ~ b        | `typeof` a <: Int64; `typeof` b <: Int64                    | if `typeof` a <: `typeof` b {`typeof` b} else {`typeof` a} | Bitwise xor                                                                       |
| a & b        | `typeof` a <: Int64; `typeof` b <: Int64                    | if `typeof` a <: `typeof` b {`typeof` b} else {`typeof` a} | Bitwise and                                                                       |
| a == b       | `typeof` b <: `typeof` a                                    | Bool                                                       | Equality comparison                                                               |
| a != b       | `typeof` b <: `typeof` a                                    | Bool                                                       | Inequality comparison                                                             |
| a > b        | `typeof` a <: Real64; `typeof` b <: Real64                  | Bool                                                       | Greater-than comparison                                                           |
| a < b        | `typeof` a <: Real64; `typeof` b <: Real64                  | Bool                                                       | Less-than comparison                                                              |
| a >= b       | `typeof` a <: Real64; `typeof` b <: Real64                  | Bool                                                       | Greater-than-equal comparison                                                     |
| a <= b       | `typeof` a <: Real64; `typeof` b <: Real64                  | Bool                                                       | Less-than-equal comparison                                                        |
| a << b       | `typeof` a <: Int64; `typeof` b <: Int64                    | if `typeof` a <: `typeof` b {`typeof` b} else {`typeof` a} | Left shift                                                                        |
| a >> b       | `typeof` a <: Int64; `typeof` b <: Int64                    | if `typeof` a <: `typeof` b {`typeof` b} else {`typeof` a} | Right shift                                                                       |
| a + b        | `typeof` a <: Real64; `typeof` b <: Real64                  | if `typeof` a <: `typeof` b {`typeof` b} else {`typeof` a} | Addition                                                                          |
| a - b        | `typeof` a <: Real64; `typeof` b <: Real64                  | if `typeof` a <: `typeof` b {`typeof` b} else {`typeof` a} | Subtraction                                                                       |
| a * b        | `typeof` a <: Real64; `typeof` b <: Real64                  | if `typeof` a <: `typeof` b {`typeof` b} else {`typeof` a} | Multiplication                                                                    |
| a / b        | `typeof` a <: Real64; `typeof` b <: Real64                  | if `typeof` a <: `typeof` b {`typeof` b} else {`typeof` a} | Division                                                                          |
| a % b        | `typeof` a <: Real64; `typeof` b <: Real64                  | if `typeof` a <: `typeof` b {`typeof` b} else {`typeof` a} | Modulus                                                                           |
| a ^ b        | `typeof` a <: Real64; `typeof` b <: Real64                  | if `typeof` a <: `typeof` b {`typeof` b} else {`typeof` a} | Exponentiation                                                                    |
| !a           | `typeof` a <: Bool                                          | Bool                                                       | Boolean negation                                                                  |
| &a           |  -                                                          | &`typeof` a                                                | Address-of                                                                        |
| *a           | `typeof` a <: &T                                            | T                                                          | Dereference                                                                       |
| -a           | `typeof` a <: Real64                                        | `typeof` a                                                 | Scalar negation                                                                   |
| ~a           | `typeof` a <: Int64                                         | `typeof` a                                                 | Bitwise negation                                                                  |
| `sizeof` T   | `typeof` T <: Type                                          | Int64                                                      | Size of type in bytes                                                             |
| `try` a      | a is a sum type with a .success field                       | `typeof` a                                                 | if `a` is successful, `a.success`, else returns `a` from function as error        |
| `typeof` a   | -                                                           | Type                                                       | Compile-time type of expression                                                   |
| a `catch` b  | `typeof` b <: `typeof` a                                    | if `typeof` a <: `typeof` b {`typeof` b} else {`typeof` a} | if `a` is successful, `a.success`, else `b`                                       |
| a `orelse` b | `typeof` b <: `typeof` a                                    | if `typeof` a <: `typeof` b {`typeof` b} else {`typeof` a} | if `a != nothing`, `a.success`, else `b`                                          |
| a(b, c, ...) | `typeof` a <: T->U, arguments match parameters              | U                                                          | Function call of `a` with parameters `b`, `c`, etc.                               |
| a[b]         | `typeof` a <: []T, `typeof` b <: Int64                      | T                                                          | Index of array `a` at index `b`                                                   |
| a[b..c]      | `typeof` a <: []T, `typeof` b <: Int64, `typeof` c <: Int64 | []T                                                        | Slice of array `a` from index `b` inclusive to index `c` exclusive                |
| a.b          | a contains field b, b is an identifier                      | `typeof` a.b                                               | The field `b` of `a`                                                              |
| a?           | a has both something and nothing fields                     | `typeof` a.something                                       | if `a != nothing`, `a.something`, else panics                                     |
| a:T          | `typeof` T <: Type                                          | T                                                          | Type cast                                                                         |
| `new` T      | `typeof` T <: Type                                          | &T                                                         | Allocates memory on the heap using system allocator. Initialized with `default` T |
| `free` a     | `typeof` a <: &\*                                           | ()                                                         | Frees the given memory address with the default system allocator                  |
| `default` T  | `typeof` T <: Type                                          | T                                                          | Default value of the type `T`                                                     |
| T <: U       | T <: Type, U <: Type                                        | Bool                                                       | Compile-time subtype                                                              |
| a ++ b       | `typeof` a <: :String; `typeof` b<: :String                 | :String                                                    | Compile-time string concatenation                                                 |

### Operator Assignment
Binary operators, except for comparisons, can be combined with assignment.

| Syntax    | Meaning      |
|-----------|--------------|
| a \|\|= b | a = a \|\| b |
| a &&= b   | a = a && b   |
| a \|= b   | a = a \| b   |
| a &= b    | a = a & b    |
| a ~= b    | a = a ~ b    |
| a <<= b   | a = a << b   |
| a >>= b   | a = a >> b   |
| a += b    | a = a + b    |
| a -= b    | a = a - b    |
| a *= b    | a = a * b    |
| a /= b    | a = a / b    |
| a ^= b    | a = a ^ b    |

### Comparison chaining
All comparison operators except `!=` can be chained together.
```
0 < x < 5
-- is equivalent to: (0 < x) && (x < 5)

0 < x > -4 == y
-- is equivalent to: (0 < x) && (x > -4) && (5 == y)
```


## Control Flow and Allocations
### Block Expressions
Blocks are formed using the curly brackets `{` `}`. Blocks are a list of statements that are executed in order. Statements can either be seperated by a newline, or by a semicolon, but not both and not neither.
```
x:Int = {y:Int = 4; z:Int = y + 2; z - 5}
std.debug.assert(x == 1)

x2:Int = {
    y:Int = 4
    z:Int = y + 2
    z - 5
}
std.debug.assert(x == x2 == 1)
```
Blocks in Orng create a new scope.
```
{
    x:Int = 4
    {
        y:Int = 4
    }
    -- y is not visible outside this scope
}
```
### If 
If expressions are formed using the `if` keyword, a condition, and a block. The block is run if the condition is true.
```
if x == 4 {
    std.system.println("This will print only if x is equal to 4")
}
``` 
An else clause is optional by including the `else` keyword at the end of the first block. The else clause will run if the condition is false.
```
if x == 4 {
    std.system.println("This will print only if x is equal to 4")
} else {
    std.system.println("This will print only if x is not equal to 4")
}
```
Else clauses can either contain blocks, or other if expressions.
```
if x == 4 {
    std.system.println("This will print only if x is equal to 4")
} else if x == 3 {
    std.system.println("This will print only if x is equal to 3")
} else {
    std.system.println("This will print only if x is not equal to 4 and x is not equal to 3")
}
```
If expressions with an else clause evaluate to whichever clause is true at run-time. The types of both clauses must match or be coerceable.
```
y:Int = if x == 4 {0} else {1}
```
If expressions without an else clause have a maybe type wrapped around the type of the block.
```
y:?Int = if x == 4 {7}
```
### For
For loops are made up of four components. The pre-condition, the condition, the post-condition, and the body. The pre-condition is ran before the for loop is executed. Then, the condition is checked. If the condition is true, the body is run, and then the post-condition. Execution then jumps back to the condition check once more until the condition is false. Neither the body nor pre-condition are ran if the condition is false.
```
for i := 0; i < 10; i += 1 {
    std.system.println("%d", i)
}
-- Variables defined in pre-condition are not visible outside of the for loop
```
For loops can have an optional else clause. This will be ran if the condition is ever false. It will not be ran if the for loop is broken out of or returned from.
```
for i := 10; i >= 0; i -= 1 {
    std.system.println("%d", i)
} else {
    std.system.println("Liftoff!")
}
```
For loops can omit the pre-condition or the post-condition, or both.
```
-- Omitted pre-condition
i:Int = 0
for ; i < 10; i += 1 {
    std.system.println("%d", i)
}

-- Omitted post-condition
for i:Int = 0; i < 10; {
    std.system.println("%d", i)
    i += 1
}

-- Both ommitted
i:Int = 0
for ; i < 10; {
    std.system.println("%d", i)
    i += 1
}
```
For loops can optionally omit the semicolons if the pre-condition and post-condition are omitted.
```
-- This is called a while loop in a language like C or Java
i:Int = 0
for i < 10 {
    std.system.println("%d", i)
    i += 1
}
```
For loops with an else clause return a value. The types must match between the body and the else clause.
```
y:Int = 0
area:Int = 
    for x := 0; x < 10; x += 1 {
        y += 
    } else {
        0
    }
```
For loops without an else clause return a maybe type.
```
y:Int = 0
x:?Int = 
    for i := 0; i < 10; i += 1 {
        y += i; y
    }
```
### Case
Case expressions are formed using the `case` keyword, an expression, and a block containing a list of mappings. The expression is compared with each mapping argument, and if it is equal, that matching expression is executed.
```
x:Int = 4
case x {
    0       => std.system.println("x is 0")

    -- Mapping arguments can be non-compile-time constant
    f(x)    => std.system.println("f(x) = x")

    -- You can combine multiple mapping arguments with the , token. They are compared in order.
    2, 3, 4 => std.system.println("x was 2, 3, or 4")
}
```
Case expressions can have `else` mappings, which are only ran if none of the mapping arguments matched. Else mappings can be place in any order.
```
x:Char = 'a'
case x {
    isUpper(x) => std.system.println("x was uppercase")
    else       => std.system.println("x was weird!")
    isLower(x) => std.system.println("x was lowercase")
    isDigit(x) => std.system.println("x was a digit")
}
```
Case expressions with an else mapping evaluate to whichever mapping expression matches at runtime.
```
x:Char = 'a'
flippedX:Char = 
    case x {
        isUpper(x) => toLower(x)
        else       => '?'
        isLower(x) => toUpper(x)
        isDigit(x) => x
    }
```
Case expressions without an else mapping evaluate to a maybe type.
```
x:Char = 'a'
maybeFlippedX:?Char = 
    case x {
        isUpper(x) => toLower(x)
        isLower(x) => toUpper(x)
        isDigit(x) => x
    }
```
### Return
The `return` keyword halts the execution of a block, set's the return value of the function, and returns back to the caller function.
```
abs::(x:Real)->Real =
    if x > 0 {
        return x
    } else {
        return -x
    }
```
Return values are coerced to sum types
```
IntOrChar::Type = <int:Int, char:Char>

getSuit::(c:Char)->IntOrChar = {
    return c -- c is coerced up to <char:Char>
}
```
### Break
The `break` keyword breaks out of `for` loops.
```
for i := 0; i < 10; i += 1 {
    if i % 2 == 0 {
        break
    }
}
```
The else clause of a `for` loop is not executed if broken out of.
```
for i := 0; i < 10; i += 1 {
    if i % 2 == 0 {
        break
    }
} else {
    std.system.println("never ran if broken out of loop")
}
```
### Continue
The `continue` keyword jumps control flow in `for` loops back to the post-condition. The else clause may still be executed if continued
```
for i := 0; i < 10; i += 1 {
    if i % 2 == 0 {
        continue
    }
    std.system.println("Only print evens: %d", i)
}
```
### Unreachable
The `unreachable` keyword halts program execution immediately. In debug mode, prints out the callstack. Does not return an error.
```
x:Int = 4 ^ 2
if x < 0 {unreachable} -- assert that x is positive after squaring four
```
### Defer
The `defer` keyword appends control flow to be executed after the block exits. Defers are ran in reverse order.
```
{
    myArray := new [100]Int
    defer {free myArray; std.system.println("ran last")}

    std.system.println("ran first")
    defer std.system.println("ran fourth")

    std.system.println("ran second")
    defer std.system.println("ran third")
}
```
### New
The `new` keyword is used to allocate space in the computer's main memory. The space reserved is enough for the type given. The default value of the type is then assigned.
```
-- Allocate enough space for an integer
x:&Int = new Int
```
### Free
The `free` keyword frees memory on the system.
```
x:&Int = new Int
free x
```

## Program Structure
Conceptually, all Orng programs have one root symbol representing the program as a whole. This program symbol has all primitive type definitions, all packages given to the compiler, and all packages found using package closure. 
### Packages
Packages are defined in a folder using `.pkg.orng` file extenstion. They must be a `:Package` type, and have a product literal as their definition. Packages have the modules in their folder as children, and also any definitions defined in the package itself. Package children must be compile-time constant.

Packages can mark other packages as dependencies by putting them in the symbol restriction. They will then be loaded from the Orng/dependencies folder.
### Modules
Modules are singleton collections of compile-time constants. They contain the functions, types, and constants of a program.