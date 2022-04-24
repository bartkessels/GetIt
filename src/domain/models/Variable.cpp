#include "domain/models/Variable.hpp"

#include <utility>

using namespace getit::domain::models;

Variable::Variable(std::string  name, std::string value):
    name(std::move(name)),
    value(std::move(value))
{

}

std::string Variable::apply(std::string input)
{
    if (input.empty())
        return input;

    boost::format variableFormat = boost::format("{%1%}") % name;
    boost::replace_all(input, variableFormat.str(), value);

    return input;
}