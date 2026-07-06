# CRy

A high performance programming and english like programming language(still on lexer stage)

___

## Key Features

* **The UFN**: Cry supports symbols in names by using the Un-alnum-for-names(ufn) function
* **Supports names with spaces**: the language support spaces inside names instead of using the old school `_`
* **High performance lexer**: Not a single `<string.h>` is included in sources
* **Leak free engine**: The language is entirely leak-free, verified via **Valgrind**
* **Amazing line and column tracking**: it handles line and column counting perfectly, no manual counting needed

___

## Cons

* **Doesn't have a parser and a vm yet**
* **Doesn't handle strings**
* **May contain hidden bugs**
* **Couldn't run from files for now**
___

## When you find a bug
Please report the bug through github issues

## Building the Project

The language is built via a `Makefile`

### Prerequisites
* **GCC(Default) or CLANG**
* **GNU Make**
* **Git**

### Build commands

to compile the program:
    ```bash
    $ make
    ```

to run the program:
    ```bash
    $ make run
    ```

or
    ```bash
    $ ./cry
    ```

to compile the program with debug symbols enabled:
    ```bash
    $ make debug
    ```

## Folder Structure

.
├── include - contains the declarations of functions
│   ├── lexer - contains lexer definitions
│   │   ├── lexer.h - contains lexer-specific function definitions
│   │   └── token.h - contains the token structure
│   └── utils - contains utility function definitions
│       ├── getline.h - the definition for the custom getline function
│       └── repl.h - definitions for the repl
├── LICENSE - license
├── Makefile - the "all-in-one" script that make uses
└── src - contains the sources of the language
    ├── lexer - contains the lexer implementations
    │   ├── lexer_api.h - the definitions of private lexer instances
    │   ├── lexer.c - main public function implementations
    │   ├── lexer_handlers.c - contains functions handling numbers, ufn, names, etc.
    │   └── lexer_utils.c - contains lexer utilities such as peek
    ├── main.c - the main entry point of the program
    └── utils - utility function implementations
        ├── getline.c - custom getline implementation
        └── repl.c - repl implementation
        
