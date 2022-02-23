#include "data/repositories/RawRequestRepository.hpp"

using namespace getit::data::repositories;

RawRequestRepository::RawRequestRepository(std::shared_ptr<domain::contracts::RequestFactory> factory):
    factory(std::move(factory))
{

}

void RawRequestRepository::saveRequest(const std::string& filePath, std::shared_ptr<domain::models::Request> request)
{
    const auto& body = std::dynamic_pointer_cast<getit::domain::implementations::RawRequestBody>(request->getBody());
    auto jsonObject = nlohmann::json::object();

    jsonObject[METHOD_NAME] = request->getMethod();
    jsonObject[URI_NAME] = request->getUri();

    jsonObject[RAW_BODY_TYPE_NAME] = nlohmann::json::object();
    jsonObject[RAW_BODY_TYPE_NAME][CONTENT_TYPE_NAME] = body->getContentType();
    jsonObject[RAW_BODY_TYPE_NAME][BODY_NAME] = body->getBody();

    std::ofstream output(filePath);
    output << std::setw(4) << jsonObject << std::endl;
    output.close();
}

std::shared_ptr<getit::domain::models::Request> RawRequestRepository::loadRequest(const std::string& filePath)
{
    auto jsonObject = nlohmann::json::object();

    std::ifstream input(filePath);
    input >> jsonObject;
    input.close();

    const auto& method = jsonObject[METHOD_NAME];
    const auto& uri = jsonObject[URI_NAME];
    const auto& contentType = jsonObject[RAW_BODY_TYPE_NAME][CONTENT_TYPE_NAME];
    const auto& body = jsonObject[RAW_BODY_TYPE_NAME][BODY_NAME];

    return this->factory->getRequest(method, uri, contentType, body);
}