# Memory Maps — AI Memory Visualizer

## 1. Project Overview

### 1.1 Objective

The objective of this analysis is to understand how memory behaves during C program execution.

The analysis focuses on:

- Stack frames and automatic storage duration.
- Recursive function calls.
- Heap allocation and deallocation.
- Pointer aliasing.
- Memory lifetime.
- Invalid memory accesses.

The analysis is based on source code inspection and normal program execution. AI-generated explanations are treated as hypotheses and are reviewed critically against the actual source code and observed behavior.

### 1.2 Environment

- Operating system: Windows
- Terminal: Git Bash (MINGW64)
- Compiler: GCC
- Compilation flags:
  `-Wall -Wextra -Werror -pedantic -std=gnu89 -g`

The programs `stack_example.c` and `aliasing_example.c` were compiled individually because the `make` command was not available in the Git Bash environment.

Valgrind was not executed because it was not available in the current environment.

---

## 2. Stack Memory Analysis

### 2.1 Program Overview

The `stack_example.c` program demonstrates how local variables behave during recursive function calls.

The program starts by calling `walk_stack(0, 3)` from `main()`.

The `walk_stack()` function calls itself recursively, increasing the `depth` parameter by one at each call, until it reaches the maximum depth of 3.

The `dump_frame()` function is used to observe local variables and their memory addresses.

It is called twice at each recursion level:

- `enter`: during the recursive descent.
- `exit`: during the return from recursive calls.

The program creates four recursive calls, from depth 0 to depth 3.

### 2.2 Recursive Stack Frames

The recursive calls follow this sequence:

| Call | Depth | Action |
|---|---:|---|
| 1 | 0 | Enter |
| 2 | 1 | Enter |
| 3 | 2 | Enter |
| 4 | 3 | Enter |
| 4 | 3 | Exit |
| 3 | 2 | Exit |
| 2 | 1 | Exit |
| 1 | 0 | Exit |

At the maximum recursion depth, four `walk_stack()` function calls are active simultaneously.

Each call has its own local variables and remains active while waiting for the next recursive call to return.

The recursive call is performed using:

    walk_stack(depth + 1, max_depth);

In C, function arguments are passed by value. The values are copied into the parameters of the new function invocation.

For example, when `walk_stack(1, 3)` calls `walk_stack(2, 3)`, the previous invocation keeps its original values:

- `depth = 1`
- `max_depth = 3`

The new invocation receives its own values:

- `depth = 2`
- `max_depth = 3`

The previous function call remains suspended until the new recursive call returns.

Each active invocation therefore maintains its own execution context and local variables.

When the deepest call finishes, the previous calls resume their execution in reverse order.

### 2.3 Local Variables and Lifetimes

The program contains two functions with different local variables.

**Variables belonging to `walk_stack()`:**

| Variable | Purpose | Lifetime |
|---|---|---|
| `depth` | Stores the current recursion level. | During the current function invocation. |
| `max_depth` | Stores the maximum recursion depth. | During the current function invocation. |
| `marker` | Stores the current depth multiplied by 10. | During the current function invocation. |

Each recursive call has its own instances of these variables.

The values of `marker` are:

| Depth | marker |
|---|---:|
| 0 | 0 |
| 1 | 10 |
| 2 | 20 |
| 3 | 30 |

These variables remain alive while their corresponding function calls are active. They cease to exist when their respective calls finish.

**Variables belonging to `dump_frame()`:**

| Variable | Purpose | Lifetime |
|---|---|---|
| `label` | Indicates whether the function is called during entry or exit. | During the current function invocation. |
| `depth` | Identifies the current recursion level. | During the current function invocation. |
| `local_int` | Stores the value `100 + depth`. | During the current function invocation. |
| `local_buf` | A local character array of 16 elements. | During the current function invocation. |
| `p_local` | A pointer containing the address of `local_int`. | During the current function invocation. |

The values of `local_int` are:

| Depth | local_int |
|---|---:|
| 0 | 100 |
| 1 | 101 |
| 2 | 102 |
| 3 | 103 |

The first element of `local_buf` contains a character from A to D, depending on the recursion depth.

The second element is initialized with the null character `'\0'`.

The pointer `p_local` points to `local_int`. It does not allocate additional memory.

When `dump_frame()` returns, its local variables cease to exist.

A subsequent call creates new local variables, even if some memory addresses are reused.

### 2.4 Memory Map at Maximum Recursion Depth

The following diagram represents the active recursive calls when the program reaches depth 3, after the `enter` call to `dump_frame()` has returned.

It is a conceptual representation of the active function calls, not an exact physical memory layout.

    STACK

    +-----------------------------+
    | main()                      |
    +-----------------------------+
    | walk_stack() - depth 0      |
    | depth = 0                   |
    | max_depth = 3               |
    | marker = 0                  |
    +-----------------------------+
    | walk_stack() - depth 1      |
    | depth = 1                   |
    | max_depth = 3               |
    | marker = 10                 |
    +-----------------------------+
    | walk_stack() - depth 2      |
    | depth = 2                   |
    | max_depth = 3               |
    | marker = 20                 |
    +-----------------------------+
    | walk_stack() - depth 3      |
    | depth = 3                   |
    | max_depth = 3               |
    | marker = 30                 |
    +-----------------------------+

Each recursive call has its own `depth`, `max_depth` and `marker` objects.

The four `marker` variables remain alive simultaneously while the deepest recursive call is active.

The `dump_frame()` function creates a temporary additional function frame whenever it is called. This frame disappears when `dump_frame()` returns.

    HEAP

    No dynamic memory allocation is performed by this program.

Note: This diagram represents the common stack-frame model used to explain function calls. The C standard specifies object lifetimes but does not require a particular physical stack layout.

### 2.5 Observed Memory Addresses

The following addresses were obtained during the normal execution of `stack_example.c` in the current environment.

| Depth | local_int address | local_buf address | marker address |
|---|---|---|---|
| 0 | `0061FEC8` | `0061FEB8` | `0061FEFC` |
| 1 | `0061FE98` | `0061FE88` | `0061FECC` |
| 2 | `0061FE68` | `0061FE58` | `0061FE9C` |
| 3 | `0061FE38` | `0061FE28` | `0061FE6C` |

The address stored in `p_local` is the same as the address of `local_int`, because `p_local` is initialized with `&local_int`.

In this execution, the addresses of `local_int` and `local_buf` were also reused between the `enter` and `exit` calls at the same recursion depth.

These addresses correspond only to the observed execution environment. They are not guaranteed to remain identical in another execution.

### 2.6 Stack Memory Observations

Each recursive call to `walk_stack()` has its own local variables, including `depth`, `max_depth` and `marker`.

Function arguments are passed by value. Therefore, when a new recursive call is created, it receives its own parameter values.

The previous function call keeps its original values while waiting for the recursive call to return.

The local variables of `dump_frame()` have a shorter lifetime. They cease to exist when `dump_frame()` returns because the function execution has ended.

Each new call to `dump_frame()` creates new local variables.

However, the same memory addresses may be reused by subsequent function calls.

A reused memory address does not mean that the new variable is the same object as the previous variable. The previous object's lifetime has already ended.

---

## 3. Heap Memory and Pointer Aliasing Analysis

### 3.1 Program Overview

File: `programs/aliasing_example.c`

The program demonstrates:

- Dynamic memory allocation using `malloc()`.
- Two pointers referencing the same allocation.
- Memory deallocation using `free()`.
- Invalid memory accesses after deallocation.

The program uses the `make_numbers()` function to allocate and initialize an array of integers.

### 3.2 Heap Allocation

The function `make_numbers()` allocates memory dynamically.

The allocation is performed using:

    arr = (int *)malloc((size_t)n * sizeof(int));

The value of `n` is 5, so the allocation reserves enough space for five integers.

The allocation size is:

    5 * sizeof(int)

The function checks whether the allocation was successful.

If `malloc()` returns `NULL`, the function returns `NULL` to indicate an allocation failure.

Otherwise, the `for` loop initializes the allocated array.

The resulting values are:

| Index | Value |
|---|---:|
| 0 | 0 |
| 1 | 11 |
| 2 | 22 |
| 3 | 33 |
| 4 | 44 |

The function then executes:

    return arr;

This returns the pointer value containing the address of the allocated memory.

When `make_numbers()` returns, its local pointer variable `arr` ceases to exist.

However, the heap allocation remains valid because returning the pointer does not deallocate the memory.

In `main()`, the returned pointer value is assigned to `a`:

    a = make_numbers(n);

The pointer `a` now provides access to the existing heap allocation.

No second allocation or copy of the array is performed.

The allocation remains alive until it is explicitly released with `free()`.

### 3.3 Pointer Aliasing

In `main()`, the following assignment is performed:

    b = a;

This operation copies the address stored in `a` into `b`.

It does not allocate another memory block and does not copy the contents of the array.

Both pointers therefore reference the same heap allocation.

Memory map before deallocation:

    STACK                         HEAP

    +------------------+
    | a = address X    |-------+
    +------------------+       |
                               |
    +------------------+       |
    | b = address X    |-------+---->
    +------------------+            |
                                    v
                         +---------------------+
                         | Heap allocation X   |
                         |                     |
                         | 0 | 11 | 22 | 33 | 44 |
                         +---------------------+

Both pointers refer to the same allocated memory block.

This situation is called pointer aliasing.

If the array is modified through one pointer, the modification is visible through the other pointer because both refer to the same memory location.

For example, before deallocation:

    b[3] = 1234;

The value can also be observed through:

    a[3];

The result is `1234` because both pointers reference the same array element.

During the normal execution, the program also displayed identical addresses for `a` and `b`.

### 3.4 Memory Deallocation

The program executes:

    free(a);

This releases the heap allocation previously created by `malloc()`.

The local pointer variables `a` and `b` do not disappear immediately because they belong to `main()`.

However, the allocation they referenced has been deallocated.

According to the C standard, the value of a pointer becomes indeterminate when the object it points to reaches the end of its lifetime.

Therefore, neither pointer can safely be evaluated or used to access the released allocation.

The program attempts to use pointer `b` after deallocation.

These operations include:

- Displaying the pointer `b`.
- Reading `b[2]`.
- Writing to `b[3]`.
- Reading `b[3]` after the invalid write.

The program may appear to work and display previous values, but this behavior is not guaranteed.

This is a use-after-free error, not a memory leak.

The allocation was explicitly released with `free(a)`. The problem is that the program subsequently attempts to use the released memory.

### 3.5 Invalid Memory Accesses

The following instructions occur after `free(a)`.

| Source line | Instruction | Problem |
|---|---|---|
| 40 | `printf()` using `b` | Evaluates the indeterminate pointer value after deallocation. |
| 42 | Reading `b[2]` | Attempts to read from released memory. |
| 44 | Writing `b[3]` | Attempts to write to released memory. |
| 45 | Reading `b[3]` | Attempts another read from released memory. |

All these operations occur after the allocation's lifetime has ended.

The read and write operations are examples of use-after-free.

The pointer display at line 40 is also problematic because the pointer value has become indeterminate. However, it does not perform the same kind of heap-memory dereference as lines 42, 44 and 45.

Valgrind Memcheck is designed to detect invalid reads and writes involving deallocated memory. It can report the location of an invalid access and information about the associated allocation.

No Valgrind report is included in this analysis because Valgrind was not executed in the current environment.

### 3.6 Runtime Observations

During the normal execution, the program displayed the following output:

    aliasing_example: aliasing and use-after-free (Valgrind should report it)
      a=00C94F40 b=00C94F40 a[2]=22 b[2]=22
      after free(a): b=00C94F40 (dangling)
      reading b[2]=22
      wrote b[3]=1234

The program completed without displaying a segmentation fault.

However, this does not mean that its memory accesses were valid.

The value `22` was still displayed after the allocation had been released.

This can happen because freeing memory does not necessarily erase its previous contents immediately.

The memory manager may keep the released memory available for later reuse.

Similarly, the program appeared to successfully write and display the value `1234`.

These results are observations from one execution only. They do not guarantee that the same behavior will occur in another execution.

All accesses after deallocation have undefined behavior, regardless of whether the program crashes.

---

## 4. Critical Review of AI-Generated Explanations

### 4.1 Identified AI Inaccuracy

During the analysis of `stack_example.c`, an initial AI-generated explanation incorrectly associated the variables `local_int`, `local_buf` and `p_local` with each recursive `walk_stack()` call.

The explanation suggested that these variables were independently created and maintained by each recursive level.

### 4.2 Why the Explanation Was Incorrect

The source code shows that `local_int`, `local_buf` and `p_local` are declared inside the `dump_frame()` function, not inside `walk_stack()`.

The variables belonging to `walk_stack()` are:

- `depth`
- `max_depth`
- `marker`

The variables belonging to `dump_frame()` are:

- `label`
- `depth`
- `local_int`
- `local_buf`
- `p_local`

The execution order also proves that the two function frames have different lifetimes.

At each recursion level, `walk_stack()` first calls:

    dump_frame("enter", depth);

This function finishes before `walk_stack()` performs the next recursive call.

Therefore, the local variables of this `dump_frame()` invocation no longer exist when the next recursive `walk_stack()` call is active.

### 4.3 Corrected Explanation

Each invocation of `walk_stack()` has its own local variables and parameters.

These variables remain alive while the corresponding recursive call is active.

The `dump_frame()` function is called separately during the entry and exit phases of each recursion level.

Its local variables only exist during the execution of each individual `dump_frame()` invocation.

When `dump_frame()` returns, its local variables cease to exist.

A later call creates new local variables, even if the compiler reuses the same memory addresses.

The original explanation was corrected by checking where the variables were declared in the source code and following the actual order of function calls and returns.

### 4.4 Lessons Learned

AI-generated explanations must be treated as hypotheses rather than verified facts.

During this analysis, checking the source code revealed an incorrect assumption about which function owned certain local variables.

To avoid similar mistakes, memory analysis should include:

- Checking the function in which each variable is declared.
- Following the actual execution order.
- Distinguishing between a variable's lifetime and its memory address.
- Checking whether function calls are still active or have already returned.
- Comparing theoretical explanations with observed program behavior.

A reused memory address does not prove that an object has remained alive or that it is the same object as