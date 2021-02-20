#pragma once

#include <list>
#include <string>
#include <utility>

namespace getit::gui::widget
{
    struct IHeadersView
    {
        public:
            ~IHeadersView() = default;

            virtual std::list<std::pair<std::string, std::string>> getHeaders() = 0;
            virtual void setHeaders(std::list<std::pair<std::string, std::string>> headers) = 0;
    };
}