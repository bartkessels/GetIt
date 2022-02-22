#pragma once

#include "domain/models/Authentication.hpp"

namespace getit::domain::implementations
{
    class OAuth2Authentication : public models::Authentication
    {
        public:
            OAuth2Authentication() = default;
            ~OAuth2Authentication() override = default;
    };
}