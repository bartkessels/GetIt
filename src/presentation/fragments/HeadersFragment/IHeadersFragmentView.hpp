#pragma once

#include <map>
#include <string>

namespace getit::presentation::fragments
{
    struct IHeadersFragmentView
    {
        public:
            virtual ~IHeadersFragmentView() = default;

            virtual std::map<std::string, std::string> getHeaders() = 0;
            virtual void setHeaders(const std::map<std::string, std::string>& headers) = 0;
    };
}