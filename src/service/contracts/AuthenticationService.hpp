#pragma once

#include <string>

namespace getit::service::contracts
{
    struct AuthenticationService
    {
        public:
            virtual ~AuthenticationService() = default;

            virtual std::string requestToken() = 0;
    };
}