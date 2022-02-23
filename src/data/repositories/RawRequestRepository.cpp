#include "data/repositories/RawRequestRepository.hpp"

using namespace getit::data::repositories;

RawRequestRepository::RawRequestRepository(std::shared_ptr<domain::contracts::RequestFactory> factory, std::shared_ptr<domain::models::Request> request):
    RequestRepository(std::move(request)),
    factory(std::move(factory))
{

}

void RawRequestRepository::saveRequest(std::string filePath)
{
    const auto& body = std::dynamic_pointer_cast<getit::domain::implementations::RawRequestBody>(request->getBody());
    auto jsonObject = nlohmann::json::object();

    jsonObject[METHOD_NAME] = request->getMethod();
    jsonObject[URI_NAME] = request->getUri();

    jsonObject[BODY_TYPE_NAME] = nlohmann::json::object();
    jsonObject[BODY_TYPE_NAME][CONTENT_TYPE_NAME] = body->getContentType();
    jsonObject[BODY_TYPE_NAME][BODY_NAME] = body->getBody();

    std::ofstream output(filePath);
    output << std::setw(4) << jsonObject << std::endl;
    output.close();
}

std::shared_ptr<getit::domain::models::Request> RawRequestRepository::loadRequest(std::string filePath)
{
    auto jsonObject = nlohmann::json::object();

    std::ifstream input(filePath);
    input >> jsonObject;
    input.close();

    const auto& method = jsonObject[METHOD_NAME];
    const auto& uri = jsonObject[URI_NAME];
    const auto& contentType = jsonObject[BODY_TYPE_NAME][CONTENT_TYPE_NAME];
    const auto& body = jsonObject[BODY_TYPE_NAME][BODY_NAME];

    return this->factory->getRequest(method, uri, contentType, body);
}