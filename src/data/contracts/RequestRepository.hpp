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

            virtual void saveRequest(std::string filePath, std::shared_ptr<domain::models::Request> request) = 0;
            virtual std::shared_ptr<domain::models::Request> loadRequest(std::string filePath) = 0;
            
            static inline
            const std::string METHOD_NAME = "method";

            static inline
            const std::string URI_NAME = "uri";
    };
}