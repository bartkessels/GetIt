#include "service/factories/AuthenticationServiceFactory.hpp"

using namespace getit::domain;
using namespace getit::service;
using namespace getit::service::factories;

std::shared_ptr<contracts::AuthenticationService> AuthenticationServiceFactory::getAuthenticationService(const std::shared_ptr<models::Authentication>& authentication)
{

//    if (std::dynamic_pointer_cast<getit::domain::implementations::FormDataRequestBody>(request->getBody())) {
//        return std::make_shared<getit::data::repositories::FormDataRequestRepository>(this->factory);
//    } else if (std::dynamic_pointer_cast<getit::domain::implementations::RawRequestBody>(request->getBody())) {
//        return std::make_shared<getit::data::repositories::RawRequestRepository>(this->factory);
//    }
}