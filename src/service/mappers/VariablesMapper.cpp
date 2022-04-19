#include "service/mappers/VariablesMapper.hpp"

using namespace getit::service::mappers;
using namespace getit::domain;

std::shared_ptr<models::Request> VariablesMapper::map(std::shared_ptr<models::Request> request, std::shared_ptr<models::Variables> variables)
{
    if (variables == nullptr)
        return request;

    this->request = request;
    this->variables = variables;

    for (const auto& variable : this->variables->variables) {
        mapUri(variable);
        mapBody(variable);
        mapHeaders(variable);
    }

    return this->request;
}

void VariablesMapper::mapUri(const std::tuple<std::string, std::string>& variable)
{
    std::string uri = request->getUri();
    uri = replaceVariable(uri, variable);
    request->setUri(uri);
}

void VariablesMapper::mapHeaders(const std::tuple<std::string, std::string>& variable)
{
    std::map<std::string, std::string> headers;

    for (const auto& [header, value] : headers) {
        headers.emplace(
            replaceVariable(header, variable),
            replaceVariable(value, variable)
        );
    }

    request->setHeaders(headers);
}

std::string VariablesMapper::replaceVariable(std::string input, const std::tuple<std::string, std::string>& variable)
{
    boost::format frmt = boost::format("{%1%}") % std::get<0>(variable);
    const auto& variableName = frmt.str();

    boost::replace_all(input, variableName, std::get<1>(variable));

    return input;
}