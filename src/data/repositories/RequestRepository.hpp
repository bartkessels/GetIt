#pragma once

#include <fstream>
#include <iomanip>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include <utility>

#include "data/contracts/RequestRepository.hpp"
#include "data/exceptions/NoAvailableRepositoryException.hpp"
#include "data/repositories/FormDataRequestRepository.hpp"
#include "data/repositories/RawRequestRepository.hpp"

#include "domain/contracts/RequestFactory.hpp"
#include "domain/implementations/FormDataRequestBody.hpp"
#include "domain/implementations/RawRequestBody.hpp"
#include "domain/models/Request.hpp"

namespace getit::data::repositories
{
    class RequestRepository : public contracts::RequestRepository
    {
        public:
            explicit RequestRepository(std::shared_ptr<contracts::RequestRepository> formDataRepository, std::shared_ptr<contracts::RequestRepository> rawRepository);
            ~RequestRepository() override = default;

            void saveRequest(const std::string& filePath, std::shared_ptr<domain::models::Request> request) override;
            std::shared_ptr<domain::models::Request> loadRequest(const std::string& filePath) override;

        private:
            std::shared_ptr<contracts::RequestRepository> formDataRepository;
            std::shared_ptr<contracts::RequestRepository> rawRepository;
    };
}