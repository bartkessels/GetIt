#pragma once

#include <string>

namespace getit::domain
{
    struct RequestBody
    {
        public:
            virtual ~RequestBody() = default;

            virtual std::string getContentType() = 0;
            virtual size_t getSize() = 0;
            virtual std::string getBody() = 0;
    };
}
