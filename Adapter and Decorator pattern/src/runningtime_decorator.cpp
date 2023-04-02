//
// Created by HP on 30-Sep-22.
//

#include <runningtime_decorator.h>
#include <sstream>
#include <iomanip>

void lib::decorators::runningtime_decorator::log(std::string_view msg) const {
    std::ostringstream oss;

    auto running_time = std::chrono::high_resolution_clock::now() - m_currTime;

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(running_time);
    running_time -= seconds;

    auto nano = std::chrono::duration_cast<std::chrono::nanoseconds>(running_time);
    oss << std::setfill('0')
        << seconds.count() << "." << std::setw(12.5);
    oss << nano.count() << ": " << msg;
    auto str = oss.str();
    decorator::log(str);
}


