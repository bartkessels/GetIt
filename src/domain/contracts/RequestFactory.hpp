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

            virtual std::shared_ptr<models::Request> getRequest(const std::string& method, const std::string& uri, std::map<std::string, std::string> headers) = 0;
            virtual std::shared_ptr<models::Request> getRequest(const std::string& method, const std::string& uri, std::map<std::string, std::string> headers, const std::string& body) = 0;
            virtual std::shared_ptr<models::Request> getRequest(const std::string& method, const std::string& uri, std::map<std::string, std::string> headers, const std::string& body, const std::string& contentType) = 0;
            virtual std::shared_ptr<models::Request> getRequest(const std::string& method, const std::string& uri, std::map<std::string, std::string> headers, std::map<std::string, std::string> elements, std::map<std::string, std::string> files, const std::string& boundary) = 0;
    };
}