//
// Created by dza02 on 10/8/2021.
//

#include "money_pot.h"

// constructor, initializes the arrays for storing names and amounts
money_pot::money_pot():
    m_amounts{ new double[DEF_CAP]{0}},
    m_names{ new std::basic_string<char>[DEF_CAP]},
    m_cap{DEF_CAP},
    m_sz{0}
{}

// stores `amount` money for `name`
// if `name` doesn't exist, creates one
double money_pot::store(std::string_view  name, double amount){
    int index = find_name(name);

    // person already exists
    if (index != -1){
        m_amounts[index] += amount;
        return m_amounts[index];
    }

    // person doesn't exist
    resize();

    index = static_cast<int>(m_sz);
    m_sz++;

    m_names[index] = name;
    m_amounts[index] = amount;
    return m_amounts[index];
}

// removes `amount` money from `name`
// if `name` doesn't exist, nothing happens
double money_pot::take(std::string_view name, double amount){
    auto index = find_name(name);

    // person  exists
    if (index != -1){
        auto to_take = m_amounts[index] >= amount ? amount : m_amounts[index];
        m_amounts[index] -= to_take;
        return to_take;
    }
    return 0;
}

// returns amount of money for `name`
// if name doesn't exist, returns 0
double money_pot::sum(std::string_view name) const{
    auto sum{0.0};
    auto index = find_name(name);

    // person  exists
    if (index != -1) {
        sum = m_amounts[index];
    }
    return sum;
}

// returns the sum of money for all persons
double money_pot::sum() const{
    auto sum{0.0};

    if (m_sz != 0) {
        for (std::size_t i = 0; i < m_sz; ++i){
            sum += m_amounts[i];
        }
    }
    return sum;
}

// finds the index of `name`
// if `name` doesn't exist, returns -1
int money_pot::find_name(std::string_view name) const {
    for (std::size_t i=0; i < m_sz; ++i){
        if (m_names[i] == name)
            return static_cast<int>(i);
    }
    return -1;
}

// resizes amounts and names arrays if size is equal to capacity
// takes care of allocation and data copying
void money_pot::resize() {
    if (m_sz == m_cap){
        auto cap = 2*m_cap;
        auto names = new std::string[cap];
        auto amounts = new double[cap];
        std::move(&m_names[0], &m_names[m_sz], &names[0]);
        std::copy(&m_amounts[0], &m_amounts[m_sz], &amounts[0]);
        m_cap = cap;
        m_names = names;
    }
}

money_pot::~money_pot(){
 delete[] m_amounts;
 delete[] m_names;
}
