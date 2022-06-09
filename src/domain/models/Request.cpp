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

void Request::addHeader(std::string header, std::string value)
{
    this->headers.emplace(header, value);
}

void Request::setHeaders(std::map<std::string, std::string> headers)
{
    this->headers = headers;
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