//
// Created by HP on 06-Oct-22.
//

#ifndef ASSIGNMENT_CLOGGER_AS_WRITER_H
#define ASSIGNMENT_CLOGGER_AS_WRITER_H


#include <logger.h>
#include "../clib/logger.h"
namespace writers {
    class clogger_as_writer : public io::itext_writer {
    public:
        explicit clogger_as_writer(std::chrono::seconds roll_interval);

        ~clogger_as_writer() override;

        itext_writer &operator<<(std::string_view view) override;

        itext_writer &operator<<(const char *string) override;

        itext_writer &operator<<(char c) override;

        itext_writer &operator<<(int n) override;

        itext_writer &operator<<(io::flush_t flush) override;

    private:
        lg_logger_t *m_clogger_writer{};
    };
}

#endif //ASSIGNMENT_CLOGGER_AS_WRITER_H
