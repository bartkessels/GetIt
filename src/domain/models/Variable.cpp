#include "domain/models/Variable.hpp"

#include <utility>

using namespace getit::domain::models;

Variable::Variable(std::string name, std::string value):
    name(std::move(name)),
    value(std::move(value))
{

}

std::string Variable::apply(std::string input)
{
    boost::format frmt = boost::format("{%1%}") % name;
    const auto& variableName = frmt.str();

    boost::replace_all(input, variableName, value);

    return input;
}