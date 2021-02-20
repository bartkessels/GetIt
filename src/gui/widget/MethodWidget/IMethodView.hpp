#pragma once

#include <string>

namespace getit::gui::widget
{
    struct IMethodView
    {
        public:
            ~IMethodView() = default;

            virtual std::string getMethod() = 0;
            virtual void setMethod(std::string method) = 0;
    };
}