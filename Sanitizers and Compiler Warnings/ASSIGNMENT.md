# Software Engineering Techniques, week 6, code analyzers

## Assignment

Your goal in this assignment is to integrate as many checks in your CMake-build as possible and to fix the detected problems.


It's again a simple money-pot implementation. With a lot of bugs (and inheritance). When fixing bugs do not modify `main`, only `money_pot` or `ibank`.


When doing this assignment you'll have to fill the [*ANALYSIS_LOG*](ANALYSIS_LOG.md) on the go. This is a required part.

Make sure to commit changes after each fixing step.


Your final commit & push should include:

1. A fixed program (as much as you managed).
2. A filled-in [*ANALYSIS_LOG*](ANALYSIS_LOG.md).
3. A modified *CMakeLists.txt* that includes all the changes that you made to enable checks.

## Enabling checks

In all examples below `${target}` is the name of the binary, possibly set with:

```cmake
set(target my_program_name)
```

**After enabling each check you'll have to reset the cmake cache and reload the project, otherwise it won't work as intended.**

### Compiler warnings

You already know how to do it.

### clang-tidy

List your checks in the placeholder `[LIST THE CHECK HERE]`

```cmake
find_program(CLANGTIDY NAMES clang-tidy clang-tidy-14 clang-tidy-13 clang-tidy-12 clang-tidy-11)

if(CLANGTIDY AND NOT (CLANGTIDY MATCHES "NOTFOUND"))
    message(STATUS "which clang-tidy: ${CLANGTIDY}")
    set_target_properties(${target} PROPERTIES
            CXX_CLANG_TIDY "${CLANGTIDY};-checks=[LIST THE CHECK HERE]"
            )
endif()
```

### Cppcheck

List your checks (one-by-one in new lines) in the placeholder `[LIST THE CHECK HERE]`

```cmake
find_program(CPPCHECK NAMES cppcheck HINTS $ENV{PROGRAMFILES}/cppcheck)
if(CPPCHECK AND NOT (CPPCHECK MATCHES "NOTFOUND"))
    message(STATUS "which cppcheck: ${CPPCHECK}")

    set(CPPCHECK_CMD "${CPPCHECK}"
            [LIST THE CHECK HERE]
            "--template=gcc")

    set_target_properties(${target} PROPERTIES
            CXX_CPPCHECK "${CPPCHECK_CMD}"
            )
endif()
```

### ASan

```cmake
execute_process(COMMAND "${CMAKE_CXX_COMPILER}" -print-file-name=libasan.so
        OUTPUT_VARIABLE LIBASAN_PATH
        RESULT_VARIABLE ASAN_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE)


if ((${ASAN_RESULT} EQUAL 0) AND (NOT ${LIBASAN_PATH} STREQUAL ""))
    target_compile_options(${target} PRIVATE -fsanitize=address -fsanitize-recover=address)
    target_link_options(${target} PRIVATE -fsanitize=address)
endif()
```

### UBSan

```cmake
execute_process(COMMAND "${CMAKE_CXX_COMPILER}" -print-file-name=libubsan.so
        OUTPUT_VARIABLE LIBUBSAN_PATH
        RESULT_VARIABLE UBSAN_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE)


if ((${UBSAN_RESULT} EQUAL 0) AND (NOT ${LIBUBSAN_PATH} STREQUAL ""))
    target_compile_options(${target} PRIVATE -fsanitize=undefined -fsanitize-recover=undefined)
    target_link_options(${target} PRIVATE -fsanitize=undefined)
endif()
```