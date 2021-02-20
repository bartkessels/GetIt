#pragma once

#include <string>

namespace getit::gui::widget::BodyWidget
{
    struct IRawBodyTabView
    {
        public:
            ~IRawBodyTabView() = default;

            virtual std::string getContentType() = 0;
            virtual std::string getBody() = 0;

            virtual void setContentType(std::string contentType) = 0;
            virtual void setBody(std::string body) = 0;
    };
}