#include "domain/RequestData.hpp"

using namespace getit::domain;

void RequestData::setMethod(std::string method)
{
    this->method = method;
}

void RequestData::setUri(std::string uri)
{
    this->uri = uri;
}

void RequestData::addHeader(std::string header, std::string value)
{
    this->headers.push_back(
        {header, value}
    );
}

void RequestData::setBody(std::shared_ptr<RequestBody> body)
{
    this->requestBody = body;
}

std::string RequestData::getMethod()
{
    if (this->method.empty()) {
        throw exception::MethodRequiredException();
    }

    return this->method;
}

std::string RequestData::getUri()
{
    if (this->uri.empty()) {
        throw exception::UriRequiredException();
    }

    return this->uri;
}

nonUniqueMap RequestData::getHeaders()
{
    return this->headers;
}

std::shared_ptr<RequestBody> RequestData::getBody()
{
    return this->requestBody;
}