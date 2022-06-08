#pragma once

#include <future>
#include <memory>
#include <list>

#include "domain/contracts/RequestTransformation.hpp"
#include "domain/contracts/ResponseTransformation.hpp"
#include "domain/models/Request.hpp"
#include "domain/models/Response.hpp"

using namespace getit::domain::contracts;
using namespace getit::domain::models;

namespace getit::service::contracts
{
    struct RequestService
    {
        public:
            virtual ~RequestService() = default;

            virtual void setRequestTransformations(std::list<std::shared_ptr<RequestTransformation>> transformations) = 0;
            virtual void setResponseTransformations(std::list<std::shared_ptr<ResponseTransformation>> transformations) = 0;
            virtual std::future<std::shared_ptr<Response>> send(std::shared_ptr<domain::models::Request> request) = 0;
    };
}