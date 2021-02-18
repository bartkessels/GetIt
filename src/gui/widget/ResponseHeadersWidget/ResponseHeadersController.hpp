#pragma once

#include <map>

#include "gui/widget/ResponseHeadersWidget/ResponseHeadersView.hpp"
#include "gui/AfterWidgetController.hpp"

namespace getit::gui::widget
{
    class ResponseHeadersController: public AfterWidgetController
    {
        public:
            ~ResponseHeadersController() = default;

            void executeAfterRequest(std::shared_ptr<getit::domain::Response> response);
    };
}