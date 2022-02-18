#pragma once

#include <future>
#include <memory>

#include "domain/models/Request.hpp"
#include "domain/models/Response.hpp"

namespace getit::service::contracts
{
    struct RequestService
    {
        public:
            virtual ~RequestService() = default;

            virtual std::future<std::shared_ptr<domain::models::Response>> send(std::shared_ptr<domain::models::Request> request) = 0;
    };
}