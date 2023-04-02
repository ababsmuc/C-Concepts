//
// Created by Dawid Zalewski on 8/25/2021.
//

#ifndef LESSON_ILOGGER_H
#define LESSON_ILOGGER_H

#include <string_view>

namespace loggers {
    class ilogger {
    public:
        virtual void log(const std::string_view& msg) const = 0;

        // Always provide a virtual destructor when a class has a virtual fucntion
        virtual ~ilogger() = default;
    };
}


#endif //LESSON_ILOGGER_H
