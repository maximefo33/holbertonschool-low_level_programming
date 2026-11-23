# AI Memory Visualizer — Memory Maps

## 1. Project Overview

This project explores how memory is used and managed during C program execution.

The objective is to understand the relationship between:

- Stack memory and function calls.
- Recursive function calls and stack frames.
- Automatic storage duration.
- Dynamic memory allocation and deallocation.
- Pointers and pointer aliasing.
- Object lifetime.
- Memory leaks and invalid memory accesses.

The project uses small C programs to observe memory behavior, inspect source code, and analyze runtime results.

Valgrind is used to detect memory management errors and examine their effects.

## 2. Project Structure

```text
ai_memory_visualizer_valgrind_tracer/
│
├── README.md
│
├── analysis/
│   ├── memory_maps.md
│   ├── valgrind_analysis.md
│   └── crash_report.md
│
└── programs/
    ├── stack_example.c
    ├── heap_example.c
    ├── aliasing_example.c
    ├── crash_example.c
    └── Makefile
```

## 3. C Programs

The project contains four C programs. Each one demonstrates a different aspect of memory behavior.

### 3.1 stack_example.c — Stack Memory and Recursion

This program demonstrates how function calls use automatic storage duration.

It focuses on:

- Recursive function calls.
- Multiple active stack frames.
- Function parameters and local variables.
- Variable lifetime.
- Memory address reuse.
- The distinction between variables belonging to different functions.

The program uses `walk_stack()` to create recursive calls and `dump_frame()` to display information about local variables.

**Main objective:** Understand how recursive calls maintain separate local variables and how those variables cease to exist when their corresponding function calls return.

### 3.2 heap_example.c — Dynamic Memory Allocation

This program demonstrates dynamic memory allocation using `malloc()` and memory deallocation using `free()`.

It focuses on:

- Allocating structures dynamically.
- Allocating memory for structure members.
- Managing multiple heap allocations.
- Correct memory ownership.
- Releasing allocated memory.
- Detecting memory leaks.

The example illustrates how failing to release an allocated member can cause a memory leak, even when the structure containing its pointer is freed.

**Main objective:** Understand how dynamically allocated memory is managed and why every allocation must be released correctly.

### 3.3 aliasing_example.c — Pointer Aliasing and Use-After-Free

This program demonstrates how two pointers can reference the same dynamically allocated memory block.

It focuses on:

- Dynamic memory allocation.
- Pointer assignment.
- Pointer aliasing.
- Shared access to an allocation.
- Memory deallocation.
- Invalid memory accesses after `free()`.

The program assigns the address stored in pointer `a` to pointer `b`. Both pointers therefore refer to the same allocation.

After the allocation is released using `free(a)`, the program attempts to access the released memory through `b`.

**Main objective:** Understand why copying a pointer does not create a new allocation and why accessing memory after deallocation is invalid.

### 3.4 crash_example.c — NULL Pointer Dereference

This program demonstrates an invalid memory access caused by attempting to write through a NULL pointer.

It focuses on:

- Pointer initialization.
- Conditional memory allocation.
- Allocation failure or early return.
- NULL pointer handling.
- Invalid memory writes.
- Runtime crashes.

The allocation function returns `NULL` when the requested size is zero. The calling function subsequently attempts to access the returned pointer without checking whether it is valid.

**Main objective:** Understand why a pointer must be checked before dereferencing it and how an invalid memory access can cause a program to crash.

## 4. Compilation and Execution

The programs can be compiled individually or using the provided Makefile.

### 4.1 Compilation

From the `programs/` directory, use:

```bash
make
```

Alternatively, compile an individual program with GCC:

```bash
gcc -Wall -Wextra -Werror -pedantic -std=gnu89 -g \
    stack_example.c -o stack_example
```

Repeat the compilation command for the other source files when needed.

The `-g` option includes debugging information, which helps identify source locations during memory analysis.

### 4.2 Execution

Run the programs individually:

```bash
./stack_example
./heap_example
./aliasing_example
./crash_example
```

**Important:** `crash_example` is intentionally designed to perform an invalid memory access. Its abnormal termination is part of the exercise.

## 5. Memory Analysis with Valgrind

Valgrind is used to inspect memory behavior during program execution.

The Memcheck tool can help identify:

- Invalid memory reads.
- Invalid memory writes.
- Use of uninitialized values.
- Memory leaks.
- Accesses to memory after it has been freed.

Example command:

```bash
valgrind --leak-check=full --show-leak-kinds=all \
    ./stack_example
```

The same approach can be used with the other executables.

For the crash example:

```bash
valgrind --leak-check=full --show-leak-kinds=all \
    ./crash_example
```

The crash is expected. The purpose of the analysis is to identify the invalid access and understand its cause.

## 6. Analysis Documents

The `analysis/` directory contains the written observations and conclusions.

| File | Purpose |
|---|---|
| `memory_maps.md` | Analysis of stack memory, heap memory, pointer aliasing and object lifetimes. |
| `valgrind_analysis.md` | Examination of Valgrind results for the four C programs. |
| `crash_report.md` | Detailed analysis of the NULL pointer dereference and resulting crash. |

These documents connect the source code, memory concepts and observed runtime behavior.

## 7. Learning Objectives

By completing this project, the main learning objectives are to:

- Understand the difference between stack and heap memory.
- Identify the lifetime of automatic and dynamically allocated objects.
- Understand how recursive function calls create separate active function frames.
- Distinguish a pointer variable from the memory it references.
- Understand pointer aliasing and shared access to memory.
- Identify use-after-free errors and invalid memory accesses.
- Understand the importance of checking pointers before dereferencing them.
- Interpret Valgrind reports to identify memory management problems.
- Critically evaluate AI-generated explanations by comparing them with source code and execution results.

## 8. Conclusion

This project provides practical examples of memory behavior in C.

By examining stack frames, dynamic allocations, pointer aliasing and invalid memory accesses, it demonstrates how memory lifetime and pointer management affect program correctness.

The combination of source code inspection, program execution and Valgrind analysis helps develop a more precise understanding of memory management in C.