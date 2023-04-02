cmake_minimum_required(VERSION 3.20)
project(week_06_assignment)

option(USE_ASAN "Use address sanitizer if available" OFF)
option(USE_UBSAN "Use undefined behavior sanitizer if available" OFF)
option(USE_CLANGTIDY "Use clang-tidy if available" OFF)
option(USE_CPPCHECK "Use Cppcheck if available" OFF)


add_executable(week_06_assignment)

set(target week_06_assignment)

target_sources(${target}
        PRIVATE
        main.cpp
        money_pot.cpp)

target_compile_features(${target} PRIVATE cxx_std_20)
set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)

target_link_options(${target} PRIVATE
        -fsanitize=address,undefined)


# detect clang, appleclang or gcc
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" OR "${CMAKE_CXX_COMPILER_ID}"
        MATCHES "GNU")
    set(CXX_GNU_LIKE ON)
else ()
    set(CXX_GNU_LIKE OFF)
endif ()
if (CXX_GNU_LIKE)
    message("A GNU-like compiler detected")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message("A MSVC compiler detected")
else ()
    message("An unsupported compiler detected")
endif ()
# this forces a build type if it's not yet set
if (CXX_GNU_LIKE AND NOT DEFINED CMAKE_BUILD_TYPE)
    message("Setting default build type")
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

 #Set options for gnu-like
target_compile_options(${target} PRIVATE
        # set warnings for all build types
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor -fsanitize=address,undefined
        -fsanitize-recover=address,undefined >
        # enable gcc static analyzer
        $<$<CXX_COMPILER_ID:GNU>:-fanalyzer>
        # debug optimisation in Debug
        $<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Release>>:-O3>
        # O3 optimisation Release
        $<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Debug>>:-Og -g -fno-omit-frame-pointer>
        # static gcc analyzer
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<BOOL:${GCC_ANALYZE}>>:-fanalyzer>
        )

# Set options for MSVC
target_compile_options(${target} PRIVATE
        # set warnings for all build types
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive- /w14265>
        # enable static analysis if option is set
        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<BOOL:${MSVC_ANALYZE}>>:/analyze>
        # debug optimisation in Debug
        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/O2>
        # O3 optimisation in Release
        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:/RTC1 /Od /Zi>
        )


execute_process(COMMAND "${CMAKE_CXX_COMPILER}" -print-file-name=libasan.so
        OUTPUT_VARIABLE LIBASAN_PATH
        RESULT_VARIABLE ASAN_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE)


if ((${ASAN_RESULT} EQUAL 0) AND (NOT ${LIBASAN_PATH} STREQUAL ""))
    target_compile_options(${target} PRIVATE -fsanitize=address -fsanitize-recover=address)
    target_link_options(${target} PRIVATE -fsanitize=address)
endif()

execute_process(COMMAND "${CMAKE_CXX_COMPILER}" -print-file-name=libubsan.so
        OUTPUT_VARIABLE LIBUBSAN_PATH
        RESULT_VARIABLE UBSAN_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE)


if ((${UBSAN_RESULT} EQUAL 0) AND (NOT ${LIBUBSAN_PATH} STREQUAL ""))
    target_compile_options(${target} PRIVATE -fsanitize=undefined -fsanitize-recover=undefined)
    target_link_options(${target} PRIVATE -fsanitize=undefined)
endif()


if (USE_CPPCHECK)
    find_program(CPPCHECK NAMES cppcheck HINTS $ENV{PROGRAMFILES}/cppcheck)
    if(CPPCHECK AND NOT (CPPCHECK MATCHES "NOTFOUND"))
        message(STATUS "which cppcheck: ${CPPCHECK}")

        set(CPPCHECK_CMD "${CPPCHECK}"
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
                "--template='{file}:{line}: warning: {id} ({severity}): {message}'")

        set_target_properties(${target} PROPERTIES
                CXX_CPPCHECK "${CPPCHECK_CMD}"
                )
    endif()
endif(USE_CPPCHECK)

if (USE_CLANGTIDY)
    find_program(CLANGTIDY NAMES clang-tidy clang-tidy-14 clang-tidy-13 clang-tidy-12 clang-tidy-11)

    if(CLANGTIDY AND NOT (CLANGTIDY MATCHES "NOTFOUND"))
        message(STATUS "which clang-tidy: ${CLANGTIDY}")
        set_target_properties(${target} PROPERTIES
                CXX_CLANG_TIDY "${CLANGTIDY};-checks=-*,google-*,clang-analyzer-*,cppcoreguidelines-*,modernize-*,portability-*,readability-*"
                )
    endif()
endif(USE_CLANGTIDY)