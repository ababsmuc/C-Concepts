//
// Created by dza02 on 9/5/2021.
//

#include "logger.h"
#include "program.h"
#include "console_writer.h"
#include "stream_writer.h"
#include "file_writer_adapter.h"
#include "multi_writer.h"
#include "decorators/timestamp_decorator.h"
#include "decorators/runningtime_decorator.h"
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <cstdbool>


#include "clib/logger.h"

#include "builders/logger_builder.h"


void demo_lg_logger(){
    lg_logger_t* logger{nullptr};
    lg_create(&logger, 3);
    lg_set_debug_output(logger, true);

    lg_log(logger, "Hello world");
    std::this_thread::sleep_for(std::chrono::seconds{6});
    lg_log(logger, "Once more...");
    std::this_thread::sleep_for(std::chrono::seconds{6});
    lg_log(logger, "And once more...");

    lg_destroy(&logger);
}


int main(){



     //Test your implementation by creating logger with a custom itext_writer in the main function.
//auto log= builders::logger_builder{};
//log.with_console_output().get()->log("yo man");
//


//    auto log = builders::default_builder()
//            .with_console_output()
//            .with_file_output("out5.txt")
//            .with_writer(std::make_unique<writers::stream_writer>("custom.txt"))
//            .with_timestamp(builders::ilogger_builder::timestamp_type::current_time)
//            .with_timestamp(builders::ilogger_builder::timestamp_type::current_time)
//            .get();

}