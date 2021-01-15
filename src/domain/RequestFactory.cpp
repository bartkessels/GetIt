#include "domain/RequestFactory.hpp"
#include "domain/request/CppRestRequest.hpp"

using namespace getit::domain;

std::shared_ptr<Request> RequestFactory::getRequest()
{
    return std::make_shared<request::CppRestRequest>();
}