#include "data/factories/RequestRepositoryFactory.hpp"

using namespace getit::data::factories;

RequestRepositoryFactory::RequestRepositoryFactory(std::shared_ptr<domain::contracts::RequestFactory> factory):
    factory(std::move(factory))
{

}

std::shared_ptr<getit::data::contracts::RequestRepository> RequestRepositoryFactory::getRepository(std::shared_ptr<domain::models::Request> request)
{
    if (std::dynamic_pointer_cast<getit::domain::implementations::FormDataRequestBody>(request->getBody())) {
        return std::make_shared<getit::data::repositories::FormDataRequestRepository>(this->factory);
    } else if (std::dynamic_pointer_cast<getit::domain::implementations::RawRequestBody>(request->getBody())) {
        return std::make_shared<getit::data::repositories::RawRequestRepository>(this->factory);
    }

    throw exceptions::NoAvailableRepositoryException();
}