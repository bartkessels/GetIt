#pragma once

#include <map>
#include <string>

namespace getit::presentation::fragments
{
    struct IResponseFragmentView
    {
        public:
            virtual ~IResponseFragmentView() = default;

            virtual std::map<std::string, std::string> getHeaders() = 0;
            virtual std::string getBody() = 0;

            virtual void setHeaders(const std::map<std::string, std::string>& headers) = 0;
            virtual void setBody(const std::string& body) = 0;

            virtual void clearHeaders() = 0;
    };
}