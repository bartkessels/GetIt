#pragma once

#include "gui/widget/ResponseRawBodyWidget/ResponseRawBodyView.hpp"
#include "gui/AfterWidgetController.hpp"

namespace getit::gui::widget
{
    class ResponseRawBodyController: public AfterWidgetController
    {
        public:
            ~ResponseRawBodyController() = default;

            void executeAfterRequest(std::shared_ptr<getit::domain::Response> response);
    };
}