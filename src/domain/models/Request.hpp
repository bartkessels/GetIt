#pragma once

#include <map>
#include <memory>
#include <string>

#include "domain/models/RequestBody.hpp"
#include "domain/models/Variables.hpp"

namespace getit::domain::models
{
    class Request
    {
        public:
            Request() = default;
            ~Request() = default;
            
            void setMethod(const std::string& method);
            void setUri(const std::string& uri);

            void setVariables(std::shared_ptr<Variables> variables);
            void setHeaders(const std::map<std::string, std::string>& headers);
            void setBody(std::shared_ptr<RequestBody> body);

            std::string getMethod();
            std::string getUri();
            std::shared_ptr<Variables> getVariables();
            std::map<std::string, std::string> getHeaders();
            std::shared_ptr<RequestBody> getBody();

        private:
            std::string method;
            std::string uri;
            std::shared_ptr<Variables> variables;
            std::map<std::string, std::string> headers;
            std::shared_ptr<RequestBody> body;
    };
}
