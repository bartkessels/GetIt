#include "domain/implementations/RawRequestBody.hpp"

using namespace getit::domain::implementations;

RawRequestBody::RawRequestBody(std::string contentType):
    contentType(std::move(contentType))
{

}

RawRequestBody::RawRequestBody():
        RawRequestBody(DEFAULT_CONTENT_TYPE)
{

}

void RawRequestBody::setContentType(std::string contentType)
{
    this->contentType = contentType;
}

void RawRequestBody::setBody(std::string body)
{
    this->body = body;
}

std::string RawRequestBody::getBody()
{
    return this->body;
}

std::string RawRequestBody::getContentType()
{
    return this->contentType;
}