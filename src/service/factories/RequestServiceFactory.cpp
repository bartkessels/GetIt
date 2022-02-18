#include "service/factories/RequestServiceFactory.hpp"

using namespace getit::service::factories;

std::shared_ptr<getit::service::contracts::RequestService> RequestServiceFactory::getRequestService()
{
    return std::make_shared<getit::service::implementations::CppRestRequestService>();
}