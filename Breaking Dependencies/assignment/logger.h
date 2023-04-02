//
// Created by Dawid Zalewski on 17/08/2021.
//

#ifndef LESSON_LOGGER_H
#define LESSON_LOGGER_H

#include <string>
#include <iostream>
#include <memory>
#include "ilogger.h"
#include "itime_source.h"
#include "itext_writer.h"
#include "stream_writer.h"
#include <string_view>

namespace lib{
class logger: public loggers::ilogger {
    public:
        logger() noexcept;


    explicit logger(std::unique_ptr<writers::itext_writer> out);

   void set_time_source(std::unique_ptr<the_time::itime_source> some_time) noexcept;

    private:
        std::unique_ptr<the_time::itime_source> m_itimeSource;
        std::unique_ptr<writers::itext_writer> m_writer;

        void log(const std::string_view &msg) const override;

};
}

#endif //LESSON_LOGGER_H
