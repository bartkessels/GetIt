#pragma once

#include <memory>

#include "domain/models/Response.hpp"

namespace getit::domain::contracts
{
    struct ResponseTransformation
    {
        public:
            virtual ~ResponseTransformation() = default;

            virtual std::shared_ptr<models::Response> transform(std::shared_ptr<models::Response> response) = 0;
    };
}