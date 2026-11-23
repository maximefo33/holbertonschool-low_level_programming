# Memory Maps — AI Memory Visualizer

## 1. Project Overview

### 1.1 Objective

The objective of this analysis is to understand how memory behaves
during C program execution.

The analysis focuses on:

- Stack frames and automatic storage duration.
- Recursive function calls.
- Heap allocation and deallocation.
- Pointer aliasing.
- Memory lifetime.
- Invalid memory accesses.

The analysis is based on source code inspection and normal program
execution. AI-generated explanations are treated as hypotheses and
must be reviewed critically.

### 1.2 Environment

- Operating system: Windows
- Terminal: Git Bash (MINGW64)
- Compiler: GCC
- Compilation flags:
  `-Wall -Wextra -Werror -pedantic -std=gnu89 -g`

The programs were compiled individually because the `make`
command was not available in the Git Bash environment.

---

## ## 2. Stack Memory Analysis

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

### 2.3 Local Variables and Lifetimes

The program contains two functions with different local variables.

**Variables belonging to `walk_stack()`:**

- `depth`: stores the current recursion level.
- `max_depth`: stores the maximum recursion depth.
- `marker`: stores the current depth multiplied by 10.

Each recursive call has its own instances of these variables.

These variables remain alive while their corresponding function calls are active. They cease to exist when their respective calls finish.

**Variables belonging to `dump_frame()`:**

- `label`: indicates whether the function is called during entry or exit.
- `depth`: identifies the current recursion level.
- `local_int`: stores the value `100 + depth`.
- `local_buf`: a local character array of 16 elements.
- `p_local`: a pointer containing the address of `local_int`.

The values of `local_int` are:

| Depth | local_int |
|---|---:|
| 0 | 100 |
| 1 | 101 |
| 2 | 102 |
| 3 | 103 |

The first element of `local_buf` contains a character from A to D, depending on the recursion depth.

The pointer `p_local` points to `local_int`.

When `dump_frame()` returns, its local variables cease to exist.

A subsequent call creates new local variables, even if some memory addresses are reused.

### 2.4 Memory Map at Maximum Recursion Depth

The following diagram represents the active recursive calls when the program reaches depth 3.

    STACK

    +-----------------------------+
    | main()                      |
    +-----------------------------+
    | walk_stack() - depth 0      |
    | marker = 0                  |
    +-----------------------------+
    | walk_stack() - depth 1      |
    | marker = 10                 |
    +-----------------------------+
    | walk_stack() - depth 2      |
    | marker = 20                 |
    +-----------------------------+
    | walk_stack() - depth 3      |
    | marker = 30                 |
    +-----------------------------+

Each recursive call has its own `marker` variable.

The four variables remain alive simultaneously while the deepest recursive call is active.

The `dump_frame()` function creates a temporary additional stack frame whenever it is called. This frame disappears when `dump_frame()` returns.

    HEAP

    No dynamic memory allocation is performed.

### 2.5 Observations

The program demonstrates that:

- Recursive function calls create multiple active function frames.
- Each recursive call has its own local variables.
- Local variables remain alive while their corresponding function calls are active.
- Variables belonging to `dump_frame()` cease to exist when that function returns.
- A memory address can be reused by a later function call without representing the same object.
- No `malloc()` or `free()` operation is required because the program does not allocate dynamic memory.

### 2.6 Stack Memory Observations

Each recursive call to walk_stack() has its own local variables,
including depth, max_depth and marker.

Function arguments are passed by value. Therefore, when a new
recursive call is created, it receives its own parameter values.
The previous function call keeps its original values while
waiting for the recursive call to return.

The local variables of dump_frame() have a shorter lifetime.
They cease to exist when dump_frame() returns, because the
function execution has ended.

Each new call to dump_frame() creates new local variables.
However, the same memory addresses may be reused by subsequent
function calls.

A reused memory address does not mean that the new variable
is the same object as the previous variable. The previous
object's lifetime has already ended.
---

## 3. Heap Memory and Pointer Aliasing Analysis

### 3.1 Program Overview

File: `programs/aliasing_example.c`

The program demonstrates:

- Dynamic memory allocation using malloc().
- Two pointers referencing the same allocation.
- Memory deallocation using free().
- Invalid memory accesses after deallocation.

### 3.2 Heap Allocation

The function make_numbers() allocates memory dynamically.

The allocation reserves space for five integers.

The resulting values are:

    Index:  0   1   2   3   4
    Value:  0  11  22  33  44

[Explain what happens to the heap allocation when
make_numbers() returns to main().]

### 3.3 Pointer Aliasing

In main(), the following assignment is performed:

    b = a;

[Explain what happens when the address stored in a
is copied into b.]

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
                         |  0 | 11 | 22 | 33 | 44 |
                         +---------------------+

Both pointers refer to the same allocated memory block.

### 3.4 Memory Deallocation

The program executes:

    free(a);

After free(a), the heap allocation is deallocated.
Any subsequent use of the pointers associated with this
allocation results in undefined behavior.

The program attempts to access the released memory
through pointer b. These operations include reading
b[2], writing to b[3], and displaying the pointer
after deallocation.

The program may appear to work and display previous
values, but this behavior is not guaranteed.

This is a use-after-free error, not a memory leak.

Important: According to the C standard, a pointer value
becomes indeterminate when the object it points to reaches
the end of its lifetime.

Therefore, the program must not use either pointer to
access the freed allocation.

### 3.5 Invalid Memory Accesses

The following instructions occur after free(a):

| Source line | Instruction | Problem |
|-------------|-------------|---------|
| 40 | printf using b | [To complete] |
| 42 | Reading b[2] | [To complete] |
| 44 | Writing b[3] | [To complete] |
| 45 | Reading b[3] | [To complete] |

These operations involve memory whose allocated lifetime
has already ended.

This is an example of a use-after-free error.

### 3.6 Runtime Observations

The program executed and displayed values even after
the memory had been freed.

[Explain why successful execution does not prove that
the memory accesses are valid.]

The observed output is not a guarantee of correct behavior.
Accessing freed memory results in undefined behavior.

---

## 4. Critical Review of AI-Generated Explanations

### 4.1 Identified AI Inaccuracy

During the analysis, an initial AI explanation incorrectly
associated the variables local_int, local_buf and p_local
with the recursive walk_stack() calls.

### 4.2 Why the Explanation Was Incorrect

[Explain where these variables are actually declared and
which function owns them.]

### 4.3 Corrected Explanation

[Write the corrected explanation using the distinction
between walk_stack() and dump_frame().]

### 4.4 Lessons Learned

[Explain why AI-generated memory diagrams and explanations
must be checked against the actual source code.]

---

## 5. Conclusion

[Summarize the main differences between automatic storage
duration and dynamically allocated storage.]

[Explain what you learned about pointer aliasing,
memory lifetime and use-after-free.]

---

