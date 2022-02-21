#include "domain/factories/RequestFactory.hpp"

using namespace getit::domain::factories;

std::shared_ptr<getit::domain::models::Request> RequestFactory::getRequest(const std::string& method, const std::string& uri, const std::string& body)
{
    const auto& requestBody = std::make_shared<implementations::RawRequestBody>();
    const auto& request = RequestFactory::getRequest(method, uri);

    requestBody->setBody(body);

    request->setBody(requestBody);

    return request;
}

std::shared_ptr<getit::domain::models::Request> RequestFactory::getRequest(const std::string& method, const std::string& uri, const std::string& body, const std::string& contentType)
{
    const auto& requestBody = std::make_shared<implementations::RawRequestBody>(contentType);
    const auto& request = RequestFactory::getRequest(method, uri);

    requestBody->setBody(body);

    request->setBody(requestBody);

    return request;
}

std::shared_ptr<getit::domain::models::Request> RequestFactory::getRequest(const std::string& method, const std::string& uri, std::map<std::string, std::string> elements, std::map<std::string, std::string> files, const std::string& boundary)
{
    const auto& requestBody = std::make_shared<implementations::FormDataRequestBody>(boundary);
    const auto& request = RequestFactory::getRequest(method, uri);

    requestBody->setElements(elements);
    requestBody->setFiles(files);

    request->setBody(requestBody);

    return request;
}

std::shared_ptr<getit::domain::models::Request> RequestFactory::getRequest(const std::string& method, const std::string& uri)
{
    const auto& request = std::make_shared<models::Request>();

    request->setMethod(method);
    request->setUri(uri);

    return request;
}