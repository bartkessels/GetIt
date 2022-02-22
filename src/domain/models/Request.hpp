#pragma once

#include <map>
#include <string>

#include "domain/models/Authentication.hpp"
#include "domain/models/RequestBody.hpp"

namespace getit::domain::models
{
    class Request
    {
        public:
            Request() = default;
            ~Request() = default;
            
            void setMethod(const std::string& method);
            void setUri(const std::string& uri);
            void setHeaders(const std::map<std::string, std::string>& headers);
            void setBody(std::shared_ptr<RequestBody> body);

            std::string getMethod();
            std::string getUri();
            std::map<std::string, std::string> getHeaders();
            std::shared_ptr<RequestBody> getBody();

        private:
            std::string method;
            std::string uri;
            std::map<std::string, std::string> headers;
            std::shared_ptr<RequestBody> body;
    };
}