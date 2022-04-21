#include "domain/models/Request.hpp"

using namespace getit::domain::models;

void Request::setMethod(const std::string& method)
{
    this->method = method;
}

void Request::setUri(const std::string& uri)
{
    this->uri = uri;
}

void Request::addHeader(const std::string& header, const std::string& value)
{
    this->headers.emplace(header, value);
}

void Request::setVariables(std::list<std::shared_ptr<Variable>> variables)
{
    this->variables = variables;
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

std::list<std::shared_ptr<Variable>> Request::getVariables()
{
    return this->variables;
}

std::map<std::string, std::string> Request::getHeaders()
{
    return this->headers;
}

std::shared_ptr<RequestBody> Request::getBody()
{
    return this->body;
}