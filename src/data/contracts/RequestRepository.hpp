#pragma once

#include <memory>
#include <string>
#include <utility>

#include "domain/models/Request.hpp"

namespace getit::data::contracts
{
    struct RequestRepository
    {
        public:
            explicit RequestRepository(std::shared_ptr<domain::models::Request> request): request(std::move(request)) {}
            virtual ~RequestRepository() = default;

            virtual void saveRequest(std::string filePath) = 0;
            virtual std::shared_ptr<domain::models::Request> loadRequest(std::string filePath) = 0;
            
            static inline
            const std::string METHOD_NAME = "method";

            static inline
            const std::string URI_NAME = "uri";

        protected:
            std::shared_ptr<domain::models::Request> request;
    };
}