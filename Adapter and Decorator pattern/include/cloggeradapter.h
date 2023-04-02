#ifndef ASSIGNMENT_CLOGGERADAPTER_H
#define ASSIGNMENT_CLOGGERADAPTER_H

#include <logger.h>
#include "logger.h"
#include "../clib/logger.h"

namespace lib {
    class cloggeradapter: public loggers::ilogger{
    public:
        void log(std::string_view msg) const override ;
        explicit cloggeradapter(std::chrono::seconds roll_interval);

        ~cloggeradapter() override ;

    private:
        lg_logger_t* m_clogger{};
    };
}

#endif //ASSIGNMENT_CLOGGERADAPTER_H
