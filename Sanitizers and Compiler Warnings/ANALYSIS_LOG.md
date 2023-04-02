# Analysis log

## First run

1. Enable all the necessary compiler warnings, clang-tidy integration and Cppcheck integration in your *CMakeLists.txt*.
2. If you are using Visual Studio use [Clang Power Tools](https://clangpowertools.com/) for clang-tidy.
3. List the detected problems in the sections below.

### compiler warnings

What compiler did you use? Which version?

A GNU-like compiler. The CXX compiler identification is Clang 10.0.0

List the warnings that were enabled.
```
$<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor >
# enable gcc static analyzer
$<$<CXX_COMPILER_ID:GNU>:-fanalyzer>
# debug optimisation in Debug
$<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Release>>:-O3>
# O3 optimisation Release
$<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Debug>>:-Og -g -fno-omit-frame-pointer>
# static gcc analyzer
$<$<AND:$<CXX_COMPILER_ID:GNU>,$<BOOL:${GCC_ANALYZE}>>:-fanalyzer>
```
#### Detected problems

```text
In file included from /mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/money_pot.cpp:5:
In file included from /mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/money_pot.h:10:
/mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/ibank.h:10:7: warning: 'ibank' has virtual functions but non-virtual destructor [-Wnon-virtual-dtor]
class ibank {
      ^
In file included from /mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/money_pot.cpp:5:
/mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/money_pot.h:13:7: warning: 'money_pot' has virtual functions but non-virtual destructor [-Wnon-virtual-dtor]
class money_pot: public ibank {
      ^
/mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/money_pot.cpp:59:14: warning: declaration shadows a local variable [-Wshadow]
        auto sum = m_amounts[index];
             ^
/mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/money_pot.cpp:54:10: note: previous declaration is here
    auto sum{0};
         ^
/mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/money_pot.cpp:59:14: warning: unused variable 'sum' [-Wunused-variable]
        auto sum = m_amounts[index];
             ^
/mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/money_pot.cpp:69:14: warning: declaration shadows a local variable [-Wshadow]
        auto sum{0};
             ^
/mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/money_pot.cpp:66:10: note: previous declaration is here
    auto sum{0};
         ^
/mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/money_pot.cpp:70:27: warning: comparison of integers of different signs: 'int' and 'const std::size_t' (aka 'const unsigned long') [-Wsign-compare]
        for (int i = 0; i < m_sz; ++i){
                        ~ ^ ~~~~
/mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/money_pot.cpp:80:21: warning: comparison of integers of different signs: 'int' and 'const std::size_t' (aka 'const unsigned long') [-Wsign-compare]
    for (int i=0; i < m_sz; ++i){
                  ~ ^ ~~~~
In file included from /mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/main.cpp:2:
In file included from /mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/money_pot.h:10:
/mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/ibank.h:10:7: warning: 'ibank' has virtual functions but non-virtual destructor [-Wnon-virtual-dtor]
class ibank {
      ^
In file included from /mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/main.cpp:2:
/mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/money_pot.h:13:7: warning: 'money_pot' has virtual functions but non-virtual destructor [-Wnon-virtual-dtor]
class money_pot: public ibank {
      ^
/mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/main.cpp:21:5: warning: delete called on 'ibank' that is abstract but has non-virtual destructor [-Wdelete-abstract-non-virtual-dtor]
    delete bank;
    ^
3 warnings generated.
7 warnings generated.
```

### clang-tidy

List the checks that were enabled.

Enabled checks:

```
google-*,clang-analyzer-*,cppcoreguidelines-*,modernize-*,portability-*,readability-*"
```


#### Detected problems

```text
ibank.h
Clang-Tidy: Function 'sum' should be marked [[nodiscard]] (for both sum functions)
Clang-Tidy: Method 'sum' can be made static

moneypot.h
Clang-Tidy: Annotate this function with 'override' or (rarely) 'final' (for all public functions except for sum())
Clang-Tidy: Function 'sum' should be marked [[nodiscard]]
Clang-Tidy: Function 'find_name' should be marked [[nodiscard]]

moneypot.cpp
Clang-Tidy: Narrowing conversion from 'std::size_t' (aka 'unsigned long') to signed type 'int' is implementation-defined
Clang-Tidy: Narrowing conversion from 'double' to 'int'


```

### cppcheck

List the checks that were enabled.

Enabled checks:
```
 "--enable=all"
  "--error"
  "--warning"
  "--style"
  "--performance"
  "--portability"
  "--all"
  "--inconclusive"
  "--inline-suppr"
  "--suppress=unmatchedSuppression"
  "--template='{file}:{line}: warning: {id} ({severity}): {message}'"
```

#### Detected problems

```text
money_pot.h
Cppcheck: (style) missingOverride: The function 'store' overrides a function in a base class but is not marked with a 'override' specifier.
Cppcheck: (style) missingOverride: The function 'take' overrides a function in a base class but is not marked with a 'override' specifier.
Cppcheck: (style) missingOverride: The function 'sum' overrides a function in a base class but is not marked with a 'override' specifier.

money_pot.cpp
Cppcheck: (style) shadowVariable: Local variable 'sum' shadows outer variable
Cppcheck: (style) unreadVariable: Variable 'sum' is assigned a value that is never used.
Cppcheck: (style) shadowVariable: Local variable 'sum' shadows outer variable
Cppcheck: (style) unreadVariable: Variable 'sum' is assigned a value that is never used.
Cppcheck: (style) unreadVariable: Variable 'sum' is assigned a value that is never used.
```

### pvs-studio (optional)

#### Detected problems

```text
(copy-paste problems detected by pvs-studio)
```

### msvc analyzer (optional)

Only if you are using msvc - check what problems are detected when using the `/analyze` switch.

#### Detected problems

```text
(copy-paste problems detected by msvc static analyzer)
```

## Second run

Fix the problems reported by your compiler, clang-tidy and cppcheck (skip pvs-studio even if you used it).

Re-run the checks afterwards. Do any of those tools still detect problems? If yes list them here in the same way as for the *first run*. **Do not fix them yet.**

No they didn't.

## Sanitizers

### First run

Enable sanitizers integration (ASan an UBSan) in *CmakeLists.txt*. 
Make sure that they continue running even if an error is encountered (`-fsanitize-recover=...` and the configuration option in CLion).

**Disable the pretty-output for sanitizers in CLion, it's also possible to do it in Visual Studio. If you choose not to disable the pretty-output you'll have to paste screenshots in the subsection below.**

Then, compile and **run** the program.

#### Detected problems 

```text
==4339==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x603000000038 at pc 0x0000004cbfd4 bp 0x7fff511f7860 sp 0x7fff511f7858
READ of size 8 at 0x603000000038 thread T0
    #0 0x4cbfd3 in std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::size() const /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/basic_string.h:907:16
    #1 0x4cc919 in std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::assign(char const*, unsigned long) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/basic_string.h:1429:40
    #2 0x4cc872 in std::enable_if<__and_<std::is_convertible<std::basic_string_view<char, std::char_traits<char> > const&, std::basic_string_view<char, std::char_traits<char> > >, std::__not_<std::is_convertible<std::basic_string_view<char, std::char_traits<char> > const*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const*> >, std::__not_<std::is_convertible<std::basic_string_view<char, std::char_traits<char> > const&, char const*> > >::value, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&>::type std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::assign<std::basic_string_view<char, std::char_traits<char> > >(std::basic_string_view<char, std::char_traits<char> > const&) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/basic_string.h:1502:17
    #3 0x4cab9c in std::enable_if<__and_<std::is_convertible<std::basic_string_view<char, std::char_traits<char> > const&, std::basic_string_view<char, std::char_traits<char> > >, std::__not_<std::is_convertible<std::basic_string_view<char, std::char_traits<char> > const*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const*> >, std::__not_<std::is_convertible<std::basic_string_view<char, std::char_traits<char> > const&, char const*> > >::value, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&>::type std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::operator=<std::basic_string_view<char, std::char_traits<char> > >(std::basic_string_view<char, std::char_traits<char> > const&) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/basic_string.h:786:23
    #4 0x4c939f in money_pot::store(std::basic_string_view<char, std::char_traits<char> >, double) /mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/money_pot.cpp:32:20
    #5 0x4c7ea2 in main /mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/main.cpp:8:11
    #6 0x7f0a8b400082 in __libc_start_main /build/glibc-SzIz7B/glibc-2.31/csu/../csu/libc-start.c:308:16
    #7 0x41d42d in _start (/mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/cmake-build-debug/week_06_assignment+0x41d42d)

0x603000000038 is located 8 bytes to the right of 32-byte region [0x603000000010,0x603000000030)
allocated by thread T0 here:
    #0 0x4c52dd in operator new(unsigned long) (/mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/cmake-build-debug/week_06_assignment+0x4c52dd)
    #1 0x4c8d3d in money_pot::money_pot() /mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/money_pot.cpp:10:14
    #2 0x4c7c9f in main /mnt/c/Users/HP/assignment-6-code-analyzis-ababsmuc/main.cpp:6:23
    #3 0x7f0a8b400082 in __libc_start_main /build/glibc-SzIz7B/glibc-2.31/csu/../csu/libc-start.c:308:16

SUMMARY: AddressSanitizer: heap-buffer-overflow /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/basic_string.h:907:16 in std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::size() const
Shadow bytes around the buggy address:
  0x0c067fff7fb0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c067fff7fc0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c067fff7fd0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c067fff7fe0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c067fff7ff0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x0c067fff8000: fa fa 00 00 00 00 fa[fa]fa fa fa fa fa fa fa fa
  0x0c067fff8010: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c067fff8020: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c067fff8030: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c067fff8040: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c067fff8050: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc
==4339==ABORTING
```

### Second run

Fix the problems (one-by-one) detected by the sanitizers.

Re-run the checks afterwards.

#### Detected problems

If there were any other problems detected, list them here.

```text
No other problems.
```

## Final checks.

Your program should compile and run fine now. If not, list the detected errors here:

```text
No other problems.
```