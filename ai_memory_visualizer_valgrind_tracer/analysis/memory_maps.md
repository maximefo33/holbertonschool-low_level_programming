# Memory Maps — Stack and Heap Analysis

## 1. Project Overview and Environment

### 1.1 Objective

The purpose of this analysis is to understand how memory is used by C programs, with a particular focus on:

- Stack memory and function calls
- Recursive function calls and stack frames
- Local variables and their lifetimes
- Heap allocation and deallocation
- Pointer aliasing
- Invalid memory accesses
- Memory leaks and Valgrind diagnostics

The analysis uses four example programs:

| Program | Main concept |
|---|---|
| `stack_example.c` | Stack frames and recursion |
| `heap_example.c` | Dynamic allocation and memory leaks |
| `aliasing_example.c` | Pointer aliasing and use-after-free |
| `crash_example.c` | NULL pointer dereferencing |

### 1.2 Test Environment

The programs were compiled and executed in an Ubuntu environment using GitHub Codespaces.

Valgrind Memcheck was used to observe memory errors and heap allocation statistics.

The Windows execution environment and the Ubuntu Codespaces environment must be distinguished: the crash observed directly on Windows was reported differently from the invalid memory access detected by Valgrind under Ubuntu.

The memory diagrams in this document are conceptual representations. They explain object lifetimes and relationships, but they do not claim to reproduce exact physical addresses or a guaranteed memory layout.

---

## 2. Stack Memory Analysis

### 2.1 Program Overview

The `stack_example.c` program demonstrates how function calls use automatic storage duration and how recursive calls create separate instances of local variables.

The program contains two important functions:

- `walk_stack(int depth, int max_depth)`
- `dump_frame(const char *label, int depth)`

The `main()` function starts the recursion by calling:

```c
walk_stack(0, 3);
```

The recursive function calls itself while `depth` is less than `max_depth`.

As a result, four calls to `walk_stack()` are made:

- `walk_stack(0, 3)`
- `walk_stack(1, 3)`
- `walk_stack(2, 3)`
- `walk_stack(3, 3)`

Each recursive call has its own parameters and local variables.

### 2.2 Recursive Stack Frames

A stack frame represents the execution context associated with a function call. It can contain parameters, local variables, and other implementation-dependent information.

In `walk_stack()`, the following variables are declared:

```c
int marker = depth * 10;
```

Each recursive call creates a separate instance of `depth`, `max_depth`, and `marker`.

The values of `marker` are:

| Function call | `depth` | `max_depth` | `marker` |
|---|---:|---:|---:|
| `walk_stack(0, 3)` | 0 | 3 | 0 |
| `walk_stack(1, 3)` | 1 | 3 | 10 |
| `walk_stack(2, 3)` | 2 | 3 | 20 |
| `walk_stack(3, 3)` | 3 | 3 | 30 |

These variables have the same names in the source code, but they belong to different function-call instances.

They do not overwrite one another because each recursive invocation has its own execution context.

The calls are nested:

```text
main()
  |
  +-- walk_stack(depth = 0)
        |
        +-- walk_stack(depth = 1)
              |
              +-- walk_stack(depth = 2)
                    |
                    +-- walk_stack(depth = 3)
```

When the deepest call finishes, execution returns in reverse order:

```text
walk_stack(depth = 3) returns
walk_stack(depth = 2) resumes and returns
walk_stack(depth = 1) resumes and returns
walk_stack(depth = 0) resumes and returns
main() continues
```

This illustrates the Last In, First Out (LIFO) behavior associated with the call stack.

### 2.3 Local Variables and Lifetimes

The program also calls `dump_frame()` before and after the recursive call.

This function declares its own local variables:

```c
int local_int = 100 + depth;
char local_buf[16];
int *p_local = &local_int;
```

Their values depend on the current `depth`:

| Call depth | `local_int` | `local_buf[0]` | `p_local` |
|---|---:|---|---|
| 0 | 100 | `'A'` | Address of `local_int` |
| 1 | 101 | `'B'` | Address of `local_int` |
| 2 | 102 | `'C'` | Address of `local_int` |
| 3 | 103 | `'D'` | Address of `local_int` |

The variables declared inside `dump_frame()` are distinct from those declared inside `walk_stack()`.

For example:

- `marker` belongs to a particular invocation of `walk_stack()`.
- `local_int` belongs to a particular invocation of `dump_frame()`.
- `p_local` stores the address of that invocation's `local_int`.
- `local_buf` is a local character array belonging to that invocation.

The pointer `p_local` does not contain a copy of `local_int`. It contains the address of that local variable.

When `dump_frame()` returns, its local objects reach the end of their lifetimes. The corresponding storage is no longer available for valid access through those objects.

The same function can be called again later, but a new invocation creates new local objects. An implementation may reuse the same memory addresses; this does not make the objects the same object.

### 2.4 Memory Map at Maximum Recursion Depth

At the deepest point of recursion, the program has entered `walk_stack(3, 3)`.

At that moment, the active function-call structure can be represented conceptually as follows:

```text
             CONCEPTUAL CALL STACK
        (not an exact physical memory layout)

        +----------------------------------+
        | main()                           |
        | Calls walk_stack(0, 3)           |
        +----------------------------------+
        | walk_stack() - depth 0           |
        | depth     = 0                    |
        | max_depth = 3                    |
        | marker    = 0                    |
        +----------------------------------+
        | walk_stack() - depth 1           |
        | depth     = 1                    |
        | max_depth = 3                    |
        | marker    = 10                   |
        +----------------------------------+
        | walk_stack() - depth 2           |
        | depth     = 2                    |
        | max_depth = 3                    |
        | marker    = 20                   |
        +----------------------------------+
        | walk_stack() - depth 3           |
        | depth     = 3                    |
        | max_depth = 3                    |
        | marker    = 30                   |
        +----------------------------------+
                  |
                  v
          Deepest active call
```

At this exact point, the previous calls to `dump_frame()` have already returned.

Therefore, their local variables (`local_int`, `local_buf`, and `p_local`) are not active in this conceptual map.

The deepest active recursive call is `walk_stack(3, 3)`. Since `depth` is no longer less than `max_depth`, this call does not make another recursive call.

It then returns, allowing the previous stack frames to resume execution.

### 2.5 Observations

The `stack_example.c` program demonstrates several important properties:

1. Each recursive call has its own local variables and parameters.
2. Variables with identical names in different recursive calls represent distinct objects.
3. The lifetime of an automatic local variable is associated with the execution of its enclosing block.
4. Returning from a function ends the lifetime of its automatic local objects.
5. Recursive calls remain active until their execution returns.
6. The call sequence follows a nested structure, with the last call returning first.

The C language defines object lifetimes and storage durations. However, it does not require every automatic object to be physically stored in a hardware stack. The stack diagrams in this document describe the conventional implementation model used to understand function calls.

### 2.6 Stack Memory Observations

The recursive execution demonstrates how the number of active function calls increases as recursion progresses.

For `walk_stack(0, 3)`, four recursive invocations are active at maximum depth:

```text
depth 0
  |
  +-- depth 1
        |
        +-- depth 2
              |
              +-- depth 3
```

Each invocation retains its own values until that invocation returns.

The calls to `dump_frame()` are temporary nested calls. They execute and return before `walk_stack()` proceeds to its next recursive call. Consequently, a `dump_frame()` invocation is not active at the deepest recursive point shown in Section 2.4.

The local pointer `p_local` demonstrates that a pointer can refer to another local object in the same function call. Its validity is limited by the lifetime of the object it points to.

No explicit `malloc()` call is present in `stack_example.c`.

However, the Valgrind report recorded one allocation and one deallocation, with 4096 bytes allocated. This does not mean that `stack_example.c` explicitly allocates 4096 bytes. The observed allocation is associated with runtime library activity, such as standard I/O buffering.

The recorded Memcheck summary was:

```text
ERROR SUMMARY: 0 errors from 0 contexts
```

At program exit, Valgrind reported no memory still in use.

---

## 3. Heap Memory and Pointer Aliasing Analysis

### 3.1 Program Overview

The heap examples demonstrate how dynamically allocated memory differs from automatic local variables.

Unlike automatic objects whose lifetimes are associated with their enclosing blocks, allocated objects remain alive until their storage is released.

The examples explore:

- Dynamic allocation with `malloc()`
- Memory ownership
- Pointer aliasing
- Deallocation with `free()`
- Invalid accesses after deallocation
- Memory leaks

### 3.2 Heap Allocation

The `heap_example.c` program uses dynamically allocated memory to create `Person` structures and their associated names.

The structure and its name are separate allocations:

```text
                 HEAP MEMORY

        +--------------------------+
        | Person structure         |
        |                          |
        | name --------------------|------+
        | other structure fields   |      |
        +--------------------------+      |
                                          |
                                          v
                                  +----------------+
                                  | Name allocation|
                                  | "Alice\0"      |
                                  +----------------+
```

The `Person` structure contains a pointer to the separately allocated name.

This distinction is important: freeing the structure does not automatically free the memory pointed to by one of its fields.

The program's cleanup logic correctly frees Bob's memory, but `person_free_partial()` does not free `p->name` before freeing the structure itself.

As a result, the allocation containing `"Alice"` is no longer accessible through the freed structure.

Valgrind reported:

```text
in use at exit: 6 bytes in 1 block
total heap usage: 5 allocs, 4 frees, 4138 bytes
```

The 6-byte allocation corresponds to the string `"Alice"` including its terminating null character:

```text
A l i c e \0
1 2 3 4 5  6 bytes
```

Valgrind identified the allocation in `person_new()` at `heap_example.c:21`, called from `main()` at `heap_example.c:51`.

The missing deallocation is the cause of the memory leak.

### 3.3 Pointer Aliasing

The `aliasing_example.c` program demonstrates how multiple pointers can refer to the same dynamically allocated memory.

The function `make_numbers(5)` allocates an array of five integers and returns a pointer to that allocation.

The pointer variable declared inside `make_numbers()` is local to that function. Its lifetime ends when the function returns, but the allocated memory remains available because it has not been freed.

The returned pointer value is received by `main()`.

The program then assigns:

```c
b = a;
```

This copies the pointer value, not the contents of the allocated array.

The relationship can be represented as follows:

```text
                 POINTER VARIABLES

        +-------------------+
        | a                 |
        | Address: 0x...    |
        +-------------------+
                  |
                  |
                  v
        +-------------------+
        | Heap allocation   |
        | 5 integers        |
        | 20 bytes*         |
        +-------------------+
                  ^
                  |
        +-------------------+
        | b                 |
        | Same address      |
        +-------------------+
```

Both `a` and `b` refer to the same allocation.

This relationship is called pointer aliasing.

*The 20-byte size corresponds to the observed environment, where `sizeof(int)` is 4 bytes.*

When the program executes:

```c
free(a);
```

the allocated memory is released.

The other pointer, `b`, does not become a valid way to access that allocation simply because it still contains a previously copied pointer value.

According to C11 section 6.2.4, the value of a pointer becomes indeterminate when the object it points to reaches the end of its lifetime.

Therefore, the program must not use `b` to access the released memory. It must not rely on the old pointer value after the allocation has been freed.

### 3.4 Memory Deallocation

The `free()` function releases dynamically allocated memory.

A correct memory management strategy requires the program to keep track of which pointer or component owns each allocation.

For the heap example, both the `Person` structure and its separately allocated name must be released.

For the aliasing example, the allocated array must be freed once. Because `a` and `b` refer to the same allocation, freeing both pointers would result in an invalid double-free operation.

The following conceptual sequence illustrates the allocation's lifetime:

```text
1. malloc()
      |
      v
   Memory allocated
      |
      v
2. a receives the address
      |
      v
3. b receives a copy of the address
      |
      v
   a and b alias the same allocation
      |
      v
4. free(a)
      |
      v
   Allocation released
      |
      v
   Access through the old pointer is invalid
```

### 3.5 Invalid Memory Accesses

The Valgrind execution of `aliasing_example.c` reported invalid accesses after the allocated array had been freed.

The report contained:

- One invalid read at `aliasing_example.c:42`
- One invalid write at `aliasing_example.c:44`
- One invalid read at `aliasing_example.c:45`

The invalid accesses occurred after the allocation was released at line 38.

Valgrind identified the allocation as originating from `make_numbers()` at line 12, called from `main()` at line 30.

The reported access sizes were 4 bytes.

The compiler also produced warnings related to using the pointer after deallocation. The program was compiled without `-Werror` for the Valgrind execution because the warnings would otherwise prevent compilation.

These warnings were retained as evidence of the issue; disabling `-Werror` did not make the accesses valid.

The Valgrind summary reported:

```text
ERROR SUMMARY: 3 errors from 3 contexts
```

No memory leak was reported at program exit.

This distinction matters: the program can release all allocated memory and still perform invalid accesses during execution.

### 3.6 Runtime Observations

The heap examples demonstrate that allocation and access validity are separate concerns.

A pointer can contain an address that was once valid but no longer refers to a live allocated object.

Similarly, releasing a structure does not automatically release allocations referenced by its pointer fields.

The Valgrind results show two different classes of memory-management problems:

| Program | Observed issue | Valgrind result |
|---|---|---|
| `heap_example.c` | Missing deallocation of a name | 6 bytes definitely lost |
| `aliasing_example.c` | Access after deallocation | 3 invalid accesses |

The `heap_example.c` result demonstrates a memory leak, while the `aliasing_example.c` result demonstrates invalid memory access after `free()`.

---

## 4. Critical Review of AI-Generated Explanations

### 4.1 Identified AI Inaccuracy

A potential source of inaccuracy in explanations of C memory is treating the conventional Stack and Heap model as if it were a physical layout explicitly guaranteed by the C language.

The C standard defines storage durations and object lifetimes. It does not require every automatic variable to occupy a physical stack frame or every allocated object to occupy a region physically named the heap.

The diagrams in this document are therefore conceptual representations based on the conventional implementation model observed in the test environment.

Another important distinction concerns pointers after deallocation.

It is not sufficient to say that a pointer becomes harmless or simply points to freed memory. Under C11 section 6.2.4, its value becomes indeterminate when the pointed-to object reaches the end of its lifetime.

### 4.2 Stack Analysis: What Must Be Distinguished

A recursive function call creates a new instance of its automatic objects.

The variables named `depth`, `max_depth`, and `marker` in `walk_stack()` belong to each individual invocation.

The variables `local_int`, `local_buf`, and `p_local` belong to separate invocations of `dump_frame()`.

These two groups must not be merged into a single stack frame.

In particular, `dump_frame()` returns before the next recursive call is made. Its local objects are therefore not active at the deepest recursive point.

### 4.3 Heap Analysis: Ownership and Lifetime

A pointer field does not automatically own or release the memory it references.

In `heap_example.c`, the `Person` structure and its name are separate allocations. Both require appropriate cleanup.

In `aliasing_example.c`, assigning `b = a` copies an address. It does not create another allocation or duplicate the array.

The program must therefore avoid freeing the same allocation more than once and must not access it after it has been released.

### 4.4 Valgrind: What the Results Actually Prove

Valgrind Memcheck reports invalid reads, invalid writes, and memory leaks detected during program execution.

The absence of a reported error does not prove that a program is correct in every possible execution. It means that Memcheck did not report an error during the recorded run.

The results must also be interpreted in context:

- `stack_example.c` produced no reported Memcheck errors.
- `heap_example.c` produced a 6-byte definite leak.
- `aliasing_example.c` produced three invalid accesses.
- `crash_example.c` produced an invalid write through a NULL pointer.

A `still reachable` allocation must not automatically be described as a definite memory leak. It means that a pointer to the allocation remained reachable when the program exited.

---

## 5. Conclusion

The four programs demonstrate different aspects of memory management in C.

The `stack_example.c` program shows how recursive function calls create separate instances of automatic variables and how those instances remain active until their calls return.

The `heap_example.c` program demonstrates that dynamically allocated structures and their separately allocated fields must each be released correctly. Failing to free the name allocation results in a 6-byte memory leak.

The `aliasing_example.c` program shows that copying a pointer does not copy the allocated memory. Multiple pointers can refer to the same allocation, and accessing that allocation after it has been freed is invalid.

Finally, `crash_example.c` demonstrates how dereferencing a NULL pointer can produce an invalid memory access and terminate a program.

Together, these examples highlight three essential principles:

1. Understand the lifetime of every object.
2. Track the ownership of every dynamically allocated block.
3. Never access an object after its lifetime has ended.

Memory diagrams are useful for understanding these relationships, but they must be interpreted as conceptual models rather than guaranteed physical layouts.

---

