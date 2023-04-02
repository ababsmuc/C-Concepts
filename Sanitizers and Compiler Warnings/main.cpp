#include <iostream>
#include "money_pot.h"

int main() {

    ibank* bank = new money_pot{};
    bank->store("alice", 100);
    bank->store("bob", 200);
    bank->store("cindy", 300);
    bank->store("derek", 400);

    bank->store("alice", 500);
    bank->store("cindy", 600);

    std::cout << "alice has: " << bank->sum("alice") << '\n';
    bank->take("alice", 100);
    std::cout << "after taking some money alice has: " << bank->sum("alice") << '\n';

    std::cout << "altogether they have: " << bank->sum()<< '\n';

    delete bank;
    return 0;
}
