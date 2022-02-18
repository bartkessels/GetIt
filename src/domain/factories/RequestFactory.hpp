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

            std::shared_ptr<models::Request> getRequest(std::string method, std::string uri, std::string body) override;
            std::shared_ptr<models::Request> getRequest(std::string method, std::string uri, std::string body, std::string contentType) override;
            std::shared_ptr<models::Request> getRequest(std::string method, std::string uri, std::map<std::string, std::string> elements, std::map<std::string, std::string> files, std::string boundary) override;

        private:
            static std::shared_ptr<models::Request> getRequest(std::string method, std::string uri);
    };
}