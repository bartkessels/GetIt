#pragma once

#include <list>
#include <memory>
#include <string>
#include <utility>

#include "domain/exception/MethodRequiredException.hpp"
#include "domain/exception/UriRequiredException.hpp"
#include "domain/RequestBody.hpp"

typedef std::list<std::pair<std::string, std::string>> nonUniqueMap;

namespace getit::domain
{
    class RequestData
    {
        public:
            RequestData() = default;
            ~RequestData() = default;

            void setMethod(std::string method);
            void setUri(std::string uri);
            void addHeader(std::string header, std::string value);
            void setBody(std::shared_ptr<RequestBody> body);

            std::string getMethod();
            std::string getUri();
            nonUniqueMap getHeaders();
            std::shared_ptr<RequestBody> getBody();

        private:
            std::string method;
            std::string uri;
            nonUniqueMap headers;
            std::shared_ptr<RequestBody> requestBody;
    };
}