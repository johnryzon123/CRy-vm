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

* **Doesn't have a proper parser and a vm yet**
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
