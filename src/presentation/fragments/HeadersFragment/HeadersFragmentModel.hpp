#pragma once

#include <map>
#include <string>

namespace getit::presentation::fragments
{
    struct HeadersFragmentModel
    {
        public:
            ~HeadersFragmentModel() = default;

            std::map<std::string, std::string> headers;
    };
}