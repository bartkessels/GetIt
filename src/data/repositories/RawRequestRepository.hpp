#pragma once

#include <fstream>
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

            void saveRequest(std::string filePath, std::shared_ptr<domain::models::Request> request) override;
            std::shared_ptr<domain::models::Request> loadRequest(std::string filePath) override;

        private:
            std::shared_ptr<domain::contracts::RequestFactory> factory;

            static inline
            const std::string BODY_TYPE_NAME = "raw";

            static inline
            const std::string BODY_NAME = "body";

            static inline
            const std::string CONTENT_TYPE_NAME = "contentType";
    };
}