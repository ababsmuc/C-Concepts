//
// Created by HP on 15-Sep-22.
//

#include <ctime>
#include "system_time_source.h"
#include "itime_source.h"
#include "logger.h"
namespace time_sources {
    std::string system_time_source::return_timestamp() {
        auto time_point = std::time(nullptr);
        auto local_time = std::localtime(&time_point);
        char buffer[16];
        std::strftime(&buffer[0], sizeof(buffer), "%H:%M:%S", local_time);
        return buffer;
    }

    system_time_source::system_time_source() = default;
}