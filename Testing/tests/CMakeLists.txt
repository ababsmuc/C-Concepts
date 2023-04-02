enable_testing()

add_executable(tests_reducer tests_reducer.cpp )
add_executable(tests_name tests_name.cpp ../src/name.cpp)
# TODO: Add your executable with tests for guest_list (e.g. tests_guest_list)
#       here, possibly adding guest_list.cpp to its sources.
add_executable(tests_guest_list ../tests/tests_guest_list.cpp ../src/guest_list.cpp ../src/name.cpp)

# TODO: Add the name of your guest list test executable (e.g. test_guest_list)
#       as the last element to the list below, just after `tests_name`
list( APPEND TEST_TARGETS tests_reducer tests_name tests_guest_list)


include(GoogleTest)

foreach(target ${TEST_TARGETS})
    target_compile_features(${target} PRIVATE cxx_std_20)
    set_target_properties(${target} PROPERTIES CXX_EXTENSIONS ON)

    target_include_directories(${target} PRIVATE ../inc)

    target_link_libraries(${target} gtest_main gmock)
    gtest_discover_tests(${target})

endforeach()


