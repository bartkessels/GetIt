#pragma once

#include <memory>

#include "domain/models/Request.hpp"
#include "domain/models/Response.hpp"

namespace getit::presentation::tabs
{
    struct RequestTabController
    {
        public:
            virtual ~RequestTabController() = default;

            virtual void setRequest(std::shared_ptr<domain::models::Request> request) = 0;
            virtual void setResponse(std::shared_ptr<domain::models::Response> response) = 0;

            virtual std::shared_ptr<domain::models::Request> getRequest() = 0;
    };
}