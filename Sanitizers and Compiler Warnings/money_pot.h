//
// Created by dza02 on 10/8/2021.
//

#ifndef WEEK_06_LESSON_GRADES_H
#define WEEK_06_LESSON_GRADES_H
#include <cstddef>
#include <string>
#include <string_view>
#include "ibank.h"


class money_pot: public ibank {
public:
    money_pot();
    ~money_pot() override;
    double store(std::string_view name, double amount) override;
    double take(std::string_view name, double amount) override;
    [[nodiscard]] double sum(std::string_view name) const override;
    [[nodiscard]] double sum() const override;
private:
    constexpr static std::size_t DEF_CAP{10};
    double* m_amounts;
    std::string* m_names;
    std::size_t m_cap;
    std::size_t m_sz;

    [[nodiscard]] int find_name(std::string_view name) const;
    void resize();
};

#endif //WEEK_06_LESSON_GRADES_H
