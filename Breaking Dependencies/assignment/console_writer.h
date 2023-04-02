//
// Created by HP on 22-Sep-22.
//

#ifndef ADVANCED_PROGRAMMING_CONCEPTS_1_CONSOLE_WRITER_H
#define ADVANCED_PROGRAMMING_CONCEPTS_1_CONSOLE_WRITER_H

#include "itext_writer.h"

namespace writers {
    class console_writer : public itext_writer{
    public:
        itext_writer &operator<<(const char *string) override;

        itext_writer &operator<<(char i) override;

        itext_writer &operator<<(int i) override;

        itext_writer &operator<<(double d) override;

        ~console_writer() override = default;

    public:
        itext_writer &operator<<(std::string_view view) override;
    };

}
#endif //ADVANCED_PROGRAMMING_CONCEPTS_1_CONSOLE_WRITER_H
