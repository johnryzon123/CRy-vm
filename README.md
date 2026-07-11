# CRy -

## A high performance programming and english like programming language(on the parser stage)

___

## Key Features

* **The UFN**: Cry supports symbols in names by using the Un-alnum-for-names(ufn) function
* **Supports names with spaces**: the language support spaces inside names instead of using the old school `_`
* **High performance lexer**: Not a single `<string.h>` is included in sources unless for the repl
* **Leak free engine**: The language is entirely leak-free, verified via **Valgrind**
* **Amazing line and column tracking**: it handles line and column counting perfectly, no manual counting needed

___

## Cons

* **Very simple math operators are available**
* **Has support on names but no support for variables/functions yet**
* **Doesn't have a proper parser and a vm yet**
* **No VM = No Standard Library**
* **Looks like it does nothing if not compiled with debug flags**
* **May contain hidden bugs**
* **Not tested on Windows**
* **The spaces in names may cause confusion so good luck**
* **Not reccomended for daily use, it doesn't even solve math yet**
___

## When you find a bug
Please report the bug through github issues or send it through my email `johnryzon2@gmail.com`
but I recommend to report it via github issues. I may also need testers from windows or other operating systems other than linux.

## Building the Project

The language is built via a `Makefile`

### Prerequisites
* **GCC(Default) or CLANG**
* **GNU Make**
* **Git**

### Build commands

to compile the program: `$ make`

to run the program:
    `$ make run` or
    `$ ./cry`

to compile the program with debug symbols enabled:
    `$ make debug`

## Why did I made another VM?
Long ago around 2024-2025, there was a VM named Ry2 for the Ry(Ry's for You) language but after some time,I got dependent on AI so now in 2026, I decided to make a whole new VM and syntax using C instead of C++.
I was cheating on Ry2 cause C++ got to much features such as shared_ptrs, classes and left Ry2 unoptimized. Now, I'm trying my best to stay away from ai slop while focusing on my studies.

I'm a grade 6 student living on the philippines,
I know that most of the children here are addicted to mobile games such as roblox and it's causing gunfights and all sorts of bad stuff there is.
I'm staying away from those habits and focusing on my studies and talents,
I have all sorts of talents such as solving rubik's cubes, playing piano, coding, drawing, desktop publishing and more but I' focusing on coding.

For anyone who sees this, please support my works but NEVER contribute to the Ry1 and Ry2 projects as they are restricted and abondoned. If you ever wanna contribute, see the future CONTRIBUTING file.
