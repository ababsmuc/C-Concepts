//
// Created by HP on 15-Sep-22.
//

#ifndef ADVANCED_PROGRAMMING_CONCEPTS_1_SYSTEM_TIME_SOURCE_H
#define ADVANCED_PROGRAMMING_CONCEPTS_1_SYSTEM_TIME_SOURCE_H

#include "itime_source.h"

namespace time_sources {
    class system_time_source : public the_time::itime_source {

    public:
        system_time_source();

        std::string return_timestamp() override;
    };

}
#endif //ADVANCED_PROGRAMMING_CONCEPTS_1_SYSTEM_TIME_SOURCE_H
