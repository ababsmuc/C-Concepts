//
// Created by dza02 on 9/24/2021.
//

#include "guest_list.h"
#include "name.h"

#include <numeric>
#include <algorithm>
#include <sstream>


std::size_t party::guest_list::add_guest(const std::string& full_name) {
    name guest{full_name};
    auto& family = m_guests[guest.last_name()];
    family.push_back(std::move(guest));
    return family.size();
}

void party::guest_list::remove_guest(const std::string& full_name) {
    name guest{full_name};

    // this will throw std::out_of_range if a family with this last name doesn't exits
    auto& family = m_guests.at(guest.last_name());

   auto iter = std::find_if(family.begin(), family.end(),
                                 [&](const auto& guest){ return guest.full_name() == full_name; });
    if (iter != m_guests[full_name].end()){
        family.erase(iter);
    }
    else{
        throw std::runtime_error("A guest with the given name is not on the list and cannot be removed");
    }
}

std::vector<std::string> party::guest_list::get_families() const {
    std::vector<std::string> result{};
    std::transform(m_guests.begin(), m_guests.end(), std::back_inserter(result),
                   [](const auto& family) { return family.first; });
    return result;
}

std::vector<std::string> party::guest_list::get_family_members(const std::string& last_name) const {
    if (m_guests.count(last_name) == 0){
        throw std::invalid_argument("The specified family is not on the guest list.");
    }

    std::vector<std::string> result{};
    for (const auto& guest: m_guests.at(last_name)){
        std::ostringstream oss{};
        auto add_space{false};
        for (const auto& first_name: guest.first_names()){
            add_space = !add_space || static_cast<bool>(oss << ' ');
            oss << first_name;
        }
        result.push_back(oss.str());
    }
    return result;
}

std::vector<std::string> party::guest_list::get_guests() const {
    std::vector<std::string> result;

    for (const auto& [last_name, members]: m_guests){
        for (const auto& guest: members){
            result.push_back(guest.initials() + " " + last_name);
        }
    }

    std::sort(result.begin(), result.end(),
              [](std::string_view a, std::string_view b){
                return a.substr(0, a.find(' ')) < b.substr(0, b.find(' ')) ||
                    a.substr(1 + a.find(' ')) > b.substr(1 + b.find(' '));
                });

    return result;
}

std::size_t party::guest_list::count_guest() const {
    auto count=0;
    for (const auto& [last_name, members]: m_guests){
        for (const auto& guest: members){
            count++;
        }
    }
    return count;
}

std::size_t party::guest_list::count_families() const {
    return m_guests.size();
}
