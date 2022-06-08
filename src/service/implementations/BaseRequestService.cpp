#include "service/implementations/BaseRequestService.hpp"

using namespace getit::domain::contracts;
using namespace getit::domain::models;
using namespace getit::service::implementations;

void BaseRequestService::setRequestTransformations(std::list<std::shared_ptr<RequestTransformation>> transformations)
{
    this->requestTransformations = transformations;
}

void BaseRequestService::setResponseTransformations(std::list<std::shared_ptr<ResponseTransformation>> transformations)
{
    this->responseTransformations = transformations;
}

std::future<std::shared_ptr<Response>> BaseRequestService::send(std::shared_ptr<Request> request)
{
    for (const auto& transformation : requestTransformations) {
        request = transformation->transform(request);
    }

    return std::async(std::launch::async, [this, request]() {
        std::shared_ptr<Response> response = sendRequest(request).get();

        for (const auto& transformation : responseTransformations) {
            response = transformation->transform(response);
        }

        return response;
    });
}