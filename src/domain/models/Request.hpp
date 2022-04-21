#pragma once

#include <list>
#include <map>
#include <memory>
#include <string>

#include "domain/models/RequestBody.hpp"
#include "domain/models/Variable.hpp"

namespace getit::domain::models
{
    class Request
    {
        public:
            Request() = default;
            ~Request() = default;

            void setMethod(const std::string& method);
            void setUri(const std::string& uri);
            void addHeader(const std::string& header, const std::string& value);

            void setVariables(std::list<std::shared_ptr<Variable>> variables);
            void setHeaders(const std::map<std::string, std::string>& headers);
            void setBody(std::shared_ptr<RequestBody> body);

            std::string getMethod();
            std::string getUri();
            std::list<std::shared_ptr<Variable>> getVariables();
            std::map<std::string, std::string> getHeaders();
            std::shared_ptr<RequestBody> getBody();

        private:
            std::string method;
            std::string uri;
            std::list<std::shared_ptr<Variable>> variables;
            std::map<std::string, std::string> headers;
            std::shared_ptr<RequestBody> body;
    };
}