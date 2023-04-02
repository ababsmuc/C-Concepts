#include <iostream>
#include "assignment.h"
#include <vector>
#include <list>

int main() {
    std::vector numbers{0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    double arr[9]= {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    //Task 1 testing
     std::cout<< task_1::compare(2,2);
     std::cout<< task_1::greater_than(3,2);
     std::cout<< task_1::less_than(5, 4);

   //Task 2 testing
    auto sum = task_2::sum<9>(arr);
    std::cout<< sum;
    //Task 3 testing
    auto sum2 = task_3::sum(arr);
    std::cout<< sum2;
    //Task 4 testing
    auto sum3 = task_4::sum(numbers, 0.0);
    std::cout<< sum3;
    //Task 5_1 testing
    auto sum4 = task_5_1::sum(numbers.begin(), numbers.begin() + 10, 0.0);
    std::cout<< sum4;
    //Task 5_2 testing
    auto sum5 = task_5_2::sum(numbers.begin(), numbers.begin() + 10, 0.0);
    std::cout<< sum5;
    //Task 6 testing
    auto sum6 = task_6::sum(numbers.begin(), numbers.begin() + 10, 0);
    std::cout<< sum6;
    return 0;
}
