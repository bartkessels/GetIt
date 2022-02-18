#pragma once

#include <map>
#include <memory>
#include <string>

#include "domain/models/Request.hpp"

namespace getit::domain::contracts
{
    struct RequestFactory
    {
        public:
            virtual ~RequestFactory() = default;

            virtual std::shared_ptr<models::Request> getRequest(std::string method, std::string uri, std::string body) = 0;
            virtual std::shared_ptr<models::Request> getRequest(std::string method, std::string uri, std::string body, std::string contentType) = 0;
            virtual std::shared_ptr<models::Request> getRequest(std::string method, std::string uri, std::map<std::string, std::string> elements, std::map<std::string, std::string> files, std::string boundary) = 0;
    };
}