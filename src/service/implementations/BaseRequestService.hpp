#pragma once

#include <future>
#include <memory>

#include "domain/models/Response.hpp"
#include "domain/models/Request.hpp"
#include "domain/contracts/RequestTransformation.hpp"
#include "domain/contracts/ResponseTransformation.hpp"
#include "service/contracts/RequestService.hpp"

using namespace getit::domain::contracts;
using namespace getit::domain::models;

namespace getit::service::implementations
{
    class BaseRequestService : public contracts::RequestService
    {
        public:
            virtual ~BaseRequestService() override = default;

            void setRequestTransformations(std::list<std::shared_ptr<RequestTransformation>> transformations) override;
            void setResponseTransformations(std::list<std::shared_ptr<ResponseTransformation>> transformations) override;
            std::future<std::shared_ptr<Response>> send(std::shared_ptr<Request> request) override;

        protected:
            virtual std::future<std::shared_ptr<Response>> sendRequest(std::shared_ptr<Request> request) = 0;

        private:
            std::list<std::shared_ptr<RequestTransformation>> requestTransformations;
            std::list<std::shared_ptr<ResponseTransformation>> responseTransformations;
    };
}