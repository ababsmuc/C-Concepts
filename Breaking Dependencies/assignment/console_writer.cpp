//
// Created by HP on 22-Sep-22.
//

#include "console_writer.h"

writers::itext_writer &writers::console_writer::operator<<(std::string_view view) {
    std::cout<< view;
    return *this;
}

writers::itext_writer &writers::console_writer::operator<<(const char *string) {
    std::cout<<string;
    return *this;
}

writers::itext_writer &writers::console_writer::operator<<(char i) {
    std::cout<<i;
    return *this;
}

writers::itext_writer &writers::console_writer::operator<<(int i) {
    std::cout<<i;
    return *this;
}

writers::itext_writer &writers::console_writer::operator<<(double d) {
    std::cout<<d;
    return *this;
}
