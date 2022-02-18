#pragma once

#include <map>
#include <string>

namespace getit::domain::models
{
    struct Response
    {
        public:
            ~Response() = default;

            std::map<std::string, std::string> headers;
            std::string body;
    };
}