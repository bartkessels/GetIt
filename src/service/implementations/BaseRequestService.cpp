#include "service/implementations/BaseRequestService.hpp"

using namespace getit::domain::contracts;
using namespace getit::domain::models;
using namespace getit::service::implementations;

void BaseRequestService::setTransformations(std::list<std::shared_ptr<Transformation>> transformations)
{
    this->transformations = transformations;
}

std::future<std::shared_ptr<Response>> BaseRequestService::send(std::shared_ptr<Request> request)
{
    for (const auto& transformation : transformations) {
        request = transformation->transform(request);
    }

    return sendRequest(request);
}