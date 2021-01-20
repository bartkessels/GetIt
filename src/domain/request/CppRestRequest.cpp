#include "domain/request/CppRestRequest.hpp"

#include <utility>

using namespace getit::domain::request;

std::shared_ptr<getit::domain::Response> CppRestRequest::sendRequest(std::shared_ptr<RequestData> data)
{
    const auto& client = std::make_unique<web::http::client::http_client>(data->getUri());
    const auto& request = this->buildRequest(data);
    const auto& response = client->request(*request).get();
    
    return this->buildResponse(response);
}

std::shared_ptr<web::http::http_request> CppRestRequest::buildRequest(std::shared_ptr<RequestData> data)
{
    const auto& request = std::make_shared<web::http::http_request>();

    request->set_method(data->getMethod());

    this->addHeadersToRequest(request, data);
    this->addBodyToRequest(request, data);

    return request;
}

void CppRestRequest::addHeadersToRequest(std::shared_ptr<web::http::http_request> request, std::shared_ptr<RequestData> data)
{
    for (auto const& [header, value]: data->getHeaders()) {
        request->headers().add(header, value);
    }
}

void CppRestRequest::addBodyToRequest(std::shared_ptr<web::http::http_request> request, std::shared_ptr<RequestData> data)
{
    if (data->getBody() != nullptr) {
        request->set_body(data->getBody()->getBody(), data->getBody()->getContentType());
    }
}

std::shared_ptr<getit::domain::Response> CppRestRequest::buildResponse(web::http::http_response restResponse)
{
    const auto& response = std::make_shared<getit::domain::Response>();
    bool ignoreContentType = true;

    response->body = restResponse.extract_string(ignoreContentType).get();
    response->statusCode = restResponse.status_code();

    for (auto const& [header, value]: restResponse.headers()) {
        response->headers.insert({header, value});
    }

    return response;
}
