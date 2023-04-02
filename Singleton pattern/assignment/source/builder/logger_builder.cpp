//
// Created by dza02 on 9/6/2021.
//

#include "builders/logger_builder.h"
#include "logger.h"
#include "console_writer.h"
#include "decorators/decorator.h"
#include "decorators/runningtime_decorator.h"
#include "decorators/timestamp_decorator.h"
#include <memory>
#include <global/runningtime_provider.h>


builders::logger_builder::logger_builder() :
        m_writer{nullptr}, m_logger{nullptr} {
    reset();
}

builders::ilogger_builder &builders::logger_builder::reset() {

    auto multi_writer = std::make_unique<writers::multi_writer>();
    m_writer = multi_writer.get();

    m_logger = std::make_unique<lib::logger>(std::move(multi_writer));
    return *this;
}

builders::ilogger_builder &builders::logger_builder::with_console_output() {
    if (m_writer) {
        m_writer->add_writer("console", std::make_unique<writers::console_writer>());
    }
    return *this;
}

builders::ilogger_builder &builders::logger_builder::with_file_output(std::string_view file_name) {
    if (m_writer) {
        m_writer->add_writer(std::string{file_name}, std::make_unique<writers::stream_writer>(file_name.data()));
    }
    return *this;
}

//There’s a slight issue that arose when you added support for multiple decorators. Now a user
//        can decorate the same logger multiple times.
builders::ilogger_builder &builders::logger_builder::with_timestamp(builders::ilogger_builder::timestamp_type type) {
    static bool must_decorate = true;
    if (!must_decorate) {
        throw std::logic_error("the logger is already decorated bro.");
    }
    if (!m_logger) {
        return *this;
    }
    switch (type) {
        case timestamp_type::none:
            break;
        case timestamp_type::current_time:


            m_logger = std::make_unique<lib::decorators::timestamp_decorator>(std::move(m_logger));
            must_decorate = false;


            break;
        case timestamp_type::running_time:


            m_logger = std::make_unique<lib::decorators::runningtime_decorator>(std::move(m_logger));
            must_decorate = false;


            break;

    }


    return *this;


}

std::unique_ptr<loggers::ilogger> builders::logger_builder::get() {
    m_writer = nullptr;
    return std::move(m_logger);
}

builders::ilogger_builder &builders::logger_builder::with_writer(std::unique_ptr<io::itext_writer> writer) {

    auto name = std::to_string(global::runningtime_provider::get_instance().running_time().count());
    m_writer->add_writer(name, std::move(writer));
    return *this;
}

builders::ilogger_builder &
builders::logger_builder::with_rolling_log_with_interval(std::chrono::seconds roll_interval) {
    auto name = std::to_string(rand());
    auto logg = std::make_unique<clogger_as_writer>(roll_interval);
    m_writer->add_writer(name, std::move(logg));
    return *this;
}


builders::logger_builder builders::default_builder() {
    return {};
}
