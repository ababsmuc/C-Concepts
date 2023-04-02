#include <chrono>
#include "cloggeradapter.h"

void lib::cloggeradapter::log(std::string_view msg) const {
    lg_log(m_clogger,std::string(msg).c_str());
}

lib::cloggeradapter::cloggeradapter(std::chrono::seconds roll_interval)
{
       auto result = lg_create(&m_clogger, roll_interval.count());
       if (result == lgr_error) {
           throw std::runtime_error("Error!");
       }
   }



lib::cloggeradapter::~cloggeradapter()
{
    lg_destroy(&m_clogger);

}