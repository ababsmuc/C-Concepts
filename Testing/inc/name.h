#ifndef WEEK_04_ASSIGNMENT_NAME_H
#define WEEK_04_ASSIGNMENT_NAME_H

#include <vector>
#include <string>

namespace party {

    /**
     * Represents a full name of a person
     */
    class name{
    public:
        /**
         * Initializes name instance by parsing a name into first names and a last name
         * @param full_name full name, the last world is interpreted as a last name
         */
        name(const std::string& full_name);

        /**
         * Creates and returns initials based on the first names
         * @return Initials
         */
        std::string initials() const;

        /**
         * Creates and returns full name
         * @return full name
         */
        std::string full_name() const;

        /**
         * Returns last name
         * @return last name
         */
        const std::string& last_name() const;

        /**
         * Returns first names' vector
         * @return first names
         */
        const std::vector<std::string>& first_names() const;

        /**
         * Equality comparison
         * @param other other name object to compare with
         * @return true if the first names and the last name are the same, false otherwise
         */
        bool operator==(const name& other) const;

        /**
         * Equality comparison
         * @param other other name object to compare with
         * @return true if any of the first names or the last name are the different, false otherwise
         */
        bool operator!=(const name& other) const;


    private:
        std::vector<std::string> m_first_names;
        std::string m_last_name;
    };

}

#endif //WEEK_04_ASSIGNMENT_NAME_H
