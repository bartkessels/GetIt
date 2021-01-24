#pragma once

#include "gui/widget/MethodWidget/MethodView.hpp"
#include "gui/BeforeWidgetController.hpp"

namespace getit::gui::widget
{
    class MethodController: public BeforeWidgetController
    {
        public:
            ~MethodController() = default;

            void executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data);
    };
}