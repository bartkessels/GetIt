#pragma once

#include <map>
#include <memory>
#include <string>

#include "domain/models/RequestBody.hpp"

using namespace getit::domain::models;

namespace getit::presentation::windows
{
    struct IMainWindowViewModel
    {
        public:
            virtual ~IMainWindowViewModel() = default;

            virtual void sendRequest(std::string method, std::string uri, std::map<std::string, std::string> headers,
                                     std::shared_ptr<RequestBody> body) = 0;
            virtual void saveRequest(std::string method, std::string uri, std::map<std::string, std::string> headers,
                                     std::shared_ptr<RequestBody> body, const std::string& location) = 0;
            virtual void openRequest(const std::string& location) = 0;
    };
}