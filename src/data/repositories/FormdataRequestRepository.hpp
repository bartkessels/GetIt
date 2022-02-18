#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include <utility>

#include "data/contracts/RequestRepository.hpp"
#include "domain/contracts/RequestFactory.hpp"
#include "domain/models/Request.hpp"
#include "domain/implementations/FormdataRequestBody.hpp"

namespace getit::data::repositories
{
    class FormdataRequestRepository: public contracts::RequestRepository
    {
        public:
            explicit FormdataRequestRepository(std::shared_ptr<domain::contracts::RequestFactory> factory);
            ~FormdataRequestRepository() override = default;

            void saveRequest(std::string filePath, std::shared_ptr<domain::models::Request> request) override;
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