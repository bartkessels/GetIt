#pragma once

#include <memory>

#include "domain/models/Request.hpp"

namespace getit::domain::contracts
{
    struct RequestTransformation
    {
        public:
            virtual ~RequestTransformation() = default;

            virtual std::shared_ptr<models::Request> transform(std::shared_ptr<models::Request> request) = 0;
    };
}