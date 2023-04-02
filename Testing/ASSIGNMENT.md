# Assignment

You assignment is to write tests for the `reducer::reduce_product` functions, extend tests for the `party::name` class and write tests for the `party::guest_list` class.

**After finishing each part `commit` your changes with a meaningful message and `push` if needed. Don't forget to `push` when you've finished your work!`**

## `reducer::reduce_product`

Do this part of the assignment in *tests_reducer.cpp*.

There are two `reduce_product` functions - they both calculate the product of the `init` argument and the numbers passed in the `numbers` vector. One function works for integers, the other for `double`s. Write test functions for both functions separating them into two suites `reducer_prod_int` and `reducer_prod_dbl`. Try to test as exhaustively as possible, remembering about `ASSERT_DOUBLE_EQ` for floating point numbers.


## `party::name`

Do this part of the assignment in *tests_name.cpp*.

Extend the tests for `party::name` class. Some functions haven't been tested at all (`initials` and equality comparisons). Some should be tested more extensively by passing different names (including an empty string) to the constructor.

## `party:guest_list`

For this part of the assignment you'll have to create a new source file (e.g. *tests_guest_list.cpp*) in the *tests* directory. You'll also need to add a new executable in the *tests/CMakeLists.txt* and add the name of this executable to the `TEST_TARGETS` list there. If in doubt, see how it's done for the other two test executables.

In your new source file, `#include` both the *gtest.h* and *gmock.h* headers and the header of the class you will test (*guest_list.h*). Then you can start writing tests.

Be as throughout as possible when writing the tests, there are **seven** functions that need to bested, some of them more than with one test. Don't forget to check the conditions that should throw an exception. Separate your tests into logical test suits.

If one of your tests fails and you think you found a bug, let me know via Teams first (@Dawid Zalewski), the bug might have been intentional;)

### Tip

It will be difficult to test some of the functions in isolation. For instance, it's almost impossible to test `add_guest` without using functions like `get_guests` or `get_family_members`. That's ok. If you really want to, you can always befriend your tests in `guest_list` to get access to its `private` `m_guests` member and inspect it directly. [See how to do this here](https://google.github.io/googletest/advanced.html#testing-private-code) and [also read this discussion](https://stackoverflow.com/questions/2396370/how-to-make-google-test-classes-friends-with-my-classes).

### Another tip

You'll most likely want to re-use a list of full names in your tests. You can use a website [like this](https://homepage.net/name_generator/) to generate a few names, tweak the generated results to your needs and add a function in your `tests_guest_list.cpp` that could look like:

```c++
static std::vector<std::string> get_names(){
    return {"Alice Cindy Johnson",
            "Bob Smith",
            "Derek Frank Smith",
            "Ginny Smith",
            "Iris Kathy Mia Johnson",
            "Luke Backer",
            // and so on...
            };
}
```

Then in your tests you can just reuse this list:

```c++
TEST(add_guest, one_family_only){
    
    party::guest_list gl{};

    std::string family = "Johnson";
    // only add members of the Johnson family
    for(const auto& name: get_names()){
        if (name.find(family) != name.npos){
            gl.add_guest(name);
        }
    }

    ASSERT...
}
```