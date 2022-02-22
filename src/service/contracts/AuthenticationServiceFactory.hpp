#pragma once

#include <memory>

#include "domain/models/Authentication.hpp"
#include "service/contracts/AuthenticationService.hpp"

using namespace getit::domain;

namespace getit::service::contracts
{
    struct AuthenticationServiceFactory
    {
        public:
            virtual ~AuthenticationServiceFactory() = default;

            virtual std::shared_ptr<AuthenticationService> getAuthenticationService(const std::shared_ptr<models::Authentication>& authentication) = 0;
    };
}