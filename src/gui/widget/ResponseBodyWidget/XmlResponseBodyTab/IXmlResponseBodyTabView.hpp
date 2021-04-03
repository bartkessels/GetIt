#pragma once

#include <string>

namespace getit::gui::widget::ResponseBodyWidget
{
    struct IXmlResponseBodyTabView
    {
        public:
            ~IXmlResponseBodyTabView() = default;

            virtual void setBody(std::string string) = 0;
    };
}