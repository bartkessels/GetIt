#pragma once

#include <memory>
#include <utility>

#include "data/contracts/RequestRepository.hpp"
#include "data/contracts/RequestRepositoryFactory.hpp"
#include "data/exceptions/NoAvailableRepositoryException.hpp"
#include "data/repositories/FormDataRequestRepository.hpp"
#include "data/repositories/RawRequestRepository.hpp"
#include "data/repositories/RequestRepository.hpp"
#include "domain/contracts/RequestFactory.hpp"
#include "domain/models/Request.hpp"
#include "domain/implementations/FormDataRequestBody.hpp"
#include "domain/implementations/RawRequestBody.hpp"

namespace getit::data::factories
{
    class RequestRepositoryFactory: public contracts::RequestRepositoryFactory
    {
        public:
            explicit RequestRepositoryFactory(std::shared_ptr<domain::contracts::RequestFactory> factory);
            ~RequestRepositoryFactory() override = default;

            std::shared_ptr<contracts::RequestRepository> getRepository() override;

        private:
            std::shared_ptr<domain::contracts::RequestFactory> factory;
    };
}