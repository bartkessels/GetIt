#pragma once

#include <fstream>
#include <iomanip>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include <utility>

#include "data/contracts/RequestRepository.hpp"
#include "domain/contracts/RequestFactory.hpp"
#include "domain/models/Request.hpp"
#include "domain/implementations/RawRequestBody.hpp"

namespace getit::data::repositories
{
    class RawRequestRepository: public contracts::RequestRepository
    {
        public:
            explicit RawRequestRepository(std::shared_ptr<domain::contracts::RequestFactory> factory);
            ~RawRequestRepository() override = default;

            void saveRequest(const std::string& filePath, std::shared_ptr<domain::models::Request> request) override;
            std::shared_ptr<domain::models::Request> loadRequest(const std::string& filePath) override;

        private:
            std::shared_ptr<domain::contracts::RequestFactory> factory;

            const std::string BODY_NAME = "body";
            const std::string CONTENT_TYPE_NAME = "contentType";
    };
}