#pragma once

#include <future>
#include <memory>
#include <list>

#include "domain/contracts/Transformation.hpp"
#include "domain/models/Request.hpp"
#include "domain/models/Response.hpp"

namespace getit::service::contracts
{
    struct RequestService
    {
        public:
            virtual ~RequestService() = default;

            virtual void setTransformations(std::list<std::shared_ptr<domain::contracts::Transformation>> transformations) = 0;
            virtual std::future<std::shared_ptr<domain::models::Response>> send(std::shared_ptr<domain::models::Request> request) = 0;
    };
}