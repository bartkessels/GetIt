#pragma once

#include <memory>

#include "service/contracts/RequestService.hpp"
#include "service/implementations/CppRestRequestService.hpp"

namespace getit::service::factories
{
    class RequestServiceFactory
    {
        public:
            ~RequestServiceFactory() = default;

            std::shared_ptr<contracts::RequestService> getRequestService();
    };
}