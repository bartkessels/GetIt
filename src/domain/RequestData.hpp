#pragma once

#include <map>
#include <memory>
#include <string>

#include "domain/exception/MethodRequiredException.hpp"
#include "domain/exception/UriRequiredException.hpp"
#include "domain/RequestBody.hpp"

namespace getit::domain
{
    class RequestData
    {
        public:
            RequestData() = default;
            ~RequestData() = default;

            void setMethod(std::string method);
            void setUri(std::string uri);
            void addOrUpdateHeader(std::string header, std::string value);
            void setBody(std::shared_ptr<RequestBody> body);

            std::string getMethod();
            std::string getUri();
            std::map<std::string, std::string> getHeaders();
            std::shared_ptr<RequestBody> getBody();

        private:
            std::string method;
            std::string uri;
            std::map<std::string, std::string> headers;
            std::shared_ptr<RequestBody> requestBody;
    };
}