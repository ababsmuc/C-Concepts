//
// Created by Dawid Zalewski on 9/5/2021.
//

/*Get rid of the <ctime> dependency in logger by creating a new abstract class itime_source
and its concrete implementation.
Get rid of the std::string usage in logger and ilogger
Get rid of the ostream dependency in logger by creating a new abstract class itext_writer
and two implementations of it.*/

#include "logger.h"
#include "program.h"
#include "console_writer.h"
#include "system_time_source.h"
#include "stream_writer.h"
#include <iostream>
#include <memory>

int main(){
    auto writer = std::make_unique<writers::stream_writer>("log.txt");
    auto logger = std::make_unique<lib::logger>(std::move(writer));
    auto system= std::make_unique<time_sources::system_time_source>();
    logger->set_time_source(std::move(system));
    program prog{ std::move(logger) };
    prog.run();
}