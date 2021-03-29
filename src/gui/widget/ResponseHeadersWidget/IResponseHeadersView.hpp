#pragma once

#include <map>
#include <string>

namespace getit::gui::widget
{
    struct IResponseHeadersView
    {
        public:
            ~IResponseHeadersView() = default;

            virtual void setHeaders(std::map<std::string, std::string> headers) = 0;
    };
}