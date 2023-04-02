//
// Created by HP on 14-Sep-22.
//

#ifndef ADVANCED_PROGRAMMING_CONCEPTS_1_ITIME_SOURCE_H
#define ADVANCED_PROGRAMMING_CONCEPTS_1_ITIME_SOURCE_H

#include <string>

namespace the_time {
    class itime_source {
    public:
        virtual std::string return_timestamp() = 0;
        virtual ~itime_source() = default;
    private:

    };




}

#endif //ADVANCED_PROGRAMMING_CONCEPTS_1_ITIME_SOURCE_H




