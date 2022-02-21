#pragma once

#include <memory>

#include "service/contracts/RequestService.hpp"
#include "service/contracts/RequestServiceFactory.hpp"
#include "service/implementations/CppRestRequestService.hpp"

namespace getit::service::factories
{
    class RequestServiceFactory : public contracts::RequestServiceFactory
    {
        public:
            ~RequestServiceFactory() override = default;

            std::shared_ptr<contracts::RequestService> getRequestService() override;
    };
}