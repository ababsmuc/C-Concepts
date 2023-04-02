//
// Created by HP on 22-Sep-22.
//

#ifndef ADVANCED_PROGRAMMING_CONCEPTS_1_STREAM_WRITER_H
#define ADVANCED_PROGRAMMING_CONCEPTS_1_STREAM_WRITER_H
#include "itext_writer.h"
#include <fstream>

namespace writers {
    class stream_writer: public itext_writer{
    public:
        stream_writer();

        explicit stream_writer(const char * file_name);
        itext_writer &operator<<(std::string_view view) override;

        itext_writer &operator<<(const char *string) override;

        itext_writer &operator<<(char i) override;

        itext_writer &operator<<(int i) override;

        itext_writer &operator<<(double d) override;

         ~stream_writer() override;

    private:
        std::ofstream m_output;
    };
}

#endif //ADVANCED_PROGRAMMING_CONCEPTS_1_STREAM_WRITER_H
