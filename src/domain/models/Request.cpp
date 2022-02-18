#include "domain/models/Request.hpp"

using namespace getit::domain::models;

void Request::setMethod(std::string method)
{
    this->method = method;
}

void Request::setUri(std::string uri)
{
    this->uri = uri;
}

void Request::addHeader(const std::string& header, const std::string& value)
{
    this->headers.insert({header, value});
}

void Request::setHeaders(const std::map<std::string, std::string>& headers)
{
    for (const auto& [header, value] : headers) {
        this->addHeader(header, value);
    }
}

void Request::setBody(std::shared_ptr<RequestBody> body)
{
    this->body = body;
}

std::string Request::getMethod()
{
    return this->method;
}

std::string Request::getUri()
{
    return this->uri;
}

std::map<std::string, std::string> Request::getHeaders()
{
    return this->headers;
}

std::shared_ptr<RequestBody> Request::getBody()
{
    return this->body;
}