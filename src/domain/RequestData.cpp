#include "domain/RequestData.hpp"

#include <iostream>

using namespace getit::domain;

void RequestData::setMethod(std::string method)
{
    this->method = method;
}

void RequestData::setUri(std::string uri)
{
    this->uri = uri;
}

void RequestData::addOrUpdateHeader(std::string header, std::string value)
{
    this->headers.insert({header, value});
}

void RequestData::setBody(std::shared_ptr<RequestBody> body)
{
    this->requestBody = body;
}



std::string RequestData::getMethod()
{
    return this->method;
}

std::string RequestData::getUri()
{
    return this->uri;
}

std::map<std::string, std::string> RequestData::getHeaders()
{
    return this->headers;
}

std::shared_ptr<RequestBody> RequestData::getRequestBody()
{
    return this->requestBody;
}