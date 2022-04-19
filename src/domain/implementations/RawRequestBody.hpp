#pragma once

#include <string>

#include "domain/models/RequestBody.hpp"

namespace getit::domain::implementations
{
    class RawRequestBody: public models::RequestBody
    {
        public:
            explicit RawRequestBody(std::string contentType);
            RawRequestBody();
            ~RawRequestBody() override = default;

            void setContentType(std::string contentType);
            void setBody(std::string body);
            
            std::string getBody() override;
            std::string getContentType() override;

        private:
            std::string body;
            std::string contentType;

            const std::string DEFAULT_CONTENT_TYPE = "text/plain";
    };
}