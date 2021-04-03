#pragma once

#include <string>

namespace getit::gui::widget::ResponseBodyWidget
{
    struct IJsonResponseBodyTabView
    {
        public:
            ~IJsonResponseBodyTabView() = default;

            virtual void setBody(std::string body) = 0;
    };
}