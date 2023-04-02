#ifndef WEEK_04_ASSIGNMENT_REDUCER_H
#define WEEK_04_ASSIGNMENT_REDUCER_H

#include <vector>

namespace reducer {
    /**
     * Calculates the sum of double numbers
     * @param init the initial value of the sum
     * @param numbers a vector of double's to be added
     * @return the sum of \ref init and \ref numbers
     */
    double reduce_sum(double init, const std::vector<double>& numbers) {
        for (auto num: numbers)
            init += num;
        return init;
    }


    /**
     * Calculates the sum of integers
     * @param init the initial value of the sum
     * @param numbers a vector of integers to be added
     * @return the sum of \ref init and \ref numbers
     */
    int reduce_sum(int init, const std::vector<int>& numbers) {
        for (auto num: numbers)
            init += num;
        return init;
    }

    /**
     * Calculates the product of double numbers
     * @param init the initial value of the product
     * @param numbers a vector of double's to be multiplied
     * @return the product of \ref init and \ref numbers
     * @note this implementation is incorrect, tests are expected to fail
     */
    double reduce_product(double init, const std::vector<double>& numbers) {
        if (init == 0) init = 1.0;
        for (auto num: numbers)
            init *= num;
        return init;
    }

    /**
     * Calculates the product of integer numbers
     * @param init the initial value of the product
     * @param numbers a vector of int's to be multiplied
     * @return the product of \ref init and \ref numbers
     */
    int reduce_product(int init, const std::vector<int>& numbers) {
        for (auto num: numbers)
            init *= num;
        return init;
    }
}

#endif //WEEK_04_ASSIGNMENT_REDUCER_H
