#include "data/factories/RequestRepositoryFactory.hpp"

using namespace getit::data::factories;

RequestRepositoryFactory::RequestRepositoryFactory(std::shared_ptr<domain::contracts::RequestFactory> factory):
    factory(std::move(factory))
{

}

std::shared_ptr<getit::data::contracts::RequestRepository> RequestRepositoryFactory::getRepository()
{
    const auto& formDataRequestRepository = std::make_shared<repositories::FormDataRequestRepository>(factory);
    const auto& rawRequestRepository = std::make_shared<repositories::RawRequestRepository>(factory);

    return std::make_shared<repositories::RequestRepository>(formDataRequestRepository, rawRequestRepository);
}