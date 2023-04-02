//
// Created by HP on 14-Sep-22.
//

#ifndef ADVANCED_PROGRAMMING_CONCEPTS_1_ITEXT_WRITER_H
#define ADVANCED_PROGRAMMING_CONCEPTS_1_ITEXT_WRITER_H
#include <iostream>
#include <string_view>

namespace writers {
    class itext_writer {
    public:
        virtual itext_writer &operator<<(std::string_view) = 0;

        virtual itext_writer &operator<<(const char *) = 0;

        virtual itext_writer &operator<<(char) = 0;

        virtual itext_writer &operator<<(int) = 0;

        virtual itext_writer &operator<<(double) = 0;

        virtual ~itext_writer() = default;
    };

}
#endif //ADVANCED_PROGRAMMING_CONCEPTS_1_ITEXT_WRITER_H
