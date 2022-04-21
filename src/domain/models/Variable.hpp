#pragma once

#include <boost/algorithm/string/replace.hpp>
#include <boost/format.hpp>
#include <string>

namespace getit::domain::models
{
    class Variable
    {
        public:
            Variable(std::string name, std::string value);
            ~Variable() = default;

            std::string name;
            std::string value;

            /***
             * Replace the variable name with the value
             * for the input
             *
             * Format: {variable-name}
             * @param input string that contains the variable
             * @return input with the variable replaced by the value
             */
            std::string apply(std::string input);
    };
}