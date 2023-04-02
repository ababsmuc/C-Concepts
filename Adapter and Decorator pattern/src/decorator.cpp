//
// Created by HP on 30-Sep-22.
//



#include <string_view>
#include "../include/decorator.h"
#include "../include/ilogger.h"

void lib::decorators::decorator::log(std::string_view msg) const {
    m_decorator->log(msg);
}

lib::decorators::decorator::decorator(std::unique_ptr<loggers::ilogger> decorator):
m_decorator{std::move(decorator)}
{

}
