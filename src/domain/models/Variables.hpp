#pragma once

#include <map>
#include <string>

namespace getit::domain::models
{
    class Variables
    {
        public:
            ~Variables() = default;

            std::map<std::string, std::string> variables;
    };
}