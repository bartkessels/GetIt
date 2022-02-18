#pragma once

#include <cpprest/http_client.h>
#include <future>
#include <memory>

#include "domain/models/Request.hpp"
#include "domain/models/Response.hpp"
#include "service/contracts/RequestService.hpp"

namespace getit::service::implementations
{
    class CppRestRequestService: public contracts::RequestService
    {
        public:
            ~CppRestRequestService() override = default;

            std::future<std::shared_ptr<domain::models::Response>> send(std::shared_ptr<domain::models::Request> request) override;
    };
}