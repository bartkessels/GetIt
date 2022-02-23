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
#include "domain/implementations/FormDataRequestBody.hpp"

namespace getit::data::repositories
{
    class FormDataRequestRepository: public contracts::RequestRepository
    {
        public:
            explicit FormDataRequestRepository(std::shared_ptr<domain::contracts::RequestFactory> factory);
            ~FormDataRequestRepository() override = default;

            void saveRequest(const std::string& filePath, std::shared_ptr<domain::models::Request> request) override;
            std::shared_ptr<domain::models::Request> loadRequest(const std::string& filePath) override;

        private:
            std::shared_ptr<domain::contracts::RequestFactory> factory;

            const std::string BOUNDARY_NAME = "boundary";
            const std::string ELEMENTS_ARRAY_NAME = "elements";
            const std::string FILES_ARRAY_NAME = "files";
            const std::string KEY_NAME = "key";
            const std::string ELEMENT_VALUE_NAME = "value";
            const std::string FILE_PATH_NAME = "filePath";
    };
}