#pragma once

#include <memory>

#include "data/contracts/RequestRepository.hpp"
#include "domain/models/Request.hpp"

namespace getit::data::contracts
{
    struct RequestRepositoryFactory
    {
        public:
            virtual ~RequestRepositoryFactory() = default;

            virtual std::shared_ptr<RequestRepository> getRepository(std::shared_ptr<domain::models::Request> request) = 0;
    };
}