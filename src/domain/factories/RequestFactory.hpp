#pragma once

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "domain/contracts/RequestFactory.hpp"
#include "domain/implementations/FormdataRequestBody.hpp"
#include "domain/implementations/RawRequestBody.hpp"
#include "domain/models/Request.hpp"

namespace getit::domain::factories
{
    class RequestFactory: public contracts::RequestFactory
    {
        public:
            ~RequestFactory() override = default;

            static std::shared_ptr<models::Request> getRequest(const std::string& method, const std::string& uri);
            std::shared_ptr<models::Request> getRequest(const std::string& method, const std::string& uri, const std::string& body) override;
            std::shared_ptr<models::Request> getRequest(const std::string& method, const std::string& uri, const std::string& body, const std::string& contentType) override;
            std::shared_ptr<models::Request> getRequest(const std::string& method, const std::string& uri, std::map<std::string, std::string> elements, std::map<std::string, std::string> files, const std::string& boundary) override;
    };
}