//
// Created by HP on 30-Sep-22.
//

#ifndef ASSIGNMENT_DECORATOR_H
#define ASSIGNMENT_DECORATOR_H

#include <memory>
#include "../include/ilogger.h"

namespace lib::decorators {
class decorator: public loggers::ilogger {
public:
    void log(std::string_view msg) const override;

    explicit decorator(std::unique_ptr<loggers::ilogger> decorator);

    ~decorator() noexcept override = default;

private:
    std::unique_ptr<loggers::ilogger> m_decorator;
};
}

#endif //ASSIGNMENT_DECORATOR_H
