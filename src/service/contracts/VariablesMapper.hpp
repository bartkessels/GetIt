#pragma once

#include <memory>

#include "domain/models/Request.hpp"

using namespace getit::domain;

namespace getit::service::contracts
{
    class VariablesMapper
    {
        public:
            virtual ~VariablesMapper() = default;

            virtual std::shared_ptr<models::Request> map(std::shared_ptr<models::Request> request) = 0;
    };
}