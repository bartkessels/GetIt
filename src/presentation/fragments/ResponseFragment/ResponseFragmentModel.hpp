#pragma once

#include <map>
#include <string>

namespace getit::presentation::fragments
{
    struct ResponseFragmentModel
    {
        public:
            std::map<std::string, std::string> headers;
            std::string body;
    };
}