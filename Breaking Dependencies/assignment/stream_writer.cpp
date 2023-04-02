//
// Created by HP on 22-Sep-22.
//

#include <fstream>
#include "stream_writer.h"

writers::itext_writer &writers::stream_writer::operator<<(std::string_view view) {
    m_output<<view;
    return *this;
}

writers::itext_writer &writers::stream_writer::operator<<(const char *string) {
    m_output<< string;
    return *this;
}

writers::itext_writer &writers::stream_writer::operator<<(char i) {
    m_output<<i;
    return *this;
}

writers::itext_writer &writers::stream_writer::operator<<(int i) {
    m_output<<i;
    return *this;
}

writers::itext_writer &writers::stream_writer::operator<<(double d) {
    m_output<<d;
    return *this;
}
writers::stream_writer::~stream_writer()  {
    m_output.close();
}

writers::stream_writer::stream_writer() {

}

writers::stream_writer::stream_writer(const char *file_name) {
    m_output.open(file_name);
}
