#pragma once

#include <memory>

#include "service/contracts/RequestService.hpp"

namespace getit::service::contracts
{
    struct RequestServiceFactory
    {
        public:
            virtual ~RequestServiceFactory() = default;

            virtual std::shared_ptr<contracts::RequestService> getRequestService() = 0;
    };
}