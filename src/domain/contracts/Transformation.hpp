#pragma once

#include <memory>

#include "domain/models/Request.hpp"

namespace getit::domain::contracts
{
    struct Transformation
    {
        public:
            virtual ~Transformation() = default;

            virtual std::shared_ptr<domain::models::Request> transform(std::shared_ptr<domain::models::Request> request) = 0;
    };
}