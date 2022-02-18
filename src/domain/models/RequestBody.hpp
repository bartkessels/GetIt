#pragma once

#include <string>

namespace getit::domain::models
{
    struct RequestBody
    {
        public:
            virtual ~RequestBody() = default;

            virtual std::string getBody() = 0;
            virtual std::string getContentType() = 0;
    };
}