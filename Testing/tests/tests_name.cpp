#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "name.h"
#include <stdexcept>

using ::testing::StrEq;

TEST(name, ctor_parsing_1) {
    party::name name{"Alice Eve Backer"};

    party::name other_name_2{"Alece Eve Backer"};
    ASSERT_EQ(2, name.first_names().size()) << "There should be two first names";

    ASSERT_EQ("Alice", name.first_names()[0]) << "The first name should be Alice";
    ASSERT_EQ("Eve", name.first_names()[1]) << "The second first name should be Eve";

    ASSERT_THAT(name.last_name(), StrEq("Backer"))<<"The Last name should be Backer";
    ASSERT_EQ("Alice Eve Backer", name.full_name()) << "The full name should be Alice Eve Backer";

    ASSERT_THAT(name.initials(), StrEq("A.E."))<< "The initials should be A.E.";

    ASSERT_FALSE(name==other_name_2) << "The two names are equal.";



}


TEST(name, ctor_throws) {
    EXPECT_THROW({ party::name name{"Alice"}; }, std::invalid_argument) << "Constructor should throw on short names";
    EXPECT_THROW({ party::name name{" "}; }, std::invalid_argument) << "Constructor should throw on empty strings";

    EXPECT_NO_THROW({ party::name name{"Bob Derek Smith"}; }) << "Constructor shouldn't throw on correct names";
}


