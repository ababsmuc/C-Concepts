//
// Created by dza02 on 10/8/2021.
//

#ifndef WEEK_06_ASSIGNMENT_IBANK_H
#define WEEK_06_ASSIGNMENT_IBANK_H

#include <string_view>

class ibank {
public:
    virtual double store(std::string_view name, double amount) = 0;
    virtual double take(std::string_view name, double amount) = 0;
    [[nodiscard]] virtual double sum(std::string_view name) const = 0;
    virtual ~ibank()=default;

    [[nodiscard]] virtual double sum() const=0;
};




#endif //WEEK_06_ASSIGNMENT_IBANK_H
