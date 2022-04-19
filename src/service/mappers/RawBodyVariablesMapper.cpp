#include "service/mappers/RawBodyVariablesMapper.hpp"

using namespace getit::service::mappers;
using namespace getit::domain::implementations;

void RawBodyVariablesMapper::mapBody(const std::tuple<std::string, std::string>& variable)
{
    auto body = std::dynamic_pointer_cast<getit::domain::implementations::RawRequestBody>(request->getBody());

    const auto& newBody = replaceVariable(body->getBody(), variable);
}


const std::shared_ptr<RawRequestBody>& RawBodyVariablesMapper::mapElements(const std::shared_ptr<RawRequestBody>& body, const std::tuple<std::string, std::string>& variable)
{

}

const std::shared_ptr<RawRequestBody>& RawBodyVariablesMapper::mapFiles(const std::shared_ptr<RawRequestBody>& body, const std::tuple<std::string, std::string>& variable)
{

}