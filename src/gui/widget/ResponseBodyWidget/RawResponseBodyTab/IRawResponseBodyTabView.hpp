#pragma once

#include <string>

namespace getit::gui::widget::ResponseBodyWidget
{
    struct IRawResponseBodyTabView
    {
        public:
            ~IRawResponseBodyTabView() = default;

            virtual void setBody(std::string body) = 0;
    };
}