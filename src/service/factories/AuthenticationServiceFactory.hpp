#pragma once

#include <memory>

#include "domain/implementations/OAuth2Authentication.hpp"
#include "domain/models/Authentication.hpp"

#include "service/contracts/AuthenticationService.hpp"
#include "service/contracts/AuthenticationServiceFactory.hpp"

using namespace getit::domain;

namespace getit::service::factories
{
    class AuthenticationServiceFactory : public contracts::AuthenticationServiceFactory
    {
        public:
            AuthenticationServiceFactory() = default;
            ~AuthenticationServiceFactory() override = default;

            std::shared_ptr<contracts::AuthenticationService> getAuthenticationService(const std::shared_ptr<models::Authentication>& authentication) override;
    };
}