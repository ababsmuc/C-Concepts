#include "name.h"
#include <sstream>
#include <stdexcept>
#include <string>

party::name::name(const std::string& full_name): m_first_names{}, m_last_name{}{
    std::istringstream iss{full_name};
    std::string name;
    while(iss >> name)
        m_first_names.push_back(std::move(name));

    if (m_first_names.size() < 2)
        throw std::invalid_argument("At least two names should be provided");

    m_last_name = std::move(m_first_names.back());
    m_first_names.pop_back();
}


std::string party::name::initials() const {
    std::ostringstream oss{};

    for (auto&& name: m_first_names)
        oss << name[0] << '.';

    return oss.str();
}


std::string party::name::full_name() const {
    std::ostringstream oss{};

    for (auto&& name: m_first_names)
        oss << name << ' ';

    oss << m_last_name;

    return oss.str();
}

const std::string& party::name::last_name() const {
    return m_last_name;
}

const std::vector<std::string>& party::name::first_names() const {
    return m_first_names;
}

bool party::name::operator==(const party::name& other) const {
    return full_name() == other.full_name();
}

bool party::name::operator!=(const party::name& other) const {
    return !(*this == other);
}

