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
            explicit FormDataRequestRepository(std::shared_ptr<domain::contracts::RequestFactory> factory, std::shared_ptr<domain::models::Request> request);
            ~FormDataRequestRepository() override = default;

            void saveRequest(std::string filePath) override;
            std::shared_ptr<domain::models::Request> loadRequest(std::string filePath) override;

        private:
            std::shared_ptr<domain::contracts::RequestFactory> factory;

            static inline
            const std::string BOUNDARY_NAME = "boundary";

            static inline
            const std::string BODY_TYPE_NAME = "formdata";

            static inline
            const std::string ELEMENTS_ARRAY_NAME = "elements";

            static inline
            const std::string FILES_ARRAY_NAME = "files";

            static inline
            const std::string KEY_NAME = "key";

            static inline
            const std::string ELEMENT_VALUE_NAME = "value";

            static inline
            const std::string FILE_PATH_NAME = "filePath";
    };
}