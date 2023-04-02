//
// Created by Dawid Zalewski on 22/08/2021.
//

#include "logger.h"

namespace lib{

    void logger::log(const std::string_view& msg) const{
        *m_writer << '[';
        *m_writer << m_itimeSource->return_timestamp();
        *m_writer << "]: " <<  msg << '\n';
    }


    void logger::set_time_source(std::unique_ptr<the_time::itime_source> some_time) noexcept {
        m_itimeSource = std::move(some_time);
    }

    logger::logger(std::unique_ptr<writers::itext_writer> out)
            : m_writer{std::move(out)} {

    }


}
