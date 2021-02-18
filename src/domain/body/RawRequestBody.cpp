#include "domain/body/RawRequestBody.hpp"

using namespace getit::domain::body;

RawRequestBody::RawRequestBody(std::string contentType):
    contentType(std::move(contentType))
{
    
}

RawRequestBody::RawRequestBody():
    RawRequestBody(DEF_CONTENT_TYPE)
{
    
}

void RawRequestBody::setBody(std::string body)
{
    this->body = std::move(body);
}

std::string RawRequestBody::getContentType()
{
    return this->contentType;
}

std::string RawRequestBody::getBody()
{
    return this->body;
}

size_t RawRequestBody::getSize()
{
    return this->body.size();
}
