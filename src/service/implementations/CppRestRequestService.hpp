#pragma once

#include <cpprest/http_client.h>
#include <future>
#include <memory>
#include <list>

#include "domain/contracts/Transformation.hpp"
#include "domain/models/Request.hpp"
#include "domain/models/Response.hpp"
#include "service/implementations/BaseRequestService.hpp"

using namespace getit::domain::models;

namespace getit::service::implementations
{
    class CppRestRequestService: public BaseRequestService
    {
        public:
            ~CppRestRequestService() override = default;

            std::future<std::shared_ptr<Response>> sendRequest(std::shared_ptr<Request> request) override;
    };
}