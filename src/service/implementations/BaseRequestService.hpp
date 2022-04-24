#pragma once

#include <memory>

#include "domain/models/Response.hpp"
#include "domain/models/Request.hpp"
#include "service/contracts/RequestService.hpp"

using namespace getit::domain::contracts;
using namespace getit::domain::models;

namespace getit::service::implementations
{
    class BaseRequestService : public contracts::RequestService
    {
        public:
            virtual ~BaseRequestService() = default;

            void setTransformations(std::list<std::shared_ptr<Transformation>> transformations) override;
            std::future<std::shared_ptr<Response>> send(std::shared_ptr<Request> request) override;

        protected:
            virtual std::future<std::shared_ptr<Response>> sendRequest(std::shared_ptr<Request> request) = 0;

        private:
            std::list<std::shared_ptr<Transformation>> transformations;
    };
}