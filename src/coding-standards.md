# Coding Standards
## Formatting
- 4 space indentation
- always have newlines before open brackets
    ```
    if (cond)
    {
        do something
        do another thing
    }
    ```
    instead of
    ```
    if (cond) {
        do something
        do another thing
    }
    ```
    - however, keep single line subscope bodes on the same line
        ```
        if (cond) { do something }
        ```
        instead of
        ```
        if (cond)
            do something
        ```
        or
        ```
        if (cond)
        {
            do something
        }
        ```
- no increase of nesting level at case statements

## Variables
- variable declarations allowed at any part of the code, generally right before first reference
- concise but clear naming preferred (i.e. abbreviations)
- use camelCase to delimit multi-word names (e.g. `int theVar;` instead of `int the_var;`)

## Functions
- `UpperCamelCase`/`PascalCase` for function names

## Types
- refrain from using plain `int`
- use `u32`, `u16`, `u8` for all unsigned types
- use `s32`, `s16`, `s8` for all signed types
- use `void*` for pointer to polymorphic data with no base type

## Project specific
### Common names

#### Generic
- integral iterator - `s32 i, j, k`
- index - `s32 idx`
- count - `s32 count`
- result code - `s32 res`
- value pair - `s32 a,b`
- character or character iterator - `char [*]c`

#### Specific
- index - `s32 <name>Idx`
- count - `s32 <name>Count`

#### Naming conventions
- current <full_name> - `<typename> curr<uppercase name>`
- previous <full_name> - `<typename> prev<uppercase name>`