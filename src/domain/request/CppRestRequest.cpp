#include "domain/request/CppRestRequest.hpp"

#include <utility>
#include <iostream>

using namespace getit::domain::request;

CppRestRequest::CppRestRequest(web::http::client::http_client* client):
    client(client)
{
    
}

CppRestRequest::~CppRestRequest()
{
    if (this->client != nullptr) delete this->client;
}

std::shared_ptr<getit::domain::Response> CppRestRequest::sendRequest(std::shared_ptr<RequestData> data)
{
    if (this->client == nullptr) {
        std::cout << "client == nullptr" << std::endl;
        std::cout << "URI: " << data->getUri() << std::endl;
        this->client = new web::http::client::http_client(data->getUri());
    }
    
    web::http::http_request request = this->buildRequest(data);

    const auto& response = this->client->request(request).get();
    
    return this->buildResponse(response);
}

// void CppRestRequest::send(std::function<void(Response*)> callback)
// {
//     web::http::http_request request = this->buildRequest();  

//     this->client.request(request).then([=](web::http::http_response restResponse) {
//         const auto& response = getit::domain::CppRestRequest::buildResponse(std::move(restResponse));

//         callback(response);
//     });
// }


web::http::http_request CppRestRequest::buildRequest(std::shared_ptr<RequestData> data)
{
    web::http::http_request request;
    request.set_method(data->getMethod());

    this->addHeadersToRequest(&request, data);
    this->addBodyToRequest(&request, data);

    return request;
}

void CppRestRequest::addHeadersToRequest(web::http::http_request* request, std::shared_ptr<RequestData> data)
{
    for (auto const& [header, value]: data->getHeaders()) {
        request->headers().add(header, value);
    }
}

void CppRestRequest::addBodyToRequest(web::http::http_request* request, std::shared_ptr<RequestData> data)
{
    if (data->getRequestBody() != nullptr) {
        request->set_body(data->getRequestBody()->getBody(), data->getRequestBody()->getContentType());
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
