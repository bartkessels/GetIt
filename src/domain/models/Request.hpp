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

            void setMethod(std::string method);
            void setUri(std::string uri);
            void addHeader(std::string header, std::string value);

            void setHeaders(std::map<std::string, std::string> headers);
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