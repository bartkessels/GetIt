#pragma once

#include <memory>
#include <utility>

#include "data/contracts/RequestRepository.hpp"
#include "data/contracts/RequestRepositoryFactory.hpp"
#include "data/exceptions/NoAvailableRepositoryException.hpp"
#include "data/repositories/FormdataRequestRepository.hpp"
#include "data/repositories/RawRequestRepository.hpp"
#include "domain/contracts/RequestFactory.hpp"
#include "domain/models/Request.hpp"
#include "domain/implementations/FormdataRequestBody.hpp"
#include "domain/implementations/RawRequestBody.hpp"

namespace getit::data::factories
{
    class RequestRepositoryFactory: public contracts::RequestRepositoryFactory
    {
        public:
            explicit RequestRepositoryFactory(std::shared_ptr<domain::contracts::RequestFactory> factory);
            ~RequestRepositoryFactory() override = default;

            std::shared_ptr<contracts::RequestRepository> getRepository(std::shared_ptr<domain::models::Request> request) override;

        private:
            std::shared_ptr<domain::contracts::RequestFactory> factory;
    };
}