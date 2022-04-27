#pragma once

#include <list>
#include <map>
#include <string>

#include "domain/models/Variable.hpp"

using namespace getit::domain::models;

namespace getit::presentation::windows
{
    struct IVariablesWindowView
    {
        public:
            virtual ~IVariablesWindowView() = default;

            virtual std::map<std::string, std::list<std::shared_ptr<Variable>>> getVariables() = 0;
            virtual void setVariables(std::map<std::string, std::list<std::shared_ptr<Variable>>> variables) = 0;
    };
}