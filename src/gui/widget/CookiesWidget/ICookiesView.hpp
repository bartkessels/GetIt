#pragma once

#include <list>
#include <string>
#include <utility>

namespace getit::gui::widget
{
    struct ICookiesView
    {
        public:
            ~ICookiesView() = default;

            virtual std::list<std::pair<std::string, std::string>> getCookies() = 0;
            virtual void setCookies(std::list<std::pair<std::string, std::string>> cookies) = 0;
    };
}