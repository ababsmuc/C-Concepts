#include <gtest/gtest.h>
#include "reducer.h"

TEST(reducer_sum_int, empty_vector_1){
    std::vector<int> vec{};
    int init = 0;
    ASSERT_EQ(init, reducer::reduce_sum(init, vec)) << "Empty vector should return the initial value";
}

TEST(reducer_sum_int, empty_vector_2){
    std::vector<int> vec{};
    int init = 42;
    ASSERT_EQ(init, reducer::reduce_sum(init, vec)) << "Empty vector should return the initial value";
}

TEST(reducer_sum_dbl, empty_vector_1){
    std::vector<double> vec{};
    double init = 0;
    ASSERT_DOUBLE_EQ(init, reducer::reduce_sum(init, vec)) << "Empty vector should return the initial value";
}

TEST(reducer_sum_dbl, empty_vector_2){
    std::vector<double> vec{};
    double init = 42;
    ASSERT_DOUBLE_EQ(init, reducer::reduce_sum(init, vec)) << "Empty vector should return the initial value";
}

TEST(reducer_prod_int, empty_vector_1){
    std::vector<int> vec{};
    int init = 0;
    ASSERT_EQ(init, reducer::reduce_product(init, vec)) << "Empty vector should return the initial value";
}

TEST(reducer_prod_int, empty_vector_2){
    std::vector<int> vec{};
    int init = 42;
    ASSERT_EQ(init, reducer::reduce_sum(init, vec)) << "Empty vector should return the initial value";
}

TEST(reducer_prod_dbl, empty_vector_2){
    std::vector<double> vec{};
    double init = 42;
    ASSERT_DOUBLE_EQ(init, reducer::reduce_product(init, vec)) << "Empty vector should return the initial value";
}

TEST(reducer_prod_dbl, empty_vector_1){
    std::vector<double> vec{0};
    double init = 0;
    ASSERT_DOUBLE_EQ(init, reducer::reduce_product(init, vec)) << "Empty vector should return the initial value";
}


TEST(reducer_sum_int, vector_1){
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int init = 0;
    const int sum = 55;
    ASSERT_EQ(init + sum, reducer::reduce_sum(init, vec)) << "The sum of the first 10 ints should be 55";
}

TEST(reducer_sum_int, vector_2){
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int init = 42;
    const int sum = 55;
    ASSERT_EQ(init + sum, reducer::reduce_sum(init, vec)) << "The sum should be sum(1..10) + 42";
}

TEST(reducer_sum_int, vector_3){
    std::vector<int> vec{1, -2, 3, -4, 5, -6, 7, -8, 9, -10};
    int init = 0;
    const int sum = -5;
    ASSERT_EQ(init + sum, reducer::reduce_sum(init, vec)) << "Summing of positive and negative numbers";
}

TEST(reducer_prod_int, vector_1){
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int init = 0;
    const int prod = 55;
    ASSERT_EQ(init * prod, reducer::reduce_product(init, vec)) << "The product of the first 10 ints should be 55";
}

TEST(reducer_prod_int, vector_2){
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int init = 42;
    const int prod = 3628800;
    ASSERT_EQ(init * prod, reducer::reduce_product(init, vec)) << "The product should be product(1..10) * 42";
}

TEST(reducer_prod_int, vector_3){
    std::vector<int> vec{1, -2, 3, -4, 5, -6, 7, -8, 9, -10};
    int init = 0;
    const int prod = 3628800;
    ASSERT_EQ(init * prod, reducer::reduce_product(init, vec)) << "Multiplication of positive and negative numbers";
}


TEST(reducer_prod_dbl, vector_1){
    std::vector<double> vec{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    int init = 0.0;
    const int prod = 3628800.0;
    ASSERT_DOUBLE_EQ(prod, reducer::reduce_product(init, vec)) << "The product of the first 10 ints should be 0";
}

TEST(reducer_prod_dbl, vector_2){
    std::vector<double> vec{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    int init = 42.0;
    const int prod = 3628800.0;
    ASSERT_DOUBLE_EQ(init * prod, reducer::reduce_product(init, vec)) << "The product should be multiplication(1..10) * 42";
}

TEST(reducer_prod_dbl, vector_3){
    std::vector<double> vec{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    int init = 0.0;
    const int prod = 3628800;
    ASSERT_DOUBLE_EQ(prod, reducer::reduce_product(init, vec)) << "Product of positive and negative numbers";
}

TEST(reducer_sum_dbl, vector_1){
    std::vector vec{0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
    double init = 0;
    const double sum = 5.5;
    ASSERT_DOUBLE_EQ(init + sum, reducer::reduce_sum(init, vec)) << "The sum of the first 10 dbl fractions  should be 5.5";
}

TEST(reducer_sum_dbl, vector_2){
    std::vector vec{0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10};
    double init = 0.42;
    const double sum = 0.55;
    ASSERT_DOUBLE_EQ(init + sum, reducer::reduce_sum(init, vec)) << "The sum should be sum(0.01..0.1) + 0.42";
}

TEST(reducer_sum_dbl, vector_3){
    std::vector<double> vec{1, -2, 3, -4, 5, -6, 7, -8, 9, -10};
    double init = 0;
    const double sum = -5;
    ASSERT_DOUBLE_EQ(init + sum, reducer::reduce_sum(init, vec)) << "Summing of positive and negative numbers";
}


TEST(dblt_numbers, sum){
    ASSERT_DOUBLE_EQ(1.0, 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 ) << "One should be one";
}