list(APPEND TARGETS assignment)
#set(TARGETS ${TARGETS} PARENT_SCOPE)
cmake_minimum_required(VERSION 3.20)

add_executable(assignment main.cpp src/cloggeradapter.cpp include/cloggeradapter.h src/decorator.cpp include/decorator.h src/runningtime_decorator.cpp include/runningtime_decorator.h)
target_include_directories(assignment PRIVATE include)

project(assignment)
add_subdirectory(src)

target_sources(assignment
        PRIVATE
        program.cpp
        )

add_subdirectory(clib)
target_link_libraries(assignment PUBLIC clogger)

list(APPEND TARGETS assignment)
#set(TARGETS ${TARGETS} PARENT_SCOPE)