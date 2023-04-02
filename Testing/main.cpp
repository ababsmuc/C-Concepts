#include <iostream>
#include "inc/guest_list.h"

#include <string_view>
#include <string>

int main() {
    std::cout << "There's nothing here - go to tests/" << std::endl;


    // name splitting test
    std::string str{"A.J.K. Johnson"};
    std::string_view sv{str};
    std::cout << "|" << sv.substr(0, sv.find(' ')) << "|\n";
    std::cout << "|" << sv.substr(sv.find(' ') + 1) << "|\n";

    return 0;
}
