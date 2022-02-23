#include "data/repositories/RequestRepository.hpp"

using namespace getit::data::repositories;

RequestRepository::RequestRepository(std::shared_ptr<contracts::RequestRepository> formDataRepository, std::shared_ptr<contracts::RequestRepository> rawRepository):
    formDataRepository(std::move(formDataRepository)),
    rawRepository(std::move(rawRepository))
{

}

void RequestRepository::saveRequest(const std::string& filePath, std::shared_ptr<domain::models::Request> request)
{
    if (std::dynamic_pointer_cast<getit::domain::implementations::FormDataRequestBody>(request->getBody())) {
        formDataRepository->saveRequest(filePath, request);
    } else if (std::dynamic_pointer_cast<getit::domain::implementations::RawRequestBody>(request->getBody())) {
        rawRepository->saveRequest(filePath, request);
    } else {
        throw exceptions::NoAvailableRepositoryException();
    }
}

std::shared_ptr<getit::domain::models::Request> RequestRepository::loadRequest(const std::string& filePath)
{
    auto jsonObject = nlohmann::json::object();

    std::ifstream input(filePath);
    input >> jsonObject;
    input.close();

    if (jsonObject.contains(RAW_BODY_TYPE_NAME)) {
        return rawRepository->loadRequest(filePath);
    } else if (jsonObject.contains(FORM_DATA_BODY_TYPE_NAME)) {
        return formDataRepository->loadRequest(filePath);
    }

    throw exceptions::NoAvailableRepositoryException();
}