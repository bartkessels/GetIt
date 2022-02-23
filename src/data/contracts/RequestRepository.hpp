#pragma once

#include <memory>
#include <string>

#include "domain/models/Request.hpp"

namespace getit::data::contracts
{
    struct RequestRepository
    {
        public:
            virtual ~RequestRepository() = default;

            virtual void saveRequest(const std::string& filePath, std::shared_ptr<domain::models::Request> request) = 0;
            virtual std::shared_ptr<domain::models::Request> loadRequest(const std::string& filePath) = 0;

        protected:
            const std::string METHOD_NAME = "method";
            const std::string URI_NAME = "uri";
            const std::string FORM_DATA_BODY_TYPE_NAME = "formdata";
            const std::string RAW_BODY_TYPE_NAME = "raw";
    };
}