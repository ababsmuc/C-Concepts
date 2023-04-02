#ifndef WEEK_04_ASSIGNMENT_GUEST_LIST_H
#define WEEK_04_ASSIGNMENT_GUEST_LIST_H

#include <vector>
#include <string>
#include <map>

#include "name.h"

namespace party{
    /**
     * This class maintains a list of guests. Guests are grouped into families based on their last names.
     */
    class guest_list {
    public:
        guest_list() = default;

        /**
         * Adds a guest to this guest list
         * @param full_name full name of a guest
         * @return number of guests on this guest list with the same last name as the guest just added
         * @note It is assumed that guests with the same last name belong to one family.
         * @note It is not an error to add multiple guests with the same name
         */
        std::size_t add_guest(const std::string& full_name );

        /**
         * Removes a guest with a given full name
         * @param full_name the full name of a guest to remove
         * @throws std::out_of_range if there's not family with the same last name as the guest in the guest list
         * @throws std::runtime_error if a guest with the given full name doesn't exist.
         */
        void remove_guest(const std::string& full_name);

        /**
         * Lists all the families on this guest list
         * @return a list of unique last names of all the guests
         * @note It is assumed that persons with the same last name belong to the same family.
         */
        std::vector<std::string> get_families() const;

        /**
         * Lists all the first names of guests belonging to one family
         * @param last_name the family last name for which to obtain a member list
         * @return the first names of one family
         * @throws std::invalid_argument if there is no guests with this last name
         */
        std::vector<std::string> get_family_members(const std::string& last_name) const;


        /**
         * Lists all the guests in alphabetical order
         * @return list of all the guests, names are formatted as "<Initials> <Last Name>"
         * @note names in the list are sorted first by the last name and then by initials
         */
        std::vector<std::string> get_guests() const;

        /**
         * Returns the number of guests
         * @return number of guests
         */
        std::size_t count_guest() const;

        /**
         * Returns the number of families
         * @return number of families
         */
        std::size_t count_families() const;

    private:
        std::map<std::string, std::vector<name>> m_guests;
    };
}
#endif //WEEK_04_ASSIGNMENT_GUEST_LIST_H
