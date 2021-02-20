#pragma once

#include <string>

namespace getit::gui::widget
{
    struct IUriView
    {
        public:
            ~IUriView() = default;

            virtual std::string getUri() = 0;
            virtual void setUri(std::string uri) = 0;
    };
}