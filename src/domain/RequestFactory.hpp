#pragma once

#include <memory>

#include "domain/Request.hpp"

namespace getit::domain
{
    class RequestFactory
    {
        public:
            RequestFactory() = default;
            ~RequestFactory() = default;

            static std::shared_ptr<Request> getRequest();
    };
}