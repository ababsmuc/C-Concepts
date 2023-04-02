#include <gtest/gtest.h>
#include "guest_list.h"
#include <gmock/gmock.h>

static std::vector<std::string> get_names() {
    return {"Alice Cindy Johnson",
            "Bob Smith",
            "Derek Frank Smith",
            "Ginny Smith",
            "Iris Kathy Mia Johnson",
            "Luke Backer"
    };
}

static std::vector<std::string> get_the_guests() {
    return {"B. Smith", "D.F. Smith", "G. Smith", "A.C. Johnson", "I.K.M. Johnson", "L. Backer"
    };
}
static std::vector<std::string> get_the_families() {
    return { "Backer", "Johnson", "Smith" };
}

static std::vector<std::string> get_the_family_member_for_Backer() {
    return { "Luke" };
}


TEST(add_guest, one_family_only) {

    party::guest_list gl{};

    std::string family = "Johnson";
    for (const auto &name: get_names()) {
        if (name.find(family) != name.npos) {
            gl.add_guest(name);
        }
    }

    ASSERT_THAT(gl.count_guest(), 2);

}

TEST(add_guest, multiple_families) {

    party::guest_list gl{};


    for (const auto &name: get_names()) {
            gl.add_guest(name);
        }


    ASSERT_THAT(gl.count_guest(), 6);

}

TEST(get_family_members, one_family_only) {

    party::guest_list gl{};

    std::string family = "Backer";

    for (const auto &name: get_names()) {
        if (name.find(family) != name.npos) {
            gl.add_guest(name);
        }
    }

    ASSERT_THAT( gl.get_family_members(family), get_the_family_member_for_Backer());
}


TEST(get_guests, one_family_only) {

    party::guest_list gl{};

    std::string family = "Johnson";

    for (const auto &name: get_names()) {
        if (name.find(family) != name.npos) {
            gl.add_guest(name);
        }
    }

    ASSERT_THAT(gl.count_guest(), 2);
}

TEST(get_guests, every_family) {

    party::guest_list gl{};
    for (const auto &name: get_names()) {
        gl.add_guest(name);
        }
    ASSERT_THAT(gl.get_guests(), get_the_guests());

}

TEST(get_families, empty_list) {

    party::guest_list gl{};
    ASSERT_FALSE(gl.get_families()==get_the_families());

}

TEST(get_families, multiple_people_list) {

    party::guest_list gl{};

    for (const auto &name: get_names()) {
            gl.add_guest(name);
    }
    ASSERT_THAT(gl.get_families(), get_the_families());
}

TEST(get_guests, all_families) {

    party::guest_list gl{};

    for (const auto &name: get_names()) {
            gl.add_guest(name);
        }
    ASSERT_THAT(gl.get_guests(), get_the_guests());
}


TEST(remove_all_guests, one_family_only) {

    party::guest_list gl{};

    std::string family = "Johnson";
    for (const auto &name: get_names()) {
        if (name.find(family) != name.npos) {
            gl.add_guest(name);
        }
    }
    for (const auto &name: get_names()) {
        if (name.find(family) != name.npos) {
            gl.remove_guest(name);
        }
    }

    ASSERT_TRUE(gl.count_guest()==0);

}

TEST(remove_all_guests, all_families) {

    party::guest_list gl{};
    for (const auto &name: get_names()) {
        gl.add_guest(name);
    }
    for (const auto &name: get_names()) {
            gl.remove_guest(name);
        }
    ASSERT_THAT(gl.count_guest(), 0);
}


TEST(count_guests, empty_list) {
    party::guest_list gl{};
    ASSERT_THAT(gl.count_guest(), 0);
}

TEST(count_guests, multiple_people_in_list) {
    party::guest_list gl{};
    std::string family = "Smith";
    for (const auto &name: get_names()) {
        if (name.find(family) != name.npos) {
            gl.add_guest(name);
        }
    }
    ASSERT_TRUE(gl.count_guest()>0);
}

TEST(count_families, empty_list) {
    party::guest_list gl{};
    ASSERT_THAT(gl.count_families(), 0);
}

TEST(count_families, multiple_families) {
    party::guest_list gl{};
    std::string family = "Smith";
    std::string family2= "Johnson";
    for (const auto &name: get_names()) {
        if (name.find(family) != name.npos) {
            gl.add_guest(name);
        }

        if (name.find(family2)!= name.npos){
            gl.add_guest(name);
        }
    }
    ASSERT_TRUE(gl.count_families()>0);
}
