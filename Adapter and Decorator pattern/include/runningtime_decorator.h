//
// Created by HP on 30-Sep-22.
//

#ifndef ASSIGNMENT_RUNNINGTIME_DECORATOR_H
#define ASSIGNMENT_RUNNINGTIME_DECORATOR_H

#include <chrono>
#include "decorator.h"

namespace lib::decorators {
    class runningtime_decorator: public lib::decorators::decorator {

    public:
        using decorator::decorator;

        void log(std::string_view msg) const override;

    private:
        static inline std::chrono::time_point<std::chrono::high_resolution_clock> m_currTime= std::chrono::high_resolution_clock::now();
    };
}

#endif //ASSIGNMENT_RUNNINGTIME_DECORATOR_H
