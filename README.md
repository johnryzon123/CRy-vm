# CRy

## A high performance programming and english like programming language(on the parser stage)

---

## Key Features

- **The UFN**: Cry supports symbols in names by using the Un-alnum-for-names(ufn) function
- **Inline Comments**: You may put a comment inside names without affecting it, etc. `name1 (<-- a space is needed before '(')name1`
- **Supports names with spaces**: the language support spaces inside names instead of using the old school `_`
- **High performance lexer**: Not a single `<string.h>` is included in sources unless for the repl
- **Leak free engine**: The language is entirely leak-free, verified via **Valgrind**
- **Amazing line and column tracking**: it handles line and column counting perfectly, no manual counting needed

---

## Cons

- **Very simple math operators are available**
- **Has support on names but no support for variables/functions yet**
- **Doesn't have a proper parser and a vm yet**
- **No VM = No Standard Library**
- **Looks like it does nothing if not compiled with debug flags**
- **May contain hidden bugs**
- **Not tested on Windows**
- **The spaces in names may cause confusion so good luck**
- **Not reccomended for daily use, it doesn't even solve math yet**

---

## Performance (Benchmarks)

CRy is optimized for speed, the following metrics is created on linux while parsing a heavy 58,999 line expression file:

```bash
ryzon@johnryzonPc:~/Dev/Projects/CRy$ time ./cry tests/bench.ry
real    0m0.116s
user    0m0.099s
sys     0m0.017s
```

## Building the Project

The language is built using a standard `Makefile`

### Prerequisites

- **GCC(Default) or CLANG**
- **GNU Make**
- **Git**

### Build commands

to compile the binary: `$ make`

to run the program:

    ```bash
    $ make run
    # or
    $ ./cry
    ```

to run files:
`$ ./cry script.ry`

to compile the program with debug symbols enabled:
`$ make debug`

## Why did I made another VM?

Long ago around **2024–2025**, I built a VM named **Ry2** for the Ry ("Ry's for You") language.
Over time, I realized I was relying too much on **AI** and bloated C++ features like `std::shared_ptr` and heavy classes, which left the project unoptimized.

In **2026**, I decided to rewrite the entire thing in pure, low-level C to stay away from AI-generated slop, and focus on my studies.

I am a Grade 6 student living in the Philippines. While many kids around me are focused heavily on mobile games such as **Roblox**, I am spending my time to mastering my talents such as coding, solving Rubik's cubes, playing the piano, drawing, and desktop publishing.

## Bugs and contribution

Please report any bugs or compilation issues through the GitHub Issues or directly via email at johnryzon2@gmail.com (GitHub Issues are preferred). I am looking for Windows and macOS testers!

If you want to support my work, feel free to star the repo! Do not contribute to the Ry1 and Ry2 projects, as they are abandoned and restricted. If you want to contribute to CRy, keep an eye out for a future CONTRIBUTING.md file.
