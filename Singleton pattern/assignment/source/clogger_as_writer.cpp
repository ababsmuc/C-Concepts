//
// Created by HP on 06-Oct-22.
//

#include <chrono>
#include "clogger_as_writer.h"

io::itext_writer & writers::clogger_as_writer::operator<<(std::string_view view) {
    lg_log(m_clogger_writer, std::string(view).c_str());
    return *this;
}

io::itext_writer & writers::clogger_as_writer::operator<<(const char *string) {
    lg_log(m_clogger_writer, string);
    return *this;
}

io::itext_writer &  writers::clogger_as_writer::operator<<(char c) {
    char buffer[16];
    sprintf(&buffer[0], "%c", c);
    lg_log(m_clogger_writer, &buffer[0]);
    return *this;
}

io::itext_writer &  writers::clogger_as_writer::operator<<(int n) {
    char buffer[16];
    sprintf(&buffer[0], "%d", n);
    lg_log(m_clogger_writer, &buffer[0]);
    return *this;
}

io::itext_writer &  writers::clogger_as_writer::operator<<(io::flush_t flush) {
    return *this;
}

writers::clogger_as_writer::clogger_as_writer(std::chrono::seconds roll_interval) {
    auto result = lg_create(&m_clogger_writer, roll_interval.count());
    if (result == lgr_error) {
        throw std::runtime_error("logger not created");

    }
}

writers::clogger_as_writer::~clogger_as_writer() {

    lg_destroy(&m_clogger_writer);
}
